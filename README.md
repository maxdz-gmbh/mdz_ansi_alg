**NOTE:** All 0.x releases are kind of "alpha-versions" without expectations of interface backward-compatibility.

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

**Linux** binaries are built against Linux Kernel 2.6.18 - and thus should be compatible with Debian (from ver. 4.0), Ubuntu (from ver. 8.04), Fedora (from ver. 9)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP (64-bit).<br>

**Android** x86/armeabi-v7a binaries - may be used from Android API level 16 ("Jelly Bean" ver. 4.1.x)<br>
**Android** x86_64/arm64-v8a binaries - may be used from Android API level 21 ("Lollipop" ver. 5.0)

**macOS** binaries - x86_64, from *MacOS X v10.6.0*

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

Performance comparison tables for *[mdz_ansi_alg_find]*() and *[mdz_ansi_alg_firstOf]*() give an idea about *mdz_ansi_alg* library overall performance on different platforms compared to STL and standard C library. Modern implementations of STL and standard C library are pretty fast, using optimized versions of memory-access functions.

- **mdz_ansi_alg_find() Test**

Following tests are executed:

- Test *1/100M*": Find 1 byte - in the end of 100M bytes long string<br>
- Test *5/100M*": Find 5 bytes long string - in the end of 100M bytes long string<br>
- Test *10/100M*": Find 10 bytes long string - in the end of 100M bytes long string<br>
- Test *100/100M*": Find 100 bytes long string - in the end of 100M bytes long string<br>
- Test *1K/100M*": Find 1K bytes long string - in the end of 100M bytes long string<br>
- Test *500K/1M*": Find 500K bytes long string - in the end of 1M bytes long string<br>
- Test *100M-100/100M*": Find "100M minus 100" bytes long string - in the end of 100M bytes long string<br>
- Test *100M/100M*": Find 100M bytes long string - in 100M bytes long string<br>

For **Windows 10 (64-bit)** on *Intel i5-6600 @ 3.30GHz (4 cores/4 threads)*<br>

**Monotone test** : "long string" and "string to find" are both filled with '1's; on the last position of both strings is '2'

monotone = MDZ_FIND_MONOTONE method<br>
clib = MDZ_FIND_CLIB method (standard C library)<br>
brute = MDZ_FIND_BRUTE method<br>
bmh = MDZ_FIND_BMH method

- VC++ toolset v140 (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi_alg, monotone | mdz_ansi_alg, clib | mdz_ansi_alg, brute |  mdz_ansi_alg, bmh |std::string.find() | clib (strstr())|
| :----:| ---------------------: | -----------------: | ------------------: | -----------------: | ----------------: | -------------: |
| 100M-100/100M| 1,262,919      | 10,884,012         | 14,182,350           | **721,370**      | 14,150,110 | 10,383,086 |

- **mdz_ansi_alg_firstOf() Test**

Following tests are executed:

- Test *1/100M*": Find first of 1 byte - in the end of 100M bytes long string<br>
- Test *5/100M*": Find first of 5 bytes - in the end of 100M bytes long string<br>
- Test *20/100M*": Find first of 20 bytes - in the end of 100M bytes long string<br>
- Test *50/100M*": Find first of 50 bytes - in the end of 100M bytes long string<br>
- Test *100/100M*": Find first of 100 bytes - in the end of 100M bytes long string<br>

For **Windows 10 (64-bit)** on *Intel i5-6600 @ 3.30GHz (4 cores/4 threads)*<br>

- VC++ toolset v140 (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi_alg| std::string.find_first_of() | clib (strcspn())|
| :---:| ---: | ---: | ---: |

- MinGW/gcc toolset (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi_alg|
| :---:| ---: |

[mdz_ansi_alg_find]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki/mdz_ansi_alg_find
[mdz_ansi_alg_firstOf]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki/mdz_ansi_alg_firstOf

## mdz_ansi_alg Usage

The functions are implemented with strict input parameters checking. It means *mdz_false* or some other error indication will be returned if one or several input parameters are invalid - even if such an invalidity doesn't lead to inconsistence (for example adding or removing 0 items).<br>

**Test license generation:** - in order to get free test-license, please proceed to our Shop page [maxdz Shop] and register an account. After registration you will be able to obtain free 14-days test-licenses for our products using "Obtain for free" button. 
Test license data should be used in *mdz_ansi_alg_init()* call for library initialization.

**NOTE:** All 0.x releases are kind of "beta-versions" and can be used 1) only with test-license (during test period of 30 days, with necessity to re-generate license for the next 30 days test period) and 2) without expectations of interface backward-compatibility.

[mdz_ansi_alg Wiki]: https://github.com/maxdz-gmbh/mdz_ansi_alg/wiki
[Glib]: https://en.wikipedia.org/wiki/GLib
[STL]: https://en.wikipedia.org/wiki/Standard_Template_Library
[Performance Comparison]: #performance-comparison
[maxdz Shop]: https://maxdz.com/shop.php

#### Code Example

*mdz_ansi_alg_init()* with license information should be called for library initialization before any subsequent calls:
