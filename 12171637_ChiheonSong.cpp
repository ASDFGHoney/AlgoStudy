#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Color {
    RED, BLACK
};

class RBTree {
    class RBTNode {
    public:
        RBTNode *parent;
        RBTNode *left;
        RBTNode *right;

        int id;
        string name;
        int vol;
        int price;
        enum Color color;

        RBTNode(RBTNode *pa, RBTNode *le, RBTNode *ri, int _id, string _name, int _vol, int _price, enum Color col) {
            parent = pa;
            left = le;
            right = ri;
            id = _id;
            name = _name;
            vol = _vol;
            price = _price;
            color = col;
        }

        RBTNode(RBTNode &copy) {
            parent = copy.parent;
            left = copy.left;
            right = copy.right;
            id = copy.id;
            name = copy.name;
            vol = copy.vol;
            price = copy.price;
            color = copy.color;
        }
    };

    RBTNode *LEAF;
    bool isEmpty;
    int depth;
    RBTNode *root;
    bool flag;

public:
    RBTree() {
        isEmpty = true;
        depth = 0;
        root = nullptr;
        flag = false;
        LEAF = new RBTNode(nullptr, nullptr, nullptr, -1, "", 0, 0, BLACK);
    }

    RBTNode *findNode(int &_iD);

    void restructuring(RBTNode *son, RBTNode *par, RBTNode *granpa);

    static bool isRight(RBTNode *node);

    int Enroll(int &A, string &N, int &S, int &P);

    void Search(int i);

    void Update(int idd, string nam, int vo, int pri);

    void Discount(int x, int y, int per);

    void recoloring(RBTNode *par);

    void insertionNode(RBTNode *papa, RBTNode *insertNode);

    void discountSel(RBTNode *pNode, int x, int y, int per);
};

RBTree::RBTNode *RBTree::findNode(int &_iD) {
    RBTNode *curNode = root;
    depth = 0;
    while (true) {
        if (curNode->id > _iD) {
            if (curNode->left == LEAF) {
                return curNode;
            } else {
                curNode = curNode->left;
                depth++;
                continue;
            }
        } else if (curNode->id < _iD) {
            if (curNode->right == LEAF) {
                return curNode;
            } else {
                curNode = curNode->right;
                depth++;
                continue;
            }
        } else {
            flag = true;
            return curNode;
        }
    }
}

bool RBTree::isRight(RBTree::RBTNode *node) {
    return node->id > node->parent->id;
}

int RBTree::Enroll(int &A, string &N, int &S, int &P) {
    if (isEmpty) {
        root = new RBTNode(nullptr, LEAF, LEAF, A, N, S, P, BLACK);
        isEmpty = false;
        return 0;
    }
    RBTNode *papa = findNode(A); // 들어갈 자리의 부모 노드와, 부모의 depth 가 정해짐.
    if (flag) {
        flag = false;
        return depth;
    }

    RBTNode *newNode = new RBTNode{papa, LEAF, LEAF, A, N, S, P, RED};
    depth++;
    if (papa->id > newNode->id) {
        papa->left = newNode;
    } else {
        papa->right = newNode;
    }

    insertionNode(papa, newNode);
    return depth;
}

void RBTree::insertionNode(RBTree::RBTNode *papa, RBTree::RBTNode *insertNode) {
    if (papa == root || papa == nullptr || insertNode == nullptr || insertNode == root) {
        return;
    }
    if (papa->color == RED) { // double RED!!!
        if (papa->parent->left->color == RED && papa->parent->right->color == RED) {  // 삼촌이 red
            recoloring(papa);
            if (papa->parent == root) {
                root->color = BLACK;
                return;
            }
            insertionNode(papa->parent->parent, papa->parent);
        } else
            restructuring(insertNode, papa, papa->parent);
    }
}

void RBTree::recoloring(RBTree::RBTNode *par) {
    par->parent->color = RED;
    par->parent->right->color = BLACK;
    par->parent->left->color = BLACK;
}

void RBTree::restructuring(RBTree::RBTNode *son, RBTree::RBTNode *par, RBTree::RBTNode *granpa) {
    RBTNode *conectPointTail;
    bool isConectPointRight;
    if (granpa != root) {
        conectPointTail = granpa->parent;
        isConectPointRight = isRight(granpa);
    } else
        conectPointTail = nullptr;

    RBTNode *conectPointHead;

    if (isRight(par)) {
        if (isRight(son)) {
            depth -= 1;
            granpa->right = par->left;
            par->left = granpa;
            granpa->parent = par;
            conectPointHead = par;
        } else {
            depth -= 2;
            granpa->right = son->left;
            par->left = son->right;
            son->left = granpa;
            son->right = par;
            par->parent = son;
            granpa->parent = son;
            conectPointHead = son;
        }
    } else {
        if (isRight(son)) {
            depth -= 2;
            granpa->left = son->right;
            par->right = son->left;
            son->left = par;
            son->right = granpa;
            par->parent = son;
            granpa->parent = son;
            conectPointHead = son;
        } else {
            depth -= 1;
            granpa->left = par->right;
            par->right = granpa;
            granpa->parent = par;
            conectPointHead = par;
        }
    }
    conectPointHead->color = BLACK;
    conectPointHead->right->color = RED;
    conectPointHead->left->color = RED;
    if (conectPointTail == nullptr) {
        root = conectPointHead;
        conectPointHead->parent = nullptr;
    } else {
        if (isConectPointRight) {
            conectPointHead->parent = conectPointTail;
            conectPointTail->right = conectPointHead;
        } else {
            conectPointHead->parent = conectPointTail;
            conectPointTail->left = conectPointHead;
        }
    }
}

void RBTree::Search(int i) {
    RBTNode *defNode = findNode(i);
    if (flag)
        cout << depth << " " << defNode->name << " " << defNode->vol << " " << defNode->price << "\n";
    else
        cout << "NULL\n";
    flag = false;
}

void RBTree::Update(int idd, string nam, int vo, int pri) {
    RBTNode *defNode = findNode(idd);
    if (flag) {
        cout << depth << "\n";
        defNode->name = nam;
        defNode->vol = vo;
        defNode->price = pri;
    } else
        cout << "NULL\n";
    flag = false;
}

void RBTree::Discount(int x, int y, int per) {
    discountSel(root, x, y, per);
}

void RBTree::discountSel(RBTree::RBTNode *pNode, int x, int y, int per) {
    if (pNode == LEAF)
        return;
    if (pNode->id >= x && pNode->id <= y)
        pNode->price = (pNode->price * (100 - per)) / 100;
    discountSel(pNode->left, x, y, per);
    discountSel(pNode->right, x, y, per);
}

int main() {
    int casee;
    cin >> casee;
    int A, S, P, x, y;
    string N;

    RBTree treee;

    while (casee--) {
        char question;
        cin >> question;

        switch (question) {
            case 'I':   // 등록
                cin >> A >> N >> S >> P;
                cout << treee.Enroll(A, N, S, P) << "\n";
                break;
            case 'F':   // 검색
                cin >> A;
                treee.Search(A);
                break;
            case 'R':   // 업데이트
                cin >> A >> N >> S >> P;
                treee.Update(A, N, S, P);
                break;
            case 'D':   // 할인
                cin >> x >> y >> P;
                treee.Discount(x, y, P);
                break;
            default:
                break;
        }
    }
    return 0;
}