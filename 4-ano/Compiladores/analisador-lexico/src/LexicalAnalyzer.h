#include <iostream>
#include <vector>
#include <queue>   // std::queue

#define CONST_INDEX_LITERAL 10

using namespace std;

typedef struct t{
    string tokenName; //toke
    string lexeme;
}token;


string recognizingSeparators(char character);
string recognizingOperator(char character);
bool isKeyword (string str);
bool isLetter (char character);
bool isDigit(char character);
bool isDelimiter(char character);
bool isOperator(char character);
bool isIdentifier(string str);
bool isNumber(string str);
int isLiteral(string str);
bool isSeparators(char character);

class LexicalAnalyzer {
private:
    queue<token> tokens;

public:
    LexicalAnalyzer();

    /*Procedimento que realiza a análise léxica do texto*/
    void run(string textInput);
    void printTableTokens();

    ~LexicalAnalyzer();
};

LexicalAnalyzer::LexicalAnalyzer(){}

LexicalAnalyzer::~LexicalAnalyzer(){

  if (!tokens.empty()) {
    while (!tokens.empty()) {
      tokens.pop();
    }
  }
}


void LexicalAnalyzer::run(string textInput) {
  int sizeTextInput = textInput.length();
  int i = 0, moveToRight = 0;

  while (moveToRight <= sizeTextInput && i <= moveToRight) {
    if (!isDelimiter(textInput[moveToRight])) {
      moveToRight++;
    }

    if (isDelimiter(textInput[moveToRight])) {
      if (i == moveToRight) {

        /*Verificar se aquele caracter é um operador, em caso de true: salvar este token*/
        if (isOperator(textInput[moveToRight])) {
          token tk;
          tk.tokenName = recognizingOperator(textInput[moveToRight]);
          tk.lexeme = textInput[moveToRight];
          tokens.push(tk);
        }

        if (isSeparators(textInput[moveToRight])) {
          token tk;
          tk.tokenName = recognizingSeparators(textInput[moveToRight]);
          tk.lexeme = textInput[moveToRight];
          tokens.push(tk);
        }
        moveToRight++;
        i = moveToRight;

      } else if ( i != moveToRight || (moveToRight == sizeTextInput && i != moveToRight) ){
        token tk;

        string word = textInput.substr(i, moveToRight-i);

        /*Palavra reservada reconhecida*/
        if (isKeyword(word)) {
          tk.lexeme = word;
          tk.tokenName = "pr_" + word;
          tokens.push(tk);
          i = moveToRight;
          continue;
        }

        if (isIdentifier(word)) {
          tk.lexeme = word;
          tk.tokenName = "id";
          tokens.push(tk);
          i = moveToRight;
          continue;
        }

        if (isNumber(word)) {
          tk.lexeme = word;
          tk.tokenName = "num";
          tokens.push(tk);
          i = moveToRight;
          continue;
        }

        int responseIsLiteral = isLiteral(word);
        if (responseIsLiteral == 1) {
          if (moveToRight == sizeTextInput) {
            cout << "Error: open but not closed literal" << endl;
          }
          moveToRight++;
          /*começo de literal encontrado*/
          continue;
        } else if (responseIsLiteral == 2) {
          /*literal completo*/
          tk.lexeme = word;
          tk.tokenName = "literal";
          tokens.push(tk);
          i = moveToRight;
          continue;
        } else if (responseIsLiteral >= 10) {
          cout << "Error: character \"" << word[responseIsLiteral-CONST_INDEX_LITERAL] << "\" is not identified" << endl;
        }

        i = moveToRight;
      }
    }
  }

  return;
}

void LexicalAnalyzer::printTableTokens() {
  queue<token> tempTokens(tokens);
  int i = 1;
  cout << "Tokens table" << endl << endl;

  while (!tempTokens.empty()) {

    token tk = tempTokens.front();

    cout << "token " << i << ":\t" << tk.tokenName << endl
         << "lexeme " << i << ":\t" << tk.lexeme << endl << endl;

    tempTokens.pop();
    i++;
  }

  cout << "----------------------------------------" << endl;
}

int isLiteral(string str) {
  int i, sizeStr = str.length();

  if (sizeStr < 2) return false;

  if ((int)str[0] != 34) {
    /*caso não for um literal por não começão com " */
    return 0;
  }

  for (i = 1; i < sizeStr-2; i++) {
    if ( !isLetter(str[i]) && !isDigit(str[i]) && str[i] != ' ' ) {
      return i + CONST_INDEX_LITERAL; /*não é um literal*/
    }
  }

  if (str[sizeStr-1] == 34) {
    /*achou o literal completo*/
    return 2;
  }

  return 1; /*achou um abre parenteses*/

}

bool isNumber(string str) {
  int i, sizeStr = str.length();

  if (sizeStr == 0) return false;

  if (isDigit(str[0])) {
    for (i = 0; i < sizeStr; i++) {
      if (str[i] != '.' && !isDigit(str[i])) {
        return false;
      }
    }
    return true;
  }

  return false;
}

bool isIdentifier(string str) {
  int i, sizeStr = str.length();

  if (sizeStr == 0) return false;

  if (str[0] == '_' || isLetter(str[0])) {
    for (i = 0; i < sizeStr; i++) {
      if ( !isLetter(str[i]) && !isDigit(str[i]) ) {
        return false;
      }
    }

    return true;
  }

  return false;
}

bool isKeyword (string str) {
  vector<string> keywords{"inicio", "inteiro", "real", "escreva", "leia", "fim"};

  vector<string>::iterator it;
  for (it = keywords.begin(); it != keywords.end(); it++) {
    if ((*it).compare(str) == 0) {
      return true;
    }
  }
  return false;
}

/*Verificador de caracteres*/
bool isLetter (char character) {
  if ( ((int)character >= 97 && (int)character <= 122) || ((int)character >= 65 && (int)character <= 90) ) {
    return true;
  }
  return false;
}

/*Verificador de Digitos*/
bool isDigit(char character) {
  if ((int)character >= 48 && (int)character <= 57) {
    return true;
  }
  return false;
}

bool isDelimiter(char character) {
  char specialCharacter[11] = {' ', ',', ';', '(', ')', '+', '-', '*', '/', '=', '\0'};
  for (int i = 0; i < 11; i++) {
    if (character == specialCharacter[i]) {
      return true;
    }
  }
  return false;
}

bool isOperator(char character) {
  if (character == '+' || character == '-' || character == '*' || character == '/' || character == '=') {
    return (true);
  }
  return (false);
}

bool isSeparators(char character) {
  if (character == ',' || character == ';' || character == '(' || character == ')') {
    return true;
  }
  return false;
}

string recognizingSeparators(char character) {
  string nameOperator;

  switch (character) {
    case ',':
      nameOperator = "virgula";
      break;

    case ';':
      nameOperator = "ponto_virgula";
      break;

    case '(':
      nameOperator = "abre_parenteses";
      break;

    case ')':
      nameOperator = "fecha_parenteses";
      break;

    default:
      break;
  }

  return nameOperator;
}

string recognizingOperator(char character) {
  string nameOperator;

  switch (character) {
    case '+':
      nameOperator = "op_adicao";
      break;

    case '-':
      nameOperator = "op_subtracao";
      break;

    case '*':
      nameOperator = "op_multiplicacao";
      break;

    case '/':
      nameOperator = "op_divisao";
      break;

    case '=':
      nameOperator = "op_atribuicao";
      break;

    default:
      break;
  }

  return nameOperator;
}

