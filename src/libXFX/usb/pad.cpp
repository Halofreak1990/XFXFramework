/******************************************************************************/
/*																              */
/*  File: pad.cpp                                                             */
/*  bkenwright@xbdev.net  -  www.xbdev.net                                    */
/*                                                                            */
/******************************************************************************/
#include "pad.h"
#include "misc.h" // memcpy(..), KernelCalls etc

#include <xboxkrnl/xboxkrnl.h>

// These couple of globals are defined in ohci.cpp - there our small group
// of descriptors which we use to communcate with the ohci-usb

extern unsigned int eds[176 + 0x100 + 0x100]; // ohci.cpp
extern unsigned int EDA;
extern s_Endpointdescripor * ED;

/******************************************************************************/
struct ohci_ed_t_ 
{
        unsigned int            ed_flags;
#define OHCI_ED_GET_FA(s)       ((s) & 0x7f)
#define OHCI_ED_ADDRMASK        0x0000007f
#define OHCI_ED_SET_FA(s)       (s)
#define OHCI_ED_GET_EN(s)       (((s) >> 7) & 0xf)
#define OHCI_ED_SET_EN(s)       ((s) << 7)
#define OHCI_ED_DIR_MASK		0x00001800
#define OHCI_ED_DIR_TD			0x00000000
#define OHCI_ED_DIR_OUT			0x00000800
#define OHCI_ED_DIR_IN			0x00001000
#define OHCI_ED_SPEED           0x00002000
#define OHCI_ED_SKIP            0x00004000
#define OHCI_ED_FORMAT_GEN      0x00000000
#define OHCI_ED_FORMAT_ISO      0x00008000
#define OHCI_ED_GET_MAXP(s)     (((s) >> 16) & 0x07ff)
#define OHCI_ED_SET_MAXP(s)     ((s) << 16)
#define OHCI_ED_MAXPMASK        (0x7ff << 16)
        unsigned int            ed_tailp;
        unsigned int            ed_headp;
#define OHCI_HALTED             0x00000001
#define OHCI_TOGGLECARRY        0x00000002
#define OHCI_HEADMASK           0xfffffffc
        unsigned int            ed_nexted;
};

struct ohci_td_t_
{
         unsigned int           td_flags;
#define  OHCI_TD_R              0x00040000              /* Buffer Rounding  */
#define  OHCI_TD_DP_MASK        0x00180000              /* Direction / PID */
#define  OHCI_TD_SETUP          0x00000000
#define  OHCI_TD_OUT            0x00080000
#define  OHCI_TD_IN             0x00100000
#define  OHCI_TD_GET_DI(x)      (((x) >> 21) & 7)       /* Delay Interrupt */
#define  OHCI_TD_SET_DI(x)      ((x) << 21)
#define  OHCI_TD_NOINTR         0x00e00000
#define  OHCI_TD_INTR_MASK      0x00e00000
#define  OHCI_TD_TOGGLE_CARRY   0x00000000
#define  OHCI_TD_TOGGLE_0       0x02000000
#define  OHCI_TD_TOGGLE_1       0x03000000
#define  OHCI_TD_TOGGLE_MASK    0x03000000
#define  OHCI_TD_GET_EC(x)      (((x) >> 26) & 3)       /* Error Count */
#define  OHCI_TD_GET_CC(x)      ((x) >> 28)             /* Condition Code */
#define  OHCI_TD_NOCC           0xf0000000
         unsigned int           td_cbp;         /* Current Buffer Pointer */
         unsigned int           td_nexttd;      /* Next TD */
         unsigned int           td_be;          /* Buffer End */
} ;

/******************************************************************************/
void usb_bulk_msg( usbd_device * dev, int size, void * data )
{
	ohci_t * ohci = dev->p_ohci;

	unsigned char buffer[256] = {0};

	memcpy(buffer, data, size);

	MmLockUnlockBufferPages((unsigned int)buffer, 0x8, 0);
	unsigned int real_pcmd = MmGetPhysicalAddress((unsigned int)buffer);

	unsigned char Descriptors[256] = {0};
	MmLockUnlockBufferPages((unsigned int)Descriptors, 256, 0);
	unsigned int real_pDescriptors = MmGetPhysicalAddress((unsigned int)Descriptors);

	s_Transferdescriptor *TD;
	TD = (s_Transferdescriptor *)(((unsigned int *)ED) + 20);
	unsigned int TDA = EDA + 80;
	unsigned int realTDA = MmGetPhysicalAddress((unsigned int)TDA);

////////////////////////////////////////////////////////////////////////
//   --Transfer Descriptor TD--
//   Offset	Field		Size	Value		Desc
//   0                  4       0..17       reserved
//                              
//      						18          R  - bufferRounding
//								19..20      DP - Direction/PID
//								                 00b SETUP
//												 01b OUT
//												 10b IN
//												 11b reserved
//								21..23      DI - DelayInterrupt
//	                            24..25      T  - DataToggle
//								26..27      EC - ErrorCount
//								28..31      CC - ConditionCode
//  4                   4                   CurrentBufferPoinnter (CBP)
//	8                   4       0..3        Zero
//	                            4..31       Next TD (NextTD)
// 12                   4                   Buffer End (BE)
//                                             
//(Total Size 16 bytes or 4 dwords)
//
////////////////////////////////////////////////////////////////////////

	// 0xE20050CA

	unsigned int td_format  = 0;
	td_format        |= OHCI_TD_OUT;        // 0x00080000  e.g. 1<<19
    td_format        |= OHCI_TD_TOGGLE_0;   // 0x02000000  e.g. 2<<24
	                                        /* I've set the data toggle sync here in 
	                                         * the TD by setting the MSB to 1 of Toggle Bits
	                                         * so the ED toggle bit isn't used. 
	                                         */
	td_format        |= OHCI_TD_NOCC;       // 0xf0000000
	                                        /* Set our ConditionCode to no errors */
	TD[0].Format     = td_format;
	//TD[0].Format	 = 0xE20050CA;			// Our Bulk Msg!
	TD[0].Buffer	 = real_pcmd;  
	TD[0].NextTD	 = realTDA + 16; 
	TD[0].BufferEnd	 = real_pcmd + size - 1; 		

	td_format        |= 0;
	td_format        |= OHCI_TD_OUT;
	td_format        |= OHCI_TD_TOGGLE_1;
	td_format        |= OHCI_TD_NOCC;

	TD[1].Format	= td_format;			// Receive Start of Descriptor
	TD[1].Buffer	= real_pDescriptors; 
	TD[1].NextTD	= realTDA + 32;
	TD[1].BufferEnd = real_pDescriptors + 7;

	td_format        |= 0;
	td_format        |= OHCI_TD_OUT;
	td_format        |= OHCI_TD_TOGGLE_0;
	td_format        |= OHCI_TD_NOCC;

	TD[3].Format	 = td_format;
	//TD[1].Format	 = 0xE30050CB;			// Queue END
	TD[3].Buffer	 = 0;
	TD[3].NextTD	 = 0;
	TD[3].BufferEnd	 = 0;

	////////////////////////////////////////////////////////////////////////
//   --EndPoint Descriptor ED--
//   Offset	Field		Size	Value		Desc
//   0                  4       Bitmap           
//	                            0..6        FA - Function Address
//	 							
//		                        7..10       EN - EndpointNumber
//								11..12      D  - Direction
//								                 00b GetDir From TD
//												 01b OUT
//												 10b IN
//												 11b GetDir From TD
//								13          S  - Speed (Full Speed=0)
//								14          K  - sKip
//								15          F  - Format
//								                 0 - Control/Bulk/Int********
//												 1 - Isochronous
//	                            16..26      MPS  MaximumPacketSize
//							    27..31      reserved
//	4                   4       Bitmap
//	                            0..3        Zero Aligment
//								4..31       TD Queue Tail Pointer (TailP)
//	8                   4       Bitmap
//	                            0           H  - Halted
//								1           C  - toggleCarry
//								2..3        reserved
//								4..31       TD Queue Head Pointer (HeadP)
//	12                  4       Bitmap
//	                            0..3        Zero Aligment
//								4..31       Next Endpoint Descriptor (NextED)
//
//(Total Size 16 bytes or 4 dwords)
//
////////////////////////////////////////////////////////////////////////

	//unsigned int format = 0x00401801; // 2(OUT) or 82(IN)?
	// 
	unsigned int ed_format =  0x00400000;
	ed_format       |= OHCI_ED_DIR_OUT;    // 0x00000800
	ed_format       |= OHCI_ED_DIR_IN;     // 0x00001000

	unsigned char Addr       =  dev->address;
	unsigned char EndAddr    =  0x2;

	ED[0].Format    =  ed_format;

	ED[0].Headptr   =  realTDA;
	ED[0].Tailptr   =  realTDA + 16;
	ED[0].Format    &= 0xFFFFFF00;          // Clear old address
	ED[0].Format    += Addr;                // Insert new address

	ED[0].Format    |= (EndAddr << 7 );

	#define OHCI_CTRL_CLE   (1 << 4)        /* control list enable */
	#define OHCI_CTRL_BLE   (1 << 5)        /* bulk list enable */
	#define OHCI_CTRL_HCFS  (3 << 6)        /* host controller functional state */

	#define OHCI_CLF        (1 << 1)        /* control list filled */
	#define OHCI_BLF        (1 << 2)        /* bulk list filled */

	// have to enable bulk tx
	//ohci->regs->cmdstatus  |= 2;			         // CommandStatus
	//ohci->regs->control	   = 0x90;		             // set CLE

	ohci->regs->cmdstatus |= (1<<2); // BLF
	ohci->regs->control = OHCI_CTRL_BLE | (2<<6); // BLF 
	ohci->regs->intrstatus = ohci->regs->intrstatus; // clear all Interruptflags

	// wait for execution
	//dbg("waiting for execution\n");
	do
	{

	}while(  (ohci->regs->intrstatus & 2)== 0 );

	Sleep(10);

	// ERRORS?
	ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;		// HCCA
	hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

	if( (hcca->done_head>>28) !=0 )
	{
#ifdef USB_DEBUG
		dbg("\nError Occured\n");
#endif //USB_DEBUG
		return;
	}

	//------------------------------------------------------------------

	// Where all done and finished now, so we set our ED's to our
	// Queue END where they behave and wait.
	ED[0].Headptr = realTDA + 48;
	ED[0].Tailptr = realTDA + 64;

#ifdef USB_DEBUG
	unsigned int ErrorCount     = OHCI_TD_GET_EC( TD[0].Format );
	unsigned int ConditionCode  = OHCI_TD_GET_CC( TD[0].Format );

	sprintf(buf, "ErrorCount: %d\n", ErrorCount); dbg(buf);
	sprintf(buf, "ConditionCode: %d\n", ConditionCode); dbg(buf);
#endif //USB_DEBUG

	Sleep(10);

	//memcpy( data, Descriptors, size);

	ED[0].Format = 0x00004000;
}

void once()
{
}

unsigned char xbuffer[256] = {0};

void usb_bulk_msg_in( usbd_device * dev, int size, void * data )
{
	ohci_t * ohci = dev->p_ohci;
	
	memset(xbuffer, 0, 256 );

	MmLockUnlockBufferPages( (unsigned int)xbuffer, 0x250, 0);
	unsigned int real_pbuffer = MmGetPhysicalAddress( (unsigned int)xbuffer);

	s_Transferdescriptor *TD;
	TD = (s_Transferdescriptor *)(((unsigned int *)ED) + 20);
	unsigned int TDA = EDA + 80;
	unsigned int realTDA = MmGetPhysicalAddress( (unsigned int)TDA );

	// 0xE20050CA

	unsigned int td_format  = 0;
	td_format        |= OHCI_TD_IN;         // 0x00100000  e.g. 1<<19
    td_format        |= OHCI_TD_TOGGLE_0;   // 0x02000000  e.g. 2<<24
	                                        /* I've set the data toggle sync here in 
	                                         * the TD by setting the MSB to 1 of Toggle Bits
	                                         * so the ED toggle bit isn't used. 
	                                         */
	td_format        |= OHCI_TD_NOCC;       // 0xf0000000
	                                        /* Set our ConditionCode to no errors */
	TD[0].Format     = td_format;			// Our Bulk Msg!		
	TD[0].Buffer	 = real_pbuffer;  
	TD[0].NextTD	 = realTDA + 16; 
	TD[0].BufferEnd	 = real_pbuffer + size - 1; 		

	/*
	td_format        |= 0;
	td_format        |= OHCI_TD_IN;
	td_format        |= OHCI_TD_TOGGLE_1;
	td_format        |= OHCI_TD_NOCC;
	TD[1].Format	= td_format;			// Receive Start of Descriptor
	TD[1].Buffer	= real_pbuffer; 
	TD[1].NextTD	= realTDA + 32;
	TD[1].BufferEnd = real_pbuffer + size - 1;
*/

	td_format        |= 0;
	td_format        |= OHCI_TD_IN;
	td_format        |= OHCI_TD_TOGGLE_1;
	td_format        |= OHCI_TD_NOCC;
	TD[1].Format	 = td_format;			// Queue END		
	TD[1].Buffer	 = 0;
	TD[1].NextTD	 = 0;
	TD[1].BufferEnd	 = 0;

	unsigned int ed_format =  0x00400000;
	ed_format       |= OHCI_ED_DIR_OUT;    // 0x00000800
	ed_format       |= OHCI_ED_DIR_IN;     // 0x00001000

	unsigned char Addr       =  dev->address;
	unsigned char EndAddr    =  0x2;

	ED[0].Format    =  ed_format;

	ED[0].Headptr   =  realTDA;
	ED[0].Tailptr   =  realTDA + 16;
	ED[0].Format    &= 0xFFFFFF00;          // Clear old address
	ED[0].Format    += Addr;                // Insert new address

	ED[0].Format    |= (EndAddr << 7 );

	#define OHCI_CTRL_CLE   (1 << 4)        /* control list enable */
	#define OHCI_CTRL_BLE   (1 << 5)        /* bulk list enable */
	#define OHCI_CTRL_HCFS  (3 << 6)        /* host controller functional state */

	#define OHCI_CLF        (1 << 1)        /* control list filled */
	#define OHCI_BLF        (1 << 2)        /* bulk list filled */

	Sleep(20);

	// have to enable bulk tx
	//ohci->regs->cmdstatus  |= 2;			         // CommandStatus
	//ohci->regs->control	   = 0x90;		             // set CLE

	ohci->regs->cmdstatus |= (1<<2); // BLF
	ohci->regs->control = OHCI_CTRL_BLE | (2<<6); // BLF 
	ohci->regs->intrstatus = ohci->regs->intrstatus; // clear all Interruptflags

	// wait for execution
	//dbg("waiting for execution\n");
	do
	{
		//dbg("waiting for execution-in loop\n");

	}while(  (ohci->regs->intrstatus & 2)== 0 );

	//dbg("waiting for execution-out loop\n");

	ohci->regs->intrstatus = ohci->regs->intrstatus;

	Sleep(30);

	// ERRORS?
	ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;		// HCCA
	hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

	if( (hcca->done_head>>28) !=0 )
	{
#ifdef USB_DEBUG
		dbg("\nError Occured\n");
#endif //USB_DEBUG
		return;
	}

	//------------------------------------------------------------------

#ifdef USB_DEBUG
	// Where all done and finished now, so we set our ED's to our
	// Queue END where they behave and wait.
	ED[0].Headptr = realTDA + 48;
	ED[0].Tailptr = realTDA + 64;


	unsigned int ErrorCount     = OHCI_TD_GET_EC( TD[0].Format );
	unsigned int ConditionCode  = OHCI_TD_GET_CC( TD[0].Format );

	if( ErrorCount  || ConditionCode )
	{
		sprintf(buf, "ErrorCount: %d\n", ErrorCount); dbg(buf);
		sprintf(buf, "ConditionCode: %d\n", ConditionCode); dbg(buf);
	}
#endif //USB_DEBUG

	//Sleep(50);

	memcpy( data, xbuffer, size);

	//ED[0].Format = 0x00004000;
}
