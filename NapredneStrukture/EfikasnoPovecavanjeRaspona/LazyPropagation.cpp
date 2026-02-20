#include <iostream>
#include <vector>



struct SegTree
{
    //Segment Tree operating witih addition
    /*
        GOALS:

        Point Query (logn)

        Range Query (logn)

        Point Update (logn)

        Range Update (logn)

        Range Set (log n)

    */ 
    private:

    struct SegNode
    {
        int value;
        int adjust;
        int set;
        bool shouldSet;

        SegNode()
        {
            value = 0; adjust = 0; set = 0;
            shouldSet = false;
        }

        SegNode(int value)
        {
            this->value = value;
            this->adjust = 0;
            this->set = 0;
            this->shouldSet = false;
        }

        bool updated()
        {
            return set + adjust;
        }

    };

    int closestPow2(int n)
    {
        int k = 1;
        while(k < n)
        {
            k <<= 1;
        }

        return k;
    }


    public:

    std::vector<SegNode> tree;
    int size;

    SegTree(std::vector<int> ogArr)
    {
        this->size = closestPow2(ogArr.size() * 2);
        tree.resize(this->size, SegNode());

        for(int i = this->size / 2; i < this->size; i++)
        {
            tree[i].value = ogArr[i - this->size / 2];
        }

        for(int i = this->size / 2 - 1; i > 0; i--)
        {
            tree[i].value = tree[2 * i].value + tree[2 * i + 1].value;
        }
    }

    SegTree(int n)
    {
        this->size = closestPow2(n) * 2;
        tree.resize(this->size, SegNode());
    }

    
};



int main()
{
    return 0;
}