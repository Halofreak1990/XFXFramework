
#ifndef XBOXFLASH_H
#define XBOXFLASH_H

extern "C" {
#include <xboxkrnl/types.h>
#include <hal/fileio.h>
}

typedef struct fci_s {
	unsigned char mfct;
	unsigned char devc;
	const char *text;
	unsigned long size;
} fci_t;

class CXBoxFlash
{

public:
	CXBoxFlash(void);
	~CXBoxFlash(void);

	bool ReadFromXbox(char *path);
	bool WriteToXbox(char *path);

protected:
	fci_t* FindFCI(BYTE manuf, BYTE code);
	inline void Write(DWORD address,BYTE data);
	inline BYTE Read(DWORD address);
	void SetReadMode2(void);
	fci_t* CheckID2(void);
	fci_t* CheckID(void) ;
	void SetReadMode(void);
	bool EraseBlock(int block);
	bool EraseDevice(fci_t* fci);
	bool WaitOnToggle(void);
};

#endif
