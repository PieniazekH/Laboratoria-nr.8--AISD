#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
// definiujemy liczbe wierszy w grafie
#define V 12


int minKey(int key[], bool mstSet[])
{
    // Inicjujemy najmniejsza wartosc
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

//funkcja do wyswietlania wyników, czyli najmniejszej drogi

int printMST(int parent[], int graph[V][V])
{
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// funkcja tworzaca macierz sasiedztwa

void primMST(int graph[V][V])
{
    // tablica przechowujaca skonstruowane MST
    int parent[V];
    // klucz okreslajacy wage danej krawedzi
    int key[V];
    // zmienna która okreœla czy wierzcholek jest zawarty w MST
    bool mstSet[V];

    // ustawienie wszystkich wartosci jako nieskonczonosc
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // ustawienie wartosci klucza na 0 w celu uwzglednienia pierwszego wierzcholka jako pierwszy

    key[0] = 0;
    parent[0] = -1; // Pierwszy wezel jest zawsze korzeniem w MST


    for (int count = 0; count < V - 1; count++) {
        // Wybranie najmniejszej wartosci sposród wierzcholków nie zawartych w MST
        int u = minKey(key, mstSet);

        // dodanie wybranego wierzcholka do MST
        mstSet[u] = true;

        // zaktualizowanie wartosci dla sasiednich wierzcholków wybranego wierzcholka
        // rozwazenie tylko tych wartosci które nie sa zawarte w MST
        for (int v = 0; v < V; v++)

            // Graf [u][v] ma wartoœci nie zerowe tylko dla sasiednich wierzcholków
            // mstSet[v] jest falszem dla wierzcholków nie zawartych w MST
            // Aktualizowanie klucza tylko wtedy, gdy graph[u][v] jest mniejszy niz key[v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // wyswietlenie skonstruowanego MST
    printMST(parent, graph);
}


int main()
{

    int graph[V][V] = { { 0, 0, 1, 4, 5, 5, 0, 0, 22, 0, 0 },//A
                        { 0, 0, 16, 0, 0, 0, 0, 0, 3, 30, 0 },//B
                        { 1, 16, 0, 1, 0, 0, 0, 0, 0, 0, 0 },//C
                        { 4, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 },//D
                        { 5, 0, 0, 1, 0, 12, 0, 0, 0, 0, 0 }, //E
                        { 5, 0, 0, 0, 12, 0, 27, 0, 0, 0, 0 }, //F
                        { 0, 0, 0, 0, 0, 27, 0, 5, 0, 10, 18},//G
                        { 0, 0, 0, 0, 0, 0, 5, 0, 5, 20, 0}, //H
                        { 22, 3, 0, 0, 0, 0, 0, 5, 0, 25, 0},//I
                        { 0, 30, 0, 0, 0, 0, 10, 20, 25, 3 },//J
                        { 0, 0, 0, 0, 0, 0, 18, 0, 0, 3, 0}};//K

    // Wyswietlenie wyniku
    primMST(graph);

    return 0;
}
