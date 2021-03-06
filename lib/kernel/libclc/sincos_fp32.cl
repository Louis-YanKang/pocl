/*
 * Copyright (c) 2014 Advanced Micro Devices, Inc.
 *
 * Copyright (c) 2017 Michal Babej / Tampere University of Technology
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


_CL_OVERLOADABLE vtype sincos(vtype x, ADDRSPACE vtype *cosval)
{
    itype ix = as_itype(x);
    itype ax = ix & (itype)0x7fffffff;
    vtype dx = as_vtype(ax);

    vtype r0, r1;
    itype regn = __pocl_argReductionS(&r0, &r1, dx);

    vtype ss = __pocl_sinf_piby4(r0, r1);
    vtype cc = __pocl_cosf_piby4(r0, r1);
    vtype ss2 = as_vtype(as_itype(ss) ^ (itype)SIGNBIT_SP32);

    itype cond = (regn << 31);
    vtype s = cond ? cc : ss;
    vtype c = cond ? ss2 : cc;

    itype t = ((regn >> 1) << 31);
    c = as_vtype(as_itype(c) ^ t);

    itype mask = ((regn > (itype)1) ? (itype)SIGNBIT_SP32 : (itype)0);
    s = as_vtype(as_itype(s) ^ mask ^ (ix ^ ax));

    itype cond2 = (ax >= (itype)PINFBITPATT_SP32);
    c = cond2 ? as_vtype((utype)QNANBITPATT_SP32) : c;
    s = cond2 ? as_vtype((utype)QNANBITPATT_SP32) : s;

    itype infcond = (ax >= (itype)PINFBITPATT_SP32);
    s = infcond ? as_vtype((utype)QNANBITPATT_SP32) : s;
    c = infcond ? as_vtype((utype)QNANBITPATT_SP32) : c;

    //Subnormals
    s = (x == 0.0f) ? x : s;
    c = (x == 0.0f) ? (vtype)1.0f : c;

    *cosval = c;
    return s;
}
