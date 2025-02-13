// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigInteger.cc
// Descripción: contiene la implementación de la clase BigInteger

#include <string>
#include <cstring>

#include "BigInteger.h"

//constructores
BigInteger::BigInteger(int n) : numero_(std::abs(n)), signo_(n < 0) { }

BigInteger::BigInteger(const BigUnsigned& numeron) : numero_(numeron), signo_(false) { }

BigInteger::BigInteger(const BigInteger& otro) : numero_(otro.numero_), signo_(otro.signo_) { }   

/**
 * @brief Operador de salida
 * @param os 
 * @param entero 
 * @return Salida por pantalla de un BigInteger
 */
std::ostream& operator<<(std::ostream& os, const BigInteger& entero) {
  if (entero.GetSigno()) os << "-";
  os << entero.GetNumero();
  return os;
}

/**
 * @brief Operador de entrada
 * @param is 
 * @param entero 
 * @return valor de is
 */
std::istream& operator>>(std::istream& is, BigInteger& entero) {
  char signo;
  is >> signo; 
  bool es_negativo = false;
  if (signo == '-') {
    es_negativo = true; 
  } else if (isdigit(signo)) {
    is.putback(signo);  
  } else {
    throw std::invalid_argument("Entrada no válida para BigInteger");
  }
  BigUnsigned numero;
  is >> numero;  
  entero = BigInteger(numero);  
  entero.SetSigno(es_negativo); 

  return is;
}

/**
 * @brief Operador de suma 
 * @param other 
 * @return Suma de dos BigIntegers
 */
BigInteger BigInteger::operator+(const BigInteger& other) const {
  if (signo_ == other.GetSigno()) {
    BigUnsigned result = numero_ + other.GetNumero();
    BigInteger result_bigint(result);
    result_bigint.SetSigno(signo_);  
    return result_bigint;
  }

  else {
    if (!(numero_ < other.GetNumero())) {
      BigUnsigned result = numero_ - other.GetNumero();
      BigInteger result_bigint(result);
      result_bigint.SetSigno(signo_);
      return result_bigint;
    } else {
      BigUnsigned result = other.GetNumero() - numero_;
      BigInteger result_bigint(result);
      result_bigint.SetSigno(other.GetSigno());
      return result_bigint;
    }
  }
}

/**
 * @brief Operador de resta
 * @param other 
 * @return Resta entre dos BigIntegers
 */
BigInteger BigInteger::operator-(const BigInteger& other) const {
  if (signo_ == other.GetSigno()) {
    if (!(numero_ < other.GetNumero())) {
      BigUnsigned result = numero_ - other.GetNumero();
      BigInteger result_bigint(result);
      result_bigint.SetSigno(signo_);
      return result_bigint;
    } else {
      BigUnsigned result = other.GetNumero() - numero_;
      BigInteger result_bigint(result);
      result_bigint.SetSigno(!signo_);  
      return result_bigint;
    }
  } else {
    BigUnsigned result = numero_ + other.GetNumero();
    BigInteger result_bigint(result);
    result_bigint.SetSigno(signo_);
    return result_bigint;
  }
}

/**
 * @brief Operador de producto
 * @param other 
 * @return producto entre dos BigIntegers
 */
BigInteger BigInteger::operator*(const BigInteger& other) const {
  BigUnsigned result = numero_ * other.GetNumero();
  bool result_sign = signo_ == other.GetSigno();
  BigInteger result_bigint(result);
  result_bigint.SetSigno(result_sign);

  return result_bigint;
}

/**
 * @brief Operador de división
 * @param other 
 * @return división entre dos BigIntegers
 */
BigInteger BigInteger::operator/(const BigInteger& other) const {
  BigUnsigned result = numero_ / other.GetNumero();
  bool result_sign = signo_ == other.GetSigno();
  BigInteger result_bigint(result);
  result_bigint.SetSigno(result_sign);

  return result_bigint;
}

/**
 * @brief Operador de módulo
 * @param other 
 * @return módulo entre dos BigIntegers
 */
BigInteger BigInteger::operator%(const BigInteger& divisor) const {
  BigUnsigned abs_numero = numero_;
  BigUnsigned abs_divisor = divisor.GetNumero();

  BigUnsigned result = abs_numero % abs_divisor;

  bool result_sign = !(signo_ == divisor.GetSigno());

  if (!result_sign) {
    if (!(result == BigUnsigned())) {
      result = abs_divisor - result;  
    }
  }

  BigInteger result_bigint(result);
  result_bigint.SetSigno(result_sign); 
  return result_bigint;
}

/**
 * @brief Operador de comparación de igualdad
 * @param otro 
 * @return Si dos BigIntegers son iguales
 */
bool BigInteger::operator==(const BigInteger& otro) const {
  if (signo_ != otro.GetSigno()) {
    return false;  
  }

  return numero_ == otro.GetNumero();
}

/**
 * @brief Operador de comparación de menor
 * @param otro 
 * @return Si un BigIntegers es menor que otro
 */
bool BigInteger::operator<(const BigInteger& otro) const {
  if (signo_ != otro.GetSigno()) {
    return signo_;  
  }

  return numero_ < otro.GetNumero();
}

BigInteger& BigInteger::operator++() { //pre-incemento
  ++numero_; 
  return *this;
}

BigInteger BigInteger::operator++(int) { //post-incremento
  BigInteger temp = numero_;
  numero_++;
  return temp;
}

BigInteger& BigInteger::operator--() { //pre-incremento
  --numero_;
  return *this;
}

BigInteger BigInteger::operator--(int) { //post-incremento
  BigInteger temp = numero_;
  numero_--;
  return temp;
}

/**
 * @brief Operador de asignación
 * @param entero 
 * @return el valor actualizado del BigInteger
 */
BigInteger& BigInteger::operator=(const BigInteger& entero) {
  numero_ = entero.GetNumero();
  signo_ = entero.GetSigno();
  return *this;
}

/**
 * @brief Esta función calcula el MCD de dos BigIntegers
 * @param numero1 
 * @param numero2 
 * @return el MCD de dichos números en un BigInteger
 */
BigInteger mcd(const BigInteger& numero1, const BigInteger& numero2) {
  if (numero2.GetNumero() == BigUnsigned()) return numero1;
  return mcd(numero2, numero1 % numero2);
}