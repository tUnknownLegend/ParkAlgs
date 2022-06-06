/*
 * 4_1. Солдаты.
 * В одной военной части решили построить в одну шеренгу по росту.
 * Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя,
 * а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
 * Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены по росту – сначала самые высокие,
 * а в конце – самые низкие. За расстановку солдат отвечал прапорщик,
 * который заметил интересную особенность – все солдаты в части разного роста. Ваша задача состоит в том,
 * чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого приходящего солдата указывать,
 * перед каким солдатом в строе он должен становится.
 *
 * Требования: скорость выполнения команды - O(log n).
 *
 * Формат входных данных.
 *
 * Первая строка содержит число N – количество команд (1 ≤ N ≤ 30 000).
 * В каждой следующей строке содержится описание команды: число 1 и X если солдат приходит в строй (X – рост солдата,
 * натуральное число до 100 000 включительно) и число 2 и Y если солдата, стоящим в строе на месте Y надо удалить из строя.
 * Солдаты в строе нумеруются с нуля.
 *
 * Формат выходных данных.
 *
 * На каждую команду 1 (добавление в строй) вы должны выводить число K – номер позиции,
 * на которую должен встать этот солдат (все стоящие за ним двигаются назад).
 */

#include <iostream>
#include <cassert>

template<class T, class Compare>
class AVLtree {
    struct Node {
        explicit Node(const T &data)
                : data(data), height(1), statOrd(1), left(nullptr), right(nullptr) {
        }

        Node() = default;

        T data;
        size_t height;
        size_t statOrd;
        Node *left;
        Node *right;
    };

public:
    explicit AVLtree(const Compare &_cmp)
            : root(nullptr), cmp(_cmp) {
    }

    ~AVLtree() {
        destroyTree(root);
    }

    int Add(const T &data) {
        int out = 0;
        root = addInternal(root, data, out);
        return out;
    }

    void Delete(int data) {
        root = deleteInternal(root, findStatOrd(data));
    }

private:
    Node *root;
    Compare cmp;

    T findStatOrd(int statOrd);

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *deleteInternal(Node *node, T data);

    Node *findMin(Node *node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node *removeMin(Node *node) {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node *addInternal(Node *node, const T &data, int &statOrd);

    size_t getHeight(Node *node) {
        return node ? node->height : 0;
    }

    void fixHeight(Node *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    Node *rotateLeft(Node *node);

    size_t GetOrd(Node *node) {
        return node ? node->statOrd : 0;
    }

    void fixStatOrd(Node *node) {
        if (!node)
            return;
        node->statOrd = GetOrd(node->left) + GetOrd(node->right) + 1;
    }

    Node *rotateRight(Node *node);

    int getBalance(Node *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node *doBalance(Node *node);

    std::pair<Node *, Node *> findDelMin(Node *node);
};

template<class T, class Compare>
typename AVLtree<T, Compare>::Node *AVLtree<T, Compare>::rotateLeft(Node *node) {
    Node *tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    fixStatOrd(node);
    fixHeight(node);
    fixStatOrd(tmp);
    fixHeight(tmp);
    return tmp;
}

template<class T, class Compare>
typename AVLtree<T, Compare>::Node *AVLtree<T, Compare>::rotateRight(Node *node) {
    Node *tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    fixStatOrd(node);
    fixHeight(node);
    fixStatOrd(tmp);
    fixHeight(tmp);
    return tmp;
}


template<class T, class Compare>
typename AVLtree<T, Compare>::Node *AVLtree<T, Compare>::addInternal(Node *node, const T &data, int &statOrd) {
    if (!node)
        return new Node(data);

    node->statOrd += 1;

    if (node->data <= data) {

        node->right = addInternal(node->right, data, statOrd);
    } else {
        statOrd += GetOrd(node->right) + 1;
        node->left = addInternal(node->left, data, statOrd);
    }
    return doBalance(node);
}

template<class T, class Compare>
T AVLtree<T, Compare>::findStatOrd(int statOrd) {
    if (root == nullptr) {
        T data = {};
        return data;
    }

    Node *node = root;

    int current = 0;
    int nodes_right = 0;

    while (true) {
        nodes_right = GetOrd(node->right);
        if (statOrd - current > nodes_right) {
            node = node->left;
            current += nodes_right + 1;
        } else if (statOrd - current < nodes_right) {
            if (node->right != nullptr) {
                node = node->right;
            } else {
                break;
            }
        } else {
            return node->data;
        }
    }
    return node->data;
}

template<class T, class Compare>
std::pair<typename AVLtree<T, Compare>::Node *, typename AVLtree<T, Compare>::Node *>
AVLtree<T, Compare>::findDelMin(Node *node) {
    if (node->left) {
        std::pair<Node *, Node *> min = findDelMin(node->left);
        node->left = min.first;
        return std::make_pair(doBalance(node), min.second);
    }

    return std::make_pair(node->right, node);
}

template<class T, class Compare>
typename AVLtree<T, Compare>::Node *AVLtree<T, Compare>::deleteInternal(Node *node, T data) {
    if (!node)
        return nullptr;

    if (node->data < data) {
        node->right = deleteInternal(node->right, data);
    } else if (node->data > data) {
        node->left = deleteInternal(node->left, data);
    } else {

        Node *left = node->left;
        Node *right = node->right;

        if (!left || !right) {

            delete node;

            if (!right)
                return left;
            else
                return right;

        } else {
            std::pair<Node *, Node *> pMin = findDelMin(right);
            Node *min = pMin.second;
            min->right = pMin.first;
            min->left = left;

            return doBalance(min);
        }
    }
    return doBalance(node);
}

template<class T, class Compare>
typename AVLtree<T, Compare>::Node *AVLtree<T, Compare>::doBalance(Node *node) {
    fixHeight(node);
    fixStatOrd(node);
    switch (getBalance(node)) {
        case 2: {
            if (getBalance(node->right) < 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        case -2: {
            if (getBalance(node->left) > 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        default:
            return node;
    }
}

struct IntCmp {
    bool operator()(int l, int r) { return l < r; }
};

int main() {
    IntCmp cmp;
    AVLtree<int, IntCmp> tree(cmp);

    int amtOfVals = 0;
    std::cin >> amtOfVals;
    int typeOfInput = 0;
    int inputVal = 0;
    for (int i = 0; i < amtOfVals; ++i) {
        std::cin >> typeOfInput;
        std::cin >> inputVal;
        switch (typeOfInput) {
            case 1: {
                std::cout << tree.Add(inputVal) << " ";
                break;
            }
            case 2: {
                tree.Delete(inputVal);
                break;
            }
            default:
                assert(false);
        }
    }
    return 0;
}