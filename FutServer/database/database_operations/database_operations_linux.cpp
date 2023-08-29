#if defined( __linux__ ) || defined( __APPLE__ )
#include "database_operations.h"
#include <iconv.h>
#include <unistd.h>

int _U2G( const char* szSrc, size_t iSrcLen, char* szDst, size_t iDstLen ) {
    iconv_t cd = iconv_open( "gb2312//IGNORE", "utf-8//IGNORE" );   // take care of "//IGNORE", it will ignore those invalid code
    if ( 0 == cd )
        return -2;
    memset( szDst, 0, iDstLen );
    char* src = const_cast<char*>(szSrc);
    char** dst = &szDst;
    if ( -1 == (int)iconv( cd, &src, &iSrcLen, dst, &iDstLen ) )
        return -1;
    iconv_close( cd );
    return 0;
}

int _G2U( const char* szSrc, size_t iSrcLen, char* szDst, size_t iDstLen ) {
    iconv_t cd = iconv_open( "utf-8//IGNORE", "gb2312//IGNORE" );
    if ( 0 == cd )
        return -2;
    memset( szDst, 0, iDstLen );
    char* src = const_cast<char*>(szSrc);
    char** dst = &szDst;
    if ( -1 == (int)iconv( cd, &src, &iSrcLen, dst, &iDstLen ) )
        return -1;
    iconv_close( cd );
    return 0;
}

char* SQLResult::G2U( const char* gb2312 ) {
    size_t iSrcLen = strlen( gb2312 );
    size_t iDstLen = 2 * iSrcLen + 1;
    char* szDst = new char[iDstLen + 1];
    int result = _G2U( gb2312, iSrcLen, szDst, iDstLen );
    if ( result == 0 ) {
        return szDst;
    }
    else {
        return nullptr;
    }
}

char* SQLResult::U2G( const char* utf8 ) {
    size_t iSrcLen = strlen( utf8 );
    size_t iDstLen = 2 * iSrcLen + 1;
    char* szDst = new char[iDstLen + 1];
    int result = _U2G( utf8, iSrcLen, szDst, iDstLen );
    if ( result == 0 ) {
        return szDst;
    }
    else {
        return nullptr;
    }
}

void __sleep( int a ) {
    sleep( a );
}

#endif