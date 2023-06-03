/** \file */
/**
 * @file listaPlaylists.cpp
 * @author Erick Marques
 * @brief Funções necessárias para as listas ligadas de playlists.
 * @version 0.1
 */
#include <iostream>
#include "listaPlaylists.h"
#include "utilitarios.h"

using namespace std;

/**< Inicializando head e tail com valores nulos e tamanho 0. */
ListOfPlaylists::ListOfPlaylists() {
  head = nullptr;
  tail = nullptr;
  size = 0;
}
/**< Caso os nós da lista ainda existam na memória, eles são desalocados pela função abaixo. */
ListOfPlaylists::~ListOfPlaylists() {
  if (size != 0) {
    no_* temp = nullptr;
    no_* cur = nullptr;
    cur = head;
    while (cur != nullptr) {
      temp = cur->next;
      delete cur->data;
      delete cur;
      cur = temp;
    }
  }
}
/**< Adquire o tamanho da lista de playlists. */
size_t ListOfPlaylists::getSize() {
  return size;
}
/** 
 * Essa função percorre a lista até a posição passada por parâmetro e obtém o ponteiro da playlist correspondente.
 * @param pos é o índice da posição escolhida (inicia-se em 1).
 * @return o ponteiro para a playlist, caso a posição desejada esteja dentro do tamanho da lista, ou nullptr caso não esteja.
 */
Playlist* ListOfPlaylists::getPlaylist(size_t pos) {
  /** O if abaixo retorna nullptr se a posição não for válida. */
  if (pos < 1 || pos > size) {
    return nullptr;
  } else {
    /** Caso seja válida entretanto, a função retorna o ponteiro para a playlist correspondente. */
    no_* temp = head;
    for (size_t i = 1; i < pos; ++i) {
      temp = temp->next;
    }
    return temp->data;
  }
}
/**
 * Essa função percorre a lista procurando a playlist com o nome passado pelo parâmetro e obtém o ponteiro correspondente.
 * @param searchName é a playlist a ser buscada.
 * @return o ponteiro para a playlist, caso a busca tenha sucesso, ou nullptr caso contrário.
 */
Playlist* ListOfPlaylists::searchPlaylist(string searchName) {
  no_* temp = head;
  while (temp != nullptr) {
    /** Transforma os caracteres do nome da playlist em minúsculos (sem alterar os valores originais) 
      e os compara, em seguida, retorna o ponteiro para o nó correspondete ou nullptr caso não encontre. */
    if ( toLowercase(temp->data->getName()) == toLowercase(searchName) ) {
      return temp->data; 
    }
    temp = temp->next;
  }
  return nullptr;
}
/** 
  * Essa função cria e insere no fim da lista um nó que armazena a playlist passada por argumento
  * @param value é um ponteiro para um objeto do tipo Playlist. 
  */
void ListOfPlaylists::insertPlaylist(Playlist* value) {
  if (searchPlaylist(value->getName()) != nullptr) {
    cout << "Uma playlist com esse nome já existe!" << endl << endl;
  } else {
    no_* temp = new no_;
    temp->data = value;
    temp->next = nullptr;
    if (head == nullptr) {
      head =  temp;
      tail = temp;
      temp = nullptr;
    } else {
      tail->next = temp;
      tail = temp;
    }
    ++size;
    cout << endl << "Playlist criada com sucesso!" << endl;
  }
}

/** 
  * Essa função deleta o nó da posição escolhida e recria o link entre seu antecessor e sucessor.
  * @param pos é o índice da posição escolhida, nesse caso começa por 1.
  */
void ListOfPlaylists::removePlaylist(size_t pos) {
  no_* pre = nullptr;
  no_* cur = nullptr;

  cur = head;
  /** Caso a posição escolhida seja a primeira ou maior que a última esse if e else fazem o devido tratamento. */
  if (pos == 1) {
    head = head->next;
  } else if (pos < size) {
    for (size_t i = 1; i < pos; ++i) {
      pre = cur;
      cur = cur->next;
    }
    pre->next = cur->next;
  } else {
    while (cur->next != nullptr) {
      pre = cur;
      cur = cur->next;
    }
    tail = pre;
    pre->next = nullptr;
  }
  --size; //Reduzindo o tamanho da lista após a operação.
  delete cur->data;
  delete cur;
}

/**
 * Percorre todas as playlists do sistema e elimina de todas a música passada por parâmetro.
 * @param target é um objeto do tipo Song com a música a ser removida.
 */
void ListOfPlaylists::removeFromAll(Song target) {
  no_* temp = head;
  //Loop que percorre todas as playlists armazenadas.
  while (temp != nullptr) {
    LinkedList* songs = temp->data->getSongs(); //Salvando a lista de músicas atual.
    //If que Verifica se a musica está na lista 
    if (songs->search(target) != nullptr) {
      size_t pos = songs->getPosition(target); //Obtém o ID da música.
      songs->removePosition(pos); //elimina a música da lista.
    }
    temp = temp->next;
  }
}
/**
 * @brief Função que exibe todas as playlists na lista ligada.
 */
void ListOfPlaylists::display() {
  no_* temp = head;
  size_t i = 1;
  string nome = "";
  while (temp != nullptr) {
    nome = temp->data->getName();
    cout << i << " - " << nome << endl;
    temp = temp->next;
    ++i;
  }
}