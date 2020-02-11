#include "Util.h"



Util::Util()
{
}


Util::~Util()
{
}

wchar_t * Util::string2wct(string str)
{
	wstring widstr = std::wstring(str.begin(), str.end());
	const wchar_t *pwidstr = widstr.c_str();
	return const_cast<wchar_t *>(pwidstr);
}
