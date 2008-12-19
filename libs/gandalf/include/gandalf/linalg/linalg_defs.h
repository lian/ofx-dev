/**
 * File:          $RCSfile: linalg_defs.h,v $
 * Module:        Miscellaneous linear algebra package stuff
 * Part of:       Gandalf Library
 *
 * Revision:      $Revision: 1.9 $
 * Last edited:   $Date: 2005/05/21 22:11:18 $
 * Author:        $Author: pm $
 * Copyright:     (c) 2000 Imagineer Software Limited
 */

/* This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _GAN_LINALG_DEFS_H
#define _GAN_LINALG_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup LinearAlgebra
 * \{
 */

/**
 * \defgroup GeneralSizeMatVec General Size Matrices and Vectors
 * \{
 */

/**
 * \defgroup GeneralSizeMatrix General Size Matrices
 * \{
 */

/* start other groups */

/**
 * \defgroup GeneralSizeMatrixAccessElement Access an Element of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixThreshold Threshold Elements of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixEigen Eigendecomposition of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixTest Test a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixNorms Norms of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixInvert Invert a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixFill Fill a General Size Matrix with Values
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixRead Read Elements of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixCopy Copy a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixScale Multiply/Divide a General Size Matrix by a Scalar
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixTranspose Transpose a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixAdd Add General Size Matrices
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixSubtract Subtract General Size Matrices
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixVectorProduct General Size Matrix/Vector Product
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixMatrixProduct General Size Matrix/Matrix Product
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixInsert Insert Part of a General Size Matrix in Another
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixExtract Extract Part of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixIO General Size Matrix I/O
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixSet Set Attributes of a General Size Matrix
 * \{
 */

/**
 * \}
 */

/**
 * \defgroup GeneralSizeMatrixSize Get Dimensions of General Size Matrix
 * \{
 */

/**
 * \}
 */

/* definitions used by linear algebra package */

/// Whether or not matrix is (to be) transposed
typedef enum
{
   /// Don't transpose matrix
   GAN_NOTRANSPOSE=0,

   /// Do transpose matrix
   GAN_TRANSPOSE=1
}
Gan_TposeFlag;

/// Whether or not matrix is (to be) inverted
typedef enum
{
   /// Don't invert matrix
   GAN_NOINVERT=0,

   /// Do invert matrix
   GAN_INVERT=1
} Gan_InvertFlag;

/// Whether matrix is upper or lower triangular
typedef enum
{
   /// Lower-triangular matrix
   GAN_MATRIXPART_LOWER,

   /// Upper-triangular matrix
   GAN_MATRIXPART_UPPER,

   /// Whole matrix
   GAN_MATRIXPART_WHOLE
} Gan_LapackUpLoFlag;

/// Matrix storage type
typedef enum
{
    /// Full matrix
    GAN_MATSTORAGE_FULL,

    /// Lower triangular matrix   
    GAN_MATSTORAGE_LOWERTRIANGULAR,

    /// Upper triangular matrix   
    GAN_MATSTORAGE_UPPERTRIANGULAR,

    /// Upper Hessenberg matrix
    GAN_MATSTORAGE_UPPERHESSENBERG,

    /// A is a symmetric band matrix with the only the lower half stored.   
    GAN_MATSTORAGE_SYMMBANDLOWER,

    /// A is a symmetric band matrix with the only the upper half stored.   
    GAN_MATSTORAGE_SYMMBANDUPPER,

    /// A is a band matrix
    GAN_MATSTORAGE_BAND
} Gan_LapackMatStorage;

/// Whether triangular matrix is unit along the diagonal
typedef enum
{
   /// Not a unit triangular matrix
   GAN_NOUNIT=0,

   /// Unit triangular matrix
   GAN_UNIT=1
} Gan_LapackUnitFlag;

/// Type of test in lamch functions
typedef enum Gan_LapackLamchFlag
{
    /// relative machine precision
    GAN_LAMCH_EPS,

    /// safe minimum, such that 1/sfmin does not overflow
    GAN_LAMCH_SFMIN,

    /// base of the machine
    GAN_LAMCH_BASE,

    /// eps*base
    GAN_LAMCH_PREC,

    /// number of (base) digits in the mantissa
    GAN_LAMCH_T,

    /// 1.0 when rounding occurs in addition, 0.0 otherwise
    GAN_LAMCH_RND,

    /// minimum exponent before (gradual) underflow
    GAN_LAMCH_EMIN,

    /// underflow threshold - base**(emin-1)
    GAN_LAMCH_RMIN,

    /// largest exponent before overflow
    GAN_LAMCH_EMAX,

    /// overflow threshold  - (base**emax)*(1-eps)
    GAN_LAMCH_RMAX
} Gan_LapackLamchFlag;

/// Type of norm in lansp functions
typedef enum Gan_LapackNormType
{
    /// Maximum absolute value
    GAN_NORMTYPE_MAXABSVAL,

    /// One norm
    GAN_NORMTYPE_ONE,

    /// Infinity norm
    GAN_NORMTYPE_INFINITY,

    /// Frobenius norm
    GAN_NORMTYPE_FROBENIUS
} Gan_LapackNormType;

/// Plane rotation type
typedef enum Gan_LapackPlaneRotationType
{
    GAN_PLANEROTATION_LEFT,
    GAN_PLANEROTATION_RIGHT
} Gan_LapackPlaneRotationType;

/// Plane rotation direction
typedef enum Gan_LapackPlaneRotationDirection
{
    GAN_PLANEROTATIONDIRECTION_FORWARDS,
    GAN_PLANEROTATIONDIRECTION_BACKWARDS
} Gan_LapackPlaneRotationDirection;

/// Pivot type
typedef enum Gan_LapackPivotType
{
    GAN_PIVOTTYPE_VARIABLE,
    GAN_PIVOTTYPE_TOP,
    GAN_PIVOTTYPE_BOTTOM
} Gan_LapackPivotType;

/// Sort order
typedef enum Gan_LapackSortOrder
{
    GAN_SORTORDER_INCREASING,
    GAN_SORTORDER_DECREASING
} Gan_LapackSortOrder;

/// Type of eigenvector calculation
typedef enum Gan_LapackEvecType
{
    /// Compute eigenvalues only
    GAN_EVECTYPE_EVALSONLY,

    /// Compute eigenvalues and eigenvectors of the original symmetric matrix
    GAN_EVECTYPE_EVECSORIGINAL,

    /// Compute eigenvalues and eigenvectors of the tridiagonal matrix
    GAN_EVECTYPE_EVECSTRIDIAGONAL
} Gan_LapackEvecType;

/// Whether product is on left or right side
typedef enum
{
   /// Multiply on left side
   GAN_LEFTMULT=0,

   /// Multiply on right side
   GAN_RIGHTMULT=1
} Gan_LapackSideFlag;

/// Types of square matrix
typedef enum
{
   /// Symmetric matrix
   GAN_SYMMETRIC_MATRIX,

   /// Diagonal matrix
   GAN_DIAGONAL_MATRIX,

   /// Identity matrix times scalar
   GAN_SCALED_IDENT_MATRIX,

   /// Lower triangular matrix
   GAN_LOWER_TRI_MATRIX,

   /// Upper triangular matrix
   GAN_UPPER_TRI_MATRIX,

   /// Square matrix filled with zeros
   GAN_ZERO_SQUARE_MATRIX
} Gan_SquMatrixType;

/**
 * \}
 */

/**
 * \}
 */

/**
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_LINALG_DEFS_H */

