#
# update this variable to wherever you installed the OpenXDK libraries
#
#########################################################################
PREFIX = /usr/local/openxdk
XFX_PREFIX = /usr/local/XFX

CC = gcc
CCAS = gcc
CPP  = g++
AR = ar rcu
RANLIB = ranlib
CXBE = $(PREFIX)/bin/cxbe

SDLFLAGS = -DENABLE_XBOX -DDEBUG
CC_FLAGS = -c -g -std=gnu99 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -mno-cygwin -march=i386 $(SDLFLAGS)
CCAS_FLAGS = -g -O2
CPP_FLAGS = -c -O2 -Wall -nostdlib -fno-builtin -mno-cygwin -march=i386 $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I$(XFX_PREFIX)/include -I/usr/local/GLES2

CLINK = -nostdlib
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib 
LD_LIBS  = $(LD_DIRS) -lXFX.Game -lXFX -lSystem.Xml -lSystem -lmscorlib -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lstdc++ -lgcc

OBJS = program.o

all: default.exe

default.exe: $(OBJS)
	$(CPP) -o $@ $(OBJS) $(LD_LIBS) $(LD_FLAGS) 
	$(CXBE) -TITLE:"default" -DUMPINFO:"default.cxbe" -OUT:"default.xbe" $@ > /dev/null
	
.c.o:
	$(CC) -c $< $(CC_FLAGS) $(INCLUDE)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(INCLUDE)

.s.o:
	$(CCAS) -c $< $(CCAS_FLAGS)

clean: 
	rm -f *.o *.exe *.dll *.xbe *.cxbe *.lib *.a
