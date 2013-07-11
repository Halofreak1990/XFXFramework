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
CPP_FLAGS = -c -O2 -std=c++03 -Wall -nostdlib -fno-builtin -fno-exceptions -fno-rtti -march=i686 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I../../include

CLINK = -nostdlib -pthread -fno-exceptions
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib 
LD_LIBS  = $(LD_DIRS) -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lgcc -lstdc++

OBJS = BinaryReader.o BinaryWriter.o BitConverter.o Boolean.o Byte.o Calendar.o Comparer.o Console.o DateTime.o DaylightTime.o Directory.o DirectoryInfo.o Double.o Environment.o EventArgs.o File.o FileStream.o FrameworkResources.o Int32.o Int64.o Math.o Object.o OperatingSystem.o Path.o sassert.o SByte.o Single.o Stream.o StreamAsyncResult.o StreamReader.o StreamWriter.o String.o StringBuilder.o Thread.o TimeSpan.o UInt16.o UInt32.o UInt64.o Version.o

all: libmscorlib.a

rebuild: clean libmscorlib.a 

libmscorlib.a: $(OBJS)
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
