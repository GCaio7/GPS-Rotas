#include "funcoes.h"

int main()
{
    int menuOP=0;
    int processouTempo;
    int existeArqRotas;
    int atualizouTempo=1;

    setlocale(LC_ALL, "portuguese");

    SetConsoleOutputCP(1254);
    SetConsoleCP(1254);
    SetConsoleTitle("PROJETO FINAL - GPS");

    char NomeArqCidades[] = "cidades.dat";
    char NomeArqRotas[] = "rotas.dat";

    do
    {
        VerificarArquivosBase(&processouTempo, &existeArqRotas);
        system("cls");
        cout<<"\t\t\t+--------SELEÇÃO DE MENU--------+"<<endl;
        cout<<"\t\t\t1 - Cidades      "<<endl;
        cout<<"\t\t\t2 - Rotas        "<<endl;
        cout<<"\t\t\t+--------------LP---------------+"<<endl;
        if(existeArqRotas != -1)
            cout<<"\t\t\t3 - Processar Tempo (Haskell)"<<endl;
        if(processouTempo != -1)
            cout<<"\t\t\t4 - Encontrar Caminhos (Prolog)"<<endl;
        cout<<"\t\t\t+-------------------------------+"<<endl;
        cout<<"\t\t\t0 - Sair"<<endl;
        cout<<"\t\t\tOpção: ";
        cin>>menuOP;
        switch(menuOP)
        {
        case 0:
            cout<<"\t\t\tSaindo..."<<endl;
            break;
        case 1:
            system("cls");
            MenuCidades(NomeArqCidades);
            break;
        case 2:
            system("cls");
            MenuRotas(NomeArqRotas);
            atualizouTempo=-1;
            break;
        case 3:
            if(existeArqRotas == 1)
            {
                cout<<"\t\t\tDICA: Utilize a função \"processarTempo\""<<endl;
                system("start tempo.hs");
                atualizouTempo=1;
            }
            else
                cout<<"\t\t\tSem arquivo \"rotas.txt\" para processar com Haskell!"<<endl;
            system("pause");
            break;
        case 4:
            if(processouTempo == 1 && atualizouTempo == 1)
            {
                cout<<"\t\t\tDICA: Utilize primeiro a funcao \"carregarArquivo().\""<<endl;
                system("start caminho.pl");
            }
            else
                cout<<"\t\t\tAtualize o tempo de viagem!\n\t\t\tSelecione a opção 3!"<<endl;
            system("pause");
            break;
        default:
            cout<<"\t\t\tInforme uma opção válida!"<<endl;
            system("pause");
        }
    }while(menuOP!=0);

    return 0;
}
