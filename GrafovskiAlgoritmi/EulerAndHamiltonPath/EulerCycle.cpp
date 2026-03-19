#include <iostream>
#include <deque>
#include <vector>
#include <stack>

struct DirectedGraph
{
    std::vector<std::vector<int>> adj;
    int size;

    DirectedGraph(int size)
    {
        this->size = size;
        adj.resize(size);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

};

std::vector<int> EulerPath(DirectedGraph &g)
{
    std::stack<int> s;

    std::deque<int> path;

    s.push(0);

    while(!s.empty())
    {
        int curr = s.top();

        if(!g.adj[curr].empty())
        {
            s.push(g.adj[curr].back());
            g.adj[curr].pop_back();
        }
        else
        {
            path.push_front(curr);
            s.pop();
        }
    }

    std::vector<int> eupath;
    while(!path.empty())
    {
        eupath.push_back(path.front());
        path.pop_front();
    }

    return eupath;
}



int main()
{
    int n; std::cin >> n;
    DirectedGraph g(n);

    int m; std::cin >> m;

    for(int i = 0; i < m; i++)
    {
        int u, v;
        std::cin >> u >> v;
        g.addEdge(u, v); 
    }

    std::vector<int> eulerPath = EulerPath(g);

    for(int i = 0; i < eulerPath.size(); i++)
    {
        std::cout << eulerPath[i] << " ";
    }
    std::cout << std::endl;
}