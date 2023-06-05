/** \file */
/**
 * @file main.cpp
 * @author Erick Marques
 * @brief Projeto que organiza músicas e playlists em listas ligadas.
 * @version 0.1
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "musica.h"
#include "listaLigada.h"
#include "utilitarios.h"
#include "playlist.h"
#include "listaPlaylists.h"

using namespace std;

string chkint;
int playing = 0;

/**
 * @brief O menu principal do programa e todas as suas operações.
 */
int main(){ 
  // Cria a lista global de músicas do programa
  LinkedList* globalList = new LinkedList;
  // Cria a lista de armazenar as playlists do programa
  ListOfPlaylists* playlists = new ListOfPlaylists;

 
  no* searchResult = nullptr; // Ponteiro para o nó retornado na busca
  size_t index = 0; // Indice na lista para as interações com o usuário
  size_t index2 = 0; // Indice na lista para as interações com o usuário
  // Variáveis temporárias para armazenar as entradas do usuário
  Playlist* tempPlaylist = nullptr;
  Song tempSong;
  string tempTitle = ""; 
  string tempArtist = "";
  int option = 1; // Variável que mantém o programa em loop.
  // Executa o menu de funcionalidades enquanto a opção for diferente de 0
  while (option != 0) {
    int validcommand = 0;
    telaInicial();
    string chooser; //Declaração da string principal do programa.
    cin >> chooser; //Lê a opção escolhida
    cout << endl << "________________________________________" << endl << endl;
    if(chooser == "add") { // Adicionar uma música
      validcommand = 1;
      // Le as entradas
      cout << "Título da música: ";
      cin.ignore(256, '\n'); //Ignorar o "Enter"
      getline(cin, tempTitle);
      cout << "Nome do artista: ";
      getline(cin, tempArtist);

      // Atribui num objeto do tipo Song
      tempSong.setTitle(tempTitle);
      tempSong.setArtist(tempArtist);

      // Adiciona ao final da lista global 
      int endadded = globalList->insertEnd(tempSong);
      if (endadded == 1){
        cout << endl << "Música adicionada com sucesso!" << endl << endl;
      }
    }
    if(chooser == "del"){ // Remover uma música
      validcommand = 1;
      if (globalList->getSize() == 0) {
        cout << "Não existem músicas registradas..." << endl << endl;
      } else {
        // Imprime a lista de músicas com seus indices
        globalList->display();

        // Lê a entrada
        cout << endl << "Insira o índice da música a ser removida (enumerada acima): ";
        cin >> chkint; //O input do usuário irá para chkint uma variável do tipo string.
        index = stoi(checkInt(chkint)); //Caso o valor em chkint seja de fato um inteiro, index assumirá o valor dele. 
        while (index < 1 || index > globalList->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Acessa a música pelo indice
        searchResult = globalList->getno(index);
        cout << "A música " << searchResult->data.getTitle()  << " - " << searchResult->data.getArtist() << " foi deletada." << endl;

        // Remove de todas as playlists
        if (playlists->getSize() > 0) {
          playlists->removeFromAll(searchResult->data);
        }

        // Remove da lista global
        globalList->removePosition(index);
      }
    }
    if(chooser == "list"){ // Listar todas as músicas
      validcommand = 1;
      // Processo para garantir que há músicas adicionadas
      if (globalList->getSize() == 0) {
        cout << "Ainda não há nada aqui. Experimente adicionar algumas músicas." << endl << endl;
      } else {
        cout << "Músicas armazenadas:" << endl << endl;
        // Imprime a lista de músicas com seus indices
        globalList->display();
        cout << endl;
      }
    }
    if(chooser == "playp"){
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));
        cout << endl << endl;
        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
        index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);
           
        // Processo para garantir que há músicas adicionadas
        if (tempPlaylist->getSongs()->getSize() == 0) {
          cout << "Ops, não há músicas nessa playlist, adicione algumas músicas e tente novamente! " << endl << endl;
        } else {
          // Imprime a lista de músicas com seus indices
          tempPlaylist->displayAllSongs(tempPlaylist->getSongs()->getHead());
            
          // Lê a entrada
          cout << "Insira o índice da música que será tocada (consulte a lista de músicas): ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));

          // Processo para garantir que a entrada é válida
          while (index < 1 || index > tempPlaylist->getSongs()->getSize()) {
            cout << "Índice inválido! Tente novamente: ";
            cin >> chkint; 
            index = stoi(checkInt(chkint));
          }
            cout << endl << "Tocando agora: ";
            tempPlaylist->displayOne(tempPlaylist->getSongs()->getHead(), index);
            playing = 1;
        }
      }
    }
    if(chooser == "playn"){
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playing == 0){
        cout << "Nada está tocando no momento..." << endl << endl;
      }
      if (playing == 1){
        if (playlists->getSize() == 0) {
          cout << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl;
        } else {
          index++;
        }
        if (index > tempPlaylist->getSongs()->getSize()) {
          cout << endl << "Sua playlist acabou, mas a música nunca acaba, recomeçando! :D" << endl << endl;
          index = 1;
        }
        cout << "Tocando agora: ";
        tempPlaylist->displayOne(tempPlaylist->getSongs()->getHead(), index);
        cout << endl << endl;
      }
    }
    if(chooser == "playb"){
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playing == 0){
        cout << "Nada está tocando no momento..." << endl << endl;
      }
      if (playing == 1){
        if (playlists->getSize() == 0) {
          cout << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl;
        } else {
          index--;
        }
        if (index < 1) {
          cout << endl << "Você está no início... Assim como o tempo, você não pode voltar atrás..." << endl << endl;
          index = 1;
        }
        cout << "Tocando agora: ";
        tempPlaylist->displayOne(tempPlaylist->getSongs()->getHead(), index);
        cout << endl << endl;
      }
    }
    if(chooser == "plays"){
      validcommand = 1;
      stopPlaying(playing, index);
    }
    if(chooser == "search") { // Buscar uma música 
      validcommand = 1;
      cout << "Título da música: ";
      cin.ignore(256, '\n');
      getline(cin, tempTitle);
      cout << "Nome do artista: ";
      getline(cin, tempArtist);

      // Atribui num objeto do tipo Song
      tempSong.setTitle(tempTitle);
      tempSong.setArtist(tempArtist);
        
      // Efetua a busca
      searchResult = globalList->search(tempSong);

      // Da o retorno
      if (searchResult == nullptr) {
        cout << endl << "Essa música não foi adicionada! Verifique se você digitou corretamente ou adicione a música antes de tentar novamente." << endl << endl;
      } else {
        cout << endl << "A música " << searchResult->data.getTitle() << " - " << searchResult->data.getArtist() << " está armazenada!" << endl;
      }
      cout << endl;
    }
    if(chooser == "addp") { // Adicionar uma playlist
      validcommand = 1;
      cout << "Nome da playlist: ";
      cin.ignore(256, '\n');
      getline(cin, tempTitle);

      // Aloca a nova playlist
      tempPlaylist = new Playlist;
        
      // Adiciona o nome escolhido
      tempPlaylist->setName(tempTitle);

      // Insere na lista
      playlists->insertPlaylist(tempPlaylist);

      cout << endl;
    }
    if(chooser == "delp") { // Remover uma playlist
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << endl << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl << endl;
      } else {
        // Imprime a lista de playlists com seus indices
        cout << "Playlists registradas: " << endl;
        playlists->display();

        // Lê a entrada
        cout << endl << "Insira o índice da playlist a ser removida: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));
        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }
          
        // Remove a playlist
        playlists->removePlaylist(index);
        cout << "Remoção concluída com sucesso." << endl << endl;
      }
    }
    if(chooser == "listp") { // Listar todas as playlists
      // Processo para garantir que as playlists foram adicionadas.
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << endl <<"Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl << endl;
      } else {
        cout << "Playlists armazenadas atualmente:" << endl << endl;
        // Imprime a lista de músicas com seus indices
        playlists->display();
      }
    }
    if(chooser == "addmp"){ // Adicionar música a uma playlist
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << endl << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da playlist desejada (enumerada acima): ";
        int validstuff = 0;
        int invalidstuff = 0;
        while (validstuff == 0){
          if(invalidstuff == 1){
            cout << "Indice inválido! Tente Novamente: ";
          }
          cin >> chkint; 
          if (isdigit(chkint[0]) == true) {
            index = stoi(chkint);
            validstuff = 1;
          } else {
            validstuff = 0;
            invalidstuff = 1;
          }
        }
        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << endl << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);
        cout << "Playlist selecionada: " << tempPlaylist->getName() << endl << endl;

        // Le as entradas
        cout << "Título da música: ";
        cin.ignore(256, '\n');
        getline(cin, tempTitle);
        cout << "Nome do artista: ";
        getline(cin, tempArtist);
        cout << "Em qual posição deseja adicionar (verifique a lista de músicas da playlist): ";
        validstuff = 0;
        while (validstuff == 0){
          cin >> chkint; 
          if (isdigit(chkint[0]) == true) {
            index = stoi(chkint);
            validstuff = 1;
          } else {
            cout << "Índice inválido! Tente novamente: ";
            validstuff = 0;
          }
        }

        // Processo para garantir que a posição é válida
        while (index < 1) {
          cout << endl << "Posição inválida. Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }
        // Atribui num objeto do tipo Song
        tempSong.setTitle(tempTitle);
        tempSong.setArtist(tempArtist);
          
        // Busca pela música armazenada
        searchResult = globalList->search(tempSong);
        if (searchResult == nullptr) {
          cout << endl << "Ops, a música não foi adicionada até o momento, por favor, adicione-a e tente novamente! " << endl << endl;
        } else {
          // Adiciona na playlist
          tempPlaylist->insertSong(index, tempSong);
          cout << endl << "Música adicionada à playlist '" << tempPlaylist->getName() << "'" << endl << endl;
        }
      }
    }
    if(chooser == "delmp"){ // Remover música de uma playlist
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma!" << endl << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << endl << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);
        cout << "Playlist selecionada: " << tempPlaylist->getName() << endl << endl;

        // Processo para garantir que há músicas adicionadas
        if (tempPlaylist->getSongs()->getSize() == 0) {
          cout << "Ops, a música não foi adicionada até o momento, por favor, adicione-a e tente novamente! " << endl << endl;
        } else {
          // Imprime a lista de músicas com seus indices
          tempPlaylist->displayAllSongs(tempPlaylist->getSongs()->getHead());
            
          // Lê a entrada
          cout << "Insira o índice da música a ser removida (consulte a lista de músicas): ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));

          // Processo para garantir que a entrada é válida
          while (index < 1 || index > tempPlaylist->getSongs()->getSize()) {
            cout << "Índice inválido! Tente novamente: ";
            cin >> chkint; 
            index = stoi(checkInt(chkint));
          }
            
          // Remove a música
          tempPlaylist->removeSong(index);
          cout << endl << "Música removida da playlist '" << tempPlaylist->getName() << "'" << endl << endl;
        }
      }
    }
    if(chooser == "mmp"){ // Mover música numa playlist
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << endl << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);
        cout << "Playlist selecionada: " << tempPlaylist->getName() << endl << endl;

        // Processo para garantir que há músicas adicionadas
        if (tempPlaylist->getSongs()->getSize() == 0) {
          cout << "Ops, a música não foi adicionada até o momento, por favor, adicione-a e tente novamente! " << endl << endl;
        } else {
          // Imprime a lista de músicas com seus indices
          cout << endl << "Músicas nesta playlist: " << endl;
          tempPlaylist->displayAllSongs(tempPlaylist->getSongs()->getHead());
            
          // Lê a entrada
          cout << endl << "Insira o índice da música a ser movida: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));

          // Processo para garantir que a entrada é válida
          while (index < 1 || index > tempPlaylist->getSongs()->getSize()) {
            cout << endl << "Índice inválido! Tente novamente: ";
            cin >> chkint; 
            index = stoi(checkInt(chkint));
          }

          // Lê a entrada
          cout << "Insira o índice da posição para qual deseja movê-la: ";
          cin >> chkint; 
          index2 = stoi(checkInt(chkint));

          // Processo para garantir que a entrada é válida
          while (index2 < 1 || index2 > tempPlaylist->getSongs()->getSize()) {
            cout << endl << "Índice inválido! Tente novamente: ";
            cin >> chkint; 
            index2 = stoi(checkInt(chkint));
          }
            
          // Move a música
          tempPlaylist->moveSong(index, index2);
          cout << endl << "Posição alterada com sucesso." << endl << endl;
        }
      }
    }
    if(chooser == "listmp") { // Listar músicas de uma playlist
      // Processo para garantir que há playlists adicionadas
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, tente criar uma! " << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
        index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);

        // Processo para garantir que há músicas adicionadas
        if (tempPlaylist->getSongs()->getSize() == 0) {
          cout << endl << "Ops, a música não foi adicionada até o momento, por favor, adicione-a e tente novamente! " << endl << endl;
        } else {
          cout << endl << endl << "Músicas da playlist '" << tempPlaylist->getName() << "':" << endl << endl;
          tempPlaylist->displayAllSongs(tempPlaylist->getSongs()->getHead());
        }
        cout << endl;
      }
    }
    if(chooser == "copyp"){ //Função que cria uma playlist cópia de uma já existente.
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, crie duas e tente novamente! " << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da primeira playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);

        Playlist* tempPlaylistC = new Playlist(*tempPlaylist);

        cout << endl << "Digite o nome da nova Playlist: ";
        cin.ignore(256, '\n');
        getline(cin, tempTitle);

        // Adiciona o nome escolhido
        tempPlaylistC->setName(tempTitle);

        // Insere na lista
        playlists->insertPlaylist(tempPlaylistC); 
      }
    }
    if (chooser == "mergep") { //Função que cria uma nova playlist que contém as músicas de duas playlists previamente criadas.
      validcommand = 1;

      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, crie duas e tente novamente! " << endl;
      }
      if  (playlists->getSize() == 1) {
        cout << "Você precisa de pelo menos duas playlists para realizar essa operação, crie-as e tente novamente! " << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da primeira playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);

        Playlist* tempPlaylist2 = nullptr;
          
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da segunda playlist desejada: ";
        cin >> chkint; 
        index2 = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index2 < 1 || index2 > playlists->getSize() || index2 == index ) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index2 = stoi(checkInt(chkint));
        }
        tempPlaylist2 = playlists->getPlaylist(index2);

        Playlist* tempPlaylist3 = new Playlist(*tempPlaylist + *tempPlaylist2); //p3 = p1+p2

        cout << "Digite o nome da nova Playlist: ";
        cin.ignore(256, '\n');
        getline(cin, tempTitle);

        // Adiciona o nome escolhido
        tempPlaylist3->setName(tempTitle);

        // Insere na lista
        playlists->insertPlaylist(tempPlaylist3);         
      }
    }
    if (chooser == "mergep-"){ // Função que usando duas playlists previamente criadas cria uma nova playlist com as músicas da segunda removidas da primeira.
      validcommand = 1;
      if (playlists->getSize() == 0) {
        cout << "Ops, nenhuma playlist foi adicionada até o momento, crie duas e tente novamente! " << endl;
      }
      if (playlists->getSize() == 1) {
        cout << "Você precisa de pelo menos duas playlists para realizar essa operação, crie-as e tente novamente! " << endl;
      } else {
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da primeira playlist desejada: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index < 1 || index > playlists->getSize()) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index = stoi(checkInt(chkint));
        }

        // Obtém a playlist pelo índice
        tempPlaylist = playlists->getPlaylist(index);

        Playlist* tempPlaylist2 = nullptr;
          
        // Lê a entrada
        cout << "Playlists disponíveis: " << endl;
        playlists->display();
        cout << "Insira o índice da segunda playlist desejada: ";
        cin >> chkint; 
        index2 = stoi(checkInt(chkint));

        // Processo para garantir que a entrada é válida
        while (index2 < 1 || index2 > playlists->getSize() || index2 == index ) {
          cout << "Índice inválido! Tente novamente: ";
          cin >> chkint; 
          index2 = stoi(checkInt(chkint));
        }
        tempPlaylist2 = playlists->getPlaylist(index2);

        Playlist* tempPlaylist3 = new Playlist(*tempPlaylist - *tempPlaylist2); //p3 = p1 - p2

        cout << "Digite o nome da nova Playlist: ";
        cin.ignore(256, '\n');
        getline(cin, tempTitle);

        // Adiciona o nome escolhido
        tempPlaylist3->setName(tempTitle);

        // Insere na lista
        playlists->insertPlaylist(tempPlaylist3);         
      }
    }
    if(chooser == "addtp"){ //Função que adiciona algumas músicas e playlists ao reprodutor automaticamente.
      validcommand = 1;
      // Adicionando primeira playlist.
      Playlist* Playlist_1 = new Playlist;
      Playlist_1->setName("Playlist 1");
      playlists->insertPlaylist(Playlist_1);
      // Adicionando segundo playlist.
      Playlist* Playlist_2 = new Playlist;
      Playlist_2->setName("Playlist 2");
      playlists->insertPlaylist(Playlist_2);
      // Adicionando primeira música
      tempSong.setTitle("Shelter");
      tempSong.setArtist("Porter Robinson");
      globalList->insertEnd(tempSong);
      //Adicionando a música na playlist 1
      Playlist_1->insertSong(1, tempSong);
      // Adicionando segunda música
      tempSong.setTitle("Never Gonna Give You Up");
      tempSong.setArtist("Rick Astley");
      globalList->insertEnd(tempSong);
      Playlist_1->insertSong(2, tempSong);
      Playlist_2->insertSong(1, tempSong);
      // Adicionando terceira música
      tempSong.setTitle("Firework");
      tempSong.setArtist("Katy Perry");
      globalList->insertEnd(tempSong);
      Playlist_1->insertSong(3, tempSong);
      Playlist_2->insertSong(2, tempSong);
      // Adicionando quarta música
      tempSong.setTitle("Complicated");
      tempSong.setArtist("Avril Lavigne");
      globalList->insertEnd(tempSong);
      Playlist_2->insertSong(3, tempSong);
      // Adicionando quinta música
      tempSong.setTitle("Jump");
      tempSong.setArtist("Van Haley");
      globalList->insertEnd(tempSong);
      Playlist_2->insertSong(4, tempSong);
      cout << endl << "Músicas adicionadas com sucesso!" << endl << endl;
    }
    if (chooser == "help"){
      validcommand = 1;
      helpPage();
    }
    if (chooser == "savetf"){
      validcommand = 1;
      ofstream myfile;
        
      cout << "Escolha a playlist que você quer armazenar: " << endl;
      playlists->display();
      cout << "Insira o índice da playlist desejada: ";
      cin >> chkint; 
      index = stoi(checkInt(chkint));
      while (index < 1 || index > playlists->getSize()) {
        cout << "Índice inválido! Tente novamente: ";
        cin >> chkint; 
        index = stoi(checkInt(chkint));
      }
      tempPlaylist = playlists->getPlaylist(index);
        
      if (tempPlaylist->getSongs()->getSize() == 0) {
        cout << endl << "Ops, a música não foi adicionada até o momento, por favor, adicione-a e tente novamente! " << endl << endl;
      } else {
        myfile.open("Playlists.txt", std::ios_base::app);
        // myfile << endl << endl << "Músicas da playlist '" << tempPlaylist->getName() << "':" << endl << endl;
        myfile << tempPlaylist->getName() << ";";
        tempPlaylist->saveAlltofile(tempPlaylist->getSongs()->getHead(), myfile);
        myfile.seekp(-1, ios::end);
        myfile << endl;
         myfile.close();
      }
    }
    if (chooser == "otest"){ // Opção de teste para os métodos sobrecarregados
      validcommand = 1;
      testeSobrecarga();
      cout << "Pressione 'Enter' para continuar." << endl;
      getchar();
      getchar();
    }
    if (chooser == "quit"){ //Encerra o programa.
      validcommand = 1;
      cout << "Encerrando o programa." << endl << endl;
      option = 0;
      // Libera a memória das listas globais
      delete globalList;
      delete playlists;
      cout << "Programa Encerrado!" << endl;
    } 
    if(validcommand == 0){
      cout << "Comando inválido!" << endl << endl;
    }
  }
  return 0;
}