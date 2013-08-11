/*****************************************************************************
 *	ReadOnlyCollection.h													 *
 *																			 *
 *	System::Collections::ObjectModel::ReadOnlyCollection definition file	 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _SYSTEM_COLLECTIONS_OBJECTMODEL_READONLYCOLLECTION_
#define _SYSTEM_COLLECTIONS_OBJECTMODEL_READONLYCOLLECTION_

#include <System/Collections/Generic/List.h>

using namespace System::Collections::Generic;

namespace System
{
	namespace Collections
	{
		namespace ObjectModel
		{
			/**
			 * Provides the base class for a generic read-only collection.
			 */
			template <typename T>
			class ReadOnlyCollection : public IEnumerable<T>
			{
			private:
				IList<T>* items;

			public:
				/**
				 * Gets the number of elements contained in the System::Collections::ObjectModel::ReadOnlyCollection<T> instance.
				 *
				 * @return
				 * The number of elements contained in the System::Collections::ObjectModel::ReadOnlyCollection<T> instance.
				 */
				inline int Count() const { return items->Count(); }
				/**
				 * Returns the System::Collections::Generic::IList<T> that the System::Collections::ObjectModel::ReadOnlyCollection<T> wraps.
				 *
				 * @return
				 * The System::Collections::Generic::IList<T> that the System::Collections::ObjectModel::ReadOnlyCollection<T> wraps.
				 */
				inline IList<T> const * const getItems() const { return items; }

				/**
				 * Initializes a new instance of the System::Collections::ObjectModel::ReadOnlyCollection<T> class that is a read-only wrapper around the specified list.
				 *
				 * @param list
				 * The list to wrap.
				 */
				ReadOnlyCollection(IList<T> * const list)
					: items(list)
				{
				}

				/**
				 * Determines whether an element is in the System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 *
				 * @param item
				 * The object to locate in the System::Collections::ObjectModel::ReadOnlyCollection<T>. The value can be null for reference types.
				 *
				 * @return
				 * true if value is found in the System::Collections::ObjectModel::ReadOnlyCollection<T>; otherwise, false.
				 */
				inline bool Contains(const T& item) const
				{
					return items->Contains(item);
				}

				/**
				 * Copies the entire System::Collections::ObjectModel::ReadOnlyCollection<T> to a compatible one-dimensional System::Array, starting at the specified index of the target array.
				 *
				 * @param array
				 * The one-dimensional System::Array that is the destination of the elements copied from System::Collections::ObjectModel::ReadOnlyCollection<T>. The System::Array must have zero-based indexing.
				 *
				 * @param index
				 * The zero-based index in array at which copying begins.
				 */
				inline void CopyTo(T array[], int index) const
				{
					items->CopyTo(array, index);
				}

				/**
				 * Returns an enumerator that iterates through the System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 *
				 * @return
				 * An System::Collections::Generic::IEnumerator<T> for the System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 */
				inline IEnumerator<T>* GetEnumerator()
				{
					return items->GetEnumerator();
				}

				/**
				 * Searches for the specified object and returns the zero-based index of the first occurrence within the entire System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 *
				 * @param item
				 * The object to locate in the System::Collections::Generic::List<T>. The value can be null for reference types.
				 *
				 * @return
				 * The zero-based index of the first occurrence of item within the entire System::Collections::ObjectModel::ReadOnlyCollection<T>, if found; otherwise, -1.
				 */
				inline int IndexOf(const T& item) const
				{
					return items->IndexOf(item);
				}

				/**
				 * Gets the element at the specified index.
				 *
				 * @param index
				 * The zero-based index of the element to get.
				 *
				 * @return
				 * The element at the specified index.
				 */
				inline T& operator[](int index) const { return *items[index]; }
			};

			///////////////////////////////////////////////////////////////////

			template <typename T>
			class ReadOnlyCollection<T *> : public IEnumerable<T *>
			{
			private:
				IList<T *>* items;

			public:
				/**
				 * Gets the number of elements contained in the System::Collections::ObjectModel::ReadOnlyCollection<T> instance.
				 *
				 * @return
				 * The number of elements contained in the System::Collections::ObjectModel::ReadOnlyCollection<T> instance.
				 */
				inline int Count() const { return items->Count(); }
				/**
				 * Returns the System::Collections::Generic::IList<T> that the System::Collections::ObjectModel::ReadOnlyCollection<T> wraps.
				 *
				 * @return
				 * The System::Collections::Generic::IList<T> that the System::Collections::ObjectModel::ReadOnlyCollection<T> wraps.
				 */
				inline IList<T *> const * const getItems() const { return items; }

				/**
				 * Initializes a new instance of the System::Collections::ObjectModel::ReadOnlyCollection<T> class that is a read-only wrapper around the specified list.
				 *
				 * @param list
				 * The list to wrap.
				 */
				ReadOnlyCollection(IList<T *> * const list)
					: items(list)
				{
				}

				/**
				 * Determines whether an element is in the System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 *
				 * @param item
				 * The object to locate in the System::Collections::ObjectModel::ReadOnlyCollection<T>. The value can be null for reference types.
				 *
				 * @return
				 * true if value is found in the System::Collections::ObjectModel::ReadOnlyCollection<T>; otherwise, false.
				 */
				inline bool Contains(const T* item) const
				{
					return items->Contains(item);
				}

				/**
				 * Copies the entire System::Collections::ObjectModel::ReadOnlyCollection<T> to a compatible one-dimensional System::Array, starting at the specified index of the target array.
				 *
				 * @param array
				 * The one-dimensional System::Array that is the destination of the elements copied from System::Collections::ObjectModel::ReadOnlyCollection<T>. The System::Array must have zero-based indexing.
				 *
				 * @param index
				 * The zero-based index in array at which copying begins.
				 */
				inline void CopyTo(T* array[], int index) const
				{
					items->CopyTo(array, index);
				}

				/**
				 * Returns an enumerator that iterates through the System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 *
				 * @return
				 * An System::Collections::Generic::IEnumerator<T> for the System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 */
				inline IEnumerator<T *>* GetEnumerator()
				{
					return items->GetEnumerator();
				}

				/**
				 * Searches for the specified object and returns the zero-based index of the first occurrence within the entire System::Collections::ObjectModel::ReadOnlyCollection<T>.
				 *
				 * @param item
				 * The object to locate in the System::Collections::Generic::List<T>. The value can be null for reference types.
				 *
				 * @return
				 * The zero-based index of the first occurrence of item within the entire System::Collections::ObjectModel::ReadOnlyCollection<T>, if found; otherwise, -1.
				 */
				inline int IndexOf(const T* item) const
				{
					return items->IndexOf(item);
				}

				/**
				 * Gets the element at the specified index.
				 *
				 * @param index
				 * The zero-based index of the element to get.
				 *
				 * @return
				 * The element at the specified index.
				 */
				inline T* operator[](int index) const { return *items[index]; }
			};
		}
	}
}

#endif //_SYSTEM_COLLECTIONS_OBJECTMODEL_READONLYCOLLECTION_
