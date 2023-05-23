#ifndef MUSICA_H
#define MUSICA_H

#include <iostream>
using namespace std;
 
//A classe abaixo representa uma musica armazenada.
class Song {
  private:
    string title;  //Título da música.
    string artist; //Artista da música.
  public:
    Song(); //Construtor da música.
    ~Song(); //Destrutor da música.  

    string getTitle(); //Adquire o título da música.
    void setTitle(string _title); //Adiciona o título da música.

    string getArtist(); //Adquire o artista da música.
    void setArtist(string _artist); //Adiciona o artista da música.
};


#endif