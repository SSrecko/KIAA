#include <iostream>
#include <vector>

struct DirectedGraf
{
    int size;
    std::vector<std::vector<int>> adj;

    DirectedGraf(int size)
    {  
        DirectedGraf::size = size;
        adj.resize(size, std::vector<int>(0));
    }

    void expandGraf(int n)
    {
        size += n;
    }
    
    // u -> v
    void addEdge(int u, int v)
    {
        if(DirectedGraf::adj.size() != DirectedGraf::size)
        {
            DirectedGraf::adj.resize(DirectedGraf::size, std::vector<int>(0));
        }
        DirectedGraf::adj[u].push_back(v);
    }
};

void dfsPostEnum(int curr, std::vector<int> &topMap, std::vector<bool> &checked, DirectedGraf &g)
{
    checked[curr] = true;

    for(int i = 0; i < g.adj[curr].size(); i++)
    {
        if(!checked[g.adj[curr][i]])
        {
            dfsPostEnum(g.adj[curr][i], topMap, checked, g);
        }
    }

    topMap.push_back(curr);
}
//asumes the graph i acylic, needs more vectors to check if it is or not
std::vector<int> dfsTopMap(DirectedGraf &g)
{
    int n = g.size;

    std::vector<int> topMap;
    std::vector<bool> checked(n, false);

    for(int i = 0; i < n; i++)
    {
        if(!checked[i])
        {
            dfsPostEnum(i, topMap, checked, g);
        }
    }

    for(int i = 0; i < n / 2; i++)
    {
        std::swap(topMap[i], topMap[n - i]);
    }

    return topMap;
}

int main()
{
    int n; std::cin >> n;

    DirectedGraf g(n);

    int m; std::cin >> m;

    for(int i = 0; i < m; i++)
    {
        int u, v; std::cin >> u >> v;

        g.addEdge(u, v);
    }

    std::vector<int> topMap = dfsTopMap(g);

    for(int i = 0; i < n; i++)
    {
        std::cout << topMap[i] << " ";
    }

    return 0;
}