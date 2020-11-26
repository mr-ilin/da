#include <iostream>
#include <fstream>

#include "avl.hpp"

TAvlNode::TAvlNode() 
    : key(), 
    value(),
    height(1),
    left(nullptr),
    right(nullptr)
{}

TAvlNode::TAvlNode(TString k, uint64_t val, int h)
    : key(std::move(k)),
    value(val),
    height(h),
    left(nullptr),
    right(nullptr)
{}

TAvlNode::~TAvlNode() {
    value = 0;
    height = 0;
    left = nullptr;
    right = nullptr;
}

TAvlTree::TAvlTree()
    : root()
{}

TAvlTree::~TAvlTree() {
    DeleteTree();
}

// Высота вершины node
int TAvlTree::GetHeight(const TAvlNode* node) const {
    if (node)  {
        return node->height;
    }
    return 0;
}

// Возвращает баланс узла
int TAvlTree::GetBalance(const TAvlNode* node) const {
    return GetHeight(node->left) - GetHeight(node->right);
}

// Пересчитывает высоту в узле
void TAvlTree::RecountHeight(TAvlNode* node) {
    if (GetHeight(node->left) > GetHeight(node->right)) {
        node->height = GetHeight(node->left) + 1;
    } else {
        node->height = GetHeight(node->right) + 1;
    }
}

// Правый поворот относительно узла node
TAvlNode* TAvlTree::RotateRight(TAvlNode* node) {
    TAvlNode* leftSon = node->left;
    node->left = leftSon->right;
    leftSon->right = node;
    
    RecountHeight(node);
    RecountHeight(leftSon);
    return leftSon;
}

// Левый поворот относительно узла node
TAvlNode* TAvlTree::RotateLeft(TAvlNode* node) {
    TAvlNode* rightSon = node->right;
    node->right = rightSon->left;
    rightSon->left = node;

    RecountHeight(node);
    RecountHeight(rightSon);
    return rightSon;
}

// Выполняет банасировку узла 
TAvlNode* TAvlTree::Balance(TAvlNode* node) {
    if (!node) {
        return nullptr;
    }

    RecountHeight(node);
    int balance = GetBalance(node);

    if (balance == 2) {
        if (GetBalance(node->left) == -1) {
            node->left = RotateLeft(node->left);
        }
        return RotateRight(node);
    } 
    if (balance == -2) {
        if (GetBalance(node->right) == 1) {
            node->right = RotateRight(node->right);
        }
        return RotateLeft(node);
    }
    return node;
}

// Поиск узла по ключу
TAvlNode* TAvlTree::Find(const TString& key) const {
    TAvlNode* node = this->root;

    while(node) {
        if (key < node->key) {
            node = node->left;
        } else if (key > node->key) {
            node = node->right;
        } else {
            return node;
        }
    }
    return nullptr; // Не найден
}

// Рекурсивная вставка узла в дерево
// Возвращает корень дерева
TAvlNode* TAvlTree::InsertInNode(TAvlNode* node, TString key, uint64_t value, const bool& printResult) {
    if (!node) {
        if (printResult) {
            std::cout << "OK\n";
        }
        return new TAvlNode(std::move(key), std::move(value));
    }

    if (key < node->key) {
        node->left = InsertInNode(node->left, std::move(key), std::move(value), printResult);
    } else if (key > node->key) {
        node->right = InsertInNode(node->right, std::move(key), std::move(value), printResult);
    } else {
        if (printResult) {
            std::cout << "Exist\n";
        }
    }

    return Balance(node);
}

// Обертка над вставкой
void TAvlTree::Insert(TString key, u_int64_t value, const bool& printResult) {
    root = InsertInNode(root, std::move(key), std::move(value), printResult);
}

// Удаляет мин. вершину из правого поддерева curr дерева node
// И меняет вершину root на мин. вершину
// Возвращает правое поддерево node'а
TAvlNode* TAvlTree::RemoveMin(TAvlNode* node, TAvlNode* curr) {
    if (curr->left) {
        curr->left = RemoveMin(node, curr->left);
    } else {
        TAvlNode* r = curr->right;
        node->key.Swap(curr->key); // Потом все равно удалится
        node->value = std::move(curr->value);
        //node->key = curr->key;
        //node->value = curr->value;

        delete curr;
        curr = r;
    }
    return Balance(curr);
}

// Удаляет вершину с ключом key из дерева node
// Возвращает измененное дерево
TAvlNode* TAvlTree::SubRemove(TAvlNode* node, const TString& key, const bool& printResult) {
    if (!node) {
        if (printResult) {
            std::cout << "NoSuchWord\n";
        }
        return nullptr;
    }

    if (key < node->key) {
        node->left = SubRemove(node->left, key, printResult);
    } else if (key > node->key) {
        node->right = SubRemove(node->right, key, printResult);
    } else { 
        // Нашли вершину для удаления
        TAvlNode* rSon = node->right;
        TAvlNode* lSon = node->left;

        if (!rSon) {
            if (printResult) {
                std::cout << "OK\n";
            }
            delete node;
            return lSon;
        } 
        if (!lSon) {
            if (printResult) {
                std::cout << "OK\n";
            }
            delete node;
            return rSon;
        } 
        // Есть оба сына
        node->right = RemoveMin(node, rSon);
        if (printResult) {
            std::cout << "OK\n";
        }
    }
    return Balance(node);
}

// Обертка над Remove
void TAvlTree::Remove(const TString& key, const bool& printResult) {
    root = SubRemove(root, key, printResult);
}

// Рекурсивное удаление дерева
void TAvlTree::SubDeleteTree(TAvlNode* node) {
    if (node) {
        SubDeleteTree(node->left);
        SubDeleteTree(node->right);
        delete node;
    }
}

// Обертка над SubDeleteTree
void TAvlTree::DeleteTree() {
    SubDeleteTree(this->root);
}

// Рекурсивная функция сохранения
void TAvlTree::SubSave(std::ostream& os, const TAvlNode* node) {
    // key.size key value height left right
    if (!node) {
        return;
    }

    size_t keySize = node->key.Size();
    os.write((char*)(&keySize), sizeof(keySize));
    os.write(node->key.Buffer(), keySize);
    os.write((char*)(&node->value), sizeof(node->value));
    os.write((char*)(&node->height), sizeof(node->height));
    
    bool LSon = (node->left != nullptr);
    bool RSon = (node->right != nullptr);
    os.write((char*)(&LSon), sizeof(LSon));
    os.write((char*)(&RSon), sizeof(RSon));
    
    if (LSon) {
        SubSave(os, node->left);
    } 
    if (RSon) {
        SubSave(os, node->right);
    }
}
// Функция рекурсивной загрузки из файла
// Возвращает корень дерева
TAvlNode* TAvlTree::SubLoad(std::istream& is) {
    size_t keySize = 0;

    is.read((char*)(&keySize), sizeof(keySize));
    if(is.gcount() == 0) {
        return nullptr;
    }

    char* str = new char[keySize + 1]{'\0'};
    is.read(str, keySize);
    TString key(str, keySize, keySize + 1);

    uint64_t value = 0;
    is.read((char*)(&value), sizeof(value));
    
    int height = 1;
    is.read((char*)(&height), sizeof(height));

    bool LSon = false;
    bool RSon = false;

    is.read((char*)(&LSon), sizeof(LSon));
    is.read((char*)(&RSon), sizeof(RSon));

    TAvlNode* node = new TAvlNode(std::move(key), std::move(value), std::move(height));

    if (LSon) {
        node->left = SubLoad(is);
    }
    if (RSon) {
        node->right = SubLoad(is);
    }

    return node;
}

void TAvlTree::Save(const TString& path, const bool& printResult) {
    std::ofstream os(path.Buffer(), std::ios::binary | std::ios::out);
    if (!os) {
        throw std::runtime_error("Can't open file");
    }

    SubSave(os, root);
    os.close();
    if (printResult) {
        std::cout << "OK\n";
    }
}

void TAvlTree::Load(const TString& path, const bool& printResult) {
    std::ifstream is(path.Buffer(), std::ios::binary | std::ios::in);
    if (!is) {
        throw std::runtime_error("Can't open file");
    }
    DeleteTree();
    root = SubLoad(is);
    is.close();
    if (printResult) {
        std::cout << "OK\n";
    }
}

void TAvlTree::DfsPrint(const TAvlNode* node, const int& depth) const {
    if (!node) {
        return;
    }

    DfsPrint(node->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        std::cout << "---";
    }
    std::cout << "[\"" << node->key << "\", " << node->value << ", " << GetBalance(node) <<" b]\n";
    // << node->height <<"h]\n";
    //std::cout << "[ " << GetBalance(node) <<" b]\n";

    DfsPrint(node->left, depth + 1);
}

void TAvlTree::Print() const {
    DfsPrint(root, 0);
}
