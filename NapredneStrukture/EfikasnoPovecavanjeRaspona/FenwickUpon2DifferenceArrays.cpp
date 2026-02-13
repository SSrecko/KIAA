#include <iostream>
#include <vector>

int nextPow2(int n)
{
    int k = 1;
    while(k < n) k <<= 1;

    return k;
}

int lowbit(int i)
{
    return i & -i;
}


struct FDA
{
    std::vector<int> bit;
    int size, ogsize;

    // 0 indexed
    void updateBit(int index, int value)
    {
        index++;
        while(index <= FDA::size)
        {
            bit[index] += value;
            index += lowbit(index);
        }
    }

    FDA(int n)
    {
        FDA::ogsize = n;
        FDA::size = nextPow2(n);

        bit.resize(FDA::size, 0);
    }

    FDA(std::vector<int>& arr)
    {
        FDA::ogsize = arr.size();
        FDA::size = nextPow2(arr.size());

        bit.resize(FDA::size + 1, 0);
        
        int curr = arr[0];
        
        for(int i = 1; i <= FDA::size; i++)
        {
            bit[i] += curr;
            if(i + lowbit(i) <= FDA::size)
                bit[i + lowbit(i)] += bit[i];

            if(i < arr.size())
            {
                curr = arr[i] - arr[i - 1];
            }
            else curr = 0;
        }
    }
    //0 indexed
    int point_query(int index)
    {
        index++;
        int sum = 0;

        while(index)
        {
            sum += bit[index];
            index -= lowbit(index);
        }

        return sum;
    }

    //0 indexed
    void point_update(int index, int value)
    {
        int diff = value - point_query(index);
        
        updateBit(index, diff);
        updateBit(++index, -diff);
    }
    //0 indexed, inclusive
    void range_update(int l, int r, int value)
    {
        updateBit(l, value);
        if(r + 1 < FDA::size)
        {
            updateBit(r + 1, -value);
        }
    }

};

struct DoubleFDA
{
    
}


int main()
{
    int n; std::cin >> n;
    
    std::vector<int> arr(n);

    for(int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    FDA fda(arr);

    for(int i = 0; i < n; i++)
    {
        std::cout << fda.point_query(i) << " ";
    }
    std::cout << std::endl;

    fda.point_update(2, 100);
    fda.point_update(3, 150);
    fda.point_update(5, 200);
    fda.point_update(7, 250);

    fda.range_update(3, 6, 5000);
    

    for(int i = 0; i < n; i++)
    {
        std::cout << fda.point_query(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}