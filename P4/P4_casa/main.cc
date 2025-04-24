// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 4
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/03/2025
// Archivo main.cc
// Descripción: contiene la funcion principal del proyecto

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <list>
#include <vector>

#include "hash.h"
#include "nif.h"

/**
 * @brief Esta función muestra un menú de ayuda al empezar el programa
 */
void MostrarMenu() {
  std::cout
      << "Este programa se centra en la implementación de las tablas hash.\n";
  std::cout << "Opciones:";
  std::cout << "-ts <s> tamaño de la tabla\n";
  std::cout << "-fd <f> funcion de dispersion\n";
  std::cout << "-hash <open/close> indica la tecnica a usar\n";
  std::cout << "-bs <s> tamaño del bloque\n";
  std::cout << "-fe <f> codigo de la función de exploración\n\n";
}

// Función principal
int main(int argc, char* argv[]) {
  void MostrarMenu();
  unsigned tableSize = 10;
  unsigned blockSize = 5;
  std::string hashType = "open";
  std::string dispersionFunc = "modulo";
  std::string explorationFunc = "linear";

  // Procesar los argumentos de línea de comandos
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-ts") == 0 && i + 1 < argc)
      tableSize = std::stoi(argv[++i]);
    else if (strcmp(argv[i], "-fd") == 0 && i + 1 < argc)
      dispersionFunc = argv[++i];
    else if (strcmp(argv[i], "-hash") == 0 && i + 1 < argc)
      hashType = argv[++i];
    else if (strcmp(argv[i], "-bs") == 0 && i + 1 < argc)
      blockSize = std::stoi(argv[++i]);
    else if (strcmp(argv[i], "-fe") == 0 && i + 1 < argc)
      explorationFunc = argv[++i];
  }

  // poner una "semilla"
  srand(time(nullptr));

  // Crear la función de dispersión
  ModuloFunction<nif> dispersion(tableSize);

  // Crear la función de exploración
  LinearExploration<nif> exploration;

  // Crear la tabla hash según el tipo de dispersión seleccionado
  if (hashType == "open") {
    HashTable<nif, dynamicSequence<nif>> hashTable(tableSize, dispersion,
                                                   exploration);
    std::cout << "Tabla hash configurada con dispersión abierta.\n";

    // Crear múltiples NIFs e insertarlos
    std::vector<nif> nifVector;
    nifVector.push_back(11111111);
    nifVector.push_back(22222221);
    nifVector.push_back(33333331);
    nifVector.push_back(44444441);
    nifVector.push_back(55555551);
    for (size_t i = 0; i < nifVector.size(); ++i) {
      hashTable.insert(nifVector[i]);
    }
    // for (size_t i = 0; i < (tableSize * blockSize) * 2; ++i) {
    //   nif newNif(10000000 + rand() % 90000000);  // NIF aleatorio de 8
    //   dígitos nifVector.push_back(newNif); hashTable.insert(newNif);
    // }

    // comprobar que se ha hecho correctamente
    std::cout << "Se han insertado " << nifVector.size()
              << " NIFs en la tabla.\n";

    // Buscar el 55555551 en la tabla
    std::cout << "NIF: 55555551 "
              << (hashTable.search(55555551) ? "encontrado" : "no encontrado")
              << "\n";

    // Buscar aleatoriamente elementos del vector
    std::cout << "Buscando NIFs aleatorios:\n";
    for (size_t i = 0; i < nifVector.size() / 2; ++i) {
      nif randomNif = nifVector[rand() % nifVector.size()];
      std::cout << "NIF: " << randomNif << " "
                << (hashTable.search(randomNif) ? "encontrado"
                                                : "no encontrado")
                << "\n";
    }

  } else {
    HashTable<nif, staticSequence<nif, 5>> hashTable(tableSize, dispersion,
                                                     exploration);
    std::cout << "Tabla hash configurada con dispersión cerrada.\n";

    // Crear múltiples NIFs e insertarlos
    std::vector<nif> nifVector;
    nifVector.push_back(11111111);
    nifVector.push_back(22222221);
    nifVector.push_back(33333331);
    nifVector.push_back(44444441);
    nifVector.push_back(55555551);
    for (size_t i = 0; i < nifVector.size(); ++i) {
      hashTable.insert(nifVector[i]);
    }
    // for (size_t i = 0; i < (tableSize * blockSize) * 2; ++i) {
    //   nif newNif(10000000 + rand() % 90000000);  
    // // NIF aleatorio de 8 dígitos 
    // nifVector.push_back(newNif); hashTable.insert(newNif);
    // }

    // comprobar que se ha hecho correctamente
    std::cout << "Se han insertado " << nifVector.size()
              << " NIFs en la tabla.\n";

    // Buscar el 55555551 en la tabla
    std::cout << "NIF: 55555551 "
              << (hashTable.search(55555551) ? "encontrado" : "no encontrado")
              << "\n";

    // Buscar aleatoriamente elementos del vector
    std::cout << "Buscando NIFs aleatorios:\n";
    for (size_t i = 0; i < nifVector.size() / 2; ++i) {
      nif randomNif = nifVector[rand() % nifVector.size()];
      std::cout << "NIF: " << randomNif << " "
                << (hashTable.search(randomNif) ? "encontrado"
                                                : "no encontrado")
                << "\n";
    }
  }

  return 0;
}
