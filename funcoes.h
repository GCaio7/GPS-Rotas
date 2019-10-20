#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <locale.h>

#include "structs.h"

using namespace std;

//{PROTÓTIPOS

//{FUNCOES COMUNS (CIDADE E ROTA)
int ObterHash(int chave, int tamanho);
bool CodigoExiste(int codigo, char *nomeArquivo);
int vrfQtdRegistros(char *nomeArquivo);
void AvisoErros(int* qtdErros, char* nomeArquivo);
void GravarArquivo(Cidade *cidade, Rota *rota, char *nomeArquivo);
void VerificarArquivosBase(int* processouTempo, int *existeRotas);
//}
/////////////////////////////////////////////////////////////////////

//{FUNCOES CIDADE
void MenuCidades(char* NomeArqCidades);
Cidade ProcurarCidade(int codigo, char* nomeArquivo);
bool CidadeExiste(Cidade cidade, char* nomeArquivo);
void ExibirCidade(Cidade cidade);
void ExibirCidades(Cidade cidade, char* nomeArquivo);
void setCodigoCidade(Cidade* cidade, char* nomeArquivo);
void setNomeCidade(Cidade* cidade, char* nomeArquivo);
void CadastrarCidade(Cidade cidade, char* nomeArquivo);
void EditarCidade(Cidade cidade, char* nomeArquivo);
void bubbleSortC(Cidade *cidade, int qtdElementos);
void OrdenarCidades(char* nomeArquivo, Cidade cidade, int qtdReg);
void RegravarArqCidade(char* nomeArquivo);
void ExcluirCidade(Cidade cidade, char* nomeArquivo);
//}
/////////////////////////////////////////////////////////////////////

//{FUNCOES ROTA
void MenuRotas(char* NomeArqRota);
Rota PesquisarRota(int codigo, char *nomeArquivo);
void RegravarArqRota(char* nomeArquivo);
void EditarRota(Rota rota, char* nomeArquivo);
void ExibirRotas(Rota rota, char* nomeArquivo);
void ExibirRota(Rota rota);
bool RotaExiste(Rota rota, char* nomeArquivo);
bool RotaExiste2(Rota rota, char* nomeArquivo);
void setCodigoCadastro(Rota* rota, char* nomeArquivo);
void setCidadeOrigem(Rota* rota, char* arqCidade);
void setCidadeDestino(Rota* rota, char* arqCidade);
void setDistancia(Rota *rota, char* nomeArquivo);
void CadastrarRota(Rota rota, char* nomeArquivo);
void ExcluirRota(Rota rota, char* nomeArquivo);
void bubbleSortR(Rota* rota, int qtdElementos);
void OrdenarRotas(char* nomeArquivo, Rota rota, int qtdReg);
//}

//}
/////////////////////////////////////////////////////////////////////

//{FUNÇÕES COMUNS (CIDADE E ROTA)
int ObterHash(int chave, int tamanho)
{
    double A = 0.6180339887;
    double valor = chave*A;
    valor = valor - (int) valor;
    return (int) (tamanho*valor);
}

bool CodigoExiste(int codigo, char *nomeArquivo)
{
    FILE* arquivo;
    bool achou=false;

    if(strcmp(nomeArquivo, "cidades.dat")==0)
    {
        Cidade cidade;
        arquivo = fopen(nomeArquivo, "rb");
        if(arquivo==NULL)
        {
            fclose(arquivo);
            return achou;
        }
        while(fread(&cidade, sizeof(Cidade), 1, arquivo)==1)
            if(cidade.codigo==codigo)
                achou = true;

        fclose(arquivo);
        return achou;
    }
    else //if(strcmp(nomeArquivo, "rotas.dat")==0)
    {
        Rota rota;
        arquivo = fopen(nomeArquivo, "rb");
        if(arquivo==NULL)
        {
            fclose(arquivo);
            return achou;
        }
        while(fread(&rota, sizeof(rota), 1, arquivo)==1)
            if(rota.codigo_hash==ObterHash(codigo, TamTabelaHash))
                if(rota.codigo_cadastro==codigo)
                    achou = true;

        fclose(arquivo);
        return achou;
    }
}

int vrfQtdRegistros(char *nomeArquivo)
{
    FILE *arquivo;
    int qtdRegistros=0;
    if(strcmp(nomeArquivo, "cidades.dat")==0)
    {
        arquivo = fopen(nomeArquivo, "rb");
        Cidade temp;
        if(arquivo==NULL)
        {
            fclose(arquivo);
            return 0;
        }
        else
        {
            while(!feof(arquivo))
                if(fread(&temp, sizeof(Cidade),1,arquivo)==1)
                    qtdRegistros++;

            fclose(arquivo);
            return qtdRegistros;
        }
    }
    else //if(strcmp(nomeArquivo, "rotas.dat")==0)
    {
        arquivo = fopen(nomeArquivo, "rb");
        Rota temp;

        if(arquivo==NULL){
            fclose(arquivo);
            return 0;
        }
        else
        {
            while(!feof(arquivo))
                if(fread(&temp, sizeof(Rota),1,arquivo)==1)
                    qtdRegistros++;

            fclose(arquivo);
            return qtdRegistros;
        }
    }
}

void AvisoErros(int* qtdErros, char* nomeArquivo)
{
    char opc;

    cout<<"\n\t\t\tVocê inseriu muitas vezes códigos já existentes.\n\t\t\tDeseja visualizar todos os registros[S/N]?->";
    cin>>opc;

    if(strcmp(nomeArquivo, "cidades.dat")==0)
    {
        Cidade cidade;

        if(opc=='S'||opc=='s')
        {
            cout<<"\t\t\t======================================"<<endl;
            ExibirCidades(cidade, nomeArquivo);
            cout<<"\t\t\t======================================"<<endl<<endl;
        }
        *qtdErros=0;
    }
    else //if(strcmp(nomeArquivo, "rotas.dat")==0)
    {
        Rota rota;

        if(opc=='S'||opc=='s')
        {
            cout<<"\t\t\t======================================"<<endl;
            ExibirRotas(rota, nomeArquivo);
            cout<<"\t\t\t======================================"<<endl<<endl;
        }
        *qtdErros=0;
    }
}

void GravarArquivo(Cidade *cidade, Rota *rota, char *nomeArquivo)
{
    FILE* arquivo;

    if(strcmp(nomeArquivo, "cidades.dat")==0)
    {
        arquivo = fopen(nomeArquivo, "ab");
        fwrite(cidade, sizeof(Cidade), 1, arquivo);
        fclose(arquivo);
    }
    else //if(strcmp(nomeArquivo, "rotas.dat")==0)
    {
        arquivo = fopen(nomeArquivo, "ab");
        fwrite(rota, sizeof(Rota), 1, arquivo);
        fclose(arquivo);

        arquivo = fopen("rotas.txt", "a");

        setlocale(LC_ALL, "english");

        fprintf(arquivo, "%s\n%s\n%0.1f\n", rota->origem.nome, rota->destino.nome, rota->distancia);
        fprintf(arquivo, "%s\n%s\n%0.1f\n", rota->destino.nome, rota->origem.nome, rota->distancia);

        setlocale(LC_ALL, "portuguese");

        fclose(arquivo);
    }
}

void VerificarArquivosBase(int* processouTempo, int *existeRotas)
{
        *processouTempo = 1;
        *existeRotas = 1;

        FILE *tmp = fopen("TempoDeViagem.txt", "r");
        FILE *tmp2 = fopen("rotas.txt", "r");

        if(tmp==NULL)
            *processouTempo=-1;

        if(tmp2==NULL)
            *existeRotas=-1;

        fclose(tmp);
        fclose(tmp2);
}
//}
////////////////////////////////////////////////////////

//{FUNÇÕES DE CIDADE
void MenuCidades(char* NomeArqCidades)
{
    int opc=0;
    Cidade cidade;
    do
    {
        system("cls");
        cout<<"\t\t\t+---------MENU CIDADES---------+"<<endl;
        cout<<"\t\t\t1 - Cadastrar Cidade"<<endl;
        cout<<"\t\t\t2 - Exibir Cidades"<<endl;
        cout<<"\t\t\t3 - Editar Cidade"<<endl;
        cout<<"\t\t\t4 - Excluir Cidade"<<endl;
        cout<<"\t\t\t5 - Ordenar Cidades pelo código"<<endl;
        cout<<"\t\t\t0 - Voltar ao Menu de Seleção"<<endl;
        cout<<"\t\t\tOpção: ";
        cin>>opc;
        switch(opc)
        {
        case 0:
            break;
        case 1:
            system("cls");
            CadastrarCidade(cidade, NomeArqCidades);
            system("pause");
            break;
        case 2:
            system("cls");
            ExibirCidades(cidade, NomeArqCidades);
            system("pause");
            break;
        case 3:
            system("cls");
            EditarCidade(cidade, NomeArqCidades);
            system("pause");
            break;
        case 4:
            system("cls");
            ExcluirCidade(cidade, NomeArqCidades);
            system("pause");
            break;
        case 5:
            system("cls");
            OrdenarCidades(NomeArqCidades, cidade, vrfQtdRegistros(NomeArqCidades));
            system("pause");
            break;
        default:
            cout<<"\t\t\tInforme uma opção válida!"<<endl;
            system("pause");
            break;
        }
    }while(opc!=0);
}

Cidade ProcurarCidade(int codigo, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");
    Cidade encontrada;
    Cidade cidade;

    while(fread(&cidade, sizeof(Cidade), 1, arquivo)==1)
        if(cidade.codigo==codigo)
            encontrada = cidade;

    fclose(arquivo);

    return encontrada;
}

bool CidadeExiste(Cidade cidade, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");
    Cidade tmp;
    bool achou=false;

    if(arquivo==NULL)
    {
        fclose(arquivo);
        return achou;
    }

    while(fread(&tmp, sizeof(Cidade), 1, arquivo)==1)
        if(strcmp(cidade.nome, tmp.nome)==0)
            achou = true;

    fclose(arquivo);
    return achou;
}

void ExibirCidade(Cidade cidade)
{
    cout<<"\t\t\tCódigo...... "<<cidade.codigo<<endl;
    cout<<"\t\t\tNome........ "<<cidade.nome<<endl;
    cout<<"\t\t\t+------------------------------+"<<endl;
}

void ExibirCidades(Cidade cidade, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");

    if(arquivo==NULL)
        cout<<"\t\t\tErro de Arquivo!"<<endl;

    else
    {
        if(vrfQtdRegistros(nomeArquivo)>0)
        {
            cout<<"\t\t\t+--------EXIBIR CIDADES--------+"<<endl;
            while(fread(&cidade, sizeof(Cidade), 1, arquivo)==1)
                ExibirCidade(cidade);
        }
        else
            cout << "\t\t\tSem registros!"<<endl;
    }
    fclose(arquivo);
}

void setCodigoCidade(Cidade* cidade, char* nomeArquivo)
{
    int controle=0;
    do
    {
        cout<<"\t\t\tInforme o Código da Cidade: ";
        cin>>cidade->codigo;

        if(CodigoExiste(cidade->codigo, nomeArquivo))
        {
            cout<<"\t\t\tCódigo já existe! Informe outro! "<<endl;
            controle++;
        }

        if(controle==Erros)
            AvisoErros(&controle, nomeArquivo);

    }while(CodigoExiste(cidade->codigo, nomeArquivo));
}

void setNomeCidade(Cidade* cidade, char* nomeArquivo)
{
    cin.ignore();
    do
    {
        cout<<"\t\t\tInforme o Nome da Cidade: ";
        cin.getline(cidade->nome, TAMVETCHAR);

        if(CidadeExiste(*cidade, nomeArquivo))
            cout<<"\t\t\tCidade já existe! Informe outra! "<<endl;

    }while(CidadeExiste(*cidade, nomeArquivo));
}

void CadastrarCidade(Cidade cidade, char* nomeArquivo)
{
    cout<<"\t\t\t+-------CADASTRAR CIDADE-------+"<<endl;

    setCodigoCidade(&cidade, nomeArquivo);

    setNomeCidade(&cidade, nomeArquivo);

    GravarArquivo(&cidade, NULL, nomeArquivo);

    cout<<"\t\t\tCidade cadastrada com sucesso!"<<endl;
}

void EditarCidade(Cidade cidade, char* nomeArquivo)
{
    Cidade editCidade;
    FILE* arquivo = fopen(nomeArquivo, "r+b");

    if(arquivo==NULL)
        cout<<"\t\t\tErro de Arquivo!"<<endl;
    else
    {
        cout<<"\t\t\t+--------EDITAR  CIDADE--------+"<<endl;
        cout<<"\t\t\tInforme o código da cidade: ";
        cin>>editCidade.codigo;
        if(!CodigoExiste(editCidade.codigo, nomeArquivo))
            cout<<"\t\t\tCódigo não existe!"<<endl;
        else
        {
            while(fread(&cidade, sizeof(Cidade), 1, arquivo)==1)
                if(editCidade.codigo==cidade.codigo)
                {
                    ExibirCidade(cidade);

                    setNomeCidade(&editCidade, nomeArquivo);

                    fseek(arquivo, -sizeof(Cidade), SEEK_CUR);
                    fwrite(&editCidade, sizeof(Cidade), 1, arquivo);
                    cout<<"\t\t\tCidade editada com sucesso!"<<endl;
                    break;
                }
        }
    }

    fclose(arquivo);
}

void bubbleSortC(Cidade *cidade, int qtdElementos)
{
    int out, in;
    Cidade aux;
    for(out=qtdElementos-1; out>0; out--)
        for(in=0; in<out; in++)
            if(cidade[in].codigo>cidade[in+1].codigo)
            {
                aux=cidade[in];
                cidade[in]=cidade[in+1];
                cidade[in+1]=aux;
            }
}

void OrdenarCidades(char* nomeArquivo, Cidade cidade, int qtdReg)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");
    Cidade* aux = new Cidade[qtdReg];
    cout<<"\t\t\t+--------ORDENAR CIDADES-------+"<<endl;

    for(int i=0; i<qtdReg; i++)
    {
        fseek(arquivo,i*sizeof(Cidade),SEEK_SET);
        fread(&cidade,sizeof(Cidade),1,arquivo);
        aux[i] = cidade;
    }

    bubbleSortC(aux, qtdReg);
    //insertionSortC(aux, qtdReg);

    FILE* outArquivo = fopen(nomeArquivo, "wb");
    fwrite(aux, sizeof(Cidade), qtdReg, outArquivo);
    fclose(outArquivo);
    cout<< "\t\t\tCidades ordenadas com sucesso!" <<endl;
}

void RegravarArqCidade(char* nomeArquivo)
{
    int qtd = vrfQtdRegistros(nomeArquivo);
    Cidade* aux = new Cidade[qtd];

    FILE* arquivo = fopen(nomeArquivo,"rb");

    fread(aux, sizeof(Cidade), qtd, arquivo);
    fclose(arquivo);

    arquivo=fopen(nomeArquivo,"wb");

    for(int i=0; i<qtd; i++)
        if((aux[i].codigo)!=-1)
            fwrite(&aux[i], sizeof(Cidade), 1, arquivo);

    fclose(arquivo);
}

void ExcluirCidade(Cidade cidade, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "r+b");
    Cidade AuxCidade;

    if(arquivo==NULL)
        cout<<"\t\t\tErro de Arquivo!"<<endl;
    else
    {
        cout<<"\t\t\t+--------EXCLUIR CIDADE--------+"<<endl;
        cout<<"\t\t\tInforme o código da cidade: ";
        cin>>AuxCidade.codigo;
        if(!CodigoExiste(AuxCidade.codigo, nomeArquivo))
            cout<<"\t\t\tCódigo não existe!"<<endl;
        else
        {
            cout<< "\n\t\t\t+--------CIDADE EXCLUÍDA--------+" <<endl;
            while(fread(&cidade, sizeof(Cidade), 1, arquivo)==1)
                if(AuxCidade.codigo==cidade.codigo)
                {
                    ExibirCidade(cidade);
                    AuxCidade.codigo=-1;
                    fseek(arquivo, -sizeof(Cidade), SEEK_CUR);
                    fwrite(&AuxCidade, sizeof(Cidade), 1, arquivo);
                    break;
                }
        }
        fclose(arquivo);
        RegravarArqCidade(nomeArquivo);
    }
}
//}
////////////////////////////////////////////////////////

//{FUNÇÕES DE ROTA
void MenuRotas(char* NomeArqRota)
{
    int opc=0;
    Rota rota;
    do
    {
        system("cls");
        cout<<"\t\t\t+---------MENU ROTAS----------+"<<endl;
        cout<<"\t\t\t1 - Cadastrar Rota"<<endl;
        cout<<"\t\t\t2 - Exibir Rotas"<<endl;
        cout<<"\t\t\t3 - Editar Rota"<<endl;
        cout<<"\t\t\t4 - Excluir Rota"<<endl;
        cout<<"\t\t\t5 - Pesquisar Rota"<<endl;
        cout<<"\t\t\t0 - Voltar ao Menu de Seleção"<<endl;
        cout<<"\t\t\tOpção: ";
        cin>>opc;
        switch(opc)
        {
        case 0:
            break;
        case 1:
            system("cls");
            CadastrarRota(rota, NomeArqRota);
            system("pause");
            break;
        case 2:
            system("cls");
            cout<<"\t\t\t+---------EXIBIR ROTAS---------+"<<endl;
            ExibirRotas(rota, NomeArqRota);
            system("pause");
            break;
        case 3:
            system("cls");
            cout<<"\t\t\t+---------EDITAR  ROTA---------+"<<endl;
            EditarRota(rota, NomeArqRota);
            system("pause");
            break;
        case 4:
            system("cls");
            cout<<"\t\t\t+---------EXCLUIR ROTA---------+"<<endl;
            ExcluirRota(rota, NomeArqRota);
            system("pause");
            break;
        case 5:
            system("cls");
            int codigo;
            cout<<"\t\t\t+--------PESQUISAR ROTA--------+"<<endl;
            cout<<"\t\t\tInforme o código da rota: ";
            cin>>codigo;
            cout<<"\t\t\t+------------------------------+"<<endl;
            if(CodigoExiste(codigo, NomeArqRota))
                ExibirRota(PesquisarRota(codigo, NomeArqRota));
            else
                cout<<"\t\t\tRota não encontrada!"<<endl;
            system("pause");
            break;
        default:
            cout<<"\t\t\tInforme uma opção válida!"<<endl;
            system("pause");
            break;
        }
    }while(opc!=0);
}

Rota PesquisarRota(int codigo, char *nomeArquivo)
{
    Rota rota;
    Rota encontrada;
    int Hash;
    FILE* arquivo = fopen(nomeArquivo, "rb");
    if(vrfQtdRegistros(nomeArquivo)>0)
    {
        Hash = ObterHash(codigo, TamTabelaHash);
        while(fread(&rota, sizeof(Rota), 1, arquivo)==1)
            if(rota.codigo_hash==Hash)
                if(rota.codigo_cadastro==codigo)
                    encontrada = rota;
    }
    fclose(arquivo);
    return encontrada;
}

void RegravarArqRota(char* nomeArquivo)
{
    int qtd = vrfQtdRegistros(nomeArquivo);
    Rota* aux = new Rota[qtd];

    FILE* arquivo = fopen(nomeArquivo,"rb");
    FILE* arqSeq = fopen("rotas.txt", "w");

    fread(aux, sizeof(Rota), qtd, arquivo);
    fclose(arquivo);

    arquivo=fopen(nomeArquivo,"wb");

    for(int i=0; i<qtd; i++)
    {
        if((aux[i].codigo_cadastro)!=-1)
        {
            fwrite(&aux[i], sizeof(Rota), 1, arquivo);
            setlocale(LC_ALL, "english");

            fprintf(arqSeq, "%s\n%s\n%0.1f\n", aux[i].origem.nome, aux[i].destino.nome, aux[i].distancia);
            fprintf(arqSeq, "%s\n%s\n%0.1f\n", aux[i].destino.nome, aux[i].origem.nome, aux[i].distancia);

            setlocale(LC_ALL, "portuguese");
        }
    }
    fclose(arqSeq);
    fclose(arquivo);
}

void GravarEdicao(Rota rota, char* nomeArquivo)
{
    Rota tmp;
    FILE* arquivo = fopen(nomeArquivo, "r+b");
    while(fread(&tmp, sizeof(Rota), 1, arquivo)==1)
        if(tmp.codigo_cadastro==rota.codigo_cadastro)
        {
            fseek(arquivo, -sizeof(Rota), SEEK_CUR);
            fwrite(&rota, sizeof(Rota), 1, arquivo);
            break;
        }
    fclose(arquivo);
}


void MenuEdicaoRota(int codigo, char* nomeArquivo)
{
    int opc;
    Rota rota = PesquisarRota(codigo, nomeArquivo);
    char arqCidade[] = "cidades.dat";
    do
    {
        system("cls");
        cout<<"\t\t\t+---------EDITAR  ROTA---------+"<<endl;
        ExibirRota(rota);
        cout<<"\t\t\t1 - Editar Cidade de Origem"<<endl;
        cout<<"\t\t\t2 - Editar Cidade de Destino"<<endl;
        cout<<"\t\t\t3 - Editar Distância"<<endl;
        cout<<"\t\t\t4 - Salvar"<<endl;
        cout<<"\t\t\t0 - Cancelar"<<endl;
        cout<<"\t\t\tOpção: ";
        cin>>opc;
        switch(opc)
        {
        case 0:
            cout<<"\t\t\tAlterações Descartadas!"<<endl;
            return;
            break;
        case 1:
            setCidadeOrigem(&rota, arqCidade);
            break;
        case 2:
            setCidadeDestino(&rota, arqCidade);
            break;
        case 3:
            setDistancia(&rota, arqCidade);
            break;
        case 4:
            if(RotaExiste2(rota, nomeArquivo) || rota.destino.codigo==rota.origem.codigo)
            {
                cout<<"\t\t\tErro, rota já existe ou Destino e Origem iguais!"<<endl;
                system("pause");
            }
            else
            {
                GravarEdicao(rota, nomeArquivo);
                cout<<"\t\t\tAlterações salvas com sucesso!"<<endl;
                return;
            }
            break;
        default:
            cout<<"\t\t\tOpção Inválida!"<<endl;
            break;
        }
    }while(opc!=0 || opc!=4);
}

void EditarRota(Rota rota, char* nomeArquivo)
{
    int codigo=0;
    cout<<"\t\t\tInforme o código da rota: ";
    cin>>codigo;
    if(!CodigoExiste(codigo, nomeArquivo))
        cout<<"\t\t\tCódigo não existe!"<<endl;
    else
        MenuEdicaoRota(codigo, nomeArquivo);

    RegravarArqRota(nomeArquivo);
}

bool RotaExiste(Rota rota, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");
    bool achou = false;
    Rota tmp;
    if(arquivo==NULL)
    {
        fclose(arquivo);
        return achou;
    }
    else
    {
        while(fread(&tmp, sizeof(Rota), 1, arquivo)==1)
        {
            if((rota.origem.codigo==tmp.origem.codigo && rota.destino.codigo==tmp.destino.codigo)
               ||(rota.destino.codigo==tmp.origem.codigo && rota.origem.codigo==tmp.destino.codigo))
            {
                achou = true;
            }
        }
        fclose(arquivo);
        return achou;
    }
}


bool RotaExiste2(Rota rota, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");
    bool achou = false;
    Rota tmp;
    if(arquivo==NULL)
    {
        fclose(arquivo);
        return achou;
    }
    else
    {
        while(fread(&tmp, sizeof(Rota), 1, arquivo)==1)
        {
            if((rota.origem.codigo==tmp.origem.codigo && rota.destino.codigo==tmp.destino.codigo && rota.distancia == tmp.distancia)
               ||(rota.destino.codigo==tmp.origem.codigo && rota.origem.codigo==tmp.destino.codigo && rota.distancia == tmp.distancia))
            {
                achou = true;
            }
        }
        fclose(arquivo);
        return achou;
    }
}

void setCodigoCadastro(Rota* rota, char* nomeArquivo)
{
    int controle=0;
    do
    {
        cout<<"\t\t\tInforme o código do cadastro: ";
        cin>>rota->codigo_cadastro;
        if(CodigoExiste(rota->codigo_cadastro, nomeArquivo))
        {
            cout<<"\t\t\tCódigo já existe! Informe outro!"<<endl;
            controle++;
        }
        if(controle==Erros)
            AvisoErros(&controle, nomeArquivo);
    }while(CodigoExiste(rota->codigo_cadastro, nomeArquivo));
}

void setCidadeOrigem(Rota* rota, char* arqCidade)
{
    int codigo=0;
    do
    {
        cout<<"\t\t\tInforme o código da cidade de origem: ";
        cin>>codigo;
        if(!CodigoExiste(codigo, arqCidade))
            cout<<"\t\t\tCódigo de cidade inexistente!"<<endl;
        else{
            rota->origem = ProcurarCidade(codigo, arqCidade);
        }
    }while(!CodigoExiste(codigo, arqCidade));
}

void setCidadeDestino(Rota* rota, char* arqCidade)
{
    int codigo=0;
    do
    {
        cout<<"\t\t\tInforme o código da cidade de destino: ";
        cin>>codigo;
        if(!CodigoExiste(codigo, arqCidade))
            cout<<"\t\t\tCódigo de cidade inexistente!"<<endl;
        else if(rota->origem.codigo==codigo)
            cout<<"\t\t\tCódigos de Origem e Destino Iguais!"<<endl;
        else
            rota->destino = ProcurarCidade(codigo, arqCidade);
    }while(!CodigoExiste(codigo, arqCidade) || rota->origem.codigo==codigo);
}

void setDistancia(Rota *rota, char* nomeArquivo)
{
    if(!RotaExiste(*rota, nomeArquivo))
    {
        cout<<"\t\t\tInforme a distância entre "<<rota->origem.nome<<" e "<<rota->destino.nome<<" (KM): ";
        cin>>rota->distancia;
    }
    else
    {
        cout<<"\t\t\tA rota cadastrada já existe!"<<endl;
    }
}

void CadastrarRota(Rota rota, char* nomeArquivo)
{
    char opc;
    Cidade cidade;
    char arqCidade[] = "cidades.dat";
    system("cls");
    cout<<"\t\t\t+--------CADASTRAR ROTA---------+"<<endl<<endl;

    setCodigoCadastro(&rota, nomeArquivo);

    cout<<"\t\t\tExibir Cidades Disponíveis[S/N]? ";
    cin>>opc;

    if(opc == 's' || opc == 'S')
    {
        ExibirCidades(cidade, arqCidade);
        cout<<"\t\t\t======================================"<<endl<<endl;
    }
    do{
        setCidadeOrigem(&rota, arqCidade);
        setCidadeDestino(&rota, arqCidade);
        setDistancia(&rota, nomeArquivo);
    }while(RotaExiste(rota, nomeArquivo));

    rota.codigo_hash = ObterHash(rota.codigo_cadastro, TamTabelaHash);

    GravarArquivo(NULL, &rota, nomeArquivo);
    OrdenarRotas(nomeArquivo, rota, vrfQtdRegistros(nomeArquivo));
    cout<<endl<<"\t\t\tRota cadastrada com sucesso!!"<<endl;
}

void ExibirRota(Rota rota)
{
    cout<<"\t\t\tCódigo HASH......... "<<rota.codigo_hash<< //TESTE
    endl<<"\t\t\tCódigo do cadastro.. "<<rota.codigo_cadastro<<
    endl<<"\t\t\tOrigem.............. "<<rota.origem.nome<<
    endl<<"\t\t\tDestino............. "<<rota.destino.nome<<
    endl<<"\t\t\tDistância........... "<<rota.distancia<<"KM"<<endl;
    cout<<"\t\t\t+------------------------------+"<<endl;
}

void ExibirRotas(Rota rota, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");

    if(arquivo==NULL)
        cout<<"\t\t\tErro de Arquivo!"<<endl;
    else
    {
        if(vrfQtdRegistros(nomeArquivo)>0)
        {
            while(fread(&rota, sizeof(rota), 1, arquivo)==1)
                ExibirRota(rota);
        }
        else
            cout <<"\t\t\tSem registros!"<<endl;
    }
    fclose(arquivo);
}

void ExcluirRota(Rota rota, char* nomeArquivo)
{
    FILE* arquivo = fopen(nomeArquivo, "r+b");
    Rota auxRota;
    if(arquivo==NULL)
        cout<<"\t\t\tErro de Arquivo!"<<endl;
    else
    {
        cout<<"\t\t\tInforme o código da rota: ";
        cin>>auxRota.codigo_cadastro;
        if(!CodigoExiste(auxRota.codigo_cadastro, nomeArquivo))
            cout<<"\t\t\tCódigo não existe!"<<endl;
        else
        {
            cout<< "\n\t\t\tDADOS DA ROTA QUE SERÁ EXCLUÍDA" <<endl;
            while(fread(&rota, sizeof(Rota), 1, arquivo)==1)
                if(auxRota.codigo_cadastro==rota.codigo_cadastro)
                {
                    ExibirRota(rota);
                    auxRota.codigo_cadastro=-1;
                    fseek(arquivo, -sizeof(Rota), SEEK_CUR);
                    fwrite(&auxRota, sizeof(Rota), 1, arquivo);
                    break;
                }
        }
        fclose(arquivo);
        RegravarArqRota(nomeArquivo);
    }
}

void bubbleSortR(Rota* rota, int qtdElementos)
{
    int out, in;
    Rota aux;
    for(out=qtdElementos-1; out>0; out--)
        for(in=0; in<out; in++)
            if(rota[in].codigo_cadastro>rota[in+1].codigo_cadastro)
            {
                aux=rota[in];
                rota[in]=rota[in+1];
                rota[in+1]=aux;
            }
}

void OrdenarRotas(char* nomeArquivo, Rota rota, int qtdReg)
{
    FILE* arquivo = fopen(nomeArquivo, "rb");

    if(arquivo == NULL)
        cout<< "\t\t\tErro de arquivo!"<<endl;
    else if(vrfQtdRegistros(nomeArquivo)>0)
    {
        Rota* aux = new Rota[qtdReg];
        for(int i=0; i<qtdReg; i++)
        {
            fseek(arquivo,i*sizeof(Rota),SEEK_SET);
            fread(&rota,sizeof(Rota),1,arquivo);
            aux[i] = rota;
        }

        bubbleSortR(aux, qtdReg);
        //insertionSortR(aux, qtdReg);
        fclose(arquivo);
        arquivo = fopen(nomeArquivo, "wb");
        fwrite(aux, sizeof(Rota), qtdReg, arquivo);
        fclose(arquivo);
        RegravarArqRota(nomeArquivo);
    }
    else
        cout<<"\t\t\tSem registros!"<<endl;

    fclose(arquivo);
}
//}

#endif // FUNCOES_H_INCLUDED
