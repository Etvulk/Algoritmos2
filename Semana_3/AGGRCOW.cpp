#include <iostream>
#include <vector>

using namespace std;


void merge(vector<int> &array, vector<int> &leftArray, vector<int> &rightArray){
    
    int length = array.size();

    int leftLength = length / 2;
    int rightLength = length - leftLength;

    int i, l, r;
    i = 0;
    l = 0;
    r = 0;

    while (l < leftLength && r < rightLength){
        /*Si el elemento de el arreglo de la izquierda
        es menor que el elemento de el arreglo de la derecha,
        entonces se le asigna a el arreglo "padre"
        (es decir el arreglo que fue picado en 2) el valor 
        de el elemento de el arreglo de la izquierda.*/
        if (leftArray[l] < rightArray[r]){
            array[i] = leftArray[l];
            i++;
            l++;
        }
        else{
            array[i] = rightArray[r];
            i++;
            r++;
        }
    }

    /*Si quedaron elementos sin asignar en el arreglo de la izquierda,
    entonces estos son asignados a el arreglo "padre".*/
    while (l < leftLength){
        array[i] = leftArray[l];
        i++;
        l++;
    }

    /*Si quedaron elementos sin asignar en el arreglo de la derecha,
    entonces estos son asignados a el arreglo "padre".*/
    while (r < rightLength){
        array[i] = rightArray[r];
        i++;
        r++;
    }
}

void mergesort(vector<int> &array){

    int length = array.size();

    /*Como "mergesort" es una función recursiva, necesitamos un caso base,
    en este caso es cuando la longitud del arreglo menor o igual a 1, ya que
    el arreglo no se podrá volver a partir entre 2.*/
    if (length <= 1){
        return;
    }

    //Se calcula el centro de el arreglo.
    int mid = length / 2;

    //El arreglo se divide en dos partes, izquierda y derecha.
    vector<int> leftArray(mid);
    vector<int> rightArray(length - mid);

    int j = 0;

    //Armamos la parte izquierda y derecha.
    for (int i = 0; i < length; i++){
        if (i < mid){
            leftArray[i] = array[i];
        }

        else{
            rightArray[j] = array[i];
            j++;
        }
    }

    /*Llamada recursiva para repetir el proceso
    en la parte izquierda y derecha.*/
    mergesort(leftArray);
    mergesort(rightArray);

    /*Se llama a la función "merge" para ordenar los arreglos
    que fueron creados al partir en 2 multiples veces el arreglo original.*/
    merge(array, leftArray, rightArray);

}

/*Función para determinar si dada una distancia y una cantidad
de vacas, es posible darles un establo a todas.*/
bool count_cows(vector<int> stalls, int mid, int n, int c){
    int count = 1;
    int last_cow = 0;

    for (int i = 0; i < n; i++){
        if (stalls[i] - stalls[last_cow] >= mid){
            last_cow = i;
            count++;
        }
    }
    
    return count >= c;
}


int binary_search(vector<int> array, int n, int c){
    /*A los pivotes "l" y "r" se les asigna el valor de el 
    primer elemento del array y el valor de el ultimó elemento,
    ya que en este caso, nos importa es calcular las distancias 
    entre establos.*/
    int l = array[0];
    int r = array[n - 1];
    int ans;

    while(l < r){
        
        int mid = l + (r - l) / 2;

        /*Si se cumple la condición, entonces se cambia el pivote "l" a "mid + 1"
        para probar si hay números mayores que cumplen la condición*/
        if (count_cows(array, mid, n, c)){
            ans = mid;
            l = mid + 1;
        }

        else{
            r = mid;
        }
    }
    return ans;

}

int main(){
    int t;
    cin >> t;

    for (int i = 0; i < t; i++){
        
        int n, c;
        cin >> n >> c;

        vector<int> stalls(n);

        for (int i = 0; i < n; i++){
            cin >> stalls[i];
        }

        //Ordenamos la lista de las posiciones de los establos(stalls).
        mergesort(stalls);
    
        
        int ans;
        /*Usamos binary search para buscar la mayor distancia posible, 
        tal que todas las vacas puedan ser asignadas a un establo.*/
        ans = binary_search(stalls, n, c);
        std::cout << ans << endl; 
    }

    return 0;
}