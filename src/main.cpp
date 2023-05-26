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

void telaInicial();
void helpPage();

string chkint;
int playing = 0;

int main(int argc, char const *argv[])
{ 
  // Cria a lista global de músicas do programa
  LinkedList* globalList = new LinkedList;
  // Cria a lista de armazenar as playlists do programa
  ListOfPlaylists* playlists = new ListOfPlaylists;

  size_t option = 12; // Opção selecionada no menu
  no* searchResult = nullptr; // Ponteiro para o nó retornado na busca
  size_t index = 0; // Indice na lista para as interações com o usuário
  size_t index2 = 0; // Indice na lista para as interações com o usuário
  // Variáveis temporárias para armazenar as entradas do usuário
  Playlist* tempPlaylist = nullptr;
  Song tempSong;
  string tempTitle = ""; 
  string tempArtist = "";
  // Executa o menu de funcionalidades enquanto a opção for diferente de 0
  while (option != 0) {
    // Limpa a tela e exibe as opções do menu
    int validcommand = 0;
    telaInicial();
    string chooser;
    //Le a opção escolhida
    cin >> chooser;
    cout << endl << "----------------------------------------" << endl << endl;
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
        if(playing == 0){
          cout << "Nada está tocando no momento..." << endl;
        }
        if(playing == 1){
          cout << "Parando a reprodução!" << endl;
          index = 0;
          playing = 0;
        }
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
        }
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
      if (chooser == "quit"){
        validcommand = 1;
        cout << "Encerrando o programa." << endl << endl;
        option = 0;
      } 
      if(validcommand == 0){
        cout << "Comando inválido!" << endl << endl;
      }
  }

  // Libera a memória das listas globais
  delete globalList;
  delete playlists;

  return 0;
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
  cout << "savetf - Salvar uma playlist em um arquivo" << endl << endl;

  cout << "Comando para encerrar o programa: " << endl << endl;
  cout << "quit - Sair" << endl;
  cout << "----------------------------------------" << endl << endl;
}

/**< Imprime a tela inicial. */
void telaInicial() {
  cout << "       ------ Tela Inicial ------" << endl;
  cout << "Para uma lista de comandos digite 'help' " << endl << endl;
  cout << "Digite um comando: ";
}