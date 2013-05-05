
namespace System
{
	// Represents an object whose underlying type is a value type that can also be assigned null like a reference type.
	template <typename T>
	class Nullable
	{
	private:
		T* data;

	public:
		static const Nullable<T> Null;

		Nullable()
			: data(null)
		{
		}

		Nullable(const T& newData)
			: data(const_cast<T*>(&newData))
		{
		}

		Nullable(const Nullable<T> &obj)
			: data(obj.data)
		{
		}

		bool HasValue() const { return (data != null); }
		T getValue() const { return *data; }

		operator T() const { return *data; }
	};

	template <typename T>
	const Nullable<T> Nullable<T>::Null = Nullable<T>();
}
