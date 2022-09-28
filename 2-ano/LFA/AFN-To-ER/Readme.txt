Para executar: python3 AFtoER.py

Exemplo de execução: 
    joao@joao-Inspiron-7560:~/Documentos/LFA/AF_ER$ python3 AFtoER.py 
    Informe os estados, separados por , : q1,q2,q3
    Informe o estado inicial: q1
    Informe os estados finais, separdos por , : q2
    Informe o alfabeto, separados por , : 0,1
    Delta(q1,0): q1
    Delta(q1,1): q2
    Delta(q1,ε): -
    Delta(q2,0): q3
    Delta(q2,1): q2
    Delta(q2,ε): -
    Delta(q3,0): q2
    Delta(q3,1): q2
    Delta(q3,ε): -


    AFN ---------> AFD


    Tabela T AFD:

    ['q1'] Com  0 :  ['q1']
    ['q1'] Com  1 :  ['q2']
    ['q2'] Com  0 :  ['q3']
    ['q2'] Com  1 :  ['q2']
    ['q3'] Com  0 :  ['q2']
    ['q3'] Com  1 :  ['q2']

    Estado Inicial:  ['q1']

    Estado(s) Final: 
    ['q2']

    Expressão Regular...

    ER: { (0*11*0(0U1)1*0*(0U1)1*U0*11* }


    Deseja adicionar outro automato?

    [1]-SIM
    [2]-NAO
    Digite: 2   

Outro Exemplo: 
    Informe os estados, separados por , : q1,q2,q3
    Informe o estado inicial: q1
    Informe os estados finais, separdos por , : q1,q2
    Informe o alfabeto, separados por , : 0,1
    Delta(q1,0): q1
    Delta(q1,1): q2
    Delta(q1,ε): -
    Delta(q2,0): q3
    Delta(q2,1): q2
    Delta(q2,ε): -
    Delta(q3,0): q3
    Delta(q3,1): q3
    Delta(q3,ε): -


    AFN ---------> AFD


    Tabela T AFD:

    ['q1'] Com  0 :  ['q1']
    ['q1'] Com  1 :  ['q2']
    ['q2'] Com  0 :  ['q3']
    ['q2'] Com  1 :  ['q2']
    ['q3'] Com  0 :  ['q3']
    ['q3'] Com  1 :  ['q3']

    Estado Inicial:  ['q1']

    Estado(s) Final: 
    ['q1']
    ['q2']

    Expressão Regular...

    ER: { (0*11*U0* }


    Deseja adicionar outro automato?

    [1]-SIM
    [2]-NAO
    Digite: 2

