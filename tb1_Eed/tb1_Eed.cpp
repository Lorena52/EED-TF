#include "pch.h"
#include "Sistema.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{

    SetConsoleOutputCP(1252);// Windows Latin-1 (Europa occidental)

    Sistema* sistema = new Sistema();
    sistema->iniciar();
    delete sistema;
    return 0;
}