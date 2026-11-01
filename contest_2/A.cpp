#include <iostream>
#include <vector>

const int cGroupSize = 5;
const long long cMod = 10000000 + 4321;
const long long cPrevCoef = 123;
const long long cPrevPrevCoef = 45;

void InsertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i < right; ++i) {
    int key = arr[i];
    int j = i - 1;

    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

int QuickSelect(std::vector<int>& arr, int k) {
  int size_arr = static_cast<int>(arr.size());
  if (size_arr <= cGroupSize) {
    InsertionSort(arr, 0, size_arr);
    return arr[k];
  }
  std::vector<int> medians;
  int idx = 0;
  while (idx < size_arr) {
    int group_end = (idx + cGroupSize < size_arr) ? idx + cGroupSize : size_arr;
    InsertionSort(arr, idx, group_end);
    medians.push_back(arr[idx + (group_end - idx) / 2]);
    idx += cGroupSize;
  }

  int x = QuickSelect(medians, static_cast<int>(medians.size()) / 2);
  std::vector<int> less_than_x;
  std::vector<int> equal_to_x;
  std::vector<int> greater_than_x;
  for (int i = 0; i < size_arr; ++i) {
    if (arr[i] < x) {
      less_than_x.push_back(arr[i]);
    } else if (arr[i] == x) {
      equal_to_x.push_back(arr[i]);
    } else {
      greater_than_x.push_back(arr[i]);
    }
  }

  int less_size = static_cast<int>(less_than_x.size());
  int equal_size = static_cast<int>(equal_to_x.size());

  if (k < less_size) {
    return QuickSelect(less_than_x, k);
  }
  if (k < less_size + equal_size) {
    return x;
  }
  return QuickSelect(greater_than_x, k - less_size - equal_size);
}

int main() {
  int n;
  int k;
  long long a_0;
  long long a_1;
  std::cin >> n >> k >> a_0 >> a_1;

  std::vector<int> arr(n);
  arr[0] = static_cast<int>(a_0);
  if (n > 1) {
    arr[1] = static_cast<int>(a_1);
  }
  for (int i = 2; i < n; ++i) {
    arr[i] = static_cast<int>(
        (arr[i - 1] * cPrevCoef + arr[i - 2] * cPrevPrevCoef) % cMod);
  }
  std::cout << QuickSelect(arr, k - 1) << std::endl;
  return 0;
}