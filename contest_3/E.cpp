#include <deque>
#include <iostream>

class MiddleDeque {
 public:
  std::deque<int> left;
  std::deque<int> right;

  void AddToBack(int x) { left.push_back(x); }

  int PopFront() {
    std::deque<int>& arr = (right.empty()) ? left : right;
    int front = arr.front();
    arr.pop_front();
    return front;
  }

  void AddToMid(int x) {
    ReAsign();
    left.push_front(x);
  }

 private:
  void ReAsign() {
    while (left.size() > right.size()) {
      int top_left = left.front();
      left.pop_front();
      right.push_back(top_left);
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n = 0;
  std::cin >> n;
  MiddleDeque deque;
  for (int i = 0; i < n; ++i) {
    char operation = 0;
    int element = 0;
    std::cin >> operation;
    switch (operation) {
      case '+':
        std::cin >> element;
        deque.AddToBack(element);
        break;
      case '*':
        std::cin >> element;
        deque.AddToMid(element);
        break;
      case '-': {
        auto result = deque.PopFront();
        std::cout << result << "\n";
        break;
      }
      default:
        break;
    }
  }

  return 0;
}