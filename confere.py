g1 = "CEXCECEECCECCEEECECE"
g2 = "EECECCECECXCXCEECECC"
g3 = "CECECEECECCCECCEEEEE"
g4 = "XECXEECCCEEXXEXCEEEC"
g5 = "CEXECCECEEXCEEECCEEE"
g6 = "CEEECEECXCXEECECEEEC"
gabarito = g1+g2+g3+g4+g5+g6

print (gabarito)

'''
g1 = "10210100110110001010"
g2 = "00101101012121001011"
g3 = "10101001011101100000"
g4 = "20120011100220210001"
g5 = "10201101002100011000"
g6 = "10001001212001010001"
gabarito = g1+g2+g3+g4+g5+g6

r1 = "11111000110112011211"
r2 = "00122201111101221220"
r3 = "00111122021100100100"
r4 = "11110001000122101011"
r5 = "10211101011211121011"
r6 = "11020111001012012001"
resposta = r1+r2+r3+r4+r5+r6

acertosA = sum(1 for a, b in zip(gabarito,resposta) if a == b or a == "2")
acertos = sum(1 for a, b in zip(gabarito,resposta) if a == b and a != "2")
erros = sum(1 for a, b in zip(gabarito,resposta) if a != b and a != "2")
feitas = sum(1 for a, b in zip(gabarito,resposta) if a != 2 and b != "2")

print("Feitas: ",feitas)
print("Acertos: ",acertosA," com anuladas")
print("Acertos: ",acertos," sem anuladas")
print("Erros: ",erros," sem anuladas")
print("Final: ",acertos-erros, " acertos - erros")
'''
