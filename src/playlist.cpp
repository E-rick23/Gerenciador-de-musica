/** \file */
/**
 * @file playlist.cpp
 * @author Erick Marques
 * @brief Funções que definem, exibem e permitem o funcionamento das playlists.
 * @version 0.1
 */
#include "playlist.h"

using namespace std;

/**< Aloca a lista de músicas e inicializa os atributos necessários. */
Playlist::Playlist() {
  songs = new LinkedList;
  playing = nullptr;
  count = 1;
}
/**< Libera a memória da lista de músicas */
Playlist::~Playlist() {
  delete songs;
}
/**< Retorna as músicas de uma playlist*/
LinkedList* Playlist::getSongs() {
  return songs;
}
/**< Retorna o nome de uma playlist*/
string Playlist::getName() {
  return name;
}
/**< Define o nome de uma playlist*/
void Playlist::setName(string _name) {
  name = _name;
}
/**< Essa função une a playlist atual com a playlist passada por referência (segPlaylist) e retorna uma nova playlist*/
Playlist Playlist::operator+ (Playlist& segPlaylist) {
  Playlist resultante; /**Criando uma nova playlist vazia*/
  resultante.insertSong(*this); /**Insere as músicas da playlist atual na playlist resultante*/
  resultante.insertSong(segPlaylist); /**Insere as músicas da segunda playlist na playlist resultante*/
  return resultante; /**Retorna a playlist resultante*/
}
/**< Essa função copia todas as músicas da playlist passada por referência para a playlist que está sendo usada atualmente*/
Playlist::Playlist(const Playlist& old) {
  songs = new LinkedList;
  playing = nullptr;
  count = 1;
  name = old.name;
  no* temp = old.songs->getHead(); 
  while (temp != nullptr) {
    songs->insertEnd(temp->data);
    temp = temp->next;
  }
}
/**< Essa função copia as músicas da playlist atual, insere a música passada por parâmetro e retorna uma nova playlist*/
Playlist Playlist::operator+ (Song& toAdd) {
  Playlist resultante; /**Criando uma nova playlist vazia*/
  resultante.insertSong(*this); /**Inserindo músicas da playlist atual na playlist resultante*/
  resultante.songs->insertEnd(toAdd); /**Inserindo a música do parâmetro no final da playlist*/
  return resultante; /**Retornando a playlist final*/
}

/** 
 * Cria uma playlist nova contendo todas as músicas da playlist atual que não estão na playlist passada por referência.
 * @param segPlaylist referência de objeto do tipo Playlist.
 * @return a playlist resiltante.
 */
Playlist Playlist::operator- (Playlist& segPlaylist) {
  Playlist resultante(*this); /**Cria uma playlist resultante a partir da playlist atual*/
  no* temp = segPlaylist.getSongs()->getHead();
  /**Loop while que percorre a segunda playlist*/
  while (temp != nullptr) {
    /**Procurando a posição da música na playlist resultante*/
    size_t pos = resultante.getSongs()->getPosition(temp->data);
    if (pos > 0) {
      resultante.removeSong(pos);
    }
    temp = temp->next;
  }
  return resultante; /**Retornando a playlist resultante*/
}
/** 
 * Copia as músicas da playlist atual, remove a música passada por parâmetro e retorna uma playlist final.
 * @param toRemove é a referência de objeto do tipo Song.
 * @return é a playlist resultante.
 */
Playlist Playlist::operator- (Song& toRemove) {
  Playlist resultante(*this); /**Criando a playlist resultante a partir da playlist atual*/
  size_t pos = resultante.getSongs()->getPosition(toRemove); /**Obtendo a posição da música na playlist final*/
  /**Se a musica existir, na playlist ela é removida*/
  if (pos > 0) {
    resultante.removeSong(pos);
  }
  return resultante; /**Retornando a playlist reslutante*/
}
/**
 * Extrai a última música da playlist e atribui seus valores a música recebida como argumento
 * @param lastSong recebe os valores da música extraída.
 */
void Playlist::operator>> (Song*& lastSong) {
  if (songs->getSize() > 0) {
    no* temp = new no;
    *songs >> temp; /**Extraindo o ultimo nó da lista de músicas*/
    *lastSong = temp->data; /**Guardando a música desse nó*/
    delete temp;
  } else {
    lastSong = nullptr;
  }
}
/** 
 * Adiciona uma música passada por argumento no fim da playlist.
 * @param newSong é a música a ser inserida.
*/
void Playlist::operator<< (Song*& newSong) {
  if (newSong == nullptr) {
    return;
  } else {
    songs->insertEnd(*newSong);
  }
}
/**
 * Chama o método da lista para inserir a música na playlist de acordo com a posição.
 * @param pos é o índice da posição escolhida (começa em 1).
 * @param value é um objeto do tipo Song.
 */
void Playlist::insertSong(size_t pos, Song value) {
  songs->insertPosition(pos, value);
  playing = songs->getHead(); /** Cada vez que uma nova música for inserida, playing recebe o head da lista*/
}

/**
 * Chama o método da lista para remover uma música da playlist baseado na posição.
 * @param pos índice da posição escolhida (a partir de 1)
 */
void Playlist::removeSong(size_t pos) {
  songs->removePosition(pos);
}

/**
 * Move uma música de acordo com as posições passadas por parâmetro
 * @param start índice da posição inicial da música.
 * @param end índice da nova posição.
 */
void Playlist::moveSong(size_t start, size_t end) {
  if (start != end) {
    /**Acessando o ID da música que será movida*/
    no* target = songs->getno(start);
    Song value = target->data;
    /**Removendo a música da posição atual*/
    songs->removePosition(start);
    /**Inserindo a música na nova posição*/
    if (end < start) {
      songs->insertPosition(end, value);
    } else {
      songs->insertPosition(end + 1, value);
    } 
    playing = songs->getHead(); /**Cada vez que uma música for movida, playing recebe o head da lista*/
  }
}

/**
 * Versão sobrecarregada do método de inserção, que insere na playlist atual todas as músicas da playlist passada por argumento.
 * @param toInsert é referência de um objeto do tipo playlist.
 */
void Playlist::insertSong(Playlist& toInsert) {
  /**Verificação para ver se a nova playlist não está vazia*/
  if (toInsert.getSongs()->getSize() < 1) {
    return;
  } else {
    songs->insertEnd(*toInsert.getSongs()); /**Inserindo as músicas na playlist atual por meio de sobrecarga*/
  }
}

/**
 * Versão sobrecarregada do método de remoção, que remove da playlist atual todas as músicas da playlist passada por parâmetro.
 * @param toRemove é referência de um objeto do tipo playlist.
 * @return quantos elementos foram removidos.
 */
size_t Playlist::removeSong(Playlist& toRemove) {
  /** Verificação para ver se a nova playlist não está vazia */
  if (toRemove.getSongs()->getSize() < 1) {
    return 0;
  } else {
    size_t removed = 0;
    no* temp = toRemove.getSongs()->getHead();
    while (temp != nullptr) {
      size_t pos = getSongs()->getPosition(temp->data); /** Obtendo a posição da música na playlist atual*/
      /** Removendo a música da playlist atual*/
      if (pos > 0) {
        removeSong(pos);
        ++removed;
      }
      temp = temp->next;
    }
    return removed; /** Retornando a quantidade de elementos removidos*/
  }
}

/**
 * Função recursiva que exibe todas as músicas que formam a playlist
 * @param current ponteiro para o nó atual contendo a música a que será exibida.
 */
void Playlist::displayAllSongs(no* current) {
  /** Condição de parada */
  if (current == nullptr) {
    count = 1;
    return;
  }
  cout << count << " - " << current->data.getTitle() << " - " << current->data.getArtist() << endl; /**Exibe a música atual*/
  ++count;
  displayAllSongs(current->next); /** Chamada recursiva para que todas as músicas sejam exibidas*/
}

/**
 * Função recursiva que exibe a música que o usuário deseja, usando seu índice.
 * @param current ponteiro para o nó atual contendo a música a que será exibida.
 * @param pos valor do índice.
 */
void Playlist::displayOne(no* current, int pos){
  if (current == nullptr) {
    count = 1;
    return;
  }
  if(count == pos){
cout << current->data.getTitle() << " - " << current->data.getArtist() << endl; /**Exibe a música atual*/
  }
  ++count;
  displayOne(current->next, pos);
}