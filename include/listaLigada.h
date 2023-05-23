#ifndef LISTALIGADA_H
#define LISTALIGADA_H

#include "musica.h"
#include <iostream>
//O struct abaixo representa um nó da lista ligada.
struct no {
  Song data; //Armazena um objeto do tipo música.
  no* next; //Ponteiro para o próximo nó.
};
//A classe abaixo representa uma lista ligada.
class LinkedList {
  private:
    no* head; //Ponteiro para o inicio da lista.
    no* tail; //Ponteiro para o final da lista.z
    size_t size; //Tamanho da lista.
  public:
    LinkedList(); //Construtor da lista ligada.
    ~LinkedList(); //Destrutor da lista ligada.

    LinkedList(const LinkedList& oldList); //Construtor cópia da lista ligada. 

    LinkedList operator+ (const LinkedList& secondList); //Concatenação de listas.

    void operator>> (no*& lastno); //Extrai o último elemento da lista.
    void operator<< (no*& newno); //Insere um nó no fim da lista.

    no* getHead(); //Obtém o ponteiro do head.
    no* getTail(); //Obtém o ponteiro do tail.
    size_t getSize(); //Obtém o tamanho da lista.

    void insertStart(Song value); //Insere um nó no início.
    int insertEnd(Song value); //Insere um nó no fim.
    void insertPosition(size_t pos, Song value); //Insere um nó na posição específica.
    
    void insertEnd(LinkedList& toInsert); //Sobrecarga do método de inserção.

    void removeFirst(); //Elimina o primeiro nó.
    void removeLast(); //Elimina o último nó.
    void removePosition(size_t pos); //Elimina o nó na posição específica.

    void removePosition(LinkedList& toRemove); //Sobrecarga do método de remoção.

    no* search(Song searchSong); //Procura um nó usando os atributos da música.
    no* getno(size_t pos); //Retorna um nó com base na posição.
    size_t getPosition(Song searchSong); //Retorna a posição de uma música na lista.

    void display(); //Exibe o conteúdo dos nós da lista.
};
#endif