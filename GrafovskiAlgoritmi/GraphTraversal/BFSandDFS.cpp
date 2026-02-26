#include <iostream>
#include <queue>
#include <stack>
#include <vector>

struct Graph
{
    private:

    struct GNode
    {
        std::vector<int> adjList;
        int adjc;
        int val;

        GNode(int value, std::vector<int> adjList)
        {
            adjc = adjList.size();
            this->adjList = adjList;
            val = value;
        }

        GNode(int value)
        {
            val = value;
            adjList.resize(0);
            adjc = 0;
        }

        void addAdj(int u)
        {
            if(!neighbours(u))
            {
                adjList.push_back(u);
                adjc++;
            }
        }

        bool neighbours(int u)
        {
            for(int i = 0; i < adjc; i++)
                if(adjList[i] == u)
                    return true;
            return false;
        }

    };


    public:

    int v;
    std::vector<GNode> vertices;

    Graph(int vertexCount, std::vector<std::vector<int>> adjLists)
    {
        v = vertexCount;

        vertices.resize(v, GNode(0));

        for(int i = 0; i < v; i++)
        {
            vertices[i].adjList = adjLists[i];
            vertices[i].adjc = adjLists[i].size();
        }

    }

    Graph(int vertexCount)
    {
        v = vertexCount;
        vertices.resize(v, GNode(0));
    }

    void addEdge(int u, int v)
    {
        vertices[u].addAdj(v);
        vertices[v].addAdj(u);
    }

    std::vector<int> getAdj(int u)
    {
        return vertices[u].adjList;
    }

};


void BFS(Graph G, int startNode)
{
    std::vector<int> checked(G.v, 0);

    std::queue<int> q;
    q.push(startNode);
    checked[startNode] = 1;
    while(!q.empty())
    {
        int curr = q.front();
        q.pop();

        std::vector<int> tmp = G.getAdj(curr);

        for(int i = 0; i < tmp.size(); i++)
        {
            if(!checked[tmp[i]])
            {
                q.push(tmp[i]);
                checked[tmp[i]] = 1;
            }
        }

        std::cout << curr << std::endl;
    }
    
}

void DFS(Graph G, int startNode)
{
    std::vector<int> checked(G.v, 0);

    std::queue<int> s;
    s.push(startNode);
    checked[startNode] = 1;
    while(!s.empty())
    {
        int curr = s.top();
        s.pop();

        std::vector<int> tmp = G.getAdj(curr);

        for(int i = 0; i < tmp.size(); i++)
        {
            if(!checked[tmp[i]])
            {
                s.push(tmp[i]);
                checked[tmp[i]] = 1;
            }
        }

        std::cout << curr << std::endl;
    }
    
}

int main()
{
    int n; std::cin >> n;
    Graph G(n);

    int k; std::cin >> k;

    for(int i = 0; i < k; i++)
    {
        int u, v; std::cin >> u >> v;
    
        G.addEdge(u, v);
    }

    
    int start; std::cin >> start;

    BFS(G, start);

    return 0;
}
