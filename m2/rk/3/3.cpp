#include <iostream>
#include <unordered_set>

using std::unordered_set;

struct Node {

    Node(std::string &_word, const int _color, const int _size) : product_name(_word), color(_color), size(_size) {};

    std::string product_name;
    int color;
    int size;

    bool operator==(const Node &node) const {
        if (product_name == node.product_name && color == node.color && size == node.size)
            return true;
        return false;
    };
};

struct Hash {
    unsigned int operator()(const Node &node) const {
        unsigned int hash = 0;
        for (char i: node.product_name)
            hash = hash * 137 + i;

        hash += node.color + node.size;
        return (hash);
    }
};


int main() {

    unordered_set<Node, Hash> table;

    char operation;
    std::string word;
    int color;
    int size;

    while (std::cin >> operation >> word >> color >> size) {
        if (operation == '+')
            std::cout << ((table.emplace(Node(word, color, size)).second) ? "OK" : "FAIL") << std::endl;
        if (operation == '?')
            std::cout << ((table.find(Node(word, color, size)) != table.end()) ? "OK" : "FAIL") << std::endl;
        if (operation == '-')
            std::cout << (table.erase(Node(word, color, size)) ? "OK" : "FAIL") << std::endl;
    }

    return 0;
}