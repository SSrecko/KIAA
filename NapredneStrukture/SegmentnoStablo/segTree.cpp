#include "segTree.hpp"

#define ll long long

int powerOf2(int n)
{
    int k = 1;
    while(n >= k) k <<= 1; 

    return k;
}


segTree::segTree(std::vector<int> arr)
{
    int n = arr.size();

    int size = powerOf2(n) * 2;
    segTree::tree.resize(size);
    
    for(int i = size / 2; i < size; i++)
    {
        if(i - size / 2 < n)
            segTree::tree[i] = arr[i - size / 2];
        else segTree::tree[i] = 0;
    }

    for(int i = size / 2 - 1; i >= 1; i--)
    {
        segTree::tree[i] = segTree::tree[2 * i] + segTree::tree[2 * i + 1];
    }

    segTree::size = size;
}

ll segTree::segSum(int l, int r)
{
    if(r < l) std::swap(l, r);

    l += segTree::size / 2;
    r += segTree::size / 2;
    
    ll res = 0;

    while(l <= r)
    {
        if(l % 2) 
            res += segTree::tree[l++];
        l /= 2;

        if(r % 2 == 0) 
            res += segTree::tree[r--];
        r /= 2; 
    }

    return res;

}

void segTree::increase(int i, int value)
{
    i += segTree::size / 2;
    while(i)
    {
        segTree::tree[i] += value;
        i /= 2;
    }
}

void segTree::enter(int i, int value)
{
    value -= segTree::tree[i + segTree::size / 2];
    increase(i, value);
}