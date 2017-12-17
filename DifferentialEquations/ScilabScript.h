#pragma once
#include <tchar.h>
#include <string>
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif


class ScilabScript
{
private:
	
	
public:
	ScilabScript();
	tstring generate(tstring func, tstring x0, tstring y0, tstring xN);
	~ScilabScript();
};

