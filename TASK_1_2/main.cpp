//https://contest.yandex.ru/contest/32613/run-report/63337527/

#include <iostream>
#include <stack>

struct Node
{
    int Key;
    Node* Left;
    Node* Right;

    explicit Node(int key = 0) :
            Key(key), Left(nullptr), Right(nullptr) {}
};


void Add(Node* root, int value)
{
    Node* curNode = root;
    while (true)
    {
        if (value < curNode->Key)
        {
            if (curNode->Left)
                curNode = curNode->Left;
            else
            {
                curNode->Left = new Node(value);
                break;
            }
        }
        else
        {
            if (curNode->Right)
                curNode = curNode->Right;
            else
            {
                curNode->Right = new Node(value);
                break;
            }
        }
    }
}

void PreOrder(Node* root)
{
    if (root == nullptr)
        return;

    std::stack<Node*> nodes;
    nodes.push(root);

    while (!nodes.empty())
    {
        Node* curElem = nodes.top();
        std::cout << curElem->Key << " ";
        nodes.pop();

        if (curElem->Right)
            nodes.push(curElem->Right);
        if (curElem->Left)
            nodes.push(curElem->Left);
    }

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

int main()
{
    int n;
    std::cin >> n;

    Node* root = nullptr;

    for (int i = 0; i < n; i++)
    {
        int key;
        std::cin >> key;
        if (root == nullptr)
            root = new Node(key);
        else
            Add(root, key);
    }

    PreOrder(root);
    DeleteTree(root);
    return 0;
}
