import os

numero = 0
caminho = "/home/sushi/Imagens/memes"
for nome in os.listdir(caminho):
    try:
        if ".jpg" in nome:
            novo_nome = str(numero) + nome[nome.index('.jpg'):]
        elif ".png" in nome:
            novo_nome = str(numero) + nome[nome.index('.png'):]
        elif ".jpeg" in nome:
            novo_nome = str(numero) + nome[nome.index('.jpeg'):]
        os.rename(caminho+'/'+nome, caminho+'/'+novo_nome)
        numero = numero + 1
    except Exception, e:
        numero = numero - 1
        print "ERRO ", e
print 'OK'