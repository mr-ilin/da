#pragma once

#include "string.hpp"

struct TAvlNode {
    TString key;
    uint64_t value;
    int height;
    
    TAvlNode* left;
    TAvlNode* right;

    TAvlNode();
    TAvlNode(const TString& k, const uint64_t& val);
    TAvlNode(TString&& k, uint64_t&& val) noexcept;
    ~TAvlNode();
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

    TAvlNode* InsertInNode(TAvlNode* node, const TString& key, const uint64_t& value, const bool& printResult);
    TAvlNode* RemoveMin(TAvlNode* node, TAvlNode* curr);
    TAvlNode* SubRemove(TAvlNode* node, const TString& key, const bool& printResult);
    void SubDeleteTree(TAvlNode* node);
    void SubSave(std::ostream& os, const TAvlNode* node);
    TAvlNode* SubLoad(std::istream& is);
    void DfsPrint(const TAvlNode* node, const int& depth) const;

public:
    TAvlTree();
    ~TAvlTree();
    
    TAvlNode* Find(const TString& key) const;
    void Insert(const TString& key, const u_int64_t& value, const bool& printResult);
    void Remove(const TString& key, const bool& printResult);
    void DeleteTree();
    void Save(const TString& path, const bool& printResult);
    void Load(const TString& path, const bool& printResult);
    void Print() const;
};
