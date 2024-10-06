/**
 * \ingroup mdz libraries
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz ansi comparison result enum for different mdz libraries
 *
 */

#ifndef MDZ_ANSI_COMPARE_RESULT_H
#define MDZ_ANSI_COMPARE_RESULT_H

/**
 * Result of comparison
 */
enum mdz_ansi_compare_result
{
  /**
   * Equal
   */
  MDZ_ANSI_COMPARE_EQUAL = 0,

  /**
   * Non-equal
   */
  MDZ_ANSI_COMPARE_NONEQUAL /*= 1*/,

  /**
   * Greater
   */
  MDZ_ANSI_COMPARE_GREATER /*= 2*/,

  /**
   * Smaller
   */
  MDZ_ANSI_COMPARE_SMALLER /*= 3*/,

  /**
   * Comparison ended with error
   */
  MDZ_ANSI_COMPARE_ERROR /*= 4*/
};

#endif
