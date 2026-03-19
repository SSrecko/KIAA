#include <iostream>
#include <vector>
#include <set>
#include <limits>
#define fi first
#define se second
struct UndirectedGraph
{
    std::vector<std::vector<std::pair<int, int>>> adj;
    int size;

    UndirectedGraph(int size)
    {
        this->size = size;
        adj.resize(size);
    }

    void addEdge(int u, int v, int weight)
    {
        adj[u].push_back(std::make_pair(v, weight));
        adj[v].push_back(std::make_pair(u, weight));        
    }

    void printGraph()
    {
        int s = 0;
        for(int i = 0; i < size; i++)
        {
            std::cout << i << ": " << std::endl;
            for(const auto &[dest, weight] : adj[i])
            {
                std::cout << "\t" << dest << ", " << weight << std::endl;
                s += weight;
            }
        }
        std::cout << "Total length: " << s / 2;
    }

};

UndirectedGraph Prim(UndirectedGraph &g)
{
    int n = g.size;
    std::set<std::pair<int, std::pair<int, int>>> q; //(weight, (origin, destination))

    std::vector<bool> checked(n, false);
    
    checked[0] = true;
    for(auto &[dest, weight] : g.adj[0])
    {
        q.insert({weight, {0, dest} });
    }
    
    UndirectedGraph mst(n);

    while(!q.empty())
    {
        int weight = q.begin()->fi;
        int org = q.begin()->se.fi;
        int dest = q.begin()->se.se;
        q.erase(q.begin());

        if(checked[dest] == false)
        {
            mst.addEdge(org, dest, weight);
            checked[dest] = true;

            for(int i = 0; i < g.adj[dest].size(); i++)
            {
                if(checked[g.adj[dest][i].fi] == false)
                    q.insert({ g.adj[dest][i].se,  {dest,  g.adj[dest][i].fi} });
            }

        }
    }

    return mst;
}


void sol(UndirectedGraph &g)
{
    UndirectedGraph mst = Prim(g);

    mst.printGraph();

}

int main()
{
    int n; std::cin >> n;
    UndirectedGraph g(n);

    int m; std::cin >> m;

    for(int i = 0; i < m; i++)
    {
        int u, v, weight; std::cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    sol(g);    


    return 0;
}