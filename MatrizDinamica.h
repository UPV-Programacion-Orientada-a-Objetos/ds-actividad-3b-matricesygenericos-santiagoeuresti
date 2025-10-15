#pragma once
#include <iostream>
#include <iomanip>

template <typename T>
class MatrizDinamica {
private:
    T **datos;
    int filas;
    int columnas;

public:
    MatrizDinamica(int f, int c);
    ~MatrizDinamica();
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;
    void ingresarDatos();
    void mostrar() const;
    void inicializar(const T& valor);
    void redimensionar(int nuevaF, int nuevaC);
};

template <typename T>
MatrizDinamica<T>::MatrizDinamica(int f, int c) : filas(f), columnas(c) {
    if (f <= 0 || c <= 0) {
        std::cout << "Error: Las dimensiones deben ser positivas" << std::endl;
        filas = columnas = 0;
        datos = nullptr;
        return;
    }

    std::cout << "Asignando memoria para matriz " << f << "x" << c << "..." << std::endl;

    datos = new T*[filas];

    for (int i = 0; i < filas; i++) {
        datos[i] = new T[columnas];
    }

    inicializar(T(0));
}

template <typename T>
MatrizDinamica<T>::~MatrizDinamica() {
    if (datos != nullptr) {
        std::cout << "Liberando memoria de matriz " << filas << "x" << columnas << "..." << std::endl;

        for (int i = 0; i < filas; i++) {
            delete[] datos[i];
        }

        delete[] datos;
        datos = nullptr;
    }
}

template <typename T>
T& MatrizDinamica<T>::operator()(int i, int j) {
    if (i < 0 || i >= filas || j < 0 || j >= columnas) {
        std::cout << "Error: Indices fuera de rango (" << i << "," << j << ")" << std::endl;
        static T dummy = T(0);
        return dummy;
    }
    return datos[i][j];
}

template <typename T>
const T& MatrizDinamica<T>::operator()(int i, int j) const {
    if (i < 0 || i >= filas || j < 0 || j >= columnas) {
        std::cout << "Error: Indices fuera de rango (" << i << "," << j << ")" << std::endl;
        static T dummy = T(0);
        return dummy;
    }
    return datos[i][j];
}

template <typename T>
void MatrizDinamica<T>::inicializar(const T& valor) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            datos[i][j] = valor;
        }
    }
}

template <typename T>
void MatrizDinamica<T>::redimensionar(int nuevaF, int nuevaC) {
    if (nuevaF <= 0 || nuevaC <= 0) {
        std::cout << "Error: dimensiones nuevas deben ser positivas" << std::endl;
        return;
    }

    T **nuevo = new T*[nuevaF];
    for (int i = 0; i < nuevaF; ++i) {
        nuevo[i] = new T[nuevaC];
    }

    // Inicializar a cero
    for (int i = 0; i < nuevaF; ++i) {
        for (int j = 0; j < nuevaC; ++j) {
            nuevo[i][j] = T(0);
        }
    }

    // Copiar datos existentes
    int minF = (filas < nuevaF) ? filas : nuevaF;
    int minC = (columnas < nuevaC) ? columnas : nuevaC;
    if (datos != nullptr) {
        for (int i = 0; i < minF; ++i) {
            for (int j = 0; j < minC; ++j) {
                nuevo[i][j] = datos[i][j];
            }
        }
    }

    // Liberar memoria antigua
    if (datos != nullptr) {
        for (int i = 0; i < filas; ++i) {
            delete[] datos[i];
        }
        delete[] datos;
    }

    // Asignar nueva matriz
    datos = nuevo;
    filas = nuevaF;
    columnas = nuevaC;
}

template <typename T>
void MatrizDinamica<T>::ingresarDatos() {
    std::cout << "\nIngresando valores para matriz " << filas << "x" << columnas << ":" << std::endl;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            std::cout << "Elemento [" << i << "," << j << "]: ";
            std::cin >> datos[i][j];
        }
    }
}

template <typename T>
void MatrizDinamica<T>::mostrar() const {
    std::cout << "\nMatriz " << filas << "x" << columnas << ":" << std::endl;

    for (int i = 0; i < filas; i++) {
        std::cout << "| ";
        for (int j = 0; j < columnas; j++) {
            std::cout << std::setw(6) << std::setprecision(2) << std::fixed << datos[i][j];
            if (j < columnas - 1) std::cout << " | ";
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
}
