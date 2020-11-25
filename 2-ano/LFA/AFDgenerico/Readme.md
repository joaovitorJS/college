TRABALHO DE LFA

Aluno: JOÃO VITOR DE OLIVEIRA
Rgm: 38342

Para fazer o teste no terminal:
    python3 ADF.py

Exemplo para usar:

    Informe os estados, separados por , : A,B,C             //os estados devem ser colocados e separados por virgula como no exemplo
    Informe o estado inicial: A
    Informe os estados finais, separdos por , : A,C         //os estados devem ser colocados e separados por virgula como no exemplo
    Informe o alfabeto, separados por , : a,b               //assim como nos estados, o alfabeto deve ser separado por virgula
    Delta(A,a): B
    Delta(A,b): C
    Delta(B,a): C
    Delta(B,b): A
    Delta(C,a): A
    Delta(C,b): B


    Informe a Palavra: aabba                            //a string nao tem separação
    A --> a --> B
    B --> a --> C
    C --> b --> B
    B --> b --> A
    A --> a --> B
    Palavra não aceita!


    Deseja inserir outra Palavra? 
    [1]-SIM
    [2]-NAO
    1

