#pragma once
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>

template <typename T>
class MatrizDinamica
{
private:
    T **datos;
    int filas;
    int columnas;

public:
    MatrizDinamica(int f, int c);
    MatrizDinamica(const MatrizDinamica &o);
    MatrizDinamica(MatrizDinamica &&o) noexcept;
    ~MatrizDinamica();
    MatrizDinamica &operator=(const MatrizDinamica &o);
    MatrizDinamica &operator=(MatrizDinamica &&o) noexcept;
    int getFilas() const { return filas; }
    int getColumnas() const { return columnas; }
    T &operator()(int i, int j);
    const T &operator()(int i, int j) const;
    void ingresarDatos();
    void mostrar() const;
    void inicializar(const T &valor);
    void redimensionar(int nuevaF, int nuevaC);
    static MatrizDinamica multiplicar(const MatrizDinamica &A, const MatrizDinamica &B);
};

template <typename T>
MatrizDinamica<T>::MatrizDinamica(int f, int c) : filas(f), columnas(c)
{
    if (f <= 0 || c <= 0)
    {
        std::cout << "Error: Las dimensiones deben ser positivas" << std::endl;
        filas = columnas = 0;
        datos = nullptr;
        return;
    }

    datos = new T *[filas];

    for (int i = 0; i < filas; i++)
    {
        datos[i] = new T[columnas];
    }

    inicializar(T(0));
}

template <typename T>
MatrizDinamica<T>::MatrizDinamica(const MatrizDinamica &o) : datos(nullptr), filas(o.filas), columnas(o.columnas)
{
    if (filas <= 0 || columnas <= 0)
    {
        datos = nullptr;
        filas = columnas = 0;
        return;
    }
    datos = new T *[filas];
    for (int i = 0; i < filas; ++i)
    {
        datos[i] = new T[columnas];
    }
    for (int i = 0; i < filas; ++i)
    {
        for (int j = 0; j < columnas; ++j)
        {
            datos[i][j] = o(i, j);
        }
    }
}

template <typename T>
MatrizDinamica<T>::MatrizDinamica(MatrizDinamica &&o) noexcept : datos(o.datos), filas(o.filas), columnas(o.columnas)
{
    o.datos = nullptr;
    o.filas = 0;
    o.columnas = 0;
}

template <typename T>
MatrizDinamica<T>::~MatrizDinamica()
{
    if (datos != nullptr)
    {
        for (int i = 0; i < filas; i++)
        {
            delete[] datos[i];
        }

        delete[] datos;
        datos = nullptr;
    }
}

template <typename T>
MatrizDinamica<T> &MatrizDinamica<T>::operator=(const MatrizDinamica &o)
{
    if (this == &o)
    {
        return *this;
    }
    MatrizDinamica temp(o);
    std::swap(datos, temp.datos);
    std::swap(filas, temp.filas);
    std::swap(columnas, temp.columnas);
    return *this;
}

template <typename T>
MatrizDinamica<T> &MatrizDinamica<T>::operator=(MatrizDinamica &&o) noexcept
{
    if (this == &o)
    {
        return *this;
    }
    if (datos != nullptr)
    {
        for (int i = 0; i < filas; ++i)
        {
            delete[] datos[i];
        }
        delete[] datos;
    }
    datos = o.datos;
    filas = o.filas;
    columnas = o.columnas;
    o.datos = nullptr;
    o.filas = 0;
    o.columnas = 0;
    return *this;
}

template <typename T>
T &MatrizDinamica<T>::operator()(int i, int j)
{
    if (i < 0 || i >= filas || j < 0 || j >= columnas)
    {
        std::cout << "Error: Indices fuera de rango (" << i << "," << j << ")" << std::endl;
        static T dummy = T(0);
        return dummy;
    }
    return datos[i][j];
}

template <typename T>
const T &MatrizDinamica<T>::operator()(int i, int j) const
{
    if (i < 0 || i >= filas || j < 0 || j >= columnas)
    {
        std::cout << "Error: Indices fuera de rango (" << i << "," << j << ")" << std::endl;
        static T dummy = T(0);
        return dummy;
    }
    return datos[i][j];
}

template <typename T>
void MatrizDinamica<T>::inicializar(const T &valor)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            datos[i][j] = valor;
        }
    }
}

template <typename T>
void MatrizDinamica<T>::redimensionar(int nuevaF, int nuevaC)
{
    if (nuevaF <= 0 || nuevaC <= 0)
    {
        std::cout << "Error: dimensiones nuevas deben ser positivas" << std::endl;
        return;
    }

    T **nuevo = new T *[nuevaF];
    for (int i = 0; i < nuevaF; ++i)
    {
        nuevo[i] = new T[nuevaC];
    }

    // Inicializar a cero
    for (int i = 0; i < nuevaF; ++i)
    {
        for (int j = 0; j < nuevaC; ++j)
        {
            nuevo[i][j] = T(0);
        }
    }

    // Copiar datos existentes
    int minF = (filas < nuevaF) ? filas : nuevaF;
    int minC = (columnas < nuevaC) ? columnas : nuevaC;
    if (datos != nullptr)
    {
        for (int i = 0; i < minF; ++i)
        {
            for (int j = 0; j < minC; ++j)
            {
                nuevo[i][j] = datos[i][j];
            }
        }
    }

    // Liberar memoria antigua
    if (datos != nullptr)
    {
        for (int i = 0; i < filas; ++i)
        {
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
void MatrizDinamica<T>::ingresarDatos()
{
    std::cout << "\nIngresando valores para matriz " << filas << "x" << columnas << ":" << std::endl;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            std::cout << "Elemento [" << i << "," << j << "]: ";
            std::cin >> datos[i][j];
        }
    }
}

template <typename T>
void MatrizDinamica<T>::mostrar() const
{
    std::cout << "\nMatriz " << filas << "x" << columnas << ":" << std::endl;

    for (int i = 0; i < filas; i++)
    {
        std::cout << "| ";
        for (int j = 0; j < columnas; j++)
        {
            std::cout << std::setw(6) << std::setprecision(2) << std::fixed << datos[i][j];
            if (j < columnas - 1)
                std::cout << " | ";
        }
        std::cout << " |" << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
MatrizDinamica<T> MatrizDinamica<T>::multiplicar(const MatrizDinamica &A, const MatrizDinamica &B)
{
    if (A.getColumnas() != B.getFilas())
    {
        throw std::invalid_argument("dimensiones incompatibles para multiplicacion");
    }
    MatrizDinamica<T> C(A.getFilas(), B.getColumnas());
    C.inicializar(T(0));
    for (int i = 0; i < A.getFilas(); ++i)
    {
        for (int j = 0; j < B.getColumnas(); ++j)
        {
            T suma = T(0);
            for (int k = 0; k < A.getColumnas(); ++k)
            {
                suma = suma + A(i, k) * B(k, j);
            }
            C(i, j) = suma;
        }
    }
    return C;
}
