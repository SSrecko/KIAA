#include "DisjointSet.hpp"
#include <vector>
#include <iostream>

int coor(int i, int j, int m)
{
    return i * m + j; 
}

int main()
{
    int n, m; std::cin >> n >> m;

    DisjointSet ds(n * m);
    std::vector<std::vector<int>> mat(n, std::vector<int>(m, 0));


    for(int j = 0; j < m; j++)
    {
        ds.disjointUnion(0, coor(0, j, m));
        ds.disjointUnion(coor(n - 1, 0, m), coor(n - 1, j, m));
    }

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    int c = 0;
    while(ds.find(coor(0, 0, m)) != ds.find(coor(n - 1, 0, m)))
    {
        //std::cout << ds.find(coor(0, 0, m)) << " " << ds.find(coor(n - 1, 0, m)) << std::endl;
        int x, y; std::cin >> y >> x;
        mat[y][x] = 1; 
        
        for(int i = 0; i < 4; i++)
        {
            int tx = x + dx[i];
            int ty = y + dy[i];
            if(tx < m && tx >= 0 && ty < n && ty >= 0 && mat[ty][tx])
            {
                ds.disjointUnion(coor(y, x, m), coor(ty, tx, m));
            }
        }
        c++;
    }

    std::cout << "Trebalo je " << c << " polja\nMatrica: \n";

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
