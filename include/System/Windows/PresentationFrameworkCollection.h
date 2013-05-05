#pragma once

#include <System/Collections/Generic/List.h>
#include <sassert.h>

using namespace System::Collections::Generic;

namespace System
{
	namespace Windows
	{
		template <typename T>
		class PresentationFrameworkCollection : public IList<T>
		{
		private:
			List<T> _items;

		protected:
			PresentationFrameworkCollection();

		public:
			int Count() const;
			bool IsReadOnly() const;

			void Add(const T& item);
			void Clear();
			bool Contains(const T& item) const;
			void CopyTo(T array[], const int index) const;
			int IndexOf(const T& item) const;
			void Insert(const int index, const T& item);
			bool Remove(const T& item);
			void RemoveAt(const int index);

			T& operator[](const int index);
		};

		///////////////////////////////////////////////////////////////////////

		template <typename T>
		int PresentationFrameworkCollection<T>::Count() const
		{
			return _items.Count();
		}

		template <typename T>
		bool PresentationFrameworkCollection<T>::IsReadOnly() const
		{
			return _items.IsReadOnly();
		}
		
		template <typename T>
		void PresentationFrameworkCollection<T>::Add(const T& item)
		{
			_items.Add(item);
		}

		template <typename T>
		void PresentationFrameworkCollection<T>::Clear()
		{
			_items.Clear();
		}

		template <typename T>
		bool PresentationFrameworkCollection<T>::Contains(const T& item) const
		{
			return (IndexOf(item) != -1);
		}

		template <typename T>
		void PresentationFrameworkCollection<T>::CopyTo(T array[], const int index) const
		{
			_items.CopyTo(array, index);
		}

		template <typename T>
		int PresentationFrameworkCollection<T>::IndexOf(const T& item) const
		{
			return _items.IndexOf(item);
		}

		template <typename T>
		void PresentationFrameworkCollection<T>::Insert(const int index, const T& item)
		{
			_items.Insert(index, item);
		}

		template <typename T>
		bool PresentationFrameworkCollection<T>::Remove(const T& item)
		{
			int itemIndex = IndexOf(item);

			if (itemIndex == -1)
				return false;

			RemoveAt(itemIndex);
			return true;
		}

		template <typename T>
		void PresentationFrameworkCollection<T>::RemoveAt(const int index)
		{
			_items.RemoveAt(index);
		}

		template <typename T>
		T& PresentationFrameworkCollection<T>::operator[](const int index)
		{
			return _items[index];
		}
	}
}
