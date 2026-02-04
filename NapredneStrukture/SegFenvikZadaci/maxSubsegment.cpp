#include <iostream>
#include <vector>
#define TYPE int

int closestPow2(int n)
{
    int k = 1;

    if(k < n) k <<= 1;

    return k;
}

struct segNode
{
    TYPE segSum, prefixSum, sufixSum, maxSub;

    segNode(TYPE segSum, TYPE prefixSum, TYPE sufixSum, TYPE maxSub)
    {
        this->segSum = segSum;
        this->prefixSum = prefixSum;
        this->sufixSum = sufixSum;
        this->maxSub = maxSub;
    }

    segNode()
    {
        this->segSum = 0;
        this->prefixSum = 0;
        this->sufixSum = 0;
        this->maxSub = 0;
    }

};

struct SegTree
{
    std::vector<segNode> tree;
    int size;

    SegTree(std::vector<int> arr)
    {
        int size = closestPow2(arr.size()) * 2;

        tree.resize(size + 1);

        for(int i = size / 2 + 1, ti = 0; i <= size; i++, ti++)
        {
            if(ti < arr.size())
            {
                tree[i] = segNode(arr[ti], std::max(arr[ti], 0), std::max(arr[ti], 0), std::max(arr[ti], 0));
            }
            else tree[i] = segNode();
        }

        for(int i = size / 2; i > 0; i--)
        {
            segNode segL = tree[i * 2];
            segNode segR = tree[i * 2 + 1];


            int segSum = segL.segSum + segR.segSum;

            int maxPrefix = std::max(segL.prefixSum, segSum);

            int maxSufix = std::max(segR.sufixSum, segSum);

            int maxSub = std::max(segL.maxSub, segR.maxSub);

            tree[i] = segNode(segSum, maxPrefix, maxSufix, maxSub);
        }



    };

};

int main()
{


    return 0;
}