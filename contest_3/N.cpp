#include <iostream>
#include <vector>

class Allocator {
 public:
  explicit Allocator(long long n) {
    segments_.push_back({1, n, true, -1, -1, -1});
    Push(0);
  }

  long long Allocate(long long k) {
    if (heap_.empty() || segments_[heap_[0]].length < k) {
      request_segment_.push_back(-1);
      return -1;
    }
    int seg = heap_[0];
    if (segments_[seg].length == k) {
      segments_[seg].free = false;
      Erase(seg);
      request_segment_.push_back(seg);
      return segments_[seg].start;
    }
    int taken = static_cast<int>(segments_.size());
    segments_.push_back(
        {segments_[seg].start, k, false, segments_[seg].prev, seg, -1});
    if (segments_[seg].prev != -1) {
      segments_[segments_[seg].prev].next = taken;
    }
    segments_[seg].prev = taken;
    segments_[seg].start += k;
    segments_[seg].length -= k;
    SiftDown(segments_[seg].heap_pos);
    request_segment_.push_back(taken);
    return segments_[taken].start;
  }

  void Deallocate(int request) {
    request_segment_.push_back(-1);
    int seg = request_segment_[request];
    if (seg == -1) {
      return;
    }
    segments_[seg].free = true;
    int left = segments_[seg].prev;
    if (left != -1 && segments_[left].free) {
      Erase(left);
      segments_[seg].start = segments_[left].start;
      segments_[seg].length += segments_[left].length;
      segments_[seg].prev = segments_[left].prev;
      if (segments_[left].prev != -1) {
        segments_[segments_[left].prev].next = seg;
      }
    }
    int right = segments_[seg].next;
    if (right != -1 && segments_[right].free) {
      Erase(right);
      segments_[seg].length += segments_[right].length;
      segments_[seg].next = segments_[right].next;
      if (segments_[right].next != -1) {
        segments_[segments_[right].next].prev = seg;
      }
    }
    Push(seg);
  }

 private:
  struct Segment {
    long long start;
    long long length;
    bool free;
    int prev;
    int next;
    int heap_pos;
  };

  std::vector<Segment> segments_;
  std::vector<int> heap_;
  std::vector<int> request_segment_ = std::vector<int>(1, -1);

  bool Better(int lhs, int rhs) const {
    const Segment& a = segments_[heap_[lhs]];
    const Segment& b = segments_[heap_[rhs]];
    return a.length > b.length || (a.length == b.length && a.start < b.start);
  }

  void Swap(int lhs, int rhs) {
    int tmp = heap_[lhs];
    heap_[lhs] = heap_[rhs];
    heap_[rhs] = tmp;
    segments_[heap_[lhs]].heap_pos = lhs;
    segments_[heap_[rhs]].heap_pos = rhs;
  }

  void SiftUp(int pos) {
    while (pos > 0) {
      int parent = (pos - 1) / 2;
      if (!Better(pos, parent)) {
        return;
      }
      Swap(pos, parent);
      pos = parent;
    }
  }

  void SiftDown(int pos) {
    int size = static_cast<int>(heap_.size());
    while (true) {
      int best = pos;
      int left = 2 * pos + 1;
      int right = 2 * pos + 2;
      if (left < size && Better(left, best)) {
        best = left;
      }
      if (right < size && Better(right, best)) {
        best = right;
      }
      if (best == pos) {
        return;
      }
      Swap(pos, best);
      pos = best;
    }
  }

  void Push(int seg) {
    heap_.push_back(seg);
    segments_[seg].heap_pos = static_cast<int>(heap_.size()) - 1;
    SiftUp(segments_[seg].heap_pos);
  }

  void Erase(int seg) {
    int pos = segments_[seg].heap_pos;
    int last = static_cast<int>(heap_.size()) - 1;
    Swap(pos, last);
    heap_.pop_back();
    segments_[seg].heap_pos = -1;
    if (pos < last) {
      SiftUp(pos);
      SiftDown(pos);
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  long long n = 0;
  int q = 0;
  std::cin >> n >> q;
  Allocator allocator(n);
  for (int i = 0; i < q; i++) {
    long long k = 0;
    std::cin >> k;
    if (k > 0) {
      std::cout << allocator.Allocate(k) << "\n";
    } else {
      allocator.Deallocate(static_cast<int>(-k));
    }
  }
  return 0;
}