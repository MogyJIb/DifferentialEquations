#pragma once
#include <list>
#include <stack>
#include "Operation.h"

using namespace std;

class Converter
{
private:
	Operation operation = Operation();

	list<tstring> makeOperandListFromString(const TCHAR* inputedString);

	void pushToFirstFromSecondStack(stack<tstring> &firstStack, stack<tstring> &secondStack);		//put top of one stack to another stack
	void emptyOperationStack(stack<tstring> &operationStack, stack<tstring> &operandStack);

	tstring processUnMinus(tstring s);
public:
	Converter();

	list<tstring> makeRpnOperandList(const TCHAR* inputedString);


	~Converter();
};

