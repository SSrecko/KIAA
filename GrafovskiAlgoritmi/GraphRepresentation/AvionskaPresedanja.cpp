#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

struct DirectedGraph
{
    int size;
    std::vector<std::vector<int>> adj;

    DirectedGraph(int size)
    {
        DirectedGraph::size = size;
        adj.resize(size);
    }
    void addNode()
    {
        size++;
    }

    //adds path from u to v (u -> v)
    void addEdge(int u, int v)
    {
        if(adj.size() != DirectedGraph::size)
            adj.resize(DirectedGraph::size);
        adj[u].push_back(v);
    }

    int bfsPath(int startNode, int endNode)
    {
        std::vector<int> step(size, -1);
        std::queue<int> q;
        
        q.push(startNode);
        step[startNode] = 0;

        while(!q.empty())
        {
            int curr = q.front();
            q.pop();

            for(int i = 0; i < adj[curr].size(); i++)
            {
                if(step[adj[curr][i]] == -1)
                {
                    q.push(adj[curr][i]);
                    step[adj[curr][i]] = step[curr] + 1;
                }
                if(adj[curr][i] == endNode)
                {
                    return step[endNode];
                }
            }
        }
        return step[endNode];
    }

};

void sol(DirectedGraph &g, int startNode, int endNode)
{
    int res = g.bfsPath(startNode, endNode);

    if(res == -1) std::cout << "ne" << std::endl;
    else std::cout << res << std::endl;
}

int main()
{
    std::unordered_map<std::string, int> dict;

    int m; std::cin >> m;
    int n = 0;
    DirectedGraph g(n);
    for(int i = 0; i < m; i++)
    {
        std::string a, b;
        std::cin >> a >> b;

        if(dict.find(a) == dict.end())
        {
            dict[a] = n;
            n++;
            g.addNode();
        }
        
        if(dict.find(b) == dict.end())
        {
            dict[b] = n;
            n++;
            g.addNode();
        }
        g.addEdge(dict[a], dict[b]);
    }

    int k; std::cin >> k;

    for(int i = 0; i < k; i++)
    {
        std::string a, b; std::cin >> a >> b;
        sol(g, dict[a], dict[b]);
    }

    return 0;
}