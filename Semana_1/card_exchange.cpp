/*Solución al problema "Card Exchange" de codeforces, https://codeforces.com/contest/1966/problem/A
Dado un número de cartas "n", el programa remplaza de la mano de cartas una cantidad "k" de cartas que tengan el mismo valor.
El objetivo es terminar con el mínimo número de cartas posibles en la mano.*/

#include <iostream>
#include <vector>


int main(){
    int t;
    std::cin >> t;
    for (int c = 0; c < t; c++){
        int n, k;
        std::cin >> n >> k;

        std::vector<int> cartas(n);
        

        //Almacenamos el número de las cartas.
        for (int i = 0; i < n; i++){
            std::cin >> cartas[i];
        }

        //En caso de que "k" sea mayor a "n", devolvemos "n".
        if (k > n){
            std::cout << n << std::endl;
            continue;
        }

        int carta;
        int cantidad;
        int posicion[k];
    
        //Vemos si hay "k" cartas del mismo número.
        for  (int j = 0; j < cartas.size(); j++){       
            carta = cartas[j];
            cantidad = 0;

            for(int i = 0; i < cartas.size(); i++){
                if (cartas[i] == carta){
                    posicion[cantidad] = i;
                    cantidad++;
                }
                if (cantidad >= k){
                    break;
                }
            }
            if (cantidad >= k){
                break;
            }
        }

        //En caso de que no se repitan "k" cartas del mismo número, devolvemos "n".
        if (cantidad < k){
            std::cout << n << std::endl;
            continue;
        }

        //Se eliminan "k" cartas del mismo número.
        for (int i = 0; i < k; i++){
            cartas.erase(cartas.begin() + posicion[i] - i);
        }
        //Se agrega "k-1" cartas de un número que este presente en la mano.
        cartas.insert(cartas.begin(), k-1, cartas[0]);
    
        
        //Se hacen los mismo pasos de eliminar y agregar hasta que el tamaño de la mano sea igual a "k-1".
        while (cartas.size() != k-1){
            cartas.erase(cartas.begin(), cartas.begin() + k);
            cartas.insert(cartas.begin(), k-1, cartas[0]);
        }

        std::cout << cartas.size() << std::endl;
    }
    return 0;
}