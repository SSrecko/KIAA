#include <iostream>
#include <vector>

int rangeSum(std::vector<std::vector<int>> &prefix, int i1, int j1, int i2, int j2)
{
    return prefix[i2 + 1][j2 + 1] - prefix[i2 + 1][j1] - prefix[i1][j2 + 1] + prefix[i1][j1];
}

int elementAt(std::vector<std::vector<int>> &prefix, int i, int j)
{
    return rangeSum(prefix, i, j, i, j);
}

int main()
{
    int n, m; std::cin >> n >> m;

    std::vector<std::vector<int>> a(n + 1, std::vector<int>(m + 1));

    for(int i = 0; i < n; i++) a[i][0] = 0;
    for(int j = 0; j < m; j++) a[0][j] = 0;

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= m; j++)
        {
            int k; std::cin >> k;
            a[i][j] = k + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    std::cout << rangeSum(a, 2, 0, 2, 2);

    return 0;
}