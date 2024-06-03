//Solución al problema "Matrix Multiplication 2K" de SPOJ, https://www.spoj.com/problems/MATRMUL0/
#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>

using namespace std;

//Función que se encarga de asignarle valores al cuadrante introducido.
void split(vector<vector<uint64_t>> const &A, vector<vector<uint64_t>> &Aii, int row, int col, int n){

    for (int i1 = 0, i2 = row; i1 < n; i1++, i2++){
        for (int j1 = 0, j2 = col; j1 < n; j1++, j2++){
            Aii[i1][j1] = A[i2][j2];
        }
    }
}

//Función que retorna la suma de 2 matrices dadas.
vector<vector<uint64_t>> add(vector<vector<uint64_t>> const &A, vector<vector<uint64_t>> const &B, int n){
    vector<vector<uint64_t>> C(n, vector<uint64_t>(n));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

//Función que retorna la resta de 2 matrices dadas.
vector<vector<uint64_t>> sub(const vector<vector<uint64_t>> &A, const vector<vector<uint64_t>> &B, int n){
    vector<vector<uint64_t>> C(n, vector<uint64_t>(n));

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

//Función para unir los cuadrantes de la matriz a la matriz original.
void join(vector<vector<uint64_t>> &Aii, vector<vector<uint64_t>> &A, int row, int col, int n){

    for(int i1 = 0, i2 = row; i1 < n; i1++, i2++){
            for(int j1 = 0, j2 = col; j1 < n; j1++, j2++){
                A[i2][j2] = Aii[i1][j1];
            }
    }
}

//Función que calcula la potencia de 2 mayor y mas cercana según el "n" dado.
int nextpow2(int n){
    return pow(2, int(ceil(log2(n))));
}

//Multiplicación de matrices iterativa.
void prod(const vector<vector<uint64_t>> &A, const vector<vector<uint64_t>> &B, vector<vector<uint64_t>> &C, int n) {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

vector<vector<uint64_t>> strassen(vector<vector<uint64_t>> const &A, vector<vector<uint64_t>> const &B, uint64_t n){
    int new_dim = n / 2;
    vector<vector<uint64_t>> C(n, vector<uint64_t>(n));

    //Solución iterativa luego de aplicar varias llamadas recursivas.
    if (n <= 128){
        prod(A, B, C, n);
    }
    else{
        
        vector<vector<uint64_t>> A11(new_dim, vector<uint64_t>(new_dim));
        vector<vector<uint64_t>> A12(new_dim, vector<uint64_t>(new_dim));
        vector<vector<uint64_t>> A21(new_dim, vector<uint64_t>(new_dim));
        vector<vector<uint64_t>> A22(new_dim, vector<uint64_t>(new_dim));

        vector<vector<uint64_t>> B11(new_dim, vector<uint64_t>(new_dim));
        vector<vector<uint64_t>> B12(new_dim, vector<uint64_t>(new_dim));
        vector<vector<uint64_t>> B21(new_dim, vector<uint64_t>(new_dim));
        vector<vector<uint64_t>> B22(new_dim, vector<uint64_t>(new_dim));

        //Dividimos la matriz A en cuatro cuadrantes.
        split(A, A11, 0, 0, new_dim);
        split(A, A12, 0, n / 2, new_dim);
        split(A, A21, n / 2, 0, new_dim);
        split(A, A22, n / 2, n / 2, new_dim);

        //Dividimos la matriz B en cuatro cuadrantes.
        split(B, B11, 0, 0, new_dim);
        split(B, B12, 0, n / 2, new_dim);
        split(B, B21, n / 2, 0, new_dim);
        split(B, B22, n / 2, n / 2, new_dim);

        vector<vector<uint64_t>> M1 = strassen(add(A11, A22, new_dim), add(B11, B22, new_dim), new_dim);
        vector<vector<uint64_t>> M2 = strassen(add(A21, A22, new_dim), B11, new_dim);
        vector<vector<uint64_t>> M3 = strassen(A11, sub(B12, B22, new_dim), new_dim);
        vector<vector<uint64_t>> M4 = strassen(A22, sub(B21, B11, new_dim), new_dim);
        vector<vector<uint64_t>> M5 = strassen(add(A11, A12, new_dim), B22, new_dim);
        vector<vector<uint64_t>> M6 = strassen(sub(A21, A11, new_dim), add(B11, B12, new_dim), new_dim);
        vector<vector<uint64_t>> M7 = strassen(sub(A12, A22, new_dim), add(B21, B22, new_dim), new_dim);

        //Calculamos los valores de los cuatro cuadrantes de "C", siendo C = A * B
        vector<vector<uint64_t>> C11 = add(sub(add(M1, M4, new_dim), M5, new_dim), M7, new_dim);
        vector<vector<uint64_t>> C12 = add(M3, M5, new_dim);
        vector<vector<uint64_t>> C21 = add(M2, M4, new_dim);
        vector<vector<uint64_t>> C22 = add(sub(add(M1, M3, new_dim), M2, new_dim), M6, new_dim);

        //Unimos los cuadrantes a C.
        join(C11, C, 0, 0, new_dim);
        join(C12, C, 0, n / 2, new_dim);
        join(C21, C, n / 2, 0, new_dim);
        join(C22, C, n / 2, n / 2, new_dim);
    }
    return C;
}

int main(){
    uint32_t n, i, j, d1, p1, r1, m1, d2, p2, r2, m2;

    cin >> n >> p1 >> d1 >> r1 >> m1 >> p2 >> d2 >> r2 >> m2;

    int new_dim = nextpow2(n);

    vector<vector<uint64_t>> A(new_dim, vector<uint64_t>(new_dim)), B(new_dim, vector<uint64_t>(new_dim)), C(new_dim, vector<uint64_t>(new_dim)); 
    vector<uint64_t> V(n, 0);


    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            d1 = d1 * p1 + r1;
            d2 = d2 * p2 + r2;
            A[i][j] = d1 >> (32 - m1);
            B[i][j] = d2 >> (32 - m2);
        }
    }
    

    C = strassen(A, B, new_dim);

    for (i=0; i<n; ++i) {
        V[i] = 0;
        for (j=0; j<n; ++j){
            V[i] ^= C[i][j];
        }
    }

    for (i = 0; i < n; ++i) {
        cout << V[i] << " ";
    }
    cout << endl;

    return 0;
}