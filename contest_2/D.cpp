#include <cstdint>
#include <iostream>
#include <vector>

const int cBitsInByte = 8;
const int cBytesInNumber = 8;
const int cBucketsCount = 256;
const std::uint64_t cByteMask = 0xFF;

int TakeByte(std::uint64_t num, int byte_idx) {
  return static_cast<int>((num >> (byte_idx * cBitsInByte)) & cByteMask);
}

void CountingSortByByte(const std::vector<std::uint64_t>& source,
                        std::vector<std::uint64_t>& destination, int byte_idx) {
  std::vector<int> bucket_start(cBucketsCount, 0);
  for (std::uint64_t num : source) {
    ++bucket_start[TakeByte(num, byte_idx)];
  }

  int prefix_sum = 0;
  for (int bucket = 0; bucket < cBucketsCount; ++bucket) {
    int count = bucket_start[bucket];
    bucket_start[bucket] = prefix_sum;
    prefix_sum += count;
  }

  for (std::uint64_t num : source) {
    int bucket = TakeByte(num, byte_idx);
    destination[bucket_start[bucket]] = num;
    ++bucket_start[bucket];
  }
}

void LSDSort(std::vector<std::uint64_t>& arr) {
  std::vector<std::uint64_t> buffer(arr.size());
  for (int byte_idx = 0; byte_idx < cBytesInNumber; ++byte_idx) {
    CountingSortByByte(arr, buffer, byte_idx);
    arr.swap(buffer);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int size = 0;
  std::cin >> size;
  std::vector<std::uint64_t> arr(size);
  for (std::uint64_t& num : arr) {
    std::cin >> num;
  }

  LSDSort(arr);

  for (std::uint64_t num : arr) {
    std::cout << num << ' ';
  }
  std::cout << '\n';
  return 0;
}