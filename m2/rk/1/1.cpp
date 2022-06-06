#include <iostream>
#include <queue>

template<class T, class Compare>
class BinaryTree {
public:
    explicit BinaryTree(const Compare &_cmp) : root(nullptr), cmp(_cmp) {}

    ~BinaryTree();

    void Add(const T &key);

    bool Has(const T &key) const;

    void TraverseDfs(void (*visit)(bool same));

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

    void traverse(Node *node, void (*visit)(bool same));

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
void BinaryTree<T, Compare>::TraverseDfs(void (*visit)(bool same)) {
    traverse(root, visit);
}

template<class T, class Compare>
void BinaryTree<T, Compare>::traverse(Node *node, void (*visit)(bool same)) {
    if (node == nullptr) {
        visit(false);
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

        if (node->Key != root->Key) {
            visit(false);
            return;
        }
    }

    visit(true);
}

struct IntCmp {
    bool operator()(int l, int r) { return l < r; }
};

int main() {
    IntCmp cmp;
    BinaryTree<int, IntCmp> tree(cmp);

    int inputVal = 0;

    while (std::cin >> inputVal) {
        tree.Add(inputVal);
    }

    tree.TraverseDfs([](bool same) { std::cout << same; });
    return 0;
}