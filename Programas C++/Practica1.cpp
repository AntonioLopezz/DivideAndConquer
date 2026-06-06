#include "Practica1.h"
#include <iostream>
#include <algorithm>
using namespace std;

//Pasamos por referencia las cadenas para no tener que estar creando copias de dichas cadenas cada vez que las consultemos, y ponemos el const para protegerlas por si acaso en alguna consulta se intentara
//modificar ya que están pasadas por referencias y se modificarían en memoria
Resultado dyv_coincidencias(const string &A, const string &B, int left, int right, int m){
    int tamano_actual = right - left + 1;       //Calculamos el tamaño de la cadena pasada como parámetro con las variables left y right que nos indican los indicies iniciales y finales
    int puntos = 0;                             //Inicializamos a 0 el numero de coincidencias
    if(tamano_actual < m){                      //Estudiamos el primer caso de que sea menor, como no es válido este caso, devolvemos -1
        return {-1,-1};
         
    }

    if(tamano_actual == m){                     //En el caso de que sea el tamaño de la cadena igual que el de la ventana que buscamos
        for(int i = left; i <= right; i++){     //Con un bucle for, recorremos desde el inicio de la cadena(variable left) hasta el final de la cadena(right incluido por eso <=)
            if(A[i] == B[i]){                   //Si ambos elementos de ambas cadenas coinciden, sumamos 1 a la variable global
                puntos++;
            }
        }
        return {puntos,left};                   //Devolvemos las coincidencias y el inicio de la ventana
    }

    //if(tamano_actual > m){ (Se comenta porque nos salia un warning)                      //Este es el caso que se nos va a dar al principio normalmente, entonces tenemos que dividir la cadena inicial en subcadenas más pequeñas
        int mid = (left + right) / 2;           //Cogemos la cadena y la dividimos por la mitad, sumamos indices izquierdo y derecho para hacerlo más preciso ya que no es lo mismo el tamaño(10) a los indices (0 a 9)
        
        //Una vez dividida la cadena vamos a tener la mitad izquierda, la derecha y por el centro las cadenas de tamaño m. Ahora nos toca llamar a la recursividad 
        Resultado izq = dyv_coincidencias(A,B,left,mid,m);      //Guardamos en izq lo que nos devuelva la funcion con limites desde el principio (left) hasta la mitad, estudiamos la mitad izquierda
        
        //Como nos dicen que si varias ventanas coinciden, cualquiera es válida, en cuanto se encuente una ventana con las mismas coincidencias que m,
        //solamente se podrá igualar esta cifra, entonces devolvemos directamente y nos ahorramos el seguir con la ejecucion
        if(izq.coincidencias == m){             
            return izq;
        }
        
        Resultado der = dyv_coincidencias(A,B,mid+1,right,m);   //A partir de la mitad(mid + 1) hasta el final será la mitad derecha, pues guardamos en der lo que nos devuelva la función para la mitad derecha


        //Hacemos lo mismo con der, lo explicado que se ha hecho con izq
        if(der.coincidencias == m){
            return der;
        }


        //Solo se llega hasta aqui si ni izquierda ni derecha tenian el mismo numero de coincidencias que m
        Resultado front = {-1,-1};                         //Inicializamos para estudiar los casos en los que la ventana m cruce la mitad (a la que hemos llamado frontera)
                                                            //Ponemos -1 para asegurarnos de que aunque nos devuelva 0, se actualice el valor
        int inicio_frontera = max(left, mid - m + 2);       //Con esto nos aseguramos que la frontera iniciará dentro de la cadena, es como un bloqueo de seguridad. Esta función se explica más a fondo en la memoria por ahorrar espacio aquí

        for(int i = inicio_frontera; i <= mid; i++){        //Comenzamos a recorrer desde el inicio de la cadena, que será inicio_frontera, hasta mid, porque si ponemos el inicio después de mid, ya pasaría a la mitad derecha, caso der explicado arriba 
            int puntos_ventana = 0;                         //Como antes inicializamos a 0 las coincidencias para cada subcadena estudiada
            
            for(int k = i ; k < i + m; k++){                //Dentro de la ventana de tamaño m, vamos recorriendola y viendo cuáles son coincidencias y sumando uno a la variable
                if(A[k] == B[k]){
                    puntos_ventana++;
                }
            }
            if(puntos_ventana > front.coincidencias){       //La variable global inicializada al principio del caso, la actualizamos en caso de que sea mayor el número de coincidencias
                front.coincidencias = puntos_ventana;       //y guardamos en donde comienza esta ventana
                front.inicio = i;
                //Y aquí igual, en cuanto se encuentre una ventana con las mismas coincidencias, se termina la ejecución
                //La ponemos dentro de este if ya que sabemos que una ventana de este numero de coincidencias siempre va a ser mayor que las que ya habian
                //si lo pusieramos fuera, evaluariamos para todos los casos con un if innecesario
                if(front.coincidencias == m){
                    return front;
                }
            }

            
        }
        if(izq.coincidencias >= der.coincidencias && izq.coincidencias >= front.coincidencias){  //Por ultimo comparamos las 3 subcadenas finales que serán la izquierda, la derecha y la que más coincidencias tenga de las que están por la mitad
            return izq;                                                                         //Devolvemos la que más coincidencias tenga junto con su índice de donde empieza dicha subcadena
        } else if(der.coincidencias >= front.coincidencias){
            return der;
        } else {
            return front;
        }
}

//Este es el caso iterativo, el más predecible pero el menos eficiente
//A diferencia de la de DyV, aquí no tenemos ni left ni right, ya que nos da igual porque vamos a recorrerla de principio a fin
Resultado dyv_coincidenciasIterativo(const string &A,const string &B,int m, int n){
    int mejor_inicio = -1;          //Como antes inicializamos ambas variables globales para poder ir comparando y guardando el mejor caso
    int mejor_coincidencias = -1;
    for(int i = 0; i <= n - m; i++){        //Con este primer bucle lo que hacemos es ir recorriendo la cadena principal hasta que se nos permita, es decir, hasta que quepa la ventana de tamaño m.
                                            //Ya que si nos fijamos, si tuvieramos una ventana de tamaño 4 y nos quedaran 3 elementos, la última posición de la ventana estaría vacía y daría error.
        int puntos = 0;                     //Como antes inicializamos a 0 la variable de las coincidencias
        for(int k = 0; k < m; k++){         //Con este segundo bucle vamos recorriendo caracteres dentro de la propia ventana, hasta que lleguemos al tamaño m
            if(A[i+k] == B[i+k]){           //Como hemos inicializado la k a 0, la posicion de cada caracter será la posicion de la i mas la de k, se podría evitar esto inicializando k a i, k = i y haciendo A[k] == B[k]
                puntos++;                   //Vamos contando coincidencias
            }
        }
        if(puntos > mejor_coincidencias){
            mejor_coincidencias = puntos;   //Y aquí como antes vamos comparando y guardando la mejor cadena con su numero de coincidencias y su inicio
            mejor_inicio = i;
        }
    }
    return {mejor_coincidencias, mejor_inicio}; //Devolvemos el tipo resultado con coincidencias e inicio
}

