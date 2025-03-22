// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 3
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/03/2025
// Archivo BigInteger.h
// Descripción: contiene la clase BigInteger

#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#include "BigNumber.h"
#include "BigUnsigned.h"

template<unsigned char Base> class BigUnsigned;
template<unsigned char Base> class BigNumber;
template<unsigned char Base> class BigRational;
template<unsigned char Base> class BigComplex;


template<unsigned char Base = 10>
class BigInteger : public BigNumber<Base> {
 public:
  BigInteger(int n = 0) : numero_(std::abs(n)), signo_(n < 0) { }

  // Constructor desde un BigUnsigned (sin signo negativo)
  BigInteger(const BigUnsigned<Base>& numeron) : numero_(numeron), signo_(false) { }

  // Constructor de copia
  BigInteger(const BigInteger<Base>& otro) : numero_(otro.numero_), signo_(otro.signo_) { }

  BigInteger(const char* cadena) : numero_(), signo_(false) {
    std::string input(cadena);
    bool es_negativo = false;
    if (!input.empty() && input[0] == '-') {
      es_negativo = true;
      input = input.substr(1); 
    }
    std::reverse(input.begin(), input.end());
    numero_ = BigUnsigned<Base>(input.c_str());
    signo_ = es_negativo;
  }

  // Operadores aritméticos
  BigInteger<Base> operator+(const BigInteger<Base>&) const;
  BigInteger<Base> operator-(const BigInteger<Base>&) const;
  BigInteger<Base> operator/(const BigInteger<Base>&) const;
  BigInteger<Base> operator*(const BigInteger<Base>&) const;
  BigInteger<Base> operator%(const BigInteger<Base>&) const;

  // Operadores de incremento y asignación
  BigInteger<Base>& operator++();     //pre-incremento
  BigInteger<Base>  operator++(int);  //post-incremento
  BigInteger<Base>& operator--();     //pre-decremento
  BigInteger<Base>  operator--(int);  //post-decremento
  BigInteger<Base>& operator=(const BigInteger<Base>&);

  // Comparaciones
  bool operator==(const BigInteger<Base>&) const;
  bool operator<(const BigInteger<Base>&) const;

  // Getters / Setters
  inline BigUnsigned<Base> GetNumero() const { return numero_; }
  inline bool GetSigno() const { return signo_; }
  inline void SetNumero(const BigUnsigned<Base>& otro) { numero_ = otro; }
  inline void SetSigno(const bool& otro_signo) { signo_ = otro_signo; }

  // Implementaciones virtuales de BigNumber
  BigNumber<Base>& add(const BigNumber<Base>& other) const override {
    const BigInteger<Base>& aux = dynamic_cast<const BigInteger<Base>&>(other);
    return *(new BigInteger<Base>(*this + aux));
  }
  BigNumber<Base>& subtract(const BigNumber<Base>& other) const override {
    const BigInteger<Base>& aux = dynamic_cast<const BigInteger<Base>&>(other);
    return *(new BigInteger<Base>(*this - aux));
  }
  BigNumber<Base>& multiply(const BigNumber<Base>& other) const override {
    const BigInteger<Base>& aux = dynamic_cast<const BigInteger<Base>&>(other);
    return *(new BigInteger<Base>(*this * aux));
  }
  BigNumber<Base>& divide(const BigNumber<Base>& other) const override {
    const BigInteger<Base>& aux = dynamic_cast<const BigInteger<Base>&>(other);
    if (aux == BigInteger<Base>(0)) {
      throw (BigNumberDivisionByZero());
    }
    return *(new BigInteger<Base>(*this / aux));
  }

  // Conversiones
  operator BigUnsigned<Base>() const override { return numero_; }
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wclass-conversion"
  operator BigInteger<Base>()   const override { return *this; }
  #pragma GCC diagnostic pop
  operator BigRational<Base>() const override { return BigRational<Base>(*this); }
  operator BigComplex<Base>() const override { return BigComplex<Base>(*this, BigInteger<Base>('0')); }

  // Lectura/Escritura
  std::ostream& write(std::ostream& os) const override {
    return os << *this << "i";
  }
  std::istream& read(std::istream& is) override {
    return is >> *this;
  }

 private:
  BigUnsigned<Base> numero_;  
  bool signo_;                // true si es negativo; false si es positivo
};

// Sobrecarga de operador<< para BigInteger
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigInteger<Base>& entero) {
  if (entero.GetSigno())
    os << "-";
  os << entero.GetNumero();
  return os;
}

// Sobrecarga de operador>> para BigInteger
template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigInteger<Base>& entero) {
  std::string input;
  is >> input;
  bool es_negativo = false;
  if (!input.empty() && (input[0] == '-' || input[0] == '+')) {
    es_negativo = (input[0] == '-');
    input = input.substr(1);
  }
  // Construimos un BigUnsigned a partir del resto
  BigUnsigned<Base> numero(input.c_str());
  entero.SetNumero(numero);
  entero.SetSigno(es_negativo);
  return is;
}

// Operadores

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator+(const BigInteger<Base>& other) const {
  // Si tienen el mismo signo, se suman los valores absolutos
  if (signo_ == other.signo_) {
    BigUnsigned<Base> result = numero_ + other.numero_;
    BigInteger<Base>  result_bigint(result);
    result_bigint.signo_ = signo_;
    return result_bigint;
  } else {
    // Signos distintos => se hace una resta de valores absolutos
    if (!(numero_ < other.numero_)) {
      BigUnsigned<Base> result = numero_ - other.numero_;
      BigInteger<Base>  result_bigint(result);
      result_bigint.signo_ = signo_;
      return result_bigint;
    } else {
      BigUnsigned<Base> result = other.numero_ - numero_;
      BigInteger<Base>  result_bigint(result);
      result_bigint.signo_ = other.signo_;
      return result_bigint;
    }
  }
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator-(const BigInteger<Base>& other) const {
  // Mismo signo => se hace la resta
  if (signo_ == other.signo_) {
    if (!(numero_ < other.numero_)) {
      BigUnsigned<Base> result = numero_ - other.numero_;
      BigInteger<Base> result_bigint(result);
      result_bigint.signo_ = signo_;
      return result_bigint;
    } else {
      BigUnsigned<Base> result = other.numero_ - numero_;
      BigInteger<Base> result_bigint(result);
      // si this < other, el resultado es negativo si ambos eran positivos (o positivo si ambos negativos).
      result_bigint.signo_ = !signo_;
      return result_bigint;
    }
  } else {
    // Distinto signo => se suman los valores absolutos
    BigUnsigned<Base> result = numero_ + other.numero_;
    BigInteger<Base> result_bigint(result);
    result_bigint.signo_ = signo_;
    return result_bigint;
  }
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator*(const BigInteger<Base>& other) const {
  BigUnsigned<Base> result = numero_ * other.numero_;
  bool result_sign = (signo_ != other.signo_); // signos distintos => negativo
  BigInteger<Base> result_bigint(result);
  result_bigint.signo_ = result_sign;
  return result_bigint;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator/(const BigInteger<Base>& other) const {
  if (other.numero_ == BigUnsigned<Base>('0')) {
    throw BigNumberDivisionByZero();
  }
  BigUnsigned<Base> result = numero_ / other.numero_;
  bool result_sign = (signo_ != other.signo_);
  BigInteger<Base> result_bigint(result);
  result_bigint.signo_ = result_sign;
  return result_bigint;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator%(const BigInteger<Base>& divisor) const {
  if (divisor.numero_ == BigUnsigned<Base>('0')) {
    throw BigNumberDivisionByZero();
  }
  BigUnsigned<Base> abs_numero  = numero_;
  BigUnsigned<Base> abs_divisor = divisor.numero_;
  BigUnsigned<Base> result      = abs_numero % abs_divisor;
  // El signo del módulo, en muchas definiciones, se considera el del dividendo.
  BigInteger<Base> mod_bigint(result);
  mod_bigint.signo_ = signo_;
  return mod_bigint;
}

// Comparaciones

template<unsigned char Base>
bool BigInteger<Base>::operator==(const BigInteger<Base>& otro) const {
  return (signo_ == otro.signo_) && (numero_ == otro.numero_);
}

template<unsigned char Base>
bool BigInteger<Base>::operator<(const BigInteger<Base>& otro) const {
  // Si difieren de signo
  if (signo_ != otro.signo_) {
    return signo_;
  }
  if (!signo_) { // ambos positivos
    return numero_ < otro.numero_;
  } else {
    return otro.numero_ < numero_;
  }
}

// Operadores de pre/post-incremento/decremento

template<unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator++() { //pre-incremento
  // ++(valor) => this + 1
  *this = *this + BigInteger<Base>(1);
  return *this;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator++(int) { //post-incremento
  BigInteger<Base> temp(*this);
  *this = *this + BigInteger<Base>(1);
  return temp;
}

template<unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator--() { //pre-decremento
  *this = *this - BigInteger<Base>(1);
  return *this;
}

template<unsigned char Base>
BigInteger<Base> BigInteger<Base>::operator--(int) { //post-decremento
  BigInteger<Base> temp(*this);
  *this = *this - BigInteger<Base>(1);
  return temp;
}

template<unsigned char Base>
BigInteger<Base>& BigInteger<Base>::operator=(const BigInteger<Base>& entero) {
  numero_ = entero.numero_;
  signo_  = entero.signo_;
  return *this;
}


/**
 * @brief Calcula el MCD de dos BigIntegers.
 * @param numero1
 * @param numero2
 * @return El MCD de dichos números como BigInteger
 */
template<unsigned char Base>
BigInteger<Base> mcd(const BigInteger<Base>& numero1, const BigInteger<Base>& numero2) {
  if (numero2 == BigInteger<Base>(0)) {
    return numero1;
  }
  return mcd(numero2, numero1 % numero2);
}

#endif // BIGINTEGER_H_

