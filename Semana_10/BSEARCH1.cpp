//Solución a "BSEARCH1 - Binary search" de SPOJ, https://www.spoj.com/problems/BSEARCH1/
#include <iostream>

using namespace std;


struct Node {
    //En la variable "num" guardamos el valor del nodo, y en la variable "index" guardamos el indice del valor en la lista original.
    int num;
    int index;
    string color;
    Node *left, *right, *parent;

    //Constructor del nodo.
    Node(){
        num = 0;
        index = -1;
        color = "RED";
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

//Árbol rojo negro
struct RedBlackTree {

    Node* root;
    Node* NIL;

    //Constructor del árbol.
    RedBlackTree(){
        NIL = new Node;
        NIL -> num = 0;
        NIL -> color = "BLACK";
        NIL -> left = NIL -> right = NIL;
        root = NIL;
    }

    //Función que se encarga de rotar a la izquierda.
    void left_rotate(Node* x){
        Node* y = x -> right;
        x -> right = y -> left;
        if (y -> left != NIL) {
            y -> left -> parent = x;
        }
        y -> parent = x -> parent;
        if (x -> parent == nullptr) {
            root = y;
        }
        else if (x == x -> parent -> left) {
            x -> parent -> left = y;
        }
        else {
            x -> parent -> right = y;
        }
        y -> left = x;
        x -> parent = y;
    }

    //Función que se encarga de rotar a la derecha.
    void right_rotate(Node* x){
        Node* y = x -> left;
        x -> left = y -> right;
        if (y -> right != NIL) {
            y -> right -> parent = x;
        }
        y -> parent = x -> parent;
        if (x -> parent == nullptr) {
            root = y;
        }
        else if (x == x -> parent -> right) {
            x -> parent -> right = y;
        }
        else {
            x -> parent -> left = y;
        }
        y -> right = x;
        x -> parent = y;
    }

    //Función que se encarga de balancear el árbol luego de insertar un nuevo nodo.
    void fix_insert(Node* k){
        while (k != root && k -> parent -> color == "RED"){
            if (k -> parent == k -> parent -> parent -> left){
                //Tio
                Node* u = k -> parent -> parent -> right; 
                if (u -> color == "RED"){
                    k -> parent -> color = "BLACK";
                    u -> color = "BLACK";
                    k -> parent -> parent -> color = "RED";
                    k = k -> parent -> parent;
                }
                else{
                    if (k == k -> parent -> right) {
                        k = k -> parent;
                        left_rotate(k);
                    }
                    k -> parent -> color = "BLACK";
                    k -> parent -> parent -> color = "RED";
                    right_rotate(k -> parent -> parent);
                }
            }
            else{
                //Tio
                Node* u = k -> parent -> parent -> left; 
                if (u -> color == "RED") {
                    k -> parent -> color = "BLACK";
                    u -> color = "BLACK";
                    k -> parent->parent->color = "RED";
                    k = k -> parent -> parent;
                }
                else{
                    if (k == k -> parent -> left) {
                        k = k -> parent;
                        right_rotate(k);
                    }
                    k -> parent -> color = "BLACK";
                    k -> parent -> parent -> color = "RED";
                    left_rotate(k -> parent -> parent);
                }
            }
        }
        root -> color = "BLACK";
    }

    //Función que se encarga de buscar si un elemento esta en el árbol.
    Node* search_helper(Node* node, int data){
        if (node == NIL || data == node -> num) {
            return node;
        }
        if (data < node -> num) {
            return search_helper(node -> left, data);
        }
        return search_helper(node -> right, data);
    }




    // Insert function
    void insert(int data, int index)
    {
        Node* new_node = new Node;
        new_node -> num = data;
        new_node -> index = index;
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        Node* current = root;

        
        while (current != NIL) {
            parent = current;
            if (new_node->num < current->num) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        new_node->parent = parent;

        if (parent == nullptr) {
            root = new_node;
        }
        else if (new_node->num < parent->num) {
            parent->left = new_node;
        }
        else {
            parent->right = new_node;
        }

        if (new_node->parent == nullptr) {
            new_node->color = "BLACK";
            return;
        }

        if (new_node->parent->parent == nullptr) {
            return;
        }

        fix_insert(new_node);
    }

    //Función de búsqueda, inicializa "search_helper" con el nodo root.
    Node* search(int data){
        return search_helper(root, data);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    int q;
    cin >> n >> q;
    int before;
    before = 1000000000 + 1;

    RedBlackTree rbt;

    int num;
    for (int i = 0; i < n; i++){
        cin >> num;
        //Si el numero actual es igual a el anterior, entonces no se agrega al árbol.
        if (num != before){
            rbt.insert(num,i);
        }
        before = num;
    }


    for (int i = 0; i < q; i++){
        cin >> num;
        //Como inicializamos a el nodo con indice -1, entonces si no encuentra a un nodo con el valor, devuelve -1.
        cout << rbt.search(num) -> index << "\n";
    }

    
    return 0;
}
