#include <iostream>
#include <vector>

struct DirectedGraf
{
    private:
    int Size;
    public:
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> weight;
    DirectedGraf(int size)
    {  
        DirectedGraf::Size = size;
        adj.resize(size, std::vector<int>(0));
        weight.resize(size, std::vector<int>(0));
    }

    int size()
    {        
        if(DirectedGraf::adj.size() != DirectedGraf::Size)
        {
            DirectedGraf::adj.resize(DirectedGraf::Size, std::vector<int>(0));
            DirectedGraf::weight.resize(DirectedGraf::Size, std::vector<int>(0));
        }
        return Size;
    }

    void expandGraf(int n)
    {
        Size += n;
    }
    
    // u -> v
    void addEdge(int u, int v, int weight)
    {
        if(DirectedGraf::adj.size() != DirectedGraf::Size)
        {
            DirectedGraf::adj.resize(DirectedGraf::Size, std::vector<int>(0));
            DirectedGraf::weight.resize(DirectedGraf::Size, std::vector<int>(0));
        }
        DirectedGraf::adj[u].push_back(v);
        DirectedGraf::weight[u].push_back(weight);
    }
};

void dfsPostEnum(int curr, std::vector<int> &topMap, std::vector<bool> &checked, DirectedGraf &g)
{
    checked[curr] = true;

    int depth = 0;

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
    int n = g.size();

    std::vector<int> topMap;
    std::vector<bool> checked(n, false);
    std::vector<int> treeDepth(n, 0);

    for(int i = 0; i < n; i++)
    {
        if(!checked[i])
        {
            dfsPostEnum(i, topMap, checked, g);
        }
    }

    for(int i = 0; i < n / 2; i++)
    {
        std::swap(topMap[i], topMap[n - i - 1]);
    }

    return topMap;
}

void dfsPrint(int curr, std::vector<int> &start, DirectedGraf &g)
{
    for(int i = 0; i < g.adj[curr].size(); i++)
    {
        int next = g.adj[curr][i];
        int taskTime = g.weight[curr][i];

        int earlyS = start[curr];
        int earlyE = earlyS + taskTime;

        int lateS = start[next] - taskTime;
        int lateE = start[next];

        int delay = start[next] - start[curr] - taskTime;

        std::cout << earlyS << " " << earlyE << " " << lateS << " " << lateE << " " << delay << std::endl; 
    }

}

void sol(DirectedGraf &g)
{
    int n = g.size();
    std::vector<int> topMap = dfsTopMap(g);

    std::vector<int> earliestStart(n, 0);
    std::vector<int> latestStart(n, 0);

    for(int i = 0; i < n; i++)
    {
        int curr = topMap[i];
        for(int j = 0; j < g.adj[curr].size(); j++)
        {
            int task = g.adj[curr][j];
            earliestStart[task] = std::max(earliestStart[task], earliestStart[i] + g.weight[curr][j]);
        }
    }

    latestStart[n - 1] = earliestStart[n - 1];
    for(int i = n - 2; i >= 0; i--)
    {
        //latestStart[i] = std::min(latestStart[i + 1] - )
    }
    

    std::cout << earliestStart[n - 1] << std::endl;

    for(int i = 0; i < n; i++)
    {
        dfsPrint(i, earliestStart, g);
    }

}

int main()
{
    int n; std::cin >> n;

    DirectedGraf g(n);

    int m; std::cin >> m;

    for(int i = 0; i < m; i++)
    {
        int u, v, weight; std::cin >> u >> v >> weight;

        g.addEdge(u, v, weight);
    }

    sol(g);

    return 0;
}
/*

    DODATI MAPE 

*/