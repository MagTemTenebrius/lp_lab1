//
// Created by tenebrius on 9/6/19.
//

#ifndef INC_1_SET_HPP
#define INC_1_SET_HPP


#include <cstdio>

class Set {
    int n;
    int* mass;
    int** massMult;
    int** massSumm;
//(коммутативность сложения, ассоциативность сложения, существование нейтрального элемента по сложению, существование
// обратного по сложению,
// коммутативность умножения, ассоциативность умножения, существование нейтрального по умножению, существование
// обратного по умножению, дистрибутивность).
    bool comm_summ();
    bool assoc_summ();
    bool neitral_summ();
    bool obratn_summ();

    bool comm_mult();
    bool assoc_mult();
    bool neitral_mult();
    bool obratn_mult();

    bool distribut();

    bool plus(int a, int b);
    bool mult(int a, int b);

public:
    void show();
    bool isField();
    int find_index(int a);
    int neitral_sum;
    int neitral_mul;
    int plus_test(int a, int b);
    int mult_test(int a, int b);

    Set(FILE* file);
};


#endif //INC_1_SET_HPP
