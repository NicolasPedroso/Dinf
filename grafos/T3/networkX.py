import networkx as nx
import matplotlib.pyplot as plt

# Função para identificar hubs (nós com alto grau)
def identificar_hubs(grafo, top_n=5):
    """
    Identifica os nós com maior grau no grafo.
    :param grafo: Grafo do NetworkX.
    :param top_n: Número de hubs a retornar.
    :return: Lista de nós hubs com seus graus.
    """
    graus = dict(grafo.degree())
    hubs = sorted(graus.items(), key=lambda x: x[1], reverse=True)[:top_n]
    return hubs

# Função para encontrar vértices ponte (articulações)
def encontrar_ponte(grafo):
    """
    Identifica os vértices que, ao serem removidos, desconectam o grafo.
    :param grafo: Grafo do NetworkX.
    :return: Lista de vértices ponte.
    """
    if nx.is_directed(grafo):
        print("A análise de vértices ponte é mais relevante em grafos não direcionados.")
    return list(nx.articulation_points(grafo)) if not nx.is_directed(grafo) else []

# Função para encontrar arestas ponte
def encontrar_arestas_ponte(grafo):
    """
    Identifica as arestas que, ao serem removidas, desconectam o grafo.
    :param grafo: Grafo do NetworkX.
    :return: Lista de arestas ponte.
    """
    return list(nx.bridges(grafo)) if not nx.is_directed(grafo) else []

# Função para identificar componentes conectados
def identificar_componentes_conectados(grafo):
    """
    Retorna as componentes conectadas do grafo.
    :param grafo: Grafo do NetworkX.
    :return: Lista de componentes conectados.
    """
    if nx.is_directed(grafo):
        componentes = nx.strongly_connected_components(grafo)
    else:
        componentes = nx.connected_components(grafo)
    return [list(componente) for componente in componentes]

# Função para calcular centralidade de intermediação (betweenness)
def calcular_centralidade_intermediacao(grafo, top_n=5):
    """
    Calcula a centralidade de intermediação dos nós.
    :param grafo: Grafo do NetworkX.
    :param top_n: Número de nós com maior centralidade a retornar.
    :return: Lista de nós com maior centralidade de intermediação.
    """
    centralidade = nx.betweenness_centrality(grafo)
    top_centralidade = sorted(centralidade.items(), key=lambda x: x[1], reverse=True)[:top_n]
    return top_centralidade


# Função para calcular o diâmetro do grafo
def calcular_diametro(grafo):
    """
    Calcula o diâmetro do grafo (distância máxima entre dois nós).
    :param grafo: Grafo do NetworkX.
    :return: Diâmetro do grafo.
    """
    if nx.is_directed(grafo):
        print("O diâmetro é mais relevante em grafos não direcionados.")
    return nx.diameter(grafo) if not nx.is_directed(grafo) else None

# Função para calcular a densidade do grafo
def calcular_densidade(grafo):
    """
    Calcula a densidade do grafo.
    :param grafo: Grafo do NetworkX.
    :return: Densidade do grafo.
    """
    return nx.density(grafo)

grafo = nx.read_edgelist("bn/bn-mouse_brain_1.edges", nodetype=int) # bn-human-BNU_1_0025864_session_1-bg

# Desenho do grafo
plt.figure(figsize=(10, 8))
nx.draw(grafo, with_labels=True, node_size=500, node_color="lightblue", font_size=10)
plt.show()

# Informações sobre o grafo
# print("Vértices do grafo:", list(grafo.nodes()))

# Pegando o numero de vertices do grafo
print("Número de vértices:", grafo.number_of_nodes())

# pegando o numero de arestas
print("Número de arestas:", grafo.number_of_edges())

# Quantos graus tem cada vertice
graus = dict(grafo.degree())
print("Graus dos nós:", graus)

#HUBS
hubs = identificar_hubs(grafo)
print("Hubs:", hubs)

#VÉRTICES PONTES
pontes = encontrar_ponte(grafo)
print("Vértices ponte:", pontes)

#COMPONENTES
componentes = identificar_componentes_conectados(grafo)
print("Componentes conectados:")
for elemento in componentes:
    print(elemento, end="\n")  # Adiciona uma quebra de linha após cada elemento

#CENTRALIDADE OU BETWEENNESS
centralidade = calcular_centralidade_intermediacao(grafo)
print("Centralidade de intermediação:", centralidade)

#CLOSENESS OU PROXIMIDADE
proximidade = nx.closeness_centrality(grafo)
mais_proximo = max(proximidade, key=proximidade.get) #Maior proximidade a outros vértices
print(f"Vértice mais próximo: {mais_proximo} (Valor: {proximidade[mais_proximo]:.4f})")

#DIAMETRO
diametro = calcular_diametro(grafo)
print("Diâmetro do grafo:", diametro)

#TIPO DO GRAFO
tipo = "Direcionado" if nx.is_directed(grafo) else "Não Direcionado"
print(f"Tipo do Grafo: {tipo}")

#DENSIDADE
densidade = calcular_densidade(grafo)
print("Densidade do grafo:", densidade)

#AGRUPAMENTO DO GRAFO
clustering = nx.clustering(grafo)
print(f"Coeficiente de agrupamento médio: {nx.average_clustering(grafo)}")

#COMUNIDADES
comunidades = list(nx.algorithms.community.greedy_modularity_communities(grafo))
print(f"Número de comunidades detectadas de Greedy Modularity: {len(comunidades)}")
print("Comunidades GREEDY:")
for elemento in comunidades:
    print(elemento, end="\n")  # Adiciona uma quebra de linha após cada elemento

# PROPAGAÇÃO DE RÓTULOS
comunidades = list(nx.algorithms.community.label_propagation_communities(grafo))
print("Comunidades detectadas de Propagação de Rótulos:")
for elemento in comunidades:
    print(elemento, end="\n")  # Adiciona uma quebra de linha após cada elemento