/*Solución al problema "Life, the Universe, and Everything" de SPOJ, https://www.spoj.com/problems/TEST/
El programa se encarga de recibir números enteros. En caso de que el número sea igual a 42, el programa para.
En caso contrario se imprime el número. */
#include <iostream>
using namespace std;

int main(){
    int n;
    while (true){
        cin >> n;
        if (n == 42){
            break;
        }
        cout << n << endl;
    };
    return 0;
}