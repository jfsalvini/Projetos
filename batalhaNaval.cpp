#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

void menuInicial();


void limpaTela(){
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]){

    int linha,coluna;
    for(linha = 0; linha < 10; linha++){
         for(coluna = 0; coluna < 10; coluna++){
            tabuleiro[linha][coluna] = 'A';
            mascara[linha][coluna] = '*';
         }
    }

}

void exibeMapa(){
    int cont;
    for(cont = 0; cont < 10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << cont << " ";
    }
    cout << "\n";
    for(cont = 0; cont < 10; cont++){
        if(cont == 0){
            cout << "     ";
        }
        cout << "| ";
    }
    cout << "\n";

}

void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito){


    char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
    char green[] = { 0x1b, '[', '1', ';', '3', '2', 'm', 0 };
    char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 };

    int linha,coluna;
    for(linha = 0; linha < 10; linha++){
         cout << linha << " - ";
         for(coluna = 0; coluna < 10; coluna++){

            switch(mascara[linha][coluna]){
                case 'A':
                    cout << blue << " " <<mascara[linha][coluna] << normal;
                    break;
                case 'P':
                    cout << green << " " <<mascara[linha][coluna] << normal;
                    break;
                default:
                    cout << " " <<mascara[linha][coluna];
                    break;
            }

         }
         cout << "\n";
    }

    if(mostraGabarito == true){
        for(linha = 0; linha < 10; linha++){
             for(coluna = 0; coluna < 10; coluna++){
                 cout << " " <<tabuleiro[linha][coluna];
             }
             cout << "\n";
        }
    }


}

void posicionaBarcos(char tabuleiro[10][10]){

    int cont, quantidade = 10, quantidadePosicionada = 0;

    while(quantidadePosicionada < quantidade){

        int linhaAleatoria = rand() % 10;
        int colunaAleatoria = rand() % 10;

        if(tabuleiro[linhaAleatoria][colunaAleatoria] == 'A'){

            tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';

            quantidadePosicionada++;

         }

    }

}

void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){

    switch(tabuleiro[linhaJogada][colunaJogada]){
        case 'P':
            *pontos = *pontos + 10;
            *mensagem = "Voce acertou um barco pequeno! (10 pts)";
            break;
        case 'A':
            *mensagem = "Voce acertou a agua";
            break;
    }

}

void jogo(string nomeDoJogador){

    ///Vari�veis Gerais
    char tabuleiro[10][10],mascara[10][10];
    int linha,coluna;
    int linhaJogada, colunaJogada;
    int estadoDeJogo = 1;
    int pontos = 0;
    int tentativas = 0, maximoDeTentativas = 5;
    int opcao;
    string mensagem = "Bem vindo ao jogo!";

    iniciaTabuleiro(tabuleiro,mascara);

    posicionaBarcos(tabuleiro);

    while(tentativas < maximoDeTentativas){

        limpaTela();

        exibeMapa();

        exibeTabuleiro(tabuleiro,mascara, false);

        cout << "\nPontos:" << pontos << ", Tentativas Restantes:" << maximoDeTentativas - tentativas;
        cout << "\n" << mensagem;

        linhaJogada = -1;
        colunaJogada = -1;

        while( (linhaJogada < 0 || colunaJogada < 0) ||  (linhaJogada > 9 || colunaJogada > 9)) {

            cout << "\n" << nomeDoJogador << ", digite uma linha:";
            cin >> linhaJogada;
            cout <<  "\n" << nomeDoJogador << ", digite uma coluna:";
            cin >> colunaJogada;

        }

        verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);

        mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];

        tentativas++;

    }

    cout << "Fim de jogo, o que deseja fazer?";
    cout << "\n1-Jogar Novamente";
    cout << "\n2-Ir para o Menu";
    cout << "\n3-Sair";
    cin >> opcao;
    switch(opcao){
        case 1:
            jogo(nomeDoJogador);
            break;
        case 2:
            menuInicial();
            break;
           }

}

void menuInicial(){

    int opcao = 0;

    string nomeDoJogador;

    while(opcao < 1 || opcao > 3){
        limpaTela();
        cout << "Bem vindo ao Jogo de Batalha Naval";
        cout << "\n1 - Jogar";
        cout << "\n2 - Sobre";
        cout << "\n3 - Sair";
        cout << "\nEscolha uma opcao e tecle ENTER:";

        cin >> opcao;

        switch(opcao){
            case 1:
                cout << "Qual seu nome?";
                cin >> nomeDoJogador;
                jogo(nomeDoJogador);
                break;
            case 2:
                cout << "Informacoes do jogo";
                limpaTela();
                cout << "Jogo desenvolvido por Jorge em 2023";
                cout << "\n1 - Voltar";
                cout << "\n2 - Sair";
                cin >> opcao;
                if(opcao == 1){
                    menuInicial();
                }

                break;
            case 3:
                cout << "Ate mais!";
                break;
        }
    }

}

int main(){

    srand((unsigned)time(NULL));

    menuInicial();
    return 0;
}
