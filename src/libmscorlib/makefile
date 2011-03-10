#
# update this variable to wherever you installed the OpenXDK libraries
#
#########################################################################
PREFIX = /usr/local/openxdk

CC = gcc
CCAS = gcc
CPP  = g++
AR = ar rcu
RANLIB = ranlib
CXBE = $(PREFIX)/bin/cxbe

SDLFLAGS = -DENABLE_XBOX -DDEBUG
CC_FLAGS = -c -g -std=gnu99 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -mno-cygwin -march=i386 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
CCAS_FLAGS = --32 -march=pentiumiii, mmx, sse -mtune=pentiumiii -msse-check=error
CPP_FLAGS = -c -O2 -Wall -nostdlib -fno-builtin -mno-cygwin -march=i386 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I../../include

CLINK = -nostdlib
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib 
LD_LIBS  = $(LD_DIRS) -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lstdc++ -lgcc

OBJS = Array.o BinaryReader.o BinaryWriter.o BitConverter.o Buffer.o Calendar.o Comparer.o DateTime.o Decoder.o Dictionary.o Directory.o Encoder.o Environment.o Exception.o File.o FileStream.o HashHelpers.o KeyNotFoundException.o KeyValuePair.o Math.o MemoryStream.o Path.o Stack.o Stream.o StreamAsyncResult.o StreamReader.o StreamWriter.o Thread.o TimeSpan.o Version.o

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
