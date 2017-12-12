#include "Operation.h"


Operation::Operation()
{
}


bool Operation::contain(set<tstring> mySet, tstring element) {
	if (mySet.find(element) != mySet.end())
		return true;
	else return false;
}

bool Operation::isLowPriority(tstring element) {
	if (contain(LOW_PRIORITY, element))
		return true;
	else return false;

}

bool Operation::isHighPriority(tstring element) {
	if (contain(HIGH_PRIORITY, element))
		return true;
	else return false;
}

bool Operation::isHighestPriority(tstring element) {
	if (contain(HIGHEST_PRIORITY, element))
		return true;
	else return false;
}

bool Operation::isOperation(tstring element) {
	if (isLowPriority(element) || isHighPriority(element) || isHighestPriority(element))
		return true;
	else if (element == OPBRÑK || element == CLBRÑK)
		return true;
	else return false;
}

bool Operation::isUnary(tstring element)
{
	if (contain(HIGHEST_PRIORITY, element))
		return true;
	else return false;
}

bool Operation::isBinary(tstring element)
{
	if ((contain(LOW_PRIORITY, element)) || (contain(HIGH_PRIORITY, element)))
		return true;
	else return false;
}

bool Operation::isFirstPriorityNotLowerThenSecond(tstring first, tstring second)
{
	if (isLowPriority(first))
		return true;
	else if (isHighestPriority(first) && isHighestPriority(second)) {
		return true;
	}
	else if (isHighPriority(first) && !isLowPriority(second)) {
		return true;
	}

	return false;
}

Operation::~Operation()
{
}
