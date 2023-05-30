#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "listaLigada.h"
#include "musica.h"
#include <iostream>
using namespace std;


//A classe abaixo representa uma playlist.
class Playlist {
  private:
    string name; //Nome da playlist.
    LinkedList* songs; //Ponteiro para a lista que armazena as músicas.
    no* playing; //Ponteiro para o nó da música que está sendo reproduzida.
    size_t count; //Contador para o método de display.
  public:
    Playlist(); //Construtor da playlist.
    ~Playlist(); //Destrutor da playlist.

    Playlist(const Playlist& old); //Construtor cópia da playlist.

    Playlist operator+ (Playlist& secondPlaylist); //Fusão de playlists.
    Playlist operator+ (Song& toAdd); //Método que copia a playlist e adiciona uma música.
    Playlist operator- (Playlist& secondPlaylist); //Diferença entre duas playlists.
    Playlist operator- (Song& toRemove); //Método que copia a playlist e remove uma música.
    void operator>> (Song*& lastSong); //Método que extrai a última música da playlist.
    void operator<< (Song*& newSong); //Método que adiciona uma música no final da playlist.

    LinkedList* getSongs(); //Adquire o ponteiro da lista de músicas.

    string getName(); //Adquire o nome da playlist.
    void setName(string _name); //Adiciona o nome da playlist.

    void insertSong(size_t pos, Song value); //Adiciona uma música na playlist.
    void removeSong(size_t pos); //Elimina uma música da playlist.
    void moveSong(size_t start, size_t end); //Move a música para outra posição na playlist.

    void insertSong(Playlist& toInsert); //Sobrecarga do método de inserção.
    size_t removeSong(Playlist& toRemove); //Sobrecarga do método de remoção.

    no* playNext(); //Retorna a próxima música a ser reproduzida.

    void displayAllSongs(no* current); //Exibe todas as músicas que compoem a playlist.
    void saveAlltofile(no* current, ofstream& myfile);
    void displayOne(no* current, int pos);
};

#endif