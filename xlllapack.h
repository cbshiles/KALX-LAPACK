// xlllapack.h - Header file for LAPACK routines.
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#define EXCEL12
#define HAVE_LAPACK_CONFIG_H
#define LAPACK_COMPLEX_STRUCTURE
//extern "C" {
#include "include/lapacke.h"
//}
#include "../xll8/xll/xll.h"

#define CATEGORY _T("LAPACK")

typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xfp xfp;

