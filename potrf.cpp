// lapack.cpp - Cholesky decomposition.
// Copyright (c) 2007 KALX, LLC. All rights reserved.
#include "xlllapack.h"

#ifndef CATEGORY
#define CATEGORY _T("LAPACK")
#endif

using namespace xll;

static AddInX xai_potrf(
	FunctionX(XLL_FPX, _T("?xll_potrf"), _T("POTRF"))
	.Arg(XLL_FPX, _T("Matrix"), _T("is the symmetric positive-definite matrix to be factored into C'C."))
	.Arg(XLL_BOOLX, _T("_Nofill"), _T("is an optional boolean value indicating lower half need not be filled with 0. "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Computes the upper Cholesky factorization of a symmetric (Hermitian) positive-definite matrix."))
	.Documentation(
		_T("This calls the LAPACK function <codeInline>DPOTRF</codeInline>. ")
		_T("LAPACK uses the lower triangular region of the matrix for stratch. ")
		_T("By default this function overwrites that with zeros. ")
	)
);
xfp* WINAPI
xll_potrf(xfp* pa, BOOL nofill)
{
#pragma XLLEXPORT
	static char u('L');

	try {
		ensure (pa->rows == pa->columns);

		int n = pa->rows;
		int info;

		DPOTRF(&u, &n, pa->array, &n, &info);

		ensure (info == 0);

		// fill in lower portion with zeros
		if (!nofill)
			for (xword i = 1; i < n; ++i)
				memset(pa->array + i*n, 0, i*sizeof(double));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return pa;
}

#ifdef _DEBUG
#ifndef EXCEL12

int
test_potrf(void)
{
	try {
		OPERX o = ExcelX(xlfEvaluate, OPERX(_T("POTRF({3,2;2,3})")));
		OPERX m = ExcelX(xlfMmult, ExcelX(xlfTranspose, o), o);
		ensure (fabs(m(0,0) - 3) < 1e-15);
		ensure (fabs(m(0,1) - 2) < 1e-15);
		ensure (fabs(m(1,0) - 2) < 1e-15);
		ensure (fabs(m(1,1) - 3) < 1e-15);

	}	
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfter> xoa_test_potrf(test_potrf);

#endif
#endif // _DEBUG
