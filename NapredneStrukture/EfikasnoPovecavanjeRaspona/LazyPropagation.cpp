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

        Range Update (logn) done

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

    void propagateAndUpdate(int nodeIndex, int range)
    {
        //nothing to do
        if(tree[nodeIndex].updated()) return;
        //nowhere to propagate (leaf node)
        if(nodeIndex * 2 >= this->size)
        {
            tree[nodeIndex].update(range);
            return;
        }

        int lchild = nodeIndex * 2, rchild = nodeIndex * 2 + 1;
        
        //push the updates down
        tree[lchild].queue_update(tree[nodeIndex].adjust, tree[nodeIndex].set, tree[nodeIndex].shouldSet);
        tree[rchild].queue_update(tree[nodeIndex].adjust, tree[nodeIndex].set, tree[nodeIndex].shouldSet);

        //update currentNode and clear it's queue
        tree[nodeIndex].update(range);
    }

    void range_increase_update(int currIndex, int currLeft, int currRight, int segLeft, int segRight, int value)
    {
        //handle leftover propagations
        propagateAndUpdate(currIndex, currRight - currLeft + 1);

        //if disjoint, nothing to update
        if(currLeft > segRight || currRight < segLeft) return;
        //if fully included, update 
        else if(currLeft >= segLeft && currRight <= segRight)
        {
            tree[currIndex].queue_update(value, 0, false);
            propagateAndUpdate(currIndex, currRight - currLeft + 1);
        }
        //if semi included update parts where it is included, and update the end result
        else
        {
            int s = currLeft + (currRight - currLeft) / 2;

            range_increase_update(currIndex * 2, currLeft, s, segLeft, segRight, value);
            range_increase_update(currIndex * 2 + 1, s + 1, currRight, segLeft, segRight, value);

            tree[currIndex].value = tree[currIndex * 2].value + tree[currIndex * 2 + 1].value;
        }   
    }

    int range_query(int currIndex, int currLeft, int currRight, int segLeft, int segRight)
    {
        //handle leftover propagations
        propagateAndUpdate(currIndex, currRight - currLeft + 1);

        //if disjoint, nothing to give
        if(currLeft > segRight || currRight < segLeft)
        {
            return 0;
        }
        //if fully complete, give everything
        else if(currLeft >= segLeft && currRight <= segRight)
        {
            return tree[currIndex].value;
        }
        //if partially give sum of left and right
        else
        {
            int s = currLeft + (currRight - currLeft) / 2;

            return  range_query(currIndex * 2,     currLeft, s        , segLeft, segRight) + 
                    range_query(currIndex * 2 + 1, s + 1   , currRight, segLeft, segRight);
        }

    }

    void completeTree(int currIndex, int range)
    {
        if(range)
        {
            propagateAndUpdate(currIndex, range);
            completeTree(currIndex * 2, range / 2);
            completeTree(currIndex * 2 + 1, range / 2);
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

    //inclusive, 0 indexed
    void range_increase_update(int l, int r, int value)
    {
        range_increase_update(1, 0, this->size / 2 - 1, l, r, value);
    }


    //inclusive, 0 indexed
    int range_query(int l, int r)
    {
        return range_query(1, 0, this->size / 2 - 1, l, r);
    }


    void completeTree()
    {
        completeTree(1, this->size / 2);
    }

};



int main()
{
    int n = 12;
    std::vector<int> arr = {5, -2, 13, 0, 7, 7, -9, 4, 18, -1, 6, 2};

    SegTree st = SegTree(arr);

    st.range_increase_update(0, 3, 100);

    std::cout << "query one: " << st.range_query(0, 0);
    std::cout << "\nquery two: " << st.range_query(0, 1);
    std::cout << "\nquery three: " << st.range_query(0, n - 1);
    std::cout << std::endl;
    st.printTree();

    /*
    st.completeTree();
    st.printTree();

    */
    return 0;
}