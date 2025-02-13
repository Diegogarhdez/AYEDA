// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigUnsigned.cc
// Descripción: contiene la implementación de la clase BigUnsigned

#include <string>
#include <cstring>
#include "BigUnsigned.h"


/**
 * @brief Constructor unsigned
 * @param n 
 */
BigUnsigned::BigUnsigned(unsigned n) : numerin_() {
  if (n == 0) {
    numerin_.push_back(0); 
  }
  while (n > 0) {
    numerin_.push_back(n % 10); 
    n /= 10;
  }
}

/**
 * @brief Constructor char*
 * @param puntero 
 */
BigUnsigned::BigUnsigned(const unsigned char* puntero) : numerin_() {
  if (!puntero) {
    throw std::invalid_argument("Puntero nulo en constructor BigUnsigned.");
  }

  size_t length = std::strlen(reinterpret_cast<const char*>(puntero));
  numerin_.reserve(length);

  for (size_t i = length; i > 0; --i) {
    if (!isdigit(puntero[i - 1])) {
      throw std::invalid_argument("Entrada no válida: solo se permiten dígitos.");
    }
    numerin_.push_back(puntero[i - 1] - '0');  // Almacenar en orden inverso
  }
}

//constructor parametrizado
BigUnsigned::BigUnsigned(const BigUnsigned& numeron) : numerin_(numeron.numerin_) { }


/**
 * @brief operador de asignación
 * @param otro_numerin 
 * @return retorna el BigUnsiged asignado
 */
BigUnsigned& BigUnsigned::operator=(const BigUnsigned& otro_numerin) {
	numerin_ = otro_numerin.numerin_;
	return *this;
}

/**
 * @brief Operador de suma
 * @param sumador 
 * @return BigUnsigned sumado
 */
BigUnsigned BigUnsigned::operator+(const BigUnsigned& sumador) const {
  BigUnsigned suma;
  size_t max_size = std::max(numerin_.size(), sumador.numerin_.size());
  suma.numerin_.assign(max_size + 1, 0);
  unsigned carry = 0;
  for (size_t i = 0; i < max_size; ++i) {
    unsigned digit1 = (i < numerin_.size()) ? numerin_[i] : 0;
    unsigned digit2 = (i < sumador.numerin_.size()) ? sumador.numerin_[i] : 0;

    unsigned sum = digit1 + digit2 + carry;
    suma.numerin_[i] = sum % 10;  
    carry = sum / 10;
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
BigUnsigned BigUnsigned::operator-(const BigUnsigned& otro) const {
  if (*this < otro) return BigUnsigned();
  BigUnsigned result;
  result.numerin_ = numerin_;
  unsigned carry = 0;

  for (size_t i = 0; i < otro.numerin_.size(); i++) {
    if (result.numerin_[i] < otro.numerin_[i] + carry) {
      result.numerin_[i] = result.numerin_[i] + 10 - (otro.numerin_[i] + carry);
      carry = 1; 
    } else {
      result.numerin_[i] -= (otro.numerin_[i] + carry);
      carry = 0;
    }
  }

  for (size_t i = otro.numerin_.size(); i < numerin_.size(); i++) {
    if (result.numerin_[i] < carry) {
      result.numerin_[i] += 10 - carry;
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
BigUnsigned BigUnsigned::operator*(const BigUnsigned& otro) const {
  if (*this == BigUnsigned() || otro == BigUnsigned()) {
    return BigUnsigned();
  }

  BigUnsigned resultado;
  resultado.numerin_.assign(numerin_.size() + otro.numerin_.size(), 0);

  for (size_t i = 0; i < numerin_.size(); ++i) {
    unsigned carry = 0;
    for (size_t j = 0; j < otro.numerin_.size() || carry; ++j) {
      unsigned long long mul = resultado.numerin_[i + j] + carry;
      if (j < otro.numerin_.size()) {
        mul += static_cast<unsigned long long>(numerin_[i]) * otro.numerin_[j];
      }
      resultado.numerin_[i + j] = static_cast<unsigned char>(mul % 10);
      carry = static_cast<unsigned>(mul / 10);
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
BigUnsigned BigUnsigned::operator/(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned()) {
    throw std::runtime_error("División por cero no permitida");
  }

  BigUnsigned cociente, residuo;
  cociente.numerin_.assign(numerin_.size(), 0);

  for (int i = numerin_.size() - 1; i >= 0; --i) {
    residuo = residuo * BigUnsigned(10) + BigUnsigned(numerin_[i]);  
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
BigUnsigned BigUnsigned::operator%(const BigUnsigned& divisor) const {
  if (divisor == BigUnsigned()) {
    throw std::invalid_argument("Divisor no puede ser 0");
  }

  if (*this < divisor) {
    return *this;  
  }
  BigUnsigned quotient = *this / divisor; 
  BigUnsigned product = quotient * divisor; 
  BigUnsigned remainder = *this - product; 

  return remainder;
}

/**
 * @brief Operador de comparación de igualdad
 * @param otro 
 * @return Si dos BigUnsigned son iguales
 */
bool BigUnsigned::operator==(const BigUnsigned& otro) const {
  return numerin_ == otro.numerin_; 
}

/**
 * @brief Operador de menor
 * @param otro 
 * @return Si un BigUnsigned es menor que otro
 */
bool BigUnsigned::operator<(const BigUnsigned& otro) const {
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

BigUnsigned& BigUnsigned::operator++() { // Pre-incremento 
  *this = *this + BigUnsigned(1);
  return *this;
}

BigUnsigned BigUnsigned::operator++(int) { // Post-incremento 
  BigUnsigned copia = *this;
  *this = *this + BigUnsigned(1);
  return copia;
}

BigUnsigned& BigUnsigned::operator--() { // Pre-decremento 
  if (*this == BigUnsigned()) throw std::underflow_error("No se puede decrementar debajo de 0");
  *this = *this - BigUnsigned(1);
  return *this;
}

BigUnsigned BigUnsigned::operator--(int) { // Post-decremento 
  if (*this == BigUnsigned()) throw std::underflow_error("No se puede decrementar debajo de 0");
  BigUnsigned copia = *this;
  *this = *this - BigUnsigned(1);
  return copia;
}

/**
 * @brief Operador de salida para BigUnsigned
 * @param os 
 * @param otro 
 * @return el número por pantalla
 */
std::ostream& operator<<(std::ostream& os, const BigUnsigned& otro) {
	for (size_t i = otro.GetNumerin().size(); i > 0; --i) {
		os << static_cast<unsigned>(otro.GetNumerin().at(i - 1));
	}
	return os;
}

/**
 * @brief Operador de salida
 * @param is 
 * @param num 
 * @return el valor de is
 */
std::istream& operator>>(std::istream& is, BigUnsigned& num) {
  std::string input;
  is >> input;

  std::vector<unsigned char> temp;
  for (int i = input.size() - 1; i >= 0; --i) {
    if (!isdigit(input[i])) {
      throw std::invalid_argument("Entrada no válida: solo se permiten dígitos.");
    }
    temp.push_back(input[i] - '0');
  }

  num.SetNumerin(temp);
  return is;
}

