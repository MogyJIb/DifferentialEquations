#include "ProcessorDE.h"

ProcessorDE::ProcessorDE()
{
}

void ProcessorDE::Eyler(Scale &scale)
{
	ProcessorRpn processorRpn = ProcessorRpn(scale.func);
	

	double xA = scale.xStart, xB = scale.xEnd,
		yA = scale.yStart,
		h = (xB - xA) / scale.count;

	double yk1 = yA, yk = yA, xk = xA, xk1 = xk, yEnd = yA, yStart = yA;


	for (int i = 0; xk < xB && i<2*scale.count-1; i+=2) {
		yk1 = yk + h*processorRpn.function(xk, yk);
		xk1 += h;

		scale.res[i] = xk1;
		scale.res[i + 1] = yk1;
		if (yk1 > yEnd)
			yEnd = yk1;
		if (yk1 < yStart)
			yStart = yk1;

		yk = yk1;
		xk = xk1;
	}


	scale.yB = yEnd;
	scale.yA = yStart;
}

void ProcessorDE::RungeKutta(Scale &scale)
{
	ProcessorRpn processorRpn = ProcessorRpn(scale.func);

	double xA = scale.xStart, xB = scale.xEnd,
		yA = scale.yStart,
		h = (xB - xA) / scale.count;

	double yk1 = yA, yk = yA, xk = xA, xk1 = xk, yEnd = yA,yStart=yA;

	double k1 = 0,k2 = 0,k3 = 0;


	for (int i=0; xk < xB && i<2*scale.count-1;i+=2) {

		
		k1 = h*processorRpn.function(xk, yk);
		k2 = h*processorRpn.function(xk + h / 2, yk + k1 / 2);
		k3 = h*processorRpn.function(xk + h, yk + 2 * k2 - k1);
		yk1 = yk + (k1 + 4 * k2 + k3) / 6;
		xk1 +=h;

		scale.res[i] = xk1;
		scale.res[i + 1] = yk1;
		if (yk1 > yEnd)
			yEnd = yk1;
		if (yk1 < yStart)
			yStart = yk1;

		yk = yk1;
		xk = xk1;

	}
		scale.yB = yEnd;
		scale.yA = yStart;
	
}


ProcessorDE::~ProcessorDE()
{
}
