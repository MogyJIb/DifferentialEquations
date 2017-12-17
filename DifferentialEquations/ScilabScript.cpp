#include "ScilabScript.h"



ScilabScript::ScilabScript()
{
}

tstring ScilabScript::generate(tstring func,tstring x0, tstring y0, tstring xN)
{
	tstring script = tstring(_T("function ydot=f(x, y); ydot = "))
		.append(func.data())
		.append(_T("; endfunction; y0 = "))
		.append(y0.data())
		.append(_T("; x0 = "))
		.append(x0.data())
		.append(_T("0; x = "))
		.append(x0.data())
		.append(_T(":0.01:"))
		.append(xN.data())
		.append(_T("; y = ode(y0, x0, x, f); plot(x, y); xgrid(); xtitle('Численное интегрирование', 'X', 'Y'); "));
	return script;
}


ScilabScript::~ScilabScript()
{
}
