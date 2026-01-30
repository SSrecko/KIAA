#include <iostream>
#include "segTree.hpp"

int main()
{
    std::vector<int> arr = { 3 };

    segTree t(arr);

    int l, r; std::cin >> l >> r;

    std::cout << t.segSum(l, r);


    return 0;
}