/** \file */
/**
 * @file listaLigada.cpp
 * @author Erick Marques
 * @brief Funções necessárias para as listas ligadas de músicas.
 * @version 0.1
 */
#include <iostream>
#include "utilitarios.h"
#include "listaLigada.h"
#include "musica.h"
using namespace std;

/**< Inicializando head e tail com valores nulos e tamanho 0. */
LinkedList::LinkedList() {
  head = nullptr;
  tail = nullptr;
  size = 0;
}

/**< Caso os nós da lista ainda existam na memória, eles são desalocados pela seguinte função. */
LinkedList::~LinkedList() {
  if (size != 0) {
    no* temp = nullptr;
    no* cur = nullptr;

    cur = head;

    while (cur != nullptr) {
      temp = cur->next;
      delete cur;
      cur = temp;
    }
  }
}

//As funções abaixo retornam o head, tail e tamanho das listas, respectivamente.
no* LinkedList::getHead() {
  return head;
}

no* LinkedList::getTail() {
  return tail;
}

size_t LinkedList::getSize() {
  return size;
}

/** 
 * Copia todos os elementos da lista passada por referência para a lista atual 
 * @param oldList referência de objeto do tipo linkedList.
 */
LinkedList::LinkedList(const LinkedList& oldList) {
  head = nullptr;
  tail = nullptr;
  size = 0;
  no* temp = oldList.head;
  while (temp != nullptr) {
    insertEnd(temp->data);
    temp = temp->next;
  }
}
/** 
 * Une a lista atual com a lista passada por referência e retorna uma nova lista resultante.
 * @param secondList referência de objeto do tipo linkedList.
 * @return a lista final concatenada.
 */
LinkedList LinkedList::operator+ (const LinkedList& segLista) {
  LinkedList listaFinal;

  //O loop abaixo percorre a lista atual (iniciando do head) e copia os valores para a lista final.
  no* temp = head;
  while (temp != nullptr) {
    listaFinal.insertEnd(temp->data);

    temp = temp->next;
  }
  temp = segLista.head;
  while (temp != nullptr) {
    no* newno = new no;

    newno->data = temp->data;
    newno->next = nullptr;
    
    if (listaFinal.head == nullptr) {
      listaFinal.head = newno;
      listaFinal.tail = newno;
      newno = nullptr;
    } else {
      listaFinal.tail->next = newno;
      listaFinal.tail = newno;
    }
    listaFinal.size++;
    temp = temp->next;
  }
  return listaFinal; //Retornando a lista final.
}

/** 
 * Extrai o último elemento da lista e atribui seus valores ao nó recebido como argumento
 * @param lastNode recebe os valores do nó extraído.
 */
void LinkedList::operator>> (no*& lastno){ 
  if (size > 0) {
    lastno->data = tail->data;
    lastno->next = tail->next;
    removeLast();
  } else {
    lastno = nullptr;
  }
}

/** 
 * Adiciona um nó passado por argumento no final da lista.
 * @param newNode é o nó a ser inserido.
 */
void LinkedList::operator<< (no*& newno) {
  if (newno == nullptr) {
    return;
  } else {
    insertEnd(newno->data);
  }
}

/**
 * Cria e insere no início da lista um nó que armazena a música passada por argumento.
 * @param value é um objeto do tipo Song.
 *
 */
void LinkedList::insertStart(Song value) {
  //O If verifica e impede que a mesma música seja inserida novamente.
  if (search(value) != nullptr) {
    cout << "Esta música já foi adicionada!" << endl << endl;
  } else {
    //Caso a música não tenha sido inserida, ela é adicionada normalmente. :)
    no* temp = new no;
    temp->data = value;
    temp->next = head;
    head = temp;
    ++size; //No final do processo, o tamanho da lista é aumentado.
  }
}

/**
 * Cria e adiciona no fim da lista um nó que armazena a música passada por argumento.
 * @param value é um objeto do tipo Song.
 * @return retorna 0 caso a música já tenha sido adicionada anteriormente ou 1 caso contrário.
 */
int LinkedList::insertEnd(Song value) {
  //O If verifica e impede que a mesma música seja inserida novamente.
  if (search(value) != nullptr) {
    cout << "Esta música já foi adicionada!" << endl << endl;
    return 0;
  } else {
    //Caso a música não tenha sido inserida, ela é adicionada normalmente. :)
    no* temp = new no;
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
    ++size; //No final do processo, o tamanho da lista é aumentado.
    return 1;
  }
}

/**
 * Versão sobrecarregada do método de inserção, que adiciona na lista atual todos os elementos da lista passada por argumento.
 * @param toInsert referência de um objeto do tipo lista ligada.
 */
void LinkedList::insertEnd(LinkedList& toInsert) {
  //O if abaixo verifica se a nova lista não está vazia.
  if (toInsert.getSize() < 1) {
    return;
  } else {
    no* temp = toInsert.getHead();
    //Esse loop adiciona cada elemento no fim da lista atual
    while (temp != nullptr) {
      insertEnd(temp->data);
      temp = temp->next;
    }
  }
}
/**
 * Cria e adiciona numa posição escolhida um nó que armazena a música passada por argumento.
 * Faz as devidas verificações e modificações caso a posição escolhida seja a primeira ou maior que a última.
 * @param pos é o índice da posição escolhida (Inicia-se em 1).
 * @param value é um objeto do tipo Song.
 */
void LinkedList::insertPosition(size_t pos, Song value) {
  no* pre = nullptr;
  no* cur = nullptr;
  //Verifica se a posição escolhida é a primeira ou maior que a última.
  if (pos == 1) {
    if (size == 0) {
      insertEnd(value);
    } else {
      insertStart(value);
    } 
  } else if (pos <= size) {
     //Esse if verifica e impede que a mesma música seja inserida novamente.
    if (search(value) != nullptr) {
      cout << "Esta música já foi adicionada!" << endl << endl;
    } else {
      no* temp = new no;
      cur = head;
      //Esse loop organiza a lista ao inserir a nova música.
      for (size_t i = 1; i < pos; ++i) {
        pre = cur;
        cur = cur->next;
      }
      temp->data = value;
      pre->next = temp;
      temp->next = cur;

      ++size; //Aumentando o valor da lista após a adição da nova música.
    }
  } else {
    insertEnd(value);
  }
}

/**< Essa função serve para declarar o segundo elemento da lista como head e deletar o primeiro. */
void LinkedList::removeFirst() {
  no* temp = head;
  head = head->next;
  --size; //Reduzindo o tamanho da lista após remover o valor.
  delete temp; //Deletando o valor temporário.
}

/**< Essa função serve para declarar o penúltimo elemento da lista como tail e deletar o ultimo. */
void LinkedList::removeLast() {
  no* pre = nullptr;
  no* cur = nullptr;
  cur = head;

  while (cur->next != nullptr) {
    pre = cur;
    cur = cur->next;
  }

  tail = pre;
  pre->next = nullptr;

  --size; //Reduzindo o tamanho da lista após remover o valor.
  delete cur;
}

/**
 * Elimina o nó da posição escolhida e recria o link entre seu antecessor e sucessor.
 * verifica e modifica o procedimento caso a posição escolhida seja a primeira ou maior que a última.
 * @param pos é o índice da posição escolhida (a partir de 1)
 */
void LinkedList::removePosition(size_t pos) {
  no* pre = nullptr;
  no* cur = nullptr;
  //Verifica se a posição escolhida é a primeira ou maior que a última.
  if (pos == 1) {
    removeFirst();
  } else if (pos < size) {
    cur = head;

    for (size_t i = 1; i < pos; ++i) {
      pre = cur;
      cur = cur->next;
    }
    
    pre->next = cur->next;

    --size;
    delete cur;
  } else if (pos < 1) {
    return;
  } else {
    removeLast();
  }
}

/**
 * Versão sobrecarregada do método de remoção, que elimina da lista atual todos os elementos da lista passada por parâmetro.
 * @param toRemove de um objeto do tipo lista ligada
 */
void LinkedList::removePosition(LinkedList& toRemove) {
   //O if abaixo verifica se a nova lista não está vazia.
  if (toRemove.getSize() < 1) {
    return;
  } else {
    no* temp = toRemove.getHead();

    while (temp != nullptr) {
      // Obtém a posição da música na lista atual
      size_t pos = getPosition(temp->data);
  
      // Remove da lista atual
      if (pos > 0) {
        removePosition(pos);
      }                      
      
      temp = temp->next;
    }    
  }
}

/**
 * Percorre a lista procurando o nó que contenha os mesmos valores da música passada por parâmetro.
 * Altera os valores (apenas na função) para desconsiderar maiúsculas.
 * @param searchSong é a música a ser buscada
 * @return o ponteiro para o nó, caso encontre, ou nullptr caso não.
 */
no* LinkedList::search(Song searchSong) {
  no* temp = head;

  while (temp != nullptr) {
    Song s = temp->data;

    /*Transforma os caracteres dos títulos e artistas em minúsculos (sem alterar os valores originais) 
      e os compara, em seguida retorna a posição correspondente ou zero caso não encontre.*/
    if ( toLowercase(s.getTitle()) == toLowercase(searchSong.getTitle()) && 
        toLowercase(s.getArtist()) == toLowercase(searchSong.getArtist()) ) {
      // Retorna o ponteiro para o nó correspondente
      return temp; 
    }

    temp = temp->next;
  }
  // Caso não encontre, retorna nullptr
  return nullptr;
}

/**
 * Percorre a lista até a posição passada por parâmetro e obtém o nó correspondente.
 * @param pos é o índice da posição escolhida (a partir de 1)
 * @return o ponteiro para o nó, caso a posição esteja devidamente dentro da lista, ou nullptr caso contrário.
 */
no* LinkedList::getno(size_t pos) {
  if (pos < 1 || pos > size) {
    return nullptr; //Caso a posição seja inválida, o retorno é nullptr.
  } else {
    //Caso a posição seja válida, a lista é percorrida do head até o final.
    no* temp = head;
    for (size_t i = 1; i < pos; ++i) {
      temp = temp->next;
    }
    return temp; //Retornando o ponteiro para o nó correspondente.
  }
}

/**
 * Percorre a lista até encontrar a música passada por parâmetro e obtém a posição correspondente.
 * @param searchSong é a música a ser buscada
 * @return a posição da música na lista, caso encontre, ou 0 caso não.
 */
size_t LinkedList::getPosition(Song searchSong) {
  no* temp = head;
  size_t pos = 1;

  while (temp != nullptr) {
    Song s = temp->data;
     /*Transforma os caracteres dos títulos e artistas em minúsculos (sem alterar os valores originais) 
      e os compara, em seguida retorna a posição correspondente ou zero caso não encontre.*/
    if ( toLowercase(s.getTitle()) == toLowercase(searchSong.getTitle()) && 
        toLowercase(s.getArtist()) == toLowercase(searchSong.getArtist()) ) {
      return pos; 
    }
    temp = temp->next;
    ++pos;
  }
  return 0;
}


/**< Essa função exibe as músicas armazenadas na lista ligada utilizando um loop while que irá até a ultima posição da lista. */
void LinkedList::display() {
  no* temp = head;
  size_t index = 1;

  while (temp != nullptr) {
    Song s = temp->data;
    cout << index << " - " << s.getTitle() << " - " << s.getArtist() << endl;
    temp = temp->next;
    ++index;
  }
}