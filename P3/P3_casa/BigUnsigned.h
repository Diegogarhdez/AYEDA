// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 3
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/03/2025
// Archivo BigUnsigned.h
// Descripción: contiene la clase BigUnsigned


#ifndef BIGUNSIGNED_H_
#define BIGUNSIGNED_H_

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "BigNumber.h"
#include "BigRational.h"
#include "BigInteger.h"

template<unsigned char Base> class BigInteger;
template<unsigned char Base> class BigNumber;
template<unsigned char Base> class BigRational;
class BigNumberException;
class BigNumberBadDigit;
class BigNumberDivisionByZero;


template<unsigned char Base = 10>
class BigUnsigned : public BigNumber<Base> {
 public:
  BigUnsigned(unsigned long long num = 0) : numerin_() {
    try {
      if (Base < 2 || Base > 26) {
        throw std::invalid_argument("Base debe estar entre 2 y 26.");
      }
      while (num > 0) {
        numerin_.push_back(num % Base);
        num /= Base;
      }
      if (numerin_.empty()) numerin_.push_back(0); 
    } catch (BigNumberException &e) {
      std::cout << e.what() << "\n";
    }
  }
  BigUnsigned(const unsigned char* );
  BigUnsigned(const BigUnsigned& numeron) : numerin_(numeron.numerin_) { } //constructor parametrizado
  BigUnsigned(const char* str) : numerin_() {
    std::string input(str);
    numerin_.clear();
    for (char c : input) {
      unsigned char valor;

      if (std::isdigit(c)) valor = c - '0';
      else if (Base > 10 && c >= 'A' && c <= 'Z') valor = 10 + (c - 'A');
      //else throw BigNumberBadDigit();

      //if (valor >= Base) throw BigNumberBadDigit();

      numerin_.push_back(valor);
    }
  }

  BigUnsigned& operator=(const BigUnsigned<Base>&);
  bool operator==(const BigUnsigned<Base>&) const;
  bool operator<(const BigUnsigned<Base>&) const;
  BigUnsigned<Base>& operator++(); // Pre-incremento
  BigUnsigned<Base> operator++(int); // Post-incremento
  BigUnsigned<Base>& operator--(); // Pre-decremento
  BigUnsigned<Base> operator--(int); // Post-decremento
  BigUnsigned<Base> operator%(const BigUnsigned<Base>&) const;
  BigUnsigned<Base> operator-(const BigUnsigned<Base>&) const;
  BigUnsigned<Base> operator*(const BigUnsigned<Base>&) const;
  BigUnsigned<Base> operator+(const BigUnsigned<Base>&) const;
  BigUnsigned<Base> operator/(const BigUnsigned<Base>&) const;

  inline std::vector<unsigned char> GetNumerin() const { return numerin_;}
  inline std::vector<unsigned char> GetNumerin() { return numerin_;}
  inline void SetNumerin(const std::vector<unsigned char> otro) {numerin_ = otro;}

  BigNumber<Base>& add(const BigNumber<Base>& other) const override {
    const BigUnsigned<Base>& aux = dynamic_cast<const BigUnsigned<Base>&>(other);
    return *(new BigUnsigned<Base>(*this + aux));
  }
  BigNumber<Base>& subtract(const BigNumber<Base>& other) const override {
    const BigUnsigned<Base>& aux = dynamic_cast<const BigUnsigned<Base>&>(other);
    return *(new BigUnsigned<Base>(*this - aux));
  }
  BigNumber<Base>& multiply(const BigNumber<Base>& other) const override {
    const BigUnsigned<Base>& aux = dynamic_cast<const BigUnsigned<Base>&>(other);
    return *(new BigUnsigned<Base>(*this * aux));
  }
  BigNumber<Base>& divide(const BigNumber<Base>& other) const override {
    const BigUnsigned<Base>& aux = dynamic_cast<const BigUnsigned<Base>&>(other);
    if (aux == BigUnsigned<Base>()) throw (BigNumberDivisionByZero());
    return *(new BigUnsigned<Base>(*this / aux));
  }

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wclass-conversion"
  inline operator BigUnsigned<Base>() const override { return *this; }
  #pragma GCC diagnostic pop
  inline operator BigInteger<Base>() const override { return BigInteger<Base>(*this); }
  inline operator BigRational<Base>() const override { return BigRational<Base>(*this); }

  std::ostream& write(std::ostream& os) const override {
    return os << *this << "u";
  }
  std::istream& read(std::istream& is) override {
    return is >> *this;
  }

 private:
  std::vector<unsigned char> numerin_;
};


template <unsigned char Base>
BigUnsigned<Base>::BigUnsigned(const unsigned char* puntero) : numerin_() {
  if (!puntero) {
    throw std::invalid_argument("Puntero nulo en constructor BigUnsigned.");
  }
  size_t length = std::strlen(reinterpret_cast<const char*>(puntero));
  numerin_.reserve(length);

  for (size_t i = length; i > 0; --i) {
    char c = puntero[i - 1];
    unsigned char valor;
    if (std::isdigit(c)) {
      valor = c - '0';  
    } else if (Base > 10 && c >= 'A' && c <= 'Z') {
      valor = 10 + (c - 'A');  
    } else {
      //throw BigNumberBadDigit();
    }

    if (valor >= Base) {
      //throw BigNumberBadDigit();
    }

    numerin_.push_back(valor); 
  }
}


/**
 * @brief Operador de salida para la clase BigUnsigned
 * @param os 
 * @param otro 
 * @return parametro os
 */
template <unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigUnsigned<Base>& otro) {
  for (size_t i = otro.GetNumerin().size(); i > 1; --i) {
    unsigned char d = otro.GetNumerin().at(i - 1); 
    if (d < 10) {
      os << static_cast<char>('0' + d);
    } else {
      os << static_cast<char>('A' + (d - 10));
    }  
  }
  return os;
}

/**
 * @brief Operador de salida
 * @param is 
 * @param num 
 * @return el valor de is
 */
template <unsigned char Base>
std::istream& operator>>(std::istream& is, BigUnsigned<Base>& num) {
  std::string input;
  is >> input;

  std::vector<unsigned char> temp;
  for (char c : input) {
    unsigned char valor;
    if ('0' <= c && c <= '9')
      valor = c - '0';
    else if (Base > 10 && c >= 'A' && c <= 'Z')
      valor = 10 + (c - 'A');
    //else throw BigNumberBadDigit(); 
    //if (valor >= Base) throw BigNumberBadDigit(); 
    temp.push_back(valor);
  }

  num.SetNumerin(temp);
  return is;
}

/**
 * @brief operador de asignación
 * @param otro_numerin 
 * @return retorna el BigUnsiged asignado
 */
template<unsigned char Base> BigUnsigned<Base>& BigUnsigned<Base>::operator=(const BigUnsigned<Base>& otro_numerin) {
	numerin_ = otro_numerin.numerin_;
	return *this;
}

/**
 * @brief Operador de suma
 * @param sumador 
 * @return BigUnsigned sumado
 */
template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator+(const BigUnsigned<Base>& sumador) const {
  BigUnsigned<Base> suma;
  size_t max_size = std::max(numerin_.size(), sumador.numerin_.size());
  suma.numerin_.assign(max_size + 1, 0);
  unsigned carry = 0;
  for (size_t i = 0; i < max_size; ++i) {
    unsigned digit1 = (i < numerin_.size()) ? numerin_[i] : 0;
    unsigned digit2 = (i < sumador.numerin_.size()) ? sumador.numerin_[i] : 0;

    unsigned sum = digit1 + digit2 + carry;
    suma.numerin_[i] = sum % Base;  
    carry = sum / Base;
  }

  if (carry) {
    suma.numerin_[max_size] = carry;  
  } else {
		suma.numerin_.pop_back();
	}
  return suma;
}

/**
 * @brief Operador de resta
 * @param otro 
 * @return resta de dos BigUnsigned
 */
template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator-(const BigUnsigned<Base>& otro) const {
  if (*this < otro) return BigUnsigned<Base>();
  BigUnsigned<Base> result;
  result.numerin_ = numerin_;
  unsigned carry = 0;

  for (size_t i = 0; i < otro.numerin_.size(); i++) {
    if (result.numerin_[i] < otro.numerin_[i] + carry) {
      result.numerin_[i] = result.numerin_[i] + Base - (otro.numerin_[i] + carry);
      carry = 1; 
    } else {
      result.numerin_[i] -= (otro.numerin_[i] + carry);
      carry = 0;
    }
  }

  for (size_t i = otro.numerin_.size(); i < numerin_.size(); i++) {
    if (result.numerin_[i] < carry) {
      result.numerin_[i] += Base - carry;
      carry = 1;
    } else {
      result.numerin_[i] -= carry;
      carry = 0;
    }
  }
  while (result.numerin_.size() > 1 && result.numerin_[result.numerin_.size() - 1] == 0) {
    result.numerin_.pop_back();
  }

  return result;
}

/**
 * @brief Operador de producto
 * @param otro 
 * @return producto entre 2 BigUnsigned
 */
template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator*(const BigUnsigned<Base>& otro) const {
  if (*this == BigUnsigned<Base>() || otro == BigUnsigned<Base>()) {
    return BigUnsigned<Base>();
  }

  BigUnsigned<Base> resultado;
  resultado.numerin_.assign(numerin_.size() + otro.numerin_.size(), 0);

  for (size_t i = 0; i < numerin_.size(); ++i) {
    unsigned carry = 0;
    for (size_t j = 0; j < otro.numerin_.size() || carry; ++j) {
      unsigned long long mul = resultado.numerin_[i + j] + carry;
      if (j < otro.numerin_.size()) {
        mul += static_cast<unsigned long long>(numerin_[i]) * otro.numerin_[j];
      }
      resultado.numerin_[i + j] = static_cast<unsigned char>(mul % Base);
      carry = static_cast<unsigned>(mul / Base);
    }
  }

  while (!resultado.numerin_.empty() && resultado.numerin_.back() == 0) {
    resultado.numerin_.pop_back();
  }
  if (resultado.numerin_.empty()) {
    resultado.numerin_.push_back(0);
  }

  return resultado;
}

/**
 * @brief Operador de división
 * @param divisor 
 * @return División entre dos BigUnsigned
 */
template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator/(const BigUnsigned<Base>& divisor) const {
  if (divisor == BigUnsigned<Base>()) {
    throw std::runtime_error("División por cero no permitida");
  }

  BigUnsigned<Base> cociente, residuo;
  cociente.numerin_.assign(numerin_.size(), 0);

  for (int i = numerin_.size() - 1; i >= 0; --i) {
    residuo = residuo * BigUnsigned<Base>(Base) + BigUnsigned<Base>(numerin_[i]);  
    unsigned digito_cociente = 0;
    while (!(residuo < divisor)) {  
      residuo = residuo - divisor;
      ++digito_cociente;
    }
    cociente.numerin_[i] = digito_cociente;
  }

  while (cociente.numerin_.size() > 1 && cociente.numerin_.back() == 0) {
    cociente.numerin_.pop_back();
  }

  return cociente;
}

/**
 * @brief Operador de módulo
 * @param divisor 
 * @return Resto de la división de dos BigUnsigned
 */
template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator%(const BigUnsigned<Base>& divisor) const {
  if (divisor == BigUnsigned<Base>()) {
    throw std::invalid_argument("Divisor no puede ser 0");
  }

  if (*this < divisor) {
    return *this;  
  }
  BigUnsigned<Base> quotient = *this / divisor; 
  BigUnsigned<Base> product = quotient * divisor; 
  BigUnsigned<Base> remainder = *this - product; 

  return remainder;
}

/**
 * @brief Operador de comparación de igualdad
 * @param otro 
 * @return Si dos BigUnsigned son iguales
 */
template<unsigned char Base> bool BigUnsigned<Base>::operator==(const BigUnsigned<Base>& otro) const {
  return numerin_ == otro.numerin_; 
}

/**
 * @brief Operador de menor
 * @param otro 
 * @return Si un BigUnsigned es menor que otro
 */
template<unsigned char Base> bool BigUnsigned<Base>::operator<(const BigUnsigned<Base>& otro) const {
  if (numerin_.size() != otro.numerin_.size()) {
    return numerin_.size() < otro.numerin_.size();
  }
  for (int i = numerin_.size() - 1; i >= 0; --i) {
    if (numerin_[i] != otro.numerin_[i]) {
      return numerin_[i] < otro.numerin_[i];
    }
  }
  return false;
}

template<unsigned char Base> BigUnsigned<Base>& BigUnsigned<Base>::operator++() { // Pre-incremento 
  *this = *this + BigUnsigned(1);
  return *this;
}

template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator++(int) { // Post-incremento 
  BigUnsigned<Base> copia = *this;
  *this = *this + BigUnsigned<Base>(1);
  return copia;
}

template<unsigned char Base> BigUnsigned<Base>& BigUnsigned<Base>::operator--() { // Pre-decremento 
  if (*this == BigUnsigned<Base>()) throw std::underflow_error("No se puede decrementar debajo de 0");
  *this = *this - BigUnsigned<Base>(1);
  return *this;
}

template<unsigned char Base> BigUnsigned<Base> BigUnsigned<Base>::operator--(int) { // Post-decremento 
  if (*this == BigUnsigned<Base>()) throw std::underflow_error("No se puede decrementar debajo de 0");
  BigUnsigned<Base> copia = *this;
  *this = *this - BigUnsigned<Base>(1);
  return copia;
}

#endif