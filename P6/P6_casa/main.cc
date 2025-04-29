// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 6
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 30/04/2025
// Archivo main.cc
// Descripción: contiene la función principal

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "AVL.h"
#include "ABB.h"
#include "nif.h"

void Help() {
  std::cout << "\n\n      Uso del programa:\n\n"
            << "-ab [abb|avl] para definir el tipo de árbol.\n"
            << "-init <i> [s] [f] la i es el tipo de inicialización, la s el tamaño y la f el nombre del fichero.\n"
            << "  i=manual [s]\n"
            << "  i=random [s]\n"
            << "  i=file [s] [t]\n"
            << "-trace [y|n] para mostrar la traza o no.\n\n"
            << "Por defecto se pondrá un árbol abb, inicialización random con size 10 y no se mostrará la traza.\n";
}

void Menu() {
  std::cout << "\n\n      MENÚ:\n"
            << "[0] Salir\n"
            << "[1] Insertar clave\n"
            << "[2] Buscar clave\n"
            << "[3] Mostrar árbol inorden\n\n";
}

int main(int argc, char* argv[]) {

  bool trace = false;
  std::string arbol = "abb";
  std::string inicializacion = "random";
  std::string nombre_fichero;
  size_t size = 10;

  for (int i = 1; i < argc; ++i) {
    if (std::string(argv[i]) == "-ab" && i + 1 < argc) arbol = argv[++i];
    else if (std::string(argv[i]) == "-init") {
      inicializacion = argv[++i];
      if (i + 1 < argc) size = std::stoi(argv[++i]);
      if (inicializacion == "file" && i + 1 < argc) nombre_fichero = argv[++i];
    }
    else if (std::string(argv[i]) == "-trace" && i + 1 < argc) trace = (argv[++i]) ? true : false;
    else {
      Help();
      return 1;
    }
  }

  AB<nif>* tree = nullptr;
  if (arbol == "avl") tree = new AVL<nif>(trace); 
  else tree = new ABB<nif>();
  
  if (inicializacion == "random") {
    srand(time(nullptr));
    for (size_t i = 0; i < size; ++i) {
      nif value = rand() % 100000000;
      tree->insertar(value);
      std::cout << value << " Insertado con exito.\n";
    }
  } else if (inicializacion == "file") {
    std::ifstream file(nombre_fichero);
    if (!file.is_open()) {
      std::cerr << "Error al abrir el fichero.\n";
      return 1;
    }
    long value;
    for (size_t i = 0; i < size; ++i) {
      file >> value;
      tree->insertar(nif(value));
      std::cout << value << " Insertado con exito.\n";
    }
  } else if (inicializacion == "manual") {
    std::cout << "Inicialización manual seleccionada. Árbol vacío.\n"
              << "Ingrese los valores del árbol:\n";
    for (size_t i = 0; i < size; ++i) {
      std::cout << "[" << i + 1 << " / " << size << "]: ";
      long NIF;
      std::cin >> NIF;
      tree->insertar(nif(NIF));
      std::cout << "\n" << NIF << " Insertado con exito.\n";
    }
  }

  while (true) {
    char c;
    std::cout<< "\nIngrese cualquier caracter para continuar: ";
    std::cin>> c;

    system("clear");

    std::cout << "Árbol inicializado:\n" << *tree;

    Menu();
    std::cout << "Introduzca una opción: ";
    int opcion;
    std::cin >> opcion;
    std::cout << "\n\n";

    switch (opcion) {
    case 0:
      delete tree;
      std::cout << "Programa terminado con exito.\n";
      return 0;
    case 1: {
      long clave;
      std::cout << "Introduzca la clave a insertar: ";
      std::cin >> clave;
      if (tree->insertar(nif(clave))) {
        std::cout << "Clave insertada correctamente.\n";
      } else {
        std::cout << "La clave ya existe en el árbol.\n";
      }
      std::cout << *tree;
      break;
    }
    case 2: {
      long clave;
      std::cout << "Introduzca la clave a buscar: ";
      std::cin >> clave;
      if (tree->buscar(nif(clave))) {
        std::cout << "Clave encontrada en el árbol.\n";
      } else {
        std::cout << "Clave no encontrada.\n";
      }
      break;
    }
    case 3:
      tree->inorden();
      break;
    default:
      std::cerr << "Opción no contemplada.\n";
      break;
    }
  }

  return 0;
}