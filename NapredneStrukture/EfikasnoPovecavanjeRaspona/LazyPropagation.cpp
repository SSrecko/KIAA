#include <iostream>
#include <vector>



struct SegTree
{
    private:

    struct SegNode
    {
        int value;
        int adjust;

        SegNode()
        {
            value = 0; adjust = 0;
        }

        SegNode(int value)
        {
            this->value = value;
            this->adjust = 0;
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