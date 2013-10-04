#
# update this variable to wherever you installed the OpenXDK libraries
#
#########################################################################
PREFIX = /openxdk

CC = xbox-gcc
CCAS = xbox-gcc
CPP  = xbox-g++
AR = xbox-ar rcu
RANLIB = xbox-ranlib
CXBE = $(PREFIX)/bin/cxbe

SDLFLAGS = -DENABLE_XBOX -DDEBUG
CC_FLAGS = -c -g -O2 -std=gnu99 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -march=i686 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
CCAS_FLAGS = --32 -march=pentiumiii, mmx, sse -mtune=pentiumiii -msse-check=error
CPP_FLAGS = -c -O2 -Wall -nostdlib -fno-builtin -fno-exceptions -fno-rtti -march=i686 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I../../include

CLINK = -nostdlib
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib 
LD_LIBS  = $(LD_DIRS) -lmscorlib -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lgcc -lstdc++

OBJS = CancelEventArgs.o Debug.o Socket.o SocketAddress.o SocketAsyncEventArgs.o Stopwatch.o

all: libSystem.a

rebuild: clean libSystem.a 

libSystem.a: $(OBJS)
	$(AR) $@ $(OBJS)
	$(RANLIB) $@
	
.c.o:
	$(CC) -c $< $(CC_FLAGS) $(INCLUDE)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(INCLUDE)

.s.o:
	$(CCAS) -c $< $(CCAS_FLAGS)

clean: 
	rm -f *.o *.exe *.dll *.xbe *.cxbe *.lib *.a
