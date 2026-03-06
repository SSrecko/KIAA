#include <iostream>
#include <vector>
#include <stack>
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

    //checked: 0 = unvisited, 1 = black, -1 = red
    int DFS(int startNode, std::vector<int> &checked)
    {
        std::stack<int> s;
        
        checked[startNode] = 1;
        s.push(startNode);

        while(!s.empty())
        {
            int curr = s.top();
            s.pop();

            for(int i = 0; i < adj[curr].size(); i++)
            {
                if(!checked[adj[curr][i]])
                {
                    checked[adj[curr][i]] = checked[curr] * -1;
                    s.push(adj[curr][i]);
                }
                else if(checked[curr] == checked[adj[curr][i]])
                    return 0;
            }
        }
        return 1;
    }

};

void sol(UndirectedGraph &g)
{
    std::vector<int> checked = std::vector<int>(g.size, 0);

    if(g.DFS(0, checked))
    {
        for(int i = 0; i < g.size; i++)
        {
            if(checked[i] == checked[0]) 
                std::cout << i << " ";
        }
    }
    else
    {
        std::cout << '-';
    }
}

int main()
{
    int n, m;
    std::cin >> n >> m;

    UndirectedGraph g = UndirectedGraph(n);

    for(int i = 0; i < m; i++)
    {
        int u, v; std::cin >> u >> v;
        g.addEdge(u, v);
    }

    sol(g);

    return 0;
}