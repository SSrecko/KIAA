#include <iostream>
#include <vector>

/*
    OPERATION COMPLEXITY

    Construction: O(n)
    
    elementAt (element of difference array): O(logn)
    
    elementAt (original element of the array): O(logn)

    updateElement

    rangeUpdate: O(logn)

    rangeQuery: O(nlogn) <- bad :(

*/

int nextPow2(int n)
{
    int k = 1;

    while(k < n) k <<= 1;

    return k;
}

int lowbit(int i)
{
    return (i & -i);
}

struct FDA //Fenwick Difference Array
{
    private:

    std::vector<int> bit;
    int ogSize, size;

    //0 indexed
    void updateBitElement(int i, int increment)
    {
        i++;
        while(i <= FDA::size)
        {
            bit[i] += increment;
            i += lowbit(i);
        }
   }

    public:

    //takes in a normal array
    FDA(std::vector<int>& arr)
    {
        FDA::ogSize = arr.size();

        //constructing difference array
        std::vector<int> diffArr(arr.size());
        diffArr[0] = arr[0];
        std::cout << diffArr[0] << " ";
        for(int i = 1; i < arr.size(); i++)
        {
            diffArr[i] = arr[i] - arr[i - 1];
            std::cout << diffArr[i] << " ";
        }
        std::cout << std::endl;

        //alloc Fenwick Tree
        FDA::size = nextPow2(diffArr.size()) + 1;
        FDA::bit.resize(FDA::size, 0);

        //construct Fenwick tree, evil hack
        for(int i = 1; i <= FDA::size; i++)
        {   
            if(i - 1 < diffArr.size())
                FDA::bit[i] += diffArr[i - 1];
            
            if(i + lowbit(i) <= FDA::size)
                FDA::bit[i + lowbit(i)] += FDA::bit[i];
        }
    }

    //i is 0 indexed
    int elementAt(int i)
    {
        i++;

        int sum = 0;

        while(i)
        {
            sum += bit[i];
            i -= lowbit(i);
        }

        return sum;
    }

    //i is 0 indexed
    int getElementOfDiff(int i)
    {
        i++;

        int j = i - 1;
        int sum = FDA::bit[i];
        
        while(j > i - lowbit(i))
        {
            sum -= bit[j];
            j -= lowbit(j);
        }

        return sum;
    }

    // 0 indexed, inclusive ([l, r])
    void rangeUpdate(int l, int r, int increment)
    {
        updateBitElement(l, increment);
        if(r + 1 < FDA::ogSize)
            updateBitElement(r + 1, -increment);
    }

    //0 indexed
    void pointUpdate(int i, int incremenet)
    {
        rangeUpdate(i, i, incremenet);
    }

    // Range query 
    // 0 indexed, inclusive
    int segSum(int l, int r)
    {
        int sum = 0;
        for(int i = l; i <= r; i++)
        {
            sum += elementAt(i);
        }
        return sum;
    }

};

int main()
{
    int n; std::cin >> n;
    std::vector<int> arr(n);
    for(int i = 0; i < n; i++) std::cin >> arr[i];

    FDA fda(arr);

    for(int i = 0; i < n; i++)
        std::cout << fda.elementAt(i) << " ";

    int l, r, inc; std::cin >> l >> r >> inc;

    fda.rangeUpdate(l, r, inc);

    for(int i = 0; i < n; i++)
        std::cout << fda.elementAt(i) << " ";
    
    
    return 0;
}