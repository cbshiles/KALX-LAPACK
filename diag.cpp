// diag.cpp - diagonal matrix
#include "xlllapack.h"

using namespace xll;

static AddInX xai_diag(
	FunctionX(XLL_FPX, _T("?xll_diag"), _T("DIAG"))
	.Arg(XLL_FPX, _T("Vector"), _T("is a vector. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a matrix having Vector for the diagonal."))
	.Documentation()
);
xfp* WINAPI
xll_diag(const xfp* pd)
{
#pragma XLLEXPORT
	static FPX d;

	try {
		d.reshape(size(*pd), size(*pd));
		std::fill(d.begin(), d.end(), 0);
		for (xword i = 0; i < size(*pd); ++i)
			d(i, i) = pd->array[i];
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return d.get();
}