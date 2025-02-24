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
    BigInteger<16> Num1, Num2;
    BigUnsigned<16> Den1, Den2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num1;
    fichero_entrada >> entrada;
    fichero_entrada >> Den1;
    BigRational<16> rational1(Num1, Den1);
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num2;
    fichero_entrada >> entrada;
    fichero_entrada >> Den2;
    BigRational<16> rational2(Num2, Den2);
    fichero_salida << base << "\n";
    fichero_salida << "N1= " << rational1 << "\n";
    fichero_salida << "N2= " << rational2 << "\n";
    fichero_salida << "N1==N2: " << ((rational1 == rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1<N2:  " << ((rational1 < rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1+N2:  " << rational1 + rational2 << "\n";
    fichero_salida << "N1-N2:  " << rational1 - rational2 << "\n";
    fichero_salida << "N1*N2:  " << rational1 * rational2 << "\n";
    fichero_salida << "N1/N2:  " << rational1 / rational2 << "\n";
  } else if (base.ends_with("10")) {
    BigInteger<10> Num1, Num2;
    BigUnsigned<10> Den1, Den2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num1;
    fichero_entrada >> entrada;
    fichero_entrada >> Den1;
    BigRational<10> rational1(Num1, Den1);
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num2;
    fichero_entrada >> entrada;
    fichero_entrada >> Den2;
    BigRational<10> rational2(Num2, Den2);
    fichero_salida << base << "\n";
    fichero_salida << "N1= " << rational1 << "\n";
    fichero_salida << "N2= " << rational2 << "\n";
    fichero_salida << "N1==N2: " << ((rational1 == rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1<N2:  " << ((rational1 < rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1+N2:  " << rational1 + rational2 << "\n";
    fichero_salida << "N1-N2:  " << rational1 - rational2 << "\n";
    fichero_salida << "N1*N2:  " << rational1 * rational2 << "\n";
    fichero_salida << "N1/N2:  " << rational1 / rational2 << "\n";
  } else if (base.ends_with("8")) {
    BigInteger<8> Num1, Num2;
    BigUnsigned<8> Den1, Den2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num1;
    fichero_entrada >> entrada;
    fichero_entrada >> Den1;
    BigRational<8> rational1(Num1, Den1);
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num2;
    fichero_entrada >> entrada;
    fichero_entrada >> Den2;
    BigRational<8> rational2(Num2, Den2);
    fichero_salida << base << "\n";
    fichero_salida << "N1= " << rational1 << "\n";
    fichero_salida << "N2= " << rational2 << "\n";
    fichero_salida << "N1==N2: " << ((rational1 == rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1<N2:  " << ((rational1 < rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1+N2:  " << rational1 + rational2 << "\n";
    fichero_salida << "N1-N2:  " << rational1 - rational2 << "\n";
    fichero_salida << "N1*N2:  " << rational1 * rational2 << "\n";
    fichero_salida << "N1/N2:  " << rational1 / rational2 << "\n";
  } else if (base.ends_with("2")) {
    BigInteger<2> Num1, Num2;
    BigUnsigned<2> Den1, Den2;
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num1;
    fichero_entrada >> entrada;
    fichero_entrada >> Den1;
    BigRational<2> rational1(Num1, Den1);
    while (fichero_entrada >> entrada) {
      if (entrada == "=") break;
    }
    fichero_entrada >> Num2;
    fichero_entrada >> entrada;
    fichero_entrada >> Den2;
    BigRational<2> rational2(Num2, Den2);
    fichero_salida << base << "\n";
    fichero_salida << "N1= " << rational1 << "\n";
    fichero_salida << "N2= " << rational2 << "\n";
    fichero_salida << "N1==N2: " << ((rational1 == rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1<N2:  " << ((rational1 < rational2) ? "true" : "false") << "\n";
    fichero_salida << "N1+N2:  " << rational1 + rational2 << "\n";
    fichero_salida << "N1-N2:  " << rational1 - rational2 << "\n";
    fichero_salida << "N1*N2:  " << rational1 * rational2 << "\n";
    fichero_salida << "N1/N2:  " << rational1 / rational2 << "\n";
  }

  fichero_entrada.close();
  fichero_salida.close();
  std::cout << "Programa terminado.\n";
  return 0;
}