#include <vector>
#define TYPE int

struct FenwickTree
{
    private:

    int size;
    std::vector<TYPE> tree;

    public:

    FenwickTree(std::vector<TYPE> originalArr);

    FenwickTree(int size);

    void updateElement(int index, int value);

    TYPE elementAt(int index);

    TYPE segmentSum(int l, int r);

};