#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

template<class T, class Compare>
class BinaryTree {
public:
    explicit BinaryTree(const Compare &_cmp) : root(nullptr), cmp(_cmp) {}

    ~BinaryTree();

    void Add(const T &key);

    bool Has(const T &key) const;

    void TraverseDfs(void (*visit)(const T &key));

private:
    struct Node {
        Node *Left;
        Node *Right;
        T Key;

        Node() = delete;

        explicit Node(const T &key) : Left(nullptr), Right(nullptr), Key(key) {}
    };

    Node *root;
    Compare cmp;

    void deleteNode(Node *node);

    void traverse(Node *node, void (*visit)(const T &key));

    void addNode(Node **node, const T &key);
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree() {
    deleteNode(root);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::deleteNode(Node *node) {
    if (node == nullptr) {
        return;
    }

    std::queue<Node *> nodeList;
    nodeList.push(node);

    while (!nodeList.empty()) {
        node = nodeList.front();
        nodeList.pop();

        if (node->Left != nullptr)
            nodeList.push(node->Left);

        if (node->Right != nullptr)
            nodeList.push(node->Right);

        delete node;
    }
}

template<class T, class Compare>
void BinaryTree<T, Compare>::Add(const T &key) {
    addNode(&root, key);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::addNode(Node **node, const T &key) {
    while (*node != nullptr) {
        if (cmp(key, (*node)->Key))
            node = &(*node)->Left;
        else
            node = &(*node)->Right;
    }

    *node = new Node(key);
}

template<class T, class Compare>
bool BinaryTree<T, Compare>::Has(const T &key) const {
    Node *node = root;
    while (node != nullptr && node->Key != key) {
        if (cmp(key, node->Key)) {
            node = node->Left;
        } else {
            node = node->Right;
        }
    }

    return node->Key == key;
}

template<class T, class Compare>
void BinaryTree<T, Compare>::TraverseDfs(void (*visit)(const T &key)) {
    traverse(root, visit);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::traverse(Node *node, void (*visit)(const T &key)) {
    if (node == nullptr) {
        return;
    }

    std::vector<Node *> nodeVec;
    nodeVec.push_back(node);
    node = node->Left;

    while (!nodeVec.empty()) {
        while (node->Left != nullptr) {
            nodeVec.push_back(node);
            node = node->Left;
        }

        visit(node->Key);
        //visit(nodeVec.back()->Key);

        while (nodeVec.back()->Right == nullptr && !nodeVec.empty()) {
            visit(nodeVec.back()->Key);
            nodeVec.pop_back();
        }

        if (nodeVec.back()->Right != nullptr) {
            visit(nodeVec.back()->Key);
            node = nodeVec.back()->Right;
            nodeVec.pop_back();

            while (node->Left == nullptr && node->Right != nullptr) {
                visit(node->Key);
                node = node->Right;
            }

            if (node->Left != nullptr) {
                nodeVec.push_back(node);
                node = node->Left;
            } else
                visit(node->Key);
        }
    }

    /*
    std::queue<Node *> nodeList;
    nodeList.push(node);
    std::queue<Node *> subNodeList;

    while (node->Left != nullptr)

    while (nodeList.front()->Right != nullptr && nodeList.front()->Left != nullptr) {
        node = nodeList.front();
        //nodeList.pop();

        if (node->Right != nullptr)
            nodeList.push(node->Right);

        if (node->Left != nullptr)
            nodeList.push(node->Left);

    }
    */
    /*
    if (node == nullptr) {
        return;
    }
    traverse(node->Left, visit);
    visit(node->Key);
    traverse(node->Right, visit);
     */
}

struct IntCmp {
    bool operator()(int l, int r) { return l < r; }
};

int main() {
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);

    int amtOfVals = 0;
    std::cin >> amtOfVals;
    int inputVal = 0;
    for (int i = 0; i < amtOfVals; ++i) {
        std::cin >> inputVal;
        tree.Add(inputVal);
    }
    tree.TraverseDfs([](const int &key) { std::cout << key << " "; });
    return 0;
}