//https://contest.yandex.ru/contest/32613/run-report/63338293/

#include <iostream>

struct Node {
    int Key;
    Node* Left;
    Node* Right;

    explicit Node(int key) : Key(key), Left(nullptr), Right(nullptr) {}
};

void Add(Node* root, int key)
{
    Node* curNode = root;
    while (true)
    {
        if (key < curNode->Key)
        {
            if (curNode->Left)
                curNode = curNode->Left;
            else
            {
                curNode->Left = new Node(key);
                break;
            }
        }
        else
        {
            if (curNode->Right)
                curNode = curNode->Right;
            else
            {
                curNode->Right = new Node(key);
                break;
            }
        }
    }
}

int MaxDepth(Node* node) {
    if (node == nullptr) return 0;
    return std::max(MaxDepth(node->Left), MaxDepth(node->Right)) + 1;
}

void DeleteTree(Node* root)
{
    while (root != nullptr)
    {
        if (root->Left == nullptr)
        {
            Node* right = root->Right;
            delete root;
            root = right;
        }
        else if (root->Right == nullptr)
        {
            Node* left = root->Left;
            delete root;
            root = left;
        }
        else
        {
            Node* minParent = root;
            Node* min = root->Right;
            while (min->Left != nullptr)
            {
                minParent = min;
                min = min->Left;
            }
            min->Key = root->Key;
            (minParent->Left == min ? minParent->Left : minParent->Right) = min->Right;
            delete min;
        }
    }
}

struct NodeDec {
    int Key;
    int Priority;
    NodeDec* Left;
    NodeDec* Right;

    explicit NodeDec(int key, int priority) : Key(key), Priority(priority), Left(nullptr), Right(nullptr) {}
};

void DeleteDecTree(NodeDec* root)
{
    while (root != nullptr)
    {
        if (root->Left == nullptr)
        {
            NodeDec* right = root->Right;
            delete root;
            root = right;
        }
        else if (root->Right == nullptr)
        {
            NodeDec* left = root->Left;
            delete root;
            root = left;
        }
        else
        {
            NodeDec* minParent = root;
            NodeDec* min = root->Right;
            while (min->Left != nullptr)
            {
                minParent = min;
                min = min->Left;
            }
            min->Key = root->Key;
            (minParent->Left == min ? minParent->Left : minParent->Right) = min->Right;
            delete min;
        }
    }
}

std::pair<NodeDec*, NodeDec*> Split(NodeDec* node, int key) {
    if (node == nullptr) return {nullptr, nullptr};
    if (node->Key < key) {
        NodeDec *help = node;
        auto [first, second] = Split(node->Right, key);
        help->Right = first;
        return {help, second};
    } else {
        NodeDec *help = node;
        auto [first, second] = Split(node->Left, key);
        help->Left = second;
        return {first, help};
    }
}

void AddDecTree(NodeDec* &dec, int key, int priority) {
    if (!dec) {
        dec = new NodeDec(key, priority);
        return;
    }
    if (dec->Priority < priority) {
        auto [first, second] = Split(dec, key);
        auto* new_node = new NodeDec(key, priority);
        new_node->Left = first;
        new_node->Right = second;
        dec = new_node;
        return;
    }
    if (dec->Key <= key) AddDecTree(dec->Right, key, priority);
    else if (dec->Key > key) AddDecTree(dec->Left, key, priority);
}

int MaxDepth(NodeDec* node) {
    if (node == nullptr) return 0;
    return std::max(MaxDepth(node->Left), MaxDepth(node->Right)) + 1;
}

int main() {
    int n;
    int x, y;
    std::cin >> n;
    std::cin >> x >> y;
    auto* tree = new Node(x);
    auto* dec_tree = new NodeDec(x, y);

    for (int i = 0; i < n - 1; i++) {
        std::cin >> x >> y;
        Add(tree, x);
        AddDecTree(dec_tree, x, y);
    }
    std::cout << abs(MaxDepth(tree) - MaxDepth(dec_tree)) << std::endl;
    DeleteTree(tree);
    DeleteDecTree(dec_tree);
    return 0;
}
