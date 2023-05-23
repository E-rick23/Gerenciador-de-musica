/** \file */
/**
 * @file utilitarios.cpp
 * @author Erick Marques
 * @brief Função que transforma caracteres maiúsculos em minúsculos.
 * @version 0.1
 */
#include <iostream>
#include <cctype>
#include "utilitarios.h"
using namespace std;

/** 
 * Essa função recebe uma string, e percorre-a transformando todos os caractéres em minúsculos.
 * @param s é a string a ser transformada.
 * @return o resultado da conversão.
 */
string toLowercase(string s) {
  string result = "";
  for (size_t i = 0; i < s.size(); i++) {
    result += tolower(s[i]);
  }
  return result;
}

/**
 * Essa função recebe uma string e verifica se há um inteiro em seu conteúdo.
 * @param s a string a ser verificada
 * @return s se houver um inteiro ou aux se não.
 */
string checkInt(string s){
  string aux = "-1";
  if (isdigit(s[0]) == true) {
    return s;
  } else {
    return aux;
  }
}