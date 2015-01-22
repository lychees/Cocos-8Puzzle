#include "ConvertUTF.h"

#include "cocos2d.h"

const char* GBKToUTF8(const char *strChar)
{

    iconv_t iconvH;
    iconvH = iconv_open("utf-8","gb2312");


	CCLOG("!");

    if (iconvH == 0)
    {
        return NULL;
    }
    size_t strLength = strlen(strChar);
    size_t outLength = strLength<<2;
    size_t copyLength = outLength;

	
	CCLOG("%s\n", strChar);

	CCLOG("%d\n" , strLength );


    memset(g_GBKConvUTF8Buf, 0, 5000);

    char* outbuf = (char*) malloc(outLength);
    char* pBuff = outbuf;
    memset( outbuf, 0, outLength);

    if (-1 == iconv(iconvH, &strChar, &strLength, &outbuf, &outLength))
    {
        iconv_close(iconvH);
        return NULL;
    }




    memcpy(g_GBKConvUTF8Buf,pBuff,copyLength);


	CCLOG("%s\n", g_GBKConvUTF8Buf);
    free(pBuff);
    iconv_close(iconvH);


	
	CCLOG("!!!!!!!!!!!!!!");

    return g_GBKConvUTF8Buf;
}