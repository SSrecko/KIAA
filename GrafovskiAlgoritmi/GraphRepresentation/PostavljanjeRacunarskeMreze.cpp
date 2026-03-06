#include <iostream>
#include <vector>


struct UndirectedGraph
{
    int size;

    std::vector<std::vector<int>> adj;

    UndirectedGraph(int size)
    {
        UndirectedGraph::size = size;
        adj.resize(size);
    }

    void addEdge(int i, int j)
    {
        if(i < UndirectedGraph::size && j < UndirectedGraph::size && i != j)
        {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }

    int DFS(int currNode, std::vector<bool> &checked)
    {
        int c = 1;
        checked[currNode] = true;

        for(int i = 0; i < adj[currNode].size(); i++)
        {
            if(!checked[adj[currNode][i]])
            {
                c += DFS(adj[currNode][i], checked);
                
            }
        }

        return c;
    }

};

int sol(int ps, int pc, UndirectedGraph &g)
{
    int n = g.size;

    if(ps <= pc) 
    {
        return ps * n;
    }

    int dfsCount = 0;
    int checkedNodes = 0;

    std::vector<bool> checked = std::vector<bool>(n, false);

    for(int i = 0; i < n; i++)
    {
        if(!checked[i])
        {
            dfsCount++;
            checkedNodes += g.DFS(i, checked);
        }    
    }   

    return ps * dfsCount + pc * (n - dfsCount);
}

int main()
{
    int ps, pc; //price servers, price cables
    std::cin >> ps >> pc;

    int n, m; std::cin >> n >> m;


    UndirectedGraph g = UndirectedGraph(n);

    for(int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        
        g.addEdge(u, v);
    }

    std::cout << sol(ps, pc, g);

    return 0;
}