#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

//CONSTANTES
#define Erros 3
#define TAMVETCHAR 50

#define TamTabelaHash 1021

//STRUCTS
typedef struct{
    int codigo;
    char nome[TAMVETCHAR];
}Cidade;

typedef struct{
    int codigo_hash;
    int codigo_cadastro;
    Cidade origem;
    Cidade destino;
    float distancia;
}Rota;

#endif // STRUCTS_H_INCLUDED
