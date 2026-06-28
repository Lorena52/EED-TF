#include "pch.h"
#include "Banner.h"

// <Windows.h> queda AISLADO en este .cpp para que no se propague por el
// header (evita el conflicto de las macros min/max con numeric_limits::max
// en otros archivos, y el choque de extern "C" con GetConsoleScreenBufferInfo).
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

namespace Banner {

    int anchoConsola() {
        CONSOLE_SCREEN_BUFFER_INFO info;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(h, &info)) {
            int a = info.srWindow.Right - info.srWindow.Left + 1;
            if (a > 0) return a;
        }
        return 100;
    }

    int altoConsola() {
        CONSOLE_SCREEN_BUFFER_INFO info;
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        if (h != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(h, &info)) {
            int a = info.srWindow.Bottom - info.srWindow.Top + 1;
            if (a > 0) return a;
        }
        return 30;
    }
}