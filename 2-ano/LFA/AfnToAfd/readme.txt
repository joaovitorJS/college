TRABALHO DE LFA

AFN ----------> AFD

Aluno: JOÃO VITOR DE OLIVEIRA
Rgm: 38342

Para fazer o teste no terminal:
    python3 afnToafd.py

Exemplo para usar:

Informe os estados, separados por , : q1,q2,q3          #os estados devem ser colocados e separados por virgula como no exemplo
Informe o estado inicial: q1                                
Informe os estados finais, separdos por , : q1          #os estados finais tambem devem ser colocados e separados por virgula
Informe o alfabeto, separados por , : a,b               #assim como nos estados devem ser separadas por virgula
Delta(q1,a): -
Delta(q1,b): q2
Delta(q1,ε): q3
Delta(q2,a): q2,q3
Delta(q2,b): q3
Delta(q2,ε): -
Delta(q3,a): q1
Delta(q3,b): -
Delta(q3,ε): -


AFN ---------> AFD


Tabela T AFD:

['q1', 'q3'] Com  a :  ['q1', 'q3']
['q1', 'q3'] Com  b :  ['q2']
['q2'] Com  a :  ['q2', 'q3']
['q2'] Com  b :  ['q3']
['q2', 'q3'] Com  a :  ['q1', 'q2', 'q3']
['q2', 'q3'] Com  b :  ['q3']
['q3'] Com  a :  ['q1', 'q3']
['q3'] Com  b :  []
['q1', 'q2', 'q3'] Com  a :  ['q1', 'q2', 'q3']
['q1', 'q2', 'q3'] Com  b :  ['q2', 'q3']
[] Com  a :  []
[] Com  b :  []

Estado Inicial:  ['q1', 'q3']

Estado(s) Final: 
['q1', 'q3']
['q1', 'q2', 'q3']


Informe a Palavra: abbba                        #a string nao precisa ser separada por virgula
['q1', 'q3'] --> a --> ['q1', 'q3']
['q1', 'q3'] --> b --> ['q2']
['q2'] --> b --> ['q3']
['q3'] --> b --> []
[] --> a --> []
Palavra nao aceita!


Deseja inserir outra Palavra? 
[1]-SIM
[2]-NAO
2


Deseja inserir outro AFN? 
[1]-SIM
[2]-NAO
2

