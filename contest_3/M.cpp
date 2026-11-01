#include <iostream>
#include <vector>

const int cMaxRank = 20;

class BinomialHeap {
 public:
  struct Node {
    int value = 0;
    int idx = 0;
    int heap_idx = 0;
    Node* parent = nullptr;
    std::vector<Node*> children;
  };

  explicit BinomialHeap(int id) : heap_id_(id) {}

  void Insert(Node* node) {
    node->parent = nullptr;
    node->heap_idx = heap_id_;
    int r = 0;
    while (roots_[r] != nullptr) {
      node = Link(roots_[r], node);
      roots_[r] = nullptr;
      r++;
    }
    roots_[r] = node;
    if (min_of_ranks_ == nullptr || Less(node, min_of_ranks_)) {
      min_of_ranks_ = node;
    }
  }

  void Merge(BinomialHeap& other) {
    if (&other == this) {
      return;
    }
    MergeRoots(other.roots_);
    other.roots_.assign(cMaxRank, nullptr);
    other.min_of_ranks_ = nullptr;
  }

  Node* GetMin() const { return min_of_ranks_; }

  void RemoveRoot(Node* root) {
    roots_[root->children.size()] = nullptr;
    std::vector<Node*> children;
    children.swap(root->children);
    MergeRoots(children);
  }

  static Node* SiftToRoot(Node* node, std::vector<Node*>& node_of) {
    while (node->parent != nullptr) {
      Node* parent = node->parent;
      int value = node->value;
      int idx = node->idx;
      node->value = parent->value;
      node->idx = parent->idx;
      parent->value = value;
      parent->idx = idx;
      node_of[node->idx] = node;
      node_of[parent->idx] = parent;
      node = parent;
    }
    return node;
  }

 private:
  int heap_id_;
  Node* min_of_ranks_ = nullptr;
  std::vector<Node*> roots_ = std::vector<Node*>(cMaxRank, nullptr);

  static bool Less(const Node* lhs, const Node* rhs) {
    return (lhs->value < rhs->value) ||
           ((lhs->value == rhs->value) && (lhs->idx < rhs->idx));
  }

  static Node* Link(Node* tree_1, Node* tree_2) {
    Node* top = Less(tree_1, tree_2) ? tree_1 : tree_2;
    Node* bottom = (tree_1 == top) ? tree_2 : tree_1;
    bottom->parent = top;
    top->children.push_back(bottom);
    return top;
  }

  void MergeRoots(const std::vector<Node*>& other) {
    Node* carry = nullptr;
    for (int r = 0; r < cMaxRank; r++) {
      if (r >= static_cast<int>(other.size()) && carry == nullptr) {
        break;
      }
      Node* theirs = (r < static_cast<int>(other.size())) ? other[r] : nullptr;
      Node* result = nullptr;
      Node* next_carry = nullptr;
      for (Node* tree : {roots_[r], theirs, carry}) {
        if (tree == nullptr) {
          continue;
        }
        if (result == nullptr) {
          result = tree;
        } else {
          next_carry = Link(result, tree);
          result = nullptr;
        }
      }
      roots_[r] = result;
      carry = next_carry;
    }
    UpdateMin();
  }

  void UpdateMin() {
    min_of_ranks_ = nullptr;
    for (Node* root : roots_) {
      if (root == nullptr) {
        continue;
      }
      root->parent = nullptr;
      root->heap_idx = heap_id_;
      if (min_of_ranks_ == nullptr || Less(root, min_of_ranks_)) {
        min_of_ranks_ = root;
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  int q = 0;
  std::cin >> n >> q;
  std::vector<BinomialHeap> heaps;
  heaps.reserve(n + 1);
  for (int i = 0; i <= n; i++) {
    heaps.emplace_back(i);
  }
  std::vector<BinomialHeap::Node> pool;
  pool.reserve(q);
  std::vector<BinomialHeap::Node*> node_of(q + 1, nullptr);
  int inserted = 0;

  for (int i = 0; i < q; i++) {
    int type = 0;
    std::cin >> type;
    if (type == 0) {
      int a = 0;
      int x = 0;
      std::cin >> a >> x;
      inserted++;
      pool.push_back({x, inserted, a, nullptr, {}});
      node_of[inserted] = &pool.back();
      heaps[a].Insert(&pool.back());
    } else if (type == 1) {
      int a = 0;
      int b = 0;
      std::cin >> a >> b;
      heaps[b].Merge(heaps[a]);
    } else if (type == 2) {
      int idx = 0;
      std::cin >> idx;
      BinomialHeap::Node* root =
          BinomialHeap::SiftToRoot(node_of[idx], node_of);
      heaps[root->heap_idx].RemoveRoot(root);
      node_of[idx] = nullptr;
    } else if (type == 3) {
      int idx = 0;
      int x = 0;
      std::cin >> idx >> x;
      BinomialHeap::Node* root =
          BinomialHeap::SiftToRoot(node_of[idx], node_of);
      int heap = root->heap_idx;
      heaps[heap].RemoveRoot(root);
      root->value = x;
      heaps[heap].Insert(root);
    } else if (type == 4) {
      int a = 0;
      std::cin >> a;
      std::cout << heaps[a].GetMin()->value << "\n";
    } else if (type == 5) {
      int a = 0;
      std::cin >> a;
      BinomialHeap::Node* root = heaps[a].GetMin();
      node_of[root->idx] = nullptr;
      heaps[a].RemoveRoot(root);
    }
  }
  return 0;
}