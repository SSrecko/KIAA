#include "FenwickTree.hpp"

int nextPow2(int n)
{
    int k = 1;

    while(k < n)
        k <<= 1;

    return k;

}

int responsibilityCount(int n)
{
    if(n == 0) return 0;
    int c = 0;

    while((n & 1) == 0)
    {
        n >>= 1;
        c++;
    }
    return c;
}


FenwickTree::FenwickTree(std::vector<TYPE> originalArr)
{
    int newSize = nextPow2(originalArr.size());

    FenwickTree::tree.resize(newSize + 1, 0);
    FenwickTree::size = newSize;

    for(int i = 1; i <= originalArr.size(); i++)
    {   
        int t = i;
        while(t <= FenwickTree::size)
        {
            FenwickTree::tree[t] += originalArr[i - 1];
            t += t & -t; 
        }
    }
}

FenwickTree::FenwickTree(int size)
{
    int newSize = nextPow2(size);

    FenwickTree::tree.resize(newSize + 1, 0);
    FenwickTree::size = newSize;
}

void FenwickTree::updateElement(int index, int addValue)
{
    index++;
    index = index & -index;
    while(index < FenwickTree::size)
    {
        FenwickTree::tree[index] += addValue;
    }
}

TYPE FenwickTree::segmentSum(int l, int r)
{
    if(l > r) std::swap(l, r);

    r++;

    int lresp = 1 << responsibilityCount(l);
    int rresp = 1 << responsibilityCount(r);

    int sum = 0;

    while(r)
    {
        sum += FenwickTree::tree[r];
        r -= rresp;
        rresp = 1 << responsibilityCount(r);
    }

    while(l)
    {
        sum -= FenwickTree::tree[l];
        l -= lresp;
        lresp = 1 << responsibilityCount(l);
    }

    return sum;
}

TYPE FenwickTree::elementAt(int index)
{
    return segmentSum(index, index);
}