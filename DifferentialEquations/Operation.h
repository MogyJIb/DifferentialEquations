#pragma once


#include <set> 
#include <tchar.h>
#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif


using namespace std;

#define MINUS _T("-")
#define PLUS _T("+")
#define DIV _T("/")
#define MUL _T("*")
#define SQRT _T("sqrt")
#define SIN _T("sin")
#define COS _T("cos")
#define TAN _T("tg")
#define POW _T("^")
#define LG _T("lg")
#define LN _T("ln")
#define OPBRÑK _T("(")
#define CLBRÑK _T(")")


class Operation
{
private:
	const  set<tstring> LOW_PRIORITY = { MINUS,PLUS };
	const  set<tstring> HIGH_PRIORITY = { DIV,MUL,POW };
	const  set<tstring> HIGHEST_PRIORITY = { SQRT,SIN, COS,TAN,LG ,LN };

	bool contain(set<tstring> mySet, tstring element);											//check if set contain the ellement

public:
	Operation();

	bool isLowPriority(tstring element);															//check if the operand is low priority
	bool isHighPriority(tstring element);														//check if the operand is high priority
	bool isHighestPriority(tstring element);
	bool isOperation(tstring element);
	bool isUnary(tstring element);
	bool isBinary(tstring element);
	bool isFirstPriorityNotLowerThenSecond(tstring first, tstring second);

	~Operation();
};

