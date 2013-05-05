#
# update this variable to wherever you installed the OpenXDK libraries
#
#########################################################################
PREFIX = /openxdk

CC = gcc
CCAS = gcc
CPP  = g++
AR = ar rcu
RANLIB = ranlib
CXBE = $(PREFIX)/bin/cxbe

SDLFLAGS = -DENABLE_XBOX -DDEBUG
CC_FLAGS = -c -g -std=gnu99 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -march=i386 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
CCAS_FLAGS = -g -O2 -march=pentiumiii -mtune=pentiumiii -mmmx -msse
CPP_FLAGS = -c -O2 -Wall -nostdlib -fno-rtti -fno-builtin -fno-exceptions -march=i386 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I../../include

CLINK = -nostdlib -fno-rtti -fno-exceptions
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib 
LD_LIBS  = $(LD_DIRS) -lmscorlib -lXFX -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lgcc -lstdc++

OBJS = DrawableGameComponent.o Game.o GameComponent.o GameComponentCollection.o GameServiceContainer.o GamerServicesComponent.o GameTime.o GraphicsDeviceManager.o

all: libXFX.Game.a

rebuild: clean libXFX.Game.a

libXFX.Game.a: $(OBJS)
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
	