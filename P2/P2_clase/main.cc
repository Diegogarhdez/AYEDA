// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 2
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/02/2025
// Archivo main.cc
// Descripción: contiene la función main del proyecto

#include <iostream>
#include <fstream>

#include "BigRational.h"
#include "BigComplex.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "No se ha aplicado correctamente el formato del ejecutable.\n./BigNumbers <fichero_entrada> <fichero_salida>\n";
  }

  std::ifstream fichero_entrada(argv[1]);
  std::ofstream fichero_salida(argv[2]);

  if (!fichero_entrada.is_open()) {
    std::cerr << "No se ha podido abrir el fichero de entrada.\n";
  } else if (!fichero_salida.is_open()) {
    std::cerr << "No se ha podido abrir el fichero de salida.\n";
  }

  std::string entrada, base;
  std::getline(fichero_entrada, base);
  if (base.ends_with("16")) {
    BigComplex<16> complejo1, complejo2;
    BigInteger<16> real1, real2, imaginario1, imaginario2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real1;
        fichero_entrada >> imaginario1;
        complejo1.SetReal(real1);
        complejo1.SetImaginario(imaginario1);
        break;
      }
    }
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real2;
        fichero_entrada >> imaginario2;
        complejo2.SetReal(real2);
        complejo2.SetImaginario(imaginario2);
        break;
      }
    }
    fichero_salida << base << "\n";
    fichero_salida << "N1= " << complejo1 << "\n";
    fichero_salida << "N2= " << complejo2 << "\n";
    fichero_salida << "N1 + N2= " << complejo1 + complejo2 << "\n";

  } else if (base.ends_with("10")) {
    BigComplex<10> complejo1, complejo2;
    BigInteger<10> real1, real2, imaginario1, imaginario2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real1;
        fichero_entrada >> imaginario1;
        complejo1.SetReal(real1);
        complejo1.SetImaginario(imaginario1);
        break;
      }
    }
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real2;
        fichero_entrada >> imaginario2;
        complejo2.SetReal(real2);
        complejo2.SetImaginario(imaginario2);
        break;
      }
    }

    fichero_salida << base << "\n";
    fichero_salida << "N1= " << complejo1 << "\n";
    fichero_salida << "N2= " << complejo2 << "\n";
    fichero_salida << "N1 + N2= " << complejo1 + complejo2 << "\n";

  } else if (base.ends_with("8")) {
    BigComplex<8> complejo1, complejo2;
    BigInteger<8> real1, real2, imaginario1, imaginario2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real1;
        fichero_entrada >> imaginario1;
        complejo1.SetReal(real1);
        complejo1.SetImaginario(imaginario1);
        break;
      }
    }
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real2;
        fichero_entrada >> imaginario2;
        complejo2.SetReal(real2);
        complejo2.SetImaginario(imaginario2);
        break;
      }
    }

    fichero_salida << base << "\n";
    fichero_salida << "N1= " << complejo1 << "\n";
    fichero_salida << "N2= " << complejo2 << "\n";
    fichero_salida << "N1 + N2= " << complejo1 + complejo2 << "\n";

  } else if (base.ends_with("2")) {
    BigComplex<2> complejo1, complejo2;
    BigInteger<2> real1, real2, imaginario1, imaginario2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real1;
        fichero_entrada >> imaginario1;
        complejo1.SetReal(real1);
        complejo1.SetImaginario(imaginario1);
        break;
      }
    }
    while (fichero_entrada >> entrada) {
      if (entrada == "=") {
        fichero_entrada >> real2;
        fichero_entrada >> imaginario2;
        complejo2.SetReal(real2);
        complejo2.SetImaginario(imaginario2);
        break;
      }
    }

    fichero_salida << base << "\n";
    fichero_salida << "N1= " << complejo1 << "\n";
    fichero_salida << "N2= " << complejo2 << "\n";
    fichero_salida << "N1 + N2= " << complejo1 + complejo2 << "\n";

  }

  fichero_entrada.close();
  fichero_salida.close();
  std::cout << "Programa terminado.\n";
  return 0;
}