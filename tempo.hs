import System.IO
import System.Directory

processarTempo :: IO ()
processarTempo = do
                let arqSaida = "TempoDeViagem.txt"
                let arqEntrada = "rotas.txt"
                conteudo <- readFile arqEntrada
                let dados = lines conteudo
                checarArquivo arqSaida
                calcularTempo dados 0 2 --Lista -> Inicio da lista -> Posicao do valor da distancia
                putStrLn "Arquivo \"TempoDeViagem.txt\" processado com sucesso e pronto para ser usado no PROLOG!"

checarArquivo :: FilePath -> IO()
checarArquivo arquivo = do --Se o arquivo ja existe, apaga
                        resultado <- doesFileExist arquivo
                        if resultado
                        then removeFile arquivo
                        else return()

calcularTempo :: [String] -> Int -> Int -> IO ()
calcularTempo lista ini dist = do
                let tempoViagem = (read (lista !! dist) :: Float)*1.5 -- Calcula (Distancia*1.5)
                let rota = ((take dist lista)++[(show tempoViagem)]) -- Concatena Origem e Destino com Tempo
                let origem = rota !! ini -- Salva cidade de origem em "origem"
                let destino = rota !! (ini+1) --Salva cidade de destino em "destino"
                let tempo = read(last rota)::Float --Salva tempo de viagem em "tempo", transformando a String lida em Float
                salvarNoArquivo origem destino tempo --Chama funcao "salvarNoArquivo" passando os parametros origem, destino e tempo
                if (dist+3)<(length lista) then calcularTempo lista (ini+3) (dist+3) else return()
                -- ^Compara se o valor que esta o destino somado com 3 e menor que o tamanho da lista
                -- Se for, chama calcularTempo novamente passando a lista e os valores +3, que é basicamente o tamanho de cada sublista
                -- que contem a origem, destino e distancia
                -- Se nao for chama return, que finaliza a funcao IO.

salvarNoArquivo :: String-> String -> Float -> IO ()
salvarNoArquivo origem destino tempo = do
                                        let nomeArq = "TempoDeViagem.txt"
                                        arq <- openFile nomeArq AppendMode --Abre de modo a gravar apenas no final do arquivo, ja que e chamada varias vezes
                                        hPutStrLn arq ("rota("++"\""++ origem ++"\""++ ", " ++"\""++destino++"\""++", "++(show tempo :: String)++").")
                                        -- ^Formatacao para ler no PROLOG^
                                        hFlush arq
                                        hClose arq