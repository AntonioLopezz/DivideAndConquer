#include <iostream>
#include "Practica1.h"
#include <cassert>
#include <random>

using namespace std;

string generarCadenaAleatoria(int longitud, unsigned int semilla){   //Definimos la funcion para generar cadenas aleatorias
    string cadena ="";          //Inicializamos la cadena como una cadena vacia

    mt19937 gen(semilla);       //Arrancamos el motor de aleatoriedad con la semilla pasada como parámetro(nos hemos fijado en el codigo del gitHub)
    uniform_int_distribution<> dist('a','z');       //Establecemos un reparto uniforme (con la misma probabilidad) entre valores desde a hasta z

    for(int i = 0; i < longitud; i++){              //Dentro de la longitud de la cadena, para cada posicion hasta llegar a la longitud, establecemos un valor aleatorio
        cadena += (char)dist(gen);              //A la cadena le vamos sumando el caracter generado en la distribucion dist y obligamos a que sea un caracter con (char)
    }                                           //gen lo que nos devuelve es un numero dentro de los valores de dist(entre a y z) y char lo convierte a caracter
    return cadena;                              //Esta funcion nos devuelve la cadena generada aleatoriamente
}

int main() {
    unsigned int semilla = 42;                  //Establecemos un valor fijo para la semilla como en el codigo que se nos daba de referencia en gitHub

    vector<int> longitudes = {10,20,50,150,300};  //Cogemos un vector de longitudes para hacer varios casos de prueba con cadenas de diferentes longitudes

    for(int i = 0; i < longitudes.size();i++){  //Recorremos el vector de longitudes
        
        string A = generarCadenaAleatoria(longitudes[i],semilla + i);       //Para cada longitud generamos una cadena nueva aleatoria, le sumamos i para que para diferentes longitudes sean cadenas distintas
        string B = generarCadenaAleatoria(longitudes[i],semilla + i + 100); //Cambiamos la semilla para que ambas cadenas no sean iguales

        int m = max(1, longitudes[i] / 2);          //Establecemos un valor de m "fijo" y ponemos la funcion max para asegurarnos de que m nunca sea 0.
                                                    //Podriamos generar un valor aleatorio de m tambien pero pensamos que era mucho lio de implementacion

        Resultado dyvItOut = dyv_coincidenciasIterativo(A,B,m,longitudes[i]);   //Llamamos a ambas funciones para las mismas cadenas y mismas longitudes
        Resultado dyvOut = dyv_coincidencias(A,B,0,longitudes[i] - 1,m);        //Se le resta 1 porque estamos fijandonos en indices no en longitud en esta funcion

        assert(dyvItOut.coincidencias == dyvOut.coincidencias);         //Nos aseguramos de que devuelven las mismas coincidencias y los mismos valores

        cout<<"-----------------"<<endl;
        cout<<"Tamano n = "<<longitudes[i]<<endl;
        cout<<"Resultado DyV: coincidencias "<< dyvOut.coincidencias<<endl;
        cout<<"Resultado Iterativo: coincidencias "<< dyvItOut.coincidencias<<endl;
        cout<<"Test superado para un tamano n = "<<longitudes[i]<<" con ventana m= "<<m<<endl;

    }

    cout<<"Todos los test han sido superados"<<endl;
    return 0;
}