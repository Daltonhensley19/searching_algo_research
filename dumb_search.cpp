#include <array>
#include <iostream>
#include <span>

int seq_search(int needle, std::span<int> container);

int bin_search(int needle, std::span<int> container);

int main()
{
  std::array<int, 5> array = {1, 2, 3, 4, 5};

  auto pos = bin_search(1, array);

  std::cout << pos << "\n";

  return 0;
}

// Worst: n = O(n)
// Average: (n + 1) / 2 = O(n)
int seq_search(int needle, std::span<int> container)
{
  int needle_pos = -1;

  for (int i = 0; i < container.size(); i++)
  {
    if (container[i] == needle)
    {
      needle_pos = i;
      break;
    }
  }

  return needle_pos;
}

// Worst: 2Log_2(n + 1) = O(Log_2(n))
// Average: 2Log_2(n) - 3 = O(Log_2(n))
int bin_search(int needle, std::span<int> container)
{
  int needle_pos = -1;

  int first_idx = 0;
  int last_idx  = container.size();

  int mid_idx = (first_idx + last_idx) / 2;

  bool found = false;
  while (first_idx <= last_idx && !found)
  {
    if (needle > container[mid_idx])
      first_idx = mid_idx + 1;
    else if (needle < container[mid_idx])
      last_idx = mid_idx - 1;
    else
    {
      needle_pos = mid_idx;
      found      = true;
    }

    mid_idx = (first_idx + last_idx) / 2;
  }

  return needle_pos;
}
