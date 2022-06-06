/*
 * Задача 2. Порядок обхода *
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
то узел K добавляется в правое поддерево root; иначе в левое поддерево root.

 * Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

 * 2_1. Выведите элементы в порядке in-order (слева направо).
 */

// best time complexity - o(log(n))
// worst time complexity - o(n)
// space complexity 0 o(n)

#include <iostream>
#include <queue>
#include <deque>

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

    std::deque<Node *> nodeVec;
    nodeVec.push_back(node);

    while (!nodeVec.empty()) {
        while (node->Left != nullptr) {
            node = node->Left;
            nodeVec.push_back(node);
        }

        while (!nodeVec.empty() && nodeVec.back()->Right == nullptr) {
            visit(nodeVec.back()->Key);
            nodeVec.pop_back();
        }

        if (!nodeVec.empty()) {
            node = nodeVec.back();
            visit(nodeVec.back()->Key);
            nodeVec.pop_back();
        }

        if (node->Right != nullptr) {
            node = node->Right;

            while (node->Left == nullptr && node->Right != nullptr) {
                visit(node->Key);
                node = node->Right;
            }

            if (node->Left != nullptr)
                nodeVec.push_back(node);
            else
                visit(node->Key);
        }
    }
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