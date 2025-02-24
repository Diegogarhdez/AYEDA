// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 2
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 27/02/2025
// Archivo BigRational.h
// Descripción: contiene la clase BigRational


#ifndef BIGRATIONAL_H_
#define BIGRATIONAL_H_

#include "BigInteger.h"

template<unsigned char Base = 10>
class BigRational {
 public:
  BigRational(const BigInteger<Base>& numerador = 0, const BigUnsigned<Base>& denominador = 1) : numerador_(numerador), denominador_(denominador) { Simplificar(); }
  BigRational(const BigRational<Base>& rational) : numerador_(), denominador_() {
    numerador_ = rational.numerador_;
    denominador_ = rational.denominador_;
    Simplificar();
  }
  BigRational(int n = 0) : numerador_(n), denominador_(1) { }
  BigRational<Base> operator+(const BigRational<Base>&) const;
  BigRational<Base> operator-(const BigRational<Base>&) const;
  BigRational<Base> operator/(const BigRational<Base>&) const;
  BigRational<Base> operator*(const BigRational<Base>&) const;

  BigRational<Base>& operator=(const BigRational<Base>&);
  bool operator==(const BigRational<Base>&) const;
  bool operator<(const BigRational<Base>&) const;

  inline BigInteger<Base> GetNumerador() const { return numerador_; }
  inline BigUnsigned<Base> GetDenominador() const { return denominador_; }
  inline void SetNumerador(const BigInteger<Base>& num) { numerador_ = num; }
  inline void SetDenominador(const BigUnsigned<Base>& den) { denominador_ = den; }
 private:
  BigInteger<Base> numerador_;
  BigUnsigned<Base> denominador_;
  void Simplificar();
};

template<unsigned char Base> std::ostream& operator<<(std::ostream& os, const BigRational<Base>& racional) {
  os << racional.GetNumerador() << " / " << racional.GetDenominador();
  return os;
}

template<unsigned char Base> std::istream& operator>>(std::istream& is, const BigRational<Base>& racional) {
  BigInteger<Base> num;
  BigUnsigned<Base> den;
  is >> num >> den;
  racional.SetNumerador(num);
  racional.SetDenominador(den);
  racional.Simplificar();
  return is;
}

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& rational) const {
  if (denominador_ == rational.GetDenominador()) return BigRational<Base>(numerador_ + rational.GetNumerador(), denominador_);
  else return BigRational<Base>((numerador_ * rational.GetDenominador()) + (rational.GetNumerador() * denominador_), denominador_ * rational.GetDenominador());
}

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& rational) const {
  if (denominador_ == rational.GetDenominador()) return BigRational<Base>(numerador_ - rational.GetNumerador(), denominador_);
  else return BigRational<Base>((numerador_ * rational.GetDenominador()) - (rational.GetNumerador() * denominador_), denominador_ * rational.GetDenominador());
}

template<unsigned char Base> BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& rational) const {
  return BigRational<Base>(numerador_ * rational.GetNumerador(), denominador_ * rational.GetDenominador());
}

template <unsigned char Base> BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& rational) const {
  BigInteger<Base> nuevoDenominador = static_cast<BigInteger<Base>>(denominador_);
  BigInteger<Base> otroDenominador = static_cast<BigInteger<Base>>(rational.GetDenominador());

  return BigRational<Base>(numerador_ * otroDenominador, nuevoDenominador.GetNumero() * rational.GetNumerador().GetNumero());
}

template<unsigned char Base> BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& rational) {
  numerador_ = rational.GetNumerador();
  denominador_ = rational.GetDenominador();
  return *this;
}

template<unsigned char Base> bool BigRational<Base>::operator==(const BigRational<Base>& rational) const {
  if ((numerador_ == rational.GetNumerador()) && (denominador_ == rational.GetDenominador())) return true;
  else return false;
}

template<unsigned char Base> bool BigRational<Base>::operator<(const BigRational<Base>& rational) const {
  if ((numerador_ * rational.GetDenominador()) < (rational.GetNumerador() * denominador_)) return true;
  else return false;
}

template<unsigned char Base> void BigRational<Base>::Simplificar() {
  if (mcd(numerador_, BigInteger<Base>(denominador_)) == BigInteger<Base>(1)) return;
  BigInteger<Base> aux = mcd(numerador_, BigInteger<Base>(denominador_));
  numerador_ = numerador_ / aux;
  denominador_ = denominador_ / aux.GetNumero();
}

#endif