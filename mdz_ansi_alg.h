/**
 * \ingroup mdz_ansi_alg library
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz_ansi_alg is algorithms library for contiguous single-byte string, containing ASCII (0..127) and "ANSI" (128 - 255) characters.
 * Functions are algorithms for processing input data. There are no memory allocations happen inside functions and no dynamic memory use.
 *
 * String may contain 0-terminators ('\0') inside, and must end with 0-terminator.
 *
 * Capacity - how many bytes of memory is reserved for string content. Capacity does not include 0-terminator byte, thus reserved memory should be at least 1 byte bigger than Capacity.
 * Size - how many characters are actually residing in a string.
 *
 * \par portability
 * Source code of library conforms to ANSI C 89/90 Standard.
 *
 * \version 0.1
 *
 * \date 2024-09
 *
 */

#ifndef MDZ_ANSI_ALG_H
#define MDZ_ANSI_ALG_H

#include <stddef.h>

#include "mdz_bool.h"
#include "mdz_ansi_compare_result.h"
#include "mdz_error.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * \defgroup Init functions
   */

  /**
   * Initializes mdz_ansi_alg library and license. This function should be called before any other function of the library.
   * \param pnFirstNameHash - user first name hash code
   * \param pnLastNameHash  - user last name hash code
   * \param pnEmailHash     - user e-mail hash code
   * \param pnLicenseHash   - license hash code
   * \return:
   * mdz_true - if the initialization succeeded, otherwise mdz_false
   */
  mdz_bool mdz_ansi_alg_init(const unsigned long* pnFirstNameHash, const unsigned long* pnLastNameHash, const unsigned long* pnEmailHash, const unsigned long* pnLicenseHash);

  /**
   * Insert pcItems into pcData from nLeftPos position. pcData and pcItems cannot overlap. New size is returned in pnDataSize.
   * Size and capacity    - do not include 0-terminator; thus size and capacity of empty string with no free space are 0
   * \param pcData        - pointer to string. It should end with 0-terminator and have enough capacity for insertion of pcItems
   * \param pnDataSize    - pointer to current Size. Size is 0 for empty string. If insertion succeeded, new size is returned here
   * \param nDataCapacity - maximal capacity of pcData buffer. nDataCapacity does not include 0-terminator byte, thus pcData buffer should be at least 1 byte bigger than nDataCapacity
   * \param nLeftPos      - 0-based position to insert. If nLeftPos == Size items are appended. nLeftPos > Size is not allowed
   * \param pcItems       - items to insert. Cannot be NULL
   * \param nCount        - number of items to insert. Cannot be 0
   * \return:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_SIZE       - pnDataSize is NULL
   * MDZ_ERROR_CAPACITY   - nDataCapacity is 0 (no space for insertion) or SIZE_MAX (no space for 0-terminator)
   * MDZ_ERROR_TERMINATOR - there is no 0-terminator in the end of pcData ([Size] position)
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is 0
   * MDZ_ERROR_BIGLEFT    - nLeftPos > Size
   * MDZ_ERROR_BIGCOUNT   - Size + nCount > nDataCapacity
   * MDZ_ERROR_OVERLAP    - [pcData .. pcData + Size + nCount] area and pcItems overlap
   * MDZ_ERROR_NONE       - function succeeded, new size is written in pnDataSize
   */
  enum mdz_error mdz_ansi_alg_insert(char* pcData, size_t* pnDataSize, size_t nDataCapacity, size_t nLeftPos, const char* pcItems, size_t nCount);

  /**
   * \defgroup Find functions
   */

  /**
   * Find first occurrence of cItem in pcData. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData    - pointer to string
   * \param nLeftPos  - 0-based start position to search from left. Use 0 to search from the beginning of string
   * \param nRightPos - 0-based end position to search up to. Use Size-1 to search till the end of string
   * \param cItem     - character to find
   * \param penError  - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE  - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA     - pcData is NULL
   * MDZ_ERROR_BIGRIGHT - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT  - nLeftPos > nRightPos
   * MDZ_ERROR_NONE     - function succeeded
   * \return:
   * SIZE_MAX - if cItem not found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_findSingle(const char* pcData, size_t nLeftPos, size_t nRightPos, char cItem, enum mdz_error* penError);

  /**
   * Find first occurrence of pcItems in pcData using optimized Boyer-Moore-Horspool search. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData       - pointer to string
   * \param nLeftPos     - 0-based start position to search from left. Use 0 to search from the beginning of string
   * \param nRightPos    - 0-based end position to search up to. Use Size-1 to search till the end of string
   * \param pcItems      - items to find. Cannot be NULL
   * \param nCount       - number of items to find. Cannot be 0
   * \param penError     - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE     - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA        - pcData is NULL
   * MDZ_ERROR_ITEMS       - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT  - nCount is NULL
   * MDZ_ERROR_BIGRIGHT    - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT     - nLeftPos > nRightPos
   * MDZ_ERROR_BIGCOUNT    - nCount is bigger than search area (between nLeftPos and nRightPos)
   * MDZ_ERROR_NONE        - function succeeded
   * \return:
   * SIZE_MAX - if pcItems not found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_find(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_error* penError);

  /**
   * Find last occurrence of cItem in pcData. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData    - pointer to string
   * \param nLeftPos  - 0-based end position to find up to. Use 0 to search till the beginning of string
   * \param nRightPos - 0-based start position to find from right. Use Size-1 to search from the end of string
   * \param cItem     - character to find
   * \param penError  - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE  - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA     - pcData is NULL
   * MDZ_ERROR_BIGRIGHT - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT  - nLeftPos > nRightPos
   * MDZ_ERROR_NONE     - function succeeded
   * \return:
   * SIZE_MAX - if cItem not found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_rfindSingle(const char* pcData, size_t nLeftPos, size_t nRightPos, char cItem, enum mdz_error* penError);

  /**
   * Find last occurrence of pcItems in pcData using optimized Boyer-Moore-Horspool search. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData       - pointer to string
   * \param nLeftPos     - 0-based end position to find up to. Use 0 to search till the beginning of string
   * \param nRightPos    - 0-based start position to find from right. Use Size-1 to search from the end of string
   * \param pcItems      - items to find. Cannot be NULL
   * \param nCount       - number of items to find. Cannot be 0
   * \param penError     - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE     - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA        - pcData is NULL
   * MDZ_ERROR_ITEMS       - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT  - nCount is NULL
   * MDZ_ERROR_BIGRIGHT    - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT     - nLeftPos > nRightPos
   * MDZ_ERROR_BIGCOUNT    - nCount is bigger than search area (between nLeftPos and nRightPos)
   * MDZ_ERROR_NONE        - function succeeded
   * \return:
   * SIZE_MAX - if pcItems not found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_rfind(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_error* penError);

  /**
   * Find first occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData    - pointer to string
   * \param nLeftPos  - 0-based end position to find up to. Use 0 to search till the beginning of string
   * \param nRightPos - 0-based start position to find from right. Use Size-1 to search till the end of string
   * \param pcItems   - items to find. Cannot be NULL
   * \param nCount    - number of items to find. Cannot be 0
   * \param penError  - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is NULL
   * MDZ_ERROR_BIGRIGHT   - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded
   * \return:
   * SIZE_MAX - if no item of pcItems found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_firstOf(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_error* penError);

  /**
   * Find first non-occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData    - pointer to string
   * \param nLeftPos  - 0-based end position to find up to. Use 0 to search till the beginning of string
   * \param nRightPos - 0-based start position to find from right. Use Size-1 to search till the end of string
   * \param pcItems   - items to find. Cannot be NULL
   * \param nCount    - number of items to find. Cannot be 0
   * \param penError  - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is NULL
   * MDZ_ERROR_BIGRIGHT   - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded
   * \return:
   * SIZE_MAX - if no item of pcItems found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_firstNotOf(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_error* penError);

  /**
   * Find last occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData    - pointer to string
   * \param nLeftPos  - 0-based end position to find up to. Use 0 to search till the beginning of string
   * \param nRightPos - 0-based start position to find from right. Use Size-1 to search till the end of string
   * \param pcItems   - items to find. Cannot be NULL
   * \param nCount    - number of items to find. Cannot be 0
   * \param penError  - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is NULL
   * MDZ_ERROR_BIGRIGHT   - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded
   * \return:
   * SIZE_MAX - if no item of pcItems found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_lastOf(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_error* penError);

  /**
   * Find last non-occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or SIZE_MAX if not found or error happened. If penError is not NULL, error will be written there
   * \param pcData    - pointer to string
   * \param nLeftPos  - 0-based end position to find up to. Use 0 to search till the beginning of string
   * \param nRightPos - 0-based start position to find from right. Use Size-1 to search till the end of string
   * \param pcItems   - items to find. Cannot be NULL
   * \param nCount    - number of items to find. Cannot be 0
   * \param penError  - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is NULL
   * MDZ_ERROR_BIGRIGHT   - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded
   * \return:
   * SIZE_MAX - if no item of pcItems found or error happened
   * Result   - 0-based position of first match
   */
  size_t mdz_ansi_alg_lastNotOf(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_error* penError);

  /**
   * \defgroup Remove functions
   */

  /**
   * Remove nCount item(s) starting from 0-based nLeftPos position
   * \param pcData     - pointer to string. It should end with 0-terminator
   * \param pnDataSize - pointer to current Size. If removal succeed, new size is returned here
   * \param nLeftPos   - 0-based start position to remove item(s) from. Use 0 to remove from the beginning of string
   * \param nCount     - number of item(s) to remove. Cannot be 0
   * \return:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_SIZE       - pnDataSize is NULL
   * MDZ_ERROR_ZERO_SIZE  - Size is 0 (string is empty)
   * MDZ_ERROR_TERMINATOR - there is no 0-terminator in the end of pcData ([Size] position)
   * MDZ_ERROR_ZERO_COUNT - nCount is 0
   * MDZ_ERROR_BIGLEFT    - nLeftPos >= Size
   * MDZ_ERROR_BIGCOUNT   - nLeftPos + nCount > Size
   * MDZ_ERROR_NONE       - function succeeded, new size is written in pnDataSize
   */
  enum mdz_error mdz_ansi_alg_removeFrom(char* pcData, size_t* pnDataSize, size_t nLeftPos, size_t nCount);

  /**
   * Remove all ocurrences of nCount item(s) matching to pcItems, residing between nLeftPos and nRightPos
   * \param pcData     - pointer to string. It should end with 0-terminator
   * \param pnDataSize - pointer to current Size. If removal succeed, new size is returned here
   * \param nLeftPos   - 0-based start position to remove item(s) from. Use 0 to search from the beginning of string
   * \param nRightPos  - 0-based end position to remove item(s) up to. Use Size-1 to search till the end of string
   * \param pcItems    - items to remove. Cannot be NULL
   * \param nCount     - number of item(s) to remove. Cannot be 0
   * \return:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_SIZE       - pnDataSize is NULL
   * MDZ_ERROR_ZERO_SIZE  - Size is 0 (string is empty)
   * MDZ_ERROR_TERMINATOR - there is no 0-terminator in the end of pcData ([Size] position)
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is 0
   * MDZ_ERROR_BIGRIGHT   - nRightPos >= Size
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_BIGCOUNT   - nCount is bigger than search area (between nLeftPos and nRightPos)
   * MDZ_ERROR_NONE       - function succeeded, new size is written in pnDataSize
   */
  enum mdz_error mdz_ansi_alg_remove(char* pcData, size_t* pnDataSize, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount);

  /**
   * Remove items which are contained in pcItems from left, until first non-contained in pcItems item is reached.
   * \param pcData    - pointer to string. It should end with 0-terminator
   * \param pnDataSize- pointer to current Size. If removal succeed, new size is returned here
   * \param nLeftPos  - 0-based start position to trim item(s) from left. Use 0 to trim from the beginning of string
   * \param nRightPos - 0-based end position to trim item(s) up to. Use Size-1 to trim till the end of string
   * \param pcItems   - items to trim. Cannot be NULL
   * \param nCount    - number of items to trim. Cannot be 0
   * \return:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_SIZE       - pnDataSize is NULL
   * MDZ_ERROR_ZERO_SIZE  - Size is 0 (string is empty)
   * MDZ_ERROR_TERMINATOR - there is no 0-terminator in the end of pcData ([Size] position)
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is 0
   * MDZ_ERROR_BIGRIGHT   - nRightPos >= Size
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded, new size is written in pnDataSize
   */
  enum mdz_error mdz_ansi_alg_trimLeft(char* pcData, size_t* pnDataSize, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount);

  /**
   * Remove items which are contained in pcItems from right, until first non-contained in pcItems item is reached.
   * \param pcData     - pointer to string. It should end with 0-terminator
   * \param pnDataSize - pointer to current Size. If removal succeed, new size is returned here
   * \param nLeftPos - 0-based end position to trim item(s) up to. Use 0 to trim till the beginning of string
   * \param nRightPos - 0-based start position to trim item(s) from right. Use Size-1 to trim from the end of string
   * \param pcItems   - items to trim. Cannot be NULL
   * \param nCount    - number of items to trim. Cannot be 0
   * \return:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_SIZE       - pnDataSize is NULL
   * MDZ_ERROR_ZERO_SIZE  - Size is 0 (string is empty)
   * MDZ_ERROR_TERMINATOR - there is no 0-terminator in the end of pcData ([Size] position)
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is 0
   * MDZ_ERROR_BIGRIGHT   - nRightPos >= Size
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded, new size is written in pnDataSize
   */
  enum mdz_error mdz_ansi_alg_trimRight(char* pcData, size_t* pnDataSize, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount);

  /**
   * Remove items which are contained in pcItems from left and from right, until first non-contained in pcItems item is reached.
   * \param pcData     - pointer to string. It should end with 0-terminator
   * \param pnDataSize - pointer to current Size. If removal succeed, new size is returned here
   * \param nLeftPos - 0-based start position to trim item(s) from left. Use 0 to trim from the beginning of string
   * \param nRightPos - 0-based start position to trim item(s) from right. Use Size-1 to trim from the end of string
   * \param pcItems   - items to trim. Cannot be NULL
   * \param nCount    - number of items to trim. Cannot be 0
   * \return:
   * MDZ_ERROR_LICENSE    - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA       - pcData is NULL
   * MDZ_ERROR_SIZE       - pnDataSize is NULL
   * MDZ_ERROR_ZERO_SIZE  - Size is 0 (string is empty)
   * MDZ_ERROR_TERMINATOR - there is no 0-terminator in the end of pcData ([Size] position)
   * MDZ_ERROR_ITEMS      - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT - nCount is 0
   * MDZ_ERROR_BIGRIGHT   - nRightPos >= Size
   * MDZ_ERROR_BIGLEFT    - nLeftPos > nRightPos
   * MDZ_ERROR_NONE       - function succeeded, new size is written in pnDataSize
   */
  enum mdz_error mdz_ansi_alg_trim(char* pcData, size_t* pnDataSize, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount);

  /**
   * \defgroup Miscellaneous functions
   */

  /**
   * Compare content of string with pcItems. If penError is not NULL, error will be written there
   * \param pcData          - pointer to string
   * \param nDataSize       - Size of pcData
   * \param nLeftPos        - 0-based start position to compare from left. Use 0 to compare from the beginning of string
   * \param pcItems         - items to compare. Cannot be NULL
   * \param nCount          - number of items to compare. Cannot be 0
   * \param bPartialCompare - if mdz_true compare only nCount items, otherwise compare full strings
   * \param penError        - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE     - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA        - pcData is NULL
   * MDZ_ERROR_SIZE        - Size is 0 (empty string)
   * MDZ_ERROR_ITEMS       - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT  - nCount is NULL
   * MDZ_ERROR_BIGLEFT     - nLeftPos >= Size
   * MDZ_ERROR_BIGCOUNT    - nLeftPos + nCount > Size
   * MDZ_ERROR_NONE        - function succeeded
   * \return:
   * MDZ_COMPARE_EQUAL or MDZ_COMPARE_NONEQUAL - Result of comparison
   */
  enum mdz_ansi_compare_result mdz_ansi_alg_compare(const char* pcData, size_t nDataSize, size_t nLeftPos, const char* pcItems, size_t nCount, mdz_bool bPartialCompare, enum mdz_error* penError);

  /**
   * Counts number of pcItems substring occurences in string. If penError is not NULL, error will be written there
   * \param pcData           - pointer to string
   * \param nLeftPos         - 0-based start position to search from left. Use 0 to search from the beginning of string
   * \param nRightPos        - 0-based end position to search up to. Use Size-1 to search till the end of string
   * \param pcItems          - items to find. Cannot be NULL
   * \param nCount           - number of items to find. Cannot be 0
   * \param bAllowOverlapped - mdz_true if overlapped substrings should be counted, otherwise mdz_false
   * \param penError         - if not NULL, error will be written there. There are following errors possible:
   * \value:
   * MDZ_ERROR_LICENSE     - license is not initialized using mdz_ansi_alg_init() or invalid
   * MDZ_ERROR_DATA        - pcData is NULL
   * MDZ_ERROR_ITEMS       - pcItems is NULL
   * MDZ_ERROR_ZERO_COUNT  - nCount is NULL
   * MDZ_ERROR_BIGRIGHT    - nRightPos is SIZE_MAX
   * MDZ_ERROR_BIGLEFT     - nLeftPos > nRightPos
   * MDZ_ERROR_BIGCOUNT    - nCount is bigger than search area (between nLeftPos and nRightPos)
   * MDZ_ERROR_NONE        - function succeeded
   * \return:
   * SIZE_MAX - if error happened
   * Result   - count of substring occurences. 0 if not found
   */
  size_t mdz_ansi_alg_count(const char* pcData, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, mdz_bool bAllowOverlapped, enum mdz_error* penError);

#ifdef __cplusplus
}
#endif

#endif
