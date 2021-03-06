// syev.cpp - Singular value decomposition
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty made.
#include <vector>
#include "xlllapack.h"

#ifndef CATEGORY
#define CATEGORY _T("LAPACK")
#endif

using namespace xll;
using std::vector;

static AddInX xai_syev(
	FunctionX(XLL_FPX, _T("?xll_syev"), _T("SYEV"))
	.Arg(XLL_FPX, _T("Matrix"), _T("is a symmetric matrix. Only the upper triangular values are used in the calculation"))
	.Arg(XLL_BOOLX, _T("_Eigenvectors"), _T("is an optional boolean indicating whether eigenvectors are to be computed"))
	.Arg(XLL_BOOLX, _T("_Lower"), _T("is an optional boolean indicating whether lower triangular values are to be used "))
	.Category(CATEGORY)
	.FunctionHelp(_T("Computes the eigenvalues and optionally the eigenvectors of a symmetric (Hermitian) matrix."))
	.Documentation(
		_T("This calls the LAPACK function <codeInline>DSYEV</codeInline>.")
	)
);
xfp* WINAPI
xll_syev(xfp* pa, BOOL vn, BOOL ul)
{
#pragma XLLEXPORT
	static FPX w;

	try {
		ensure (pa->rows == pa->columns);

		char jobz = vn ? 'V' : 'N';
		char uplo = ul ? 'U' : 'L'; // L - means upper
		int la = pa->rows;
		int lwork;
		int info;
		w.reshape(1 + (vn == TRUE)*pa->rows, pa->columns);

		// workspace query
		double size;
		lwork = -1;
		DSYEV(&jobz, &uplo, &la, pa->array, &la, &w[0], &size, &lwork, &info);
		lwork = static_cast<int>(size);
		vector<double> work(lwork);

		DSYEV(&jobz, &uplo, &la, pa->array, &la, &w[0], &work[0], &lwork, &info);
		if (vn) {
			std::copy(begin(*pa), end(*pa), &w[0] + la);
		}

		ensure (info == 0);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return w.get();
}
