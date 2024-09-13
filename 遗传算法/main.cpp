#include <iostream>
#include "Bin.h"
using namespace std;
int main() {
    Bin bin(2000, 22);
    bin.interation(200);
    bin.print_max_fitness();
    return 0;
}