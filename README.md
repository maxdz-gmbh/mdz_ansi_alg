**NOTE:** All 0.x releases are kind of "alpha-versions" without expectations of API backward-compatibility.

## Table of Contents
[mdz_ansi_alg Overview](#mdz_ansi-Overview)<br>
[mdz_ansi_alg Advantages](#mdz_ansi-Advantages)<br>
[Performance Comparison](#performance-comparison)<br>
[mdz_ansi_alg Usage](#mdz_ansi_alg-Usage)<br>
[Licensing info](#Licensing-info)<br>

## mdz_ansi_alg Overview
Please take a look at *"mdz_ansi_alg.h"* C header file or [mdz_ansi_alg Wiki] site for detailed functions descriptions.

[mdz_ansi_alg Wiki]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki

[mdz_ansi_alg] - is a very lightweight, versatile and speedy C  library for handling single-byte (ASCII/ANSI) strings, developed by [maxdz Software GmbH]. Source code of library is highly-portable, conforms to ANSI C 89/90 Standard.

Only shared/dynamically loaded libraries (*.so* and *.dll* files with import libraries) are available for evaluation testing purposes. Static libraries are covered by our commercial licenses.

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP (64-bit).<br>

**Linux** binaries are built against Linux Kernel 2.6.17 - and thus should be compatible with Debian (from ver. 4), Ubuntu (from ver. 6.10), Fedora (from ver. 9), Red Hat/CentOS (from ver. 5)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0 (for x86) and ver. 8.0 (for x64)

~~**Android** x86/armeabi-v7a binaries - may be used from Android API level 16 ("Jelly Bean" ver. 4.1.x)<br>~~
~~**Android** x86_64/arm64-v8a binaries - may be used from Android API level 21 ("Lollipop" ver. 5.0)~~

~~**macOS** binaries - x86_64, from *MacOS X v10.6.0*~~

[mdz_ansi_alg]: https://github.com/maxdz-gmbh/mdz_ansi_alg
[maxdz Software GmbH]: https://maxdz.com/

## mdz_ansi_alg Advantages

**1. High Portability:** The entire codebase conforms to the ANSI C 89/90 standard.

**2. Minimal Dependencies:** *mdz_ansi_alg* functions solely depend on standard C-library functions. This means you can integrate the library into your code without any additional dependencies beyond the standard platform libraries/APIs.

**3. Performance:** The library functions are highly optimized for speed, particularly for operations like searching. Especially when processing very large string (e.g., hundreds of megabytes or gigabytes).
Comparison tables for *mdz_ansi_alg_find()*, *mdz_ansi_alg_firstOf()* are here [Performance Comparison](#performance-comparison). There will be more tables/info later.

**4. Flexibilty:** Most library functions offer both "left position" and "right position" parameters, allowing you to limit the processing area. Additionally, the library provides more string functions than comparable libraries such as STL, Boost, or GLib.

**5. Extended Error-Checking:** All functions use strict error-checking mechanisms and return specific error codes pointing the problem precisely.

**6. Extended Control:** The functions perform only explicit operations. For example, when an "insert" function is called, it will return an error if there is not enough capacity in string - no implicit memory allocations/reservations will be made.

**7. No Memory Overhead:** The functions are designed to process input data without making internal memory allocations or using dynamic memory.

## Performance Comparison

Performance comparison table for *[mdz_ansi_alg_find]*() gives an idea about *mdz_ansi_alg* library overall performance on different platforms compared to STL and standard C library. Modern implementations of STL and standard C library are pretty fast, using optimized versions of memory-access functions.

For Windows 10 (64-bit) on *Intel i5-6600 @ 3.30GHz (4 cores/4 threads)*<br>
- VC++ toolset v140; SSE2 enchancements are activated for 32-bit test; AVX2 enchancements are activated for 64-bit test<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

- **mdz_ansi_alg_find() Test**

Following tests are executed:
- 32-bit test "*100M-100/100M*": Find 100M minus 100 (99,999,900) in 100M (100,000,000) bytes long string<br>
- 64-bit test "*3G-100/3G*": Find 3G minus 100 (2,999,999,900) in 3G (3,000,000,000) bytes long string<br>

| Test  | mdz_ansi_alg_find() |std::string.find() | clib (strstr())|
| :----:| -----------------: | ----------------: | -------------: |
| 100M-100/100M| **681,259**      | 14,923,163 | 11,181,341 |
| 3G-100/3G| **19,509,757**      | 359,457,282 | 322,119,234 |

- **mdz_ansi_alg_firstOf() Test**

Following tests are executed:
- 32-bit test "*100M/150*": Find first of 150 items in 100M (100,000,000) bytes long string<br>
- 64-bit test "*3G/150*": Find first of 150 items in 3G (3,000,000,000) bytes long string<br>

| Test  | mdz_ansi_alg_firstOf() |std::string.find_first_of() | clib (strcspn())|
| :----:| -----------------: | ----------------: | -------------: |
| 100M/150| **331,853**      | 43,824,190 | 2,394,748 |
| 3G/150| **8,571,427**      | 1,590,268,614 | 24,277,950 |

[mdz_ansi_alg_find]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki/mdz_ansi_alg_find
[mdz_ansi_alg_firstOf]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki/mdz_ansi_alg_firstOf

## mdz_ansi_alg Usage

**Test license generation:** - in order to get free test-license, please proceed to our Shop page [maxdz Shop] and register an account. After registration you will be able to obtain free 30-days test-licenses for our products using "Obtain for free" button. 
Test license data should be used in *mdz_ansi_alg_init()* call for library initialization.

**NOTE:** All 0.x releases are kind of "beta-versions" and can be used 1) only with test-license (during test period of 30 days, with necessity to re-generate license for the next 30 days test period) and 2) without expectations of interface backward-compatibility.

[mdz_ansi_alg Wiki]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki
[Glib]: https://en.wikipedia.org/wiki/GLib
[STL]: https://en.wikipedia.org/wiki/Standard_Template_Library
[Performance Comparison]: #performance-comparison
[maxdz Shop]: https://maxdz.com/shop.php

#### Code Example

file "test.c"

```
#include <mdz_ansi_alg.h>

#include <string.h>
#include <assert.h>

int main(void)
{
  char pcBuffer[100] = "0123456789";
  size_t nSize = strlen(pcBuffer);
  size_t nCapacity = sizeof(pcBuffer) - 1;

  size_t nPosition, nCount;
  enum mdz_error enError;
  enum mdz_ansi_compare_result enCompareResult;

  unsigned long pnFirstNameHash[] = { /* your personal first name hash */ };
  unsigned long pnLastNameHash[] = { /* your personal last name hash */ };
  unsigned long pnEmailHash[] = { /* your personal last email hash */ };
  unsigned long pnLicenseHash[] = { /* your personal license hash */ };

  /* library/license initialization, must be called before any other library function */
  if (mdz_false == mdz_ansi_alg_init(pnFirstNameHash, pnLastNameHash, pnEmailHash, pnLicenseHash))
  {
    return 0;
  }

  if (MDZ_ERROR_NONE != mdz_ansi_alg_insert(pcBuffer, &nSize, nCapacity, nSize, "9876543210", 10))
  {
    return 0;
  }
  assert(20 == nSize);
  assert(0 == strcmp(pcBuffer, "01234567899876543210"));

  nPosition = mdz_ansi_alg_findSingle(pcBuffer, 0, 10, '4', &enError);
  assert(4 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_find(pcBuffer, 0, nSize - 1, "99", 2, &enError);
  assert(9 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_rfindSingle(pcBuffer, 0, nSize - 1, '4', &enError);
  assert(15 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_rfind(pcBuffer, 0, nSize - 1, "9", 1, &enError);
  assert(10 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_firstOf(pcBuffer, 0, nSize - 1, "43", 2, &enError);
  assert(3 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_firstNotOf(pcBuffer, 0, nSize - 1, "3210", 4, &enError);
  assert(4 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_lastOf(pcBuffer, 0, nSize - 1, "34", 4, &enError);
  assert(16 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  nPosition = mdz_ansi_alg_lastNotOf(pcBuffer, 0, nSize - 1, "0123", 4, &enError);
  assert(15 == nPosition);
  assert(MDZ_ERROR_NONE == enError);

  if (MDZ_ERROR_NONE != mdz_ansi_alg_removeFrom(pcBuffer, &nSize, 2, 3))
  {
    return 0;
  }
  assert(17 == nSize);
  assert(0 == strcmp(pcBuffer, "01567899876543210"));

  if (MDZ_ERROR_NONE != mdz_ansi_alg_remove(pcBuffer, &nSize, 0, nSize - 1, "99", 2))
  {
    return 0;
  }
  assert(15 == nSize);
  assert(0 == strcmp(pcBuffer, "015678876543210"));

  if (MDZ_ERROR_NONE != mdz_ansi_alg_trimLeft(pcBuffer, &nSize, 0, nSize - 1, "012", 3))
  {
    return 0;
  }
  assert(13 == nSize);
  assert(0 == strcmp(pcBuffer, "5678876543210"));

  if (MDZ_ERROR_NONE != mdz_ansi_alg_trimRight(pcBuffer, &nSize, 0, nSize - 1, "012", 3))
  {
    return 0;
  }
  assert(10 == nSize);
  assert(0 == strcmp(pcBuffer, "5678876543"));

  if (MDZ_ERROR_NONE != mdz_ansi_alg_trim(pcBuffer, &nSize, 0, nSize - 1, "012345", 6))
  {
    return 0;
  }
  assert(6 == nSize);
  assert(0 == strcmp(pcBuffer, "678876"));

  enCompareResult = mdz_ansi_alg_compare(pcBuffer, nSize, 0, "678", 3, mdz_false, &enError);
  assert(MDZ_ANSI_COMPARE_NONEQUAL == enCompareResult);
  assert(MDZ_ERROR_NONE == enError);

  enCompareResult = mdz_ansi_alg_compare(pcBuffer, nSize, 0, "678", 3, mdz_true, &enError);
  assert(MDZ_ANSI_COMPARE_EQUAL == enCompareResult);
  assert(MDZ_ERROR_NONE == enError);

  nCount = mdz_ansi_alg_count(pcBuffer, 0, nSize - 1, "6", 1, mdz_true, &enError);
  assert(2 == nCount);
  assert(MDZ_ERROR_NONE == enError);

  return 0;
}
```

## Licensing info

Use of **mdz_ansi_alg** library is regulated by license agreement in *LICENSE.txt*

Basically private non-commercial "test" usage is unrestricted. Commercial usage of library (incl. its source code) will be regulated by according license agreement.
