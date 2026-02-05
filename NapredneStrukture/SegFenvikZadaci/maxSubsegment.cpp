#include <iostream>
#include <vector>
#define TYPE int

int closestPow2(int n)
{
    int k = 1;

    while(k < n) k <<= 1;

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

segNode combine(segNode segL, segNode segR)
{
    int segSum = segL.segSum + segR.segSum;

    int maxPrefix = std::max(segL.prefixSum, segL.segSum + segR.prefixSum);

    int maxSufix = std::max(segR.sufixSum, segR.segSum + segL.sufixSum);

    int maxSub = std::max(segL.sufixSum + segR.prefixSum, std::max(segL.maxSub, segR.maxSub));


    return segNode(segSum, maxPrefix, maxSufix, maxSub);
}


struct SegTree
{
    std::vector<segNode> tree;
    int size;

    SegTree(std::vector<int> arr)
    {
        int size = closestPow2(arr.size()) * 2;

        tree.resize(size);

        for(int i = size / 2, ti = 0; i < size; i++, ti++)
        {
            if(ti < arr.size())
            {
                tree[i] = segNode(arr[ti], std::max(arr[ti], 0), std::max(arr[ti], 0), std::max(arr[ti], 0));
            }
            else tree[i] = segNode();
        }

        for(int i = size / 2 - 1; i > 0; i--)
        {
            segNode segL = tree[i * 2];
            segNode segR = tree[i * 2 + 1];


            tree[i] = combine(tree[i * 2] , tree[i * 2 + 1]);
        }

        this->size = size;

    };

    int maxSubSeg(int l, int r)
    {
        l++, r++;

        int maxl = 0, maxr;

        while(l <= r)
        {
            if(l % 2)
            {
                segNode t = combine(tree[l], tree[l / 2 + 1]);
                maxl = t.maxSub;
            }
            l /= 2;

            if(r % 2)
            {
                segNode t = combine(tree[r], tree[r / 2 - 1]);
                maxr = t.maxSub;
            }
            r /= 2;

        }

        return std::max(maxl, maxr);
    }

};

int main()
{
    int n; std::cin >> n;

    std::vector<int> arr(n);

    for(int i = 0; i < n; i++) std::cin >> arr[i];

    SegTree st(arr);

    for(int i = 0; i < n; i++)
    {
        int l, r; std:: cin >> l >> r;
        std::cout << st.maxSubSeg(l, r);

    }

    return 0;
}