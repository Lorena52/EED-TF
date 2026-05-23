#include "pch.h"
#include "Sistema.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
    srand(time(nullptr));
    Sistema* sistema = new Sistema();
    sistema->iniciar();
    delete sistema;
    return 0;
}