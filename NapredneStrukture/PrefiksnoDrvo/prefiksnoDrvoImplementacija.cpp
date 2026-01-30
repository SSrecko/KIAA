#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
struct node
{
    std::unordered_map<char, node*> children;
    bool fullWord = false;
};

void insertWord(node* root, std::string& word)
{
    int n = word.size();

    for(int i = 0; i < n; i++)
    {
        std::unordered_map<char, node*>::iterator it = root->children.find(word[i]);
        if(it == root->children.end())
        {
            root->children[word[i]] = new node();
        }
        root = root->children[word[i]];
    }
    root->fullWord = true;
}

void deleteSubtree(node* root)
{
    if(!root->children.empty())
    {
        deleteSubtree((root->children.begin())->second);
    }
    delete root;
}
void deleteWord(node* root, std::string& word)
{
    int n = word.size();
    if(n == 0) return;
    std::unordered_map<char, node*>::iterator it = root->children.find(word[0]);
    node* lastSplit = nullptr;
    char lastLetter = word[0];
    if(it != root->children.end())
    {
        lastSplit = root;
    }
    else return;

    for(int i = 0; i < n; i++)
    {
        std::unordered_map<char, node*>::iterator it = root->children.find(word[i]);
        
        if(it != root->children.end() && root->children.size() >= 2)
        {
            lastSplit = root;
            lastLetter = word[i];
        }
        else if(it == root->children.end())
            return;
    }
    deleteSubtree(root->children[lastLetter]);
}
bool findWord(node* root, std::string& word)
{
    int n = word.size();
    for(int i = 0; i < n; i++)
    {
        std::unordered_map<char, node*>::iterator it = root->children.find(word[i]);
        if(it == root->children.end())
            return false;
        root->children[word[i]];
    }
    return true;
}
void printTree(node* root, std::string prefix)
{
    if(root->children.size() >= 2)
    {
        std::cout << std::endl << prefix << ": " << std::endl;
    }
    if(root->fullWord)
        std::cout << prefix << " ";
    for(auto it : root->children)
    {
        prefix.push_back(it.first);
        printTree(it.second, prefix);
        prefix.pop_back();
    }
}


int main()
{
    std::vector<std::string> words = {
            "a", "an", "ant", "ante", "anthem", "anti", "antique",
            "app", "apple", "apples", "applet", "application", "applied", "apply", "apt", "apter",
            "arc", "arch", "archive", "archer", "architect",
            "ban", "band", "bandit", "bandage", "banana", "banter", "bank", "banker",
            "bar", "bare", "bark", "barn", "barrel",
            "bat", "batch", "bath", "baton",
            "be", "bee", "beef", "been", "beep",
            "car", "card", "cargo", "carpet", "carb", "carbon", "cart", "carter", "carton",
            "cat", "catch", "cater", "caterer", "category",
            "clap", "clasp", "class", "classic", "classified",
            "coal", "coast", "coat", "coating",
            "code", "coder", "coding", "codex",
            "con", "cone", "conflict", "confirm", "conform", "connect", "connection",
            "day", "deal", "dear", "deer", "deep", "deepen",
            "do", "dog", "dogs", "done", "doing",
            "ear", "earn", "earned", "earning",
            "fast", "faster", "fastest",
            "flow", "flower", "flown",
            "go", "goal", "goat", "gone",
            "he", "her", "hero", "heron",
            "in", "inn", "inner", "input",
            "map", "maps", "mapped", "mapping",
            "no", "nor", "north", "not", "note", "noted",
            "pre", "preface", "prefix", "preform", "preheat", "prelude",
            "pro", "probe", "problem", "process", "processor", "produce", "product",
            "re", "read", "reader", "reading", "real", "really",
            "test", "tester", "testing",
            "apple", "band", "cart", "prefix", "testing"
    };

    int n = words.size();

    node* root = new node();

    for(int i = 0; i < n; i++)
    {
        insertWord(root, words[i]);
    }

    std::string prefix = "";
    printTree(root, prefix);
    
    return 0;    
}