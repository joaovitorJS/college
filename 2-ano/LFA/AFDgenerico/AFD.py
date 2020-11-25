#
#
# Aluno: JOÃO VITOR DE OLIVEIRA
# Rgm: 	38342
#
#

sair1 = True
while(sair1):
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
	
	#Validação do Delta
	Delta = {}
	for i in estados:
		for j in alfabeto:
			#entrada do Delta
			conf = True
			while(conf):
				Delta[i,j]  = input('Delta(%s,%s): ' %(i,j))
				if(Delta[i,j] in estados):
					conf = False
				else:
					print("Delta não pertence ao conjunto de estados!")
	
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
		aceito = estadoinicial
		for s in string:
				det = aceito
				aceito = Delta[det,s]
				print(det,"-->",s,"-->",aceito)

		if aceito in estadofinal:
			print("Palavra aceita!")
		else:
			print("Palavra não aceita!")


		#verificação para inserir ou nao mais uma palavra
		print("\n\nDeseja inserir outra Palavra? ")
		print("[1]-SIM")
		print("[2]-NAO")
		aux2 = int(input())
		if (aux2 == 1):
			sair2 = True	#continua
		else:
			sair2 = False	#sai 

	#verificação para inserir ou nao mais uma maquina
	print("\n\nDeseja inserir outra maquina? ")
	print("[1]-SIM")
	print("[2]-NAO")
	aux = int(input())
	if (aux == 1):
		sair1 = True	#continua
	else:
		sair1 = False	#encerra

