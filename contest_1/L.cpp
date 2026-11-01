#include <iostream>
#include <string>
#include <vector>

bool CheckSubStr(const std::string& s, const std::string& t,
                 const std::vector<int>& when, int k) {
  int s_size = static_cast<int>(s.size());
  int t_size = static_cast<int>(t.size());
  int j = 0;
  for (int i = 0; i < s_size && j < t_size; ++i) {
    if (when[i] > k && s[i] == t[j]) {
      ++j;
    }
  }
  return j == t_size;
}

int AnsBinSearch(const std::string& s, const std::string& t,
                 const std::vector<int>& when) {
  int s_size = static_cast<int>(s.size());
  int l = -1;
  int r = s_size;
  while (r - l > 1) {
    int m = (l + r) / 2;
    auto check = CheckSubStr(s, t, when, m);
    if (check) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

int main() {
  std::string s;
  std::cin >> s;
  std::string t;
  std::cin >> t;

  int n = static_cast<int>(s.size());
  std::vector<int> idxs(n);
  for (int i = 0; i < n; i++) {
    std::cin >> idxs[i];
  }

  std::vector<int> when(n);
  for (int i = 0; i < n; i++) {
    when[idxs[i] - 1] = i + 1;
  }

  auto result = AnsBinSearch(s, t, when);
  std::cout << result;
  return 0;
}