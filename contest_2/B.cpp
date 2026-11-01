#include <iostream>
#include <vector>

const int cGroupSize = 5;
const int cSmallSize = 32;
const long long cMod = 10000000 + 4321;
const long long cPrevCoef = 123;
const long long cPrevPrevCoef = 45;

void Swap(int& first, int& second) {
  int tmp = first;
  first = second;
  second = tmp;
}

void CompareSwap(int& first, int& second) {
  int low = (first < second) ? first : second;
  int high = (first < second) ? second : first;
  first = low;
  second = high;
}

void SortFive(std::vector<int>& arr, int pos) {
  CompareSwap(arr[pos], arr[pos + 1]);
  CompareSwap(arr[pos + 3], arr[pos + 4]);
  CompareSwap(arr[pos + 2], arr[pos + 4]);
  CompareSwap(arr[pos + 2], arr[pos + 3]);
  CompareSwap(arr[pos], arr[pos + 3]);
  CompareSwap(arr[pos], arr[pos + 2]);
  CompareSwap(arr[pos + 1], arr[pos + 4]);
  CompareSwap(arr[pos + 1], arr[pos + 3]);
  CompareSwap(arr[pos + 1], arr[pos + 2]);
}

void InsertionSort(std::vector<int>& arr, int left, int right) {
  for (int i = left + 1; i < right; ++i) {
    int key = arr[i];
    int j = i - 1;
    while (j >= left && arr[j] > key) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = key;
  }
}

int QuickSelect(std::vector<int>& arr, int left, int right, int k) {
  while (right - left > cSmallSize) {
    int cnt = 0;
    for (int group = left; group < right; group += cGroupSize) {
      int group_end = (group + cGroupSize < right) ? group + cGroupSize : right;
      if (group_end - group == cGroupSize) {
        SortFive(arr, group);
      } else {
        InsertionSort(arr, group, group_end);
      }
      Swap(arr[left + cnt], arr[group + ((group_end - group) / 2)]);
      ++cnt;
    }

    int pivot = QuickSelect(arr, left, left + cnt, cnt / 2);

    int less = left;
    int cur = left;
    int greater = right;
    while (cur < greater) {
      if (arr[cur] < pivot) {
        Swap(arr[less], arr[cur]);
        ++less;
        ++cur;
      } else if (arr[cur] > pivot) {
        --greater;
        Swap(arr[cur], arr[greater]);
      } else {
        ++cur;
      }
    }

    int less_size = less - left;
    int equal_size = greater - less;
    if (k < less_size) {
      right = less;
      continue;
    }
    if (k < less_size + equal_size) {
      return pivot;
    }
    k -= less_size + equal_size;
    left = greater;
  }
  InsertionSort(arr, left, right);
  return arr[left + k];
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
        ((arr[i - 1] * cPrevCoef) + (arr[i - 2] * cPrevPrevCoef)) % cMod);
  }
  std::cout << QuickSelect(arr, 0, n, k - 1) << '\n';
  return 0;
}