#include "DisjointSet.hpp"

int main()
{
    DisjointSet ds(15);

    ds.disjointUnion(2, 7);
    ds.disjointUnion(4, 7);

    ds.disjointUnion(1, 3);
    ds.disjointUnion(5, 3);
    ds.disjointUnion(3, 2);

    ds.disjointUnion(12, 13);
    ds.disjointUnion(14, 11);
    ds.disjointUnion(11, 11);

    ds.printSet();


    return 0;
}