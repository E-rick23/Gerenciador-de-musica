#ifndef LISTOFPLAYLISTS_H
#define LISTOFPLAYLISTS_H

#include "playlist.h"
#include <iostream>

//O struct abaixo representa um nó da lista ligada.
struct no_ {
  Playlist* data; //Armazena um objeto do tipo ponteiro de playlist.
  no_* next; //Ponteiro para o próximo nó.
};

//A classe abaixo representa uma lista ligada de playlists
class ListOfPlaylists {
  private:
    no_* head; //Ponteiro para o primeiro nó.
    no_* tail; //Ponteiro para o último nó.
    size_t size; //Tamanho da lista.
  public:
    ListOfPlaylists(); //Construtor da lista ligada.
    ~ListOfPlaylists(); //Destrutor da lista ligada.

    size_t getSize(); //Adquire o tamanho da lista.

    Playlist* getPlaylist(size_t pos); //Retorna o ponteiro para a playlist usando a posição na lista.
    Playlist* searchPlaylist(std::string searchName); //Retorna o ponteiro para a playlist usando o nome da playlist.

    void insertPlaylist(Playlist* value); //Insere um nó da playlist no fim da lista.
    void removePlaylist(size_t pos); //Elimina o nó da playlist de uma posição específica.
    void removeFromAll(Song target); //Elimina uma música de todas as playlists de uma vez.
    void display(); //Exibe o conteúdo de todos os nós da lista. 

};


#endif