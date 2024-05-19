//Solución al problema "Sasha and the Beautiful Array" the codeforces, https://codeforces.com/problemset/problem/1929/A

#include <iostream>

using namespace std;

const int max_len = 100;
int list_num[max_len];

int main(){
    int t;
    cin >> t;
    //Loop de los casos.
    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        for (int i = 0; i < n; i++){
            cin >> list_num[i];
        }
        
        
        //Bubble sort.
        for (int i = 0; i < n - 1; i++){
            
            for (int j = 0; j < n - i - 1; j++){
                if (list_num[j] > list_num[j + 1]){
                    swap(list_num[j], list_num[j + 1]);
                }
            }
        }

        /*Luego de ordenar la lista de números, veamos que para obtener la "belleza"
        del arreglo es de la forma belleza = (a2−a1)+(a3−a2), tomando como ejemplo un arreglo
        de tres elementos. Esto es una serie telescópica, por lo tanto para un arreglo de 
        tamaño "n" la solución seria belleza = an - a1*/
        int ans;
        ans = list_num[n-1] - list_num[0];
        cout << ans << endl;
    }
    return 0;
}