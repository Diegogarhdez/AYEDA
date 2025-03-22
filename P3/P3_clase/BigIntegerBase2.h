// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 3
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/03/2025
// Archivo BigIntegerBase2.h
// Descripción: contiene la clase BigInteger para la base 2

#ifndef BIGINTEGERBASE2_H_
#define BIGINTEGERBASE2_H_

#include "BigInteger.h"
#include "BigNumber.h"

template <> class BigInteger<2> {
 public:
  BigInteger(int n = 0) {
    bool isNegative = (n < 0);
    numero_ = intToBinary(std::abs(n));
    while (numero_.size() < 8) {
      numero_.insert(numero_.begin(), false);
    }
    if (isNegative) {
      ComplA2(); 
    }
  }

  BigInteger(const std::vector<bool>& numeron) : numero_(numeron) {}
  BigInteger(const BigInteger<2>& otro) : numero_(otro.numero_) {}

  BigInteger<2> operator+(const BigInteger<2>&) const;
  BigInteger<2> operator-(const BigInteger<2>&) const;
  BigInteger<2> operator/(const BigInteger<2>&) const;
  BigInteger<2> operator*(const BigInteger<2>&) const;
  BigInteger<2> operator%(const BigInteger<2>&) const;

  BigInteger<2>& operator++();    // Pre-incremento
  BigInteger<2> operator++(int);  // Post-incremento
  BigInteger<2>& operator--();    // Pre-decremento
  BigInteger<2> operator--(int);  // Post-decremento

  BigInteger<2>& operator=(const BigInteger<2>&);
  bool operator==(const BigInteger<2>&) const;
  bool operator<(const BigInteger<2>&) const;

  inline std::vector<bool> GetNumero() const { return numero_; }
  inline void SetNumero(const std::vector<bool>& otro) { numero_ = otro; }

  void ComplA2();

 private:
  std::vector<bool> numero_;  // Último bit indica el signo

  static std::vector<bool> intToBinary(int n) {
    std::vector<bool> bits;
    if (n == 0) return {false};
    while (n > 0) {
      bits.push_back(n % 2);
      n /= 2;
    }
    std::reverse(bits.begin(), bits.end());
    return bits;
  }
};

void BigInteger<2>::ComplA2() {
  if (numero_.empty()) return;  // Evita acceso a vector vacío
  bool carry = true;
  for (int i = numero_.size() - 1; i >= 0; --i) {
    numero_[i] = !numero_[i];
    if (carry) {
      carry = numero_[i];
      numero_[i] = !numero_[i];
    }
  }
}


BigInteger<2> BigInteger<2>::operator+(const BigInteger<2>& other) const {
  std::vector<bool> a = numero_;
  std::vector<bool> b = other.numero_;

  int size = std::max(a.size(), b.size());
  a.insert(a.begin(), size - a.size(), false);
  b.insert(b.begin(), size - b.size(), false);

  bool carry = false;
  std::vector<bool> result(size + 1, false);

  for (int i = size - 1; i >= 0; --i) {
    bool sum = a[i] ^ b[i] ^ carry;
    carry = (a[i] & b[i]) | (carry & (a[i] ^ b[i]));
    result[i + 1] = sum;
  }
  result[0] = carry;

  if (carry) result.insert(result.begin(), true);

  return BigInteger<2>(result);
}

BigInteger<2> BigInteger<2>::operator-(const BigInteger<2>& other) const {
  BigInteger<2> negOther = other;
  negOther.ComplA2();
  return *this + negOther;
}

BigInteger<2> BigInteger<2>::operator*(const BigInteger<2>& other) const {
  BigInteger<2> result(0);
  BigInteger<2> multiplicando = *this;

  for (size_t i = 0; i < other.numero_.size() - 1; ++i) {
    if (other.numero_[i]) {
      result = result + multiplicando;
    }
    multiplicando.numero_.insert(multiplicando.numero_.begin(), false);
  }
  return result;
}

BigInteger<2> BigInteger<2>::operator/(const BigInteger<2>& other) const {
  BigInteger<2> dividend = *this;
  BigInteger<2> divisor = other;
  BigInteger<2> quotient(0);
  BigInteger<2> one(1);

  if (divisor == BigInteger<2>(0)) throw std::domain_error("División por cero");
  
  while (!(dividend < divisor)) {
    dividend = dividend - divisor;
    quotient = quotient + one;
  }
  return quotient;
}

BigInteger<2> BigInteger<2>::operator%(const BigInteger<2>& other) const {
  BigInteger<2> dividend = *this;
  BigInteger<2> divisor = other;

  while (!(dividend < divisor)) {
    dividend = dividend - divisor;
  }
  return dividend;
}

BigInteger<2>& BigInteger<2>::operator++() {
  *this = *this + BigInteger<2>(1);
  return *this;
}

BigInteger<2> BigInteger<2>::operator++(int) {
  BigInteger<2> temp = *this;
  ++(*this);
  return temp;
}

BigInteger<2>& BigInteger<2>::operator--() {
  *this = *this - BigInteger<2>(1);
  return *this;
}

BigInteger<2> BigInteger<2>::operator--(int) {
  BigInteger<2> temp = *this;
  --(*this);
  return temp;
}

BigInteger<2>& BigInteger<2>::operator=(const BigInteger<2>& otro) {
  if (this != &otro) {
    numero_ = otro.numero_;
  }
  return *this;
}

bool BigInteger<2>::operator==(const BigInteger<2>& otro) const {
  return numero_ == otro.numero_;
}

bool BigInteger<2>::operator<(const BigInteger<2>& otro) const {
  return numero_ < otro.numero_;
}

std::ostream& operator<<(std::ostream& os, const BigInteger<2>& entero) {
  for (bool bit : entero.GetNumero()) os << bit;
  return os;
}

std::istream& operator>>(std::istream& is, BigInteger<2>& entero) {
  std::string input;
  is >> input;

  std::vector<bool> numero;
  for (char c : input) {
    if (c == '0') numero.push_back(false);
    else if (c == '1') numero.push_back(true);
    else throw std::invalid_argument("Entrada no válida para BigInteger<2>");
  }
  entero = BigInteger<2>(numero);
  return is;
}

BigInteger<2> mcd(const BigInteger<2>& numero1, const BigInteger<2>& numero2) {
  if (numero2.GetNumero() == BigInteger<2>(1)) return numero1;
  return mcd(numero2, numero1 % numero2);
}

#endif