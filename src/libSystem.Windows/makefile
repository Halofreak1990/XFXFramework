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
CC_FLAGS = -c -g -O2 -std=gnu99 -ffreestanding -nostdlib -fno-builtin -fno-exceptions -march=i686 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
CCAS_FLAGS = --32 -march=pentiumiii, mmx, sse -mtune=pentiumiii -msse-check=error
CPP_FLAGS = -c -O2 -Wall -nostdlib -fno-builtin -fno-exceptions -fno-rtti -march=i686 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I../../include

CLINK = -nostdlib -pthread -fno-exceptions
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib 
LD_LIBS  = $(LD_DIRS) -lSystem -lmscorlib -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lgcc -lstdc++

OBJS = Border.o Brush.o ButtonBase.o ClosingEventArgs.o Color.o ContentControl.o Control.o CornerRadius.o FrameworkElement.o Grid.o MessageBox.o Panel.o Point.o RangeBase.o Size.o SolidColorBrush.o StackPanel.o SystemColors.o TextBlock.o TextBox.o Thickness.o Thumb.o ToggleButton.o UIElement.o Window.o

all: libSystem.Windows.a

rebuild: clean libSystem.Windows.a

libSystem.Windows.a: $(OBJS)
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
