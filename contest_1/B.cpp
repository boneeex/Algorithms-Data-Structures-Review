#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<long double> PrefixLogSum(const std::vector<long double>& arr) {
  std::vector<long double> pref(arr.size() + 1, 0.0L);
  for (size_t i = 0; i < arr.size(); ++i) {
    pref[i + 1] = pref[i] + std::log(arr[i]);
  }
  return pref;
}

long double GeometricMean(int left, int right,
                          const std::vector<long double>& pref) {
  long double len = right - left + 1;
  return std::exp((pref[right + 1] - pref[left]) / len);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;
  std::vector<long double> arr(n);
  for (auto& x : arr) {
    std::cin >> x;
  }

  auto pref = PrefixLogSum(arr);

  const int cPrecision = 10;
  std::cout << std::fixed << std::setprecision(cPrecision);

  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int left;
    int right;
    std::cin >> left >> right;
    std::cout << GeometricMean(left, right, pref) << "\n";
  }
  return 0;
}