cmake_minimum_required(VERSION 3.18.1)
project(teste VERSION 0.1 LANGUAGES CXX )

include_directories( include )

#Building Instructions for Bash/WSL:
#On the terminal type -> cmake .
#Then type -> make
#After that, to execute it, type -> ./music

add_executable( music
                src/main.cpp
                src/listaLigada.cpp
                src/listaPlaylists.cpp
                src/utilitarios.cpp
                src/playlist.cpp
                src/musica.cpp )
