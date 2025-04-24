// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 5
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 10/04/2025
// Archivo main.cc
// Descripción: contiene la función principal

/**
 * -size <s>, s es el tamaño de la secuencia.
 * -ord <m>, m es el código que identifica un método de ordenación.
 * -init <i> [f], indica la forma de introducir los datos de la secuencia
 *  i=manual
 *  i=random
 *  i=file f=nombre del fichero de entrada
 * -trace <y|n>, indica si se muestra o no la traza durante la ejecución
*/


#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

#include "nif.h"
#include "secuence.h"
#include "sort_methods.h"


int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Uso del programa: ./Sort <size>";
    return 1;
  }
    unsigned size = std::stoi(argv[1]);
  bool trace = false;
  double shellSortAlpha = 0.5;

  staticSequence<nif> sequence(size);

  try {
    srand(time(NULL));
    std::cout << "Ingresando " << size << " random NIFs...\n\n";
    for (unsigned i = 0; i < size; ++i) {
      sequence[i] = nif(10000000 + rand() % 90000000);
    }

    SortMethod<nif>* sorter = nullptr;
    sorter = new InsertionSort<nif>();
    std::cout << "Ordenando usando InsertionSort...\n";
    std::cout << "Iniciando temporizador\n";
    auto inicio = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence, trace);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;
    std::cout << "Tiempo de InsertionSort: " << duracion.count() << ".\n";

    sorter = new ShakerSort<nif>();
    std::cout << "Ordenando usando ShakerSort...\n";
    std::cout << "Iniciando temporizador\n";
    inicio = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence, trace);
    fin = std::chrono::high_resolution_clock::now();
    duracion = fin - inicio;
    
    std::cout << "Tiempo de ShakeSort: " << duracion.count() << ".\n";
    
    sorter = new QuickSort<nif>();
    std::cout << "Ordenando usando QuickSort...\n";
    std::cout << "Iniciando temporizador\n";
    inicio = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence, trace);
    fin = std::chrono::high_resolution_clock::now();
    duracion = fin - inicio;
    
    std::cout << "Tiempo de QuickSort: " << duracion.count() << ".\n";
    
    
    sorter = new HeapSort<nif>();
    std::cout << "Ordenando usando HeapSort...\n";
    std::cout << "Iniciando temporizador\n";
    inicio = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence, trace);
    fin = std::chrono::high_resolution_clock::now();
    duracion = fin - inicio;
    
    std::cout << "Tiempo de HeapSort: " << duracion.count() << ".\n";
    
    
    sorter = new ShellSort<nif>(shellSortAlpha);
    std::cout << "Ordenando usando ShellSort...\n";
    std::cout << "Iniciando temporizador\n";
    inicio = std::chrono::high_resolution_clock::now();
    sorter->Sort(sequence, trace);
    fin = std::chrono::high_resolution_clock::now();
    duracion = fin - inicio;
    
    std::cout << "Tiempo de ShellSort: " << duracion.count() << ".\n";

    delete sorter;

    std::cout << "\n";

  } catch (const std::out_of_range& oor) {
    std::cerr << "Error: Fuera de rango. Detalles: "
              << oor.what() << "\n";
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "An unexpected error occurred: " << e.what() << "\n";
    return 1;
  } catch (...) {
    std::cerr << "An unknown error occurred.\n";
    return 1;
  }

  return 0;
}
