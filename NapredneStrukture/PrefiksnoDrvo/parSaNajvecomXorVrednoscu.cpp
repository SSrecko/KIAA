#include <iostream>
#include <bits/stdc++.h>
#include <climits>
#define MASK 0x8000000000000000
#define ull unsigned long long
#define SIZE 8 * sizeof(unsigned long long)
struct node
{
    node* children[2];
    node(){
        std::memset(node::children, 0, sizeof(node::children)); 
    }
};


void insertNumber(node* root, ull num, int i)
{
    if(i == SIZE) { return;}
    int curr = num & MASK ? 1 : 0;
    if(!root->children[curr])
    {
        root->children[curr] = new node();
    }
    insertNumber(root->children[curr], num << 1, i + 1);
}

void insertNumber(node* root, ull num)
{
    insertNumber(root, num, 0);
}

void printTrie(node* root, int num, int i)
{
    if(i == SIZE) std::cout << num << std::endl;
    if(root->children[0])
        printTrie(root->children[0], num << 1, i + 1);
    if(root->children[1])
        printTrie(root->children[1], (num << 1) + 1, i + 1);
}

ull max(ull a, ull b)
{
    return a > b ? a : b;
}

ull maxXor(node* root, ull num)
{
    node *curr = root;
    ull x = 0;

    for(int i = 0; i < SIZE; i++)
    {   
        short bit = num & MASK ? 1 : 0;
        if(curr->children[!bit])
        {
            x = (x << 1) + 1;
            curr = curr->children[!bit];
        }
        else
        {
            x <<= 1;
            curr = curr->children[bit];
        }
        num <<= 1;
    }

    return x;
}
int main()
{
    int n; std::cin >> n;
    node* trie = new node();
    ull res = 0;
    for(int i = 0; i < n; i++)
    {
        ull k; std::cin >> k;
        insertNumber(trie, k);
        res = max(maxXor(trie, k), res);
    }

    std::cout << res;
    return 0;
}