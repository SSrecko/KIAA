#include <iostream>
#include "segTree.hpp"

int main()
{
    int n; std::cin >> n;

    std::vector<int> arr(n);

    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    segTree t(arr);

    t.increase(4, 20);
    t.increase(6, 9);
    t.increase(6, 7);
    t.increase(3, 60);

    while(true)
    {
        int l, r; std::cin >> l >> r;

        std::cout << t.segSum(l, r) << std::endl;
    }

    return 0;
}