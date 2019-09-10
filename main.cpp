#include <iostream>
#include "Set.hpp"

int main() {
    FILE* file = fopen("get.txt", "r");

    Set* newset = new Set(file);
    newset->show();

    std::cout << (newset->isField() ? "Это поле" : "Это не поле\n");
    return 0;
}