#include "E:/cocos2d-x-3.3/cocos2d-x-3.3/external/win32-specific/icon/include/iconv.h"
#include "cstdio"
#include "cstring"
#include "malloc.h"
#pragma once

static char g_GBKConvUTF8Buf[5000] = {0};

const char* GBKToUTF8(const char *strChar);