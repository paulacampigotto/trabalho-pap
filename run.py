from flask import Flask, render_template
from flask import request
import os
import io
import sys

app = Flask(__name__)
global retornoTemplate
reload(sys)
sys.setdefaultencoding('utf8')

html = io.open('accessed.html', 'r+', encoding="utf-8")
texto = html.read()
html.close()


retornoTemplate = texto


@app.route('/')
def home():
    return render_template('home.html')

@app.route('/accessed')
def something():
    global retornoTemplate


    return retornoTemplate

@app.route('/getRegisters/nome=<string:nome>&cpf=<string:cpf>&tipo=<string:tipo>', methods=['GET', 'POST'])
def req(nome, cpf, tipo):
    global retornoTemplate
    permissao = 'Professor'
    if(tipo == 2):
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

    return "<h1> Requisicao recebida pelo servidor! </h1>"
