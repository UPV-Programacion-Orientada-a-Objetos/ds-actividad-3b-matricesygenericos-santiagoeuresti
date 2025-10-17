#include <iostream>
#include "MatrizDinamica.h"

int main()
{
    std::cout << "--- Sistema de Analisis de Transformaciones Lineales ---" << std::endl;

    std::cout << "\n>> Prueba de Matriz ENTERA (Matriz A) <<" << std::endl;
    std::cout << "Creando Matriz A (Tipo INT) de 2x3..." << std::endl;
    MatrizDinamica<int> A(2, 3);
    std::cout << "\nIngresar valores para A (2x3):" << std::endl;
    A.ingresarDatos();
    std::cout << "\nMatriz A (int):" << std::endl;
    A.mostrar();

    std::cout << "\n>> Redimensionando Matriz A <<" << std::endl;
    std::cout << "Redimensionando A a 3x3. Datos conservados:" << std::endl;
    A.redimensionar(3, 3);
    A.mostrar();

    std::cout << "\n>> Prueba de Multiplicacion (Tipo FLOAT) <<" << std::endl;
    std::cout << "Creando Matriz B (Tipo FLOAT) de 3x2..." << std::endl;
    MatrizDinamica<float> B(3, 2);
    std::cout << "\nIngresar valores para B (3x2):" << std::endl;
    B.ingresarDatos();

    MatrizDinamica<float> Afloat(A.getFilas(), A.getColumnas());
    for (int i = 0; i < A.getFilas(); ++i)
    {
        for (int j = 0; j < A.getColumnas(); ++j)
        {
            Afloat(i, j) = static_cast<float>(A(i, j));
        }
    }

    std::cout << "\nMatriz C = A(3x3) x B(3x2) ..." << std::endl;
    MatrizDinamica<float> C = MatrizDinamica<float>::multiplicar(Afloat, B);
    std::cout << "\nMatriz C (Resultado 3x2, Tipo FLOAT):" << std::endl;
    C.mostrar();

    std::cout << "\nLiberando memoria de todas las matrices..." << std::endl;
    return 0;
}
