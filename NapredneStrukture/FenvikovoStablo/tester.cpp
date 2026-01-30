#include <iostream>
#include<cstdlib>
#include "FenwickTree.hpp"
int main()
{
    int n; std::cin >> n;
    
    std::vector<int> arr(n);

    for(int i = 0; i < n; i++) 
        std::cin >> arr[i];
    
    FenwickTree ft(arr);
    //segTree seg(arr);
    
    int score = 1;
    int attempts = 20;
    for(int i = 0; i < attempts; i++)
    {
        int l = rand() % arr.size();
        int r = rand() % arr.size();
        
        std::cout << l << " " << r << ": " << ft.segmentSum(l, r) << std::endl;
        /*
        if(ft.segmentSum(l, r) == seg.segSum(l, r))
        {
            std::cout << "true" << std::endl;
            score++;
        }
        */
    }

    std::cout << (double)score / attempts << "%";


    return 0;
}