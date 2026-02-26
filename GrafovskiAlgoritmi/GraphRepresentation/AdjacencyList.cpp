#include <iostream>
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

    int v;
    std::vector<GNode> vertices;

    public:

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

    void addEdge(int u, int v)
    {
        vertices[u].addAdj(v);
        vertices[v].addAdj(u);
    }

};

int main()
{
    return 0;
}