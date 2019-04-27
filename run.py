from flask import Flask, render_template
from flask import request
import os
import io
import sys

app = Flask(__name__)
global retornoTemplate
global cont
cont = 0
reload(sys)
sys.setdefaultencoding('utf8')
html = io.open('accessed.html', 'r+', encoding="utf-8")
texto = html.read()
html.close()
retornoTemplate = texto

@app.route('/')
def home():
    return render_template('home.html')

@app.route('/totalaccessed')
def total():
    global cont
    return """

    <!DOCTYPE html>
    <html>
    <body style="background-color:powderblue;">
    	<style>
    		div.a {
    			text-align: center;
    		}
    	</style>
    	<div class="a">
    		<h2> """ + str(cont) + """ acessos nas catracas</h2>
    		<br><br>
    	</div>
    </body>
    </html>

"""

@app.route('/accessed')
def something():
    global retornoTemplate
    return retornoTemplate

@app.route('/getRegisters/nome=<string:nome>&cpf=<string:cpf>&tipo=<int:tipo>', methods=['GET', 'POST'])
def req(nome, cpf, tipo):
    global retornoTemplate
    global cont
    permissao = ''
    if(tipo == 1):
        permissao = 'Professor'
    elif(tipo == 2):
        permissao = 'Aluno'
    elif(tipo == 3):
        permissao = 'Servidor'

    linha = '\n<tr>\n<td>\n' + nome + '\n</td>\n<td>\n' + cpf + '\n</td>\n<td>\n' + permissao + '\n</td>\n</tr>\n</table>\n'


    html = io.open('accessed.html', 'r+', encoding="utf-8")
    texto = html.read().split('</table>')
    html.close()

    html = io.open('accessed.html', 'r+', encoding="utf-8")
    html.writelines(texto[0] + linha+ texto[1])
    html.close()

    retornoTemplate = texto[0] + linha+ texto[1]
    cont =cont+ 1

    return "<h1> Requisicao recebida pelo servidor! </h1>"
