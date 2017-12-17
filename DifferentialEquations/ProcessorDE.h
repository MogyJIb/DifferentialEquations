#pragma once

#include "ProcessorRpn.h"

#include "Scale.h"
#include <cmath>

class ProcessorDE
{
public:
	ProcessorDE();

	void RungeKutta( Scale &scale);
	void Eyler( Scale &scale);

	~ProcessorDE();
};

