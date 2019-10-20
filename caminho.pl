%----------------------------------------------------------------------------------------------------------%
:-dynamic(rota/3).

carregarArquivo:-
        open('TempoDeViagem.txt', read, ArqEntrada),
        lerLinha(ArqEntrada),
        close(ArqEntrada).

lerLinha(ArqEntrada):-
        at_end_of_stream(ArqEntrada), !.

lerLinha(ArqEntrada):-
        read(ArqEntrada, rota(Origem, Destino, Tempo)), !,
        checarRota(Origem, Destino, Tempo),
        lerLinha(ArqEntrada).

lerLinha(ArqEntrada):-
        lerLinha(ArqEntrada).

checarRota(Origem, Destino, Tempo):-
        rota(Origem, Destino, Tempo), !.

checarRota(Origem, Destino, Tempo):-
        assert(rota(Origem, Destino, Tempo)).
%----------------------------------------------------------------------------------------------------------%

caminho(Origem, Destino, Tempo, Caminho):-
        caminho1(Origem, [Destino], 0, Tempo,  Caminho).

caminho1(Cidade, [Cidade|Cidades], Tempo, Tempo, [Cidade|Cidades]).
caminho1(Origem, [CidAdj|Cidades], Tempo, TempoF, CamF):-
        rota(Intermediario, CidAdj,  T1),
        \+ pertence(Intermediario, [CidAdj|Cidades]),
        T2  is Tempo + T1,
        caminho1(Origem, [Intermediario, CidAdj|Cidades], T2, TempoF,  CamF).

pertence(Elemento, [Elemento|_]):-!.
pertence(Elemento, [_|Cauda]):- pertence(Elemento, Cauda).

exibir([X]):-
        write(X),!.

exibir([X|Y]):-
        write(X),
        write("->"),
        exibir(Y).    

exibirRotas(X, Lim, [(Tempo, Origem, Destino, Caminho)|Cauda]):-
        Cont is X + 1,
        Cont =< Lim,
        nl,
        write("ROTA ["), write(Cont), write("]"), nl, 
        write("De "), write(Origem), write(" para "), write(Destino),  
        write(", seguindo esta rota: "), nl, exibir(Caminho), nl,
        write("Voce vai gastar cerca de "), write(Tempo), write(" Minutos. "), nl,
        exibirRotas(Cont, Lim, Cauda).
            
mostrarRotas(Origem, Destino, QtdRotas):-
                carregarArquivo(),
                setof((Tempo, Origem, Destino, Caminho), caminho(Origem, Destino, Tempo, Caminho), Rotas),
                exibirRotas(0, QtdRotas, Rotas).
%----------------------------------------------------------------------------------------------------------%