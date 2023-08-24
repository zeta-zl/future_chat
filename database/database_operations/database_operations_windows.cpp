#if defined(_WIN32) || defined(_MSC_VER) 
#include <atlstr.h>
#include "database_operations.h"

char* SQLResult::U2G( const char* utf8 ) {
    int len = MultiByteToWideChar( CP_UTF8, 0, utf8, -1, NULL, 0 );
    wchar_t* wstr = new wchar_t[len + 1];
    memset( wstr, 0, len + 1 );
    MultiByteToWideChar( CP_UTF8, 0, utf8, -1, wstr, len );
    len = WideCharToMultiByte( CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL );
    char* str = new char[len + 1];
    memset( str, 0, len + 1 );
    WideCharToMultiByte( CP_ACP, 0, wstr, -1, str, len, NULL, NULL );
    if ( wstr ) delete[] wstr;
    return str;
}

char* SQLResult::G2U( const char* gb2312 ) {
    int len = MultiByteToWideChar( CP_ACP, 0, gb2312, -1, NULL, 0 );
    wchar_t* wstr = new wchar_t[len + 1];
    memset( wstr, 0, len + 1 );
    MultiByteToWideChar( CP_ACP, 0, gb2312, -1, wstr, len );
    len = WideCharToMultiByte( CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL );
    char* str = new char[len + 1];
    memset( str, 0, len + 1 );
    WideCharToMultiByte( CP_UTF8, 0, wstr, -1, str, len, NULL, NULL );
    if ( wstr ) delete[] wstr;
    return str;
}

void __sleep(int a) {
    Sleep( a );
}

#endif