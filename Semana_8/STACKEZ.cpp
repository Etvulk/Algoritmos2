//Solucion al problema "STACKEZ - Easy Stack" de SPOJ, https://www.spoj.com/problems/STACKEZ/
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

struct Stack{
    //Tenemos a el apuntador "top" que apunta al tope de la pila.
    Element *top;

    //Inicializamos "top" como null pointer.
    Stack(){
        top = nullptr;
    }

    //Función para añadir elementos a la pila.
    void push(int y){
        Element *new_element = new Element;

        //Como estamos en una pila a el nuevo elemento se posiciona en el tope de la pila.
        new_element -> x = y;
        //El nuevo elemento apunta a el elemento que esta abajo de el, es decir el "top" antiguo.
        new_element -> next_element = top;

        //Ahora "top" es igual a el nuevo elemento.
        top = new_element;
    }

    //Función para quitar el elemento que esta en el tope de la pila.
    void pop(){
        //En caso de que la pila sea vacía, no se hace nada.
        if (top == nullptr){
            return;
        }

        //Ahora "top" es igual a el elemento que estaba abajo de el "top" antiguo.
        top = top -> next_element;
    }

    //Función para imprimir al elemento que esta en el tope de la pila.
    void print_top(){
        //Si no hay elementos se imprime "Empty!".
        if (top == nullptr){
            cout << "Empty!" << "\n";
            return;
        }

        cout << top -> x << "\n";
    }
};  



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 
    int t;
    Stack s;

    cin >> t;


    for (int i = 0; i < t; i++){
        //En la variable "action" se almacena las "queries" que se van a hacer con la pila.
        int action;
        int n;

        cin >> action;

        if (action == 1){
            cin >> n;
            s.push(n);
        }

        else if(action == 2){
            s.pop();
        }

        else if (action == 3){
            s.print_top();
        }
        
    }
}