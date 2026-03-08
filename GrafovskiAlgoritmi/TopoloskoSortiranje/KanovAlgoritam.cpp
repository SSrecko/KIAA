#include <iostream>
#include <vector>
#include <queue>

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

    std::vector<int> createInDegree()
    {
        std::vector<int> inDegree(size, 0);

        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < adj[i].size(); j++)
            {
                inDegree[adj[i][j]]++;
            }
        }

        return inDegree;
    }
};

std::vector<int> Kahn(DirectedGraf g)
{
    std::vector<int> topMap;
    std::vector<int> inDegree = g.createInDegree();
    std::queue<int> q;

    int n = g.size;

    for(int i = 0; i < n; i++)
    {
        if(!inDegree[i])
            q.push(i);
    }

    int c = 0;

    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        topMap.push_back(curr);

        for(int i = 0; i < g.adj[curr].size(); i++)
        {
            inDegree[g.adj[curr][i]]--;
            if(inDegree[g.adj[curr][i]] == 0)
                q.push(g.adj[curr][i]);
        }
        c++;
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

    std::vector<int> topMap = Kahn(g);

    for(int i = 0; i < n; i++)
    {
        std::cout << topMap[i] << " ";
    }

    return 0;
}