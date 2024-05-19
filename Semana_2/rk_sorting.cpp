//Solución al problema "RK sorting" de SPOJ, https://www.spoj.com/problems/RKS/
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

/*Función que retorna la segunda coordenada de una lista de pares.
el argumento "n" es el tamaño de la lista y el argumento "m" es la
primera coordenada del vector del que se desea obtener la segunda
coordenada.*/
int obtener_2_coordenada(vector< pair<int,int> > &lista_pares, int &n, int &m){
    for (int i = 0; i < n; i++){
        if (lista_pares[i].first == m){
            return lista_pares[i].second;
        }
    }
    return 0;
}



int main(){
    int n,c;
    cin >> n >> c;
    
    vector<int> secuencia(n);
    vector<int> nueva_secuencia(n);
    
    for (int i = 0; i < n; i++){
        cin >> secuencia[i];
    }

    int agregados = 0;
    /*La variable unicos se encarga de contar cuentos números son 
`   unicos, esto nos servirá para los indices de la lista de pares.*/
    int unicos = 0;
    int pivote;

    /* Repeticiones va a almacenar pares donde la primera coordenada
    es el elemento que esta en la secuencia, y la segunda coordenada
    es la cantidad de veces que el elemento se repite en la secuencia.*/
    vector< pair<int,int> > repeticiones(n); 

    for (int i = 0; i < n; i++){
        if (secuencia[i] == 0){
            continue;
        }
        //Agregamos a el número como la primera coordenada de un par.
        repeticiones[unicos].first = secuencia[i];

        //El pivote almacena el número que se le van a contar las veces que se repite.
        pivote = secuencia[i];
        for (int j = 0; j < n; j++){
            if (secuencia[j] == pivote){
                //Se agrega el número junto a sus repeticiones a la nueva secuencia.
                nueva_secuencia[agregados] = secuencia[j];
                agregados++;   
                //Se almacena en la segunda coordenada del par las veces que se repite el número.
                repeticiones[unicos].second += 1; 
                secuencia[j] = 0;
            }
        }
        unicos++;
    }

    /*Bubble sort para ordenar la secuencia. La relación entre dos números consiste en que
    el número que menos se repita es mayor a el número que mas se repita.*/
    for (int i = 0; i < n - 1; i++){

        for (int j = 0; j < n - i; j++){
            if (obtener_2_coordenada(repeticiones, unicos, nueva_secuencia[j]) < obtener_2_coordenada(repeticiones, unicos, nueva_secuencia[j + 1])){
                swap(nueva_secuencia[j], nueva_secuencia[j+1]);
            }
        }
    }


    for (int i = 0; i < n; i++){
        cout << nueva_secuencia[i] << " ";
    }

    cout << endl;
}