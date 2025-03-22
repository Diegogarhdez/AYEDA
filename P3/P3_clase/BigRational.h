// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 3
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/03/2025
// Archivo BigRational.h
// Descripción: contiene la clase BigRational


#ifndef BIGRATIONAL_H_
#define BIGRATIONAL_H_

#include "BigNumber.h"
#include "BigUnsigned.h"
#include "BigInteger.h"

template<unsigned char Base> class BigInteger;
template<unsigned char Base> class BigNumber;
template<unsigned char Base> class BigUnsigned;
template<unsigned char Base> class BigComplex;


template<unsigned char Base = 10>
class BigRational : public BigNumber<Base> {
 public:
  BigRational(const BigInteger<Base>& numerador = 0,
              const BigUnsigned<Base>& denominador = 1)
    : numerador_(numerador),
      denominador_(denominador) {
    Simplificar();
  }

  BigRational(const BigRational<Base>& rational)
    : numerador_(rational.numerador_),
      denominador_(rational.denominador_) {
    Simplificar();
  }

  BigRational(const char* cadena) : numerador_(), denominador_() {
    std::string num(cadena);
    size_t pos = num.find('/');
    if (pos == std::string::npos) {
      // No hay '/', se asume que es un entero
      numerador_   = BigInteger<Base>(num.c_str());
      denominador_ = BigUnsigned<Base>(1);
    } else {
      // Extraer numerador y denominador
      std::string sNum = num.substr(0, pos);
      std::string sDen = num.substr(pos + 1);
      if (sDen == "0") {
        throw BigNumberDivisionByZero();
      }
      numerador_   = BigInteger<Base>(sNum.c_str());
      denominador_ = BigUnsigned<Base>(sDen.c_str());
    }
    Simplificar();
  }

  BigRational(int n) : numerador_(n), denominador_(1) { }

  // Operadores
  BigRational<Base> operator+(const BigRational<Base>&) const;
  BigRational<Base> operator-(const BigRational<Base>&) const;
  BigRational<Base> operator*(const BigRational<Base>&) const;
  BigRational<Base> operator/(const BigRational<Base>&) const;

  BigRational<Base>& operator=(const BigRational<Base>&);
  bool operator==(const BigRational<Base>&) const;
  bool operator<(const BigRational<Base>&) const;

  // Getters / Setters
  inline BigInteger<Base>    GetNumerador()   const { return numerador_; }
  inline BigUnsigned<Base>   GetDenominador() const { return denominador_; }
  inline void SetNumerador(const BigInteger<Base>& num)   { numerador_ = num; }
  inline void SetDenominador(const BigUnsigned<Base>& den){ denominador_ = den; }

  // Métodos virtuales
  BigNumber<Base>& add(const BigNumber<Base>& other) const override {
    const BigRational<Base>& aux = dynamic_cast<const BigRational<Base>&>(other);
    return *(new BigRational<Base>(*this + aux));
  }
  BigNumber<Base>& subtract(const BigNumber<Base>& other) const override {
    const BigRational<Base>& aux = dynamic_cast<const BigRational<Base>&>(other);
    return *(new BigRational<Base>(*this - aux));
  }
  BigNumber<Base>& multiply(const BigNumber<Base>& other) const override {
    const BigRational<Base>& aux = dynamic_cast<const BigRational<Base>&>(other);
    return *(new BigRational<Base>(*this * aux));
  }
  BigNumber<Base>& divide(const BigNumber<Base>& other) const override {
    const BigRational<Base>& aux = dynamic_cast<const BigRational<Base>&>(other);
    if (aux.GetNumerador() == BigInteger<Base>(0)) {
      throw BigNumberDivisionByZero();
    }
    return *(new BigRational<Base>(*this / aux));
  }

  // Conversiones
  operator BigUnsigned<Base>() const override {
    // Si numerador es negativo, esto no tiene sentido; en todo caso, se tomaría el valor absoluto
    if (numerador_ < BigInteger<Base>(0)) {
      throw BigNumberBadDigit(); // O la excepción que corresponda
    }
    // "Parte entera" de la división
    BigInteger<Base> division = numerador_ / BigInteger<Base>(denominador_);
    return division.GetNumero(); // El BigUnsigned interno
  }

  operator BigInteger<Base>() const override {
    // Simplemente numerador_ / denominador_, truncando decimales
    return numerador_ / BigInteger<Base>(denominador_);
  }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wclass-conversion"
  operator BigRational<Base>() const override { return *this; }
#pragma GCC diagnostic pop

  operator BigComplex<Base>() const override { return BigComplex<Base>(numerador_); }

  // E/S
  std::ostream& write(std::ostream& os) const override {
    return os << *this << "r";
  }
  std::istream& read(std::istream& is) override {
    return is >> *this;
  }

  // Simplifica el número racional
  void Simplificar();

 private:
  BigInteger<Base>    numerador_;
  BigUnsigned<Base>   denominador_;
};

// Sobrecarga de operador<<
template<unsigned char Base>
std::ostream& operator<<(std::ostream& os, const BigRational<Base>& racional) {
  os << racional.GetNumerador() << "/" << racional.GetDenominador();
  return os;
}

// Sobrecarga de operador>>
template<unsigned char Base>
std::istream& operator>>(std::istream& is, BigRational<Base>& racional) {
  // Se espera leer algo del estilo "12/7" o "12"
  std::string input;
  is >> input;
  size_t pos = input.find('/');
  if (pos == std::string::npos) {
    racional.SetNumerador(BigInteger<Base>(input.c_str()));
    racional.SetDenominador(BigUnsigned<Base>(1));
  } else {
    std::string sNum = input.substr(0, pos);
    std::string sDen = input.substr(pos + 1);
    if (sDen == "0") {
      throw BigNumberDivisionByZero();
    }
    racional.SetNumerador(BigInteger<Base>(sNum.c_str()));
    racional.SetDenominador(BigUnsigned<Base>(sDen.c_str()));
  }
  racional.Simplificar();
  return is;
}

// Operadores de la clase

template<unsigned char Base>
BigRational<Base> BigRational<Base>::operator+(const BigRational<Base>& r) const {
  // a/b + c/d = (ad + cb) / bd
  BigInteger<Base>   a = numerador_;
  BigUnsigned<Base>  b = denominador_;
  BigInteger<Base>   c = r.numerador_;
  BigUnsigned<Base>  d = r.denominador_;

  BigInteger<Base>   ad = a * BigInteger<Base>(d);
  BigInteger<Base>   cb = c * BigInteger<Base>(b);
  BigInteger<Base>   sum = ad + cb;
  BigUnsigned<Base>  bd  = b * d;

  return BigRational<Base>(sum, bd);
}

template<unsigned char Base>
BigRational<Base> BigRational<Base>::operator-(const BigRational<Base>& r) const {
  // a/b - c/d = (ad - cb) / bd
  BigInteger<Base>   a = numerador_;
  BigUnsigned<Base>  b = denominador_;
  BigInteger<Base>   c = r.numerador_;
  BigUnsigned<Base>  d = r.denominador_;

  BigInteger<Base>   ad = a * BigInteger<Base>(d);
  BigInteger<Base>   cb = c * BigInteger<Base>(b);
  BigInteger<Base>   dif = ad - cb;
  BigUnsigned<Base>  bd  = b * d;

  return BigRational<Base>(dif, bd);
}

template<unsigned char Base>
BigRational<Base> BigRational<Base>::operator*(const BigRational<Base>& r) const {
  // a/b * c/d = (ac) / (bd)
  BigInteger<Base>   a  = numerador_;
  BigUnsigned<Base>  b  = denominador_;
  BigInteger<Base>   c  = r.numerador_;
  BigUnsigned<Base>  d  = r.denominador_;

  BigInteger<Base>  ac = a * c;
  BigUnsigned<Base> bd = b * d;

  return BigRational<Base>(ac, bd);
}

template<unsigned char Base>
BigRational<Base> BigRational<Base>::operator/(const BigRational<Base>& r) const {
  // (a/b) / (c/d) = (a/b) * (d/c) = (ad) / (bc)
  // c = 0 => error
  if (r.numerador_ == BigInteger<Base>(0)) {
    throw BigNumberDivisionByZero();
  }
  BigInteger<Base> a = numerador_;
  BigUnsigned<Base> b = denominador_;
  BigInteger<Base> c = r.numerador_;
  BigUnsigned<Base> d = r.denominador_;

  // Para dividir por c, en BigRational necesitamos multiplicar numerador por d
  // y denominador por c (en valor absoluto).
  // Ojo a posible signo.
  BigInteger<Base>   ad = a * BigInteger<Base>(d);
  // b es BigUnsigned, c si es negativo (BigInteger), se hereda el signo en multiplicación
  // El denominador final en BigRational debe ser positivo, así que
  // podemos tomar el valor absoluto de c para el denominador y propagar el signo a ad.
  c.SetSigno(false);
  
  BigUnsigned<Base> bc = b * c.GetNumero();

  // Si c era negativo, eso cambia el signo del numerador.
  if (c < BigInteger<Base>('0')) {
    ad.SetSigno(false);
  }

  return BigRational<Base>(ad, bc);
}

// Operadores de asignación y comparación

template<unsigned char Base>
BigRational<Base>& BigRational<Base>::operator=(const BigRational<Base>& r) {
  numerador_   = r.numerador_;
  denominador_ = r.denominador_;
  return *this;
}

template<unsigned char Base>
bool BigRational<Base>::operator==(const BigRational<Base>& r) const {
  return (numerador_ == r.numerador_) && (denominador_ == r.denominador_);
}

template<unsigned char Base>
bool BigRational<Base>::operator<(const BigRational<Base>& r) const {
  // a/b < c/d <=> a*d < c*b (suponiendo b,d > 0)
  // Para BigInteger podemos hacer directly: a*d < c*b
  BigInteger<Base> left  = numerador_ * BigInteger<Base>(r.denominador_);
  BigInteger<Base> right = r.numerador_ * BigInteger<Base>(denominador_);
  return left < right;
}

// Simplificar fracción
template<unsigned char Base>
void BigRational<Base>::Simplificar() {
  // MCD del valor absoluto del numerador y del denominador
  if (denominador_ == BigUnsigned<Base>('0')) throw BigNumberDivisionByZero();
  BigInteger<Base> abs_den(denominador_);
  BigInteger<Base> aux = numerador_;
  aux.SetSigno(false);
  BigInteger<Base> gcd = mcd(aux, abs_den);

  if (gcd == BigInteger<Base>(0)) {
    numerador_   = 0;
    denominador_ = 1;
    return;
  }

  // Dividimos numerador y denominador entre gcd
  numerador_   = numerador_ / gcd;
  denominador_ = denominador_ / gcd.GetNumero();
}

#endif // BIGRATIONAL_H_

