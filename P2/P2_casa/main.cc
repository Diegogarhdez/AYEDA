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

#include "BigInteger.h"
#include "BigUnsigned.h"

int main() {

  BigInteger<2> Binario(-100);
  BigInteger<2> Binario2(10);
  BigInteger<8> Octal(-100);
  BigInteger<10> Decimal(-100);
  BigInteger<16> Hexadecimal(-100);
  BigInteger<16> Hexadecimal2(88);

  Binario = Binario + Binario2;
  Octal++;
  Decimal--;
  Hexadecimal = Hexadecimal - Hexadecimal2;

  std::cout << Binario << "\n" << Octal << "\n" << Decimal << "\n" << Hexadecimal << "\n";

  if (Binario == Binario2) std::cout << "Los numeros binarios son iguales\n";
  else std::cout << "No son iguales los números en binario\n";

  if (Hexadecimal < Hexadecimal2) std::cout << "El primer Hexadecimal es menor que el segundo\n";
  else std::cout<< "El segundo Hexadecimal es menor que el primero\n";

  BigInteger<2> Binario3(64);
  BigInteger<2> Binario4(32);
  std::cout << Binario3 / Binario4 << "\n" << Binario3 % Binario4 << "\n";

  return 0;
}