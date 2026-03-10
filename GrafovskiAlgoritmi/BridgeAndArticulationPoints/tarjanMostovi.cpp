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

int TarjanLowlinkDFS(int curr, int parent, int &preindex, std::vector<std::pair<int, int>> &bridges, std::vector<int>& preTrav, 
                     std::vector<int> &lowlink, UndirectedGraph &g)
{
    //doubles as visited
    preTrav[curr] = ++preindex;
    lowlink[curr] = preindex;

    for(int i = 0; i < g.adj[curr].size(); i++)
    {
        int next = g.adj[curr][i];

        if(next == parent) continue;

        if(!preTrav[next])
        {
            lowlink[curr] = std::min(lowlink[curr], TarjanLowlinkDFS(next, curr, preindex, bridges, preTrav, lowlink, g));

            if(preTrav[curr] < lowlink[next])
                bridges.push_back(std::make_pair(curr, next));
        }
        else
        {
            lowlink[curr] = std::min(lowlink[curr], lowlink[next]);
        }
    }
    return lowlink[curr];
}

void sol(UndirectedGraph &g)
{
    int n = g.size;
    std::vector<std::pair<int, int>> bridges; 
    std::vector<int> lowlink(n, 0);
    std::vector<int> preTrav(n, 0);
    int preindex = 0;

    TarjanLowlinkDFS(0, -1, preindex, bridges, preTrav, lowlink, g);

    for(const auto &[u, v] : bridges)
    {
        std::cout << "(" << u << " " << v << ")" << std::endl;
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