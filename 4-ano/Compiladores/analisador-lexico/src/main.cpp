#include <iostream>
#include <fstream> /* Manipulação de arquivos*/
#include "LexicalAnalyzer.h"

using namespace std;

int main(int argc, char const *argv[]) {
  string filename("entrada.txt"), textInput, textLine;
  ifstream inputFile;
  LexicalAnalyzer lexicalAnalyzer;

  /* Validação da linha de execução:
    Dois métodos válidos:
    -> ./nomedoexecutavel (nome de arquivo padrão: "entrada.txt")
    -> ./nomedoexecutavel nomedearquivo.txt
  */
  if (argc > 1) {
    if (argc == 2) {
      filename = argv[1];
    } else {
      cout << "Error: number of arguments passed!" 
           << endl 
           << "Correct: ./executable or ./excutable filename.txt" 
           << endl;
      return -1;
    }
  }

  /*Abrindo o arquivo*/
  inputFile.open(filename, ifstream::in);

  /*Tratativa de erro ao abrir o arquivo*/
  if (!inputFile.is_open()) {
    cout << "Error: error opening input file!" << endl
         << "Check the filename passed by parameter on the runline" << endl
         << "or" << endl
         << "Check if there is a file named entrada.txt" << endl;
    return -1;
  }

  /*Leitura do arquivo de entrada*/
  while (getline (inputFile, textLine)) {
    textInput += textLine;
  }

  lexicalAnalyzer.run(textInput);
  lexicalAnalyzer.printTableTokens();
  /*Fechando o arquivo de entrada*/
  inputFile.close();

  return 0;
}
