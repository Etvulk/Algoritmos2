//Solución al problema "RK sorting" de SPOJ, https://www.spoj.com/problems/RKS/
#include <iostream>
#include <vector>
#include <utility>

using namespace std;
int unicos;
vector< pair<int,int> > repeticiones(0); 

/*Función que retorna la segunda coordenada de una lista de pares.
el argumento "n" es el tamaño de la lista y el argumento "m" es la
primera coordenada del vector del que se desea obtener la segunda
coordenada.*/
pair<int,int> obtener_2_coordenada(int &m){
    
    pair<int,int> result;
    for (int i = 0; i < unicos; i++){
        if (repeticiones[i].first == m){
            result.first = repeticiones[i].second;
            result.second = i;
            return result;
        }
    }
    return result;
}

//Función para crear un árbol binario dado un arreglo, cada padre es mayor o igual a sus hijos.
void maxHeap(vector<int> &arr, int n, int i){

    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    /*Nuestro criterio para determinar que valor es mayor a otro es:
    Sean "a" y "b" dos valores y "a" != "b", si "a" se repite menos que "b", entonces a < b
    El otro caso es si "a" y "b" se repiten la misma cantidad de veces, pero el indice de "a"
    en la secuencia es menor que el de "b", entonces a < b*/
    pair<int,int> root = obtener_2_coordenada(arr[largest]);
    pair<int,int> left = obtener_2_coordenada(arr[l]);
    if (l < n && (left.first < root.first || (left.first == root.first && left.second > root.second))){
        largest = l;
    }

    root = obtener_2_coordenada(arr[largest]);
    pair<int,int> right = obtener_2_coordenada(arr[r]);
    if (r < n && (right.first < root.first || (right.first == root.first && right.second > root.second))){
        largest = r;
    }
    
    if (largest != i){
        swap(arr[i], arr[largest]);

        maxHeap(arr, n, largest);
    }
}


void heapSort(vector<int> &arr, int length){

    
    for (int i = length / 2 - 1; i >= 0; i--){
        maxHeap(arr, length, i); 
    }

    for (int i = length - 1; i >= 0; i--) {
        //Ponemos a el mayor valor actual en la ultima posición.
        swap(arr[0], arr[i]);

        //Ordenamos otra vez el árbol binario, sin contar el ultimo nodo modificado, en donde se puso el mayor valor actual.
        maxHeap(arr, i, 0);
        
    }
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
    unicos = 0;
    int pivote;

    /* Repeticiones va a almacenar pares donde la primera coordenada
    es el elemento que esta en la secuencia, y la segunda coordenada
    es la cantidad de veces que el elemento se repite en la secuencia.*/
    repeticiones.resize(n); 

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
    
    //Ordenamos con heap Sort.
    heapSort(nueva_secuencia, n);

    for (int i = 0; i < n; i++){
        cout << nueva_secuencia[i] << " ";
    }

    cout << endl;
}