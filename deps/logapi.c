#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */
#include <string.h>     /* strlen */
#include <time.h>
#include "logapi.h"

#ifdef _WIN32
#include "winansi.h"
#include <windows.h>
#define localtime_r(src, dst) localtime_s(dst, src)
#if defined _MSC_VER
#  include <malloc.h>
#  define alloca _alloca
#endif
#endif // _WIN32

/* logprint source was derived from ccminer source */
void logprint(int prio, const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

    const char* color = "";
    const time_t now = time(NULL);
    char *f;
    int len;
    struct tm tm;
    int use_colors = 1;

    localtime_r(&now, &tm);

    switch (prio) {
        case LOG_ERR:     color = CL_RED; break;
        case LOG_WARNING: color = CL_YLW; break;
        case LOG_NOTICE:  color = CL_WHT; break;
        case LOG_INFO:    color = ""; break;
        case LOG_DEBUG:   color = CL_GRY; break;

        case LOG_BLUE:
            prio = LOG_NOTICE;
            color = CL_CYN;
            break;
    }
    if (!use_colors)
        color = "";

    len = 40 + (int) strlen(fmt) + 2;
    f = (char*) alloca(len);
    sprintf(f, "[%d-%02d-%02d %02d:%02d:%02d]%s %s%s\n",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        color,
        fmt,
        use_colors ? CL_N : ""
    );
    if (prio == LOG_RAW) {
            sprintf(f, "%s%s\n", fmt, CL_N);
    }

    vfprintf(stdout, f, ap);
    fflush(stdout);

	va_end(ap);
}
