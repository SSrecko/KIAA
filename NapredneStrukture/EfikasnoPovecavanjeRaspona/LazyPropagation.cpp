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

        void queue_update(int adjust, int set, int shouldSet)
        {
            if(shouldSet)
            {
                this->adjust = 0;
                this->set = set;
            }
            else if(this->shouldSet)
            {
                this->set += adjust;
            }
            else
            {
                this->adjust += adjust;   
            }
        }

        bool updated()
        {
            return !(adjust + shouldSet);
        }

        void update(int range)
        {
            value = set * range * shouldSet + (value +  range * adjust) * !shouldSet;

            SegNode propagateNode = SegNode();

            propagateNode.adjust = this->adjust;
            propagateNode.set = this->set;
            propagateNode.shouldSet = this->set;

            this->adjust = 0;
            this->set = 0;
            this->shouldSet = false;
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

    /*
        updates the current node, and pushes the required updates to lower nodes
    */

    void propagate(int nodeIndex, int range)
    {
        if(tree[nodeIndex].updated() || nodeIndex * 2 >= this->size) return;
        
        int lchild = nodeIndex * 2, rchild = nodeIndex * 2 + 1;
        
        //push the updates down
        tree[lchild].queue_update(tree[nodeIndex].adjust, tree[nodeIndex].set, tree[nodeIndex].shouldSet);
        tree[rchild].queue_update(tree[nodeIndex].adjust, tree[nodeIndex].set, tree[nodeIndex].shouldSet);

        //update currentNode and clear it's queue
        tree[nodeIndex].update(range);
    }

    void range_increase_update(int currNodeIndex, int currLeft, int currRight, int segLeft, int segRight, int value)
    {
        propagate(currNodeIndex, currRight - currLeft + 1);

        if(currLeft > segRight || currRight < segLeft) return;
        else if(currLeft >= segLeft && currRight <= segRight)
        {
            tree[currNodeIndex].queue_update(value, 0, false);
            propagate(currNodeIndex, currRight - currLeft + 1);
        }
        else
        {
            int s = currLeft + (currRight - currLeft) / 2;

            range_increase_update(currNodeIndex * 2, currLeft, s, segLeft, segRight, value);
            range_increase_update(currNodeIndex * 2 + 1, s + 1, currRight, segLeft, segRight, value);

            tree[currNodeIndex].value = tree[currNodeIndex * 2].value + tree[currNodeIndex * 2 + 1].value;
        }   
    }


    public:

    std::vector<SegNode> tree;
    int size;

    SegTree(std::vector<int> ogArr)
    {
        this->size = closestPow2(ogArr.size() * 2);
        tree.resize(this->size, SegNode());

        for(int i = this->size / 2; i - this->size / 2 < ogArr.size(); i++)
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

    void printTree()
    {
        std::cout << "Main Tree: \n" ;
        for(int i = 1; i < this->size; i++)
        {
            std::cout << i << ": " << tree[i].value << " | ";
            if(i + 1 == closestPow2(i + 1)) std::cout << std::endl;
        }
        std::cout << "Lazy Tree \n";
        for(int i = 1; i < this->size; i++)
        {
            std::cout << i << ": " << tree[i].adjust << " | ";
            if(i + 1 == closestPow2(i + 1)) std::cout << std::endl;
        }

    }

    void range_increase_update(int l, int r, int value)
    {
        range_increase_update(1, 0, this->size / 2 - 1, l, r, value);
    }
    


};



int main()
{
    int n = 12;
    std::vector<int> arr = {5, -2, 13, 0, 7, 7, -9, 4, 18, -1, 6, 2};

    SegTree st = SegTree(arr);

    st.range_increase_update(0, 3, 100);

    st.printTree();

    return 0;
}