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

#include "AVL.h"
#include "ABB.h"

void Menu() {
  std::cout << "\n\n    MENÚ:\n"
            << "[0] Salir\n"
            << "[1] Insertar clave\n"
            << "[2] Buscar clave\n"
            << "[3] Mostrar árbol inorden\n\n";

}

int main(int argc, char* argv[]) {




  while (true) {
    Menu();

    std::cout << "Introduzca una opción: ";
    int opcion;
    std::cin >> opcion; 
    std::cout << "\n\n";

    switch (opcion) {
    case 0:
      return 0;
      break;
    case 1:
      
      break;
    case 2:

      break;
    case 3:

      break;
    default:
      std::cerr << "Opción no contemplada.\n";
      break;
    }

  }
  return 0;
}