// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzadas
// Curso: 2º
// Práctica 3
// Autor: Diego García Hernández
// Correo: alu0101633732@ull.edu.es
// Fecha: 13/03/2025
// Archivo main.cc
// Descripción: contiene la función main del proyecto

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include "BigInteger.h"
#include "BigNumber.h"
#include "BigRational.h"
#include "BigUnsigned.h"

/**
 * @brief Función para evaluar una operación en notación postfija (RPN)
 * @param board 
 * @param operacion 
 * @return Puntero al objeto BigNumber resultado de la operación
 */
template <unsigned char Base>
BigNumber<Base>* operar(std::map<std::string, BigNumber<Base>*>& board, const std::string& operacion) {
  std::stack<BigNumber<Base>*> pila;
  size_t i = 0;

  while (i < operacion.size()) {
    if (operacion[i] == ' ') {
      i++;
      continue;
    }
    char c = operacion[i];

    // Comprobamos si es un operador
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      if (pila.size() < 2) {
        std::cerr << "Error: Operación con pocos operandos\n";
        return nullptr;
      }
      BigNumber<Base>* num2 = pila.top();
      pila.pop();
      BigNumber<Base>* num1 = pila.top();
      pila.pop();

      BigNumber<Base>* resultado = nullptr;
      switch (c) {
        case '+':
          resultado = &(num1->add(*num2));
          break;
        case '-':
          resultado = &(num1->subtract(*num2));
          break;
        case '*':
          resultado = &(num1->multiply(*num2));
          break;
        case '/':
          resultado = &(num1->divide(*num2));
          break;
      }
      pila.push(resultado);
      i++;
    } else {
      // No es operador: asumimos que es un token (E1 por ejemplo)
      std::string token;
      while (i < operacion.size() && operacion[i] != ' ' &&
             operacion[i] != '+' && operacion[i] != '-' &&
             operacion[i] != '*' && operacion[i] != '/') {
        token.push_back(operacion[i]);
        i++;
      }
      auto it = board.find(token);
      if (it != board.end()) {
        pila.push(it->second);
      } else {
        std::cerr << "Error: token \"" << token << "\" no encontrado.\n";
        return nullptr;
      }
    }
  }

  if (pila.size() != 1) {
    std::cerr << "Error: La operación no se evaluó correctamente.\n";
    return nullptr;
  }
  return pila.top();
}

/**
 * @brief Función para procesar el archivo de entrada y escribir los resultados
 * en el archivo de salida
 * @param entrada Archivo de entrada
 * @param salida Archivo de salida
 */
template <unsigned char Base>
void procesar(std::ifstream& entrada, std::ofstream& salida) {
  std::map<std::string, BigNumber<Base>*> board;
  std::string linea;

  while (std::getline(entrada, linea)) {
    // Se busca el símbolo '=' o '?' en la línea
    size_t posIgual = linea.find('=');
    size_t posInterrogacion = linea.find('?');

    if (posIgual != std::string::npos && posInterrogacion == std::string::npos) {
      std::string nombre = linea.substr(0, posIgual);
      std::string numero = linea.substr(posIgual + 1);

      auto startName = nombre.find_first_not_of(" \t");
      auto endName   = nombre.find_last_not_of(" \t");
      if (startName == std::string::npos) {
        std::cerr << "Error: nombre vacío\n";
        continue;
      }
      nombre = nombre.substr(startName, endName - startName + 1);

      auto startNum = numero.find_first_not_of(" \t");
      auto endNum   = numero.find_last_not_of(" \t");
      if (startNum == std::string::npos) {
        std::cerr << "Error: número vacío\n";
        continue;
      }
      numero = numero.substr(startNum, endNum - startNum + 1);

      BigNumber<Base>* ptr = new BigInteger<Base>(numero.c_str());
      board[nombre] = ptr;
    }

    else if (posInterrogacion != std::string::npos) {
      // Extraemos nombre y operación
      std::string nombre = linea.substr(0, posInterrogacion);
      std::string operacion = linea.substr(posInterrogacion + 1);

      auto startName = nombre.find_first_not_of(" \t");
      auto endName   = nombre.find_last_not_of(" \t");
      if (startName == std::string::npos) {
        std::cerr << "Error: nombre vacío en operación\n";
        continue;
      }
      nombre = nombre.substr(startName, endName - startName + 1);

      auto startOp = operacion.find_first_not_of(" \t");
      auto endOp   = operacion.find_last_not_of(" \t");
      if (startOp == std::string::npos) {
        std::cerr << "Error: operación vacía\n";
        continue;
      }
      operacion = operacion.substr(startOp, endOp - startOp + 1);

      BigNumber<Base>* resultado = operar<Base>(board, operacion);
      if (resultado) {
        board[nombre] = resultado;
      } else {
        std::cerr << "Error al evaluar la operación: " << linea << "\n";
      }
    }
  }

  // Imprimir resultados en el archivo de salida
  salida << "Base = " << static_cast<int>(Base) << '\n';
  for (const auto& par : board) {
    salida << par.first << " = " << *(par.second) << '\n';
  }

}

/**
 * @brief Función principal
 */
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Uso: " << argv[0] << " <archivo_entrada> <archivo_salida>\n";
    return 1;
  }

  std::ifstream archivo_entrada(argv[1]);
  if (!archivo_entrada) {
    std::cerr << "Error al abrir el archivo: " << argv[1]<< "\n";
    return 1;
  }

  std::ofstream salida(argv[2]);
  if (!salida) {
    std::cerr << "Error al abrir el archivo de salida: " << argv[2] << "\n";
    return 1;
  }

  std::string linea;
  unsigned char base = 0;

  // Leemos la primera línea para extraer la base
  if (std::getline(archivo_entrada, linea)) {
    size_t pos = linea.find('=');
    if (pos != std::string::npos) {
      std::string basestring = linea.substr(pos + 1);
      base = static_cast<unsigned char>(std::stoi(basestring));
    } else {
      std::cerr << "Formato incorrecto en la primera línea.\n";
      return 1;
    }
  } else {
    std::cerr << "Archivo vacío.\n";
    return 1;
  }

  // Procesar el resto del archivo según la base leída
  switch (base) {
    case 2:
      procesar<2>(archivo_entrada, salida);
      break;
    case 8:
      procesar<8>(archivo_entrada, salida);
      break;
    case 10:
      procesar<10>(archivo_entrada, salida);
      break;
    case 16:
      procesar<16>(archivo_entrada, salida);
      break;
    default:
      std::cerr << "Base no soportada: " << static_cast<int>(base) << "\n";
      return 1;
  }

  return 0;
}

