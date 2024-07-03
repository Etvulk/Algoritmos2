//Solucion al problema "QUEUEEZ - Easy Queue" de SPOJ, https://www.spoj.com/problems/QUEUEEZ/
#include <iostream>

using namespace std;

//En "Element" esta el valor de el elemento y un apuntador a el siguiente elemento.
struct Element{
    int x;
    Element *next_element;

    //Se inicializa a "x" como "0" y a "next_element" como un null pointer.
    Element(){
        x = 0;
        next_element = nullptr;
    }
};


struct Queue{
    /*Tenemos dos apuntadores, "start" que apunta el primer elemento de la cola
    y "end" que apunta a el ultimo elemento de la cola.*/
    Element *start;
    Element *end;

    //Se inicializa "start" y "end" como null pointers.
    Queue(){
        start = nullptr;
        end = nullptr;
    }

    //Función para añadir elementos a la cola.
    void enqueue(int y){
        
        Element *new_element = new Element;
        new_element -> x = y;

        //En caso de que la cola este vacía, el nuevo elemento se establece como el primer elemento.
        if (start == nullptr){
            start = new_element;
            //Como solo hay un elemento entonces el ultimo elemento es igual a el primero.
            end = start;
            return;
        }

        //El nuevo elemento se posiciona después de el ultimo.
        end -> next_element = new_element;
        //Ahora el ultimo elemento sera el nuevo elemento.
        end = new_element;
    }

    //Función para quitar el primer elemento de la cola.
    void dequeue(){
        //Si no hay elementos no se hace nada.
        if (start == nullptr){
            return;
        }
        //Asignamos como primer elemento a el elemento segundo elemento.
        start = start -> next_element;
    }

    //Función que imprime el primer elemento de la cola.
    void print_first_element(){
        //Si no hay elementos se imprime "Empty!".
        if (start == nullptr){
            cout << "Empty!" << "\n";
            return;
        }
        //Se imprime el primer elemento.
        cout << start -> x << "\n";
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int t;
    Queue q;

    cin >> t;

    for (int i = 0; i < t; i++){
        //En la variable "action" se almacena las "queries" que se van a hacer con la cola.
        int action;
        int n;

        cin >> action;

        if (action == 1){
            cin >> n;
            q.enqueue(n);
        }

        else if(action == 2){
            q.dequeue();
        }

        else if (action == 3){
            q.print_first_element();
        }
        
    }
}



