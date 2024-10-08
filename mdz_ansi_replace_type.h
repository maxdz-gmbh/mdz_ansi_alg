/**
 * \ingroup mdz libraries
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz attachment type enum for different mdz libraries
 *
 */

#ifndef MDZ_ANSI_REPLACE_TYPE_H
#define MDZ_ANSI_REPLACE_TYPE_H

/**
 * Attachment type
 */
enum mdz_ansi_replace_type
{
  /**
   * Dual-pass. 1st pass for counting final length, 2nd pass for replacement
   */
  MDZ_ANSI_REPLACE_DUAL = 0,

  /**
   * Single pass. 1st pass for replacement. If there is not enough capacity and no realloc function - stop, without partial replace and without string original state restore
   */
  MDZ_ANSI_REPLACE_STRAIGHT /* = 1 */
};

#endif
