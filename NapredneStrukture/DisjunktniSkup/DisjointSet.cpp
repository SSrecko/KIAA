#include "DisjointSet.hpp"
#include <iostream>
#include <map>

DisjointSet::DisjointSet()
{
    
}

DisjointSet::DisjointSet(int setCount)
{
    DisjointSet::parents.resize(setCount);
    DisjointSet::degrees.resize(setCount);
    for(int i = 0; i < setCount; i++)
    {
        DisjointSet::parents[i] = i;
        DisjointSet::degrees[i] = 0;
    }
    DisjointSet::size = setCount;
}

int DisjointSet::pushSets(int setCount)
{
    //return the number of the first set pushed
    for(int i = 0; i < setCount; i++)
    {
        DisjointSet::parents.push_back(size + i);
        DisjointSet::degrees.push_back(0);
    }

    DisjointSet::size = DisjointSet::size + setCount;
    return DisjointSet::size - setCount;
}

int DisjointSet::find(int element)
{
    int rep = element;
    while(rep != DisjointSet::parents[rep])
    {
        rep = DisjointSet::parents[rep];
    }

    while(element != rep)
    {
        int tmp = DisjointSet::parents[rep];
        DisjointSet::parents[element] = rep;
        element = tmp;
    }

    return rep;
}

void DisjointSet::disjointUnion(int setA, int setB)
{
    int repA = DisjointSet::find(setA); 
    int repB = DisjointSet::find(setB);

    if(repA == repB) return;

    int degA = DisjointSet::degrees[repA];
    int degB = DisjointSet::degrees[repB];
    
    if(degA >= degB)
    {
        DisjointSet::parents[repB] = repA;
        
        if(degA == degB) degA++;
    }
    else
    {
        DisjointSet::parents[repA] = repB;
    }
}

void DisjointSet::printSet()
{
    std::map<int, std::vector<int>> printMap;

    for(int i = 0; i < DisjointSet::size; i++)
    {
        printMap[DisjointSet::find(i)].push_back(i);
    }

    for(std::map<int, std::vector<int>>::iterator it = printMap.begin(); it != printMap.end(); it++)
    {
        std::cout << "Set represented by " << it->first << " " << std::endl;

        for(int i = 0; i < it->second.size(); i++)
        {
            std::cout << it->second[i] << " ";
        }

        std::cout << std::endl << std::endl;
    }
}
