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

int main() {
    std::cout << "=== Sistema de Analisis de Transformaciones Lineales ===" << std::endl;
    std::cout << "=================================================================" << std::endl;
    
    std::cout << "\n>> PRUEBA: Matriz de ENTEROS <<" << std::endl;
    {
        MatrizDinamica<int> matrizA(2, 3);
        
        std::cout << "\nMatriz A inicializada (valores por defecto):" << std::endl;
        matrizA.mostrar();
        
        std::cout << "\nIngresando datos para la Matriz A:" << std::endl;
        matrizA.ingresarDatos();
        
        std::cout << "\nMatriz A con datos ingresados:" << std::endl;
        matrizA.mostrar();
        
        std::cout << "Acceso directo: A(0,1) = " << matrizA(0,1) << std::endl;
        matrizA(1,2) = 99;
        std::cout << "Modificando A(1,2) = 99" << std::endl;
        matrizA.mostrar();
        
    }
    
    std::cout << "\n" << std::string(50, '-') << std::endl;
    
    std::cout << "\n>> PRUEBA: Matriz de FLOTANTES <<" << std::endl;
    {
        MatrizDinamica<float> matrizB(3, 2);
        
        std::cout << "\nMatriz B inicializada (valores por defecto):" << std::endl;
        matrizB.mostrar();
        
        std::cout << "\nIngresando datos para la Matriz B:" << std::endl;
        matrizB.ingresarDatos();
        
        std::cout << "\nMatriz B con datos ingresados:" << std::endl;
        matrizB.mostrar();
        
        std::cout << "Inicializando matriz B con valor 2.5:" << std::endl;
        matrizB.inicializar(2.5f);
        matrizB.mostrar();
        
    }
    
    return 0;
}
