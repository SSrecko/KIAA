#include <iostream>
#include <vector>
#include <unordered_map>

int nextpow2(int n)
{
    int k = 1;

    while(k < n) 
        k <<= 1;
    
    return k;
}

struct FenwickTree
{
    //  Fenwick tree which counts numbers less than x
    //  input is numbers from 1 to n where n is the amount 
    //  of different numbers in the original array
    
    std::vector<int> tree;
    int size;

    FenwickTree(int n)
    {
        size = nextpow2(n);
        FenwickTree::tree.resize(size + 1, 0);
        FenwickTree::size = size;
    }

    //  takes the element being put in, only index is important 
    //  cause elements are fromm 1 to n anyway

    void insertElement(int index)
    {
        while(index <= size)
        {
            tree[index]++;
            index += index & -index;
        }
    }

    int countInversions(int index)
    {
        int tindex = index;
        index--;
        int c = 0;
        while(index > 0)
        {
            c += tree[index];
            index -= index & -index;
        }

        insertElement(tindex);

        return c;
    }


};

void quicksort(int l, int r, std::vector<int>& arr)
{
    if(l >= r) return;

    int cur = l;
    for(int i = l + 1; i <= r; i++)
    {
        if(arr[i] < arr[l])
        {
            std::swap(arr[++cur], arr[i]);
        }
    }
    std::swap(arr[cur], arr[l]);

    quicksort(l, cur - 1, arr);
    quicksort(cur + 1, r, arr);
}


//  preforms a sort and remaps all the numbers to be from 1 to k 
//  (k is the number of unique numbers) 
int remap(std::unordered_map<int, int>& remap, std::vector<int> arr)
{
    quicksort(0, arr.size() - 1, arr);

    int k = 0;
    int prev = 1e6;
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] != prev)
        {
            remap[arr[i]] = ++k;
            prev = arr[i];
        }
    }

    return k;
}


int main()
{
    int n; std::cin >> n;

    std::vector<int> arr(n);

    for(int i = 0; i < n; i++) std::cin >> arr[i];

    std::unordered_map<int, int> remapKey;

    int k = remap(remapKey, arr);
    
    FenwickTree ft(k);

    int c = 0;

    for(int i = n - 1; i >= 0; i--)
    {
        c += ft.countInversions(remapKey[arr[i]]);
    }

    std::cout << c;

    return 0;
}