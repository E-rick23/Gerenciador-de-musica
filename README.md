Grupo: Erick Marques Oliveira Azevedo - Matricula 20210047901 

## Como rodar o programa:

### Usando o WSL/Bash: 

```bash

# Na pasta do programa compile o programa usando o CMake:

$ cmake .

$ make

# Em seguida execute o arquivo gerado com o seguinte comando:

$ ./music

```

Os comandos disponíveis neste programa são:

## Comando de ajuda e encerramento do programa:

```bash

# help - Comando que exibe a lista de comandos.

# quit - Comando que encerra o programa.

```

## Comandos para gerenciamento de músicas:

```bash

# add - Comando que adiciona uma música.

# del - Comando que deleta uma música previamente armazenada.

# list - Comando que lista todas as músicas armazenadas.

# search - Comando que busca uma música específica na lista de músicas armazenadas.

```

## Comandos para gerenciamento de playlists:

```bash

# addp - Comando que adiciona uma playlist.

# delp - Comando que elimina uma playlist previamente armazenada.

# listp - Comando que lista todas as playlists armazenadas.


```

## Comandos para reprodução de música nas playlists:

```bash

# playp - Comando para reproduzir uma playlist.

# playn - Comando para que a próxima música da playlist seja reproduzida.

# playb - Comando para que a música anterior da playlist seja reproduzida.

# plays - Comando para que a reprodução de músicas pare.

```

## Comandos para gerenciamento de música nas playlists:

```bash


# addmp - Comando que adiciona uma música em uma playlist.

# delmp - Comando que remove uma música previamente armazenada em uma playlist.

# mmp = Comando que move músicas em uma playlist.

# listmp - Comando que lista músicas em uma playlist.

# copymp - Comando que cria uma cópia de uma playlist existente.

# mergep - Comando que cria uma nova playlist união de duas playlists.

# mergep- - Comando que cria uma nova playlist, removendo as músicas da segunda playlist da primeira.

# savetf - Salvar uma playlist em um arquivo "Playlists.txt".

```

## Comandos para testes das funções:

```bash

# addtp - Adiciona algumas músicas e playlists pré-definidas.

# otest - Testa os métodos sobrecarregados.

```

## Exemplo de utilização do programa:



### Iniciando o programa

```bash

$ ./music

``` 
### Tela inicial do programa:

```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando:

```

### Comando "help" para exibir todos os comandos:

```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: help

________________________________________

Comandos para gerenciamento de músicas:

add - Adicionar uma música
del - Remover uma música
list - Listar todas as músicas
search - Buscar uma música

Comandos para gerenciamento de playlists:

addp - Adicionar uma playlist
delp - Remover uma playlist
listp - Listar todas as playlists

Comandos para reproduzir músicas de playlists:       
playp - Comece a tocar uma playlist
playn - Toque a próxima música de uma playlist.      
playb - Volte uma música.
plays - Pare a reprodução de músicas.

Comandos para gerenciamento de músicas em playlists: 

addmp - Adicionar música a uma playlist
delmp - Remover música de uma playlist
mmp - Mover música numa playlist
listmp - Listar músicas de uma playlist
copyp - Criar uma cópia de uma playlist existente.
mergep - Unir duas playlists em uma única playlist
mergep- - Remover músicas da segunda playlist da primeira e retornar uma nova playlist

savetf - Salvar uma playlist em um arquivo
Comandos para teste:
addtp - Adicionar músicas e playlists pré-definidas ao programa.
otest - Teste de métodos sobrecarregados.

quit - Encerrar o programa.
________________________________________

```
### Adicionando uma música
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: add

----------------------------------------

Título da música: Shiny and New          
Nome do artista: Lonely Bunker

Música adicionada com sucesso!
```
### Removendo uma música previamente adicionada
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: del

----------------------------------------

1 - Shiny and New - Lonely Bunker

Insira o índice da música a ser removida (consulte a lista de músicas): 1
A música Shiny and New - Lonely Bunker foi deletada.
```
### Listando todas as músicas adicionadas
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: list

----------------------------------------

Músicas armazenadas:

1 - Shiny and New - Lonely Bunker
2 - A Sky Full Of Stars - Coldplay
3 - Complicated - Avril Lavigne
4 - Careless Whisper - George Michael
```
### Verificando se uma música já foi adicionada 
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: search

----------------------------------------

Título da música: A Sky Full Of Stars
Nome do artista: Coldplay

A música A Sky Full Of Stars - Coldplay está armazenada!
```
### Adicionando uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: addp

----------------------------------------

Nome da playlist: Favoritas

Playlist criada com sucesso!
```
### Eliminando uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: delp

----------------------------------------

Playlists registradas:
1 - Favoritas

Insira o índice da playlist a ser removida: 1 
Remoção concluída com sucesso.
```
### Listar todas as playlists
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: listp

----------------------------------------

Playlists armazenadas atualmente:

1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
```
### Iniciando a reprodução de uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: playp

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
Insira o índice da playlist desejada: 3

1 - Take It - Avril Lavigne
2 - Paradise City - Guns N Roses
3 - Could Have Been Me - The Struts
4 - Hot Night Crash - Sahara Hotnights
5 - Complicated - Avril Lavigne

Insira o índice da música que será tocada (consulte a lista de músicas): 1

Tocando agora: Take It - Avril Lavigne

```
### Tocar a próxima música na playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: playn

----------------------------------------

Tocando agora: Paradise City - Guns N Roses

```
### Tocar a música anterior na playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: playb

----------------------------------------

Tocando agora: Take It - Avril Lavigne

```
### Parar a reprodução de músicas
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: plays

----------------------------------------

Parando a reprodução!
```

### Adicionar música a uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: addmp

----------------------------------------

Playlists disponíveis: 
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
Insira o índice da playlist desejada (enumerada acima): 3
Playlist selecionada: Rock

Título da música: Complicated
Nome do artista: Avril Lavigne
Em qual posição deseja adicionar (consulte a lista de músicas): 1

Música adicionada à playlist 'Rock'
```
### Eliminando uma música de uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: delmp

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
Insira o índice da playlist desejada: 1
Playlist selecionada: Pop

1 - Shiny and New - Lonely Bunker
2 - Careless Whisper - George Michael
3 - Call Me Maybe - Carly Rae Jepsen
Insira o índice da música a ser removida (consulte a lista de músicas): 1

Música removida da playlist 'Pop'
```
### Movendo músicas em uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: mmp

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
Insira o índice da playlist desejada: 3
Playlist selecionada: Rock


Músicas nesta playlist:

1 - Take It - Avril Lavigne
2 - Paradise City - Guns N Roses
3 - Could Have been Me - The Struts
4 - Hot Night Crash - Sahara Hotnights
5 - Complicated - Avril Lavigne

Insira o índice da música a ser movida: 3
Insira o índice da posição para qual deseja movê-la: 1

Posição alterada com sucesso.
```
### Listando todas as músicas em uma playlist
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: listmp

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
Insira o índice da playlist desejada: 3


Músicas da playlist 'Rock':

1 - Could Have Been Me - The Struts
2 - Take It - Avril Lavigne
3 - Paradise City - Guns N Roses
4 - Hot Night Crash - Sahara Hotnights
5 - Complicated - Avril Lavigne
```
### Criando uma playlist cópia usando uma playlist já existente
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: copyp

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
Insira o índice da playlist desejada: 3

Digite o nome da nova playlist: Cópia de Rock

Playlist criada com sucesso!
```
### Unindo duas playlists em uma nova playlist

```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: mergep

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
5 - Cópia de Rock
Insira o índice da primeira playlist desejada: 3

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
5 - Cópia de Rock
Insira o índice da segunda playlist desejada: 1

Digite o nome da nova playlist: Pop-Rock

Playlist criada com sucesso!
```
### Apagando as músicas de uma playlist em outra playlist

```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: mergep-

----------------------------------------

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
5 - Cópia de Rock
6 - Pop-Rock
Insira o índice da primeira playlist desejada: 6

Playlists disponíveis:
1 - Pop
2 - Eletrônica
3 - Rock
4 - Lo-Fi
5 - Cópia de Rock
6 - Pop-Rock
Insira o índice da segunda playlist desejada: 1

Digite o nome da nova playlist: Rock 2

Playlist criada com sucesso!
```

### Salvando uma playlist em um arquivo

```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: savetf


Escolha a playlist que você quer armazenar:
1 - Rock
2 - Pop
3 - Eletrônica
4 - Lo-Fi
5 - Cópia de Rock
6 - Pop-Rock
7 - Rock 2
Insira o índice da playlist desejada: 7

-> Output em Playlists.txt: 

Rock 2;Could Have Been Me:The Struts,Take It:Avril Lavigne,Paradise City:Guns N Roses,Hot Night Crash:Sahara Hotnights,Complicated:Avril Lavigne

```

### Adicionando músicas e playlists pré-definidas
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: addtp

________________________________________


Playlist criada com sucesso!

Playlist criada com sucesso!

Músicas adicionadas com sucesso!
```

### Encerrando o programa
```bash
       ------ Tela Inicial ------
Para uma lista de comandos digite 'help'

Digite um comando: quit

----------------------------------------

Encerrando o programa.

```

A documentação pode ser encontrada em pdf no arquivo "Documentação.pdf" na pasta raiz do programa ou em html na pasta "/docs/html/index.html".