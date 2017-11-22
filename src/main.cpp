//============================================================================
// Name        : topsis.cpp
// Author      : Athanasios Fotos
// Version     :
// Copyright   : Copy Everything
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "Topsis.h"

using namespace std;

int main(void) {

    Topsis *calc = new Topsis();
    calc->doCrazyMath();
    delete calc;

    return 0;
}
