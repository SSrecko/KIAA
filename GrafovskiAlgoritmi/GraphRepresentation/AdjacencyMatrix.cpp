#include <iostream>
#include <vector>

struct Graph
{
    private: 
    std::vector<std::vector<int>> adj;    
    std::vector<int> data;
    int v;
    

    public:

    Graph(int n)
    {
        v = n;
        adj.resize(v, std::vector<int>(v, 0));
        data.resize(v);
    }

    void addEdge(int u, int v)
    {
        adj[u][v] = adj[v][u] = 1;
    }
    
    void print()
    {
        for(int i = 0; i < v; i++)
        {
            std::cout << i << ": ";

            for(int j = 0; j < v; j++)
                std::cout << adj[i][j] << " ";

            std::cout << std::endl;
        }
    }

};


int main()
{
    return 0;
}