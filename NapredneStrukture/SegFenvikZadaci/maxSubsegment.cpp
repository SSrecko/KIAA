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
    segNode(TYPE segSum)
    {
        this->segSum = segSum;
        this->prefixSum = std::max(segSum, 0);
        this->sufixSum = std::max(segSum, 0);
        this->maxSub = std::max(segSum, 0);
    }
    segNode()
    {
        this->segSum = 0;
        this->prefixSum = 0;
        this->sufixSum = 0;
        this->maxSub = 0;
    }

    void toString()
    {
        std::cout << 
            "segSum: " << segSum << std::endl <<
            
            "prefix: " << prefixSum << std::endl <<
            
            "sufix: " << sufixSum << std::endl <<
            
            "goat: " << maxSub << std::endl;
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

    SegTree(const std::vector<int>& arr)
    {
        int size = closestPow2(arr.size()) * 2;

        tree.resize(size, segNode());

        for(int i = size / 2, ti = 0; i < size; i++, ti++)
        {
            if(ti < arr.size())
            {
                tree[i] = segNode(arr[ti]);
            }
            else break;
        }

        for(int i = size / 2 - 1; i > 0; i--)
        {
            tree[i] = combine(tree[i * 2], tree[i * 2 + 1]);
        }

        this->size = size;

    };

    int maxSubSeg(int l, int r)
    {
        l += SegTree::size / 2, r += SegTree::size / 2;


        int maxl = 0, maxr;

        segNode lnode = SegTree::tree[l];
        segNode rnode = SegTree::tree[r];
        
        if(l == r) return lnode.maxSub;

        while(l / 2 != r / 2)
        {

            if(l % 2 == 0)
            {
                lnode = combine(lnode, SegTree::tree[l + 1]);
            }
            l /= 2;


            if(r % 2)
            {
                rnode = combine(SegTree::tree[r - 1], rnode);
            }
            r /= 2;            
            /* TESTER
            std::cout << "\nL: " << l << "\nLnode: \n"; 
            lnode.toString();            
            std::cout << "\nR: " << r << "\nRnode: \n"; 
            rnode.toString();*/
        }

        return combine(lnode, rnode).maxSub;
    }


    void updateComponent(int index, int newValue)
    {
        index += SegTree::size / 2;

        SegTree::tree[index] = segNode(newValue);
        index /= 2;
        while(index)
        {
            SegTree::tree[index] = combine(SegTree::tree[index * 2], SegTree::tree[index * 2 + 1]);
            index /= 2;
        }
        
    }
};

int main()
{
    int n; std::cin >> n;

    std::vector<int> arr(n);

    for(int i = 0; i < n; i++) std::cin >> arr[i];

    SegTree st(arr);

    int k; std::cin >> k;

    for(int i = 0; i < k; i++)
    {
        char key; std::cin >> key;
        int l, r; std:: cin >> l >> r;

        if(key == 's')
            std::cout << st.maxSubSeg(l, r) << std::endl;
        else st.updateComponent(l, r);

    }

    return 0;
}