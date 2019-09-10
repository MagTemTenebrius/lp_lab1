//
// Created by tenebrius on 9/6/19.
//

#include <iostream>
#include "Set.hpp"

using namespace std;

Set::Set(FILE *file) {
    fscanf(file, "%d", &n);
    this->mass = new int[n];

    char probel;
    fscanf(file, "%c", &(probel));

    for(int i = 0; i < n; i++) {
        fscanf(file, "%c", &(this->mass[i]));
        this->mass[i]-='0';
        fscanf(file, "%c", &(probel));
    }

    this->massMult = new int*[n];
    this->massSumm = new int*[n];

    for(int i = 0; i < n; i++) {
        this->massMult[i] = new int[n];
        this->massSumm[i] = new int[n];
    }

    for(int i = 0; i < n*n; i++) {
        fscanf(file, "%c", &(this->massSumm[i/n][i%n]));
        this->massSumm[i/n][i%n]-='0';
        fscanf(file, "%c", &(probel));
    }
    for(int i = 0; i < n*n; i++) {
        fscanf(file, "%c", &(this->massMult[i/n][i%n]));
        this->massMult[i/n][i%n]-='0';
        fscanf(file, "%c", &(probel));
    }

//    Тимофей Херьянов
}

void Set::show() {
    cout << "Таблица для суммы" << endl;
    for(int i = -1; i < n; i++) {
        if(i==-1) {
            for(int k = -1; k < n; k++) {
                if(k==-1) {
                    cout << "  \t";
                    continue;
                }
                cout << mass[k] << "\t";
            }
            cout << endl;
            continue;
        }
        for(int j = -1; j < n; j++) {
            if(j==-1) {
                cout << mass[i] << "|\t";
                continue;
            }
            cout << massSumm[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Таблица для умнажения" << endl;
    for(int i = -1; i < n; i++) {
        if(i==-1) {
            for(int k = -1; k < n; k++) {
                if(k==-1) {
                    cout << "  \t";
                    continue;
                }
                cout << mass[k] << "\t";
            }
            cout << endl;
            continue;
        }
        for(int j = -1; j < n; j++) {
            if(j==-1) {
                cout << mass[i] << "|\t";
                continue;
            }
            cout << massMult[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int Set::find_index(int a) {
    for(int i = 0; i < this->n; i++) {
        if(a==mass[i])
            return i;
    }
    return -1;
}

int Set::plus_test(int a, int b) {
    int index_a = find_index(a);
    int index_b = find_index(b);
    return massSumm[index_a][index_b];
}
int Set::mult_test(int a, int b) {
    int index_a = find_index(a);
    int index_b = find_index(b);
    return massMult[index_a][index_b];
}

bool Set::isField() {
    return comm_summ() && comm_mult() && assoc_summ() && assoc_mult() && neitral_summ() && neitral_mult() &&
    obratn_summ() && obratn_mult() && distribut();
}

bool Set::comm_summ() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
            if(massSumm[i][j]!=massSumm[j][i]){
                cout << "Коммутативность суммы не выполнена" << endl;
                return false;
            }
    return true;
}
bool Set::comm_mult() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < i; j++)
            if(massMult[i][j]!=massMult[j][i]){
                cout << "Коммутативность умножения не выполнена" << endl;
                return false;
            }
    return true;
}

bool Set::assoc_summ() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                if(plus_test(mass[i], plus_test(mass[j], mass[k]))!=plus_test(plus_test(mass[i], mass[j]), mass[k])) {
                    cout << "Ассоциативность суммы не выполнена" << endl;
                    return false;
                }
    return true;
}
bool Set::assoc_mult() {
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                if(mult_test(mass[i], mult_test(mass[j], mass[k]))!=mult_test(mult_test(mass[i], mass[j]), mass[k])) {
                    cout << mass[i] << "* (" << mass[j] << "*" << mass[k] <<")!=(" << mass[i] << "*" << mass[j] << ")*" << mass[k] << endl;
                    cout << "Ассоциативность уумножения не выполнена" << endl;
                    return false;
                }
    return true;
}

bool Set::neitral_summ() {
    for(int j = 0; j < n; j++) {
        if(plus_test(mass[0], mass[j]) == mass[0]){
            int k = 1;
            for(int i = 1; i < n; i++) {
                if(plus_test(mass[i], mass[j]) != mass[i]) {
                    k = 0;
                    break;
                }
            }
            if(k){
                neitral_sum = j;
                return true;
            }
        }
    }
    cout << "Нейтральный по сложению не найден" << endl;
    return false;
}
bool Set::neitral_mult() {
    for(int j = 0; j < n; j++) {
        if(mult_test(mass[0], mass[j]) == mass[0]){
            int k = 1;
            for(int i = 1; i < n; i++) {
                if(mult_test(mass[i], mass[j]) != mass[i]) {
                    k = 0;
                    break;
                }
            }
            if(k){
                neitral_mul = j;
                return true;
            }
        }
    }
    cout << "Нейтральный по умножению не найден" << endl;
    return false;
}

bool Set::obratn_summ() {
    for(int i = 0; i < n; i++) {
        int k = 0;
        for(int j = 0; j < n; j++) {
            if(plus_test(mass[i], mass[j]) == neitral_sum){
                k = 1;
                break;
            }
        }
        if(!k) {
            cout << "Обратный по сложению не найден" << endl;
            return false;
        }
    }
    return true;
}
bool Set::obratn_mult() {
    for(int i = 0; i < n; i++) {
        int k = 0;
        for(int j = 0; j < n; j++) {
            if(mult_test(mass[i], mass[j]) == neitral_mul || mass[i] == neitral_sum){
                k = 1;
                break;
            }
        }
        if(!k) {
            cout << "Обратный по умножению не найден, нейтральный эл-т = " << neitral_mul << endl;
            return false;
        }
    }
    return true;
}

bool Set::distribut(){
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++)
                if(mult_test(mass[i], plus_test(mass[j], mass[k]))!=plus_test(mult_test(mass[i], mass[j]), mult_test(mass[i], mass[k]))) {
                    cout << "Дистрибутивность не выполнена" << endl;
                    return false;
                }
    return true;
}