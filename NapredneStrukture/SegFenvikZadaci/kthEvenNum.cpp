#include <iostream>
#include <vector>

struct SegNode
{
    int evenc;
    int num;

    SegNode(int num)
    {
        this->evenc = !(num % 2);

        SegNode::num = num;
    }

    SegNode(SegNode l, SegNode r)
    {
        evenc = l.evenc + r.evenc;
        num = -1;
    }

    int value()
    {
        return num;
    }

};

int nextPow2(int n)
{
    int k = 1;
    
    while(k < n) k <<= 1;

    return k;
}

struct SegTree
{
    std::vector<SegNode> tree;
    int size;
    int ogSize;
    SegTree(int n)
    {
        SegTree::ogSize = n;

        SegTree::size = nextPow2(n) * 2;
        
        SegTree::tree.resize(size, SegNode(0));

        for(int i = size / 2 - 1; i > 0; i--)
        {
            tree[i] = SegNode(tree[2 * i], tree[2 * i + 1]);
        }
    }

    //zero indexed
    void insertElement(int index, int num)
    {
        index += size / 2 - 1;

        SegTree::tree[index] = SegNode(num);

        index /= 2;

        while(index)
        {
            SegTree::tree[index] = SegNode(tree[index * 2], tree[index * 2 + 1]);

            index /= 2;
        }

    }

    int kthEvenNum(int k)
    {
        int i = 1;
        while(i < SegTree::size / 2)
        {

            if(SegTree::tree[i * 2].evenc < k)
            {
                k -= SegTree::tree[i * 2].evenc;
                i = i * 2 + 1;
            }
            else i *= 2;
        }

        int res = i - SegTree::size / 2 + 1;

        if(res <= SegTree::ogSize) return res;
        else return -1;
    }

};


int main()
{
    int n; std::cin >> n;

    SegTree st(n);

    int m; std::cin >> m;
    for(int i = 0; i < m; i++)
    {
        char key; std::cin >> key;

        if(key == 'u')
        {
            int index, value;
            std::cin >> index >> value;

            st.insertElement(index, value);
        }
        else
        {
            int k; std::cin >> k;
            

            std::cout << st.kthEvenNum(k) << std::endl;
        }
    }

    return 0;
}