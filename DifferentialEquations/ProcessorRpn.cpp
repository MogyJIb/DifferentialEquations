#include "ProcessorRpn.h"



#define WRONG_STRING_INPUT_EXCEPTION 1

ProcessorRpn::ProcessorRpn(TCHAR* expression)
{
	 rpnOperandList = converter.makeRpnOperandList(expression);	
}



double ProcessorRpn::processRpnExpression(list<tstring> rpnOperandList) {

	stack<double> processingStack;

	for (tstring operand : rpnOperandList) {
		if (operationProcessor.isOperation(operand)) {
			makeOperation(processingStack, operand);
		}
		else {

			double res = 0;
			if (!isZeroString(operand)) {
				res = _ttof(operand.data());
				if (res == 0)
					throw WRONG_STRING_INPUT_EXCEPTION;
			}
			processingStack.push(res);
		}

	}
	if (processingStack.size()<1)
		throw WRONG_STRING_INPUT_EXCEPTION;
	double res = processingStack.top();
	return res;
}

void ProcessorRpn::makeOperation(stack<double> &numberStack, tstring operation) {
	if (operationProcessor.isBinary(operation)) {
		if (numberStack.size()<2)
			throw WRONG_STRING_INPUT_EXCEPTION;
		double secondOper = numberStack.top();
		numberStack.pop();
		double firstOper = numberStack.top();
		numberStack.pop();

		numberStack.push(makeBinOperation(firstOper, secondOper, operation));
	}
	else if (operationProcessor.isUnary(operation)) {
		if (numberStack.size()<1)
			throw WRONG_STRING_INPUT_EXCEPTION;
		double firstOper = numberStack.top();
		numberStack.pop();

		numberStack.push(makeUnOperation(firstOper, operation));
	}
	else throw WRONG_STRING_INPUT_EXCEPTION;
}

void ProcessorRpn::changeChar(list<tstring> &rpnOperandList, tstring ch, double xNumber)
{
	for (list<tstring>::iterator iter = rpnOperandList.begin(); iter != rpnOperandList.end(); ++iter)
	{
		if (*iter == ch)
			*iter = to_tstring(xNumber);
	}

}


double ProcessorRpn::makeUnOperation(double firstOper, tstring operation) {
	if (!operation.compare(COS)) {
		double res = 0;
		_asm {
			fld firstOper;
			fcos;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(SIN)) {
		double res = 0;
		_asm {
			fld firstOper;
			fsin;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(TAN)) {
		double res = 0;
		_asm {
			fld firstOper;
			fptan;
			fstp res;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(LG)) {
		double res = 0;
		double ten = 10;
		_asm {
			fld1;			// push 1
			fld firstOper;
			fyl2x;			// 1 * log2(x)
			fld1;			// push 1
			fld ten;		// push log2(10)
			fyl2x;
			fdiv;			// log2(x) / log2(10)
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(SQRT)) {
		double res = 0;
		_asm {
			fld firstOper;
			fsqrt;
			fstp res;
		}
		return res;
	}
	else throw WRONG_STRING_INPUT_EXCEPTION;
}

double ProcessorRpn::makeBinOperation(double firstOper, double secondOper, tstring operation) {
	if (!operation.compare(PLUS)) {
		double res = 0;
		_asm {
			fld firstOper;
			fadd secondOper;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(MINUS)) {
		double res = 0;
		_asm {
			fld firstOper;
			fsub secondOper;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(MUL)) {
		double res = 0;
		_asm {
			fld firstOper;
			fmul secondOper;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(DIV)) {
		double res = 0;
		_asm {
			fld firstOper;
			fdiv secondOper;
			fstp res;
		}
		return res;
	}
	else if (!operation.compare(POW)) {
		double res = 1, sign = 1, minus = -1, two = 2, isMinus = 0, tmp;
		//x^y
		_asm {
			fld firstOper	//load X
			fldz			//load 0
			fcomip st(0), st(1)     // check X is minus
			jb mPlusNumber

			fld secondOper;	//load Y
			fabs				// abs(Y)
				fld secondOper	//load Y
				fabs				// abs(Y)
				frndint			// round(Y)
				fsub				// Y - round(Y)
				fldz				//load 0	
				fcomip st(0), st(1)	//check X is integer 
				fstp tmp				//clear stack
				jb mPlusNumber

				fld firstOper; //load X
			fchs			//abs(X)

				fldz				//load 0
				fld two				//load 2
				fld secondOper;			//load Y
			fabs					//abs(Y)
				fprem					//Y%2
				fxch st(1)			//clear stack
				fstp tmp
				fcomip st(0), st(1)		//check Y is odd or even
				fstp tmp
				je mPlusNumber
				fld minus			//set sign as minus	
				fstp sign

				mPlusNumber :
			fld secondOper			//load Y
				fxch st(1)				//change place Y and X (x - st(0); y - st(1))
				fyl2x					// y*log2(X) 
				fld st(0)				//load   y*log2(X) = t
				frndint					//round(t) 
				fld st(0)				//load   t
				fsubr st(0), st(2)		//t- round(t)
				f2xm1					//  2 ^ t - 1 
				fld1;					//load 1
			fadd;					//add 1
			fscale;					//  x * 2 ^ y 
			fld sign				//load sign = (1 or -1)
				fmul					// st(0) * sing
				fstp res				//clear stack
				fstp tmp				//clear stack
				fstp tmp				//clear stack
				fstp tmp				//clear stack
				fstp tmp				//clear stack

		}
		return res;
	}
	else throw WRONG_STRING_INPUT_EXCEPTION;
}

double ProcessorRpn::function()
{
	double res = processRpnExpression(rpnOperandList);
	return res;
}

double ProcessorRpn::function(double point)
{
	list<tstring> tmp = list<tstring>(rpnOperandList);
	changeChar(tmp, _T("x"),point);
	double res = processRpnExpression(tmp);
	return res;
}

double ProcessorRpn::function(double x, double y)
{
	list<tstring> tmp = list<tstring>(rpnOperandList);
	changeChar(tmp, _T("x"), x);
	changeChar(tmp, _T("y"), y);
	double res = processRpnExpression(tmp);
	return res;
}

bool  ProcessorRpn::isZeroString(tstring str) {
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) != _T('0') && str.at(i) != _T('.') && str.at(i) != _T('-'))
			return false;
	}
	return true;
}


ProcessorRpn::~ProcessorRpn()
{
}
