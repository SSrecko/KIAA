#include <iostream>
#include <vector>

int nextPow2(int n)
{
    int k = 1;
    while(k < n) k <<= 1;

    return k;
}

struct FDA
{
    std::vector<int> bit;
    int size, ogsize;
    
    FDA(int n)
    {
        FDA::ogsize = n;
        FDA::size = nextPow2(n);

        bit.resize(FDA::size, 0);
    }

    FDA(std::vector<int>& arr)
    {
        FDA::ogsize = arr.size();
        FDA::size = nextPow2(arr.size()) + 1;

        bit.resize(FDA::size, 0);

        
        for(int i = 1; i < FDA::size; i++)
        {

        }
    }

};

int main()
{
    return 0;
}