#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>   
#include <random>
#include <algorithm>
#include <cmath>
#include "Practica1.h"

using namespace std;
using namespace std::chrono;

//Generamos el mejor caso en el que ambas cadenas serán iguales, entonces en la primera comprobación ya se cumplirá la condición de que
//coincidencias==m y terminará el algoritmo, será super rápido
pair<string, string> generarMejorCaso(int longitud) {
    string A(longitud, 'a'); // Crea un string de tamaño 'longitud' lleno de 'a'
    string B(longitud, 'a'); // Crea otro string idéntico
    return {A, B};           // Devolvemos el par
}

// Genera dos cadenas sin coincidencias, para el peor caso, en el que se tenga que evaluar la cadena entera para poder llegar a un resultado
pair<string, string> generarPeorCaso(int longitud) {
    string A(longitud, 'a'); // Llena A con 'a'
    string B(longitud, 'b'); // Llena B con 'b'
    return {A, B};           // Devolvemos el par
}
//Con esta función lo que buscamos es dejar un main más sencillo, en la que medimos los tiempos.Los miramos gracias a la libreria chrono
// y con fstream la metemos en un excel para poder mostrar la grafica
double medirTiempo(const string& A, const string& B, int n, int m) {
    auto start = high_resolution_clock::now();
    
    // Llamamos a tu algoritmo
    dyv_coincidencias(A, B, 0, n - 1, m);
    
    auto end = high_resolution_clock::now();
    duration<double, std::milli> duracion = end - start;
    return duracion.count();
}

//Añadimos la función para calcular la mediana
double mediana(std::vector<double> v) {
    int n = v.size();
    if (n == 0) return 0.0;

    std::sort(v.begin(), v.end());

    if (n % 2 == 1)
        return v[n / 2];
    else
        return (v[n / 2 - 1] + v[n / 2]) / 2.0;
}

int main() {
    unsigned int semilla = 42;
    

    int c_0 = 1000;
    vector<int> longitudes;
    int m = 100;    //Como nos pedían en el enunciado, tomamos la m constante.
    
    //Creamos un vector para guardar los diferentes tamaños con los que vamos a probar el tiempo de ejecucion para luego poder llamar a las funciones con esos tamaños.
    for(int i = 0; i <= 10; i++){
        int n = c_0 * pow(2,i);
        longitudes.push_back(n);
    }
   
    ofstream archivo_csv("resultados_tiempos.csv");  //Creamos y abrimos un archivo Excel (CSV)
    
    
    archivo_csv << "Longitud(n), DyV_Mejor(ms), DyV_Peor(ms)\n"; //Escribimos la cabecera del Excel (las columnas separadas por coma)
    
    cout << "Calculando tiempos, por favor espera..." << endl;

    for (int n : longitudes) {
        //Generamos las cadenas para el mejor caso para cada una de las longitudes y despues extraemos cada cadena del resultado
        pair<string,string> mejorCaso = generarMejorCaso(n);
        string mejorA = mejorCaso.first;
        string mejorB = mejorCaso.second;
        
        vector<double> tiempos_dyv_mejor;
        for(int j = 0;j < 10;j++){

            double tiempo = medirTiempo(mejorA,mejorB,n,m); 

            tiempos_dyv_mejor.push_back(tiempo);      //Guardamos el tiempo en el vector

        }
        double mediana_dyv_mejor = mediana(tiempos_dyv_mejor);
        //Ahora estudiamos para el peor caso, en el que se tenga que evaluar la cadena entera
        pair<string,string> peorCaso = generarPeorCaso(n);
        string peorA = peorCaso.first;
        string peorB = peorCaso.second;

        vector<double> tiempos_dyv_peor;
        for(int j = 0;j < 10;j++){

            double tiempo = medirTiempo(peorA,peorB,n,m); 

            tiempos_dyv_peor.push_back(tiempo);      //Guardamos el tiempo en el vector

        }
        //Calculamos las medianas de los 10 tiempos del algoritmo
        double mediana_dyv_peor = mediana(tiempos_dyv_peor);

        //Escribimos los resultados directamente en el archivo del excel (CSV)
        archivo_csv << n << ", "
                    << mediana_dyv_mejor << ", " 
                    << mediana_dyv_peor << "\n";
        
        cout << "Test completado para n = " << n << endl;
    }

    
    archivo_csv.close(); //Cerramos el archivo
    
    cout << "Los datos se encuentran en el archivo .CSV" << endl;
    return 0;
}