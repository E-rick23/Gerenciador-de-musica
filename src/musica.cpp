/** \file */
/**
 * @file musica.cpp
 * @author Erick Marques
 * @brief Funções que definem e exibem informações das músicas.
 * @version 0.1
 */
#include "musica.h"

using namespace std;

/**
 * @brief Constrói um novo Song:: Song object
 * 
 */
Song::Song() {
}
/**
 * @brief Destroy um Song:: Song object
 * 
 */
Song::~Song() {
}
/**
 * @brief Get que retorna o título de um "Song".
 * 
 * @return string título da música.
 */
string Song::getTitle() {
  return title;
}
/**
 * @brief Get que retorna o artísta de um "Song".
 * 
 * @return string Artista da música.
 */
string Song::getArtist() {
  return artist;
}
/**
 * @brief  Set que define o título de um "Song". 
 * 
 * @param _title 
 */
void Song::setTitle(string _title) {
  title = _title;
}
/**
 * @brief Set que define o artista de um "Song". 
 * 
 * @param _artist 
 */
void Song::setArtist(string _artist) {
  artist = _artist;
}
