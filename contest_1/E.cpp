#include <iostream>
#include <vector>

int BinSearch(int x, int n, const std::vector<int>& arr_a,
              const std::vector<int>& arr_b) {
  int l = -1;
  int r = n;
  while (r - l > 1) {
    int m = (r + l) / 2;
    if ((long long)arr_a[m] - arr_b[m] + x > 0) {
      r = m;
    } else {
      l = m;
    }
  }

  if (r == 0) {
    return 0;
  }
  if (r == n) {
    return n - 1;
  }
  if (arr_b[r - 1] < (long long)arr_a[r] + x) {
    return r - 1;
  }
  return r;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> arr_a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr_a[i];
  }
  std::vector<int> arr_b(n);
  for (int i = 0; i < n; i++) {
    std::cin >> arr_b[i];
  }

  int q;
  std::cin >> q;
  for (int i = 0; i < q; i++) {
    int x;
    std::cin >> x;
    int best_idx = BinSearch(x, n, arr_a, arr_b);
    std::cout << best_idx + 1 << "\n";
  }
  return 0;
}