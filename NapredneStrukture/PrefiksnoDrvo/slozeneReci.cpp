#include <iostream>
#include <string>
#include <unordered_map>
struct node
{
    std::unordered_map<char, node*> children;
    bool fullWord = false;
};

void insertWord(node* root, std::string& word, int i)
{
    if(i == word.size()) 
    {
        root->fullWord = true;
        return;
    }
    if(!root->children[word[i]])
    {
        root->children[word[i]] = new node();
    }
    insertWord(root->children[word[i]], word, i + 1);
}

void insertWord(node* root, std::string& word)
{
    insertWord(root, word, 0);
}

bool composite(node* root, node* ban, std::string& word, int i)
{
    node* curr = root;
    bool found = false;
    while(i < word.size() && curr->children[word[i]])
    {
        curr = curr->children[word[i]];
        if(curr->fullWord && curr != ban)
        {
            found = composite(root, ban, word, i + 1);
        }
        if(found) return true;
        i++;
    }
    if(i == word.size() && curr != ban) return true;
    return false;
    
}

void printTree(node* root, node* curr, std::string prefix)
{
    if(curr->fullWord && composite(root, curr, prefix,  0))
        std::cout << prefix << '\n';
    for(auto it : curr->children)
    {
        prefix.push_back(it.first);
        printTree(root, it.second, prefix);
        prefix.pop_back();
    }
}


int main()
{
    int n; std::cin >> n;

    node* trie = new node();
    for(int i = 0; i < n; i++)
    {
        std::string a;
        std::cin >> a;
        insertWord(trie, a);
    }

    std::string tmp = "";
    printTree(trie, trie, tmp);

    return 0;
}