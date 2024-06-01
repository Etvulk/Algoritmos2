#include <iostream>
#include <vector>
#include <utility>

using namespace std;

vector<int> ans;
vector< pair<long long, int> > nums;

void merge(vector< pair<long long, int> > &array, vector< pair<long long, int> > &leftArray, vector< pair<long long, int> > &rightArray){
    
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

void mergesort(vector< pair< long long, int> > &array){

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
    vector< pair< long long, int> > leftArray(mid);
    vector< pair< long long, int> > rightArray(length - mid);

    int j = 0;

    //Armamos la parte izquierda y derecha.
    for (int i = 0; i < length; i++){
        if (i < mid){
            leftArray[i].first = array[i].first;
            leftArray[i].second = array[i].second;
        }

        else{
            rightArray[j].first = array[i].first;
            rightArray[j].second = array[i].second;
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

int main(){
    int t;
    cin >> t;
    for (int i = 0; i < t; i++){
        int n;
        cin >> n;

        ans.resize(n);
        nums.resize(n);
        
        /*Como el problema nos pide que la solución este
        en el mismo orden que el input, entonces almacenamos
        los números en pares, de manera que la primera coordenada
        sea el numero y la segunda su indice.*/
        for (int i = 0; i < n; i++){
            cin >> nums[i].first;
            nums[i].second = i;
        }

        //Ordenamos el arreglo de pares.
        mergesort(nums);

        /*La solución sera de la siguiente manera. Seleccionamos 
        el primer numero del arreglo y le asignamos el valor del 
        numero a la  variable "score". Luego comparamos con
        el siguiente numero del arreglo, si el valor de "score"
        es mayor o igual, entonces se le suma a "score" el valor del
        numero y avanzamos otra casilla para compararlo con el siguiente
        numero. En caso contrario si "score" no es mayor o igual a el
        numero con el que se esta comparando, entonces el primer número
        que seleccionamos ya no puede seguir, por lo tanto la cantidad de
        números que pudo eliminar es la cantidad de casillas que se movió
        en este caso "j" pero como no lo debemos contar a el mismo, entonces
        seria "j - 1". Luego pasamos a el siguiente numero del arreglo y repetimos
        los mismos pasos, hasta que lleguemos a el ultimo elemento. Pero hay que 
        tener en cuenta que el "score" acumulado del número anterior se guarda para
        el siguiente, lo que nos ahorra volver a sumar los números anteriores a el.*/
        long long score = 0;
        int j = 0;

        for (int i = 0; i < n; i++){
            if (i == j){
                score += nums[i].first;
                j++;
            }
            while(j < n && score >= nums[j].first){
                score += nums[j].first;
                j++;
            }

            ans[nums[i].second] = j - 1;
        }

        for (int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }

        cout << endl;
    }
    return 0;
}