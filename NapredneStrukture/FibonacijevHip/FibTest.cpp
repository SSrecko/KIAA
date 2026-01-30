#include <iostream>
#include <list>
#include <vector>
#include "FibonacciHeap.hpp"
#define TYPE int
#define ull unsigned long long

int main()
{
    FibHeap fibHeap;
    int n; std::cin >> n;
    std::vector<TYPE> arr(n);
    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    for(int i = 0; i < n; i++)
    {
        fibHeap.insert(arr[i]);
    }

    for(int i = 0; i < n; i++)
    {
        std::cout << fibHeap.getMin() << std::endl;
        fibHeap.extractMin();
    }

    return 0;
}