#ifndef FPTREE_HPP
#define FPTREE_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <utility>


using Transaction = std::vector<int>;
using TransformedPrefixPath = std::pair<std::vector<int>, int>;
using Pattern = std::pair<std::set<int>, int>;


struct FPNode {
    const int item;
    int frequency;
    std::shared_ptr<FPNode> node_link;
    std::weak_ptr<FPNode> parent;
    std::vector<std::shared_ptr<FPNode>> children;

    FPNode(const int&, const std::shared_ptr<FPNode>&);
};

struct FPTree {
    std::shared_ptr<FPNode> root;
    std::map<int, std::shared_ptr<FPNode>> header_table;
    int minimum_support_threshold;

    FPTree(const std::vector<Transaction>&, int);

    bool empty() const;
};


std::set<Pattern> fptree_growth(const FPTree&);


#endif  // FPTREE_HPP
