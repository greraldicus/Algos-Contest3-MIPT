//https://contest.yandex.ru/contest/32613/run-report/63370197/

#include <iostream>

struct AVLNode {
    int Key;
    int Height;
    int Count;
    AVLNode* Left;
    AVLNode* Right;

    explicit AVLNode(int key) : Key(key), Height(1), Count(1), Left(nullptr), Right(nullptr) {}
};

int Height(AVLNode* node) {
    return node ? node->Height : 0;
}


void FixHeight(AVLNode* node) {
    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
}

int Count(AVLNode* node)
{
    return node ? node->Count : 0;
}

void FixCount(AVLNode*& root) {
    root->Count = Count(root->Right) + Count(root->Left) + 1;
}

int Balance(AVLNode* node) {
    if (!node) return 0;
    return Height(node->Left) - Height(node->Right);
}

void RotateLeft2(AVLNode*& root) {
    AVLNode* right = root->Right;
    root->Right = root->Right->Left;
    right->Left = root;
    root = right;
    FixHeight(root->Left);
    FixHeight(root);
    FixCount(root->Left);
    FixCount(root);
}

void RotateRight2(AVLNode*& root) {
    AVLNode* left = root->Left;
    root->Left = root->Left->Right;
    left->Right = root;
    root = left;
    FixHeight(root->Right);
    FixHeight(root);
    FixCount(root->Right);
    FixCount(root);
}

void BigRotateLeft2(AVLNode*& root) {
    if (Balance(root->Right) > 0) {
        RotateRight2(root->Right);
        RotateLeft2(root);
    } else {
        RotateLeft2(root);
    }
}

void BigRotateRight2(AVLNode*& root) {
    if (Balance(root->Left) < 0) {
        RotateLeft2(root->Left);
        RotateRight2(root);
    } else {
        RotateRight2(root);
    }
}

void FixTree(AVLNode*& root) {
    if (Balance(root) == -2) {
        BigRotateLeft2(root);
    } else if (Balance(root) == 2) {
        BigRotateRight2(root);
    } else {
        FixHeight(root);
        FixCount(root);
    }
}

void Add(int key, AVLNode*& root) {
    if (!root) {
        root = new AVLNode(key);
        return;
    }
    if (root->Key < key)
        Add(key, root->Right);
    else
        Add(key, root->Left);
    FixTree(root);
}

AVLNode* MinLeft(AVLNode* root) {
    while (root->Left) {
        root = root->Left;
    }
    return root;
}

AVLNode* MinRight(AVLNode* root) {
    if (root->Left) {
        root->Left = MinRight(root->Left);
    } else {
        return root->Right;
    }
    FixTree(root);
    return root;
}

AVLNode* Remove(int k, AVLNode*& root) {
    if (root->Key < k) {
        root->Right = Remove(k, root->Right);
    } else if (k < root->Key) {
        root->Left = Remove(k, root->Left);
    } else {
        if (!root->Left || !root->Right) {
            AVLNode* child = root->Left ? root->Left : root->Right;
            delete root;
            return child;
        } else {
            AVLNode* min_node = MinLeft(root->Right);
            min_node->Right = MinRight(root->Right);
            min_node->Left = root->Left;
            delete root;
            root = min_node;
        }
    }
    FixTree(root);
    return root;
}

void FreeTree(AVLNode* root) {
    while (root) {
        if (root->Left == nullptr) {
            AVLNode* right = root->Right;
            delete root;
            root = right;
        } else if (root->Right == nullptr) {
            AVLNode* left = root->Left;
            delete root;
            root = left;
        } else {
            AVLNode* minParent = root;
            AVLNode* min = root->Right;
            while (min->Left) {
                minParent = min;
                min = min->Left;
            }
            min->Key = root->Key;
            (minParent->Left == min ? minParent->Left : minParent->Right) = min->Right;
            delete min;
        }
    }
}

int FindKStat(int kOrder, AVLNode* root) {
    int Stat = Count(root->Right);
    while (Stat != kOrder) {
        if (kOrder < Stat) {
            root = root->Right;
            Stat = Stat - 1 - Count(root->Left);
        } else {
            root = root->Left;
            Stat = Stat + 1 + Count(root->Right);
        }
    }
    return root->Key;
}


int main() {
    int n,key,k;
    std::cin >> n >> key >> k;
    AVLNode* root = new AVLNode(key);
    std::cout << root->Key;
    for (int i = 1; i < n; i++)
    {
        std::cin >> key >> k;
        if (key >= 0)
        {
            Add(key,root);
            std::cout << FindKStat(k,root) << std::endl;
        }
        else if (key < 0)
        {
            Remove(key,root);
            std::cout << FindKStat(k,root) << std::endl;
        }
    }
    FreeTree(root);
    return 0;
}
