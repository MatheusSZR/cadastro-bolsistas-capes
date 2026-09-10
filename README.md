# Cadastro de Bolsistas da CAPES

Programa desenvolvido em linguagem C para importar registros de bolsistas de um arquivo CSV para outro, evitando nomes duplicados.

## Compilação

No terminal do VS Code:

gcc copiador.c -o copiador.exe

## Execução

.\copiador.exe bolsistas-2025.csv cadastro.csv estatisticas.csv

O programa recebe:
- arquivo CSV de origem;
- arquivo CSV de destino;
- arquivo CSV de estatísticas.

## Estatísticas

O programa gera um arquivo CSV contendo:

nomes_inseridos,comparacoes

## Experimentos

Foram realizados experimentos com:
- 10 nomes;
- 20 nomes;
- 40 nomes;
- 80 nomes;
- 160 nomes.

Os arquivos de entrada, saída e estatísticas dos experimentos estão disponíveis neste repositório.