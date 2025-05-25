# Teoria dos Grafos | Instituto de Computação (UFAL)

## Descrição

Este projeto apresenta a implementação de cinco algoritmos fundamentais da Teoria dos Grafos, abordados na disciplina de Teoria dos Grafos no Instituto de Computação da UFAL. Cada algoritmo foi desenvolvido com o objetivo de resolver problemas clássicos envolvendo grafos, como cálculo de caminhos mínimos, árvores geradoras mínimas e análise de componentes fortemente conexas.

## Alunos

- Hugo Stankowich Souza  
- Lucca Paes Costa

## Algoritmos Implementados

### 🔹 Algoritmo de Prim
Constrói a árvore geradora mínima de um grafo conectado e ponderado, selecionando as arestas de menor peso enquanto evita a formação de ciclos.

### 🔹 Algoritmo de Dijkstra
Encontra o caminho mais curto de um vértice origem para todos os outros vértices em um grafo com arestas de pesos não negativos.

### 🔹 Algoritmo de Kruskal
Determina a árvore geradora mínima de um grafo conectado e ponderado, ordenando as arestas por peso e adicionando-as progressivamente enquanto evita ciclos.

### 🔹 Algoritmo de Floyd-Warshall
Resolve o problema de caminhos mínimos entre todos os pares de vértices em um grafo, sejam ele direcionado ou não, com pesos positivos ou negativos (desde que não haja ciclos de peso negativo).

### 🔹 Algoritmo de Kosaraju
Identifica componentes fortemente conectadas em grafos direcionados, utilizando uma abordagem baseada em duas passagens pelo grafo (forward e reverse DFS).

## Tecnologias Utilizadas

- **Linguagem**: C++

## Como Executar

1. **Clone este repositório**:

```bash
git clone https://github.com/Stankowichs/Algoritmo-Grafos.git
```

2. **Navegue até o diretório do algoritmo desejado**:

```bash
cd Algoritmo-Grafos/<DIRETÓRIO_DO_ALGORITMO>
```

3. **Compile e execute**:

```bash
make (Nome do algoritmo)
```

4. **(Se necessário)**: Torne os arquivos da pasta executáveis:

```bash
chmod -R +x Bat1/
```
