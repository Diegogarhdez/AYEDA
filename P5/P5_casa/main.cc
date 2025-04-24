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

#include "nif.h"
#include "secuence.h"
#include "sort_methods.h"

void Menu() {
  std::cout << "\n\nEste programa tiene como objetivo mostrar diferentes formas de ordenación.\n\n"
            << "Las opciones del programa son las siguientes:\n"
            << "  -size <s> para definir el tamaño de la secuencia a ordenar\n"
            << "  -ord <m> para definir el método de ordenación\n"
            << "    insertion\n    shaker\n    quicksort\n    heapsort\n    shellsort\n"
            << "  -init <i> indica la forma para introducir los datos\n"
            << "    manual\n    random\n    file <fichero_entrada>\n"
            << "  -trace <y|n>\n\n";
}

int main(int argc, char* argv[]) {
  Menu();
  unsigned size = 10;
  std::string method = "insertion";
  std::string initMode = "random";
  std::string fileName = "";
  bool trace = false;
  double shellSortAlpha = 0.5;

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "-size") == 0 && i + 1 < argc) {
      try {
        size = std::stoi(argv[++i]);
      } catch (const std::invalid_argument& ia) {
        std::cerr << "Error: Invalid number provided for -size.\n";
        return 1;
      } catch (const std::out_of_range& oor) {
        std::cerr << "Error: Number provided for -size is out of range.\n";
        return 1;
      }
    } else if (strcmp(argv[i], "-ord") == 0 && i + 1 < argc) {
      method = argv[++i];
    } else if (strcmp(argv[i], "-init") == 0 && i + 1 < argc) {
      initMode = argv[++i];
      if (initMode == "file" && i + 1 < argc) {
        fileName = argv[++i];
      } else if (initMode != "random" && initMode != "manual") {
        std::cerr << "Error: Invalid mode for -init. Use 'random', 'manual', "
                     "or 'file <filename>'.\n";
        return 1;
      }
    } else if (strcmp(argv[i], "-trace") == 0 && i + 1 < argc) {
      trace = (strcmp(argv[++i], "y") == 0);
    } else {
      std::cerr << "Warning: Unrecognized or incomplete argument '" << argv[i]
                << "'.\n";
    }
  }

  if (size == 0) {
    std::cerr << "Error: La secuencia tiene que tener elementos.\n";
    return 1;
  }

  staticSequence<nif> sequence(size);
  unsigned current_size = 0;

  try {
    if (initMode == "random") {
      srand(time(NULL));
      std::cout << "Ingresando " << size << " random NIFs...\n";
      for (unsigned i = 0; i < size; ++i) {
        sequence[i] = nif(10000000 + rand() % 90000000);
      }
      current_size = size;
    } else if (initMode == "manual") {
      std::cout << "Ingrese " << size << " NIFs (Sin letra):\n";
      for (unsigned i = 0; i < size; ++i) {
        int value;
        std::cout << "[" << i + 1 << "/" << size << "]: ";
        while (!(std::cin >> value)) {
          std::cerr << "Invalid input. Ingrese un entero: ";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        sequence[i] = nif(value);
      }
      current_size = size;
    } else if (initMode == "file") {
      if (fileName.empty()) {
        std::cerr << "Error: No se ha especificado ningún archivo: -init <file>.\n";
        return 1;
      }
      std::ifstream file(fileName);
      if (file.is_open()) {
        std::cout << "Leyendo los NIFs del archivo: " << fileName << "\n";
        unsigned i = 0;
        while (i < size && file >> sequence[i]) {
          ++i;
        }
        current_size = i;
        if (i < size && !file.eof()) {
          std::cerr << "Warning: Error leyendo el archivo con "
                    << i << " NIFs.\n";
        } else if (i == 0) {
          std::cerr << "Warning: El archivo está vacío o no contiene NIFs.\n";
        }
        file.close();
      } else {
        std::cerr << "Error: No se puede abrir el archivo '" << fileName << "'.\n";
        return 1;
      }
    }
    sequence.updateSize(current_size);

    if (sequence.getSize() == 0) {
      std::cerr << "Error: Secuencia vacía. Nada que ordenar.\n";
      return 1;
    }

    std::cout << "Secuencia inicializada con " << sequence.getSize()
              << " elementos.\n";
    if (trace) {
      std::cout << "sequencia inicial: ";
      for (unsigned i = 0; i < sequence.getSize(); ++i) {
        std::cout << sequence[i] << " ";
      }
      std::cout << "\n";
    }

    SortMethod<nif>* sorter = nullptr;
    if (method == "insertion") {
      sorter = new InsertionSort<nif>();
    } else if (method == "shaker") {
      sorter = new ShakerSort<nif>();
    } else if (method == "quicksort") {
      sorter = new QuickSort<nif>();
    } else if (method == "heapsort") {
      sorter = new HeapSort<nif>();
    } else if (method == "shellsort") {
      std::cout << "Ingrese alfa para ShellSort: ";
      std::cin >> shellSortAlpha;
      std::cout << "\n"; 
      sorter = new ShellSort<nif>(shellSortAlpha);
    } else {
      std::cerr << "Error: Algoritmo de ordenación: '" << method << "' no encontrado.\n";
      std::cerr << "Métodos posibles: insertion, shaker, quicksort, heapsort, "
                   "shellsort\n";
      return 1;
    }

    std::cout << "Ordenando usando " << method << "...\n";
    sorter->Sort(sequence, trace);
    delete sorter;

    std::cout << "Secuencia Final ordenada:\n";
    for (unsigned i = 0; i < sequence.getSize(); ++i) {
      std::cout << sequence[i] << " ";
    }
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
