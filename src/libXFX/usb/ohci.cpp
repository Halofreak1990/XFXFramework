/******************************************************************************/
/*																              */
/*  File: ohci.cpp                                                            */
/*                                                                            */
/*  Details: Original File & Design:  Thomas Frei                             */
/*  (modifications for xbox openxdk by bkenwright)                            */
/*  (bkenwright@xbdev.net)  www.xbdev.net                                     */
/*  and Halofreak1990 (halofreak_1990@hotmail.com)							  */
/*                                                                            */
/******************************************************************************/

//#define USB_DEBUG

#include "misc.h"

#ifdef USB_DEBUG
#include <stdio.h>				// sprintf(..)
#endif //USB_DEBUG

#include "ohci.h"		

/******************************************************************************/
/*                                                                            */
/*                                 Globals                                    */
/*                                                                            */
/******************************************************************************/

unsigned int eds[176 + 0x100 + 0x100];
unsigned int EDA;
s_Endpointdescripor * ED;
unsigned char found = 0;

/******************************************************************************/
int FindOHC(ohci_t * ohci, void *regbase) 
{
	// STI and CLI can be used to enable/disable interrupts 
	/*
	__asm
	{
		cli
	}
	*/
	
	void *hcca;
	
	memset(ohci,0,sizeof(ohci_t));
	
	ohci->regs = (ohci_regs*)regbase;
	
	// This is where we align or hcca so its 256byte aligned
	hcca = malloc(0x10000+0x100);
	memset(hcca,0,0x10000+0x100);	
	ohci->hcca = (ohci_hcca *)((unsigned int)(unsigned int(hcca) + 0x100) & 0xffffff00);

	MmLockUnlockBufferPages( (unsigned int)hcca, 0x10000+0x100, 0);

	MmLockUnlockBufferPages( (unsigned int)eds, 0x100, 0);

	// Just make sure our memory for ED's is aligned
	EDA = (unsigned int)eds;
	EDA += 0x100;
	EDA &= 0xfffff00;								  // e.g was 0x0002ED20, but is now 0x0002EE00, so its
	                                                  // 16 bit memory aligned
	ED = (s_Endpointdescripor*)EDA;

	unsigned int realEDA = MmGetPhysicalAddress( (unsigned int)EDA );

	unsigned int * pHCCA = (unsigned int*)ohci->hcca;
	for(int i=0; i<32; i++) pHCCA[i] = realEDA; //EDA;
	pHCCA[32] = 0;
	pHCCA[33] = 0;

	for( i=0; i<5; i++ )
	{
		ED[i].Format = AUTOIO | 0x402000; // AUTOIO 0x1800L
		ED[i].NextED = realEDA + (16*(i+1)); //EDA + (16*(i+1));
		ED[i].Headptr = 0;
		ED[i].Tailptr = 0;
	}

	ED[0].Format = 0x4000;                            // Should really explain whats happening
	ED[0].NextED = 0;                                 // here, ED[0] is going to be the bulkhead descriptor.
	ED[1].NextED = 0;                                 // It is setup, but never used - as you'll always see
	ED[4].NextED = 0;                                 // ED[1] being set with values in this demo code.
	                                                  // As ED's are all 16bit aligned this way.
	// init the hardware

	// what state is the hardware in at the moment?  (usually reset state)
	switch( ohci->regs->control & 0xc0 )
	{
	case 0x0: // in reset: a cold boot
		ohci->regs->roothub.a = 0x10000204;
		ohci->regs->roothub.b = 0x00020002;
		ohci->regs->fminterval = (4096<<16)|(11999);
		ohci->regs->control = ((ohci->regs->control) & (~0xc0))|0x80;
		break;

	case 0x80: // operational already
		break;

	case 0x40: // resume
	case 0xc0: // suspend
		ohci->regs->control = ((ohci->regs->control)&(~0xc0))|0x40;
		Sleep(50000);
		break;
	}

	unsigned int fminterval = ohci->regs->fminterval;	// stash interval
	ohci->regs->cmdstatus = 1;							// host controller reset

	Sleep(20);	// should only take 10us max to reset

	ohci->regs->fminterval = fminterval;				// restore our saved interval

	unsigned int realhcca = MmGetPhysicalAddress( (unsigned int)ohci->hcca );
	//ohci->regs->hcca = (unsigned int)ohci->hcca;
	ohci->regs->hcca = realhcca;

	//ohci->regs->intrdisable = ~0x0;					// Not sure about this...but turn off any interrupts?

	ohci->regs->intrenable = 0xC000007B;				// set HcInterruptEnable

	ohci->regs->control = 0x00000080;					// HC operational

	Sleep(50);

#ifdef USB_DEBUG
	// HCFS - usb state (00,01,10,11->reset,resume,operational,suspend)
    // bits 6 and 7 in the control register
	sprintf( buf, "USBOPERATIONAL : %s\n",  ( ((ohci->regs->control>>6) & 0x3) == 0x2) ? "yes":"no" );	dbg(buf);
	sprintf( buf, "USBOPERATIONAL : 0x%02X\n",  ( (ohci->regs->control>>6) & 0x3));	dbg(buf);
#endif // USB_DEBUG

	ohci->regs->fminterval |= 0x27780000;				// set FSLargestDataPacket
	
	unsigned int temp = ohci->regs->fminterval & 0xffff;
	temp /= 10;
	ohci->regs->periodicstart = temp;					// set HcPeriodicStart to 10% of HcFmInterval

	// Global power on
	ohci->regs->roothub.status = 0x10000;

	unsigned int tt = ohci->regs->intrstatus;					// clear interrupts
	ohci->regs->intrstatus = tt;

#ifdef USB_DEBUG
	DebugFile( ohci );
#endif // USB_DEBUG

	//ohci->regs->ed_bulkhead = EDA;						// BulkHead
	
	//unsigned int realEDA = MmGetPhysicalAddress( (unsigned int)EDA );
	ohci->regs->ed_bulkhead = realEDA;

	// link ED's in Queue
	//ohci->regs->ed_controlhead = EDA+16;				// ControlHead
	ohci->regs->ed_controlhead = realEDA + 16;

	// NDP
	int NDP = (ohci->regs->roothub.a & 0xFF);

	// disable all devices
	for( int i=0; i<4; i++ )
	{
		ohci->regs->roothub.portstatus[i] = 0x11;
	}

	return NDP;
}// End FindOHC(..)

/******************************************************************************/
int FindDev(ohci_t * ohci, int Port)
{
	unsigned int TDA;
	int Speed=0;

	s_USB_Devicedescriptor DD;
	s_USB_Devicedescriptor * pDD = &DD;
	memset(pDD, 0, sizeof(DD) );

	s_Transferdescriptor * TD;

	unsigned int GetDescr[2] = { 0x01000680, 0x00080000 };
	unsigned int WG  = (unsigned int)GetDescr;
	MmLockUnlockBufferPages( WG, 0x8, 0);
	unsigned int DDA = (unsigned int)pDD;
	MmLockUnlockBufferPages( DDA, 0x32, 0);

	TD = (s_Transferdescriptor*) (((unsigned int*)ED)+20); // Same as saying TD = EDA+80 ;)
	TDA = EDA + 80;

	unsigned int realTDA = MmGetPhysicalAddress( (unsigned int)TDA );

	TD[0].Format	= 0xE20050C0;	// Get DeviceDescriptor
	TD[0].Buffer	= MmGetPhysicalAddress(WG);
	//TD[0].NextTD	= TDA + 16;
	TD[0].NextTD	= realTDA + 16;
	TD[0].BufferEnd = MmGetPhysicalAddress(WG+7);
	TD[1].Format	= 0xE31050C1;	// Receive first 8 bytes of DeviceDescriptor
	TD[1].Buffer	= MmGetPhysicalAddress(DDA);
	TD[1].NextTD	= realTDA + 32;
	TD[1].BufferEnd = MmGetPhysicalAddress(DDA + 7);
	TD[2].Format	= 0xE20050C2;	// Queue END
	TD[2].Buffer	= 0;
	TD[2].NextTD	= 0;
	TD[2].BufferEnd = 0;

	// Power on + Enable Ports
	ohci->regs->roothub.portstatus[ Port ] = 0x100;
	Sleep(2);

	if( (ohci->regs->roothub.portstatus[ Port] & 1) == 0 )
		return 0; // No device

	if( ohci->regs->roothub.portstatus[ Port] & 0x200)  // lowspeed device?
		Speed = 1;
	else
		Speed = 2;

	if( ohci->regs->roothub.portstatus[ Port ] & 0x10000 ) // Port Power changed?
	{
		ohci->regs->roothub.portstatus[ Port ] = 0x10000; // Port power Ack
	}

	// Port Reset
	// We will try and do this 4 times
	ohci->regs->roothub.portstatus[ Port ] = 0x10;
	Sleep(40);
	for(int i=0; i<4; i++)
	{
		if( (ohci->regs->roothub.portstatus[ Port ] & 0x10) == 0 )
			break;
		
#ifdef USB_DEBUG
		sprintf(buf, "\tport: %d, reset failed %d times\n", Port, i);
		dbg(buf);
#endif //USB_DEBUG

		Sleep(100);
	}

	ohci->regs->roothub.portstatus[ Port ] = 0x100000;

	if( (ohci->regs->roothub.portstatus[ Port ] & 7) != 3 ) // Port disabled?
	{
		ohci->regs->roothub.portstatus[ Port ] = 2;
	}

	// Configure Endpointdescriptor
	if(Speed==2)
		ED[1].Format &= 0xFFFFDFFF;
	else
		ED[1].Format |= 0x2000;

	// determine MPS
	ED[1].Headptr = realTDA;
	ED[1].Tailptr = realTDA + 32;
	ED[1].Format &= 0xffffff00;

	// set CLF
	ohci->regs->cmdstatus |= 2;		// CommandStatus

	ohci->regs->control = 0x90;		// set CLE

	unsigned int tt = ohci->regs->intrstatus;		// clear all Interruptflags
	ohci->regs->intrstatus = tt;

#ifdef USB_DEBUG
	DebugFile( ohci );
#endif // USB_DEBUG

#ifdef USB_DEBUG
	// wait for execution
	dbg("waiting for execution\n");
#endif // USB_DEBUG
	do
	{
		ohci->regs->intrstatus = 0x4; // SOF

	}while(  (ohci->regs->intrstatus & 2)== 0 );

	Sleep(10);

	// Errors?
	ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;				// HCCA
	hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

	if( (hcca->done_head>>28)==0 )
	{
		ED[1].Format &= 0xF800FFFF;
		ED[1].Format |= (((unsigned int)DD.MaxPacketSize) << 16);
		found++;
	}
	else
		return 0;

#ifdef USB_DEBUG
	sprintf(buf, "\nDescriptor.Length: 0x%x\n",			DD.Length );			dbg(buf);
	sprintf(buf, "Descriptor.DescriptorType: 0x%02X\n",	DD.DescriptorType );	dbg(buf);
	sprintf(buf, "Descriptor.USB: 0x%04X\n",			DD.USB );				dbg(buf);
	sprintf(buf, "Descriptor.DeviceClass: 0x%04X\n",	DD.DeviceClass );		dbg(buf);
	sprintf(buf, "Descriptor.DeviceSubClass: 0x%04X\n",	DD.DeviceSubClass );	dbg(buf);
	sprintf(buf, "Descriptor.DeviceProtocol: 0x%04X\n",	DD.DeviceProtocol );	dbg(buf);
	sprintf(buf, "Descriptor.MaxPacketSize: 0x%04X\n",	DD.MaxPacketSize );		dbg(buf);
	sprintf(buf, "Descriptor.Vendor: 0x%04X\n",			DD.Vendor );			dbg(buf);
	sprintf(buf, "Descriptor.ProductID: 0x%04X\n",		DD.ProductID );			dbg(buf);
	sprintf(buf, "Descriptor.Manufacturer: 0x%04X\n",	DD.Manufacturer );		dbg(buf);
	sprintf(buf, "Descriptor.ProductIndex: 0x%04X\n",	DD.ProductIndex );		dbg(buf);
	sprintf(buf, "Descriptor.SerialNumber: 0x%04X\n",	DD.SerialNumber );		dbg(buf);
	sprintf(buf, "Descriptor.ConfigNumber: 0x%04X\n",	DD.ConfigNumber );		dbg(buf);
#endif // USB_DEBUG

	return (Speed);
}// End FindDev(..)

/******************************************************************************/
int ResetPort(ohci_t * ohci, int Port)
{
	ohci->regs->roothub.portstatus[ Port*4 ] = 0x10;
	Sleep(40);

	ohci->regs->roothub.portstatus[ Port*4 ] = 0x100000;

	return 0;
}// End ResetPort(..)

/******************************************************************************/
int SetAddres(ohci_t * ohci, int Port, unsigned char AddrNew)
{
	unsigned int SetAddr[2] = {0x00000500, 0 };
	unsigned int WS = (unsigned int)SetAddr;

	s_Transferdescriptor *TD;
	unsigned char P = Port;

	if( P==0 ) P = found;
	
	SetAddr[0] |= (((unsigned int)AddrNew)<<16);

	MmLockUnlockBufferPages( WS, 0x8, 0);

	unsigned int TDA;

	//TD = (s_Transferdescriptor* ) new int[0x1000];
	//TD = (s_Transferdescriptor*) ((((unsigned int)TD)+0x100)&0xfffff00);
	//memset(TD, 0, sizeof(s_Transferdescriptor)*4 );

	///TD = (s_Transferdescriptor *) (((unsigned int *)ED)+20);
	TD  = (s_Transferdescriptor *)(EDA+80); 
	TDA = EDA+80;

	unsigned int realTDA = MmGetPhysicalAddress( (unsigned int)TDA );

	TD[0].Format	= 0xE20050C4;		// Set Address
	TD[0].Buffer	= MmGetPhysicalAddress(WS);
	TD[0].NextTD	= realTDA + 16; // (unsigned int)(&TD[1]); //TDA + 16;
	TD[0].BufferEnd	= MmGetPhysicalAddress(WS + 7);
	TD[1].Format	= 0xE31050C5;		// Receive Acknowledge
	TD[1].Buffer	= 0;
	TD[1].NextTD	= realTDA + 32; // (unsigned int)(&TD[2]); //TDA + 32;
	TD[1].BufferEnd	= 0;
	TD[2].Format	= 0xE20050C6;		// End Queue
	TD[2].Buffer	= 0;
	TD[2].NextTD	= 0;
	TD[2].BufferEnd	= 0;
	
	//ED[1].Headptr	= (unsigned int)(&(TD[0])); // TDA;
	//ED[1].Tailptr	= (unsigned int)(&(TD[2])); // TDA + 32;

	ED[1].Headptr = realTDA;
	ED[1].Tailptr = realTDA + 32;

	// set CLF
	ohci->regs->cmdstatus |= 2;			// CommandStatus

	ohci->regs->control	 = 0x90;		// set CLE

	ohci->regs->intrstatus = ohci->regs->intrstatus; // clear all Interruptflags

	DebugFile( ohci );

#ifdef USB_DEBUG
	// wait for execution
	dbg("waiting for execution\n");
#endif // USB_DEBUG
	do
	{

	}while(  (ohci->regs->intrstatus & 2)== 0 );

	Sleep(10);

	// ERRORS?
	ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;	// HCCA
	hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

	if( (hcca->done_head>>28) !=0 )
		return 1;

	ED[1].Format &= 0xFFFFFF00;
	ED[1].Format += AddrNew;

	return 0;
}// End SetAddr(..)

/******************************************************************************/
int SetConfigur(ohci_t * ohci, unsigned char Addr, unsigned char Config)
{
	unsigned int SetConfig[2] = {0x00000900, 0 };

	unsigned int WC = (unsigned int)SetConfig;

	s_Transferdescriptor *TD;

	SetConfig[0] |= (((unsigned int)Config)<<16);

	MmLockUnlockBufferPages( WC, 0x8, 0);

	unsigned int TDA;

	TD = (s_Transferdescriptor *) (((unsigned int *)ED) +20 );
	TDA = EDA + 80;

	unsigned int realTDA = MmGetPhysicalAddress( (unsigned int)TDA );

	TD[0].Format	= 0xE20050C7;				// Set Configuration
	TD[0].Buffer	= MmGetPhysicalAddress(WC);
	TD[0].NextTD	= realTDA + 16;//TDA + 16;
	TD[0].BufferEnd	= MmGetPhysicalAddress(WC + 7);
	TD[1].Format	= 0xE30050C8;
	TD[1].Buffer	= 0;
	TD[1].NextTD	= 0;
	TD[1].BufferEnd	= 0;
	
	ED[1].Headptr	= realTDA; //TDA;
	ED[1].Tailptr	= realTDA + 16; //TDA + 16;
	ED[1].Format	&= 0xFFFFFF00;
	ED[1].Format	+= Addr;

	// set CLF
	ohci->regs->cmdstatus |= 2;			// CommandStatus

	ohci->regs->control	 = 0x90;		// set CLE

	ohci->regs->intrstatus = ohci->regs->intrstatus; // clear all Interruptflags

#ifdef USB_DEBUG
	// wait for execution
	dbg("waiting for execution\n");
#endif //USB_DEBUG
	do
	{

	}while(  (ohci->regs->intrstatus & 2)== 0 );

	Sleep(10);

	// ERRORS?
	//ohci_hcca *hcca = (ohci_hcca*)ohci->regs->hcca;	// HCCA
	ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;
	hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

	if( (hcca->done_head>>28) !=0 )
		return 1;

	return 0;
}// End SetConfig(..)

/******************************************************************************/
int GetDesc(ohci_t * ohci, unsigned char Addr, unsigned char DescrType, unsigned char Index, unsigned char Count, unsigned char *DBuffer)
{
	unsigned int TDA;

	unsigned char Descriptors[256];
	unsigned int GetDescr[2] = {0x00000680, 0x0 };
	unsigned int WG = (unsigned int)GetDescr;
	unsigned int DA = (unsigned int)Descriptors;

	MmLockUnlockBufferPages( WG, 0x8, 0);
	MmLockUnlockBufferPages( DA, 256, 0);

	unsigned int realDA = MmGetPhysicalAddress(DA);

	unsigned char lCount = Count;

	GetDescr[0] |= (((unsigned int) DescrType) << 24 );
	GetDescr[0] |= (((unsigned int) Index ) << 16 );

	s_Transferdescriptor *TD;

	TD = (s_Transferdescriptor *)(((unsigned int *)ED) + 20);
	TDA = EDA + 80;

	unsigned int realTDA = MmGetPhysicalAddress( (unsigned int)TDA );

	TD[0].Format	= 0xE20050CA;		// Get Descriptor
	TD[0].Buffer	= MmGetPhysicalAddress(WG);
	TD[0].NextTD	= realTDA + 16; //TDA + 16;
	TD[0].BufferEnd	= MmGetPhysicalAddress(WG+7);			
	TD[1].Format	= 0xE31450CB;		// Receive Start of Descriptor
	TD[1].Buffer	= realDA; //DA;
	TD[1].NextTD	= realTDA+32; //TDA+32;
	TD[1].BufferEnd = realDA + 7;  //DA + 7;

	//-------------------------------------------------------------

	TD[2].Format	= 0xE21450CC;			// Receive Rest of Descriptor
	TD[2].Buffer	= realDA + 8;//DA + 8;
	TD[2].NextTD	= realTDA + 48; //TDA + 48;
	TD[2].BufferEnd	= 0;
	TD[3].Format	= 0xE30050CD;			// Queue END
	TD[3].Buffer	= 0;
	TD[3].NextTD	= 0;
	TD[3].BufferEnd	= 0;

	GetDescr[1] = ((unsigned int) lCount) << 16 ;
	ED[1].Headptr = realTDA; //TDA;
	ED[1].Tailptr = realTDA + 32; //TDA + 32;
	ED[1].Format  &= 0xFFFFFF00;
	ED[1].Format  += Addr;

	if( DescrType == 3 )
		GetDescr[1] |= 0x0409;
	TD[1].BufferEnd = realDA + lCount - 1; // DA + lCount - 1;

	// set CLF
	ohci->regs->cmdstatus |= 2;			// CommandStatus

	ohci->regs->control	 = 0x90;		// set CLE

	ohci->regs->intrstatus = ohci->regs->intrstatus; // clear all Interruptflags

#ifdef USB_DEBUG
	// wait for execution
	dbg("waiting for execution\n");
#endif //USB_DEBUG
	do
	{

	}while(  (ohci->regs->intrstatus & 2)== 0 );

	Sleep(10);

	// ERRORS?
	//ohci_hcca *hcca = (ohci_hcca*)ohci->regs->hcca;	// HCCA
	ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;
	hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

	if( (hcca->done_head>>28) !=0 )
	{
#ifdef USB_DEBUG
		dbg("\nError Occured\n");
#endif //USB_DEBUG
		return 1;
	}

	//------------------------------------------------------------------

	ED[1].Headptr = realTDA + 48; //TDA + 48;
	ED[1].Tailptr = realTDA + 64; //TDA + 64;

	if( (DescrType==3) && (lCount < Descriptors[0]) && 0)
	{
		// set CLF
		ohci->regs->cmdstatus |= 2;			// CommandStatus

		ohci->regs->control	 = 0x90;		// set CLE

		ohci->regs->intrstatus = ohci->regs->intrstatus; // clear all Interruptflags

#ifdef USB_DEBUG
		// wait for execution
		dbg("waiting for execution");
#endif //USB_DEBUG
		do
		{

		}while(  (ohci->regs->intrstatus & 2)== 0 );

		Sleep(10);

		// ERRORS?
		//ohci_hcca *hcca = (ohci_hcca*)ohci->regs->hcca;	// HCCA
		ohci_hcca *hcca = (ohci_hcca*)ohci->hcca;
		hcca->done_head &= 0xfffffffe;					// DoneHead in HCCA

		if( (hcca->done_head>>28) !=0 )
			return 1;
	}

	if( DescrType==2)
	{
		if( Descriptors[2] < lCount) lCount = Descriptors[2];
	}
	else
	{
		if( Descriptors[0] < lCount) lCount = Descriptors[0];
	}

	/*
	sprintf( buf, "Descriptors:\n");	dbg(buf);
	for(int i=0; i<lCount; i++)
	{
		sprintf(buf, "%X ", Descriptors[i]); dbg(buf); 
	}
	sprintf(buf, "\n"); dbg(buf);
	*/

	Sleep(10);

	memcpy( DBuffer, Descriptors, lCount);

	return 0;
}// End GetDesc(..)

/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*  These function are nothing more than debug functions - they are used      */
/*  to save the register, or descriptor values back to file, so we can check  */
/*  that all is okay and ticking away as we want :)                           */
/*                                                                            */
/******************************************************************************/
void DebugFile(ohci_t * ohci)
{
#ifdef USB_DEBUG
	dbg("\n\n");

	sprintf( buf, " revision 0x%08x\n",ohci->regs->revision);					dbg(buf);
	sprintf( buf, " control 0x%08x\n",ohci->regs->control);						dbg(buf);
	sprintf( buf, " cmdstatus 0x%08x\n",ohci->regs->cmdstatus);					dbg(buf);
	sprintf( buf, " intrstatus 0x%08x\n",ohci->regs->intrstatus);				dbg(buf);
	sprintf( buf, " intrenable 0x%08x\n",ohci->regs->intrenable);				dbg(buf);
	sprintf( buf, " intrdisable 0x%08x\n",ohci->regs->intrdisable);				dbg(buf);
	sprintf( buf, " ed_periodcurrent 0x%08x\n",ohci->regs->ed_periodcurrent);	dbg(buf);
	sprintf( buf, " ed_controlhead 0x%08x\n",ohci->regs->ed_controlhead);		dbg(buf);
	sprintf( buf, " ed_controlcurrent 0x%08x\n",ohci->regs->ed_controlcurrent);	dbg(buf);
	sprintf( buf, " ed_bulkhead 0x%08x\n",ohci->regs->ed_bulkhead);				dbg(buf);
	sprintf( buf, " ed_bulkcurrent 0x%08x\n",ohci->regs->ed_bulkcurrent);		dbg(buf);
	sprintf( buf, " donehead 0x%08x\n",ohci->regs->donehead);					dbg(buf);
	sprintf( buf, " fminterval 0x%08x\n",ohci->regs->fminterval);				dbg(buf);
	sprintf( buf, " fmremaining 0x%08x\n",ohci->regs->fmremaining);				dbg(buf);
	sprintf( buf, " periodicstart 0x%08x\n",ohci->regs->periodicstart);			dbg(buf);
	sprintf( buf, " lsthresh 0x%08x\n",ohci->regs->lsthresh);					dbg(buf);
	sprintf( buf, " ohci_roothub_regs.a 0x%08x\n",ohci->regs->roothub.a);		dbg(buf);
	sprintf( buf, " ohci_roothub_regs.b 0x%08x\n",ohci->regs->roothub.b);		dbg(buf);
	sprintf( buf, " ohci_roothub_regs.status 0x%08x\n",ohci->regs->roothub.status);	dbg(buf);

	sprintf( buf, " ohci_roothub_regs.portstatus[0] 0x%08x\n",ohci->regs->roothub.portstatus[0]);	dbg(buf);
	sprintf( buf, " ohci_roothub_regs.portstatus[1] 0x%08x\n",ohci->regs->roothub.portstatus[1]);	dbg(buf);
	sprintf( buf, " ohci_roothub_regs.portstatus[2] 0x%08x\n",ohci->regs->roothub.portstatus[2]);	dbg(buf);
	sprintf( buf, " ohci_roothub_regs.portstatus[3] 0x%08x\n",ohci->regs->roothub.portstatus[3]);	dbg(buf);
#endif //USB_DEBUG

}// End of DebugFile(..)

void DebugDescriptor( s_USB_Devicedescriptor * pDes )
{
#ifdef USB_DEBUG
	sprintf(buf, "\n*Descriptor*\n");											dbg(buf);

	sprintf(buf, "Descriptor.Length: 0x%x\n",			pDes->Length );			dbg(buf);
	sprintf(buf, "Descriptor.DescriptorType: 0x%02X\n",	pDes->DescriptorType );	dbg(buf);
	sprintf(buf, "Descriptor.USB: 0x%04X\n",			pDes->USB );			dbg(buf);
	sprintf(buf, "Descriptor.DeviceClass: 0x%04X\n",	pDes->DeviceClass );	dbg(buf);
	sprintf(buf, "Descriptor.DeviceSubClass: 0x%04X\n",	pDes->DeviceSubClass );	dbg(buf);
	sprintf(buf, "Descriptor.DeviceProtocol: 0x%04X\n",	pDes->DeviceProtocol );	dbg(buf);
	sprintf(buf, "Descriptor.MaxPacketSize: 0x%04X\n",	pDes->MaxPacketSize );	dbg(buf);

	sprintf(buf, "Descriptor.Vendor: 0x%04X\n",			pDes->Vendor );			dbg(buf);
	sprintf(buf, "Descriptor.ProductID: 0x%04X\n",		pDes->ProductID );		dbg(buf);
	sprintf(buf, "Descriptor.Device: 0x%04X\n",			pDes->Device);          dbg(buf);

	sprintf(buf, "Descriptor.Manufacturer: 0x%02X\n",	pDes->Manufacturer );	dbg(buf);
	sprintf(buf, "Descriptor.ProductIndex: 0x%02X\n",	pDes->ProductIndex );	dbg(buf);
	sprintf(buf, "Descriptor.SerialNumber: 0x%02X\n",	pDes->SerialNumber );	dbg(buf);
	sprintf(buf, "Descriptor.ConfigNumber: 0x%02X\n",	pDes->ConfigNumber );	dbg(buf);
#endif //USB_DEBUG

}// End DebugDescriptor(..)

void DebugConfigDescriptor( s_USB_Configurationdescriptor * pDes )
{
#ifdef USB_DEBUG
	sprintf(buf, "\n+Configuration Descriptor+\n");								dbg(buf);

	sprintf(buf, "ConfDesc.Length: 0x%02X\n",			pDes->Length );			dbg(buf);
	sprintf(buf, "ConfDescDescriptorType: 0x%02X\n",	pDes->DescriptorType );	dbg(buf);
	sprintf(buf, "ConfDesc.TotalLength: 0x%04X\n",		pDes->TotalLength );	dbg(buf);
	sprintf(buf, "ConfDesc.NumberofInterfaces: 0x%02X\n",	pDes->NumberofInterfaces );		dbg(buf);

	sprintf(buf, "ConfDesc.ConfigValue: 0x%02X\n",		pDes->ConfigValue );	dbg(buf);
	sprintf(buf, "ConfDesc.Configuration: 0x%02X\n",	pDes->Configuration );	dbg(buf);
	sprintf(buf, "ConfDesc.Attributes: 0x%02X\n",		pDes->Attributes );		dbg(buf);
	sprintf(buf, "ConfDesc.MaxPower: 0x%02X\n",			pDes->MaxPower );		dbg(buf);
#endif //USB_DEBUG

}// End DebugConfigDescriptor(..)

void DebugIntefaceDescriptor( s_USB_Interfacedescriptor * pDes )
{
#ifdef USB_DEBUG
	sprintf(buf, "\n#Interface Descriptor#\n");										dbg(buf);
	
	sprintf(buf, "InterDesc.Length: 0x%02X\n",		pDes->Length );					dbg(buf);
	sprintf(buf, "InterDesc.DescriptorType: 0x%02X\n",		pDes->DescriptorType );	dbg(buf);
	sprintf(buf, "InterDesc.Interfacenumber: 0x%02X\n", pDes->Interfacenumber );	dbg(buf);
	sprintf(buf, "InterDesc.AlternateSetting: 0x%02X\n",pDes->AlternateSetting );	dbg(buf);
	sprintf(buf, "InterDesc.NumberofEndpoints: 0x%02X\n", pDes->NumberofEndpoints );dbg(buf);
	sprintf(buf, "InterDesc.InterfaceClass: 0x%02X\n", pDes->InterfaceClass );		dbg(buf);
	sprintf(buf, "InterDesc.InterfaceSubClass: 0x%02X\n", pDes->InterfaceSubClass );dbg(buf);
	sprintf(buf, "InterDesc.InterfaceProtocol: 0x%02X\n",pDes->InterfaceProtocol );	dbg(buf);
	sprintf(buf, "InterDesc.InterfaceIndex: 0x%02X\n",	 pDes->InterfaceIndex );	dbg(buf);
#endif //USB_DEBUG

}// End DebugInterfaceDescriptor(..)

void DebugEndPointDescriptor( s_USB_Endpointdescriptor * pDes )
{
#ifdef USB_DEBUG
	sprintf(buf, "\n#EndPointDescriptor Descriptor#\n");	dbg(buf);


	sprintf(buf, "EndPointDes.Length: 0x%02X\n",		pDes->Length );				dbg(buf);
	sprintf(buf, "EndPointDes.DescriptorType: 0x%02X\n", pDes->DescriptorType );	dbg(buf);
	sprintf(buf, "EndPointDes.EndpointAddress: 0x%02X\n", pDes->EndpointAddress );	dbg(buf);
	sprintf(buf, "EndPointDes.Attributes: 0x%02X\n",pDes->Attributes );				dbg(buf);
	sprintf(buf, "EndPointDes.MaxPacketSize: 0x%02X\n", pDes->MaxPacketSize );		dbg(buf);
	sprintf(buf, "EndPointDes.Interval: 0x%02X\n", pDes->Interval );				dbg(buf);
#endif //USB_DEBUG
	
}// End of DebugEndPointDescriptor(..)
