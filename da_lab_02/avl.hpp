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

    TAvlNode* RotateRight(TAvlNode* node);
    TAvlNode* RotateLeft(TAvlNode* node);
    TAvlNode* Balance(TAvlNode* node);
    void RecountHeight(TAvlNode* node);

    TAvlNode* InsertInNode(TAvlNode* node, const TString& key, const uint64_t& value);
    TAvlNode* RemoveMin(TAvlNode* node, TAvlNode* curr);
    TAvlNode* SubRemove(TAvlNode* node, const TString& key); //
    void SubDeleteTree(TAvlNode* node);
    void SubSave(std::ostream& os, const TAvlNode* node);
    TAvlNode* SubLoad(std::istream& is);
    void DfsPrint(const TAvlNode* node, const int& depth) const;

public:
    TAvlTree();
    ~TAvlTree();
    
    TAvlNode* Find(const TString& key) const;
    void Insert(const TString& key, const u_int64_t& value);
    void Remove(const TString& key);
    void DeleteTree();
    void Save(const TString& path);
    void Load(const TString& path);
    void Print() const;
};
