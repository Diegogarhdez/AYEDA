// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estrucutras de Datos Avanzadas
// Curso: 2º
// Práctica 3
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/03/2025
// Archivo BigNumber.h
// Descripción: contiene la clase BigNumber


#ifndef BIGNUMBER_H_
#define BIGNUMBER_H_

#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>  


class BigNumberException : public std::exception {
 public:
  virtual const char* what() const noexcept override {
    return "Error en BigNumber";
  }
};

class BigNumberBadDigit : public BigNumberException {
 public:
  const char* what() const noexcept override {
    return "Error: Dígito no válido en la representación del número";
  }
};

class BigNumberDivisionByZero : public BigNumberException {
 public:
  const char* what() const noexcept override {
    return "Error: División por cero";
  }
};


template<unsigned char Base> class BigInteger;
template<unsigned char Base> class BigUnsigned;
template<unsigned char Base> class BigRational;


template<unsigned char Base = 10>
class BigNumber {
 public:
  // Métodos virtuales puros para operaciones básicas
  virtual BigNumber<Base>& add(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& subtract(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& multiply(const BigNumber<Base>&) const = 0;
  virtual BigNumber<Base>& divide(const BigNumber<Base>&) const = 0;
 
  // Conversiones virtuales a otros tipos
  virtual operator BigUnsigned<Base>() const = 0;
  virtual operator BigInteger<Base>()  const = 0;
  virtual operator BigRational<Base>() const = 0;

  // Entrada/salida virtual
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;

  static BigNumber<Base>* create(const char* input) {
    
    std::string cadena = input;
    try {
    if (cadena.ends_with("u")) {
      cadena.pop_back(); // Quitamos la 'u'
      return new BigUnsigned<Base>(reinterpret_cast<const unsigned char*>(cadena.c_str()));
    }
    if (cadena.ends_with("i")) {
      cadena.pop_back(); // Quitamos la 'i'
      return new BigInteger<Base>(cadena.c_str());
    }
    if (cadena.ends_with("r")) {
      cadena.pop_back(); // Quitamos la 'r'
      return new BigRational<Base>(cadena.c_str());
    }


    } catch (const BigNumberBadDigit& e) {
      std::cout << e.what() << "\n";
    }
  }

  virtual ~BigNumber() {}
};

// Sobrecarga de operador<<
template<unsigned char Base> 
std::ostream& operator<<(std::ostream& os, const BigNumber<Base>& numero) {
  return numero.write(os);
}

// Sobrecarga de operador>>
template<unsigned char Base> 
std::istream& operator>>(std::istream& is, BigNumber<Base>& numero) {
  return numero.read(is);
}


#endif // BIGNUMBER_H_
