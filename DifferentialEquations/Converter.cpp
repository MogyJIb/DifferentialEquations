#include "Converter.h"



Converter::Converter()
{
}



list<tstring> Converter::makeRpnOperandList(const TCHAR* inputedString) {
	list<tstring> operandList = makeOperandListFromString(inputedString);

	//operands stack
	stack<tstring> operandStack;

	//operations stack
	stack<tstring> operationStack;

	//go from item to item and make operand stack
	for (tstring operand : operandList) {

		//if this operand is close bracket
		if (operand == CLBRÑK) {

			//push all operands from operation stack to operand stack while 
			//stack is empty or open bracket found
			while (!operationStack.empty()) {
				if (operationStack.top() == OPBRÑK)
				{
					operationStack.pop();
					break;
				}
				pushToFirstFromSecondStack(operandStack, operationStack);
			}
		}
		else {
			if (operation.isOperation(operand)) {
				if (!operationStack.empty() && operation.isFirstPriorityNotLowerThenSecond(operand, operationStack.top()))
					emptyOperationStack(operationStack, operandStack);
				operationStack.push(operand);
			}
			else
				operandStack.push(operand);
		}
	}

	//push all operands from operation stack to operand stack while stack is empty
	emptyOperationStack(operationStack, operandStack);

	//make list of operand and return it
	list<tstring> rpnOperandList;
	while (!operandStack.empty()) {
		rpnOperandList.push_front(operandStack.top());
		operandStack.pop();
	}



	return rpnOperandList;
}

list<tstring> Converter::makeOperandListFromString(const TCHAR* inputedString) {
	tstring processedString = processUnMinus(inputedString);

	list<tstring> operandList;

	//if string is empty return empty list
	if (processedString.empty())
		return operandList;

	//string length
	int strLength = processedString.length();

	//and next previous char in string
	char prevCh = processedString[0], thisCh;

	//operand (chars list) to add to operand list
	tstring operand;
	operand += (prevCh);

	//go from char to char while string end
	for (int i = 1; i < strLength; i++) {

		thisCh = processedString[i];

	
		//if the previous and next are number
		if ((_istdigit(prevCh) || (prevCh == _T('.')))
			&& (_istdigit(thisCh) || (thisCh == _T('.'))))
			operand += (thisCh);

		//if the previous and next are alpha
		else if (_istalpha(prevCh) && _istalpha(thisCh))
			operand += (thisCh);

		//if the other char
		else {
			operandList.push_back(operand);
			operand.clear();
			operand += (thisCh);
		}


		prevCh = thisCh;
	}
	operandList.push_back(operand);

	return operandList;
}


void Converter::pushToFirstFromSecondStack(stack<tstring> &firstStack, stack<tstring> &secondStack) {
	if (!secondStack.empty()) {
		firstStack.push(secondStack.top());
		secondStack.pop();
	}
}

void Converter::emptyOperationStack(stack<tstring> &operationStack, stack<tstring> &operandStack) {
	while (!operationStack.empty()) {
		if (operationStack.top() == OPBRÑK) {
			break;
		}
		pushToFirstFromSecondStack(operandStack, operationStack);
	}
}

tstring Converter::processUnMinus(tstring str)
{

	tstring result = tstring(str);

	if (str[0] == _T('-')) {
		result = tstring(_T("0-")).append(str.substr(1, str.length() - 1));
		str = tstring(result);
	}

	int pos = 0;
	while ((pos = str.find(_T("(-"))) >= 0) {
		result = (str.substr(0, pos)).append(_T("(0-")).append(str.substr(pos + 2, str.length() - 1));
		str = tstring(result);
	}


	return result;
}

Converter::~Converter()
{
}
