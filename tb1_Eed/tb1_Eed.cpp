#include "pch.h"
#include "Sistema.h"
#include <iostream>

using namespace std;

int main()
{
    Sistema* sistema = new Sistema();
    sistema->iniciar();
    delete sistema;
    return 0;
}