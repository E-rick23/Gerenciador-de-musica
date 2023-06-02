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
#include "musica.h"
#include "listaLigada.h"
#include "playlist.h"
#include "listaPlaylists.h"

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

/**
 * Função que testa os métodos sobrecarregados.
 */
void testeSobrecarga(){
  LinkedList* testList = new LinkedList;
  Song tempSong;
  LinkedList* lista1 = new LinkedList; //Criando uma lista ligada...
        // Inserindo músicas previamente a uma lista...
       
        // Adicionando primeira música
        tempSong.setTitle("Shelter");
        tempSong.setArtist("Porter Robinson");
        lista1->insertEnd(tempSong);
        // Adicionando segunda música
        tempSong.setTitle("Never Gonna Give You Up");
        tempSong.setArtist("Rick Astley");
        lista1->insertEnd(tempSong);
        //Imprimindo a lista...
        cout << "Lista 1:" << endl;
        lista1->display();
        cout << endl << "________________________________________" << endl << endl;
        
        // Cria uma segunda lista utilizando o construtor cópia.
        LinkedList* lista2 = new LinkedList(*lista1);

        // Adiciona mais músicas a segunda lista
        tempSong.setTitle("Live and Learn");
        tempSong.setArtist("Crush 40");
        lista2->insertEnd(tempSong);

        tempSong.setTitle("Bone Dry");
        tempSong.setArtist("Tristan");
        lista2->insertEnd(tempSong);

        tempSong.setTitle("Lua de Cristal");
        tempSong.setArtist("Xuxa Meneghel");
        lista2->insertEnd(tempSong);

        cout << "Lista 2 criada a partir da lista 1 com mais músicas:" << endl;
        lista2->display();
        cout << endl << "________________________________________" << endl << endl;
        
        lista2->removePosition(*lista1); //Removendo da lista 2 as músicas da lista 1 por meio de sobrecarga...

        cout << "Lista 2 sem os elementos da lista 1:" << endl;
        lista2->display();

        //Inserindo as músicas dessa lista à lista global por meio de sobrecarga...
        testList->insertEnd(*lista2);
        cout << endl << "________________________________________" << endl << endl;

        // Criando uma nova lista a partir da concatenação das duas listas já existentes...
        LinkedList* lista3 = new LinkedList(*lista1 + *lista2);
        cout << "Lista 3 criada usando a lista 1 + lista 2: " << endl;
        lista3->display();
        cout << endl << "________________________________________" << endl << endl;

        // Extraindo o ultimo nó da lista 3...
        no* temp = new no;
        *lista3 >> temp;

        cout << "Lista 3 pós-extração:" << endl;
        lista3->display();
        cout << endl << "Música extraída: ";
        cout << temp->data.getTitle() << " - " << temp->data.getArtist() << endl;
        cout << endl << "________________________________________" << endl << endl;

        // Retornando o nó  final da lista 3...
        *lista3 << temp;
        cout << "Lista 3 após inserção:" << endl;
        lista3->display();
        cout << endl << "________________________________________" << endl << endl;

        // Inserindo músicas previamente a uma playlist
        Playlist* p1 = new Playlist;
        p1->setName("Playlist 1");

        tempSong.setTitle("Never Gonna Give You Up");
        tempSong.setArtist("Rick Astley");
        p1->insertSong(1, tempSong);

        tempSong.setTitle("Shelter");
        tempSong.setArtist("Porter Robinson");
        p1->insertSong(2, tempSong);

        cout << p1->getName() << ":" << endl;
        p1->displayAllSongs(p1->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;
        // Inserindo músicas em uma segunda playlist...
        Playlist* p2 =  new Playlist;
        p2->setName("Playlist 2");

        tempSong.setTitle("Running in the 90s");
        tempSong.setArtist("Max Coveri");
        p2->insertSong(1, tempSong);

        tempSong.setTitle("It's My Life");
        tempSong.setArtist("No Doubt");
        p2->insertSong(2, tempSong);

        cout << p2->getName() << ":" << endl;
        p2->displayAllSongs(p2->getSongs()->getHead());
        cout << endl;
        // Inserindo músicas de p1 em p2 usando sobrecarga...
        p2->insertSong(*p1);
        cout << p2->getName() << " com as músicas da playlist 1:" << endl;
        p2->displayAllSongs(p2->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Removendo de p2 as músicas de p1 usando sobrecarga...
        size_t count = p2->removeSong(*p1);
        cout << p2->getName() << " sem as " << count << " músicas da playlist 1:" << endl;
        p2->displayAllSongs(p2->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Criando uma playlist p3 identica a p1 utilizando o construtor cópia...
        Playlist* p3 = new Playlist(*p1);
        p3->setName("Playlist 3");
        cout << p3->getName() << " cópia de playlist 1:" << endl;
        p3->displayAllSongs(p3->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Adicionando mais músicas a p1...
        tempSong.setTitle("Love Sux");
        tempSong.setArtist("Avril Lavigne");
        p1->insertSong(3, tempSong);

        tempSong.setTitle("Why do I");
        tempSong.setArtist("Set it Off");
        p1->insertSong(4, tempSong);

        cout << p1->getName() << " com mais músicas:" << endl;
        p1->displayAllSongs(p1->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Criando uma playlist 4 resultante da união da playlist 1 e playlist 2...
        Playlist* p4 = new Playlist(*p1 + *p2);
        p4->setName("Playlist 4");
        cout << p4->getName() << " criada a partir da playlist 1 em união com a playlist 2:" << endl;
        p4->displayAllSongs(p4->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;
        
        // Criando uma playlist p5 usando a playlist 4 e o "tempSong"...
        tempSong.setTitle("Fooled Again");
        tempSong.setArtist("Lonely Bunker");
        Playlist* p5 = new Playlist(*p4 + tempSong);
        p5->setName("Playlist 5");
        cout << p5->getName() << " criada a partir da playlist 4 + uma nova música:" << endl;
        p5->displayAllSongs(p5->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Criando a playlist 6 baseando se na playlist 5 menos as músicas da playlist 3...
        Playlist* p6 = new Playlist(*p5 - *p3);
        p6->setName("Playlist 6");
        cout << p6->getName() << " criada da playlist 5 - playlist 3:" << endl;
        p6->displayAllSongs(p6->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Criando a playlist 7 a partir da playlist 6 menos o "tempSong"...
        Playlist* p7 = new Playlist(*p6 - tempSong);
        p7->setName("Playlist 7");
        cout << p7->getName() << " criada da playlist 6 - uma música:" << endl;
        p7->displayAllSongs(p7->getSongs()->getHead());
        cout << endl << "________________________________________" << endl << endl;

        // Extraindo a última música da playlist 6...
        Song* songPtr = new Song;
        *p6 >> songPtr;

        cout << p6->getName() << " após extração:" << endl;
        p6->displayAllSongs(p6->getSongs()->getHead());
        cout << endl << "Música que foi extraída: ";
        cout << songPtr->getTitle() << " - " << songPtr->getArtist() << endl;
        cout << endl << "________________________________________" << endl << endl;

        // Adicionando novamente a música ao fim da playlist 6...
        *p6 << songPtr;
        cout << p6->getName() << " após inserção:" << endl;
        p6->displayAllSongs(p6->getSongs()->getHead());

        cout << endl << "________________________________________" << endl << endl;
        cout << "Eliminando variáveis..." << endl;
        //Deletando as listas e variáveis do teste...
        cout << "testList: ";
        delete testList;
        cout << "Concluído!" << endl;
        cout << "Lista 1: ";
        delete lista1;
        cout << "Concluído!" << endl;
        cout << "Lista 2: ";
        delete lista2;
        cout << "Concluído!" << endl;
        cout << "Lista 3: ";
        delete lista3;
        cout << "Concluído!" << endl;
        cout << "Playlist 1: ";
        delete p1;
        cout << "Concluído!" << endl;
        cout << "Playlist 2: ";
        delete p2;
        cout << "Concluído!" << endl;
        cout << "Playlist 3: ";
        delete p3;
        cout << "Concluído!" << endl;
        cout << "Playlist 4: ";
        delete p4;
        cout << "Concluído!" << endl;
        cout << "Playlist 5: ";
        delete p5;
        cout << "Concluído!" << endl;
        cout << "Playlist 6: ";
        delete p6;
        cout << "Concluído!" << endl;
        cout << "Playlist 7: ";
        delete p7;
        cout << "Concluído!" << endl;
        cout << "temp: ";
        delete temp;
        cout << "Concluído!" << endl;
        cout << "songPtr: ";
        delete songPtr;
        cout << "Concluído!" << endl << endl;
        cout << "Teste finalizado com sucesso!" << endl;
}

/**< Imprime os comandos que o programa pode executar. */
void helpPage(){

  cout << "Comandos para gerenciamento de músicas: " << endl << endl;
  cout << "add - Adicionar uma música" << endl;
  cout << "del - Remover uma música" << endl;
  cout << "list - Listar todas as músicas" << endl;
  cout << "search - Buscar uma música" << endl << endl;

  cout << "Comandos para gerenciamento de playlists: " << endl << endl;
  cout << "addp - Adicionar uma playlist" << endl;
  cout << "delp - Remover uma playlist" << endl;
  cout << "listp - Listar todas as playlists" << endl;
  cout << "playp - Comece a tocar uma playlist" << endl << endl;

  cout << "Comandos para gerenciamento de músicas em playlists: " << endl << endl;
  cout << "playn - Toque a próxima música de uma playlist." << endl;
  cout << "playb - Volte uma música." << endl;
  cout << "plays - Pare a reprodução de músicas." << endl;
  cout << "addmp - Adicionar música a uma playlist" << endl;
  cout << "delmp - Remover música de uma playlist" << endl;
  cout << "mmp - Mover música numa playlist" << endl;
  cout << "listmp - Listar músicas de uma playlist" << endl;
  cout << "savetf - Salvar uma playlist em um arquivo" << endl;
  cout << "mergep - Unir duas playlists em uma única playlist" << endl << endl;

  cout << "otest - Teste de métodos sobrecarregados." << endl << endl;

  cout << "quit - Encerrar o programa." << endl;
  cout << "________________________________________" << endl << endl;
}

/**< Imprime a tela inicial. */
void telaInicial() {
  cout << "       ------ Tela Inicial ------" << endl;
  cout << "Para uma lista de comandos digite 'help' " << endl << endl;
  cout << "Digite um comando: ";
}

void stopPlaying(int& playing, size_t& index){
  if(playing == 0){
    cout << "Nada está tocando no momento..." << endl;
  }
  if(playing == 1){
    cout << "Parando a reprodução!" << endl;
    index = 0;
    playing = 0;
  }
}