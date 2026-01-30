#include <vector>

struct segTree
{
    private: 
    
    std::vector<long long> tree;

    int size;


    public:

    segTree(std::vector<int> arr);

    long long segSum(int l, int r);

    void increase(int i, int value);

    void enter(int i, int value);
};