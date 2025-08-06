//Código inspirado em https://alonza.com.br/projetos-em-c-mais-mais//
#include<iostream>
#include<stdio.h>
#include<string>
#include<fstream>

using namespace std;

struct Cliente{
    string nome;
    string cpf;
    string email;
    int idade;
};

void CadastrarCliente(){
    Cliente cliente;

    cout<<"Nome do cliente:"<<endl;
    cin.ignore();
    getline(cin, cliente.nome);
    cout<<"CPF do cliente: "<< endl;
    cin.ignore();
    getline(cin,cliente.cpf);
    cout<<"E-mail do cliente:"<< endl;
    cin.ignore();
    getline(cin,cliente.email);
    cout<<"Idade do cliente: "<< endl;
    cin.ignore();
    cin>>cliente.idade;

    ofstream arquivo("clientes_cadastrados.txt",ios::app);

    if (arquivo.is_open())
    {
        arquivo<<cliente.nome<<","<<cliente.cpf<<","<<cliente.email<<","<<cliente.idade<<endl;
        arquivo.close();

        cout<<"Cliente cadastrado com sucesso!"<<endl;
    } else{
        cout<<"Erro ao abrir o arquivo";    
    }
     
}

void listarCliente(){
    ifstream arquivo("clientes_cadastrados.txt");

    if(arquivo.is_open()){
        string linha;

        while(getline(arquivo,linha)){
            cout<<linha<<endl;
        }

        arquivo.close();
    } else{
        cout<<"Erro ao abrir o arquivo"<<endl;
    }
}

void excluirCliente(){
    string nomeCliente;
    cout<< "Digite o nome do cliente que deseja excluir: "<<endl;
    cin.ignore();
    getline(cin, nomeCliente);

    ifstream arquivoAntigo("clientes_cadastrados.txt");

    if(arquivoAntigo.is_open()){
        string linha;
        string arquivoTemporario="temp.txt";

        ofstream arquivoNovo(arquivoTemporario,ios::app);

        if(arquivoNovo.is_open()){
            while(getline(arquivoAntigo,linha)){
                size_t posicao=linha.find(nomeCliente);
                if(posicao==string::npos){
                    arquivoNovo<<linha<<endl;
                }
            }

            arquivoAntigo.close();
            arquivoNovo.close();

            remove("clientes_cadastrados.txt");
            rename("temp.txt","clientes_cadastrados.txt");

            cout<<"Cliente excluido com sucesso"<<endl;
        } else{
            cout<<"Erro ao abrir o arquivo temporario"<<endl;
        }
    } else{
        cout<<"Erro ao abrir o arquivo antigo"<<endl;
    }
}

int main(){

    cout<<"Sistema Cliente:";
    CadastrarCliente();
    excluirCliente();

    return 0;
}