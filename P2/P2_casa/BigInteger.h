// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 2
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/02/2025
// Archivo BigInteger.h
// Descripción: contiene la clase BigInteger

#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <iostream>
#include <vector>

#include "BigUnsigned.h"

template<unsigned char Base = 10>
class BigInteger {
 public:
  BigInteger(int n = 0) : numero_(std::abs(n)), signo_(n < 0) { }
  BigInteger(const BigUnsigned<Base>& numeron) : numero_(numeron), signo_(false) { }
  BigInteger(const BigInteger<Base>& otro) : numero_(otro.numero_), signo_(otro.signo_) { }

  BigInteger<Base> operator+(const BigInteger<Base>&) const;
  BigInteger<Base> operator-(const BigInteger<Base>&) const;
  BigInteger<Base> operator/(const BigInteger<Base>&) const;
  BigInteger<Base> operator*(const BigInteger<Base>&) const;
  BigInteger<Base> operator%(const BigInteger<Base>&) const;
  BigInteger<Base>& operator++(); //pre-incremento
  BigInteger<Base> operator++(int); //post-incremento
  BigInteger<Base>& operator--(); //pre-incremento
  BigInteger<Base> operator--(int); //post-incremento
  BigInteger<Base>& operator=(const BigInteger<Base>&);
  bool operator==(const BigInteger<Base>&) const;
  bool operator<(const BigInteger<Base>&) const;

  inline BigUnsigned<Base> GetNumero() const { return numero_; }
  inline bool GetSigno() const { return signo_; }
  inline void SetNumero(const BigUnsigned<Base>& otro) { numero_ = otro; }
  inline void SetSigno(const bool& otro_signo) { signo_ = otro_signo; }
 private:
  BigUnsigned<Base> numero_;
  bool signo_;
};

/**
 * @brief Operador de salida
 * @param os 
 * @param entero 
 * @return Salida por pantalla de un BigInteger
 */
template<unsigned char Base> std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& entero) {
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
template<unsigned char Base> std::istream& operator>>(std::istream& is, BigInteger<Base>& entero) {
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
  BigUnsigned<Base> numero;
  is >> numero;  
  entero = BigInteger<Base>(numero);  
  entero.SetSigno(es_negativo); 

  return is;
}

/**
 * @brief Operador de suma 
 * @param other 
 * @return Suma de dos BigIntegers
 */
template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator+(const BigInteger<Base>& other) const {
  if (signo_ == other.GetSigno()) {
    BigUnsigned<Base> result = numero_ + other.GetNumero();
    BigInteger<Base> result_bigint(result);
    result_bigint.SetSigno(signo_);  
    return result_bigint;
  }

  else {
    if (!(numero_ < other.GetNumero())) {
      BigUnsigned<Base> result = numero_ - other.GetNumero();
      BigInteger<Base> result_bigint(result);
      result_bigint.SetSigno(signo_);
      return result_bigint;
    } else {
      BigUnsigned<Base> result = other.GetNumero() - numero_;
      BigInteger<Base> result_bigint(result);
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
template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& other) const {
  if (signo_ == other.GetSigno()) {
    if (!(numero_ < other.GetNumero())) {
      BigUnsigned<Base> result = numero_ - other.GetNumero();
      BigInteger<Base> result_bigint(result);
      result_bigint.SetSigno(signo_);
      return result_bigint;
    } else {
      BigUnsigned<Base> result = other.GetNumero() - numero_;
      BigInteger<Base> result_bigint(result);
      result_bigint.SetSigno(!signo_);  
      return result_bigint;
    }
  } else {
    BigUnsigned<Base> result = numero_ + other.GetNumero();
    BigInteger<Base> result_bigint(result);
    result_bigint.SetSigno(signo_);
    return result_bigint;
  }
}

/**
 * @brief Operador de producto
 * @param other 
 * @return producto entre dos BigIntegers
 */
template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& other) const {
  BigUnsigned<Base> result = numero_ * other.GetNumero();
  bool result_sign = signo_ == other.GetSigno();
  BigInteger<Base> result_bigint(result);
  result_bigint.SetSigno(result_sign);

  return result_bigint;
}

/**
 * @brief Operador de división
 * @param other 
 * @return división entre dos BigIntegers
 */
template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator/(const BigInteger<Base>& other) const {
  BigUnsigned<Base> result = numero_ / other.GetNumero();
  bool result_sign = signo_ == other.GetSigno();
  BigInteger<Base> result_bigint(result);
  result_bigint.SetSigno(result_sign);

  return result_bigint;
}

/**
 * @brief Operador de módulo
 * @param other 
 * @return módulo entre dos BigIntegers
 */
template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& divisor) const {
  BigUnsigned<Base> abs_numero = numero_;
  BigUnsigned<Base> abs_divisor = divisor.GetNumero();

  BigUnsigned<Base> result = abs_numero % abs_divisor;

  bool result_sign = !(signo_ == divisor.GetSigno());

  if (!result_sign) {
    if (!(result == BigUnsigned<Base>())) {
      result = abs_divisor - result;  
    }
  }

  BigInteger<Base> result_bigint(result);
  result_bigint.SetSigno(result_sign); 
  return result_bigint;
}

/**
 * @brief Operador de comparación de igualdad
 * @param otro 
 * @return Si dos BigIntegers son iguales
 */
template<unsigned char Base> bool BigInteger<Base>::operator==(const BigInteger<Base>& otro) const {
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
template<unsigned char Base> bool BigInteger<Base>::operator<(const BigInteger<Base>& otro) const {
  if (signo_ != otro.GetSigno()) {
    return signo_;  
  }
  return numero_ < otro.GetNumero();
}

template<unsigned char Base> BigInteger<Base>& BigInteger<Base>::operator++() { //pre-incemento
  ++numero_; 
  return *this;
}

template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator++(int) { //post-incremento
  BigInteger<Base> temp = numero_;
  numero_++;
  return temp;
}

template<unsigned char Base> BigInteger<Base>& BigInteger<Base>::operator--() { //pre-incremento
  --numero_;
  return *this;
}

template<unsigned char Base> BigInteger<Base> BigInteger<Base>::operator--(int) { //post-incremento
  BigInteger<Base> temp = numero_;
  numero_--;
  return temp;
}

/**
 * @brief Operador de asignación
 * @param entero 
 * @return el valor actualizado del BigInteger
 */
template<unsigned char Base> BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& entero) {
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
template<unsigned char Base> BigInteger<Base> mcd(const BigInteger<Base>& numero1, const BigInteger<Base>& numero2) {
  if (numero2.GetNumero() == BigUnsigned<Base>()) return numero1;
  return mcd(numero2, numero1 % numero2);
}

#endif