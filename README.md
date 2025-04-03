# Questão 3 - Covid Genoma Analysis

## Descrição da Questão

Nesta questão, o objetivo é processar um arquivo de genoma do Coronavírus e contar a frequência de blocos de 6 bases nitrogenadas (A, T, C, G) consecutivos. A leitura é feita em blocos de 6 caracteres e armazenada em uma tabela de espalhamento (hash table) para contagem eficiente.

O programa recebe como entrada um arquivo FASTA e gera um arquivo de saída com a contagem de cada bloco de 6 bases encontrado.

## Estrutura do Projeto

O projeto contém os seguintes arquivos:

- `analisador_genoma.cpp` - Implementação principal do algoritmo.
- `sequences.fasta.txt` - Arquivo de entrada com o genoma do Coronavírus.
- `counts.txt` - Arquivo de saída gerado contendo a contagem de cada bloco de 6 bases.
- `teste.txt` - Arquivo de entrada menor para testes.
- `counts_teste.txt` - Arquivo de saída com a contagem do arquivo de teste.

## Como Compilar e Executar

### Compilação
Para compilar o programa, utilize o seguinte comando:
```bash
 g++ -o covid_analysis analisador_genoma.cpp
```
Isso criará um executável chamado `covid_analysis`.

### Execução
O programa pode ser executado passando o arquivo de entrada e o arquivo de saída como argumentos:
```bash
 ./covid_analysis sequences.fasta.txt counts.txt
```
Se desejar testar com um arquivo menor, utilize:
```bash
 ./covid_analysis teste.txt counts_teste.txt
```

## Formato do Arquivo de Entrada
O arquivo de entrada deve estar no formato FASTA, contendo a sequência do genoma com blocos de 60 caracteres por linha. A primeira linha é um cabeçalho e será ignorada na leitura.

Exemplo:
```
>sequencia_teste_1
ATTAAAGGTTTATACCTTCCCAGGTAACAAACCAACCAACTTTCGATCTCTTGTAGATCT
TTTTTTGGGGGGAATTCCGCGCGCGAGAGCTTATTAGGGTAAAGGCCAAAGCCAAACCCA
```

## Formato do Arquivo de Saída
O arquivo de saída gerado terá duas colunas:
- A primeira coluna contém o bloco de 6 bases nitrogenadas.
- A segunda coluna contém a contagem de quantas vezes esse bloco apareceu no genoma.

Exemplo:
```
ATTAAA 3
AGGTTT 5
TATACC 2
```

