#include <iostream>
#include <list>
#include <curl/curl.h>
#include <string.h>
using namespace std;


class Pessoa {
	int permissao;
	string nome, cpf;
  public:
    string getCpf() { return cpf; }
	string getNome() { return nome; }
	int getPermissao() { return permissao; }
	void setNome(string nome) { this->nome = nome; }
	void setCpf(string cpf) { this->cpf = cpf; }
	void setPermissao(int p) { permissao = p; }
};

class Professor : public Pessoa {
public:
	Professor(string nome, string cpf){
		setNome(nome);
	  	setCpf(cpf);
		setPermissao(1);
	}
};

class Aluno : public Pessoa {
public:
	Aluno(string nome, string cpf){
		setNome(nome);
	  	setCpf(cpf);
		setPermissao(2);
	}
};

class Servidor : public Pessoa {
public:
	Servidor(string nome, string cpf){
		setNome(nome);
	  	setCpf(cpf);
		setPermissao(3);
	}
};


list<Pessoa> cadastrar(list<Pessoa>);
void lista(list<Pessoa>);
void catracas(list<Pessoa>);
void requisicao(string, string, string);
list<Pessoa> menu(list<Pessoa>);


int main () {

	list<Pessoa> cadastro;

	cadastro = menu(cadastro);

  return 0;
}


list<Pessoa> cadastrar(list<Pessoa> cadastro){
	string nome, cpf;
	int tipo;

	cout << endl << "CPF: ";
	cin >> cpf;
	cout << "Nome: ";
	cin >> nome;
	cout << endl << "Tipo de cadastro: \n 1. Professor\n 2. Aluno\n 3. Servidor\n ->";
	cin >> tipo;

	if(tipo == 1){
		Professor p (nome, cpf);
		cadastro.push_back(p);
	} else if(tipo == 2){
		Aluno a (nome, cpf);
		cadastro.push_back(a);
	} else if(tipo == 3){
		Servidor s (nome, cpf);
		cadastro.push_back(s);
	} else cout << "Numero invalido" << endl;

	return cadastro;
}

void lista(list<Pessoa> cadastro){
	list<Pessoa>::iterator it;

	cout << "\n\n>>> Lista de cadastro <<<\n\n";

	for(it = cadastro.begin(); it != cadastro.end(); it++){
		cout << "nome: " << it->getNome() << endl << "cpf: " << it->getCpf() << endl;
		cout << "Tipo de cadastro: "<< it->getPermissao() << endl << endl;
	}
}

void requisicao(string nome, string cpf, string tipo){

	CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

	string url1 = "http://127.0.0.1:5000/getRegisters/nome=" + nome + "&cpf=" + cpf + "&tipo=" + tipo;

	char url[url1.size() + 1];

	strcpy(url, url1.c_str());

    if(curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      res = curl_easy_perform(curl);
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void catracas(list<Pessoa> cadastro){
	list<Pessoa>::iterator it;
	string cpf;
	int key;

	cout << ">>> Catracas <<<" << endl << endl;
	cout << "CPF: ";
	cin >> cpf;


	for(it = cadastro.begin(); it != cadastro.end(); it++){
		if(cpf.compare(it->getCpf()) == 0){
			cout << endl << endl << "Usuario: " << it->getNome();
			cout << endl << endl << "1. Catraca dos professores" <<endl;
			cout << "2. Catraca dos alunos" << endl;
			cout << "3. Catraca dos servidores" << endl << endl << "-> ";
			cin >> key;

			if(key == 1 && it->getPermissao() == 1){
				cout << "Acesso Autorizado!\n" << endl;
				requisicao(it->getNome(), it->getCpf(), "1");
				return;
			}else if(key == 2 && it->getPermissao() == 2){
				cout << "Acesso Autorizado!\n" << endl;
				requisicao(it->getNome(), it->getCpf(), "2");
				return;
			}else if(key == 3 && it->getPermissao() == 3){
				cout << "Acesso Autorizado!\n" << endl;
				requisicao(it->getNome(), it->getCpf(), "3");
				return;
			}else cout << "Acesso negado!\n" << endl; return;
		}
	}
	cout << "CPF não cadastro!\n" << endl;
}

list<Pessoa> menu(list<Pessoa> cadastro){

	while(1){
		int key;

		cout << "\n>>>>>>> MENU <<<<<<<" << endl << endl;
		cout << "1. Cadastrar novo usuario" << endl;
		cout << "2. Catracas" << endl;
		cout << "3. Listar cadastro" << endl;
		cout << "4. Sair" <<endl << endl << "->";

		cin >> key;

		switch(key){
			case 1:
				cadastro = cadastrar(cadastro);
			break;
			case 2:
				catracas(cadastro);
			break;
			case 3:
				lista(cadastro);
			break;
			case 4:
				exit(0);
			break;
		}
	}
	return cadastro;
}
