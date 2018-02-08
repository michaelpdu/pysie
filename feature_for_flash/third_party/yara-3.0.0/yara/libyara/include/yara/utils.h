/*
Copyright (c) 2007. The YARA Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef YR_UTILS_H
#define YR_UTILS_H

#include <assert.h>
#include <stdlib.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif


#ifndef min
#define min(x, y) ((x < y) ? (x) : (y))
#endif

#ifndef max
#define max(x, y) ((x > y) ? (x) : (y))
#endif

#define UINT64_TO_PTR(type, x)  ((type)(size_t) x)

#define PTR_TO_UINT64(x)  ((uint64_t) (size_t) x)


#ifdef WIN32
#if _MSC_VER>=1900
#  define STDC99
#elif
#define snprintf _snprintf
#endif

#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#endif


#ifdef NDEBUG
#define assertf(expr, msg, ...) ((void)0)
#else
#define assertf(expr, msg, ...) \
    if(!(expr)) { \
      fprintf(stderr, "%s:%d: " msg "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
      abort(); \
    }
#endif



size_t xtoi(const char* hexstr);

#endif