# João Vitor de Oliveira 
# RGM: 38342
# 2º ano - Ciência da Computação - Linguagens Formais e Autômatos
# Trabalho 3: AFN para ER

import string  #importa a biblioteca String
import os #Contem a função os.system('clear') --> limpa a tela do terminal

#Função que lê os estados
def get_states():
    states = input('Informe os estados, separados por '','' : ').split(",")
    return states

#Função que lê o estado inicial e verifica se o mesmo pertence ao conjuto de estados
def get_state_first(states):
	conf = True
	while(conf):	
		firstState = input('Informe o estado inicial: ')
		if(firstState in states):	#Verificação
			conf = False
		else:
			print("Estado inicial não aceito...")
	return firstState, firstState
  
#Função que lê os estados finais e verifica se o mesmo pertence ao conjunto de estados
def get_state_end(states):
	conf = True
	while(conf):
		endStates = input('Informe os estados finais, separdos por '','' : ').split(",")	
		if(set(endStates).issubset(set(states))): 	#issubset == está contido ou contem
			conf = False
		else:
			print("Estados finais não aceitos...")			
	return endStates

#Função para ler a entrada do Alfabeto
def get_alphabet():
    #entrada do alfabeto
	alphabet = input('Informe o alfabeto, separados por '','' : ').split(",")
	#adiciona o 'ε' no alfabeto
	lenAlphabet = len(alphabet) + 1 
	alphabet.insert(lenAlphabet, 'ε') 
	return alphabet

#Função que monta o nosso Delta
def make_delta(states, alphabet):
	Delta = {}
	for i in states:
		for j in alphabet:
			#entrada do Delta
			conf = True
			while(conf):
				deltaInput = input('Delta(%s,%s): ' %(i,j)).split(",")
				Delta[i,j] = deltaInput
				if( (set(Delta[i,j]).issubset(set(states))) or (set('-').issubset(set(Delta[i,j]))) ):
					conf = False
				else:
					print("Delta não pertence ao conjunto de estados!")
	return Delta

#Função que retorna o aux para montar nosso fecho
def auxMakeLock(auxDelta, delta):
	auxList = []
	auxList = auxDelta
	for x in auxList:
		if("-" not in delta[x,'ε']):
			auxDelta += delta[x,'ε']
	return auxDelta

#Transforma o Delta
def transformDelta(alphabet, auxDelta, Geral, delta):
	for i in alphabet:
		auxGeral = []
		for j in auxDelta:
			if("ε" not in i):
				if("-" not in delta[j,i] ):
					auxGeral += delta[j,i]
				Geral[i] = auxGeral
	return Geral

#Função que monta o fecho 
def makeLock(lock, auxDelta, delta, alphabet):
	auxLock = []
	auxLock = auxMakeLock(auxDelta, delta)

	lock[0] = auxLock 
	x = 0
	conf = True
	while(conf):	
		aux = {}
		if(x <= len(lock)-1):
			aux =  transformDelta(alphabet, lock[(x)], aux, delta)
		
		else:
			conf = False
	
		for j in aux.values():
			auxLock = []
			auxLock = auxMakeLock(j, delta)
			auxLock = sorted(set(auxLock))
			
			if(auxLock not in lock.values()):

				lenLock = len(lock) 
				lock[lenLock] = auxLock
		x = x + 1 		
	return lock

#monta o delta e mostra as transições
def makeDeltaAFD(DeltaAFD, lock, alphabet, delta):
	for i in lock.values():
		for j in alphabet:
			auxDeltaAfd = {}
			auxDeltaAfd = 	transformDelta(j,i,auxDeltaAfd,delta)
			for k in auxDeltaAfd.values():	
				auxList = []
				auxList = auxMakeLock(k, delta)
				auxList = sorted(set(auxList))
			
				DeltaAFD[tuple(i),j] = auxList
			if(i == []):
				DeltaAFD[tuple(i), j] = i		 	

			print(i,"Com ",j,": ", DeltaAFD[tuple(i), j])		
	return DeltaAFD

#acha o novo estado inicial
def newStateFirst(lock):
	return lock[0]

#Acha os novos estados final e retorna uma lista com eles
def newStateEnd(lock, statesEnd, newEnd):
	for i in lock.values():
		for j in statesEnd:
			if( j in i):
				newEnd.append(i)
	return newEnd

#Função que deixa simples o Delta AFD
def simple_AFD(delta, alphabet, lock, states, newEnd):
	newDelta = {}
	keysLock = []
	statesEndAFD = []

	'''
	keys = ( list(lock.keys()) ).copy() 	#lista com as chaves do dicionario de fecho	
	for i in keys: 	
		if(lock[i] == []):	
			del(lock[i])
	'''				
	keysLock = ( list(lock.keys()) ).copy() 	#lista com as chaves do dicionario de fecho

	cont = 0
	for i in lock.values():
		for j in alphabet:
			for x in keysLock:
				if ( delta[tuple(i), j] == lock[x] ):	
					indexLock = x
				for k in newEnd:
					if ( k == lock[x] ):
						if (states[x] not in statesEndAFD):
							statesEndAFD.append(states[x]) #usando o append evita repetições na nossa lista

			newDelta[states[cont], j] = states[indexLock]   
		cont += 1
	return newDelta, statesEndAFD

#Reune todos os dados e retorna o AFD e seus dados
def return_AFD():
	states = get_states()
	statesFirst, auxDelta = get_state_first(states)
	statesEnd = get_state_end(states)
	alphabet = get_alphabet()
	delta = make_delta(states, alphabet)

	#Depois de pegar os dados do nosso AF e montar o delta:
	#Transformar em AFD	
	auxDelta = auxDelta.split(",")

	lock = {}	#nosso fecho
	lock = makeLock(lock, auxDelta, delta, alphabet)	

	newEnd = []
	newEnd = newStateEnd(lock, statesEnd, newEnd)
	newFirst = newStateFirst(lock)


	alphabet.remove('ε')

	print("\n\nAFN ---------> AFD")
	print("\n\nTabela T AFD:\n")
	DeltaAFD = {}
	DeltaAFD = makeDeltaAFD(DeltaAFD, lock, alphabet, delta)

	print("\nEstado Inicial: ", newFirst)

	print("\nEstado(s) Final: ")
	for x in newEnd:
		print(x)		


	#Proximo passo será deixar simples o AFD
	simpleDelta, statesEndAFD =  simple_AFD(DeltaAFD, alphabet, lock, states, newEnd)
	
	stateFirstAFD = states[0]	

	return simpleDelta, stateFirstAFD, statesEndAFD, states, alphabet

def aux_Delta_Modify(alphabet, q, delta):
	aux = {}
	for alpha in alphabet:
		aux[alpha] = delta[q,alpha]
	return aux

#modifica o delta para auxiliar na transformação para ER
def delta_Modify(delta, states, alphabet):
	aux = {}
	for q in states:
		aux[q] = aux_Delta_Modify(alphabet, q, delta)
	return aux

def get_repeated(delta, state):
    for q in delta:
        if delta[q] == state:
            return q

#Adiciona os Parenteses
def add_Parentheses(delta):
    aux = {} 
    for q in delta:
        aux['(' + q + ')'] = delta[q]
    return aux

#Uniao da Expressão
def union(delta):
    aux = {}
    for q in delta:
        if delta[q] not in aux.values():	
            aux[q] = delta[q]
        else:
            new_key = get_repeated(aux, delta[q]) + 'U' + q   #Faz a união
            aux[new_key] = delta[q]
            del aux[get_repeated(aux, delta[q])]  #del serve para deletar elementos

            aux = add_Parentheses(aux)

    return aux

#Ajusta a expressao
def adjust(delta):
    for q in delta:
        delta[q] = union(delta[q])

#Adiciona o Qstart e o Qaccepted
def add_new_states(delta, statesEnd, stateFirst):
    delta['qs'] = {'ε': stateFirst}
    delta['qa'] = {}

    for Qend in statesEnd:
        delta[Qend]['ε'] = 'qa'

#Retorna uma lista com que nao faz loop
def is_not_loop(delta, alpha):
    list_looped = []
    for q in delta[alpha]:
        if delta[alpha][q] != alpha and delta[alpha][q] != '':
            list_looped.append(q)
    return list_looped

#Retorna uma lista com os que faz loop
def is_loop(delta, alpha):
    list_looped = []
    for q in delta[alpha]:
        if delta[alpha][q] == alpha:
            list_looped.append(q)
    return list_looped

#Pega as chaves que fazem loops
def key_loop(key, list_looped):
    new_key = key
    for i in list_looped:
        new_key += i + '*'

    return new_key

#Pega o novo estado
def get_aux(key, delta, list_aux, alpha):
    new_qs = {}
    for i in list_aux:
        new_qs[key + i] = delta[alpha][i]
    return new_qs

def set_qs(delta, alpha, state='qs'):
    list_loop = is_loop(delta, alpha)
    list_not_loop = is_not_loop(delta, alpha)

    new_q = '' #nova chave
    aux = {}	

    for q, j in delta[state].items():
        if j == alpha:
            new_q += key_loop(q, list_loop)
            aux = get_aux(new_q, delta, list_not_loop, alpha)

    for q, j in delta[state].items():
        if j != alpha:
            aux[q] = j
    return aux

def readjust(delta, alpha):
	aux = delta[alpha]
	for key in aux:
		q = delta[alpha][key]
		if q != alpha and q != '':
			for i in delta[q]:
				if i in delta[q] and delta[q][i] == alpha:
					delta[q] = set_qs(delta, alpha, q)
					delta[q] = union(delta[q])

def transform(delta):
    if len(delta) < 3:
        return delta

    qs_state = delta['qs']

    qs_state = sorted(qs_state.keys(), key=len)   #ordena os estados de acordo com o tamanho

    for alfa in qs_state:
        if alfa in delta['qs'] and delta['qs'][alfa] != 'qa':
            last_alfa = delta['qs'][alfa]
            delta['qs'] = set_qs(delta, last_alfa)
            delta['qs'] = union(delta['qs'])

            readjust(delta, last_alfa)

            del delta[last_alfa]
            transform(delta)

#Função que tira os parenteses sobrando, os ε, e os de Uniao 
def simplify_er(er):
	listER = list(filter(None, er.split('ε')))
	lenListER = len(listER)
	newString = ''

	if lenListER > 1:
		for i in range(lenListER):  
			if i + 1 < lenListER:
				if ( not(listER[i][-1] in ['U', ')', '('] and listER[i + 1][0] in ['U', ')', '(']) ):
					newString += listER[i]
	else:
		newString = listER[0]

	return newString


def print_ER(delta):
	print("\nExpressão Regular...\n")
	for q in delta['qs']:
		er = simplify_er(q)
		print("ER: {", er, "}")

def remain(exit):
	print("\n\nDeseja adicionar outro automato?")
	print("\n[1]-SIM")
	print("[2]-NAO")
	validation = True
	while(validation):
		opc = int( input("Digite: ") )
		print(opc)
		if(not ( opc != 1 and opc != 2 ) ):
			validation = False
			if(opc == 1):
				os.system('clear')
			else:
				exit = False
			
		else:
			print("Opcao Invalida...")
	return exit

#main
def start():
	exit = True	
	while(exit):
		Delta, stateFirst, statesEnd, states, alphabet = return_AFD()
	
		new_delta = delta_Modify(Delta, states, alphabet)

		

		adjust(new_delta)
		add_new_states(new_delta, statesEnd, stateFirst)
		transform(new_delta)
		print_ER(new_delta)

		exit = remain(exit)

start()