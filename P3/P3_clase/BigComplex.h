// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 1
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/02/2025
// Archivo BigComplex.h
// Descripción: contiene la definición de la clase BigComplex


#ifndef BIGCOMPLEX_H_
#define BIGCOMPLEX_H_

#include <iostream>

#include "BigNumber.h"

template<unsigned char Base> class BigUnsigned;
template<unsigned char Base> class BigNumber;
template<unsigned char Base> class BigRational;
template<unsigned char Base> class BigInteger;

//clase BigComplex
template<unsigned char Base = 10> class BigComplex : public BigNumber<Base> {
 public:
  BigComplex(const BigInteger<Base>&, const BigInteger<Base>&);
  BigComplex() : parte_real_(), parte_imaginaria_() { }
  BigComplex<Base> operator+(const BigComplex<Base>&);
  inline BigInteger<Base> GetReal() const { return parte_real_; }
  inline BigInteger<Base> GetImaginario() const { return parte_imaginaria_;}
  inline void SetReal(const BigInteger<Base>& real) { parte_real_ = real; }
  inline void SetImaginario(const BigInteger<Base>& imaginario) { parte_imaginaria_ = imaginario;}

  operator BigUnsigned<Base>() const override {
    return BigUnsigned<Base>(parte_real_.GetNumero());
  }
  operator BigInteger<Base>() const override {
    return parte_real_;
  }
  operator BigRational<Base>() const override {
    return BigRational<Base>(parte_real_);
  }
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wclass-conversion"
  operator BigComplex<Base>() const override {
    return *this;
  }
  #pragma GCC diagnostic pop

  std::ostream& write(std::ostream& os) const override {
    os << *this;
    return os;
  }
  std::istream& read(std::istream& is) override {
    return is;
  } 


  BigNumber<Base>& add(const BigNumber<Base>& numero) const override {
    const BigComplex<Base>& aux = dynamic_cast<const BigComplex<Base>&>(numero);
    return *(new BigComplex<Base>(*this + aux));
  }
  BigNumber<Base>& subtract(const BigNumber<Base>&) const override {

  }
  BigNumber<Base>& multiply(const BigNumber<Base>&) const override {

  }
  BigNumber<Base>& divide(const BigNumber<Base>&) const override {

  }

 private:
  BigInteger<Base> parte_real_;
  BigInteger<Base> parte_imaginaria_;
};

template<unsigned char Base> std::ostream& operator<<(std::ostream& os, const BigComplex<Base>& complex) {
  os << complex.GetReal();
  if (complex.GetImaginario().GetSigno() == false) os << " + ";
  os << complex.GetImaginario() << "i";
  return os;
}

template<unsigned char Base> BigComplex<Base> BigComplex<Base>::operator+(const BigComplex<Base>& complex) {
  return BigComplex<Base>(complex.GetReal() + parte_real_, complex.GetImaginario() + parte_imaginaria_);
}

template<unsigned char Base> BigComplex<Base>::BigComplex(const BigInteger<Base>& real, const BigInteger<Base>& imaginario) : parte_real_(real), parte_imaginaria_(imaginario) { }



#endif