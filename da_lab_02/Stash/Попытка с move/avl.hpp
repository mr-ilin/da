#pragma once

#include "string.hpp"

struct TAvlNode {
    TString key;
    uint64_t value;
    int height;
    
    TAvlNode* left;
    TAvlNode* right;

    TAvlNode();
    TAvlNode(const TString& k, const u_int64_t& val);
    TAvlNode(TString&& k, u_int64_t&& val) noexcept;
};

class TAvlTree {
private:
    TAvlNode* root;

    int GetHeight(const TAvlNode* node) const;
    int GetBalance(const TAvlNode* node) const;
    int CountTreeHeight(TAvlNode* node) const;

    TAvlNode* RotateRight(TAvlNode* node);
    TAvlNode* RotateLeft(TAvlNode* node);
    TAvlNode* Balance(TAvlNode* node);
    void RecountHeight(TAvlNode* node);

    TAvlNode* InsertInNode(TAvlNode* node, TString key, uint64_t value); //
    TAvlNode* RemoveMin(TAvlNode* node, TAvlNode* curr);
    TAvlNode* SubRemove(TAvlNode* node, TString key); // 
    void SubDeleteTree(TAvlNode* node);
    void SubSave(std::ostream& os, const TAvlNode* node);
    TAvlNode* SubLoad(std::istream& is);
    void DfsPrint(const TAvlNode* node, int depth) const;

public:
    TAvlTree();
    ~TAvlTree();
    
    TAvlNode* Find(TString key) const;
    void Insert(TString key, uint64_t value);
    void Remove(TString key);
    void DeleteTree();
    void Save(TString& path);
    void Load(TString& path);
    void Print() const;
};
