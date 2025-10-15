#include <iostream>
#include "MatrizDinamica.h"

int main() {
    std::cout << "Sistema Generico de Analisis de Transformaciones Lineales" << std::endl;

    MatrizDinamica<int> A(2, 3);
    A.inicializar(0);
    A(0,0) = 1; A(0,1) = 2; A(0,2) = 3;
    A(1,0) = 4; A(1,1) = 5; A(1,2) = 6;

    std::cout << "\nMatriz A (int):" << std::endl;
    A.mostrar();

    std::cout << "\nRedimensionando A a 3x3..." << std::endl;
    A.redimensionar(3,3);
    std::cout << "Matriz A redimensionada (3x3):" << std::endl;
    A.mostrar();

    MatrizDinamica<float> B(3, 2);
    B.inicializar(0.0f);
    B(0,0) = 1.5f; B(0,1) = 0.5f;
    B(1,0) = 2.0f; B(1,1) = 1.0f;
    B(2,0) = 1.0f; B(2,1) = 2.5f;

    std::cout << "\nMatriz B (float):" << std::endl;
    B.mostrar();

    std::cout << "Acceso A(0,1) = " << A(0,1) << std::endl;
    A(1,2) = 99;
    std::cout << "Modificado A(1,2) = 99" << std::endl;
    A.mostrar();

    return 0;
}
