#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

struct NoHash {
    string chave;
    int valor;
};

class TabelaHash {
private:
    vector<list<NoHash>> tabela;
    size_t tamanho_tabela;
    const int BASE_HASH = 31;

    size_t funcao_hash(const string& chave) const {
        size_t valor_hash = 0;
        for (char c : chave)
            valor_hash = (valor_hash * BASE_HASH + (c - 'A' + 1)) % tamanho_tabela;
        return valor_hash;
    }

public:
    TabelaHash(size_t tamanho) : tamanho_tabela(tamanho) {
        if (tamanho == 0)
            throw invalid_argument("O tamanho da tabela hash deve ser positivo.");
        tabela.resize(tamanho_tabela);
    }

    void inserir_ou_incrementar(const string& chave) {
        if (chave.length() != 6) return;
        
        size_t indice = funcao_hash(chave);
        auto& balde = tabela[indice];

        for (auto& no : balde) {
            if (no.chave == chave) {
                no.valor++;
                return;
            }
        }

        balde.push_back({chave, 1});
    }

    vector<NoHash> obter_todas_entradas() const {
        vector<NoHash> todas_entradas;
        for (const auto& balde : tabela)
            todas_entradas.insert(todas_entradas.end(), balde.begin(), balde.end());
        return todas_entradas;
    }

    size_t obter_contagem_elementos() const {
        size_t contagem = 0;
        for (const auto& balde : tabela)
            contagem += balde.size();
        return contagem;
    }
};

bool eBaseValida(char c) {
    return c == 'A' || c == 'T' || c == 'C' || c == 'G';
}

int main(int argc, char* argv[]) {
    string nome_arquivo_entrada = (argc > 1) ? argv[1] : "sequences.fasta.txt";
    string nome_arquivo_saida = (argc > 2) ? argv[2] : "counts.txt";

    const int TAMANHO_BLOCO = 6;
    const size_t TAMANHO_TABELA_HASH = 5003;

    ifstream arquivo_entrada(nome_arquivo_entrada);
    if (!arquivo_entrada) {
        cerr << "Erro: Não foi possível abrir o arquivo de entrada.\n";
        return 1;
    }

    TabelaHash contagens_blocos(TAMANHO_TABELA_HASH);
    string linha;
    int contador_blocos_total = 0;

    while (getline(arquivo_entrada, linha) && linha[0] == '>');
    do {
        linha.erase(remove(linha.begin(), linha.end(), '\r'), linha.end());
        linha.erase(remove(linha.begin(), linha.end(), '\n'), linha.end());

        for (size_t i = 0; (i + TAMANHO_BLOCO) <= linha.length(); i++) {
            string bloco = linha.substr(i, TAMANHO_BLOCO);
            if (all_of(bloco.begin(), bloco.end(), eBaseValida)) {
                contagens_blocos.inserir_ou_incrementar(bloco);
                contador_blocos_total++;
            }
        }
    } while (getline(arquivo_entrada, linha));

    arquivo_entrada.close();

    cout << "Processamento concluido.\n";
    cout << "Total de blocos processados: " << contador_blocos_total << endl;
    cout << "Blocos unicos encontrados: " << contagens_blocos.obter_contagem_elementos() << endl;

    ofstream arquivo_saida(nome_arquivo_saida);
    if (!arquivo_saida) {
        cerr << "Erro: Não foi possível criar o arquivo de saída.\n";
        return 1;
    }

    for (const auto& no : contagens_blocos.obter_todas_entradas())
        arquivo_saida << no.chave << "\t" << no.valor << "\n";

    cout << "Resultados salvos em " << nome_arquivo_saida << endl;

    return 0;
}