#include <iostream>
#include <vector>

struct UndirectedGraph
{
    std::vector<std::vector<int>> adj;
    int size;

    UndirectedGraph(int size)
    {
        this->size = size;
        adj.resize(this->size);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

};

void ArticDFS(int curr, int parent, int &preIndex, std::vector<int> &articPoints, std::vector<int> &preTrav, std::vector<int> &lowlink, UndirectedGraph &g)
{
    preTrav[curr] = lowlink[curr] = ++preIndex;

    int indieChildren = 0, dfsChildren = 0;

    for(const auto &next : g.adj[curr])
    {
        if(next == parent) continue;

        if(preTrav[next] == 0)
        {
            dfsChildren++;
            ArticDFS(next, curr, preIndex, articPoints, preTrav, lowlink, g);
            lowlink[curr] = std::min(lowlink[curr], lowlink[next]);

            if(preTrav[curr] <= lowlink[next])
                indieChildren++;
        }
        else
        {
            lowlink[curr] = std::min(lowlink[curr], lowlink[next]);
        }
    }

    if(parent == -1 && dfsChildren >= 2)
    {
        articPoints.push_back(curr);
    }
    else if(parent != -1 && indieChildren > 0)
        articPoints.push_back(curr);

}


void sol(UndirectedGraph &g)
{
    int n = g.size, preIndex = 0;
    std::vector<int> articPoints, preTrav(n, 0), lowlink(n, 0);

    ArticDFS(0, -1, preIndex, articPoints, preTrav, lowlink, g);

    for(int u : articPoints)
    {
        std::cout <<  u << std::endl;
    }

}


int main()
{
    int n; std::cin >> n;
    UndirectedGraph g(n);

    int m; std::cin >> m;

    for(int i = 0; i < m; i++)
    {
        int u, v; std::cin >> u >> v;
        g.addEdge(u, v);
    }

    sol(g);

    return 0;
}
