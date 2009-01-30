/*
Copyright 2005, 2006 Computer Vision Lab, 
Ecole Polytechnique Federale de Lausanne (EPFL), Switzerland. 
All rights reserved.

This file is part of BazAR.

BazAR is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

BazAR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
BazAR; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/
#ifndef PROSAC_FUNCTION_TYPES_H
#define PROSAC_FUNCTION_TYPES_H

typedef bool (*prosac_function_20scalars)(ls_minimizer_type * state, 
                                          ls_minimizer_type s0, ls_minimizer_type s1, ls_minimizer_type s2, ls_minimizer_type s3, ls_minimizer_type s4, 
                                          ls_minimizer_type s5, ls_minimizer_type s6, ls_minimizer_type s7, ls_minimizer_type s8, ls_minimizer_type s9, 
                                          ls_minimizer_type s10, ls_minimizer_type s11, ls_minimizer_type s12, ls_minimizer_type s13, ls_minimizer_type s14, 
                                          ls_minimizer_type s15, ls_minimizer_type s16, ls_minimizer_type s17, ls_minimizer_type s18, ls_minimizer_type s19, 
                                          void ** user_data);

#endif // PROSAC_FUNCTION_TYPES_H
