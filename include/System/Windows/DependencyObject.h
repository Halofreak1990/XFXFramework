#pragma once

#include <System/Collections/Generic/Dictionary.h>

using namespace System::Collections::Generic;

namespace System
{
	namespace Windows
	{
		// Represents an object that participates in the dependency property system.
		class DependencyObject
		{
		private:
			Dictionary<String, Object*> dependencyProperties;

		protected:
			DependencyObject();

		public:
			void ClearValue(const String& property);
			// Returns the Object stored in the property, or NULL if the property did not exist.
			Object* GetValue(const String& property) const;
			void SetValue(const String& property, Object* value);
		};
	}
}
