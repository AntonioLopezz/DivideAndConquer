#include <iostream>
#include <string>
#include <cassert>
#include "Practica1.h"

using namespace std;

void casoEnunciado(){
    
    string A = "cddabcdacc";
    string B = "cacddbcadc";
    int m = 5;
    Resultado res = dyv_coincidencias(A,B,0,A.length() - 1, m);
    assert(res.inicio == 5);
    assert(res.coincidencias == 2);

}

void casoPrincipio(){
        string A = "abcdejjjjj";
        string B = "abcdeiiiii";
    int m = 5;
    Resultado res = dyv_coincidencias(A,B,0,A.length() - 1, m);
    assert(res.inicio == 0);
    assert(res.coincidencias == 5);
}

void casoFinal(){
        string A = "abcdejjjjj";
        string B = "abcdrjjjjj";
    int m = 5;
    Resultado res = dyv_coincidencias(A,B,0,A.length() - 1, m);
    assert(res.inicio == 5);
    assert(res.coincidencias == 5);
}

void casoFrontera(){
        string A = "xxabcdeyyy";
        string B = "zzabcdezzz";
    int m = 5;
    Resultado res = dyv_coincidencias(A,B,0,A.length() - 1, m);
    assert(res.inicio == 2);
    assert(res.coincidencias == 5);
}

void casoCero(){
        string A = "abcdejjjjj";
        string B = "tesesfghhh";
    int m = 5;
    Resultado res = dyv_coincidencias(A,B,0,A.length() - 1, m);
    assert(res.coincidencias == 0);
}


int main() {
    casoEnunciado();
    casoPrincipio();
    casoFinal();
    casoFrontera();
    casoCero();
    cout<<"Todas las pruebas han sido superadas \n";
    return 0;
}
