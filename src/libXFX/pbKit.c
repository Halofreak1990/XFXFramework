//pbKit core functions
//see AFL license

//#define DBG
//#define LOG
#include <hal/video.h>
#include <hal/xbox.h>
#include <hal/io.h>
#include <xboxkrnl/xboxkrnl.h>
#include <openxdk/debug.h>

#include "pbKit.h"
#include "outer.h"
#include "nv_objects.h"  //shared with renouveau files
#include "nv20_shader.h" //(search "nouveau" on wiki)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



#define INSTANCE_MEM_MAXSIZE				0x5000	//20Kb

#define ADDR_SYSMEM					1
#define ADDR_FBMEM					2
#define ADDR_AGPMEM					3

#define DMA_CLASS_2					2
#define DMA_CLASS_3					3
#define DMA_CLASS_3D					0x3D

#define GR_CLASS_30					0x30
#define GR_CLASS_39					0x39
#define GR_CLASS_62					0x62
#define GR_CLASS_97					0x97
#define GR_CLASS_9F					0x9F

#define GPU_IRQ						3

#define XTAL_16MHZ					16.6667f
#define DW_XTAL_16MHZ				16666666

#define MAX_EXTRA_BUFFERS			8

#define MAXRAM						0x03FFAFFF

#define NONE						-1

#define TICKSTIMEOUT					100	//if Dma doesn't react in that time, send a warning

#define PB_SETOUTER					0xB2A
#define PB_SETNOISE					0xBAA
#define	PB_FINISHED					0xFAB

struct s_CtxDma
{
	DWORD				ChannelID;
	DWORD				Inst;	//Addr in PRAMIN area, unit=16 bytes blocks, baseaddr=VIDEO_BASE+NV_PRAMIN
	DWORD				Class;
	DWORD				isGr;
};

struct s_PseudoReg
{
	int reg;
	int num;
	union {
		int msk;
		int swz;
	};
	int mod;
	int idx;
};

struct s_PseudoRegs
{
	int			n;
	struct s_PseudoReg	dest;
	struct s_PseudoReg	src0;
	struct s_PseudoReg	src1;
	struct s_PseudoReg	src2;
};

static	int			pb_running=0;

static	DWORD			pb_vbl_counter=0;

#ifdef DBG
static int			pb_trace_mode=1;
#else
static int			pb_trace_mode=0;
#endif
				//if set, we wait after each block sending (pb_end) 
				//so we are sure GPU received all the data (slower)
				//and that any GPU error comes from last block sent.

static	int			pb_disable_gpu=0;
				//if set, prevents GPU from delaying CPU when FIFO is
				//full (allows to see how fast CPU code is fast alone)

static	KINTERRUPT		pb_InterruptObject;
static	KDPC			pb_DPCObject;

static	HANDLE			pb_VBlankEvent;

static	DWORD			pb_OldMCEnable;
static	DWORD			pb_OldMCInterrupt;
static	DWORD			pb_OldFBConfig0;
static	DWORD			pb_OldFBConfig1;
static	DWORD			pb_OldVideoStart;

static	DWORD			*pb_DmaBuffer8;	//points at 32 contiguous bytes (Dma Channel ID 8 buffer)
static	DWORD			*pb_DmaBuffer2;	//points at 32 contiguous bytes (Dma Channel ID 2 buffer)
static	DWORD			*pb_DmaBuffer7;	//points at 32 contiguous bytes (Dma Channel ID 7 buffer)

static	DWORD			pb_Size=512*1024;//push buffer size, must be >64Kb and a power of 2
static	DWORD			*pb_Head;	//points at push buffer head
static	DWORD			*pb_Tail;	//points at push buffer tail
static	DWORD			*pb_Put=NULL;	//where next command+params are to be written

static	float			pb_CpuFrequency;

static	DWORD			pb_GpuInstMem;

static	DWORD			pb_PushBase;
static	DWORD			pb_PushLimit;

static	DWORD			pb_FifoHTAddr;
static	DWORD			pb_FifoFCAddr;
static	DWORD			pb_FifoU1Addr;

static	DWORD			pb_3DGrCtxInst[2]={0,0};//Adress of the two 3D graphic contexts (addr=inst<<4+NV_PRAMIN)
static	DWORD			pb_GrCtxTableInst;	//Adress of the table that points at the two graphic contexts
static	DWORD			pb_GrCtxInst[2];	//Adress of the two graphic contexts (addr=inst<<4+NV_PRAMIN)
static	int			pb_GrCtxID;		//Current context ID : 0,1 or NONE

static	DWORD			pb_FifoBigInst;		//graphic contexts are stored there, and much more (addr=inst<<4+NV_PRAMIN)

static	DWORD			pb_FreeInst;		//next free space in PRAMIN area (addr=inst<<4+NV_PRAMIN)

static	int			pb_GammaRampIdx=0;
static	int			pb_GammaRampbReady[3]={0,0,0};
static	BYTE			pb_GammaRamp[3][3][256];

static	int			pb_BackBufferNxt=0;
static	int			pb_BackBufferNxtVBL=0;
static	int			pb_BackBufferbReady[3]={0,0,0};
static	int			pb_BackBufferIndex[3];

static	DWORD			pb_FifoChannelsReady=0;
static	DWORD			pb_FifoChannelsMode=NV_PFIFO_MODE_ALL_PIO;
static	DWORD			pb_FifoChannelID=0;

static	DWORD			pb_PutRunSize=0;
static	DWORD			pb_GetRunSize;

static	DWORD			pb_FrameBuffersCount;
static	DWORD			pb_FrameBuffersWidth;
static	DWORD			pb_FrameBuffersHeight;
static	DWORD			pb_FrameBuffersAddr;
static	DWORD			pb_FrameBuffersPitch;
static	DWORD			pb_FBAddr[3];		//frame buffers addresses
static	DWORD			pb_FBSize;		//size of 1 buffer
static	DWORD			pb_FBGlobalSize;	//size of all buffers
static	DWORD			pb_FBVFlag;
static	DWORD			pb_GPUFrameBuffersFormat;//encoded format for GPU
static	DWORD			pb_EXAddr[8];		//extra buffers addresses
static	DWORD			pb_ExtraBuffersCount=0;

static	DWORD			pb_DepthStencilAddr;
static	DWORD			pb_DepthStencilPitch;
static int			pb_DepthStencilLast;
static	DWORD			pb_DSAddr;		//depth stencil address
static	DWORD			pb_DSSize;		//size of depth stencil buffer
static	DWORD			pb_GPUDepthStencilFormat;//encoded format for GPU

static	int			pb_front_index;
static	int			pb_back_index;

static	DWORD			pb_Viewport_x;
static	DWORD			pb_Viewport_y;
static	DWORD			pb_Viewport_width;
static	DWORD			pb_Viewport_height;
static	DWORD			pb_Viewport_zmin;
static	DWORD			pb_Viewport_zmax;

static	float			pb_XScale;
static	float			pb_YScale;
static	float			pb_ZScale;
static	float			pb_GlobalScale;
static	float			pb_Bias;

static	int			pb_debug_screen_active;

static	DWORD			pb_DmaChID9Inst;
static	DWORD			pb_DmaChID10Inst;
static	DWORD			pb_DmaChID11Inst;

static	DWORD			*pb_DmaUserAddr;

static	DWORD			pb_PushIndex;
static	DWORD			*pb_PushStart;
static	DWORD			*pb_PushNext;

static int 			pb_BeginEndPair=0;

static float			pb_FixedPipelineConstants[12]={
					0.0f,	0.5f,	1.0f,	2.0f,
					-1.0f,	0.0f,	1.0f,	2.0f,
					0.0f,	0.0f,	-1.0f,	0.0f	};

static	float			pb_IdentityMatrix[16]={
					1.0f,	0.0f,	0.0f,	0.0f,
					0.0f,	1.0f,	0.0f,	0.0f,
					0.0f,	0.0f,	1.0f,	0.0f,
					0.0f,	0.0f,	0.0f,	1.0f	};

static	DWORD			pb_TilePitches[16]={
					0x0200,0x0400,0x0600,0x0800,
					0x0A00,0x0C00,0x0E00,0x1000,
					0x1400,0x1800,0x1C00,0x2800,
					0x3000,0x3800,0x5000,0x7000	};

static	float			pb_BiasTable[7]={
					0.0f,
					0.585f,
					1.0f,
					1.322f,
					1.585f,
					1.907f,
					2.0f	};

				//temporary storage for pb_pcode2mcode()
static	DWORD			pb_gpu_programnc[136*5+192*7+8];//vertex shader micro-code setup (max:136 instructions + 192 constants)
static	DWORD			pb_gpu_registers[6*8+7];//pixel shader registers values
static int			pb_tmp_registers[16];//some vertex shader macros need to find free temp registers
static int			pb_exp_constflag;
static int			pb_log_constflag;

//forward references
static void pb_load_gr_ctx(int ctx_id);

//private pb_text_screen functions

#define ROWS	16
#define COLS	60

static	char		pb_text_screen[ROWS][COLS];

static int 		pb_next_row=0;
static int		pb_next_col=0;

static unsigned char systemFont[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,56,56,56,56,56,0,56,56,
	108,108,0,0,0,0,0,0,0,108,254,254,108,254,254,108,
	48,126,224,124,14,254,252,48,98,230,204,24,48,102,206,140,
	120,220,252,120,250,222,252,118,28,28,56,0,0,0,0,0,
	14,28,28,28,28,28,28,14,112,56,56,56,56,56,56,112,
	0,0,0,230,124,56,124,206,0,0,28,28,127,127,28,28,
	0,0,0,0,0,28,28,56,0,0,0,0,124,124,0,0,
	0,0,0,0,0,0,56,56,28,28,56,56,112,112,224,224,
	124,254,238,238,238,254,254,124,56,120,248,56,56,254,254,254,
	252,254,14,60,112,254,254,254,252,254,14,60,14,254,254,252,
	238,238,238,254,254,14,14,14,254,254,224,252,14,254,254,252,
	124,252,224,252,238,254,254,124,252,254,14,14,28,28,56,56,
	124,254,238,124,238,254,254,124,124,254,238,126,14,254,254,252,
	0,0,28,28,0,28,28,28,0,0,28,28,0,28,28,56,
	6,14,28,56,56,28,14,6,0,0,124,124,0,124,124,124,
	112,56,28,14,14,28,56,112,124,254,206,28,56,0,56,56,
	124,198,190,182,190,182,200,126,124,254,238,254,238,238,238,238,
	252,254,206,252,206,254,254,252,124,254,238,224,238,254,254,124,
	252,254,238,238,238,254,254,252,254,254,224,248,224,254,254,254,
	126,254,224,248,224,224,224,224,126,254,224,238,238,254,254,124,
	238,238,238,254,238,238,238,238,254,254,56,56,56,254,254,254,
	254,254,14,14,238,254,254,124,238,238,252,248,252,238,238,238,
	224,224,224,224,224,254,254,126,130,198,238,254,254,238,238,238,
	206,238,254,254,254,254,238,230,124,254,238,238,238,254,254,124,
	252,254,238,238,252,224,224,224,124,254,238,238,254,254,252,118,
	252,254,238,238,252,238,238,238,126,254,224,124,14,254,254,252,
	254,254,56,56,56,56,56,56,238,238,238,238,238,254,254,124,
	238,238,238,238,238,238,124,56,238,238,238,254,254,238,198,130,
	238,238,124,56,124,238,238,238,238,238,124,124,56,56,112,112,
	254,254,28,56,112,254,254,254,124,124,112,112,112,124,124,124,
	112,112,56,56,28,28,14,14,124,124,28,28,28,124,124,124,
	56,124,238,198,0,0,0,0,0,0,0,0,0,254,254,254,
	56,56,28,0,0,0,0,0,0,124,254,238,254,238,238,238,
	0,252,254,206,252,206,254,252,0,124,254,238,224,238,254,124,
	0,252,254,238,238,238,254,252,0,254,254,224,248,224,254,254,
	0,126,254,224,248,224,224,224,0,126,254,224,238,238,254,124,
	0,238,238,238,254,238,238,238,0,254,254,56,56,56,254,254,
	0,254,254,14,14,238,254,124,0,238,238,252,248,252,238,238,
	0,224,224,224,224,224,254,126,0,130,198,238,254,254,238,238,
	0,206,238,254,254,254,238,230,0,124,254,238,238,238,254,124,
	0,252,254,238,238,252,224,224,0,124,254,238,238,254,252,118,
	0,252,254,238,238,252,238,238,0,126,254,224,124,14,254,252,
	0,254,254,56,56,56,56,56,0,238,238,238,238,238,254,124,
	0,238,238,238,238,238,124,56,0,238,238,238,254,238,198,130,
	0,238,238,124,56,124,238,238,0,238,238,124,124,56,56,112,
	0,254,254,28,56,112,254,254,60,124,112,112,112,124,124,60,
	56,56,56,0,56,56,56,56,120,124,28,28,28,124,124,120,
	236,254,118,0,0,0,0,0,0,16,56,124,254,254,254,254,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

static void pb_scrollup(void)
{
	int i;
	for(i=0;i<ROWS-1;i++)
	memcpy(&pb_text_screen[i][0],&pb_text_screen[i+1][0],COLS);
	memset(&pb_text_screen[ROWS-1][0],0,COLS);
}

static void pb_print_char(char c)
{
	if (c=='\n')
	{
		pb_next_row++;
		if (pb_next_row>=ROWS) { pb_next_row=ROWS-1; pb_scrollup(); }
		pb_next_col=0;
	}
	else
	if (c=='\r')
	{
		pb_next_col=0;
	}
	else
	if (c==8)
	{
		pb_next_col--;
		if (pb_next_col<0) pb_next_col=0;
	}
	else
	if (c>=32)
	{
		pb_text_screen[pb_next_row][pb_next_col]=c;
		pb_next_col++;
		if (pb_next_col>=COLS)
		{
			pb_next_row++;
			if (pb_next_row>=ROWS) { pb_next_row=ROWS-1; pb_scrollup(); }
			pb_next_col=0;
		}		
	}
}

//private functions

static void pb_set_gamma_ramp(BYTE *pGammaRamp)
{
	int			i;

	VIDEOREG8(NV_USER_DAC_WRITE_MODE_ADDRESS)=0;	//&NV_USER_DAC_WRITE_MODE_ADDRESS_VALUE

	for(i=0;i<256;i++)
	{
		VIDEOREG8(NV_USER_DAC_PALETTE_DATA)=pGammaRamp[i];	//&NV_USER_DAC_PALETTE_DATA_VALUE
		VIDEOREG8(NV_USER_DAC_PALETTE_DATA)=pGammaRamp[i+256];	//&NV_USER_DAC_PALETTE_DATA_VALUE
		VIDEOREG8(NV_USER_DAC_PALETTE_DATA)=pGammaRamp[i+512];	//&NV_USER_DAC_PALETTE_DATA_VALUE
	}
}

static void pb_vbl_handler(void)
{
	BYTE		old_color_addr; //important index to preserve if we are called from Dpc or Isr

	int		flag;
	int		next;
	int		index;

	old_color_addr=VIDEOREG8(NV_PRMCIO_CRX__COLOR);

	pb_vbl_counter++;

	//Index of next back buffer to show up (0-4)
	next=pb_BackBufferNxtVBL;

	//Is the next back buffer to show up is ready?
	if (pb_BackBufferbReady[next]==1)
	{
		//screen swapping has been done already, theoretically, in ISR
		pb_BackBufferbReady[next]=0;

		index=pb_GammaRampIdx;
		if (pb_GammaRampbReady[index])
		{
			pb_set_gamma_ramp(&pb_GammaRamp[index][0][0]);
			pb_GammaRampbReady[index]=0;
			index=(index+1)%3;
			pb_GammaRampIdx=index;
		}

		VIDEOREG(NV_PGRAPH_INCREMENT)|=NV_PGRAPH_INCREMENT_READ_3D_TRIGGER;

		//rotate next back buffer & gamma ramp index
		next=(next+1)%3;
		pb_BackBufferNxtVBL=next;
	}

	do
	{
		VIDEOREG(PCRTC_INTR)=PCRTC_INTR_VBLANK_RESET;
	}while(VIDEOREG(NV_PMC_INTR_0)&NV_PMC_INTR_0_PCRTC_PENDING);

	NtPulseEvent(pb_VBlankEvent, NULL);

//	if (UserCallback) UserCallback(); //user callback must be brief and preserve fpu state

	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=old_color_addr; //restore color index
}

static void pb_cache_flush(void)
{
	__asm__ __volatile__ ("sfence");
	//assembler instruction "sfence" : waits end of previous instructions

	VIDEOREG(NV_PFB_WC_CACHE)|=NV_PFB_WC_CACHE_FLUSH_TRIGGER;
	while(VIDEOREG(NV_PFB_WC_CACHE)&NV_PFB_WC_CACHE_FLUSH_IN_PROGRESS) {};
}

static void pb_subprog(DWORD subprogID, DWORD paramA, DWORD paramB)
{
	//inner registers 0x1D8C & 0x1D90 match 2 outer registers :
	//[0x1D8C]=[NV20_TCL_PRIMITIVE_3D_PARAMETER_A]=VIDEOREG(NV_PGRAPH_PARAMETER_A)=[0xFD401A88]
	//[0x1D90]=[NV20_TCL_PRIMITIVE_3D_PARAMETER_B]=VIDEOREG(NV_PGRAPH_PARAMETER_B)=[0xFD40186C]
	//so they can be used by a push buffer sequence to set parameters
	//before triggering a subprogram by the command 0x0100 which will
	//throw an interrupt and have CPU execute its code right here.
	
	//Here just test the subprogID value and execute your own subprogram
	//associated code (avoid using subprogID=0, it seems to be reserved)

	int			next;

	switch(subprogID)
	{
		case PB_SETOUTER: //sets an outer register
			VIDEOREG(paramA)=paramB;
			break;

		case PB_SETNOISE: //Dxt1NoiseEnable: copy paramA in NV_PGRAPH_RDI(sel 0xE0 adr 0x50 & sel 0xDF adr 0x08)
			VIDEOREG(NV_PGRAPH_RDI_INDEX)=((0xE0<<16)&NV_PGRAPH_RDI_INDEX_SELECT)|((0x50)&NV_PGRAPH_RDI_INDEX_ADDRESS);
			VIDEOREG(NV_PGRAPH_RDI_DATA)=paramA;
			VIDEOREG(NV_PGRAPH_RDI_INDEX)=((0xDF<<16)&NV_PGRAPH_RDI_INDEX_SELECT)|((0x08)&NV_PGRAPH_RDI_INDEX_ADDRESS);
			VIDEOREG(NV_PGRAPH_RDI_DATA)=paramA;
			break;

		case PB_FINISHED: //warns that all drawing has been finished for the frame
			next=pb_BackBufferNxt;
			pb_BackBufferIndex[next]=paramA;
			pb_BackBufferbReady[next]=1;
			next=(next+1)%3;
			pb_BackBufferNxt=next;
			break;

		default:
			debugPrint(	"Unknown subProgID %d has been detected by DPC (A=%x B=%x).\n",
					subprogID,
					paramA,
					paramB	);
			break;
	}
}

static DWORD pb_gr_handler(void)
{
	DWORD			status;
	DWORD			trapped_address;
	int				trapped_ctx_id;
	DWORD			nsource;
	DWORD			GrClass;
	DWORD			DataLow;
	int				i;
	DWORD			*p;

	VIDEOREG(NV_PGRAPH_FIFO)=NV_PGRAPH_FIFO_ACCESS_DISABLE;

	status=VIDEOREG(NV_PGRAPH_INTR);
	trapped_address=VIDEOREG(NV_PGRAPH_TRAPPED_ADDR);
	nsource=VIDEOREG(NV_PGRAPH_NSOURCE);

	trapped_ctx_id=(trapped_address&NV_PGRAPH_TRAPPED_ADDR_CHID)>>20;
	trapped_address&=NV_PGRAPH_TRAPPED_ADDR_MTHD;

	if (status&NV_PGRAPH_INTR_CONTEXT_SWITCH_PENDING)
	{
		VIDEOREG(NV_PGRAPH_INTR)=NV_PGRAPH_INTR_CONTEXT_SWITCH_RESET;

		while(VIDEOREG(NV_PGRAPH_STATUS));

		pb_load_gr_ctx(trapped_ctx_id);
	}

	if (status&NV_PGRAPH_INTR_MISSING_HW_PENDING)
	{
		VIDEOREG(NV_PGRAPH_INTR)=NV_PGRAPH_INTR_MISSING_HW_RESET;
	}

	if (	(status&NV_PGRAPH_INTR_NOTIFY_PENDING)||
		(status&NV_PGRAPH_INTR_ERROR_PENDING)	)
	{
		if (nsource&NV_PGRAPH_NSOURCE_ILLEGAL_MTHD_PENDING)
		{
			if (status&NV_PGRAPH_INTR_NOTIFY_PENDING)
				VIDEOREG(NV_PGRAPH_INTR)=	NV_PGRAPH_INTR_NOTIFY_RESET|
								NV_PGRAPH_INTR_ERROR_RESET|
								NV_PGRAPH_INTR_SINGLE_STEP_RESET|
								NV_PGRAPH_INTR_MORE_RESET;
			else
				VIDEOREG(NV_PGRAPH_INTR)=NV_PGRAPH_INTR_ERROR_RESET;
		}
	}

	status=VIDEOREG(NV_PGRAPH_INTR);

	if (status)
	{
		VIDEOREG(NV_PGRAPH_INTR)=NV_PGRAPH_INTR_CONTEXT_SWITCH_RESET;

		if (	(status!=NV_PGRAPH_INTR_CONTEXT_SWITCH_PENDING)&&
			(status!=NV_PGRAPH_INTR_SINGLE_STEP_PENDING)	)
		{
			if (status&NV_PGRAPH_INTR_MISSING_HW_PENDING)
			{
				while(VIDEOREG(NV_PGRAPH_STATUS)) {};
			}

			if (nsource)
			{
				if (	(status&NV_PGRAPH_INTR_NOTIFY_PENDING)||
					(status&NV_PGRAPH_INTR_ERROR_PENDING)	)
				{
					GrClass=VIDEOREG(NV_PGRAPH_CTX_SWITCH1)&NV_PGRAPH_CTX_SWITCH1_GRCLASS;
					DataLow=VIDEOREG(NV_PGRAPH_TRAPPED_DATA_LOW);	//&NV_PGRAPH_TRAPPED_DATA_LOW_VALUE

					if ((nsource&NV_PGRAPH_NSOURCE_ILLEGAL_MTHD_PENDING)==0)
					{
						if (trapped_address==0x0100)
						{
							//The following line may be a bad idea. But without it, interrupt fires permanently...
							VIDEOREG(NV_PGRAPH_INTR)=NV_PGRAPH_INTR_ERROR_RESET;
							//calls subprogram
							pb_subprog(DataLow,VIDEOREG(NV_PGRAPH_PARAMETER_A),VIDEOREG(NV_PGRAPH_PARAMETER_B));
						}
						else
						{
							pb_show_debug_screen();

							debugPrint("\n");
							if (nsource&NV_PGRAPH_NSOURCE_DATA_ERROR_PENDING) debugPrint("GPU Error : invalid data error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_PROTECTION_ERROR_PENDING) debugPrint("GPU Error : protection error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_RANGE_EXCEPTION_PENDING) debugPrint("GPU Error : range exception error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_LIMIT_COLOR_PENDING) debugPrint("GPU Error : color buffer limit error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_LIMIT_ZETA_PENDING) debugPrint("GPU Error : zeta buffer limit error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_DMA_R_PROTECTION_PENDING) debugPrint("GPU Error : dma read protection error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_DMA_W_PROTECTION_PENDING) debugPrint("GPU Error : dma write protection error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_FORMAT_EXCEPTION_PENDING)	debugPrint("GPU Error : format exception error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_PATCH_EXCEPTION_PENDING) debugPrint("GPU Error : patch exception error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_STATE_INVALID_PENDING) debugPrint("GPU Error : object state invalid error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_DOUBLE_NOTIFY_PENDING) debugPrint("GPU Error : double notify error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_NOTIFY_IN_USE_PENDING) debugPrint("GPU Error : notify in use error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_METHOD_CNT_PENDING) debugPrint("GPU Error : method count error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_BFR_NOTIFICATION_PENDING) debugPrint("GPU Error : buffer notification error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_DMA_VTX_PROTECTION_PENDING) debugPrint("GPU Error : DMA vertex protection error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_IDX_INLINE_REUSE_PENDING) debugPrint("Graphics index inline reuse error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_INVALID_OPERATION_PENDING) debugPrint("GPU Error : invalid operation error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_FD_INVALID_OPERATION_PENDING) debugPrint("GPU Error : FD invalid operation error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_TEX_A_PROTECTION_PENDING) debugPrint("GPU Error : texture A protection error!\n");
							if (nsource&NV_PGRAPH_NSOURCE_TEX_B_PROTECTION_PENDING) debugPrint("GPU Error : texture B protection error!\n");

							debugPrint(	"Error binary flags : %08x\n"
									"Channel ID : %d (0=3D)\n"
									"Channel class : %x\n"
									"Push buffer inner register target : %04x\n"
									"Push buffer data (lo) or instance : %08x\n"
									"Push buffer data (hi) or instance : %08x\n"
									"Multi-purpose register A [0x1D8C] : %08x\n"
									"Multi-purpose register B [0x1D90] : %08x\n\n",
									nsource,
									trapped_ctx_id,
									GrClass,
									trapped_address,
									DataLow,
									VIDEOREG(NV_PGRAPH_TRAPPED_DATA_HIGH),
									VIDEOREG(NV_PGRAPH_PARAMETER_A),
									VIDEOREG(NV_PGRAPH_PARAMETER_B)		);

							if (pb_trace_mode==0) debugPrint("Report is accurate only if pb_trace_mode=1 (slower)\n");
							
							debugPrint("System halted\n");

							//calling XReboot() from here doesn't work well.

							// Halt the system with these instructions, so the CPU can idle.
							__asm__ (
								"cli\n"
								"hlt");
						}
					}
				}
			}

			if (status&NV_PGRAPH_INTR_BUFFER_NOTIFY_PENDING)
			{
				while (VIDEOREG(NV_PGRAPH_STATUS)) {};
			}
		}
	}

	VIDEOREG(NV_PGRAPH_FIFO)=NV_PGRAPH_FIFO_ACCESS_ENABLE;

	return VIDEOREG(NV_PGRAPH_INTR);
}

static void pb_wait_until_gr_not_busy(void)
{
	DWORD		status;

	while(VIDEOREG(NV_PGRAPH_STATUS)!=NV_PGRAPH_STATUS_NOT_BUSY)
	{
		status=VIDEOREG(NV_PMC_INTR_0);
		if (status&NV_PMC_INTR_0_PGRAPH_PENDING) pb_gr_handler();
		if (status&NV_PMC_INTR_0_PCRTC_PENDING) pb_vbl_handler();
	}
}

static void pb_load_gr_ctx(int ctx_id)
{
	DWORD			old_fifo_access;
	DWORD			dummy;
	int			i;

	if (VIDEOREG(NV_PGRAPH_INTR)!=NV_PGRAPH_INTR_NOT_PENDING) pb_gr_handler();

	old_fifo_access=VIDEOREG(NV_PGRAPH_FIFO);
	VIDEOREG(NV_PGRAPH_FIFO)=NV_PGRAPH_FIFO_ACCESS_DISABLE;

	pb_wait_until_gr_not_busy();

	if ((ctx_id!=pb_GrCtxID)&&(ctx_id!=NONE))
	{
		VIDEOREG(NV_PGRAPH_CHANNEL_CTX_POINTER)=pb_GrCtxInst[ctx_id]&NV_PGRAPH_CHANNEL_CTX_POINTER_INST;
		VIDEOREG(NV_PGRAPH_CHANNEL_CTX_STATUS)=NV_PGRAPH_CHANNEL_CTX_STATUS_UNLOADED;

		pb_wait_until_gr_not_busy();

		VIDEOREG(NV_PGRAPH_CTX_CONTROL)=NV_PGRAPH_CTX_CONTROL_DEVICE_ENABLED;
	}

	pb_GrCtxID=ctx_id;

	if (ctx_id==NONE)
	{
		VIDEOREG(NV_PGRAPH_CTX_CONTROL)=NV_PGRAPH_CTX_CONTROL_DEVICE_ENABLED|NV_PGRAPH_CTX_CONTROL_TIME_NOT_EXPIRED;
		VIDEOREG(NV_PGRAPH_FFINTFC_ST2)=NV_PGRAPH_FFINTFC_ST2_CHID_STATUS_VALID;

		VIDEOREG(NV_PGRAPH_FIFO)=old_fifo_access|NV_PGRAPH_FIFO_ACCESS_ENABLE;
	}
	else
	{
		if (pb_3DGrCtxInst[ctx_id])
		{
			VIDEOREG(NV_PGRAPH_DEBUG_0) =	NV_PGRAPH_DEBUG_0_IDX_STATE_RESET|
							NV_PGRAPH_DEBUG_0_VTX_STATE_RESET|
							NV_PGRAPH_DEBUG_0_CAS_STATE_RESET;
			dummy=VIDEOREG(NV_PGRAPH_DEBUG_0);
			VIDEOREG(NV_PGRAPH_DEBUG_0)=NV_PGRAPH_DEBUG_0_NO_RESET;
			dummy=VIDEOREG(NV_PGRAPH_DEBUG_0);

			VIDEOREG(NV_PGRAPH_RDI_INDEX)=((0x00)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0x3D<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
			for(i=0;i<15;i++) VIDEOREG(NV_PGRAPH_RDI_DATA)=0;
		}

		VIDEOREG(NV_PGRAPH_DEBUG_1)|=NV_PGRAPH_DEBUG_1_CACHE_INVALIDATE;

		VIDEOREG(NV_PGRAPH_CTX_USER)=(ctx_id<<24)&NV_PGRAPH_CTX_USER_CHID;
		VIDEOREG(NV_PGRAPH_CHANNEL_CTX_POINTER)=pb_GrCtxInst[ctx_id]&NV_PGRAPH_CHANNEL_CTX_POINTER_INST;
		VIDEOREG(NV_PGRAPH_CHANNEL_CTX_STATUS)=NV_PGRAPH_CHANNEL_CTX_STATUS_LOADED;

		pb_wait_until_gr_not_busy();

		VIDEOREG(NV_PGRAPH_CTX_USER)=(VIDEOREG(NV_PGRAPH_CTX_USER)&~NV_PGRAPH_CTX_USER_CHID)|((ctx_id<<24)&NV_PGRAPH_CTX_USER_CHID);

		VIDEOREG(NV_PGRAPH_CTX_CONTROL) =	NV_PGRAPH_CTX_CONTROL_TIME_NOT_EXPIRED|
							NV_PGRAPH_CTX_CONTROL_CHID_VALID|
							NV_PGRAPH_CTX_CONTROL_DEVICE_ENABLED;

		VIDEOREG(NV_PGRAPH_FFINTFC_ST2)&=(NV_PGRAPH_FFINTFC_ST2_CHSWITCH_CLEAR&NV_PGRAPH_FFINTFC_ST2_FIFOHOLD_CLEAR);
	}
}

static DWORD pb_fifo_handler(void)
{
	DWORD		i;
	DWORD		status;
	DWORD		pull;
	DWORD		get_address;
	int		skip_waiting;

	skip_waiting=0;

	status=VIDEOREG(NV_PFIFO_INTR_0);

	if (status&NV_PFIFO_INTR_0_SEMAPHORE_PENDING)
	{
		VIDEOREG(NV_PFIFO_INTR_0)=NV_PFIFO_INTR_0_SEMAPHORE_RESET;
	}

	if (status&NV_PFIFO_INTR_0_ACQUIRE_TIMEOUT_PENDING)
	{
		VIDEOREG(NV_PFIFO_INTR_0)=NV_PFIFO_INTR_0_ACQUIRE_TIMEOUT_RESET;
	}

	status=VIDEOREG(NV_PFIFO_INTR_0);

	if (status&NV_PFIFO_INTR_0_CACHE_ERROR_PENDING)
	{
		pull=VIDEOREG(NV_PFIFO_CACHE1_PULL0);
		get_address=VIDEOREG(NV_PFIFO_CACHE1_GET);	//&NV_PFIFO_CACHE1_GET_ADDRESS (0x3FC)
		get_address>>=2;
		VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;
		VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_DISABLE;
		VIDEOREG(NV_PFIFO_INTR_0)=NV_PFIFO_INTR_0_CACHE_ERROR_RESET;

		for(i=0;i<65535;i++)
		{
			if ((pull&NV_PFIFO_CACHE1_PULL0_HASH_STATE_BUSY)==0) break;
			pull=VIDEOREG(NV_PFIFO_CACHE1_PULL0);
		}		

		if (	(pull&NV_PFIFO_CACHE1_PULL0_DEVICE_SOFTWARE)||
			(pull&NV_PFIFO_CACHE1_PULL0_HASH_FAILED)	)
		{
			VIDEOREG(NV_PFIFO_CACHE1_GET)=((get_address+1)<<2)&NV_PFIFO_CACHE1_GET_ADDRESS;
		}

		VIDEOREG(NV_PFIFO_CACHE1_HASH)=0;	//&NV_PFIFO_CACHE1_HASH_INSTANCE
		VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_ENABLE;
		VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_REASSIGN_ENABLED;
	}

	if (status&NV_PFIFO_INTR_0_DMA_PUSHER_PENDING)
	{
		pb_show_debug_screen();
		debugPrint("Software Put=%08x\n",pb_Put);
		debugPrint("Hardware Put=%08x\n",VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT));
		debugPrint("Hardware Get=%08x\n",VIDEOREG(NV_PFIFO_CACHE1_DMA_GET));
		debugPrint("Dma push buffer engine encountered invalid data at these addresses.\n");

		VIDEOREG(NV_PFIFO_INTR_0)=NV_PFIFO_INTR_0_DMA_PUSHER_RESET;
		VIDEOREG(NV_PFIFO_CACHE1_DMA_STATE)=NV_PFIFO_CACHE1_DMA_STATE_METHOD_COUNT_0;
		
		if (VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT)!=VIDEOREG(NV_PFIFO_CACHE1_DMA_GET))
			VIDEOREG(NV_PFIFO_CACHE1_DMA_GET)+=(1<<2);
	}

	if (status&NV_PFIFO_INTR_0_DMA_PT_PENDING)
	{
		VIDEOREG(NV_PFIFO_INTR_0)=NV_PFIFO_INTR_0_DMA_PT_RESET;
	}

	if (VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)&NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)
	{
		if ((VIDEOREG8(NV_PFIFO_CACHE1_STATUS)&NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY)==0)
		do
		{
			if (VIDEOREG(NV_PFIFO_INTR_0)==NV_PFIFO_INTR_0_NOT_PENDING)
			{
				if (VIDEOREG(NV_PGRAPH_INTR)) pb_fifo_handler();

				if (VIDEOREG(NV_PMC_INTR_0)&NV_PMC_INTR_0_PCRTC_PENDING) pb_vbl_handler();

				if ((VIDEOREG8(NV_PFIFO_CACHE1_STATUS)&NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY)==0)
					continue; //jump to loop start
			}

			if ((VIDEOREG8(NV_PFIFO_CACHE1_STATUS)&NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY)==0)
			{
				skip_waiting=1;
				break;
			}
			
		}while(VIDEOREG8(NV_PFIFO_CACHE1_STATUS)&NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY);

		if (skip_waiting==0)
		{
			//wait
			while(VIDEOREG8(NV_PFIFO_CACHES)&NV_PFIFO_CACHES_DMA_SUSPEND_BUSY);
			VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)&=NV_PFIFO_CACHE1_DMA_PUSH_STATUS_RUNNING;
		}
	}

	if (VIDEOREG(NV_PFIFO_INTR_0)==NV_PFIFO_INTR_0_NOT_PENDING)
	{
		VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_ENABLE;
		VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_REASSIGN_ENABLED;
	}

	return VIDEOREG(NV_PFIFO_INTR_0)|(VIDEOREG(NV_PFIFO_DEBUG_0)&NV_PFIFO_DEBUG_0_CACHE_ERROR0_PENDING);
}

static void pb_set_fifo_channel(int channel)
{
	DWORD		old_caches,old_push,old_pull,old_channel;

	DWORD		*p;

	DWORD 		pending_flags;

	old_caches=VIDEOREG(NV_PFIFO_CACHES);
	old_push=VIDEOREG(NV_PFIFO_CACHE1_PUSH0);
	old_pull=VIDEOREG(NV_PFIFO_CACHE1_PULL0);
	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_DISABLE;

	old_channel=VIDEOREG(NV_PFIFO_CACHE1_PUSH1)&NV_PFIFO_CACHE1_PUSH1_CHID;

	//backup old channel details into PRAMIN area
	p=(DWORD *)(VIDEO_BASE+pb_FifoFCAddr+old_channel*64);
	*(p+0)=VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT);	//&NV_PFIFO_CACHE1_DMA_PUT_OFFSET
	*(p+1)=VIDEOREG(NV_PFIFO_CACHE1_DMA_GET);	//&NV_PFIFO_CACHE1_DMA_GET_OFFSET
	*(p+2)=VIDEOREG(NV_PFIFO_CACHE1_REF);		//&NV_PFIFO_CACHE1_REF_CNT
	*(p+3)=VIDEOREG(NV_PFIFO_CACHE1_DMA_INSTANCE);	//&NV_PFIFO_CACHE1_DMA_INSTANCE_ADDRESS
	*(p+4)=VIDEOREG(NV_PFIFO_CACHE1_DMA_STATE);
	*(p+5)=VIDEOREG(NV_PFIFO_CACHE1_DMA_FETCH);
	*(p+6)=VIDEOREG(NV_PFIFO_CACHE1_ENGINE);
	*(p+7)=VIDEOREG(NV_PFIFO_CACHE1_PULL1);
	*(p+8)=VIDEOREG(NV_PFIFO_CACHE1_ACQUIRE_2);	//&NV_PFIFO_CACHE1_ACQUIRE_2_VALUE
	*(p+9)=VIDEOREG(NV_PFIFO_CACHE1_ACQUIRE_1);	//&NV_PFIFO_CACHE1_ACQUIRE_1_TIMESTAMP
	*(p+10)=VIDEOREG(NV_PFIFO_CACHE1_ACQUIRE_0);	//&NV_PFIFO_CACHE1_ACQUIRE_0_TIMEOUT
	*(p+11)=VIDEOREG(NV_PFIFO_CACHE1_SEMAPHORE);
	*(p+12)=VIDEOREG(NV_PFIFO_CACHE1_DMA_SUBROUTINE);

	if (VIDEOREG(NV_PFIFO_CACHE1_PUSH1)&NV_PFIFO_CACHE1_PUSH1_MODE_DMA)
	{
		pending_flags=VIDEOREG(NV_PFIFO_DMA);
		pending_flags&=~(1<<old_channel);
		if (VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT)!=VIDEOREG(NV_PFIFO_CACHE1_DMA_GET))
			pending_flags|=(1<<old_channel);
		VIDEOREG(NV_PFIFO_DMA)=pending_flags;			
	}

	//let's switch from old_channel to channel

	VIDEOREG(NV_PFIFO_CACHE1_PUSH1)=channel&NV_PFIFO_CACHE1_PUSH1_CHID;

	if (channel!=1)
	if (pb_FifoChannelsMode&(1<<channel)) //Channel mode was DMA?
		VIDEOREG(NV_PFIFO_CACHE1_PUSH1)|=NV_PFIFO_CACHE1_PUSH1_MODE_DMA;

	//restore channel details from VRAM
	p=(DWORD *)(VIDEO_BASE+pb_FifoFCAddr+channel*64);
	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT)=*(p+0);	//&NV_PFIFO_CACHE1_DMA_PUT_OFFSET
	VIDEOREG(NV_PFIFO_CACHE1_DMA_GET)=*(p+1);	//&NV_PFIFO_CACHE1_DMA_GET_OFFSET
	VIDEOREG(NV_PFIFO_CACHE1_REF)=*(p+2);		//&NV_PFIFO_CACHE1_REF_CNT
	VIDEOREG(NV_PFIFO_CACHE1_DMA_INSTANCE)=*(p+3);	//&NV_PFIFO_CACHE1_DMA_INSTANCE_ADDRESS
	VIDEOREG(NV_PFIFO_CACHE1_DMA_STATE)=*(p+4);
	VIDEOREG(NV_PFIFO_CACHE1_DMA_FETCH)=*(p+5);
	VIDEOREG(NV_PFIFO_CACHE1_ENGINE)=*(p+6);
	VIDEOREG(NV_PFIFO_CACHE1_PULL1)=*(p+7);
	VIDEOREG(NV_PFIFO_CACHE1_ACQUIRE_2)=*(p+8);	//&NV_PFIFO_CACHE1_ACQUIRE_2_VALUE
	VIDEOREG(NV_PFIFO_CACHE1_ACQUIRE_1)=*(p+9);	//&NV_PFIFO_CACHE1_ACQUIRE_1_TIMESTAMP
	VIDEOREG(NV_PFIFO_CACHE1_ACQUIRE_0)=*(p+10);	//&NV_PFIFO_CACHE1_ACQUIRE_0_TIMEOUT
	VIDEOREG(NV_PFIFO_CACHE1_SEMAPHORE)=*(p+11);
	VIDEOREG(NV_PFIFO_CACHE1_DMA_SUBROUTINE)=*(p+12);

	if (channel!=1)
	if (pb_FifoChannelsMode&(1<<channel)) //Channel mode was DMA?
		VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=NV_PFIFO_CACHE1_DMA_PUSH_ACCESS_ENABLE;

	VIDEOREG(NV_PFIFO_TIMESLICE)=NV_PFIFO_TIMESLICE_TIMER_EXPIRED;

	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=old_pull;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=old_push;
	VIDEOREG(NV_PFIFO_CACHES)=old_caches;
}

static void __stdcall DPC(PKDPC Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	//Deferred Procedure Call (delayed treatment, triggered by ISR)
	//DPCs avoid crashes inside non reentrant user callbacks called by nested ISRs.
	//CAUTION : if you use fpu in DPC you have to save & restore yourself fpu state!!!
	//(fpu=floating point unit, i.e the coprocessor executing floating point opcodes)

	DWORD			more;
	DWORD			status;

	do
	{
		more=0;
		status=VIDEOREG(NV_PMC_INTR_0);

		if (status&NV_PMC_INTR_0_PTIMER_PENDING)
		{
			VIDEOREG(NV_PTIMER_INTR_0)=NV_PTIMER_INTR_0_ALARM_RESET;
			more=VIDEOREG(NV_PTIMER_INTR_0);
		}

		if (status&NV_PMC_INTR_0_PCRTC_PENDING) pb_vbl_handler();

		if (status&NV_PMC_INTR_0_PGRAPH_PENDING) more|=pb_gr_handler();

		if (	(VIDEOREG8(NV_PFIFO_DEBUG_0)&NV_PFIFO_DEBUG_0_CACHE_ERROR0_PENDING)||	
			(status&NV_PMC_INTR_0_PFIFO_PENDING)	) more|=pb_fifo_handler();

		if (	(VIDEOREG8(NV_PVIDEO_INTR)&NV_PVIDEO_INTR_BUFFER_0_PENDING)||
			(status&NV_PMC_INTR_0_PVIDEO_PENDING)	) VIDEOREG(NV_PVIDEO_INTR)=NV_PVIDEO_INTR_BUFFER_0_RESET;
	}while(more);

	VIDEOREG(NV_PMC_INTR_EN_0)=NV_PMC_INTR_EN_0_INTA_HARDWARE;

	return;
}

static BOOLEAN __stdcall ISR(PKINTERRUPT Interrupt, PVOID ServiceContext)
{
	//Interruption Service Routine (triggered by interrupt signal IRQ3)
	int			next;

	if (pb_running==0) return FALSE;

	//really, not for us at all
	if (VIDEOREG(NV_PMC_INTR_0)==NV_PMC_INTR_0_NOT_PENDING) return FALSE;

	//is it the VBlank event? (if so, proceed screen swapping immediately & in DPC)
	if (VIDEOREG(NV_PMC_INTR_0)&NV_PMC_INTR_0_PCRTC_PENDING)
	{
		//Need to show next back buffer to show up? (do it now, it's urgent)
		if (pb_debug_screen_active==0)
		if (pb_BackBufferbReady[pb_BackBufferNxtVBL]==1) VIDEOREG(PCRTC_START)=pb_FBAddr[pb_BackBufferIndex[pb_BackBufferNxtVBL]]&0x03FFFFFF;
	}

	VIDEOREG(NV_PMC_INTR_EN_0)=NV_PMC_INTR_EN_0_INTA_DISABLED;

	//handle longer & non urgent stuff later with the Dpc
	KeInsertQueueDpc(&pb_DPCObject,NULL,NULL);

	return TRUE;
}

static int pb_install_gpu_interrupt(void)
{
	int r;
	KIRQL irql;
	ULONG vector;	

	vector = HalGetInterruptVector(GPU_IRQ, &irql);

	KeInitializeDpc(&pb_DPCObject,&DPC,NULL);

	KeInitializeInterrupt(&pb_InterruptObject,
				&ISR,
				NULL,
				vector,
				irql,
				LevelSensitive,
				TRUE);
	
	r=KeConnectInterrupt(&pb_InterruptObject);

	return r;
}

static void pb_uninstall_gpu_interrupt(void)
{
	KeDisconnectInterrupt(&pb_InterruptObject);
}



static DWORD pb_wait_until_tiles_not_busy(void)
{
	DWORD old_dma_push;

	while (((VIDEOREG8(NV_PFIFO_CACHE1_STATUS)&NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY)==0)||
		((VIDEOREG8(NV_PFIFO_RUNOUT_STATUS)&NV_PFIFO_RUNOUT_STATUS_LOW_MARK_EMPTY)==0)||
		((VIDEOREG8(NV_PFIFO_CACHE1_DMA_PUSH)&NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)!=0)	)
	{
		pb_fifo_handler();
		if (VIDEOREG(NV_PGRAPH_INTR)!=NV_PGRAPH_INTR_NOT_PENDING) pb_gr_handler();
		if (VIDEOREG(NV_PMC_INTR_0)&NV_PMC_INTR_0_PCRTC_PENDING) pb_vbl_handler();
	}

	old_dma_push=VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH);
	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=NV_PFIFO_CACHE1_DMA_PUSH_ACCESS_DISABLE;
	while((VIDEOREG8(NV_PFIFO_CACHE1_DMA_PUSH)&NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)!=0);

	return old_dma_push;
}


static void pb_release_tile(int index,int clear_offset)
{
	DWORD		*pTile;
	DWORD		*pZcomp;
	DWORD		*p;

	DWORD		addr;
	DWORD		data;

	DWORD		old_dma_push;

	old_dma_push=pb_wait_until_tiles_not_busy();

	//points tile in NV_PFB
	pTile=(DWORD *)(VIDEO_BASE+NV_PFB_TILE+index*16);

	//points tile in NV_PGRAPH
	p=(DWORD *)(VIDEO_BASE+NV_PGRAPH_TILE_XBOX+index*16);

	//points tile in NV_PGRAPH_RDI(0x10)
	addr=((index*4+0x10)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	data=0;

	do
	{
		pb_wait_until_gr_not_busy();

		*(pTile+0)=0;
		*(p+0)=0;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=addr; VIDEOREG(NV_PGRAPH_RDI_DATA)=data;		
	}while(*(pTile+0)!=*(p+0));

	//points tile Zcomp in NV_PFB
	pZcomp=(DWORD *)(VIDEO_BASE+NV_PFB_ZCOMP+index*4);

	//points tile Zcomp in NV_PGRAPH
	p=(DWORD *)(VIDEO_BASE+NV_PGRAPH_ZCOMP_XBOX+index*4);

	//points tile Zcomp in NV_PGRAPH_RDI(0x90)
	addr=((index*4+0x90)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	data=0;

	*(pZcomp+0)=0;
	*(p+0)=0;
	VIDEOREG(NV_PGRAPH_RDI_INDEX)=addr; VIDEOREG(NV_PGRAPH_RDI_DATA)=data;		

	if (clear_offset)
	{
		VIDEOREG(NV_PFB_ZCOMP_OFFSET)=0;
		VIDEOREG(NV_PGRAPH_ZCOMP_OFFSET_XBOX)=0;
	}

	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=old_dma_push;
}



void pb_assign_tile(	int	tile_index,
				DWORD	tile_addr,
				DWORD	tile_size,
				DWORD	tile_pitch,
				DWORD	tile_z_start_tag,
				DWORD	tile_z_offset,
				DWORD	tile_flags	)
{
	DWORD				old_dma_push;

	DWORD				addr10;
	DWORD				addr30;
	DWORD				addr50;
	DWORD				addr90;

	DWORD				tile_tail;

	DWORD				*pTile;
	DWORD				*pZcomp;
	DWORD				*p;

	DWORD				EncodedZStartTag;
	DWORD				EncodedZOffset;
#ifdef DBG
	if ((tile_addr&0x3fff)||(tile_size&0x3fff)) debugPrint("pb_assign_tile: addr & size not well aligned\n");
#endif
	old_dma_push=pb_wait_until_tiles_not_busy();

	//points at tile in NV_PGRAPH_RDI(0x10(Addr),0x30(Tail) & 0x50(Pitch))
	addr10=((tile_index*4+0x10)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	addr30=((tile_index*4+0x30)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	addr50=((tile_index*4+0x50)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);

	tile_tail=tile_addr+tile_size-1;

	//points tile in NV_PFB
	pTile=(DWORD *)(VIDEO_BASE+NV_PFB_TILE+tile_index*16);

	//points tile in NV_PGRAPH
	p=(DWORD *)(VIDEO_BASE+NV_PGRAPH_TILE_XBOX+tile_index*16);


	do
	{
		pb_wait_until_gr_not_busy();

		*(pTile+0)=tile_addr|2|(tile_flags&1);
		*(p+0)=tile_addr|2|(tile_flags&1); 
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=addr10; VIDEOREG(NV_PGRAPH_RDI_DATA)=tile_addr|2|(tile_flags&1);

		*(pTile+1)=tile_tail;
		*(p+1)=tile_tail;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=addr30; VIDEOREG(NV_PGRAPH_RDI_DATA)=tile_tail;

		*(pTile+2)=tile_pitch;
		*(p+2)=tile_pitch;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=addr50; VIDEOREG(NV_PGRAPH_RDI_DATA)=tile_pitch;
	}
	while	(	(*(pTile+0)!=*(p+0))||
			(((*(pTile+1))&0xFFFFC000)!=((*(p+1))&0xFFFFC000))||
			(*(pTile+2)!=*(p+2))	);

	if (tile_flags&0x80000000)	//Tag in use?
	{
		EncodedZStartTag=(tile_z_start_tag>>2)|0x80000000;

		if (tile_flags&0x04000000) EncodedZStartTag|=0x04000000;

		//points tile Zcomp in NV_PFB
		pZcomp=(DWORD *)(VIDEO_BASE+NV_PFB_ZCOMP+tile_index*4);

		//points tile Zcomp in NV_PGRAPH
		p=(DWORD *)(VIDEO_BASE+NV_PGRAPH_ZCOMP_XBOX+tile_index*4);

		//points tile Zcomp in NV_PGRAPH_RDI(0x90)
		addr90=((tile_index*4+0x90)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);

		do
		{
			pb_wait_until_gr_not_busy();

			*(pZcomp+0)=EncodedZStartTag;
			*(p+0)=EncodedZStartTag;
			VIDEOREG(NV_PGRAPH_RDI_INDEX)=addr90; VIDEOREG(NV_PGRAPH_RDI_DATA)=EncodedZStartTag;
		}while (*(pZcomp+0)!=*(p+0));

		if (tile_z_offset)
		{
			EncodedZOffset=tile_z_offset|tile_index|0x80000000;

			do
			{
				pb_wait_until_gr_not_busy();

				VIDEOREG(NV_PFB_ZCOMP_OFFSET)=EncodedZOffset;
				VIDEOREG(NV_PGRAPH_ZCOMP_OFFSET_XBOX)=EncodedZOffset;
			}while(VIDEOREG(NV_PFB_ZCOMP_OFFSET)!=VIDEOREG(NV_PGRAPH_ZCOMP_OFFSET_XBOX));
		}
	}

	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=old_dma_push;
}



static void pb_prepare_tiles(void)
{
	DWORD			*pTile;
	DWORD			*pTlimit;
	DWORD			*pTsize;
	DWORD			*pZcomp;

	DWORD			Tile;
	DWORD			Tlimit;
	DWORD			Tsize;
	DWORD			Zcomp;
	DWORD			Zcomp_offset;
	DWORD			Config0;
	DWORD			Config1;

	DWORD			*p;

	int			i;

	p=(DWORD *)(VIDEO_BASE+NV_PGRAPH_TILE_XBOX);
	pTlimit=(DWORD *)(VIDEO_BASE+NV_PFB_TLIMIT);
	pTsize=(DWORD *)(VIDEO_BASE+NV_PFB_TSIZE);
	pTile=(DWORD *)(VIDEO_BASE+NV_PFB_TILE);

	//Copy 8 Tiles details from NV_PFB to NV_PGRAPH and to NV_PGRAPH_RDI(0x10)
	for(i=0x10;i<0x30;i+=4)
	{
		Tile=*(pTile+0);
		*(p+0)=Tile;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=((i+0x00)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
		VIDEOREG(NV_PGRAPH_RDI_DATA)=Tile;

		Tlimit=*(pTlimit+0);
		*(p+1)=Tlimit;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=((i+0x20)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
		VIDEOREG(NV_PGRAPH_RDI_DATA)=Tlimit;

		Tsize=*(pTsize+0);
		*(p+2)=Tsize;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=((i+0x40)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
		VIDEOREG(NV_PGRAPH_RDI_DATA)=Tsize;

		p+=4; //move 16 bytes forward
		pTile+=4;
		pTlimit+=4;
		pTsize+=4;
	}

	p=(DWORD *)(VIDEO_BASE+NV_PGRAPH_ZCOMP_XBOX);
	pZcomp=(DWORD *)(VIDEO_BASE+NV_PFB_ZCOMP);

	//Copy 8 Tiles Zcomp from NV_PFB to NV_PGRAPH and to NV_PGRAPH_RDI(0x90)
	for(i=0x90;i<0x110;i+=4)
	{
		Zcomp=*(pZcomp+0);
		*(p+0)=Zcomp;
		VIDEOREG(NV_PGRAPH_RDI_INDEX)=((i+0x00)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
		VIDEOREG(NV_PGRAPH_RDI_DATA)=Tsize;

		p++; //move 4 bytes forward
		pZcomp++;
	}

	//Copy 3 parameters from NV_PFB to NV_PGRAPH and to NV_PGRAPH_RDI(sel 0xEA : 0xC, 0 & 4)

	Zcomp_offset=VIDEOREG(NV_PFB_ZCOMP_OFFSET);
	VIDEOREG(NV_PGRAPH_ZCOMP_OFFSET_XBOX)=Zcomp_offset;
	VIDEOREG(NV_PGRAPH_RDI_INDEX)=((0x0C)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	VIDEOREG(NV_PGRAPH_RDI_DATA)=Zcomp_offset;

	Config0=VIDEOREG(NV_PFB_CFG0);
	VIDEOREG(NV_PGRAPH_CFG0_XBOX)=Config0;
	VIDEOREG(NV_PGRAPH_RDI_INDEX)=((0x00)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	VIDEOREG(NV_PGRAPH_RDI_DATA)=Config0;

	Config1=VIDEOREG(NV_PFB_CFG1);
	VIDEOREG(NV_PGRAPH_CFG1_XBOX)=Config1;
	VIDEOREG(NV_PGRAPH_RDI_INDEX)=((0x04)&NV_PGRAPH_RDI_INDEX_ADDRESS)|((0xEA<<16)&NV_PGRAPH_RDI_INDEX_SELECT);
	VIDEOREG(NV_PGRAPH_RDI_DATA)=Config1;
}



static void pb_create_dma_ctx(	DWORD ChannelID,
				DWORD Class,
				DWORD Base,
				DWORD Limit,
				struct s_CtxDma *pDmaObject	)
{
	DWORD			Addr;
	DWORD			AddrSpace;
	DWORD			Inst;
	DWORD			dma_flags;

	Addr=0;
	AddrSpace=0;

	if ((Base&0xF0000000)!=0x80000000)
	{
		Addr=Base;
		AddrSpace=ADDR_FBMEM;
	}
	else
	{
		Addr=Base&0x03FFFFFF;
		AddrSpace=ADDR_SYSMEM;
	}

	Inst=pb_FreeInst; pb_FreeInst+=1; //reserve 1 block (16 bytes)

	dma_flags=Class;
	dma_flags|=0x00003000;
	if (AddrSpace==ADDR_AGPMEM) dma_flags|=0x00030000;
	if (AddrSpace==ADDR_SYSMEM) dma_flags|=0x00020000;
	dma_flags|=0x00008000;			

	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x08)=Addr|3;	//0x00000003|Addr
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x0C)=Addr|3;	//0x00000003|Addr
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x00)=dma_flags;	//0x???sB0cl ???=Addr&0xFFF
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x04)=Limit;	//0x03FFAFFF (MAXRAM)

	memset(pDmaObject,0,sizeof(struct s_CtxDma));

	pDmaObject->ChannelID=ChannelID;
	pDmaObject->Inst=Inst;
	pDmaObject->Class=Class;
	pDmaObject->isGr=0;
}




static void pb_bind_channel(struct s_CtxDma *pCtxDmaObject)
{
	DWORD		entry;
	DWORD		*p;
	
	//entry in hash table
	entry=(((pCtxDmaObject->ChannelID>>11)^pCtxDmaObject->ChannelID)>>11)^pCtxDmaObject->ChannelID;	

	//entry*8 max valid value is 0x1000

	//points at entry in hash table (table element size is 8 bytes = 2 dwords)
	p=(DWORD *)(VIDEO_BASE+pb_FifoHTAddr+entry*8);

	*(p+0)=	pCtxDmaObject->ChannelID;
	*(p+1)=	(0x80000000)|
		(pb_FifoChannelID<<24)|
		(pCtxDmaObject->isGr<<16)|
		(pCtxDmaObject->Inst&0xFFFF);
}	



static void pb_3D_init(void)
{
	DWORD			Inst;

	int 			channel;
	
	int			i;

	DWORD			offset;

	DWORD			offset_cmn;

	DWORD			offset_pipe;

	DWORD			offset_4dwords;

	DWORD			offset_20dwords;

	//Initialization of 3 big structures in PRAMIN area
	//At offset 0x0000 size=0x231C bytes=0x1A9C+0x0880
	//At offset 0x231C size=0x0C00 bytes
	//At offset 0x2F1C size=0x0784 bytes
	//Padding 4 dwords (at offset 0x36A0 size=0x0010 bytes?)

	channel=pb_FifoChannelID;

	Inst=pb_GrCtxInst[channel];

	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x000)|=1;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x33C)=0xFFFF0000;
	for(i=0x340;i<=0x39C;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x3A0)=0x0FFF0000;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x3A4)=0x0FFF0000;
	for(i=0x3A8;i<=0x478;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x47C)=0x00000101;
	for(i=0x480;i<=0x48C;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x490)=0x00000111;
	for(i=0x494;i<=0x4A4;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x4A8)=0x44400000;
	for(i=0x4AC;i<=0x4D0;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	for(i=0x4D4;i<=0x4E0;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x00030303;
	for(i=0x4E4;i<=0x4F0;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	for(i=0x4F4;i<=0x500;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x00080000;
	for(i=0x504;i<=0x508;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	for(i=0x50C;i<=0x518;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x01012000;
	for(i=0x51C;i<=0x528;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x000105B8;
	for(i=0x52C;i<=0x538;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x00080008;
	for(i=0x53C;i<=0x558;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	for(i=0x55C;i<=0x578;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x07FF0000; //8 dwords
	for(i=0x57C;i<=0x598;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0x07FF0000; //8 dwords
	for(i=0x59C;i<=0x5A0;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x5A4)=0x4B7FFFFF;
	for(i=0x5A8;i<=0x5F8;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x5FC)=0x00000001;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x600)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x604)=0x00004000;
	for(i=0x608;i<=0x60C;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x610)=0x00000001;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x614)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x618)=0x00040000;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x61C)=0x00010000;
	for(i=0x620;i<=0x628;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;
	for(i=0x62C;i<=0x6B4;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//35 dwords
	for(i=0x6B8;i<=0x728;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//26 dwords
	for(i=0x72C;i<=0x79C;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//26 dwords
	for(i=0x7A0;i<=0x810;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//26 dwords
	for(i=0x814;i<=0x818;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//2 dwords
	for(i=0x81C;i<=0xA18;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//128 dwords
	for(i=0xA1C;i<=0xC18;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//128 dwords
	for(i=0xC1C;i<=0xE18;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//128 dwords
	for(i=0xE1C;i<=0x1018;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//128 dwords
	for(i=0x101C;i<=0x1318;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//192 dwords
	for(i=0x131C;i<=0x1A98;i+=4) VIDEOREG(NV_PRAMIN+(Inst<<4)+i)=0;	//224 dwords

	offset=0x1A9C/4;	//number of dwords initialized so far = 0x6A7

	for(i=0;i<0x88;i++) //136 blocks (unit=16 bytes=4 dwords)
	{
		VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*16+0x00)=0x10700FF9;
		VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*16+0x04)=0x0436086C;
		VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*16+0x08)=0x000C001B;
		VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*16+0x0C)=0;
		offset+=4;
	}

	offset_cmn=offset;	//0x231C/4

	for(i=0;i<0x300;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//768 dwords
	offset+=0x300;	//0xC00 bytes

	offset_pipe=offset;	//0x2F1C/4

	for(i=0;i<0x68;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//104 dwords
	offset+=0x68;
	for(i=0;i<0xD0;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//208 dwords
	offset+=0xD0;
	offset_4dwords=offset;

	for(i=0;i<0x04;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//004 dwords
	offset+=0x04;
	offset_20dwords=offset;
	for(i=0;i<0x14;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//020 dwords
	offset+=0x14;
	for(i=0;i<0x0F;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//015 dwords
	offset+=0x0F;

	for(i=0;i<0x0E;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//014 dwords
	offset+=0x0E;
	for(i=0;i<0x44;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//068 dwords
	offset+=0x44;
	for(i=0;i<0x20;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//032 dwords
	offset+=0x20;
	for(i=0;i<0x0F;i++) VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4+i*4)=0;//015 dwords
	offset+=0x0F;

	//total: +0x1E0
	//theoretically, offset=0x369C/4=0xDA7

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset*4)=0;
	offset++;

	//total: +0x1E1
	//theoretically, offset=0x36A0/4=0xDA8

	//Padding : 4 dwords?

	//total: +0x1E5
	//theoretically, offset=0x36B0/4=0xDAC

#ifdef DBG
	if (offset+4!=0x36B0/4) debugPrint("pb_3D_init: bad final value for offset\n");
#endif
	//floating point post-initializations in cmn structure

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x380)=0x3F800000; //1.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x384)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x388)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x38C)=0x00000000; //0.0f

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3C0)=0x40000000; //2.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3C4)=0x3F800000; //1.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3C8)=0x3F000000; //0.5f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3CC)=0x00000000; //0.0f

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3D0)=0x40000000; //2.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3D4)=0x3F800000; //1.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3D8)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3DC)=0xBF800000; //-1.0f

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3E0)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3E4)=0xBF800000; //-1.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3E8)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3EC)=0x00000000; //0.0f

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x390)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x394)=0x3F800000; //1.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x398)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x39C)=0x00000000; //0.0f

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3F0)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3F4)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3F8)=0x00000000; //0.0f
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_cmn*4+0x3FC)=0x00000000; //0.0f

	//post-initializations in pipe structure

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x160)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x164)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x168)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x16C)=0;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x100)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x104)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x108)=0x000FE000;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x10C)=0;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x110)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x114)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x118)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x11C)=0;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x130)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x134)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x138)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x13C)=0;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x180)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x184)=0x000003F8;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x188)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_pipe*4+0x18C)=0;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_4dwords*4)=0x002FE000;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x010)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x014)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x018)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x01C)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x020)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x024)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x028)=0x001C527C;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+offset_20dwords*4+0x02C)=0x001C527C;

#ifdef DBG
	//at this point pb_GrCtxID and pb_FifoChannelID must be different
	//debugPrint("pb_3D_init: gr=%d fifo=%d\n",pb_GrCtxID,pb_FifoChannelID);
#endif
}





static void pb_create_gr_ctx(	int ChannelID,
				int Class,
				struct s_CtxDma *pGrObject	)
{
	DWORD			flags;
	DWORD			flags3D;

	int			size;

	DWORD			Inst;
	
	flags3D=0;

	if (	(Class!=GR_CLASS_30)&&
		(Class!=GR_CLASS_39)&&
		(Class!=GR_CLASS_62)&&
		(Class!=GR_CLASS_97)&&
		(Class!=GR_CLASS_9F)	) 
	{
		//"CreateGrObject invalid class number"
		size=Class;
	}
	else
	{
		size=16;		//16 bytes
		if (Class==GR_CLASS_97)
		{
			size=0x330;	//816 bytes
			flags3D=1;
		}
	}

	Inst=pb_FreeInst; pb_FreeInst+=(size>>4);

	if (flags3D)
	{
		pb_3DGrCtxInst[pb_FifoChannelID]=Inst;
		pb_3D_init();
	}


	flags=Class&0x000000FF;
	flags3D=0x00000000;

	if (Class==GR_CLASS_39) flags|=0x01000000;

	if (Class==GR_CLASS_97) flags3D=0x00000A00;

	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x00)=flags;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x04)=flags3D;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x08)=0;
	VIDEOREG(NV_PRAMIN+(Inst<<4)+0x0C)=0;


	memset(pGrObject,0,sizeof(struct s_CtxDma));

	pGrObject->ChannelID=ChannelID;
	pGrObject->Class=Class;
	pGrObject->isGr=1;
	pGrObject->Inst=Inst;
}


static void pb_start(void)
{
	if (pb_disable_gpu==0) //do we really want to send data to GPU?
	{
		//asks push buffer Dma engine to detect incoming Dma data (written at pb_Put)

		pb_cache_flush();
		*(pb_DmaUserAddr+0x40/4)=((DWORD)pb_Put)&0x03FFFFFF;
		//from now any write will be detected

#ifdef DBG
		if ((*(pb_DmaUserAddr+0x44/4))>0x04000000) 
		{
			debugPrint("pb_start: wrong GetAddr\n");
			return;
		}
#endif		
	}
}




static void pb_jump_to_head(void)
{
	//Have Dma engine pointer point at push buffer head again.
	//(so we don't run into the tail of push buffer)
	//The best method would be to call this once per frame since it costs time.
	//Of course, avoid writing more data than push buffer size in 1 frame time.
	//If it happens you will get a message suggesting to call pb_reset more often
	//or to enlarge push buffer (with pb_size, before calling pb_init).
	//Default size is 512Kb (128*1024 dwords)

	DWORD			*pGetAddr;

	DWORD			TimeStampTicks;

#ifdef DBG
	if (pb_BeginEndPair) 
	{
		debugPrint("pb_reset musn't be called inside a begin-end block.\n");
		return;
	}
#endif

	//writes a jump command
	//forces GPU to jump at push buffer head address at next fetch
	*(pb_Put+0)=1+(((DWORD)pb_Head)&0x0FFFFFFF);
	pb_Put=pb_Head;
	pb_start();

	TimeStampTicks=KeTickCount;	

	//wait for arrival of Gpu Get to push buffer head
	do
	{
		if ((*(pb_DmaUserAddr+0x44/4))>0x04000000) 
		{
#ifdef DBG
			debugPrint("pb_reset: bad getaddr\n");
#endif
			return;
		}


		if (KeTickCount-TimeStampTicks>TICKSTIMEOUT)
		{
			debugPrint("pb_reset: too long\n");
			break;
		}

		//converts physical address into virtual address
		pGetAddr=(DWORD *)((*(pb_DmaUserAddr+0x44/4))|0x80000000);
	}while (pGetAddr!=pb_Head);
			
}








//public functions

int pb_busy(void)
{
	DWORD			PutAddr;
	DWORD			GetAddr;

	GetAddr=*(pb_DmaUserAddr+0x44/4);
#ifdef DBG
	if (GetAddr>0x04000000) 
	{
		debugPrint("pb_busy: wrong GetAddr\n");
		return 0;
	}	
#endif
	PutAddr=(DWORD)pb_Put;

	if ((GetAddr^PutAddr)&0x0FFFFFFF) return 1; //means different addresses

	if (VIDEOREG(NV_PGRAPH_STATUS)) return 1;
	
	return 0;
}

DWORD pb_back_buffer_width(void)
{
	return	pb_FrameBuffersWidth;
}

DWORD pb_back_buffer_height(void)
{
	return pb_FrameBuffersHeight;
}

DWORD pb_back_buffer_pitch(void)
{
	return pb_FrameBuffersPitch;
}

DWORD *pb_back_buffer(void)
{
	return (DWORD *)pb_FBAddr[pb_back_index];
}

DWORD *pb_extra_buffer(int index_buffer)
{
	if (index_buffer>pb_ExtraBuffersCount)
	{
		debugPrint("pb_target_extra_buffer: buffer index out of range\n");
		return pb_back_buffer();
	}

	return (DWORD *)pb_EXAddr[index_buffer];
}


void pb_target_back_buffer(void)
{
	DWORD			*p;

	DWORD			width;
	DWORD			height;
	DWORD			pitch;
	DWORD			pitch_depth_stencil;

	DWORD			dma_flags;
	DWORD			dma_addr;
	DWORD			dma_limit;

	int			flag;
	int			depth_stencil;
	
	width=pb_FrameBuffersWidth;
	height=pb_FrameBuffersHeight;
	pitch=pb_FrameBuffersPitch;
	pitch_depth_stencil=pb_DepthStencilPitch;

	//DMA channel 9 is used by GPU in order to render pixels
	dma_addr=pb_FBAddr[pb_back_index]&0x03FFFFFF;
	dma_limit=height*pitch-1; //(last byte)
	dma_flags=DMA_CLASS_3D|0x0000B000;
	dma_addr|=3;

	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x08,dma_addr); p+=3; //set params addr,data
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(addr)=data
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x0C,dma_addr); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x00,dma_flags); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x04,dma_limit); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT3,9); p+=2;
	pb_end(p);

	//DMA channel 11 is used by GPU in order to bitblt images
	dma_addr=pb_FBAddr[pb_back_index]&0x03FFFFFF;
	dma_limit=height*pitch-1; //(last byte)
	dma_flags=DMA_CLASS_3D|0x0000B000;
	dma_addr|=3;
	
	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x08,dma_addr); p+=3; //set params addr,data
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(addr)=data
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x0C,dma_addr); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x00,dma_flags); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x04,dma_limit); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push1to(SUBCH_4,p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT2,11); p+=2;
	pb_end(p);

	depth_stencil=1;

	if (depth_stencil!=-1) //don't care
	if (pb_DepthStencilLast!=depth_stencil) //changed?
	{
		//DMA channel 10 is used by GPU in order to render depth stencil
		if (depth_stencil)
		{
			dma_addr=pb_DSAddr&0x03FFFFFF;
			dma_limit=height*pitch_depth_stencil-1; //(last byte)
			dma_flags=DMA_CLASS_3D|0x0000B000;
			dma_addr|=3;
			flag=1;
		}
		else
		{
			dma_addr=0;
			dma_limit=0;
			dma_flags=DMA_CLASS_3D|0x0000B000;
			dma_addr|=3;
			flag=0;
			pitch_depth_stencil=pitch;
		}
		
		p=pb_begin();
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2;
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x08,dma_addr); p+=3; //set params addr,data
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(addr)=data
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x0C,dma_addr); p+=3;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x00,dma_flags); p+=3;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x04,dma_limit); p+=3;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT4,10); p+=2;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_DEPTH_TEST_ENABLE,flag); p+=2;	//ZEnable=TRUE or FALSE (But don't use W, see below)
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_TEST_ENABLE,1); p+=2;	//StencilEnable=TRUE
		pb_end(p);

		pb_DepthStencilLast=depth_stencil;
	}

	p=pb_begin();
	pb_push3(p,NV20_TCL_PRIMITIVE_3D_BUFFER_PITCH,(pitch_depth_stencil<<16)|(pitch&0xFFFF),0,0); p+=4;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_HORIZ,width<<16,height<<16); p+=3;
	//Default (0x00100001)
	//We use W (0x00010000)
	//We don't enable YUV (0x10000000)
	//We don't use floating point depth (0x00001000)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_W_YUV_FPZ_FLAGS,0x00110001); p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BUFFER_FORMAT,pb_GPUFrameBuffersFormat|pb_FBVFlag); p+=2;
	pb_end(p);
}


void pb_target_extra_buffer(int index_buffer)
{
	DWORD			*p;

	DWORD			width;
	DWORD			height;
	DWORD			pitch;
	DWORD			pitch_depth_stencil;

	DWORD			dma_flags;
	DWORD			dma_addr;
	DWORD			dma_limit;

	int			flag;
	int			depth_stencil;

	if (index_buffer>=pb_ExtraBuffersCount)
	{
		debugPrint("pb_target_extra_buffer: buffer index out of range\n");
		return;
	}
	
	width=pb_FrameBuffersWidth;
	height=pb_FrameBuffersHeight;
	pitch=pb_FrameBuffersPitch;
	pitch_depth_stencil=pb_DepthStencilPitch;

	//DMA channel 9 is used by GPU in order to render pixels
	dma_addr=pb_EXAddr[index_buffer]&0x03FFFFFF;
	dma_limit=height*pitch-1; //(last byte)
	dma_flags=DMA_CLASS_3D|0x0000B000;
	dma_addr|=3;

	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x08,dma_addr); p+=3; //set params addr,data
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(addr)=data
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x0C,dma_addr); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x00,dma_flags); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID9Inst<<4)+0x04,dma_limit); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT3,9); p+=2;
	pb_end(p);

	//DMA channel 11 is used by GPU in order to bitblt images
	dma_addr=pb_EXAddr[index_buffer]&0x03FFFFFF;
	dma_limit=height*pitch-1; //(last byte)
	dma_flags=DMA_CLASS_3D|0x0000B000;
	dma_addr|=3;

	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x08,dma_addr); p+=3; //set params addr,data
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(addr)=data
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x0C,dma_addr); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x00,dma_flags); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID11Inst<<4)+0x04,dma_limit); p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
	pb_push1to(SUBCH_4,p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT2,11); p+=2;
	pb_end(p);
	
	depth_stencil=1;
	
	if (depth_stencil!=-1) //don't care
	if (pb_DepthStencilLast!=depth_stencil) //changed?
	{
		//DMA channel 10 is used by GPU in order to render depth stencil
		if (depth_stencil)
		{
			dma_addr=pb_DSAddr&0x03FFFFFF;
			dma_limit=height*pitch_depth_stencil-1; //(last byte)
			dma_flags=DMA_CLASS_3D|0x0000B000;
			dma_addr|=3;
			flag=1;
		}
		else
		{
			dma_addr=0;
			dma_limit=0;
			dma_flags=DMA_CLASS_3D|0x0000B000;
			dma_addr|=3;
			flag=0;
			pitch_depth_stencil=pitch;
		}
		
		p=pb_begin();
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2;
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x08,dma_addr); p+=3; //set params addr,data
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(addr)=data
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x0C,dma_addr); p+=3;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x00,dma_flags); p+=3;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PRAMIN+(pb_DmaChID10Inst<<4)+0x04,dma_limit); p+=3;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT4,10); p+=2;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_DEPTH_TEST_ENABLE,flag); p+=2;	//ZEnable=TRUE or FALSE (But don't use W, see below)
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_TEST_ENABLE,1); p+=2;	//StencilEnable=TRUE
		pb_end(p);

		pb_DepthStencilLast=depth_stencil;
	}

	p=pb_begin();
	pb_push3(p,NV20_TCL_PRIMITIVE_3D_BUFFER_PITCH,(pitch_depth_stencil<<16)|(pitch&0xFFFF),0,0); p+=4;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_HORIZ,width<<16,height<<16); p+=3;
	//Default (0x00100001)
	//We use W (0x00010000)
	//We don't enable YUV (0x10000000)
	//We don't use floating point depth (0x00001000)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_W_YUV_FPZ_FLAGS,0x00110001); p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BUFFER_FORMAT,pb_GPUFrameBuffersFormat|pb_FBVFlag); p+=2;
	pb_end(p);
}

DWORD pb_get_vbl_counter(void)
{
	return pb_vbl_counter; //allows caller to know if a frame has been missed
}


DWORD pb_wait_for_vbl(void)
{
	NtWaitForSingleObject(pb_VBlankEvent, FALSE, NULL);
	return pb_vbl_counter; //allows caller to know if a frame has been missed
}


void pb_print(char *format, ...)
{
	char 	buffer[512];
	int 	i;
	
	va_list argList;
	va_start(argList, format);
	vsprintf(buffer, format, argList);
	va_end(argList);

	for(i=0;i<strlen(buffer);i++) pb_print_char(buffer[i]);	
}

void pb_printat(int row, int col, char *format, ...)
{
	char 	buffer[512];
	int 	i;

	if ((row>=0)&&(row<ROWS)) pb_next_row=row;
	if ((col>=0)&&(col<COLS)) pb_next_col=col;
	
	va_list argList;
	va_start(argList, format);
	vsprintf(buffer, format, argList);
	va_end(argList);

	for(i=0;i<strlen(buffer);i++) pb_print_char(buffer[i]);	
}



void pb_erase_text_screen(void)
{
	pb_next_row=0;	
	pb_next_col=0;
	memset(pb_text_screen,0,sizeof(pb_text_screen));
}

void pb_draw_text_screen(void)
{
	int i,j,k,l,m,x1,x2,y;
	unsigned char c;

	for(i=0;i<ROWS;i++)
	for(j=0;j<COLS;j++)
	{
		c=pb_text_screen[i][j];
		if ((c==' ')||(c=='\t')) pb_text_screen[i][j]=0;
	}

	//convert pb_text_screen characters into push buffer commands
	//TODO: replace rectangle fill with texture copy when available!
	for(i=0;i<ROWS;i++)
	for(j=0;j<COLS;j++)
	{
		c=pb_text_screen[i][j];
		if (c)
		{
			for(l=0,x1=-1,x2=-1;l<8;l++,x1=-1,x2=-1)
			for(k=0,m=0x80;k<8;k++,m>>=1)					
			if (systemFont[c*8+l]&m)
			{
				if (x1>=0) 
					x2=20+j*10+k;
				else
					x1=20+j*10+k;
			}
			else
			{
				if (x2>=0)
				{
					y=25+i*25+l*2;
					pb_fill(x1,y,x2-x1+1,2,0xFFFFFF);
					x1=x2=-1;
				}
				else
				if (x1>=0)
				{
					y=25+i*25+l*2;
					pb_fill(x1,y,1,2,0xFFFFFF);
					x1=-1;
				}
			}
		}
	}	
}


void pb_extra_buffers(int n)
{
	if (n>MAX_EXTRA_BUFFERS)
		debugPrint("Too many extra buffers\n");
	else
		pb_ExtraBuffersCount=n;
}

void pb_size(DWORD size)
{
	if (pb_running)
		debugPrint("Can't set size while push buffer Dma engine is running.\n");
	else
	{
		if (size<64*1024)
			debugPrint("Push buffer size must be equal or larger than 64Kb.\n");
		else
		if ((size-1)&size)
			debugPrint("Push buffer size must be a power of 2.\n");
		else
		pb_Size=size;
	}
}


void pb_reset(void)
{
	pb_jump_to_head();
}


DWORD *pb_begin(void)
{
#ifdef DBG
	if (pb_Put>=pb_Tail) debugPrint("ERROR! Push buffer overflow! Use pb_reset more often or enlarge push buffer!\n");

	if (pb_BeginEndPair==1) debugPrint("pb_start without a pb_end earlier\n");
	pb_BeginEndPair=1;
	pb_PushIndex=0;
	pb_PushNext=pb_Put;
	pb_PushStart=pb_Put;
#endif
	return pb_Put;
}

#ifdef LOG
static FILE *fd;
static int logging=0;


void pb_start_log(void)
{
	if (logging) return;
	
	logging=1;
	
	fd=fopen("pbkit_record.txt","w");
}

void pb_stop_log(void)
{
	if (logging==0) return;
	
	logging=0;
	fclose(fd);
}
#endif


void pb_end(DWORD *pEnd)
{
	DWORD			TimeStamp1;
	DWORD			TimeStamp2;
	
	int			i;

#ifdef LOG
	DWORD			*p;
	int			n;
	
	if (logging)
	{
		p=pb_PushStart;		
		while (p!=pEnd)
		{
			n=(*p>>18)&0x7FF;
			fprintf(fd,"0x%08x, ",*(p++));
			for(i=0;i<n;i++) fprintf(fd,"0x%x, ",*(p++));
			fprintf(fd,"\n");
		}

	}
#endif

#ifdef DBG
	if (pb_BeginEndPair==0) debugPrint("pb_end without a pb_start\n");
	pb_BeginEndPair=0;
#endif

	pb_Put=pEnd;
	
	pb_start(); //start (or continue) reading and sending data to GPU

	if (pb_trace_mode) //do we want to wait until block data has been sent (for debugging GPU errors)?
	{
		
		TimeStamp1=KeTickCount;

		//wait until all begin-end block has been sent to GPU
		while(pb_busy())
		{
			TimeStamp2=KeTickCount;
			if (TimeStamp2-TimeStamp1>TICKSTIMEOUT)
			{
				debugPrint("pb_end: Busy for too long (%d) (%08x)\n",
					((DWORD)(pb_Put)-(DWORD)(pb_Head)),
					VIDEOREG(NV_PFIFO_CACHE1_DMA_GET)
					);
				break;
			}
		}
	}
}



void pb_push1to(DWORD subchannel, DWORD *p, DWORD command, DWORD param1)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push1to: new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push1to: missing pb_begin earlier\n");
	pb_PushIndex+=2;
	pb_PushNext+=2;
	if (pb_PushIndex>128) debugPrint("pb_push1to: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(subchannel,command,1);
	*(p+1)=param1;
}

void pb_push2to(DWORD subchannel, DWORD *p, DWORD command, DWORD param1, DWORD param2)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push2to : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push2to : missing pb_begin earlier\n");
	pb_PushIndex+=3;
	pb_PushNext+=3;
	if (pb_PushIndex>128) debugPrint("pb_push2to: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(subchannel,command,2);
	*(p+1)=param1;
	*(p+2)=param2;
}

void pb_push3to(DWORD subchannel, DWORD *p, DWORD command, DWORD param1, DWORD param2, DWORD param3)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push3to : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push3to : missing pb_begin earlier\n");
	pb_PushIndex+=4;
	pb_PushNext+=4;
	if (pb_PushIndex>128) debugPrint("pb_push3to: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(subchannel,command,3);
	*(p+1)=param1;
	*(p+2)=param2;
	*(p+3)=param3;
}

void pb_push4to(DWORD subchannel, DWORD *p, DWORD command, DWORD param1, DWORD param2, DWORD param3, DWORD param4)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push4to : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push4to : missing pb_begin earlier\n");
	pb_PushIndex+=5;
	pb_PushNext+=5;
	if (pb_PushIndex>128) debugPrint("pb_push4to: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(subchannel,command,4);
	*(p+1)=param1;
	*(p+2)=param2;
	*(p+3)=param3;
	*(p+4)=param4;
}


void pb_push1(DWORD *p, DWORD command, DWORD param1)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push1: new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push1: missing pb_begin earlier\n");
	pb_PushIndex+=2;
	pb_PushNext+=2;
	if (pb_PushIndex>128) debugPrint("pb_push1: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(SUBCH_3D,command,1);
	*(p+1)=param1;
}

void pb_push2(DWORD *p, DWORD command, DWORD param1, DWORD param2)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push2 : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push2 : missing pb_begin earlier\n");
	pb_PushIndex+=3;
	pb_PushNext+=3;
	if (pb_PushIndex>128) debugPrint("pb_push2: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(SUBCH_3D,command,2);
	*(p+1)=param1;
	*(p+2)=param2;
}

void pb_push3(DWORD *p, DWORD command, DWORD param1, DWORD param2, DWORD param3)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push3 : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push3 : missing pb_begin earlier\n");
	pb_PushIndex+=4;
	pb_PushNext+=4;
	if (pb_PushIndex>128) debugPrint("pb_push3: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(SUBCH_3D,command,3);
	*(p+1)=param1;
	*(p+2)=param2;
	*(p+3)=param3;
}

void pb_push4(DWORD *p, DWORD command, DWORD param1, DWORD param2, DWORD param3, DWORD param4)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push4 : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push4 : missing pb_begin earlier\n");
	pb_PushIndex+=5;
	pb_PushNext+=5;
	if (pb_PushIndex>128) debugPrint("pb_push4: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(SUBCH_3D,command,4);
	*(p+1)=param1;
	*(p+2)=param2;
	*(p+3)=param3;
	*(p+4)=param4;
}

void pb_push4f(DWORD *p, DWORD command, float param1, float param2, float param3, float param4)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push4f : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push4f : missing pb_begin earlier\n");
	pb_PushIndex+=5;
	pb_PushNext+=5;
	if (pb_PushIndex>128) debugPrint("pb_push4f: begin-end block musn't exceed 128 dwords\n");
#endif

	*(p+0)=EncodeMethod(SUBCH_3D,command,4);
	*((float *)(p+1))=param1;
	*((float *)(p+2))=param2;
	*((float *)(p+3))=param3;
	*((float *)(p+4))=param4;
}

void pb_push_transposed_matrix(DWORD *p, DWORD command, float *m)
{
#ifdef DBG
	if (p!=pb_PushNext) debugPrint("pb_push_transposed_matrix : new write address invalid or not following previous write addresses\n");
	if (pb_BeginEndPair==0) debugPrint("pb_push_transposed_matrix : missing pb_begin earlier\n");
	pb_PushIndex+=17;
	pb_PushNext+=17;
	if (pb_PushIndex>128) debugPrint("pb_push_transposed_matrix : begin-end block musn't exceed 128 dwords\n");
#endif

	*(p++)=EncodeMethod(SUBCH_3D,command,16);

	*((float *)p++)=m[_11];
	*((float *)p++)=m[_21];
	*((float *)p++)=m[_31];
	*((float *)p++)=m[_41];

	*((float *)p++)=m[_12];
	*((float *)p++)=m[_22];
	*((float *)p++)=m[_32];
	*((float *)p++)=m[_42];

	*((float *)p++)=m[_13];
	*((float *)p++)=m[_23];
	*((float *)p++)=m[_33];
	*((float *)p++)=m[_43];

	*((float *)p++)=m[_14];
	*((float *)p++)=m[_24];
	*((float *)p++)=m[_34];
	*((float *)p++)=m[_44];
}





void pb_show_front_screen(void)
{
	VIDEOREG(PCRTC_START)=pb_FBAddr[pb_front_index]&0x03FFFFFF;
	pb_debug_screen_active=0;
}

void pb_show_debug_screen(void)
{
	VIDEOREG(PCRTC_START)=((DWORD)XVideoGetFB())&0x0FFFFFFF;
	pb_debug_screen_active=1;
}

void pb_show_depth_screen(void)
{
	VIDEOREG(PCRTC_START)=pb_DSAddr&0x0FFFFFFF;
	pb_debug_screen_active=1;
}







void pb_set_viewport(int dwx,int dwy,int width,int height,float zmin,float zmax)
{
	DWORD			*p;
	DWORD			dwzminscaled;
	DWORD			dwzmaxscaled;
	float			x,y,w,h;

	if (dwx<0) dwx=0;
	if (dwy<0) dwy=0;
	if (dwx+width>pb_FrameBuffersWidth) width=pb_FrameBuffersWidth-dwx;
	if (dwy+height>pb_FrameBuffersHeight) height=pb_FrameBuffersHeight-dwy;

	pb_Viewport_x=dwx;
	pb_Viewport_y=dwy;
	pb_Viewport_width=width;
	pb_Viewport_height=height;
	pb_Viewport_zmin=zmin;
	pb_Viewport_zmax=zmax;

	x=0.53125f+(float)dwx;
	y=0.53125f+(float)dwy;
	w=0.5f*((float)pb_Viewport_width);
	h=-0.5f*((float)pb_Viewport_height);
	*((float *)&dwzminscaled)=zmin*pb_ZScale;
	*((float *)&dwzmaxscaled)=zmax*pb_ZScale;
/*
	p=pb_begin();
	pb_push4f(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_OX,x+0.53125f,y+0.53125f,0.0f,0.0f); p+=5;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_DEPTH_RANGE_NEAR,dwzminscaled,dwzmaxscaled); p+=3;
	pb_end(p);
*/
	p=pb_begin();
	pb_push4f(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_OX,x+w,y-h,zmin*pb_ZScale,0.0f); p+=5;
	pb_push4f(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_PX_DIV2,w,h,(zmax-zmin)*pb_ZScale,0.0f); p+=5;
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_DEPTH_RANGE_NEAR,dwzminscaled,dwzmaxscaled); p+=3;
	pb_end(p);
}



void pb_fill(int x, int y, int w, int h, DWORD color)
{
	DWORD		*p;

	int		x1,y1,x2,y2;

	x1=x;
	y1=y;
	x2=x+w;
	y2=y+h;
	
	//if you supply 32 bits color and res is 16 bits, apply function below
	//color=((color>>8)&0xF800)|((color>>5)&0x07E0)|((color>>3)&0x001F);

	p=pb_begin();
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_HORIZ,2);		//sets rectangle coordinates
	*(p++)=((x2-1)<<16)|x1;
	*(p++)=((y2-1)<<16)|y1;
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_DEPTH,3);		//sets data used to fill in rectangle
	*(p++)=0;			//(depth<<8)|stencil
	*(p++)=color;			//color
	*(p++)=0xF0; 			//triggers the HW rectangle fill (0x03 for D&S)
	pb_end(p);
}





//ALWAYS use this at beginning of frame or you may lose one third of performance because
//automatic compression algorithm for tile #1 can't afford any garbage left behind...
//Also, try to draw from closest distance to farest distance to help algorithm
//Depth is set to max and stencil is set to 0. We assume D24S8 format is used.
//Implies that depth test function is set to "less or equal"
void pb_erase_depth_stencil_buffer(int x, int y, int w, int h)
{
	DWORD		*p;

	int		x1,y1,x2,y2;

	x1=x;
	y1=y;
	x2=x+w;
	y2=y+h;
	
	p=pb_begin();
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_HORIZ,2);		//sets rectangle coordinates
	*(p++)=((x2-1)<<16)|x1;
	*(p++)=((y2-1)<<16)|y1;
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_CLEAR_VALUE_DEPTH,3);		//sets data used to fill in rectangle
	*(p++)=0xffffff00;		//(depth<<8)|stencil
	*(p++)=0;			//color
	*(p++)=0x03; 			//triggers the HW rectangle fill (only on D&S)
	pb_end(p);
}




//returns 1 if we have to retry later (means no free buffer, draw more details next time)
int pb_finished(void)
{
	DWORD			*p;

	if (pb_BackBufferbReady[pb_BackBufferNxt]) return 1; //table is full, retry later

	//insert in push buffer the commands to trigger screen swapping at next VBlank
	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_ASK_FOR_IDLE,0); p+=2; //ask for idle
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_NOP,0); p+=2; //wait for idle
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2; //wait/makespace (obtains null status)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,pb_back_index); p+=2; //set param=back buffer index to show up
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_FINISHED); p+=2; //subprogID PB_FINISHED: gets frame ready to show up soon
//	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STALL_PIPELINE,0); p+=2; //stall gpu pipeline (not sure it's needed in triple buffering technic)
	pb_end(p);

	//insert in push buffer the commands to trigger selection of next back buffer
	//(because previous ones may not have finished yet, so need to use 0x0100 call)
	pb_back_index=(pb_back_index+1)%3;
	pb_target_back_buffer();
	
	return 0;
}




void pb_kill(void)
{
	void			*pSavedData;
	int			i;
	DWORD			old_caches,old_push,old_pull;
	DWORD			*p;

	DWORD			TimeStampTicks;

	int			counter;

#ifdef DBG
//	debugPrint("Waiting until Dma is not busy\n");
#endif
	if (pb_Put)
	{	
		pb_start();
		pb_wait_until_gr_not_busy();

		*(pb_Put)=(((DWORD)pb_Head)&0x0FFFFFFF)+1; //writes a jump to push buffer head
		pb_Put=pb_Head;
		pb_start();

		TimeStampTicks=KeTickCount;

		while(1)
		{
			if ((*(pb_DmaUserAddr+0x44/4))>0x04000000) 
			{
				debugPrint("pb_kill: Bad get addr\n");
				break;
			}

			//did GetAddr reach push buffer head as planned?
			if (((*(pb_DmaUserAddr+0x44/4))&0x0FFFFFFF)==(((DWORD)pb_Head)&0x0FFFFFFF)) break;

			if (KeTickCount-TimeStampTicks>TICKSTIMEOUT)
			{
				debugPrint("pb_kill: Dma busy for too long\n");
				break;
			}
		}
	}
#ifdef DBG
//	if (KeTickCount-TimeStampTicks<=TICKSTIMEOUT) debugPrint("Dma not busy. All is ok.\n");
#endif

	//wait until screen swapping is finished (if one is on its way)
	while(pb_BackBufferbReady[pb_BackBufferNxt]);

	pb_running=0;

	if (pb_ExtraBuffersCount) MmFreeContiguousMemory((PVOID)pb_EXAddr[0]);
	if (pb_DepthStencilAddr) MmFreeContiguousMemory((PVOID)pb_DepthStencilAddr);
	if (pb_FrameBuffersAddr) MmFreeContiguousMemory((PVOID)pb_FrameBuffersAddr);

	if (pb_DmaBuffer8) MmFreeContiguousMemory(pb_DmaBuffer8);
	if (pb_DmaBuffer2) MmFreeContiguousMemory(pb_DmaBuffer2);
	if (pb_DmaBuffer7) MmFreeContiguousMemory(pb_DmaBuffer7);

	if (pb_Head) MmFreeContiguousMemory(pb_Head);


	//eventually restore a previously saved video mode

	pSavedData=AvGetSavedDataAddress();
	if (pSavedData==0) AvSendTVEncoderOption((PVOID)VIDEO_BASE,VIDEO_ENC_VIDEOENABLE,1,NULL);


	//restore system completely

	for(i=0;i<8;i++) pb_release_tile(i,1);

	VIDEOREG(NV_PFIFO_DMA_TIMESLICE)=NV_PFIFO_DMA_TIMESLICE_ALL_DISABLE;

	while (	((VIDEOREG8(NV_PFIFO_CACHE1_STATUS)&NV_PFIFO_CACHE1_STATUS_LOW_MARK_EMPTY)==0)||
		((VIDEOREG8(NV_PFIFO_RUNOUT_STATUS)&NV_PFIFO_RUNOUT_STATUS_LOW_MARK_EMPTY)==0)||
		((VIDEOREG8(NV_PFIFO_CACHE1_DMA_PUSH)&NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)!=0)	)
	{
		pb_fifo_handler();
		if (VIDEOREG(NV_PGRAPH_INTR)!=NV_PGRAPH_INTR_NOT_PENDING) pb_gr_handler();
		if (VIDEOREG(NV_PMC_INTR_0)&NV_PMC_INTR_0_PCRTC_PENDING) pb_vbl_handler();
	}

	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=NV_PFIFO_CACHE1_DMA_PUSH_ACCESS_DISABLE;
	while((VIDEOREG8(NV_PFIFO_CACHE1_DMA_PUSH)&NV_PFIFO_CACHE1_DMA_PUSH_STATE_BUSY)!=0);

	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE0_PUSH0)=NV_PFIFO_CACHE0_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE0_PULL0)=NV_PFIFO_CACHE0_PULL0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_DISABLE;

	pb_set_fifo_channel(1);

	VIDEOREG(NV_PFIFO_CACHE1_PUT)=0;
	VIDEOREG(NV_PFIFO_CACHE1_GET)=0;

	old_caches=VIDEOREG(NV_PFIFO_CACHES);
	old_push=VIDEOREG(NV_PFIFO_CACHE1_PUSH0);
	old_pull=VIDEOREG(NV_PFIFO_CACHE1_PULL0);
	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_DISABLE;

	//Neutralize DMA (for channels 0 and 1)
	for(i=0;i<2;i++)
	{
		if (pb_FifoChannelsReady) //any active channel?
		{
			p=(DWORD *)(VIDEO_BASE+pb_FifoFCAddr+i*64);
			*(p+1)=*(p+0);	//DMA_GET=DMA_PUT
			*(p+4)=0;	//DMA_STATE=0
		}
	}

	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=old_pull;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=old_push;
	VIDEOREG(NV_PFIFO_CACHES)=old_caches;

	VIDEOREG(NV_PFIFO_DMA)=NV_PFIFO_DMA_NOT_PENDING;
	VIDEOREG(NV_PFIFO_INTR_EN_0)=NV_PFIFO_INTR_EN_0_ALL_DISABLE;

	pb_load_gr_ctx(NONE);

	//restore most essential outer registers
	VIDEOREG(NV_PFB_CFG0)=pb_OldFBConfig0;
	VIDEOREG(NV_PFB_CFG1)=pb_OldFBConfig1;
	VIDEOREG(NV_PMC_ENABLE)=pb_OldMCEnable;
	VIDEOREG(NV_PMC_INTR_EN_0)=pb_OldMCInterrupt;
	VIDEOREG(PCRTC_START)=pb_OldVideoStart;

	pb_uninstall_gpu_interrupt();

	NtClose(pb_VBlankEvent);
}




int pb_init(void)
{
	DWORD			old;
	DWORD			mdiv,ndiv,odiv,pdiv,result;

	BYTE			old_color_31;
	BYTE			old_color_82;

	DWORD			baseaddr,baseaddr2;

	int			i,j,k;

	DWORD			*p;

	struct s_CtxDma	sDmaObject2;
	struct s_CtxDma	sDmaObject3;
	struct s_CtxDma	sDmaObject4;
	struct s_CtxDma	sDmaObject5;
	struct s_CtxDma	sDmaObject6;
	struct s_CtxDma	sDmaObject7;
	struct s_CtxDma	sDmaObject8;
	struct s_CtxDma	sDmaObject9;
	struct s_CtxDma	sDmaObject10;
	struct s_CtxDma	sDmaObject11;
	struct s_CtxDma	sDmaObject12;

	struct s_CtxDma	sGrObject13;
	struct s_CtxDma	sGrObject14;
	struct s_CtxDma	sGrObject16;
	struct s_CtxDma	sGrObject17;

	DWORD			UserAddr;

	DWORD			TimeStamp1;
	DWORD			TimeStamp2;
	DWORD			GetAddr;
	DWORD			PutAddr;
						//Dma channel properties
	int 			dma_trig=128;	//min 8		max 256 
	int			dma_size=128;	//min 32 	max 256 
	int			dma_max_reqs=8;	//min 0   	max 15

	DWORD			dummy;

	DWORD			channel;

	DWORD			*pGrCtxTable;

	VIDEO_MODE		vm;

	DWORD			format;

	DWORD			BackBufferCount;
	DWORD			BackBufferFormat;
	DWORD			DepthStencilFormat;

	DWORD			Width;
	DWORD			Height;

	DWORD			FrameBufferCount;

	DWORD			HScale;
	DWORD			VScale;

	DWORD			HSize;
	DWORD			VSize;

	DWORD			Pitch;

	DWORD			Addr;
	DWORD			Size;

	DWORD			FBAddr;
	DWORD			FBSize;

	DWORD			DSAddr;
	DWORD			DSSize;

	DWORD			EXAddr;
	DWORD			EXSize;
	
	int			n;

	DWORD			value;
	
	if (pb_running) return -8;

	//reset global vars (except pb_Size)

	pb_3DGrCtxInst[0]=0;
	pb_3DGrCtxInst[1]=0;

	pb_FifoChannelsReady=0;
	pb_FifoChannelsMode=NV_PFIFO_MODE_ALL_PIO;
	pb_FifoChannelID=0;

	pb_GammaRampIdx=0;
	for(i=0;i<3;i++) pb_GammaRampbReady[i]=0;
	for(k=0;k<3;k++) for(i=0;i<3;i++) for(j=0;j<256;j++) pb_GammaRamp[k][i][j]=j;

	pb_BackBufferNxt=0;
	for(i=0;i<5;i++) pb_BackBufferbReady[i]=0;

	pb_Put=NULL;

	pb_PutRunSize=0;

	pb_FrameBuffersAddr=0;


	pb_DmaBuffer8=MmAllocateContiguousMemoryEx(32,0,MAXRAM,0,4);
	pb_DmaBuffer2=MmAllocateContiguousMemoryEx(32,0,MAXRAM,0,4);
	pb_DmaBuffer7=MmAllocateContiguousMemoryEx(32,0,MAXRAM,0,4);
		//NumberOfBytes,LowestAcceptableAddress,HighestAcceptableAddress,Alignment,ProtectionType
	if ((pb_DmaBuffer8==NULL)||(pb_DmaBuffer2==NULL)||(pb_DmaBuffer7==NULL)) return -2;
	memset(pb_DmaBuffer8,0,32);
	memset(pb_DmaBuffer2,0,32);
	memset(pb_DmaBuffer7,0,32);

	pb_Head=MmAllocateContiguousMemoryEx(pb_Size+8*1024,0,MAXRAM,0,0x404);
		//NumberOfBytes,LowestAcceptableAddress,HighestAcceptableAddress,Alignment OPTIONAL,ProtectionType
	if (pb_Head==NULL) return -3;

	memset(pb_Head,0,pb_Size+8*1024);

	pb_Tail=pb_Head+pb_Size/4;

	pb_Put=pb_Head;

	pb_BackBufferNxt=0;		//increments when we finish drawing a frame
	pb_BackBufferbReady[0]=0;
	pb_BackBufferbReady[1]=0;
	pb_BackBufferbReady[2]=0;

	pb_BackBufferNxtVBL=0;		//increments when VBlank event fires

	//initialize push buffer DMA engine
	//DMA=Direct Memory Access (means CPU is not involved in the data transfert)

	NtCreateEvent(&pb_VBlankEvent, NULL, NotificationEvent, FALSE);

	VIDEOREG(NV_PBUS_PCI_NV_1)|=NV_PBUS_PCI_NV_1_BUS_MASTER_ENABLED;
	VIDEOREG(PCRTC_INTR_EN)=PCRTC_INTR_EN_VBLANK_DISABLED;
	VIDEOREG(NV_PTIMER_INTR_EN_0)=NV_PTIMER_INTR_EN_0_ALARM_DISABLED;

	if (pb_install_gpu_interrupt()==0)
	{
		if (pb_DmaBuffer8) MmFreeContiguousMemory(pb_DmaBuffer8);
		if (pb_DmaBuffer2) MmFreeContiguousMemory(pb_DmaBuffer2);
		if (pb_DmaBuffer7) MmFreeContiguousMemory(pb_DmaBuffer7);
		if (pb_Head) MmFreeContiguousMemory(pb_Head);
		NtClose(pb_VBlankEvent);
		return -4; //OpenXDK probably hooked IRQ3 already
	}

	//backup of the most essential outer registers (pb_kill will restore them)
	pb_OldMCEnable=VIDEOREG(NV_PMC_ENABLE);
	pb_OldMCInterrupt=VIDEOREG(NV_PMC_INTR_EN_0);
	pb_OldFBConfig0=VIDEOREG(NV_PFB_CFG0);
	pb_OldFBConfig1=VIDEOREG(NV_PFB_CFG1);
	pb_OldVideoStart=((DWORD)XVideoGetFB())&0x03FFFFFF;

	VIDEOREG(NV_PBUS_PCI_NV_12)=NV_PBUS_PCI_NV_12_ROM_DECODE_DISABLED;
	VIDEOREG(NV_PBUS_PCI_NV_3)=NV_PBUS_PCI_NV_3_LATENCY_TIMER_248_CLOCKS;

	VIDEOREG(NV_PMC_ENABLE)=NV_PMC_ENABLE_ALL_ENABLE;
	VIDEOREG(NV_PMC_INTR_EN_0)=NV_PMC_INTR_EN_0_INTA_HARDWARE;

	mdiv=(VIDEOREG(NV_PRAMDAC_NVPLL_COEFF)&NV_PRAMDAC_NVPLL_COEFF_MDIV);
	ndiv=(VIDEOREG(NV_PRAMDAC_NVPLL_COEFF)&NV_PRAMDAC_NVPLL_COEFF_NDIV)>>8;
	odiv=1;
	pdiv=(VIDEOREG(NV_PRAMDAC_NVPLL_COEFF)&NV_PRAMDAC_NVPLL_COEFF_PDIV)>>16;

	if (mdiv)
	{
		//Xtal in Xbox is at 16.666 Mhz but we want 31.25Mhz for GPU...
		if (((DW_XTAL_16MHZ*ndiv)/(odiv<<pdiv))/mdiv!=233333324)
		{
			//This PLL configuration doesn't create a 233.33 Mhz freq from Xtal
			//Have this issure reported so we can update source for that case
			debugPrint("PLL=%d\n",((DW_XTAL_16MHZ*ndiv)/(odiv<<pdiv))/mdiv);
			return -5;
		}
	}
	else
	{ 
		pb_kill(); 
		return -5; //invalid GPU internal PLL (Phase Locked Loop=GPU freq generator)
	}

	//program GPU timer in order to obtain 31.25Mhz (we assume PLL creates 233.33Mhz)
	VIDEOREG(NV_PTIMER_NUMERATOR)=56968; //233333324/56968*7629=31247365 (31.25Mhz)
	VIDEOREG(NV_PTIMER_DENOMINATOR)=7629;

	VIDEOREG(NV_PTIMER_ALARM_0)=0xFFFFFFFF;


	//The Gpu instance memory is a special place in PRAMIN area (VRAM attached to RAM?)
	//Essential Gpu data will be stored there, for, I guess, top speed access.
	
	if ((VIDEOREG(NV_PFB_CFG0)&NV_PFB_CFG0_PART_3)!=3)
	{
		pb_kill();
		return -6;
	}

	pb_GpuInstMem=(DWORD)MmClaimGpuInstanceMemory(0xFFFFFFFF,&baseaddr);
		//returns 0x83FF0000			//0x10000
		//physical_memory(0x83FF0000)=0x03FF0000

	if (pb_GpuInstMem==0)
	{
		pb_kill();
		return -7;
	}

	pb_GpuInstMem-=INSTANCE_MEM_MAXSIZE; 	//-0x5000=-20480=-20Kb
		// =0x83FEB000

	//a hash table
	pb_FifoHTAddr=baseaddr+NV_PRAMIN;	//0x10000+NV_PRAMIN(0x700000)

	VIDEOREG(NV_PFIFO_RAMHT)=((baseaddr>>8)&NV_PFIFO_RAMHT_BASE_ADDRESS)|NV_PFIFO_RAMHT_SEARCH_128;
			//      =NV_PFIFO_RAMHT_BASE_ADDRESS_10000

	//FC (size 0x80)
	pb_FifoFCAddr=baseaddr+NV_PRAMIN+0x1000;//=0x11000+NV_PRAMIN

	//U1 (size 0x20) Unknown1
	pb_FifoU1Addr=baseaddr+NV_PRAMIN+0x1080;//=0x11080+NV_PRAMIN

	//FC (dwFifoFCAddr, but 128 bytes aligned, with flag 0x200)
	baseaddr2=((pb_FifoFCAddr+0x80)&0x1FC00)|0x200; //0x11200

	VIDEOREG(NV_PFIFO_RAMFC)=baseaddr2<<7|((pb_FifoFCAddr>>8)&NV_PFIFO_RAMFC_BASE_ADDRESS);
					//   |NV_PFIFO_RAMFC_BASE_ADDRESS_11000
	//=0x00890110 (theoretical value)
	//=0x008A0110 (current value read under openxdk : |0x400 instead of |0x200)

	pb_FreeInst=(pb_FifoU1Addr-NV_PRAMIN+0x20)>>4;
			//     =0x110A (unit=16 bytes block)

	VIDEOREG(NV_PFB_NVM)=VIDEOREG(NV_PFB_NVM)&NV_PFB_NVM_MODE_DISABLE;

	//zeroes whole GPU instance memory
	for(i=0;i<INSTANCE_MEM_MAXSIZE;i+=4) VIDEOREG(NV_PRAMIN+baseaddr+i)=0;

	//reserve 8 blocks (128 bytes) for GrCtxTable 
	//(2 first dwords will point at the 2 graphic contexts for the 2 channels)
	pb_GrCtxTableInst=pb_FreeInst; pb_FreeInst+=8;






	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=31; old_color_31=VIDEOREG8(NV_PRMCIO_CR__COLOR);
	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=31; VIDEOREG8(NV_PRMCIO_CR__COLOR)=87;

	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=82; old_color_82=VIDEOREG8(NV_PRMCIO_CR__COLOR);
	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=82; VIDEOREG8(NV_PRMCIO_CR__COLOR)=old_color_82+4;

	VIDEOREG(NV_PVIDEO_DEBUG_2)=(VIDEOREG(NV_PVIDEO_DEBUG_2)&NV_PVIDEO_DEBUG_2_BURST1_CLEAR)|NV_PVIDEO_DEBUG_2_BURST1_INIT;
	VIDEOREG(NV_PVIDEO_DEBUG_2)=(VIDEOREG(NV_PVIDEO_DEBUG_2)&NV_PVIDEO_DEBUG_2_BURST2_CLEAR)|NV_PVIDEO_DEBUG_2_BURST2_INIT;

	VIDEOREG(NV_PVIDEO_DEBUG_3)=(VIDEOREG(NV_PVIDEO_DEBUG_3)&NV_PVIDEO_DEBUG_3_WATER_MARK1_CLEAR)|NV_PVIDEO_DEBUG_3_WATER_MARK1_INIT;
	VIDEOREG(NV_PVIDEO_DEBUG_3)=(VIDEOREG(NV_PVIDEO_DEBUG_3)&NV_PVIDEO_DEBUG_3_WATER_MARK2_CLEAR)|NV_PVIDEO_DEBUG_3_WATER_MARK2_INIT;

	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=32; VIDEOREG8(NV_PRMCIO_CR__COLOR)=41;
	VIDEOREG8(NV_PRMCIO_CRX__COLOR)=27; VIDEOREG8(NV_PRMCIO_CR__COLOR)=5;

	if (old_color_31==0)
	{
		VIDEOREG8(NV_PRMCIO_CRX__COLOR)=31; VIDEOREG8(NV_PRMCIO_CR__COLOR)=153;
	}

	VIDEOREG(NV_PCRTC_CONFIG)=(VIDEOREG(NV_PCRTC_CONFIG)&~NV_PCRTC_CONFIG_START_ADDRESS)|NV_PCRTC_CONFIG_START_ADDRESS_HSYNC;
	//3 replaced with 2=(3&~7)|2




	VIDEOREG(NV_PVIDEO_LUMINANCE_0)=NV_PVIDEO_LUMINANCE_CONTRAST_UNITY|NV_PVIDEO_LUMINANCE_BRIGHTNESS_UNITY;
	VIDEOREG(NV_PVIDEO_LUMINANCE_1)=NV_PVIDEO_LUMINANCE_CONTRAST_UNITY|NV_PVIDEO_LUMINANCE_BRIGHTNESS_UNITY;

	VIDEOREG(NV_PVIDEO_CHROMINANCE_0)=NV_PVIDEO_CHROMINANCE_SAT_COS_UNITY|NV_PVIDEO_CHROMINANCE_SAT_SIN_UNITY;
	VIDEOREG(NV_PVIDEO_CHROMINANCE_1)=NV_PVIDEO_CHROMINANCE_SAT_COS_UNITY|NV_PVIDEO_CHROMINANCE_SAT_SIN_UNITY;

//maybe let's preserve previous setting
//VIDEOREG(NV_PVIDEO_OFFSET_0)=NV_PVIDEO_OFFSET_VALUE_ZERO;
//VIDEOREG(NV_PVIDEO_OFFSET_1)=NV_PVIDEO_OFFSET_VALUE_ZERO;

	VIDEOREG(NV_PVIDEO_SIZE_IN_0)=NV_PVIDEO_SIZE_IN_UNKNOWN_WIDTH|NV_PVIDEO_SIZE_IN_UNKNOWN_HEIGHT;
	VIDEOREG(NV_PVIDEO_SIZE_IN_1)=NV_PVIDEO_SIZE_IN_UNKNOWN_WIDTH|NV_PVIDEO_SIZE_IN_UNKNOWN_HEIGHT;

	VIDEOREG(NV_PVIDEO_POINT_IN_0)=NV_PVIDEO_POINT_IN_S_ORIGIN|NV_PVIDEO_POINT_IN_T_ORIGIN;
	VIDEOREG(NV_PVIDEO_POINT_IN_1)=NV_PVIDEO_POINT_IN_S_ORIGIN|NV_PVIDEO_POINT_IN_T_ORIGIN;

	VIDEOREG(NV_PVIDEO_DS_DX_0)=NV_PVIDEO_DS_DX_RATIO_UNITY;
	VIDEOREG(NV_PVIDEO_DS_DX_1)=NV_PVIDEO_DS_DX_RATIO_UNITY;

	VIDEOREG(NV_PVIDEO_DT_DY_0)=NV_PVIDEO_DT_DY_RATIO_UNITY;
	VIDEOREG(NV_PVIDEO_DT_DY_1)=NV_PVIDEO_DT_DY_RATIO_UNITY;


	pb_GrCtxID=NONE;

	VIDEOREG(NV_PGRAPH_CHANNEL_CTX_TABLE)=pb_GrCtxTableInst&NV_PGRAPH_CHANNEL_CTX_TABLE_INST;

	p=(DWORD *)(VIDEO_BASE+NV_PRAMIN+(pb_GrCtxTableInst<<4));
	*(p+0)=0; //we don't point at the 2 graphic contexts yet
	*(p+1)=0;

	VIDEOREG(NV_PFIFO_CACHE1_PUT)=0;
	VIDEOREG(NV_PFIFO_CACHE1_GET)=0;
	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT)=0;
	VIDEOREG(NV_PFIFO_CACHE1_DMA_GET)=0;
	VIDEOREG(NV_PFIFO_CACHE0_HASH)=0;
	VIDEOREG(NV_PFIFO_CACHE1_HASH)=0;
	VIDEOREG(NV_PFIFO_MODE)=NV_PFIFO_MODE_ALL_PIO;
	VIDEOREG(NV_PFIFO_DMA)=NV_PFIFO_DMA_NOT_PENDING;
	VIDEOREG(NV_PFIFO_SIZE)=0;
	VIDEOREG(NV_PFIFO_CACHE1_DMA_STATE)=0;
	VIDEOREG(NV_PFIFO_RUNOUT_PUT)=0;
	VIDEOREG(NV_PFIFO_RUNOUT_GET)=0;

	pb_running=1;

	old=VIDEOREG(NV_PBUS_PCI_NV_19);
	VIDEOREG(NV_PBUS_PCI_NV_19)=old&NV_PBUS_PCI_NV_19_AGP_COMMAND_SBA_ENABLE_OFF&NV_PBUS_PCI_NV_19_AGP_COMMAND_AGP_ENABLE_OFF;
	VIDEOREG(NV_PBUS_PCI_NV_19)=old;

	VIDEOREG(PCRTC_INTR)=PCRTC_INTR_VBLANK_RESET;
	VIDEOREG(PCRTC_INTR_EN)=PCRTC_INTR_EN_VBLANK_ENABLED;

//VIDEOREG(NV_PTIMER_TIME_0)=0;
//VIDEOREG(NV_PTIMER_TIME_1)=ticks; //time & date in ticks (nasty calculation, let's skip it for now)

	VIDEOREG(NV_PGRAPH_FIFO)=NV_PGRAPH_FIFO_ACCESS_DISABLE;

	VIDEOREG(NV_PMC_ENABLE)=VIDEOREG(NV_PMC_ENABLE)&NV_PMC_ENABLE_PGRAPH_DISABLED;
	VIDEOREG(NV_PMC_ENABLE)=VIDEOREG(NV_PMC_ENABLE)|NV_PMC_ENABLE_PGRAPH_ENABLED;

	VIDEOREG(NV_PGRAPH_DEBUG_0) =	NV_PGRAPH_DEBUG_0_NO_RESET;

	VIDEOREG(NV_PGRAPH_DEBUG_1) =	NV_PGRAPH_DEBUG_1_VTX_PTE_ENABLED|
					NV_PGRAPH_DEBUG_1_VTX_CACHE_ENABLED|
					NV_PGRAPH_DEBUG_1_VTX_FILE_ENABLED|
					NV_PGRAPH_DEBUG_1_DRAWDIR_Y_INCR|
					NV_PGRAPH_DEBUG_1_INSTANCE_ENABLED|
					NV_PGRAPH_DEBUG_1_CTX_ENABLED;

	VIDEOREG(NV_PGRAPH_DEBUG_7) =	NV_PGRAPH_DEBUG_7_UNKNOWN_OPTIONS;

	VIDEOREG(NV_PGRAPH_DEBUG_3) =	NV_PGRAPH_DEBUG_3_FLUSHING_ENABLED|
					NV_PGRAPH_DEBUG_3_SYNC_TO_CRTC_ENABLED|
					NV_PGRAPH_DEBUG_3_FAST_DATA_STRTCH_ENABLED|
					NV_PGRAPH_DEBUG_3_FAST_3D_SHADOW_DATA_ENABLED|
					NV_PGRAPH_DEBUG_3_FAST_DMA_READ_ENABLED|
					NV_PGRAPH_DEBUG_3_IDLE_FILTER_ENABLED|
					NV_PGRAPH_DEBUG_3_SINGLE_CYCLE_LOAD_ENABLED|
					NV_PGRAPH_DEBUG_3_BILINEAR_3D_ENABLED|
					NV_PGRAPH_DEBUG_3_VOLATILE_RESET_ENABLED|
					NV_PGRAPH_DEBUG_3_DATA_CHECK_ENABLED|
					NV_PGRAPH_DEBUG_3_FORMAT_CHECK_ENABLED|
					NV_PGRAPH_DEBUG_3_DMA_CHECK_ENABLED|
					NV_PGRAPH_DEBUG_3_STATE_CHECK_ENABLED|
					NV_PGRAPH_DEBUG_3_IMAGE_64BIT_ENABLED|
					NV_PGRAPH_DEBUG_3_XFMODE_COALESCE_ENABLED|
					NV_PGRAPH_DEBUG_3_CTX_METHODS_ENABLED|
					NV_PGRAPH_DEBUG_3_OP_METHODS_ENABLED|
					NV_PGRAPH_DEBUG_3_IGNORE_PATCHVALID_ENABLED;

	VIDEOREG(NV_PGRAPH_DEBUG_4) = NV_PGRAPH_DEBUG_4_ALL_DISABLE;

	VIDEOREG(NV_PGRAPH_DEBUG_5) = NV_PGRAPH_DEBUG_5_ZCULL_SPARE2_ENABLED;

	if (VIDEOREG(NV_PBUS_ROM_VERSION)&NV_PBUS_ROM_VERSION_MASK)
		VIDEOREG(NV_PGRAPH_UNKNOWN_400B80)=0x45EAD10F;
	else
		VIDEOREG(NV_PGRAPH_UNKNOWN_400B80)=0x45EAD10E;
	VIDEOREG(NV_PGRAPH_UNKNOWN_400B84)=0;
	VIDEOREG(NV_PGRAPH_UNKNOWN_400B88)=0;

	VIDEOREG(NV_PGRAPH_UNKNOWN_400098)=0x78;
	VIDEOREG(NV_PGRAPH_UNKNOWN_40009C)=0x40;

	VIDEOREG(NV_PGRAPH_CHANNEL_CTX_TABLE)=pb_GrCtxTableInst&NV_PGRAPH_CHANNEL_CTX_TABLE_INST;

	pb_wait_until_gr_not_busy();

	pb_prepare_tiles();

	VIDEOREG(NV_PGRAPH_CTX_SWITCH1)=NV_PGRAPH_CTX_SWITCH1_ALL_DISABLE;
	VIDEOREG(NV_PGRAPH_CTX_SWITCH2)=NV_PGRAPH_CTX_SWITCH2_ALL_DISABLE;
	VIDEOREG(NV_PGRAPH_CTX_SWITCH3)=NV_PGRAPH_CTX_SWITCH3_ALL_DISABLE;
	VIDEOREG(NV_PGRAPH_CTX_SWITCH4)=NV_PGRAPH_CTX_SWITCH4_ALL_DISABLE;

	VIDEOREG(NV_PGRAPH_CTX_CONTROL)=NV_PGRAPH_CTX_CONTROL_DEVICE_ENABLED;

	VIDEOREG(NV_PGRAPH_FFINTFC_ST2)=NV_PGRAPH_FFINTFC_ST2_CHID_STATUS_VALID;

	pb_load_gr_ctx(pb_GrCtxID);


	VIDEOREG(NV_PGRAPH_INTR)=NV_PGRAPH_INTR_ALL_ENABLE;
	VIDEOREG(NV_PGRAPH_INTR_EN)=NV_PGRAPH_INTR_EN_ALL_ENABLE;


	VIDEOREG(NV_PFIFO_CACHE1_DMA_FETCH) =	NV_PFIFO_CACHE1_DMA_FETCH_TRIG_128_BYTES|
						NV_PFIFO_CACHE1_DMA_FETCH_SIZE_32_BYTES|
						NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS_15;

	VIDEOREG(NV_PFIFO_DMA_TIMESLICE) =	NV_PFIFO_DMA_TIMESLICE_SELECT_128K|
						NV_PFIFO_DMA_TIMESLICE_TIMEOUT_ENABLED;

	VIDEOREG(NV_PFIFO_DELAY_0)=255&NV_PFIFO_DELAY_0_WAIT_RETRY;
	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE0_PUSH0)=NV_PFIFO_CACHE0_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE0_PULL0)=NV_PFIFO_CACHE0_PULL0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=NV_PFIFO_CACHE1_DMA_PUSH_ACCESS_DISABLE;

	pb_set_fifo_channel(1);

	VIDEOREG(NV_PFIFO_CACHE1_PUT)=0;	//&NV_PFIFO_CACHE1_PUT_ADDRESS
	VIDEOREG(NV_PFIFO_CACHE1_GET)=0;	//&NV_PFIFO_CACHE1_GET_ADDRESS

	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_ENABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_ENABLE;

	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_REASSIGN_ENABLED;
	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;

	VIDEOREG(NV_PFIFO_INTR_0)=NV_PFIFO_INTR_0_ALL_RESET;
	VIDEOREG(NV_PFIFO_INTR_EN_0)=NV_PFIFO_INTR_EN_0_ALL_ENABLE;;

	//calculate number of CPU cycles per second
	HalReadWritePCISpace(0,0x60,0x6C,&value,4,FALSE);
		//BusNumber,SlotNumber,RegisterNumber,pBuffer,Length,bWritePCISpace
	if (value&0xFF)	
		pb_CpuFrequency=5.5f*((float)((value>>8)&0xFF))*(XTAL_16MHZ/((float)(value&0xFF)));
	else
		pb_CpuFrequency=733.33f; //Mhz, theoretically

	pb_create_dma_ctx(3,DMA_CLASS_3D,0,MAXRAM,&sDmaObject3);
	pb_create_dma_ctx(5,DMA_CLASS_2,0,MAXRAM,&sDmaObject5);
	pb_create_dma_ctx(4,DMA_CLASS_3,0,MAXRAM,&sDmaObject4);

	pb_create_dma_ctx(9,DMA_CLASS_3D,0,MAXRAM,&sDmaObject9);
	pb_create_dma_ctx(10,DMA_CLASS_3D,0,MAXRAM,&sDmaObject10);
	pb_create_dma_ctx(11,DMA_CLASS_3D,0,MAXRAM,&sDmaObject11);
	pb_DmaChID9Inst=sDmaObject9.Inst;
	pb_DmaChID10Inst=sDmaObject10.Inst;
	pb_DmaChID11Inst=sDmaObject11.Inst;

	pb_create_dma_ctx(2,DMA_CLASS_3,(DWORD)pb_DmaBuffer2,0x1F,&sDmaObject2);
	pb_create_dma_ctx(7,DMA_CLASS_3D,(DWORD)pb_DmaBuffer7,0x1F,&sDmaObject7);
	//this one is damn important. memory address 0x80000000 acts as a trigger.
	pb_create_dma_ctx(12,DMA_CLASS_3D,0x80000000,0x10000000,&sDmaObject12);
	pb_create_dma_ctx(8,DMA_CLASS_3D,(DWORD)pb_DmaBuffer8,0x20,&sDmaObject8);
	pb_create_dma_ctx(6,DMA_CLASS_2,0,MAXRAM,&sDmaObject6);

	//we initialized channel 0 first, that will match graphic context 0
	pb_FifoChannelID=0;
	pb_FifoChannelsMode=NV_PFIFO_MODE_ALL_PIO;

	pb_FifoBigInst=pb_FreeInst; pb_FreeInst+=0x37F; //895 blocks=14320 bytes=0x37F0 bytes

	dummy=VIDEOREG(NV_PFIFO_CACHES);

	channel=pb_FifoChannelID;	

	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_ALL_DISABLE;

	//zeroes 0x37F0 bytes (0xDFC/4=0x37F blocks, 4 dwords in 1 block)
	for(i=0;i<0xDFC;i++) VIDEOREG(NV_PRAMIN+(pb_FifoBigInst<<4)+i*4)=0;

	//here we go, we initialize first graphic context pointer
	pGrCtxTable=(DWORD *)(VIDEO_BASE+NV_PRAMIN+(pb_GrCtxTableInst<<4));
	*(pGrCtxTable+channel)=pb_FifoBigInst;
	pb_GrCtxInst[channel]=pb_FifoBigInst;

	//points at channel details in PRAMIN area
	p=(DWORD *)(VIDEO_BASE+pb_FifoFCAddr+channel*64);

	//zeroes details
	for(i=0;i<16;i++) *(p+i)=0;

	//set dma instance, future value for VIDEOREG(NV_PFIFO_CACHE1_DMA_INSTANCE)
	*(p+3)=sDmaObject6.Inst;

	//encode trig & size
	dma_trig=(dma_trig>>3)-1;
	dma_size=(dma_size>>5)-1;

	//set dma fetch, future value for VIDEOREG(NV_PFIFO_CACHE1_DMA_FETCH)
	*(p+5)=	((dma_trig<<3)&NV_PFIFO_CACHE1_DMA_FETCH_TRIG)|
		((dma_size<<13)&NV_PFIFO_CACHE1_DMA_FETCH_SIZE)|
		((dma_max_reqs<<16)&NV_PFIFO_CACHE1_DMA_FETCH_MAX_REQS);
		
	pb_FifoChannelsMode|=(1<<channel);
	VIDEOREG(NV_PFIFO_MODE)=pb_FifoChannelsMode;

	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_DISABLE;

	VIDEOREG(NV_PFIFO_CACHE1_PUSH1)=channel&NV_PFIFO_CACHE1_PUSH1_CHID;

	if (pb_FifoChannelsMode&(1<<channel)) VIDEOREG(NV_PFIFO_CACHE1_PUSH1)|=NV_PFIFO_CACHE1_PUSH1_MODE_DMA;

	VIDEOREG(NV_PFIFO_CACHE1_DMA_PUT)=0;	//&NV_PFIFO_CACHE1_DMA_PUT_OFFSET
	VIDEOREG(NV_PFIFO_CACHE1_DMA_GET)=0;	//&NV_PFIFO_CACHE1_DMA_GET_OFFSET
	VIDEOREG(NV_PFIFO_CACHE1_DMA_INSTANCE)=*(p+3);
	VIDEOREG(NV_PFIFO_CACHE1_DMA_CTL)=NV_PFIFO_CACHE1_DMA_CTL_ALL_DISABLE;
	VIDEOREG(NV_PFIFO_CACHE1_DMA_STATE)=NV_PFIFO_CACHE1_DMA_STATE_METHOD_COUNT_0;
	VIDEOREG(NV_PFIFO_CACHE1_ENGINE)=NV_PFIFO_CACHE1_ENGINE_ALL_SW;
	VIDEOREG(NV_PFIFO_CACHE1_DMA_FETCH)=*(p+5);

	if (pb_FifoChannelsMode&(1<<channel)) VIDEOREG(NV_PFIFO_CACHE1_DMA_PUSH)=NV_PFIFO_CACHE1_DMA_PUSH_ACCESS_ENABLE;

	VIDEOREG(NV_PFIFO_CACHE1_PULL0)=NV_PFIFO_CACHE1_PULL0_ACCESS_ENABLE;
	VIDEOREG(NV_PFIFO_CACHE1_PUSH0)=NV_PFIFO_CACHE1_PUSH0_ACCESS_ENABLE;
	VIDEOREG(NV_PFIFO_CACHES)=NV_PFIFO_CACHES_REASSIGN_ENABLED;

	pb_FifoChannelsReady|=(1<<channel);

	UserAddr=VIDEO_BASE+NV_USER+(pb_FifoChannelID<<16);

	pb_bind_channel(&sDmaObject6);
	pb_bind_channel(&sDmaObject12);
	pb_bind_channel(&sDmaObject2);
	pb_bind_channel(&sDmaObject7);
	pb_bind_channel(&sDmaObject4);
	pb_bind_channel(&sDmaObject5);
	pb_bind_channel(&sDmaObject3);
	pb_bind_channel(&sDmaObject9);
	pb_bind_channel(&sDmaObject10);
	pb_bind_channel(&sDmaObject11);
	pb_bind_channel(&sDmaObject8);

	//These objects match the GPU sub channels (3D, 2, 3, 4, in that order)
	pb_create_gr_ctx(13,GR_CLASS_97,&sGrObject13);
	pb_create_gr_ctx(14,GR_CLASS_39,&sGrObject14);
	pb_create_gr_ctx(16,GR_CLASS_9F,&sGrObject16);
	pb_create_gr_ctx(17,GR_CLASS_62,&sGrObject17);
	pb_bind_channel(&sGrObject13);
	pb_bind_channel(&sGrObject14);
	pb_bind_channel(&sGrObject16);
	pb_bind_channel(&sGrObject17);

	pb_DmaUserAddr=(DWORD *)UserAddr;	//VIDEOBASE+NV_USER+(0<<16)

	pb_PushBase=(DWORD)pb_Head;
	pb_PushLimit=(DWORD)pb_Tail;

	//This is the magic part of the whole push buffer DMA engine thing...
	//Both these instructions are necessary, remove one, then no dma engine!
	*((DWORD *)0x80000000)=(((DWORD)pb_Head)&0x0FFFFFFF)+1;
	__asm__ __volatile__ ("wbinvd");
	//assembler instruction wbinvd : write back and invalidate cache

	pb_start(); //start checking if new data has been written and send it to GPU
	//(nothing will be sent, since we sent nothing yet)

	TimeStamp1=KeTickCount;

#ifdef DBG
//	debugPrint("Waiting undil DMA is ready\n");
#endif
	//wait until DMA is ready
	while(1)
	{
		GetAddr=*(pb_DmaUserAddr+0x44/4);
	
		if (GetAddr>0x04000000) 
		{
			debugPrint("pb_init: Bad getaddr\n");
			pb_kill();
			return -9;
		}	

		PutAddr=((DWORD)pb_Put);

		if (((GetAddr^PutAddr)&0x0FFFFFFF)==0) break; //means same addresses (Dma is ready)
	
		TimeStamp2=KeTickCount;

		if (TimeStamp2-TimeStamp1>TICKSTIMEOUT)
		{
			debugPrint("pb_init: Dma didn't get ready in time\n");
			pb_kill();
			return -10;
		}		
	}
#ifdef DBG
//	debugPrint("Dma is ready!!!\n");
#endif

	*((DWORD *)0x80000000)=0xFFFFFFFF;

	//Let's start initializing inner GPU registers!!!

	//These commands assign DMA channels to push buffer subchannels
	//and associate some specific GPU parts to specific Dma channels
	p=pb_begin();
	pb_push1to(SUBCH_2,p,NV20_TCL_PRIMITIVE_SET_MAIN_OBJECT,14); p+=2;
	pb_push1to(SUBCH_3,p,NV20_TCL_PRIMITIVE_SET_MAIN_OBJECT,16); p+=2;
	pb_push1to(SUBCH_4,p,NV20_TCL_PRIMITIVE_SET_MAIN_OBJECT,17); p+=2;
	pb_push1to(SUBCH_3D,p,NV20_TCL_PRIMITIVE_SET_MAIN_OBJECT,13); p+=2;
	pb_push1to(SUBCH_2,p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT0,7); p+=2;
	pb_push1to(SUBCH_3,p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT5,17); p+=2;
	pb_push1to(SUBCH_3,p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT_UNKNOWN,3); p+=2;
	pb_push2to(SUBCH_4,p,NV20_TCL_PRIMITIVE_3D_SET_OBJECT1,3,11); p+=3;
	pb_end(p); //calls pb_start() which will trigger the reading and sending to GPU (asynchronous, no waiting)

	//setup needed for color computations
	p=pb_begin();
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_SET_OBJECT0,3);
	*(p++)=2;
	*(p++)=3;
	*(p++)=3;
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_SET_OBJECT2A,6);
	*(p++)=4;
	*(p++)=9;
	*(p++)=10;
	*(p++)=3;
	*(p++)=3;
	*(p++)=8;
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_SET_OBJECT8,1);
	*(p++)=12;
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_ACTIVATE_COLORS,1);
	*(p++)=0;
	pb_end(p);

	p=pb_begin();
	pb_push1(p,0x09FC,1); p+=2;
	pb_push4f(p,0x0A50,0.0f,0.0f,0.0f,1.0f); p+=5;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_EDGE_FLAG,1); p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_SHADER_PREVIOUS,0x00210000); p+=2; //(PSTextureInput) What previous stage is used at each stage
	pb_push1(p,0x1D80,1); p+=2;
	pb_push1(p,0x1E68,0x7F800000); p+=2;
	pb_push1(p,0x1D78,1); p+=2;
	pb_end(p);

	p=pb_begin();
	pb_push_transposed_matrix(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_A(0),pb_IdentityMatrix); p+=17;
	pb_push_transposed_matrix(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_A(4),pb_IdentityMatrix); p+=17;
	pb_push_transposed_matrix(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_A(8),pb_IdentityMatrix); p+=17;
	pb_push_transposed_matrix(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_A(12),pb_IdentityMatrix); p+=17;
/*	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_ENABLE(0),0x2202);  p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_ENABLE(1),0x2202);  p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_ENABLE(2),0x2202);  p+=2;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CLIP_PLANE_ENABLE(3),0x2202);  p+=2;
*/	pb_push4f(p,0x09D0,0.0f,0.0f,1.0f,0.0f); p+=5;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_ID,0x0000003C); p+=2; //set shader constants cursor at C-36
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,12); 		//loads C-36, C-35 & C-34
	memcpy(p,pb_FixedPipelineConstants,12*4); p+=12; //used by common xbox shaders, but I doubt we will use them.
	//(also usually C-37 is screen center offset Decals vector & c-38 is Scales vector)
	pb_end(p);

	//Frame buffers creation
	//So far, tested only with 640*480 32 bits (default openxdk res)
	//Even if it's a waste of memory, for now, we will leave the openxdk (& SDL)
	//default frame buffer untouched. debugPrint (& SDL) will still target it.
	//We will provide functions pb_show_debug_screen() and pb_show_front_screen()
	//in order to let user (developper) toggle between screens at will.

	pb_FrameBuffersAddr=0;
	pb_DepthStencilAddr=0;
	pb_DepthStencilLast=-2;

	vm=XVideoGetMode();
	if (vm.bpp==32) pb_GPUFrameBuffersFormat=0x128;//A8R8G8B8
	else pb_GPUFrameBuffersFormat=0x113;		//R5G6B5 (0x123 if D24S8 used, bpp 16 untested)
	pb_ZScale=16777215.0f;				//D24S8
	Width=vm.width;
	Height=vm.height;

	BackBufferCount=2;			//triple buffering technic!
						//allows dynamic details adjustment

	pb_FrameBuffersCount=BackBufferCount+1; //front buffer + back buffers
	pb_FrameBuffersWidth=Width;
	pb_FrameBuffersHeight=Height;

	HScale=1;
	VScale=1;

	HSize=HScale*Width;	//Total width
	VSize=VScale*Height;	//Total height

	//Front and back buffers (tile #0)

	FrameBufferCount=BackBufferCount+1;

	//pitch is the gap between start of a pixel line and start of next pixel line
	//(not necessarily the size of a pixel line, because of hardware optimization)

	Pitch=(((vm.bpp*HSize)>>3)+0x3F)&0xFFFFFFC0; //64 units aligned
	pb_FrameBuffersPitch=Pitch;

	//look for a standard listed pitch value greater or equal to theoretical one
	for(i=0;i<16;i++)
	{
		if (pb_TilePitches[i]>=Pitch)
		{
			Pitch=pb_TilePitches[i];
			break;
		}
	}

	Size=Pitch*VSize;

	//verify 64 bytes alignment for size of a frame buffer
	if (Size&(64-1)) debugPrint("pb_init: FBSize is not well aligned.\n");

	pb_FBSize=Size;

	//multiply size by number of physical frame buffers in order to obtain global size
	FBSize=Size*FrameBufferCount;

	//Huge alignment enforcement (16 Kb aligned!) for the global size
	FBSize=(FBSize+0x3FFF)&0xFFFFC000;

	FBAddr=(DWORD)MmAllocateContiguousMemoryEx(FBSize,0,0x03FFB000,0x4000,0x404);
		//NumberOfBytes,LowestAcceptableAddress,HighestAcceptableAddress,Alignment OPTIONAL,ProtectionType

	pb_FBGlobalSize=FBSize;

	pb_FrameBuffersAddr=FBAddr;
	if (!FBAddr) 
	{
		pb_kill();
		return -11;
	}

	for(i=0;i<FrameBufferCount;i++)
	{	
		pb_FBAddr[i]=FBAddr;
		FBAddr+=Size;
	}

	//8 separate memory contiguous memory zones can be assigned to 8 GPU 'tiles'
	//simultaneously. GPU will apply automatic optimizations or caching on tiles.
	//The most important one is the automatic compression of data (by chunk of
	//16 dwords) in the depth stencil buffer. This buffer reading and writing
	//consumes most of the GPU time. By replacing the 16 dwords by a few dwords
	//(2 or 4), potential performance gain is about one third of frame time (60fps).
	//It is necessary to clear depth stencil buffer entirely at beginning of
	//each frame and draw things from closest depth to farest depth in order to
	//take full benefit of this very important feature. All fast games use it.
	//Compression is calculated by picking up central value of 4x4 block and
	//coding global x & y variation, plus all needed adjustments necessary to
	//fully recover original values. Compression is aborted if the 16 dwords have
	//very different values (will occur at the edges of projected triangles).

	pb_assign_tile(	0,				//int	tile_index,
			pb_FrameBuffersAddr&0x03FFFFFF,	//DWORD	tile_addr,
			FBSize,				//DWORD	tile_size,
			Pitch,				//DWORD	tile_pitch,
			0,				//DWORD	tile_z_start_tag,
			0,				//DWORD	tile_z_offset,
			0				//DWORD	tile_flags
			);


	//Depth stencil buffer (tile #1)
	
	//pitch is the gap between start of a pixel line and start of next pixel line
	//(not necessarily the size of a pixel line, because of hardware optimization)

	Pitch=(((vm.bpp*HSize)>>3)+0x3F)&0xFFFFFFC0; //64 units aligned
	pb_DepthStencilPitch=Pitch;

	//look for a standard listed pitch value greater or equal to theoretical one
	for(i=0;i<16;i++)
	{
		if (pb_TilePitches[i]>=Pitch)
		{
			Pitch=pb_TilePitches[i];
			break;
		}
	}

	Size=Pitch*VSize;

	//verify 64 bytes alignment for size of a frame buffer
	if (Size&(64-1)) debugPrint("pb_init: DSSize is not well aligned.\n");

	pb_DSSize=Size;

	//multiply size by number of physical frame buffers in order to obtain global size
	DSSize=Size*FrameBufferCount;

	//Huge alignment enforcement (16 Kb aligned!) for the global size
	DSSize=(DSSize+0x3FFF)&0xFFFFC000;

	DSAddr=(DWORD)MmAllocateContiguousMemoryEx(FBSize,0,0x03FFB000,0x4000,0x404);
		//NumberOfBytes,LowestAcceptableAddress,HighestAcceptableAddress,Alignment OPTIONAL,ProtectionType

	pb_DepthStencilAddr=DSAddr;
	if (!DSAddr) 
	{
		pb_kill();
		return -11;
	}

	pb_DSAddr=DSAddr;

	pb_assign_tile(	1,				//int	tile_index,
			pb_DepthStencilAddr&0x03FFFFFF,	//DWORD	tile_addr,
			DSSize,				//DWORD	tile_size,
			Pitch,				//DWORD	tile_pitch,
			0,				//DWORD	tile_z_start_tag,
			0,				//DWORD	tile_z_offset,
			0x84000001			//DWORD	tile_flags (0x04000000 for 32 bits)
			);


	if (pb_ExtraBuffersCount)
	{
		//Extra back buffers (tile #2)
	
		//pitch is the gap between start of a pixel line and start of next pixel line
		//(not necessarily the size of a pixel line, because of hardware optimization)

		Pitch=(((vm.bpp*HSize)>>3)+0x3F)&0xFFFFFFC0; //64 units aligned

		//look for a standard listed pitch value greater or equal to theoretical one
		for(i=0;i<16;i++)
		{
			if (pb_TilePitches[i]>=Pitch)
			{
				Pitch=pb_TilePitches[i];
				break;
			}	
		}

		Size=Pitch*VSize;

		//verify 64 bytes alignment for size of a frame buffer
		if (Size&(64-1)) debugPrint("pb_init: EXSize is not well aligned.\n");

		//multiply size by number of physical frame buffers in order to obtain global size
		EXSize=Size*pb_ExtraBuffersCount;

		//Huge alignment enforcement (16 Kb aligned!) for the global size
		EXSize=(EXSize+0x3FFF)&0xFFFFC000;

		EXAddr=(DWORD)MmAllocateContiguousMemoryEx(EXSize,0,0x03FFB000,0x4000,0x404);
		//NumberOfBytes,LowestAcceptableAddress,HighestAcceptableAddress,Alignment OPTIONAL,ProtectionType

		if (!EXAddr) 
		{
			pb_kill();
			return -11;
		}	

		for(i=0;i<pb_ExtraBuffersCount;i++)
		{	
			pb_EXAddr[i]=EXAddr;
			EXAddr+=Size;
		}

		pb_assign_tile(	2,				//int	tile_index,
				pb_EXAddr[0]&0x03FFFFFF,	//DWORD	tile_addr,
				EXSize,				//DWORD	tile_size,
				Pitch,				//DWORD	tile_pitch,
				0,				//DWORD	tile_z_start_tag,
				0,				//DWORD	tile_z_offset,
				0				//DWORD	tile_flags
			);

	}

	pb_FBVFlag=0x0000; //Quincunx & Gaussian need special flags. We don't, for now.
	pb_XScale=(float)HScale;
	pb_YScale=(float)VScale;
	if (pb_YScale<pb_XScale) pb_GlobalScale=pb_YScale; else pb_GlobalScale=pb_XScale;

	i=(DWORD)(2.0f*(pb_GlobalScale)+0.5f);
	switch(i)
	{
		case 0:
			pb_Bias=-8.0f;
			break;
		case 1:
			pb_Bias=0.53125f;
			break;
		case 2: //0.0f
		case 3:	//0.585f
		case 4: //1.0f
		case 5:	//1.322f
		case 6:	//1.585f
		case 7:	//1.907f
		case 8:	//2.0f
			pb_Bias=pb_BiasTable[i-2];
			break;
	}

	p=pb_begin();
	n=pb_FrameBuffersCount; //(BackBufferCount+1)
	pb_push3(p,NV20_TCL_PRIMITIVE_3D_MAIN_TILES_INDICES,0,1,n); p+=4;
	pb_end(p);

	//set area where GPU is allowed to draw pixels
	pb_set_viewport(0,0,vm.width*HScale,vm.height*VScale,0.0f,1.0f);

	//set vertex shader type
	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_SHADER_TYPE,SHADER_TYPE_INTERNAL); p+=2;
	pb_end(p);

	//no scissors (accept pixels in 8 rectangles covering all screen)
	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_CLIP_MODE,0); p+=2;	//accept pixels inside scissor rectangles union (1=reject)
	for(i=0;i<8;i++)
	{
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_CLIP_HORIZ(i),0|((vm.width*HScale-1)<<16)); p+=2;
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_VIEWPORT_CLIP_VERT(i),0|((vm.height*VScale-1)<<16)); p+=2;
	}
	pb_end(p);

	//funcs: never(0x200), less(0x201), equal(0x202), less or equal(0x203)
	//greater(0x204), not equal(0x205), greater or equal(0x206), always(0x207)

	//various intial settings (simple states)
	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_DEPTH_FUNC,0x203); p+=2; //Depth comparison function="less or equal"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_ALPHA_FUNC_FUNC,0x207); p+=2; //Alpha comparison function="always"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_ENABLE,0); p+=2; //AlphaBlendEnable=FALSE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_ALPHA_FUNC_ENABLE,0); p+=2; //AlphaTestEnable=FALSE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_ALPHA_FUNC_REF,0); p+=2; //AlphaRef=0 
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_SRC,1); p+=2; //SrcBlend=(1,1,1,1)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BLEND_FUNC_DST,0); p+=2; //DstBlend=(0,0,0,0) 
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_DEPTH_WRITE_ENABLE,1); p+=2; //ZWriteEnable=TRUE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_DITHER_ENABLE,0); p+=2; //DitherEnable=FALSE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_SHADE_MODEL,0x1D01); p+=2; //ShadeMode="gouraud"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_COLOR_MASK,0x01010101); p+=2; // ColorWriteEnable=abgr
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_OP_ZFAIL,0x1E00); p+=2; //StencilZFail="keep"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_OP_ZPASS,0x1E00); p+=2; //StencilPass="keep"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_FUNC_FUNC,0x207); p+=2; // Stencil comparison function="always"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_FUNC_REF,0); p+=2; //StencilRef=0
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_FUNC_MASK,0xFFFFFFFF); p+=2; //StencilMask=0xFFFFFFFF
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_MASK,0xFFFFFFFF); p+=2; //StencilWriteMask=0xFFFFFFFF
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BLEND_EQUATION,0x8006); p+=2; //Blend operator="add"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_BLEND_COLOR,0); p+=2; //BlendColor=0x000000 
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_SWATHWIDTH,4); p+=2; //SwathWidth=128 
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_POLYGON_OFFSET_FACTOR,0); p+=2; //PolygonOffZSlopeScale=0.0f (because ZBias=0.0f)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_POLYGON_OFFSET_UNITS,0); p+=2; //PolygonOffZOffset=0.0f (because ZBias=0.0f)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_POLYGON_OFFSET_POINT_ENABLE,0); p+=2; //PtOffEnable=FALSE (because ZBias=0.0f)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_POLYGON_OFFSET_LINE_ENABLE,0); p+=2; //WireFrameOffEnable=FALSE (because ZBias=0.0f)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_POLYGON_OFFSET_FILL_ENABLE,0); p+=2; //SolidOffEnable=FALSE (because ZBias=0.0f)
	pb_end(p);

	//various intial settings (complex states)
	p=pb_begin();
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_VERTEX_BLEND_ENABLE,0); p+=2; //VertexBlend="disable"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FOG_COLOR,0); p+=2; //FogColor=0x000000
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_POLYGON_MODE_FRONT,0x1B02,0x1B02); p+=3; //FillMode="solid" BackFillMode="point"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_NORMALIZE_ENABLE,0); p+=2; //NormalizeNormals=FALSE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_STENCIL_OP_FAIL,0x1E00); p+=2; //StencilFail="keep"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FRONT_FACE,0x900); p+=2; //FrontFace="clockwise"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CULL_FACE_ENABLE,1); p+=2;//CullModeEnable=TRUE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CULL_FACE,0x405); p+=2; //CullMode="FrontFace opposite" (counterclockwise)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_COLOR_LOGIC_OP_ENABLE,0); p+=2; //Logic operator="none"
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_LINE_SMOOTH_ENABLE,0,0); p+=3; //EdgeAntiAlias=0
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_MULTISAMPLE,0xFFFF0001); p+=2; //MultiSampleAntiAliasing=TRUE & MultiSampleMask=0xFFFF
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_SHADOW_FUNC_FUNC,0); p+=2; //Shadow comparison function="never"
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_LINE_WIDTH,(DWORD)(1.0f*8.0f*pb_GlobalScale+0.5f)); p+=2; //LineWidth=1.0f =>8 (0-511)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2; //prepare subprogram call (wait/makespace, will obtain null status)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,1); p+=2; //set parameter for subprogram (TRUE)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETNOISE); p+=2; //call subprogID PB_SETNOISE: Dxt1NoiseEnable=TRUE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_CULL_ENABLE,3); p+=2; //bit0:OcclusionCullEnable=TRUE & bit1:StencilCullEnable=TRUE
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_WAIT_MAKESPACE,0); p+=2; //prepare subprogram call (wait/makespace, will obtain null status)
	pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PGRAPH_DEBUG_5,NV_PGRAPH_DEBUG_5_ZCULL_SPARE2_ENABLED); p+=3; //set parameters A & B: DoNotCullUncompressed=FALSE (|8 otherwise)
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(ParamA)=ParamB
	if (VIDEOREG(NV_PBUS_ROM_VERSION)&NV_PBUS_ROM_VERSION_MASK)
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PGRAPH_UNKNOWN_400B80,(0x45EAD10F&~0x18100000)); //RopZCmpAlwaysRead=FALSE (bit27) & RopZRead=FALSE (bit20)
	else
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_PARAMETER_A,NV_PGRAPH_UNKNOWN_400B80,(0x45EAD10E&~0x18100000));
	p+=3;
	pb_push1(p,NV20_TCL_PRIMITIVE_3D_FIRE_INTERRUPT,PB_SETOUTER); p+=2; //calls subprogID PB_SETOUTER: does VIDEOREG(ParamA)=ParamB
	pb_end(p);


	//various intial settings (texture stages states)
	p=pb_begin();
	pb_push1(p,0x1b68,0); p+=2; //texture stage 1 BumpEnvMat00=0.0f (stage +1 because no pixel shader used yet)
	pb_push1(p,0x1b6c,0); p+=2; //texture stage 1 BumpEnvMat01=0.0f
	pb_push1(p,0x1b70,0); p+=2;//texture stage 1 BumpEnvMat11=0.0f
	pb_push1(p,0x1b74,0); p+=2; //texture stage 1 BumpEnvMat10=0.0f
	pb_push1(p,0x1b78,0); p+=2; //texture stage 1 BumpEnvMatLightScale=0.0f
	pb_push1(p,0x1b7c,0); p+=2; //texture stage 1 BumpEnvMatLightOffset=0.0f
	pb_push3(p,0x03c0,0,0,0); p+=4; //texture stages 0 TexCoordIndex="passthru"
	pb_push1(p,0x1b24,0); p+=2; //texture stage 0 BorderColor=0x000000
	pb_push1(p,0x0ae0,0); p+=2; //texture stage 0 ColorKeyColor=0x000000
	pb_push1(p,0x1ba8,0); p+=2; //texture stage 2 BumpEnvMat00=0.0f (stage +1 because no pixel shader used yet)
	pb_push1(p,0x1bac,0); p+=2; //texture stage 2 BumpEnvMat01=0.0f
	pb_push1(p,0x1bb0,0); p+=2;//texture stage 2 BumpEnvMat11=0.0f
	pb_push1(p,0x1bb4,0); p+=2; //texture stage 2 BumpEnvMat10=0.0f
	pb_push1(p,0x1bb8,0); p+=2; //texture stage 2 BumpEnvMatLightScale=0.0f
	pb_push1(p,0x1bbc,0); p+=2; //texture stage 2 BumpEnvMatLightOffset=0.0f
	pb_push3(p,0x03d0,0,0,0); p+=4; //texture stages 1 TexCoordIndex="passthru"
	pb_push1(p,0x1b64,0); p+=2; //texture stage 1 BorderColor=0x000000
	pb_push1(p,0x0ae4,0); p+=2; //texture stage 1 ColorKeyColor=0x000000
	pb_push1(p,0x1be8,0); p+=2; //texture stage 3 BumpEnvMat00=0.0f (stage +1 because no pixel shader used yet)
	pb_push1(p,0x1bec,0); p+=2; //texture stage 3 BumpEnvMat01=0.0f
	pb_push1(p,0x1bf0,0); p+=2;//texture stage 3 BumpEnvMat11=0.0f
	pb_push1(p,0x1bf4,0); p+=2; //texture stage 3 BumpEnvMat10=0.0f
	pb_push1(p,0x1bf8,0); p+=2; //texture stage 3 BumpEnvMatLightScale=0.0f
	pb_push1(p,0x1bfc,0); p+=2; //texture stage 3 BumpEnvMatLightOffset=0.0f
	pb_push3(p,0x03e0,0,0,0); p+=4; //texture stages 2 TexCoordIndex="passthru"
	pb_push1(p,0x1ba4,0); p+=2; //texture stage 2 BorderColor=0x000000
	pb_push1(p,0x0ae8,0); p+=2; //texture stage 2 ColorKeyColor=0x000000
	pb_push3(p,0x03f0,0,0,0); p+=4; //texture stages 3 TexCoordIndex="passthru"
	pb_push1(p,0x1be4,0); p+=2; //texture stage 3 BorderColor=0x000000
	pb_push1(p,0x0aec,0); p+=2; //texture stage 3 ColorKeyColor=0x000000
	pb_end(p);

	memset((DWORD *)pb_FBAddr[0],0,pb_FBSize);
	memset((DWORD *)pb_DSAddr,0,pb_DSSize);

	pb_back_index=1;		//frame buffer #1 is the back buffer for now
	pb_target_back_buffer();	//tells GPU what is the frame buffer target

	pb_front_index=0;		//frame buffer #0 is the front buffer for now
	pb_show_front_screen();		//show it

	return 0;
}


//enqueues shaders micro-code into push buffer stream
//(not recommended for pixel shader: slow and redundant)
DWORD *pb_push_mcode(DWORD *p,DWORD *mcode)
{
	DWORD		size;

	if (((*mcode)&0xFFFF0000)!=0x43210000) //pixel shader registers values
	{
		//Pixel shader initialization (on xbox it's just registers initialization)
		//1-8 stages where (alpha and rgb processed in parallel)
		//2x4 inputs redirected to (a,b,c,d) can produce 2x3 outputs (a*b,c*d or a*b+c*d) 
		//redirected to v0-v1, t0-t3, or r0-r1 (r0=final result at final stage)
		pb_push2(p,NV20_TCL_PRIMITIVE_3D_RC_COLOR0,pb_gpu_registers[48],pb_gpu_registers[49]); p+=3; //PSFinalCombinerC0 & C1
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_SHADER_CULL_MODE,pb_gpu_registers[50]); p+=2; //PSCompareMode (0 means fragment killed if r<0 or s<0 or t<0 or q<0, used in clipplane mode)
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_SHADER_OP,pb_gpu_registers[51]); p+=2; //PSTextureModes=1 (1<<(stage*5) is project 2D: argb=texture(r/q,s/q) usually q=1.0f)
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_SHADER_DOTMAPPING,pb_gpu_registers[52]); p+=2; //PSDotMapping (0 means [0,255]argb from texture=>[0.0,1.0](r,g,b))
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_TX_SHADER_PREVIOUS,pb_gpu_registers[53]); p+=2; //PSInputTextureSource (usual value for 4 stages: 0x00210000, what previous stage each stage uses)
		pb_push1(p,NV20_TCL_PRIMITIVE_3D_RC_ENABLE,pb_gpu_registers[54]); p+=2; //PSCombinerCount (stages usage count=1, r0.a LSB controls mux, C0's & C1's may be different)
		pb_push(p++,NV20_TCL_PRIMITIVE_3D_RC_IN_ALPHA(0),8); memcpy(p,&pb_gpu_registers[0],8*4); p+=8;    //8 PSAlphaInputs
		//Inputs: 8x 0xaabbccdd 
		//0=0 1=c0 2=c1 3=fog.rgb 4=v0 5=v1 8=t0 0xb=t3 0xc=r0 0xd=r1 0x10=x.a default=|0.rgb| 
		//0x20=1-|x| 0x40=2*max(0,x)-1("_bx2") 0x60=1-2*max(0,x) 0x80=max(0,x)-0.5f("_bias") 0xa0=0.5f-max(0,x) 0xc0=x 0xf0=-x
		pb_push(p++,NV20_TCL_PRIMITIVE_3D_RC_OUT_ALPHA(0),8); memcpy(p,&pb_gpu_registers[8],8*4); p+=8;  //8 PSAlphaOutputs
		pb_push(p++,NV20_TCL_PRIMITIVE_3D_RC_IN_RGB(0),8); memcpy(p,&pb_gpu_registers[16],8*4); p+=8;  //8 PSRGBInputs
		pb_push(p++,NV20_TCL_PRIMITIVE_3D_RC_OUT_RGB(0),8); memcpy(p,&pb_gpu_registers[24],8*4); p+=8;  //8 PSRGBOutputs
		//Outputs: 8x 0xFlags+<> <:a*b dest >:c*d dest +:a*b+c*d dest with 0xc=r0 0=discared, i.e no destination
		//Flags: 2(ab)/1(cd)="* is replaced with dot product", 4="+ is replaced with (r0.a LSB or MSB not set)?(a*b):(c*d)"
		//Flags: 8=-0.5f (then) 0x10=*2.0f 0x20=*4.0f 0x40=*0.5f
		//Flags: 0x80(ab)/0x40(cd)=result.b propagates to result.a on rgb side (case of dp3 r0,?n,?n for example)
		pb_push(p++,NV20_TCL_PRIMITIVE_3D_RC_CONSTANT_COLOR0(0),16); memcpy(p,&pb_gpu_registers[32],16*4); p+=16; //8 C0's 8 C1's
		return p;
	}
		
	//enqueues a vertex shader setup:
	size=(*(mcode++))&0xFFFF;
	if (size>136*5+96*7+8)
	{
		debugPrint("pb_push_mcode: Wrong vertex shader size\n");
		return NULL;
	}

	memcpy(p,mcode,size*4); p+=size;

	return p;
}

//converts pseudo-code register into encoded xbox gpu pixel shader input register
static int pb_preg2psreg(struct s_PseudoReg *pReg)
{
	int reg=0xc; //r0

	switch(pReg->reg) 
	{
		case 8: reg=0xc+pReg->num; break; //r0-r1 (side effect: r2=0(0) r3=fog.rgb r4=v0 r5=v1 r6=v1r0sum(0xe) r7=EFprod(0xf))
		case 9: reg=4+pReg->num; break; //v0-v1 (side effect: v2=v1r0sum(0xe) v3=EFprod(0xf) v4=c0 v5=c1 v6=0 v7=0)
		case 0xa: reg=1+pReg->num; //c0-c1 (ps constants Cn are 0xaarrggbb dwords)
		//Pseudo code created by psa.exe allows to define C0-C7 but
		//NVidia pixel shaders only refers to C0-C1, but they may be different
		//at each stage. So there is not only one way to map them.
		//Since this function supports only 1 stage, we use only c0-c1 (c2-c3 for 2nd stage, later, eventually)
		//thus, we can choose to have c4-c7 match non standard xbox gpu specific registers at any stage
		if (pReg->num==4) reg=0; 	//c4=zero
		if (pReg->num==5) reg=3; 	//c5=fog.rgb
		if (pReg->num==6) reg=0xe;	//c6=v1r0sum
		if (pReg->num==7) reg=0xf;	//c7=EFprod (see final combiner comment below)
		break;
		case 0xb: reg=8+pReg->num; break; //t0-t3
	}
	switch(pReg->mod)
	{
		case 0: reg|=0xc0; break; //x
		case 1: reg|=0xe0; break; //-x
		case 2: reg|=0x80; break; //x_bias (x-0.5f)
		case 3: reg|=0xa0; break; //-x_bias -(x-0.5f)
		case 4: reg|=0x40; break; //x_bx2 (|x|*2.0f-1.0f)
		case 5: reg|=0x60; break; //-x_bx2 -(|x|*2.0f-1.0f)
		case 6: reg|=0x20; break; //1-|x| (0x00=|x|)
		case 7: debugPrint("pb_preg2psreg: ?n_x2 modifier is not supported\n"); break; //x_x2 (|x|*2) is not supported
		default: debugPrint("pb_preg2psreg: Unrecognized modifier %d\n",pReg->mod); break;
	}
	return reg;
}

//reads data from pseudo-code stream and fills in structure
static void pb_read_pregs(DWORD *pcode, struct s_PseudoRegs *pRegs, int n)
{
	DWORD			code;
	struct	s_PseudoReg	*pReg;

	pRegs->n=n;

	if (n>=1) //dest
	{
		code=*(pcode++);
		pReg=&pRegs->dest;		//ps: 8=r 9=v 0xa=c 0xb=t
		pReg->reg=(code>>28)&0xf;	//vs: 8=r 0xa=c 0xb=a 0xc=oP(oP0=oPos oP1=oFog oP2=oPts) 0xd=oD 0xe=oT
		pReg->num=(code>> 0)&0xf;
		pReg->msk=(code>>16)&0xf;	//bit0=x/r bit1=y/g bit2=z/b bit3=w/a (need to reverse order for xbox gpu)
		pReg->msk=((pReg->msk&8)>>3)|((pReg->msk&4)>>1)|((pReg->msk&2)<<1)|((pReg->msk&1)<<3);
		if (pReg->reg==8) pb_tmp_registers[pReg->num]=1; //markup for actually used temporary registers
	}
	if (n>=2) //src0
	{
		code=*(pcode++);
		pReg=&pRegs->src0;		//ps: 8=r 9=v 0xa=c 0xb=t
		pReg->reg=(code>>28)&0xf;	//vs: 8=r 9=v 0xa=c 0xb=a
		pReg->num=(code>> 0)&0xf;
		pReg->mod=(code>>24)&0xf;	//0=x 1=-x (ps: 2=x_bias 3=-x_bias 4=x_bx2 5=-x_bx2 6=1-x 7=x_x2(not supported))
		pReg->swz=(code>>16)&0xff;	//.p0p1p2p3=>p3p2p1p0 with 00=x/r 01=y/g 10=z/b 11=w/a (need to reverse order for xbox gpu)
		pReg->swz=((pReg->swz&0xc0)>>6)|((pReg->swz&0x30)>>2)|((pReg->swz&0xc)<<2)|((pReg->swz&3)<<6);
		pReg->idx=(code>>13)&1;	//vs: if set, means cn to be replaced with c[a0.x+n]
	}
	if (n>=3) //src1
	{
		code=*(pcode++);
		pReg=&pRegs->src1;		//ps: 8=r 9=v 0xa=c 0xb=t
		pReg->reg=(code>>28)&0xf;	//vs: 8=r 9=v 0xa=c 0xb=a
		pReg->num=(code>> 0)&0xf;
		pReg->mod=(code>>24)&0xf;	//0=x 1=-x (ps: 2=x_bias 3=-x_bias 4=x_bx2 5=-x_bx2 6=1-x 7=x_x2(not supported))
		pReg->swz=(code>>16)&0xff;	//.p0p1p2p3=>p3p2p1p0 with 00=x/r 01=y/g 10=z/b 11=w/a (need to reverse order for xbox gpu)
		pReg->swz=((pReg->swz&0xc0)>>6)|((pReg->swz&0x30)>>2)|((pReg->swz&0xc)<<2)|((pReg->swz&3)<<6);
		pReg->idx=(code>>13)&1;	//vs: if set, means cn to be replaced with c[a0.x+n]
	}
	if (n>=4) //src2
	{
		code=*(pcode++);
		pReg=&pRegs->src2;		//ps: 8=r 9=v 0xa=c 0xb=t
		pReg->reg=(code>>28)&0xf;	//vs: 8=r 9=v 0xa=c 0xb=a
		pReg->num=(code>> 0)&0xf;
		pReg->mod=(code>>24)&0xf;	//0=x 1=-x (ps: 2=x_bias 3=-x_bias 4=x_bx2 5=-x_bx2 6=1-x 7=x_x2(not supported))
		pReg->swz=(code>>16)&0xff;	//.p0p1p2p3=>p3p2p1p0 with 00=x/r 01=y/g 10=z/b 11=w/a (need to reverse order for xbox gpu)
		pReg->swz=((pReg->swz&0xc0)>>6)|((pReg->swz&0x30)>>2)|((pReg->swz&0xc)<<2)|((pReg->swz&3)<<6);
		pReg->idx=(code>>13)&1;	//vs: if set, means cn to be replaced with c[a0.x+n]
	}
}					

//sets usual parts of vertex shader micro-code (instruction independant parts)
static int pb_set_mcode(DWORD *p,struct s_PseudoRegs *pRegs)
{
//xbox gpu micro-code format:
//renouveau constants:
//|       |       |       |       |       |       |       |       | DWORD#0 (0)
//|     |scalar#|vector#|(0-95)const_src|inp_src|  source0_high   | DWORD#1
//|source0_low|         source1             |    source2_high     | DWORD#2
//|src2low|vtmpmsk|temp_id|stmpmsk|destmsk|x|  (const) dest |p|i| | DWORD#3
//'x' bit allows to choose a constant as destination. 
//Shader must be declared with a special type previously
//in order to get this priviledge and runs much slower.
//x=1 : destination is not a constant register
//x=0 : destination is a constant register (4 bits dest field becomes 8 bits const dest field)

//The way I describe things (using c,v,r characters):
//|       |       |       |       |       |       |       |       | DWORD#0 (0)
//|     |sc_code|op_code|(0-191) c_numbr|v_numbr|m|source0_swizzle| DWORD#1 (96=>C0 on xbox)
//|r_numbr|cvr|m|source1_swizzle|r_numbr|cvr|m|source2_swizzle|r_n  DWORD#2
//r? dest:
//umbr|cvr|dst_msk|r_numbr|sdstmsk|0 0 0 0|1|1 1 1 1 1 1 1 1|0|i| | DWORD#3
//o? dest: (o0=oPos o1-2=oT6-7(n/a) o3-4=oD0-1(ff) o5=oFog o6=oPts o7-8=oT4-5(bf) o9-12=oT0-3)
//umbr|cvr|0 0 0 0|0 1 1 1|0 0 0 0|dst_msk|1|0 0 0 0|o_numbr|s|i| | DWORD#3
//c? dest: (shaders that can write into constants run slower and have special type)
//umbr|cvr|0 0 0 0|0 1 1 1|0 0 0 0|dst_msk|0|(0-191) c_numbr|s|i| | DWORD#3 (96=>C0 on xbox)
//a0 dest: (only allowed in instruction mov a0.x,...)
//|   |cvr|0 0 0 0|0 1 1 1|0 0 0 0|0 0 0 0|1 1 1 1 1 1 1 1 1|0|i| | DWORD#3
//i: 0=cn 1=c[a0.x+n] (if any constant is used as any of the sources)
//s: set if scalar function result is expected in destination
//no c: c_numbr=0
//no v: v_numbr=0
//m: 0=x 1=-x
//cvr: (can't set more than 1 c and more than 1 v as src)
//01=r
//10=v
//11=c
//missing src: m=0(x) swizzle=00011011(.xyzw) r_numbr=0(0) cvr=10(v)

	DWORD src0,src1,src2;

	*(p+0)=NV20_VP_INST0_KNOWN; //always 0
	*(p+1)=0;
	*(p+2)=0;
	*(p+3)=0;

	if (pRegs->n<2) //it's a nop
	{	//src0, src1 & src2 are missing (set them to v0.xyzw)
		*(p+1)|=0x1b;
		*(p+2)|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT)<<NV20_VP_INST_SRC0L_SHIFT;
		*(p+2)|=((0x1b<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT)|(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT))<<NV20_VP_INST_SRC1_SHIFT;
		*(p+2)|=((0x1b<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT)>>NV20_VP_SRC2_HIGH_SHIFT)<<NV20_VP_INST_SRC2H_SHIFT;
		*(p+3)|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT)<<NV20_VP_INST_SRC2L_SHIFT;
		*(p+3)|=0x00700ff8;
		return 0;
	}
	
	switch(pRegs->dest.reg) //8=r 0xa=c 0xb=a 0xc=oP(oP0=oPos oP1=oFog oP2=oPts) 0xd=oD 0xe=oT
	{
		case 8  : *(p+3)|=0x00000ff8|(pRegs->dest.msk<<NV20_VP_INST_VTEMP_WRITEMASK_SHIFT)|(pRegs->dest.num<<NV20_VP_INST_DEST_TEMP_ID_SHIFT); break; //r (dest=255 NV20_VP_INST_CONST_DEST_FLAG set)
		case 0xa: *(p+3)|=0x00700000|(pRegs->dest.msk<<NV20_VP_INST_DEST_WRITEMASK_SHIFT)|(pRegs->dest.num<<NV20_VP_INST_CONST_DEST_SHIFT); break; //c (shaders that can write into constants run slower, NV20_VP_INST_CONST_DEST_FLAG cleared)
		case 0xb: *(p+3)|=0x00700ff8; break; //dest a0 (mask is zero in micro-code but is considered as .x) (only valid for "mov a0.x,...") (r_dest=7 dest=255 NV20_VP_INST_CONST_DEST_FLAG set)
		case 0xc: *(p+3)|=0x00700800|(pRegs->dest.msk<<NV20_VP_INST_DEST_WRITEMASK_SHIFT)|((pRegs->dest.num?(pRegs->dest.num==1?NV20_VP_INST_DEST_FOG:NV20_VP_INST_DEST_PTS):NV20_VP_INST_DEST_POS)<<NV20_VP_INST_DEST_SHIFT);break; //o(oP0=oPos=o0 oP1=oFog=o5 oP2=oPts=o6) (r_dest=7 NV20_VP_INST_CONST_DEST_FLAG set)
		case 0xd: *(p+3)|=0x00700800|(pRegs->dest.msk<<NV20_VP_INST_DEST_WRITEMASK_SHIFT)|((pRegs->dest.num?NV20_VP_INST_DEST_COL1:NV20_VP_INST_DEST_COL0)<<NV20_VP_INST_DEST_SHIFT);break; //o(oD0-1=o3-4(front faces)) (r_dest=7 NV20_VP_INST_CONST_DEST_FLAG set)
		case 0xe: *(p+3)|=0x00700800|(pRegs->dest.msk<<NV20_VP_INST_DEST_WRITEMASK_SHIFT)|(((pRegs->dest.num<4)?NV20_VP_INST_DEST_TC(pRegs->dest.num):((pRegs->dest.num<6)?pRegs->dest.num+3:pRegs->dest.num-5))<<NV20_VP_INST_DEST_SHIFT); break; //o(oT0-3=o9-12 oT4-5=o7-8(bf) oT6-7=o1-2(n/a)) (r_dest=7 NV20_VP_INST_CONST_DEST_FLAG set)
		//(on xbox, oT4-5 act as oD0-1 for back faces, oT6-7 do not exist, and r12 is an alias for oPos)
		default : debugPrint("Unrecognized destination register\n"); return -1; break; 
	}
	
	src0=(pRegs->src0.mod*NV20_VP_SRC_REG_NEGATE)|(pRegs->src0.swz<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT);
	switch(pRegs->src0.reg) //8=r 9=v 0xa=c 0xb=a
	{
		case 8  : src0|=(NV20_VP_SRC_REG_TYPE_TEMP<<NV20_VP_SRC_REG_TYPE_SHIFT)|(pRegs->src0.num<<NV20_VP_SRC_REG_TEMP_ID_SHIFT); break; //r
		case 9  : src0|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT); *(p+1)|=(pRegs->src0.num<<NV20_VP_INST_INPUT_SRC_SHIFT); break; //v
		case 0xa: src0|=(NV20_VP_SRC_REG_TYPE_CONST<<NV20_VP_SRC_REG_TYPE_SHIFT); *(p+1)|=((pRegs->src0.num+96)<<NV20_VP_INST_CONST_SRC_SHIFT); break; //c
		default : debugPrint("Unrecognized src0 register\n"); return -2; break;
	}
	*(p+1)|=((src0&NV20_VP_SRC0_HIGH_MASK)>>NV20_VP_SRC0_HIGH_SHIFT)<<NV20_VP_INST_SRC0H_SHIFT;
	*(p+2)|=(src0&NV20_VP_SRC0_LOW_MASK)<<NV20_VP_INST_SRC0L_SHIFT;
	*(p+3)|=pRegs->src0.idx*NV20_VP_INST_INDEX_CONST;
	
	if (pRegs->n==2)
	{	//src1 & src2 are missing (set them to v0.xyzw)
		*(p+2)|=((0x1b<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT)|(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT))<<NV20_VP_INST_SRC1_SHIFT;
		*(p+2)|=((0x1b<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT)>>NV20_VP_SRC2_HIGH_SHIFT)<<NV20_VP_INST_SRC2H_SHIFT;
		*(p+3)|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT)<<NV20_VP_INST_SRC2L_SHIFT;
		return 0;
	}

	src1=(pRegs->src1.mod*NV20_VP_SRC_REG_NEGATE)|(pRegs->src1.swz<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT);
	switch(pRegs->src1.reg) //8=r 9=v 0xa=c 0xb=a
	{
		case 8  : src1|=(NV20_VP_SRC_REG_TYPE_TEMP<<NV20_VP_SRC_REG_TYPE_SHIFT)|(pRegs->src1.num<<NV20_VP_SRC_REG_TEMP_ID_SHIFT); break; //r
		case 9  : src1|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT); *(p+1)|=(pRegs->src1.num<<NV20_VP_INST_INPUT_SRC_SHIFT); break; //v
		case 0xa: src1|=(NV20_VP_SRC_REG_TYPE_CONST<<NV20_VP_SRC_REG_TYPE_SHIFT); *(p+1)|=((pRegs->src1.num+96)<<NV20_VP_INST_CONST_SRC_SHIFT); break; //c
		default : debugPrint("Unrecognized src1 register\n"); return -3; break;
	}
	*(p+2)|=src1<<NV20_VP_INST_SRC1_SHIFT;
	*(p+3)|=pRegs->src1.idx*NV20_VP_INST_INDEX_CONST;

	if (pRegs->n==3)
	{	//src2 is missing (set it to v0.xyzw)
		*(p+2)|=((0x1b<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT)>>NV20_VP_SRC2_HIGH_SHIFT)<<NV20_VP_INST_SRC2H_SHIFT;
		*(p+3)|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT)<<NV20_VP_INST_SRC2L_SHIFT;
		return 0;
	}

	src2=(pRegs->src2.mod*NV20_VP_SRC_REG_NEGATE)|(pRegs->src2.swz<<NV20_VP_SRC_REG_SWZ_ALL_SHIFT);
	switch(pRegs->src2.reg) //8=r 9=v 0xa=c 0xb=a
	{
		case 8  : src2|=(NV20_VP_SRC_REG_TYPE_TEMP<<NV20_VP_SRC_REG_TYPE_SHIFT)|(pRegs->src2.num<<NV20_VP_SRC_REG_TEMP_ID_SHIFT); break; //r
		case 9  : src2|=(NV20_VP_SRC_REG_TYPE_INPUT<<NV20_VP_SRC_REG_TYPE_SHIFT); *(p+1)|=(pRegs->src2.num<<NV20_VP_INST_INPUT_SRC_SHIFT); break; //v
		case 0xa: src2|=(NV20_VP_SRC_REG_TYPE_CONST<<NV20_VP_SRC_REG_TYPE_SHIFT); *(p+1)|=((pRegs->src2.num+96)<<NV20_VP_INST_CONST_SRC_SHIFT); break; //c
		default : return -4; debugPrint("Unrecognized src2 register\n"); break;
	}
	*(p+2)|=((src2&NV20_VP_SRC2_HIGH_MASK)>>NV20_VP_SRC2_HIGH_SHIFT)<<NV20_VP_INST_SRC2H_SHIFT;
	*(p+3)|=(src2&NV20_VP_SRC2_LOW_MASK)<<NV20_VP_INST_SRC2L_SHIFT;
	*(p+3)|=pRegs->src2.idx*NV20_VP_INST_INDEX_CONST;
	
	return 0;
}

//converts shaders pseudo-code into xbox gpu micro-code
//(not recommended for pixel shader: slow and incomplete)
DWORD *pb_pcode2mcode(const DWORD *pseudocode)
{
	DWORD			*p;
	DWORD			constant;
	DWORD			size;
	DWORD			*pcode;
	int			i,n;
	
	struct	s_PseudoRegs	sRegs;
	
	pcode=(DWORD *)pseudocode;
	
	if (pcode==NULL) 
	{
		debugPrint("pb_pcode2mcode: NULL parameter\n");
		return NULL;
	}

	//pb_tmp_registers will tell us unused registers.
	//this array is updated by pb_read_regs() when tmp registers are detected as destination
	memset(pb_tmp_registers,0,sizeof(pb_tmp_registers));

	if (*pcode==0xffff0101) //ps_1_1
	{
		pcode++;
		//currently supported (not a lot, but manual ps registers setting is possible): 
		//- only 1 stage (1 or 2 instructions to set r0, with or without 1 'tex t0' instruction)
		//- modifier -?n
		//- modifier ?n_bias (-0.5f)
		//- modifier ?n_bx2 (*2.0f)
		//- modifier 1-|?n|
		//- def cn, r, g, b, a
		//- nop
		//- tex t0
		//- mov r0, ?n         (r0=?n)
		//- mul r0, ?n, ?n     (r0=?n*?n)
		//- dp3 r0, ?n, ?n     (r0=?n.?n)
		//- add r0, ?n, ?n     (r0=?n+?n)
		//- sub r0, ?n, ?n     (r0=?n-n)
		//- mad r0, ?n, ?n, ?n (r0=?n*?n+?n)
		//- lrp r0, src0, src1, src2 (r0=src0*src1+(1-src0)*src2)
		//- cnd r0, r0.a, src1, src2 (r0=(r0.a>0.5f)?src1:src2) (if r0.a MSB is used for mux)
		//- coherent destination mask & swizzle (no swizzle or .rgba, .xyzw, .a, .x, .rgb, .xyz for separate rgb/alpha processing)

		p=&pb_gpu_registers[0];
		//It's recommended to learn initializing registers oneself
		//in order to avoid resetting most of this -probably useless- default values
		memset(&pb_gpu_registers[0],0,sizeof(pb_gpu_registers));
		p[0] =0xd4301010; //PSAlphaInput for stage 0: a.a=v0.a b.a=1.a-|0.a|
		p[8] =0x000000c0; //PSAlphaOutput for stage 0: r0.a=a*b
		p[16]=0xc4200000; //PSRGBInput for stage 0: a.rgb=v0.rgb b.rgb=1.rgb-|0.rgb|
		p[24]=0x000000c0; //PSRGBOutput for stage 0: r0.rgb=a*b
		//p[32] //C0's constants
		//p[40] //C1's constants
		//p[48] //final combiner C0 constant
		//p[49] //final combiner C1 constant
		//p[50] //PSCompareMode (used only for texture mode clipplane)
		//p[51] //PSTextureModes (1 is project 2D: argb=texture(r/q,s/q) usually q=1.0f)
		//p[52] //PSDotMapping (0 means [0,255]argb from texture=>[0.0,1.0](r,g,b))
		//p[53] //PSInputTextureSource (most logical value is 0x00210000 when texture stages 2 & 3 are used)
		p[54]=0x11101; //PSCombinerCount ("stages usage count" | "C0 & C1 may be different from stage to stage" | "r0.a MSB used for mux")
		//These default settings do "mov r0,v0"

		//'final combiner' is an additional invisible (free) stage doing this:
		//final pixel.rgb = A * B + (1 - A) * C + D
		//final pixel.alpha = G.b or G.a (.a modifier must be used if you want .a)
		//Also all values are clamped to 0..1 (negative values become zero)

		//Inner registers NV20_TCL_PRIMITIVE_3D_RC_FINAL0 and following one
		//define inputs and modifiers for the 7 parameters A,B,C,D and E,F,G,? (?=0x80, unknown)
		//Here are a few useful values depending what you want to do:
		//fog on  & specular on  : 0x130e0300,0x00001c80 (means pixel.rgb=fog.a * (r0.rgb + v1.rgb) + (1 - fog.a) * fog.rgb & pixel.a=r0.a)
		//fog on  & specular off : 0x130c0300,0x00001c80 (means pixel.rgb=fog.a * r0.rgb + (1 - fog.a) * fog.rgb & pixel.a=r0.a)
		//fog off & specular on  : 0x0000000e,0x00001c80 (means pixel.rgb=r0.rgb + v1.rgb & pixel.a=r0.a)
		//fog off & specular off : 0x0000000c,0x00001c80 (means D=r0.rgb & G=r0.a, so final pixel.rgb=r0.rgb & pixel.a=r0.a)
		
		//These special read-only registers are also available at final combiner stage (maybe also at any stage?):
		//zero    = 0       (0x0 is the numeric code for this register, modifier is bits 7-4, mapped to C4)
		//fog     = fog     (0x3, fog.rgb returns the fog color inner register value, mapped to pseudocode C5 -fog.a is fog transparency, coming from fog table, I guess-)
		//v1r0sum = r0 + v1 (0xe, I've mapped it to pseudocode C6 in pcode2mcode, useful when specular v1 is to be used)
		//EFprod  = E * F   (0xf, I've mapped it to pseudocode C7 in pcode2mcode, useful for pixel shader optimization, i.e reduce number of stages)

		//Codes for normal registers:
		//C0 => 0x1
		//C1 => 0x2
		//v0 => 0x4
		//v1 => 0x5
		//t0 => 0x8
		//t1 => 0x9
		//t2 => 0xa
		//t3 => 0xb
		//r0 => 0xc
		//r1 => 0xd

		//Modifiers (Or it to code above):
		//default 0x00=|0.rgb| 0x10=x.a
		//0x20=1-|x| 0x40=2*max(0,x)-1("_bx2") 0x60=1-2*max(0,x) 0x80=max(0,x)-0.5f("_bias") 0xa0=0.5f-max(0,x) 0xc0=x 0xf0=-x

		while (*pcode!=0x0000ffff)
		{
			switch(*(pcode++))
			{
				case 0x00000000: //nop
				case 0x40000000: //+nop...
					break;

				case 0x00000001: //mov r0, ?n (r0=?n)
				case 0x40000001: //+mov...
					pb_read_pregs(pcode,&sRegs,2); pcode+=2;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if (sRegs.dest.msk&1) p[0]=0x10301010|(pb_preg2psreg(&sRegs.src0)<<24); //PSAlphaInput for stage 0: a.a=?.a b.a=1-|0.a|
					if ((sRegs.dest.msk&0xe)==0xe) p[16]=0x00200000|(pb_preg2psreg(&sRegs.src0)<<24); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=1.rgb-|0.rgb|
					break;

				case 0x00000002: //add r0, ?n, ?n (r0=?n+?n)
				case 0x40000002: //+add...
					pb_read_pregs(pcode,&sRegs,3); pcode+=3;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if (sRegs.dest.msk&1)
					{
						p[0]=0x10301030|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<8); //PSAlphaInput for stage 0: a.a=?.a b.a=1.a-|0.a| c.a=?.a d=1.a-|0.a|
						p[8]=0x00000c00; //PSAlphaOutput for stage 0: r0.a=a*b+c*d
					}
					if ((sRegs.dest.msk&0xe)==0xe) 
					{
						p[16]=0x00200020|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<8); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=1.rgb-|0.rgb| c.rgb=?.rgb d.rgb=1.rgb-|0.rgb|
						p[24]=0x00000c00; //PSRGBOutput for stage 0: r0.rgb=a*b+c*d
					}
					break;
						
				case 0x00000003: //sub r0, ?n, ?n (r0=?n-?n)
				case 0x40000003: //+sub...
					pb_read_pregs(pcode,&sRegs,3); pcode+=3;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }					
					if (sRegs.src1.mod<6) 
						sRegs.src1.mod^=1; //inverts src1 sign
					else
					{
						debugPrint("pb_pcode2mcode: sub not supported if src1 has 1-|x| modifier\n");
						return NULL;
					}
					if (sRegs.dest.msk&1)
					{
						p[0]=0x10301030|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<8); //PSAlphaInput for stage 0: a.a=?.a b.a=1.a-|0.a| c.a=?.a d=1.a-|0.a|
						p[8]=0x00000c00; //PSAlphaOutput for stage 0: r0.a=a*b+c*d
					}
					if ((sRegs.dest.msk&0xe)==0xe) 
					{
						p[16]=0x00200020|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<8); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=1.rgb-|0.rgb| c.rgb=?.rgb d.rgb=1.rgb-|0.rgb|
						p[24]=0x00000c00; //PSRGBOutput for stage 0: r0.rgb=a*b+c*d
					}
					break;

				case 0x00000004: //mad r0, ?n, ?n, ?n (r0=?n*?n+?n)
				case 0x40000004: //+mad...
					pb_read_pregs(pcode,&sRegs,4); pcode+=4;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if (sRegs.dest.msk&1)
					{
						p[0]=0x10101030|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16)|(pb_preg2psreg(&sRegs.src2)<<8); //PSAlphaInput for stage 0: a.a=?.a b.a=?.a c.a=?.a d.a=1-|0.a|
						p[8]=0x00000c00; //PSAlphaOutput for stage 0: r0.a=a*b+c*d
					}
					if ((sRegs.dest.msk&0xe)==0xe)
					{
						p[16]=0x00000020|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16)|(pb_preg2psreg(&sRegs.src2)<<8); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=?.rgb c.rgb=?.rgb d.rgb=1-|0.rgb|
						p[24]=0x00000c00; //PSRGBOutput for stage 0: r0.rgb=a*b+c*d
					}
					break;
						
				case 0x00000005: //mul r0, ?n, ?n (r0=?n*?n)
				case 0x40000005: //+mul...
					pb_read_pregs(pcode,&sRegs,3); pcode+=3;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if (sRegs.dest.msk&1) p[0]=0x10101010|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16); //PSAlphaInput for stage 0: a.a=?.a b.a=?.a
					if ((sRegs.dest.msk&0xe)==0xe) p[16]=0x00000000|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=?.rgb
					break;

				case 0x00000008: //dp3 r0, ?n, ?n (r0=?n.?n)
				case 0x40000008: //+dp3...
					pb_read_pregs(pcode,&sRegs,3); pcode+=3;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if ((sRegs.dest.msk&0xf)==0xe) //dp3 r0.xyz, ...
					{
						p[16]=0x00000000|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=?.rgb
						p[24]=0x000020c0; //PSRGBOutput for stage 0: r0.rgb=a.b (dot product)
					}
					if ((sRegs.dest.msk&0xf)==0xf) //dp3 r0, ...
					{
						p[0]=0x10101010;
						p[8]=0x00000000; //PSAlphaOutput for stage 0: discarded (we will use the b->a propagate bit on rgb side)
						p[16]=0x00000000|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16); //PSRGBInput for stage 0: a.rgb=?.rgb b.rgb=?.rgb
						p[24]=0x000820c0; //PSRGBOutput for stage 0: r0.rgb=a.b (dot product) (and r0.b propagates to r0.a)
					}
					break;
						
				case 0x00000012: //lrp r0, src0, src1, src2 (r0=src0*src1+(1-src0)*src2)
				case 0x40000012: //+lrp...
					pb_read_pregs(pcode,&sRegs,4); pcode+=4;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if (sRegs.src0.mod) { debugPrint("pb_pcode2mcode(lrp): Unsupported source 0 modifier\n"); return NULL; }
					if (sRegs.dest.msk&1)
					{
						p[0]=0x10101030|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16)|(pb_preg2psreg(&sRegs.src2)<<8)|(pb_preg2psreg(&sRegs.src0)&0xf); //PSAlphaInput for stage 0: a.a=src0.a b.a=src1.a c.a=src2.a d.a=1-|src0.a|
						p[8]=0x00000c00; //PSAlphaOutput for stage 0: r0.a=a*b+c*d
					}
					if ((sRegs.dest.msk&0xe)==0xe)
					{
						p[16]=0x00000020|(pb_preg2psreg(&sRegs.src0)<<24)|(pb_preg2psreg(&sRegs.src1)<<16)|(pb_preg2psreg(&sRegs.src2)<<8)|(pb_preg2psreg(&sRegs.src0)&0xf); //PSRGBInput for stage 0: a.rgb=src0.rgb b.rgb=src1.rgb c.rgb=src2.rgb d.rgb=1-|src0.rgb|
						p[24]=0x00000c00; //PSRGBOutput for stage 0: r0.rgb=a*b+c*d
					}
					break;
					
				case 0x00000042: //tex t0
				case 0x40000042: //+tex...
					//We assume tn has been replaced with texture color
					//because of a previous correct texture stage initialization
					pb_read_pregs(pcode,&sRegs,1); pcode+=1;
					if (sRegs.dest.num) { debugPrint("pb_pcode2mcode: Only 'tex t0' is supported\n"); return NULL; }
					p[51]=0x00000001; //PSTextureModes (1<<(stage*5) is project 2D: argb=texture(r/q,s/q) usually q=1.0f)
					break;

				case 0x00000050: //cnd r0, r0.a, src1, src2 (r0=(r0.a>0.5f)?src1:src2) (if r0.a MSB used for mux)
				case 0x40000050: //+cnd...
					pb_read_pregs(pcode,&sRegs,4); pcode+=4;
					if ((sRegs.dest.reg!=8)||(sRegs.dest.num!=0)) { debugPrint("pb_pcode2mcode: Unsupported destination register\n"); return NULL; }
					if (sRegs.dest.msk&1)
					{
						p[0]=0x10301030|(pb_preg2psreg(&sRegs.src2)<<24)|(pb_preg2psreg(&sRegs.src1)<<8); //PSAlphaInput for stage 0: a.a=src2.a b.a=1-|0.a| c.a=src1.a d.a=1-|0.a|
						p[8]=0x00004c00; //PSAlphaOutput for stage 0: r0.rgb=(r0.a MSB not set)?(a*b):(c*d)=(r0.a<=0.5f)?src2.rgb:src1.rgb
					}
					if ((sRegs.dest.msk&0xe)==0xe)
					{
						p[16]=0x00200020|(pb_preg2psreg(&sRegs.src2)<<24)|(pb_preg2psreg(&sRegs.src1)<<8); //PSRGBInput for stage 0: a.rgb=src2.rgb b.rgb=1.rgb-|0.rgb| c.rgb=src1.rgb d.rgb=1.rgb-|0.rgb|
						p[24]=0x00004c00; //PSRGBOutput for stage 0: r0.rgb=(r0.a MSB not set)?(a*b):(c*d)=(r0.a<=0.5f)?src2.rgb:src1.rgb
					}
					break;

				case 0x00000051: //def cn, r, g, b, a
					pb_read_pregs(pcode,&sRegs,1); pcode+=1;
					//converts 4 floats (r,g,b,a) into 1 dword 0xaarrggbb ([0,1.0f]=>[0,0xff])
					constant=0;
					constant|=((DWORD)(255.0f*(*((float *)(pcode+3)))))<<24;
					constant|=((DWORD)(255.0f*(*((float *)(pcode+0)))))<<16;
					constant|=((DWORD)(255.0f*(*((float *)(pcode+1)))))<<8;
					constant|=((DWORD)(255.0f*(*((float *)(pcode+2)))))<<0;
					//distribute c0=>c0 stage 0, c1=>c1 stage 0, c2=>c0 stage 1, etc...
					p[32+8*(sRegs.dest.num&1)+(sRegs.dest.num>>1)]=constant;
					pcode+=4;
					break;

				default:
					debugPrint("pb_pcode2mcode: Unrecognized ps token #%08x\n",*(pcode-1));
					return NULL;
			}
		}
		return &pb_gpu_registers[0];
	}

	if (*pcode!=0xfffe0101) //vs_1_1
	{
		debugPrint("pb_pcode2mcode: Shader version not supported\n");
		return NULL;
	}
	
	//it's a vertex shader! (vs_1_1 should be entirely supported by code below -report any issue-)
	pcode++;
	
	pb_exp_constflag=0; //in order to not set taylor series exp macro constants up more than once
	pb_log_constflag=0; //in order to not set taylor series log macro constants up more than once
	
	n=0; //instructions counter (can't exceed 136 on xbox)

	p=&pb_gpu_programnc[1]; //push buffer compatible sequence setting up program and constants
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_PROGRAM_START_ID,1); *(p++)=0; //set run address of shader
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_SHADER_TYPE,2); *(p++)=SHADER_TYPE_EXTERNAL; *(p++)=SHADER_SUBTYPE_REGULAR; //set shader vertex type (external shader, regular: not allowed to write into constants -faster-)
	pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_FROM_ID,1); *(p++)=0; //set cursor in order to load data into program area
	
	while(*pcode!=0x0000ffff)
	{
		if (n==136) { debugPrint("pb_pcode2mcode: Too many instructions: max=136 (including expanded macros)\n"); return NULL; }

		switch(*(pcode++))
		{
			//standard pseudo-code:

			case 0x00000000: //nop
			case 0x40000000: //+nop
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,0); pcode+=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_NOP<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000001: //mov dest,src0
			case 0x40000001: //+mov
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4);  n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				if (sRegs.dest.reg==0xb) 
					*(p+1)|=NV20_VP_INST_OPCODE_ARL<<NV20_VP_INST_VEC_OPCODE_SHIFT; //mov a0,...
				else
					*(p+1)|=NV20_VP_INST_OPCODE_MOV<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000002: //add dest,src0,src1
			case 0x40000002: //+add
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				//src2 is used instead of src1 for add
				sRegs.n=4;
				sRegs.src2=sRegs.src1;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_ADD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000003: //sub dest,src0,src1
			case 0x40000003: //+sub
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				sRegs.src1.mod^=1; //inverts src1 sign
				//src2 is used instead of src1 for add
				sRegs.n=4;
				sRegs.src2=sRegs.src1;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_ADD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000004: //mad dest,src0,src1,src2
			case 0x40000004: //+mad
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,4); pcode+=4;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;
				
			case 0x00000005: //mul dest,src0,src1
			case 0x40000005: //+mul
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MUL<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000006: //rcp dest,src0 (scalar 1/x function)
			case 0x40000006: //+rcp
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_RCP<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}			
				p+=4;
				break;

			case 0x00000007: //rsq dest,src0 (scalar 1/sqrt(x) function)
			case 0x40000007: //+rsq
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_RSQ<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}
				p+=4;
				break;

			case 0x00000008: //dp3 dest,src0,src1
			case 0x40000008: //+dp3
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000009: //dp4 dest,src0,src1
			case 0x40000009: //+dp4
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000000a: //min dest,src0,src1
			case 0x4000000a: //+min
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MIN<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000000b: //max dest,src0,src1
			case 0x4000000b: //+max
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAX<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000000c: //slt dest,src0,src1 (set dest=1 if src0<src1)
			case 0x4000000c: //+slt
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_SLT<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000000d: //sge dest,src0,src1 (set dest=1 if src0>=src1)
			case 0x4000000d: //+sge
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_SGE<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000000e: //exp dest,src0 (macro expanding many full precision instructions: slow)
			case 0x4000000e: //+exp
				if (pb_exp_constflag==0) //exp macro constants already set?
				{
					pb_exp_constflag=1;
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_ID,1); *(p++)=94; //set cursor in order to load data into C-2 and C-1 (xbox accepts C-96 up to C-1)
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,4); //Taylor series related coefficients
					*((float *)(p++))=1.0f; 		//C-2.x a
					*((float *)(p++))=-6.93147182e-1; 	//C-2.y b
					*((float *)(p++))=2.40226462e-1; 	//C-2.z c
					*((float *)(p++))=-5.55036440e-2;	//C-2.w d
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,4); 
					*((float *)(p++))=9.61597636e-3; 	//C-1.x e
					*((float *)(p++))=-1.32823968e-3; 	//C-1.y f
					*((float *)(p++))=1.47491097e-4; 	//C-1.z g
					*((float *)(p++))=-1.08635004e-5;	//C-1.w h
				}
				//after a first step x=expp(src0)
				//we will compute ri.w=ax^0+bx^1+cx^2+dx^3+...+hx^7
				//i.e ri.w=x*(x*(x*(x*(x*(x*(x*h+g)+f)+e)+d)+c)+b)+a
				//then exp(x)=x*(1/ri.w)
				//expp ri, src0 (first partial precision calculation & preserve x in ri.x)
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,2); //but don't increment pcode yet (so we can read again dest later)
				//look for unused temp register i
				for(i=0;i<16;i++) if (pb_tmp_registers[i]==0) break;
				if (i==16) { debugPrint("pb_pcode2mcode: exp macro needs 1 temporary register (none left)\n"); return NULL; }
				sRegs.dest.reg=8; //replace dest with ri.x
				sRegs.dest.num=i;
				sRegs.dest.msk=8; //.x
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_EXP<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				//scalar temp dest mask=temp dest mask & temp dest mask=0
				*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
				*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				p+=4;
				//mov ri.w, C-1.w
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.n=2;
				sRegs.dest.msk=1; //.w
				sRegs.src0.reg=0xa; //c
				sRegs.src0.num=-1;
				sRegs.src0.swz=0xff; //.wwww
				sRegs.src0.mod=0;
				sRegs.src0.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MOV<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-1.z (next=x*(previous+constant))
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.n=4;
				sRegs.src0.reg=8; //r
				sRegs.src0.num=i;
				sRegs.src1.reg=8; //r
				sRegs.src1.num=i;
				sRegs.src1.swz=0; //.xxxx
				sRegs.src1.mod=0;
				sRegs.src1.idx=0;
				sRegs.src2.reg=0xa; //c
				sRegs.src2.num=-1;
				sRegs.src2.swz=0xaa; //.zzzz
				sRegs.src2.mod=0;
				sRegs.src2.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-1.y
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0x55; //.yyyy
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-1.x
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0; //.xxxx
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-2.w
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.num=-2;
				sRegs.src2.swz=0xff; //.wwww
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-2.z
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0xaa; //.zzzz
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-2.y
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0x55; //.yyyy
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-2.x
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0; //.xxxx
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//rcp ri.w, ri.w (ri.w=1/ri.w)
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;			
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_RCP<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				//scalar temp dest mask=temp dest mask & temp dest mask=0
				*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
				*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				p+=4;
				//mul dest, ri.w, ri.x
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(exp): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,2); pcode+=2; //read dest again and preserve it
				sRegs.n=3;
				sRegs.src0.reg=8; //r
				sRegs.src0.num=i;
				sRegs.src0.swz=0xff; //.wwww
				sRegs.src0.mod=0;
				sRegs.src0.idx=0;
				sRegs.src1.reg=8; //r
				sRegs.src1.num=i;
				sRegs.src1.swz=0; //.xxxx
				sRegs.src1.mod=0;
				sRegs.src1.idx=0;				
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(exp): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MUL<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000000f: //log dest,src0 (macro expanding many full precision instructions: slow)
			case 0x4000000f: //+log
				if (pb_log_constflag==0) //log macro constants already set?
				{
					pb_log_constflag=1;
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_ID,1); *(p++)=93; //set cursor in order to load data into C-5, C-4 and C-3 (xbox accepts C-96 up to C-1)
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,4); //Taylor series related coefficients
					*((float *)(p++))=1.0f; 		//C-5.x
					*((float *)(p++))=0.0f;
					*((float *)(p++))=0.0f;
					*((float *)(p++))=0.0f;
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,4);
					*((float *)(p++))=1.44268966f;	//C-4.x a
					*((float *)(p++))=-7.21165776e-1; 	//C-4.y b
					*((float *)(p++))=4.78684813e-1; 	//C-4.z c
					*((float *)(p++))=-3.47305417e-1;	//C-4.w d
					pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,4); 
					*((float *)(p++))=2.41873696e-1; 	//C-3.x e
					*((float *)(p++))=-1.37531206e-1; 	//C-3.y f
					*((float *)(p++))=5.20646796e-2; 	//C-3.z g
					*((float *)(p++))=-9.31049418e-3;	//C-3.w h
				}
				//after a first step y=logp(src0)
				//we will compute ri.w=ax^0+bx^1+cx^2+dx^3+...+hx^7
				//i.e ri.w=x*(x*(x*(x*(x*(x*(x*h+g)+f)+e)+d)+c)+b)+a
				//then log(y)=x*ri.w+y (with x=y-1)
				//logp ri.xy, src0 (first partial precision calculation & preserve y in ri.y)
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,2); //but don't increment pcode yet (so we can read again dest later)
				//look for unused temp register i
				for(i=0;i<16;i++) if (pb_tmp_registers[i]==0) break;
				if (i==16) { debugPrint("pb_pcode2mcode: log macro needs 1 temporary register (none left)\n"); return NULL; }
				sRegs.dest.reg=8; //replace dest with ri.x
				sRegs.dest.num=i;
				sRegs.dest.msk=0xc; //.xy
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_LOG<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				//scalar temp dest mask=temp dest mask & temp dest mask=0
				*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
				*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				p+=4;
				//sub ri.x, ri.x, C-5.x (x=y-1)
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.n=3;
				sRegs.dest.msk=8; //.x
				sRegs.src0.reg=8;
				sRegs.src0.num=i;
				sRegs.src0.swz=0; //.xxxx
				sRegs.src0.mod=0;
				sRegs.src0.idx=0;
				//src2 is used instead of src1 for add
				sRegs.n=4;
				sRegs.src2.reg=0xa; //c
				sRegs.src2.num=-5;
				sRegs.src2.swz=0; //.xxxx
				sRegs.src2.mod=1; //-
				sRegs.src2.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;	
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_ADD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mov ri.w, C-3.w
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.n=2;
				sRegs.dest.msk=1; //.w
				sRegs.src0.reg=0xa; //c
				sRegs.src0.num=-3;
				sRegs.src0.swz=0xff; //.wwww
				sRegs.src0.mod=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MOV<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-3.z (next=x*(previous+constant))
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.n=4;
				sRegs.src0.reg=8; //r
				sRegs.src0.num=i;
				sRegs.src1.reg=8; //r
				sRegs.src1.num=i;
				sRegs.src1.swz=0; //.xxxx
				sRegs.src1.mod=0;
				sRegs.src2.reg=0xa; //c
				sRegs.src2.num=-3;
				sRegs.src2.swz=0xaa; //.zzzz
				sRegs.src2.mod=0;
				sRegs.src2.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-3.y
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0x55; //.yyyy
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-3.x
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0; //.xxxx
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-4.w
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.num=-4;
				sRegs.src2.swz=0xff; //.wwww
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-4.z
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0xaa; //.zzzz
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-4.y
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0x55; //.yyyy
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad ri.w, ri.w, ri.x, C-4.x
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.src2.swz=0; //.xxxx
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//mad dest, ri.w, ri.x, ri.y
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(log): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,2); pcode+=2; //read dest again and preserve it
				sRegs.n=4;
				sRegs.src0.reg=8; //r
				sRegs.src0.num=i;
				sRegs.src0.swz=0xff; //.wwww
				sRegs.src0.mod=0;
				sRegs.src0.idx=0;
				//pb_read_pregs shouldn't have changed src1
				sRegs.src2.reg=8; //r
				sRegs.src2.num=i;
				sRegs.src2.swz=0x55; //.yyyy
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode(log): Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_MAD<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000010: //lit dest,src0 (scalar lighting calculation function)
			case 0x40000010: //+lit
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_LIT<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}			
				p+=4;
				break;

			case 0x00000011: //dst dest,src0,src1 (calculates distance)
			case 0x40000011: //+dst
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DST<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000012: //frc dest,src0 (calculates fractional part -let's consider it same as expp for now-)
			case 0x40000012: //+frc
			case 0x00000013: //frc dest,src0 (calculates fractional part -let's consider it same as expp for now-)
			case 0x40000013: //+frc
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_EXP<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}
				p+=4;
				break;

			case 0x00000014: //m4x4 dest, src0, ?i (matrix multiply)
			case 0x40000014: //+m4x4
				//dp4 dest.x, src0, ?i
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (	(sRegs.src0.swz!=0x1b)||
					(sRegs.src1.swz!=0x1b)||
					(sRegs.src0.mod)||
					(sRegs.src1.mod)	) { debugPrint("pb_pcode2mcode: Modifiers or swizles not allowed in matrices multiplication macros\n"); return NULL; }
				sRegs.dest.msk=8; //.x
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp4 dest.y, src0, ?i+1
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=4; //.y				
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp4 dest.z, src0, ?i+2
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=2; //.z
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp4 dest.w, src0, ?i+3
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=1; //.w
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;
				
			case 0x00000015: //m4x3 dest, src0, ?i (matrix multiply)
			case 0x40000015: //+m4x3
				//dp4 dest.x, src0, ?i
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x3): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (	(sRegs.src0.swz!=0x1b)||
					(sRegs.src1.swz!=0x1b)||
					(sRegs.src0.mod)||
					(sRegs.src1.mod)	) { debugPrint("pb_pcode2mcode: Modifiers or swizles not allowed in matrices multiplication macros\n"); return NULL; }
				sRegs.dest.msk=8; //.x
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp4 dest.y, src0, ?i+1
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x3): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=4; //.y				
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp4 dest.z, src0, ?i+2
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m4x3): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=2; //.z
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP4<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000016: //m3x4 dest, src0, ?i (matrix multiply)
			case 0x40000016: //+m3x4
				//dp3 dest.x, src0, ?i
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (	(sRegs.src0.swz!=0x1b)||
					(sRegs.src1.swz!=0x1b)||
					(sRegs.src0.mod)||
					(sRegs.src1.mod)	) { debugPrint("pb_pcode2mcode: Modifiers or swizles not allowed in matrices multiplication macros\n"); return NULL; }
				sRegs.dest.msk=8; //.x
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp3 dest.y, src0, ?i+1
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=4; //.y				
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp3 dest.z, src0, ?i+2
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=2; //.z
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp3 dest.w, src0, ?i+3
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x4): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=1; //.w
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000017: //m3x3 dest, src0, ?i (matrix multiply)
			case 0x40000017: //+m3x3
				//dp3 dest.x, src0, ?i
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x3): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (	(sRegs.src0.swz!=0x1b)||
					(sRegs.src1.swz!=0x1b)||
					(sRegs.src0.mod)||
					(sRegs.src1.mod)	) { debugPrint("pb_pcode2mcode: Modifiers or swizles not allowed in matrices multiplication macros\n"); return NULL; }
				sRegs.dest.msk=8; //.x
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp3 dest.y, src0, ?i+1
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x3): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=4; //.y				
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp3 dest.z, src0, ?i+2
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x3): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=2; //.z
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000018: //m3x2 dest, src0, ?i (matrix multiply)
			case 0x40000018: //+m3x2
				//dp3 dest.x, src0, ?i
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x2): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (	(sRegs.src0.swz!=0x1b)||
					(sRegs.src1.swz!=0x1b)||
					(sRegs.src0.mod)||
					(sRegs.src1.mod)	) { debugPrint("pb_pcode2mcode: Modifiers or swizles not allowed in matrices multiplication macros\n"); return NULL; }
				sRegs.dest.msk=8; //.x
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				//dp3 dest.y, src0, ?i+1
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++; if (n==136) { debugPrint("pb_pcode2mcode(m3x2): Too many instructions: max=136 (including expanded macros)\n"); return NULL; }
				sRegs.dest.msk=4; //.y				
				if (sRegs.src1.reg==0xc) sRegs.src1.num=(sRegs.src1.num+1)%96; else sRegs.src1.num=(sRegs.src1.num+1)%16;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DP3<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x0000004e: //expp dest,src0 (scalar partial precision exponential function)
			case 0x4000004e: //+expp
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_EXP<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}
				p+=4;
				break;

			case 0x0000004f: //logp dest,src0 (scalar partial precision logarithm function)
			case 0x4000004f: //+logp
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_LOG<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}
				p+=4;
				break;

			case 0x00000051: //def cn x, y, z, w or def cn r, g, b, a
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_ID,1); *(p++)=((*(pcode++))&0xff)+96; //set cursor in order to load data into Cn
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_CONST_X,4); *(p++)=*(pcode++); *(p++)=*(pcode++); *(p++)=*(pcode++); *(p++)=*(pcode++);
				break;

			//non standard pseudo-code: nvidia-specific (vsa.exe won't accept these assembler instructions)
			//workaround : use dp4 and rcp, then, in pseudo code, replace 9 with 0x100 and 6 with 0x101

			case 0x00000100: //dph dest,src0,src1 (homogeneous dot product: same as dp4 but src0.w is seen as 1.0f)
			case 0x40000100: //+dph
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,3); pcode+=3;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_DPH<<NV20_VP_INST_VEC_OPCODE_SHIFT;
				p+=4;
				break;

			case 0x00000101: //rcc dest,src0 (clamped scalar 1/x function)
			case 0x40000101: //+rcc
				pb_push(p++,NV20_TCL_PRIMITIVE_3D_VP_UPLOAD_INST0,4); n++;
				pb_read_pregs(pcode,&sRegs,2); pcode+=2;
				//src2 is used instead of src0 in scalar functions
				sRegs.n=4;
				sRegs.src2=sRegs.src0;
				sRegs.src0.reg=9; //v0.xyzw for unused src
				sRegs.src0.num=0;
				sRegs.src0.mod=0;
				sRegs.src0.swz=0x1b;
				sRegs.src0.idx=0;
				sRegs.src1.reg=9; //v0.xyzw for unused src
				sRegs.src1.num=0;
				sRegs.src1.mod=0;
				sRegs.src1.swz=0x1b;
				sRegs.src1.idx=0;
				if (pb_set_mcode(p,&sRegs)) { debugPrint("pb_pcode2mcode: Unrecognized token\n"); return NULL; }
				*(p+1)|=NV20_VP_INST_OPCODE_RCC<<NV20_VP_INST_SCA_OPCODE_SHIFT;
				if (sRegs.dest.reg!=8) //not r
					*(p+3)|=NV20_VP_INST_DEST_SCA; //warns GPU that destination will receive scalar function result
				else
				{
					//scalar temp dest mask=temp dest mask & temp dest mask=0
					*(p+3)|=((*(p+3))&NV20_VP_INST_VTEMP_WRITEMASK_MASK)>>(NV20_VP_INST_VTEMP_WRITEMASK_SHIFT-NV20_VP_INST_STEMP_WRITEMASK_SHIFT);
					*(p+3)&=~NV20_VP_INST_VTEMP_WRITEMASK_MASK;
				}
				p+=4;
				break;
				
			default:
				debugPrint("pb_pcode2mcode: Unrecognized vs token #%08x\n",*(pcode-1));
				return NULL;	
		}
	}

	*(p-1)|=NV20_VP_INST_LAST_INST; //bit 0 of 4th dword means end of shader

	pb_gpu_programnc[0]=p-&pb_gpu_programnc[1]; //size
	pb_gpu_programnc[0]|=0x43210000; //personal vs marker
	return &pb_gpu_programnc[0];
}
