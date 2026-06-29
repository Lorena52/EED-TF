#include "pch.h"
#include "Sistema.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    // UTF-8: para que los bloques "█" del logo y los bordes de las
    // tablas (caracteres de caja) y los acentos se muestren bien.
    SetConsoleOutputCP(CP_UTF8);

    // Activar el procesamiento de secuencias ANSI (colores \033[..m)
    // en la consola de Windows. Sin esto, los colores podrian salir
    // como texto raro en algunas consolas.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD modo = 0;
        if (GetConsoleMode(hOut, &modo)) {
            modo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // 0x0004
            SetConsoleMode(hOut, modo);
        }
    }

    Sistema* sistema = new Sistema();
    sistema->iniciar();
    delete sistema;

    system("pause>=0");
    return 0;
}