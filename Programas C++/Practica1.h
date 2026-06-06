#ifndef DYV_H
#define DYV_H

#include <string>
using namespace std;

struct Resultado {
    int coincidencias;
    int inicio;
};

Resultado dyv_coincidencias(const string &A, const string &B, int left, int right, int m);
Resultado dyv_coincidenciasIterativo(const string &A, const string &B, int m, int n);

#endif