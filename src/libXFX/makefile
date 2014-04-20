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
CCAS_FLAGS = -g -O2
CPP_FLAGS = -c -O2 -std=c++03 -Wall -nostdlib -fno-builtin -fno-rtti -fno-exceptions -march=i686 -mmmx -msse -mfpmath=sse $(SDLFLAGS)
INCLUDE  = -I$(PREFIX)/i386-pc-xbox/include -I$(PREFIX)/include -I$(PREFIX)/include/SDL -I../../include

CLINK = -nostdlib -fno-rtti -fno-exceptions
ALIGN = -Wl,--file-alignment,0x20 -Wl,--section-alignment,0x20 
SHARED = -shared
ENTRYPOINT = -Wl,--entry,_WinMainCRTStartup 
STRIP = -Wl,--strip-all
LD_FLAGS = $(CLINK) $(ALIGN) $(SHARED) $(ENTRYPOINT) $(STRIP)
LD_DIRS = -L$(PREFIX)/i386-pc-xbox/lib -L$(PREFIX)/lib -L$(XFX_PREFIX)/lib
LD_LIBS  = $(LD_DIRS) -lmscorlib -lm -lopenxdk -lhal -lc -lusb -lc -lxboxkrnl -lc -lhal -lxboxkrnl -lhal -lopenxdk -lc -lgcc -lstdc++

OBJS = BoundingBox.o BoundingFrustum.o BoundingSphere.o MathHelper.o Matrix.o Plane.o Point.o Quaternion.o Ray.o Rectangle.o Vector2.o Vector3.o Vector4.o
AUDIO_OBJS = SoundEffect.o SoundEffectInstance.o
#CONTENT_OBJS = ContentManager.o ContentReader.o
GAMERSERVICES_OBJS = Guide.o StorageDeviceAsyncResult.o
GRAPHICS_OBJS = BasicEffect.o BlendState.o Color.o DisplayMode.o DisplayModeCollection.o Effect.o GraphicsAdapter.o GraphicsDevice.o GraphicsResource.o IGraphicsDeviceService.o pbKit.o PresentationParameters.o Sprite.o SpriteBatch.o SpriteFont.o StateBlock.o Texture.o Texture2D.o TextureCollection.o VertexElement.o VertexPositionColor.o VertexPositionNormalTexture.o VertexPositionTexture.o Viewport.o
INPUT_OBJS = GamePad.o Keyboard.o Mouse.o
MEDIA_OBJS = VideoPlayer.o
NET_OBJS = PacketReader.o PacketWriter.o
STORAGE_OBJS = StorageContainer.o StorageDevice.o

OBJS1 = $(OBJS) $(AUDIO_OBJS) $(CONTENT_OBJS) $(GAMERSERVICES_OBJS) $(GRAPHICS_OBJS) $(INPUT_OBJS) $(MEDIA_OBJS) $(STORAGE_OBJS)

all: libXFX.a

rebuild: clean libXFX.a

libXFX.a: $(OBJS1)
	$(AR) $@ $(OBJS1)
	$(RANLIB) $@

.c.o:
	$(CC) -c $< $(CC_FLAGS) $(INCLUDE)

.cpp.o:
	$(CPP) -c $< $(CPP_FLAGS) $(INCLUDE)

.s.o:
	$(CCAS) -c $< $(CCAS_FLAGS)

clean: 
	rm -f *.o *.exe *.dll *.xbe *.cxbe *.lib *.a
	