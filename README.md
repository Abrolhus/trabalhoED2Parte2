# trabalho ED2 - Parte2
Trabalho de ED2, parte 2 \
Parte 1: https://github.com/abreuthrj/Trabalho_ED2

# Compilação - Thiago

Para rodar o código por linha de comando, digitar no repositorio:
* Windows:
    ```
    g++ *.cpp ArvoresBalanceadas/*.cpp LeituraArvoreQuad/*.cpp -I .\ -o trab.exe -finput-charset=utf-8
   .\Trab.exe // executar o arquivo
   ```

* Linux ou OSX:
  * Usando g++:
  ```
   g++ -std=c++11  -o trab *.cpp # compila e gera executavel
   ./trab # executa o arquivo
  ```
  * Usando cmake:
  ```
  mkdir build && cd build
  cmake ..
  make
  ./trab
  ```
