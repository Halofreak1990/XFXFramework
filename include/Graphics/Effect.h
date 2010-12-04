#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <System.h>
#include <System/IO/Stream.h>
#include "Enums.h"
#include "EffectFunctionCollection.h"
#include "EffectPool.h"
#include "EffectParameterCollection.h"
#include "EffectTechnique.h"
#include "EffectTechniqueCollection.h"
#include "GraphicsDevice.h"

using namespace System;
using namespace System::IO;

namespace XFX
{
	namespace Graphics
	{
		/// <summary>
		/// Used to set and query effects and choose techniques.
		/// </summary>
		class Effect : public IDisposable
		{
		private:
			int _isDisposed;	
		
		protected:
			~Effect();
			Effect(GraphicsDevice &graphicsDevice, Effect &cloneSource);
		
			void Dispose(int disposing);
			
		public:
			String Creator();
			EffectTechnique CurrentTechnique;
			EffectPool EffectPool_();
			EffectFunctionCollection Functions();
			GraphicsDevice GraphicsDevice_();
			int IsDisposed();
			EffectParameterCollection Parameters();
			EffectTechniqueCollection Techniques();
		
			Effect(GraphicsDevice &graphicsDevice, byte effectCode[], CompilerOptions_t options, EffectPool &pool);
			Effect(GraphicsDevice &graphicsDevice, String &effectCodeFile, CompilerOptions_t options, EffectPool &pool);
			Effect(GraphicsDevice &graphicsDevice, Stream &effectCodeFileStream, CompilerOptions_t options, EffectPool &pool);
			Effect(GraphicsDevice &graphicsDevice, Stream &effectCodeFileStream, int numberBytes, CompilerOptions_t options, EffectPool &pool);
		
			void Begin();
			void Begin(SaveStateMode_t saveStateMode);
			virtual Effect Clone(GraphicsDevice &device);
			void CommitChanges();
			static CompiledEffect CompileEffectFromFile(String &effectFile, CompilerMacro preprocessorDefines[], CompilerIncludeHandler &includeHandler, CompilerOptions_t options, TargetPlatform_t &platform);
			static CompiledEffect CompileEffectFromFile(Stream &effectFileStream, int numberBytes, CompilerMacro preprocessorDefines[], CompilerIncludeHandler &includeHandler, CompilerOptions_t options, TargetPlatform_t platform);
			static CompiledEffect CompileEffectFromFile(Stream effectFileStream, CompilerMacro preprocessorDefines[], CompilerIncludeHandler &includeHandler, CompilerOptions_t options, TargetPlatform_t platform);
			static CompiledEffect CompileEffectFromSource(String effectFileSource, CompilerMacro preprocessorDefines[], CompilerIncludeHandler &includeHandler, CompilerOptions_t options, TargetPlatform_t platform);
			static String Disassemble(Effect &effect, int enableColorCode);
			String Disassemble(bool enableColorCode);
			void Dispose();
			void End();
			String ToString();
		};
	}
}

#endif //_EFFECT_H_
