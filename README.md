# XFXFramework
## C++ implementation of XNA For XBOX

XFX, or [XNA](http://en.wikipedia.org/wiki/Microsoft_XNA) for [XBOX](http://en.wikipedia.org/wiki/Xbox_(console)) is an implementation of [XNA](http://en.wikipedia.org/wiki/Microsoft_XNA), written in C++ for Microsofts [XBOX](http://en.wikipedia.org/wiki/Xbox_(console)) console.
It's written on top of [OpenXDK](http://sourceforge.net/projects/openxdk/), the open source, free, legal XBOX Development Kit.

XFX is an attempt to bring development for the original [XBOX](http://en.wikipedia.org/wiki/Xbox_(console)) console to the masses by wrapping all low-level code in the familiar XNA classes.
Being written in C++ allows XFX to be lightweight and as close to the hardware as possible.

Compiling XFX requires at least OpenXDK version 0.7


As of this writing, XFX Contains the following libraries:
* libmscorlib		- Provides the necessary classes found in mscorlib.dll to support the other libraries
* libSystem			- Implements any types in the System.dll required by the other libs
* libSystem.Windows - A re-implementation of the System.Windows.dll found on Windows Phone, to allow the creation of GUI-driven applications
* libSystem.Xml		- Implements the functions found in System.Xml.dll
* libXFX			- Implements the functions found in Microsoft.Xna.Framework.dll
* libXFX.Game		- Implements the functions found in Microsoft.Xna.Framework.Game.dll
