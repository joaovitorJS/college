import os #Contem a função os.system('clear') --> limpa a tela do terminal
#
#
# Aluno: JOÃO VITOR DE OLIVEIRA
# Rgm: 	38342
#
#


def fecho(auxDelta, Delta):
	auxdoaux = []
	auxdoaux = auxDelta
	for b in auxdoaux:
		if("-" not in Delta[b,'ε']):
			auxDelta += Delta[b,'ε']

	return auxDelta

def transformDelta(alfabeto, auxDelta, Geral, Delta):
	for i in alfabeto:
		auxGeral = []
		for j in auxDelta:
			if("ε" not in i):
				if("-" not in Delta[j,i] ):
					auxGeral += Delta[j,i]
				Geral[i] = auxGeral

	return Geral

def montaFecho(Fecho):
	auxfecho = []
	auxfecho = fecho(auxDelta, Delta)

	Fecho[0] = auxfecho 
	x = 0
	conf = True
	while(conf):	
		aux = {}
		if(x <= len(Fecho)-1):
			aux =  transformDelta(alfabeto, Fecho[(x)], aux, Delta)
		
		else:
			conf = False
	
		for j in aux.values():
			auxfecho = []
			auxfecho = fecho(j, Delta)
			auxfecho = sorted(set(auxfecho))
			
			if(auxfecho not in Fecho.values()):

				tam = len(Fecho) 
				Fecho[tam] = auxfecho
		x = x + 1 	
	
	return Fecho

#monta o delta e mostra as transições
def montaDeltaAFD(DeltaAFD, Fecho):
	for i in Fecho.values():
		for j in alfabeto:
			auxDeltaAfd = {}
			auxDeltaAfd = 	transformDelta(j,i,auxDeltaAfd,Delta)
			for k in auxDeltaAfd.values():	
				teste = []
				teste = fecho(k, Delta)
				teste = sorted(set(teste))
			
				DeltaAFD[tuple(i),j] = teste
			if(i == []):
				DeltaAFD[tuple(i), j] = i		 	

			print(i,"Com ",j,": ", DeltaAFD[tuple(i), j])		
	return DeltaAFD

#acha o novo estado inicial
def novoEstadoInicial(Fecho):
	return Fecho[0]

#Acha os novos estados final e retorna uma lista com eles
def novoEstadoFinal(Fecho, estadofinal, newFinal):

	for i in Fecho.values():
		for j in estadofinal:
			if( j in i):
				newFinal.append(i)

	return newFinal

sair1 = True
while(sair1):
	#limpa a tela do terminal
	os.system('clear')
	
	#entrada dos estados
	estados = input('Informe os estados, separados por '','' : ').split(",")

	#Validação do estado inicial		
	conf = True
	while(conf):	
		#entrada do estado incial
		estadoinicial = input('Informe o estado inicial: ')
		if(estadoinicial in estados):
			conf = False
		else:
			print("Estado inicial não aceito")

	#Validacão dos estados finais
	conf = True
	while(conf):
		#entrada dos estados finais
		estadofinal = input('Informe os estados finais, separdos por '','' : ').split(",")	
		if(set(estadofinal).issubset(set(estados))): 	#issubset == está contido ou contem
			conf = False
		else:
			print("Estados finais não aceitos")	

	#entrada do alfabeto
	alfabeto = input('Informe o alfabeto, separados por '','' : ').split(",")

	#adiciona o 'ε' no alfabeto
	tamAlfa = len(alfabeto) + 1 
	alfabeto.insert(tamAlfa, 'ε') 

	#Validação do Delta
	Delta = {}
	for i in estados:
		for j in alfabeto:
			#entrada do Delta
			conf = True
			while(conf):
				deltaIN = input('Delta(%s,%s): ' %(i,j)).split(",")
				Delta[i,j] = deltaIN
				if( (set(Delta[i,j]).issubset(set(estados))) or (set('-').issubset(set(Delta[i,j]))) ):
					conf = False
				else:
					print("Delta não pertence ao conjunto de estados!")

	auxDelta = estadoinicial
	auxDelta = auxDelta.split(",")

	Fecho = {}
	Fecho = montaFecho(Fecho)	

	newFinal = []
	newFinal = novoEstadoFinal(Fecho, estadofinal, newFinal)
	newInicial = novoEstadoInicial(Fecho)


	alfabeto.remove('ε')

	print("\n\nAFN ---------> AFD")
	print("\n\nTabela T AFD:\n")
	DeltaAFD = {}
	DeltaAFD = montaDeltaAFD(DeltaAFD, Fecho)

	print("\nEstado Inicial: ", newInicial)

	print("\nEstado(s) Final: ")
	for n in newFinal:
		print(n)

	sair2 = True
	while(sair2):
		print("\n")
		#validacao da string
		conf = True
		while(conf):
			#entrada da string
			string = input('Informe a Palavra: ')
			if(set(string).issubset(set(alfabeto))):  #issubset == esta contido ou contem
				conf = False
			else:
				print("Palavra com caracter nao pertencente ao alfabeto!")

		#validação da string
		aceito = newInicial
		for s in string:
			det = aceito
			aceito = DeltaAFD[tuple(det),s]
			print(det,"-->",s,"-->",aceito)

		validacao = 1
		for n in newFinal:
			if aceito == n:
				print("Palavra aceita!")
				validacao = 1
				break
			else:
				validacao = 0
		if validacao == 0:
			print("Palavra nao aceita!")		

		#verificação para inserir ou nao mais uma palavra
		print("\n\nDeseja inserir outra Palavra? ")
		print("[1]-SIM")
		print("[2]-NAO")
		aux2 = int(input())
		if (aux2 == 1):
			sair2 = True	#continua
		else:
			sair2 = False	#sai 

#verificação para inserir ou nao mais um AFN
	print("\n\nDeseja inserir outro AFN? ")
	print("[1]-SIM")
	print("[2]-NAO")
	aux = int(input())
	if (aux == 1):
		sair1 = True	#continua
	else:
		sair1 = False	#encerra

