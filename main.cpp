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

void editarCliente(){
    string nomeCliente;
    cout<<"Digite o nome do cliente que voce quer editar:"<<endl;
    cin.ignore();
    getline(cin,nomeCliente);

    ifstream arquivoAntigo("clientes_cadastrados.txt");

    if(arquivoAntigo.is_open()){
        string linha;
        string arquivoTemporario = "temp.txt";
        ofstream arquivoNovo(arquivoTemporario,ios::app);

        if(arquivoNovo.is_open()){
            bool clienteEncontrado=false;

            while(getline(arquivoAntigo,linha)){
                size_t posicao = linha.find(nomeCliente);

                if(posicao!=string::npos){
                    clienteEncontrado=true;

                    cout<<"Cliente encontrado: "<<linha<< endl;

                    Cliente clienteEditado;
                    size_t pos1=linha.find(",");
                    size_t pos2=linha.find(",",pos1+1);
                    size_t pos3=linha.find(",",pos2+1);

                    clienteEditado.nome=linha.substr(0,pos1);
                    clienteEditado.cpf=linha.substr(pos1+1,pos2-pos1-1);
                    clienteEditado.email=linha.substr(pos2+1,pos3-pos2-1);
                    clienteEditado.idade=stoi(linha.substr(pos3+1));

                    int opcao=0;
                    do{
                        cout << "\nO que deseja editar?\n";
                        cout << "1. Nome\n";
                        cout << "2. CPF\n";
                        cout << "3. E-mail\n";
                        cout << "4. Idade\n";
                        cout << "0. Finalizar edição\n";
                        cout << "Escolha: ";
                        cin >> opcao;
                        cin.ignore();

                        switch(opcao){
                            case 1:
                                cout<<"Novo nome:"<<endl;
                                getline(cin,clienteEditado.nome);
                                break;
                            case 2:
                                cout<<"Novo cpf: "<<endl;
                                getline(cin,clienteEditado.cpf);
                                break;
                            case 3:
                                cout<<"Novo email:"<<endl;
                                getline(cin,clienteEditado.email);
                                break;
                            case 4: 
                                cout<<"Nova idade:" <<endl;
                                getline(cin,clienteEditado.idade);
                                break;
                            case 0:
                                break;
                            default:
                                cout<<"Opção inválida!"<<endl;
                        }
                    } while(opcao !=0);

                    arquivoNovo<<clienteEditado.nome<<endl;
                    arquivoNovo<<clienteEditado.cpf<<endl;
                    arquivoNovo<<clienteEditado.email<<endl;
                    arquivoNovo<<clienteEditado.idade<<endl;

                }
            }
        }
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