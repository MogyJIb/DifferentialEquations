#pragma once

#include <string>
#include <winstring.h>

#ifdef _UNICODE
#define to_tstring(x) std::to_wstring(x);
#else
#define to_tstring(x) std::to_string(x);
#endif

#include "Operation.h"
#include "Converter.h"

using namespace std;

class ProcessorRpn
{
private:
	list<tstring> rpnOperandList;

	Operation operationProcessor = Operation();
	Converter converter = Converter();
	void makeOperation(stack<double> &numberStack, tstring operation);
	void changeChar(list<tstring> &rpnOperandList, tstring ch, double xNumber);

	double processRpnExpression(list<tstring> rpnOperandList);
	bool isZeroString(tstring str);
public:
	

	ProcessorRpn(TCHAR* expression);


	double makeUnOperation(double firstOper, tstring operation);
	double makeBinOperation(double firstOper, double secondOper, tstring operation);
	double function();
	double function(double point);
	double function(double x, double z);

	~ProcessorRpn();
};

