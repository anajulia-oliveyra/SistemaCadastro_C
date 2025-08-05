#include<iostream>
#include<stdio.h>
#include<string>

using namespace std;

int main(){

    struct{
        string nome;
        string cpf;
        string email;
        int idade;

        void imprimir(){
            cout<<"Nome:"<< nome<< endl;
            cout<<"CPF: " << cpf<< endl;
            cout<<"Email: "<<email<<endl;
            cout<<"Idade: "<< idade <<endl;

        }
    } pessoa1;

    cout<<"Nome do cliente:"<<endl;
    getline(cin, pessoa1.nome);
    cout<<"CPF do cliente: "<< endl;
    getline(cin,pessoa1.cpf);
    cout<<"E-mail do cliente:"<< endl;
    getline(cin,pessoa1.email);
    cout<<"Idade do cliente: "<< endl;
    cin>>pessoa1.idade;

    pessoa1.imprimir();

    return 0;
}