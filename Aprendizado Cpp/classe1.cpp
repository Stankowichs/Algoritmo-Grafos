#include <iostream>

using namespace std;

class Pessoa {
    private:
        string nome;
        int idade;

    public:
    //Construtor
    Pessoa(string n, int i){
        nome = n;
        idade = i;
    }

    //Método para imprimir os dados
    void apresentar(){
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << " anos" << endl;
    }
};

int main(){
    Pessoa p1("Ana", 25);
    Pessoa p2("Bruno", 19);

    p1.apresentar();
    p2.apresentar();

    return 0;
}