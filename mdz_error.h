/**
 * \ingroup mdz libraries
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz error enum for different mdz libraries
 *
 */
#ifndef MDZ_ERROR_H
#define MDZ_ERROR_H

/**
 * Error code
 */
enum mdz_error
{
  /**
   * No error
   */
  MDZ_ERROR_NONE = 0,

  /*
   * Invalid license
   */
  MDZ_ERROR_LICENSE /* = 1 */,

  /**
   * Invalid "data" parameter
   */
  MDZ_ERROR_DATA /* = 2 */,

  /**
   * Invalid size
   */
  MDZ_ERROR_SIZE /* = 3 */,

  /**
   * Invalid capacity
   */
  MDZ_ERROR_CAPACITY /* = 4 */,

  /**
   * Size is zero
   */
  MDZ_ERROR_ZERO_SIZE /* = 5 */,

  /**
   * Invalid size
   */
  MDZ_ERROR_BIGSIZE /* = 6 */,

  /**
   * Count is zero
   */
  MDZ_ERROR_ZERO_COUNT /* = 7 */,

  /**
   * "Count" parameter is too big
   */
  MDZ_ERROR_BIGCOUNT /* = 8 */,

  /**
   * "Left" parameter is too big
   */
  MDZ_ERROR_BIGLEFT /* = 9 */,

  /**
   * "Right" parameter is too big
   */
  MDZ_ERROR_BIGRIGHT /* = 10 */,

  /**
   * Invalid "items" parameter
   */
  MDZ_ERROR_ITEMS /* = 11 */,

  /**
   * Invalid terminator
   */
  MDZ_ERROR_TERMINATOR /* = 12 */,

  /**
   * Data and Items overlap
   */
  MDZ_ERROR_OVERLAP /* = 13 */,
};

#endif
