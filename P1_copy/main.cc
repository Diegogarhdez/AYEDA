// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo main.cc
// Descripción: contiene la función main del proyecto

#include <iostream>
#include <fstream>
#include <vector>
#include "BigInteger.h"
#include "BigComplex.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "No se ha solicitado un archivo del que obtener los numeros\n";
    return 1;
  }

  std::ifstream fichero_entrada(argv[1]);
  if (!fichero_entrada.is_open()) {
    std::cerr << "No se ha podido abrir el archivo\n";
  }

/**
  BigUnsigned num1{100},num2{33};
  std::cout << num1 % num2 << "\n";
 */

  BigInteger entero1, entero2, entero3, entero4;
  fichero_entrada >> entero1 >> entero2 >> entero3 >> entero4;
  BigComplex complejo1(entero1, entero2), complejo2(entero3, entero4);
  std::cout << "Suma de dos complejos: " << complejo1 + complejo2 << "\n";
/*   std::cout << entero1 % entero2 << "\n";
  BigInteger entero3 = mcd(entero1, entero2);
  std::cout << "MCD de los dos enteros anteriores: " << entero3 << "\n"; */

/**  std::cout << "Se procede a operar con los BigUnisgned\n";
  BigUnsigned numerin4 = numerin1 + numerin2;
  std::cout << "Suma de numero1 y numero2: " << numerin4 << "\n";
  numerin4 = numerin1 - numerin2;
  std::cout << "Resta de numero1 y numero2: " << numerin4 << "\n";
  numerin4 = numerin1 * numerin2;
  std::cout << "multiplicación de numero1 y numero2: " << numerin4 << "\n";
  numerin4 = numerin1 / numerin2;
  std::cout << "División de numero1 y numero2: " << numerin4 << "\n";
  numerin4 = numerin1 % numerin2;
  std::cout << "Módulo de numero1 y numero2: " << numerin4 << "\n";
  
  std::cout << "Comparación de los números 1 y 2\n";
  if (numerin1 == numerin2) {
    std::cout << "El numero1 es igual al numero2\n";
  } else if (numerin1 < numerin2) {
    std::cout << "El numero2 es mayor que el uno\n";
  } else {
    std::cout << "El numero1 es mayor que el dos\n";
  }

  std::cout << "Comprobación de incrementos:\n";
  std::cout << "numero3:" << numerin3 << "\n";
  numerin3++;
  std::cout << "numero3 incrementado de ambas formas:\n" << numerin3 << "\n" << ++numerin3 << "\n";
  numerin3--;
  std::cout << "numero3 decrementado de ambas formas:\n" << numerin3 << "\n" << --numerin3 << "\n";
*/
  return 0;
}