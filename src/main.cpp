//============================================================================
// Name        : topsis.cpp
// Author      : Athanasios Fotos
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
