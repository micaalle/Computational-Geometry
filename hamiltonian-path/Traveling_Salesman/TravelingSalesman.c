#include <stdio.h>
#include <limits.h>

#define MAX_V 10
#define INF INT_MAX

int G[MAX_V][MAX_V];
int n = MAX_V;


// find min function for prim's
int findMin(int key[], int mstSet[]) {
    int min = INF, minIndex;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// implemtation of prims algorithm to find minimum spanning tree (simplified somewhat)
void MST_PRIM(int G[MAX_V][MAX_V], int r, int parent[]) {
    int key[MAX_V];
    int mstSet[MAX_V];

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[r] = 0;
    parent[r] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = findMin(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (G[u][v] && !mstSet[v] && G[u][v] < key[v]) {
                key[v] = G[u][v];
                parent[v] = u;
            }
        }
    }
}

// DFS on the tree to get the path
void preorderDFS(int u, int parent[], int visited[], int H[], int *index) {
    visited[u] = 1;
    H[(*index)++] = u;

    for (int v = 0; v < n; v++) {
        if (!visited[v] && parent[v] == u) {
            preorderDFS(v, parent, visited, H, index);
        }
    }
}

// traveling salemans implementation
void APPROX_TSP_TOUR(int G[MAX_V][MAX_V], int root) {
    int parent[MAX_V];
    int visited[MAX_V] = {0};
    int H[MAX_V];
    int index = 0;

    // prims algorithm 
    MST_PRIM(G, root, parent);

    // find the preorder traversal via DFS
    preorderDFS(root, parent, visited, H, &index);

    // hamiltonian cycle print
    printf("Hamiltonian Cycle: \n");
    for (int i = 0; i < index - 1; i++) {
        printf("%d - %d\n", H[i], H[i + 1]);
    }
    printf("%d - %d\n", H[index - 1], root);
}

int main() {
    int G[10][10] = {
        {0, 4, 3, 5, 23, 6, 2, 8, 1, 7},
        {4, 0, 6, 4, 10, 3, 2, 23, 9, 5},
        {3, 6, 0, 7, 8, 2, 4, 3, 6, 2},
        {5, 8, 7, 0, 3, 5, 8, 4, 6, 2},
        {23, 10, 8, 3, 0, 9, 5, 1, 2, 4},
        {6, 3, 12, 5, 9, 0, 2, 7, 2, 3},
        {2, 2, 4, 8, 5, 2, 0, 5, 3, 7},
        {8, 23, 3, 4, 8, 7, 5, 0, 6, 9},
        {1, 9, 6, 6, 21, 4, 3, 6, 0, 1},
        {7, 5, 25, 32, 4, 3, 7, 9, 1, 0}
    };

    int root = 0;
    APPROX_TSP_TOUR(G, root);

    return 0;
}
