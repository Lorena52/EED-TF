#include "pch.h"
#include "Sistema.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{

    // UTF-8: para que los bloques del logo y los bordes de las tablas se vean bien.
    SetConsoleOutputCP(CP_UTF8);

    Sistema* sistema = new Sistema();
    sistema->iniciar();
    delete sistema;
    return 0;
}