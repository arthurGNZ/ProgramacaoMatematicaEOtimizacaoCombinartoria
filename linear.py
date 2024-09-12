from pulp import *

class Retangulo:
    def __init__(self, id, x1, y1, x2, y2):
        self.id = id
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2
    def ha_sobreposicao(self,r):    
        if self.x2 < r.x1 or r.x2 < self.x1:
            return False
        if self.y2 < r.y1 or r.y2 < self.y1:
            return False
        return True

modelo = LpProblem("Problema dos Rótulos", LpMaximize)#objeto que representa problema de prog linear. 1 parametro: nome do problema, 2 parametros: se é de maximização ou minimização
num_rotulos = int(input())
#variaveis do problema
x = LpVariable.dicts("x", range(num_rotulos), 0, 1, LpInteger)
#restrições:
retangulos = []
for i in range(num_rotulos):
    entrada = input().split(" ")
    indice, x1, y1, x2, y2 = map(int, entrada)
    retangulos.append(Retangulo(indice, x1,y1,x2,y2))
    if(len(retangulos)>1):
        for j in range(0, len(retangulos)-1):
            if(retangulos[i].ha_sobreposicao(retangulos[j])):
                modelo+=(x[j]+x[i]<=1)
#função objetivo:
modelo += (lpSum([x[i] for i in range(num_rotulos)]), "Funcao objetivo")
#Fazendo a biblioteca resolver o problema:
modelo.solve()
#exibindo valor ótimo da função objetivo:
print("Valor ótimo:", value(modelo.objective))
#impressão das variáveis
for x in modelo.variables():
    print(x.name,"=", x.value())
