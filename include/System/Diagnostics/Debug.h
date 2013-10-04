/*****************************************************************************
 *	Debug.h 																 *
 *																			 *
 *	System::Diagnostics::Debug class definition file.						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_DIAGNOSTICS_DEBUG_
#define _SYSTEM_DIAGNOSTICS_DEBUG_

namespace System
{
	class String;

	namespace Diagnostics
	{
		/**
		 * Provides a set of methods and properties that help debug your code. This class cannot be inherited.
		 */
		class Debug
		{
		private:
			Debug();

		public:
			/**
			 * Checks for a condition; if the condition is false, displays a message box that shows the call stack.
			 *
			 * @param condition
			 * The conditional expression to evaluate. If the condition is true, a failure message is not sent and the message box is not displayed.
			 */
			static void Assert(bool condition);
			/**
			 * Checks for a condition; if the condition is false, outputs a specified message and displays a message box that shows the call stack.
			 *
			 * @param condition
			 * The conditional expression to evaluate. If the condition is true, the message is not sent and the message box is not displayed.
			 *
			 * @param message
			 * Checks for a condition; if the condition is false, outputs a specified message and displays a message box that shows the call stack.
			 */
			static void Assert(bool condition, const String& message);
			/**
			 * Writes a formatted message followed by a line terminator to the attached debugger.
			 *
			 * @param format
			 * A composite format string that contains text intermixed with zero or more format items, which correspond to objects in the args array.
			 *
			 * @param args
			 * An object array containing zero or more objects to format.
			 */
			static void WriteLine(const String& format, ...);
		};
	}
}

#endif //_SYSTEM_DIAGNOSTICS_DEBUG_
