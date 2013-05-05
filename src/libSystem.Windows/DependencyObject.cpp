#include <System/Windows/DependencyObject.h>

namespace System
{
	namespace Windows
	{
		DependencyObject::DependencyObject()
		{
		}

		void DependencyObject::ClearValue(const String& property)
		{
			if (dependencyProperties.ContainsKey(property))
			{
				// Because wrapper classes and other types may be passed in-place,
				// we explicitly destroy them as to prevent memory leaks.
				dependencyProperties[property]->~Object();
				
				// with the Object destroyed, we can now safely remove the entry.
				dependencyProperties.Remove(property);
			}
		}

		Object* DependencyObject::GetValue(const String& property)
		{
			Object* obj = NULL;
			
			dependencyProperties.TryGetValue(property, obj);
			
			return obj;
		}

		void DependencyObject::SetValue(const String& property, Object *value)
		{
			if (!dependencyProperties.ContainsKey(property))
				dependencyProperties.Add(property, value);
			else
				dependencyProperties[property] = value;
		}
	}
}
