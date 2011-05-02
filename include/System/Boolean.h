#ifndef _BOOLEAN_
#define _BOOLEAN_

namespace System
{
	struct Boolean
	{
	private:
		bool value;

	public:
		Boolean(const bool &obj); // Copy constructor

		static const char* True;
		static const char* False;

		char* ToString();
		static char* ToString(bool value);

		bool operator!=(bool right);
		bool operator!=(Boolean right);
		bool operator==(bool right);
		bool operator==(Boolean right);
		Boolean operator =(bool right);
		Boolean operator =(Boolean right);
	};
}

#endif //_BOOLEAN_
