/*****************************************************************************
 *	DependencyObject.h														 *
 *																			 *
 *	System::Windows::DependencyObject definition file						 *
 *	Copyright (c) XFX Team. All rights reserved								 *
 *****************************************************************************/
#ifndef _SYSTEM_WINDOWS_DEPENDENCYOBJECT_
#define _SYSTEM_WINDOWS_DEPENDENCYOBJECT_

#include <System/Collections/Generic/Dictionary.h>
#include "DependencyProperty.h"

using namespace System::Collections::Generic;

namespace System
{
	namespace Windows
	{
		/**
		 * Represents an object that participates in the dependency property system.
		 */
		class DependencyObject : public Object
		{
		private:
			Dictionary<String, Object *> dependencyProperties;

		protected:
			DependencyObject();

		public:
			template <typename T>
			void ClearValue(DependencyProperty<T> p)
			{
				if (dependencyProperties.ContainsKey(p.Name))
				{
					// Because wrapper classes and other types may be passed in-place,
					// we explicitly destroy them as to prevent memory leaks.
					dependencyProperties[p]->~Object();
				
					// with the Object destroyed, we can now safely remove the entry.
					dependencyProperties.Remove(p);
				}
			}

			static const Type& GetType();

			template <typename T>
			T GetValue(DependencyProperty<T> p) const
			{
				return *dependencyProperties[p.Name];
			}

			template <typename T>
			T *GetValue(DependencyProperty<T *> p) const
			{
				return dependencyProperties[p.Name];
			}

			template <typename T>
			void SetValue(DependencyProperty<T> p, const T value)
			{
				if (!dependencyProperties.ContainsKey(p.Name))
					dependencyProperties.Add(p.Name, value);
				else
					dependencyProperties[p.Name] = value;
			}

			template <typename T>
			void SetValue(DependencyProperty<T *> p, T * const value)
			{
				if (!dependencyProperties.ContainsKey(p.Name))
					dependencyProperties.Add(p.Name, value);
				else
					dependencyProperties[p.Name] = value;
			}
		};
	}
}

#endif //_SYSTEM_WINDOWS_DEPENDENCYOBJECT_
