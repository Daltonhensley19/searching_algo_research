#include "hash_table.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <ostream>

int HashTable::get_capacity() const
{
  return m_capacity;
}
int HashTable::get_current_size() const
{
  return m_currentSize;
}

void HashTable::print_chain() const
{
  for (int i = 0; i < m_capacity; i++)
  {
    std::cout << "[" << i << "] -> [";

    int iter_count = 1;
    for (auto begin = m_chain[i].begin(); begin != m_chain[i].end(); begin++)
    { // No comma needed if last number
      if (iter_count == m_chain[i].size()) [[unlikely]]
        std::cout << *begin;
      else [[likely]]
        std::cout << *begin << ", ";
      iter_count += 1;
    }

    std::cout << "]\n";
  }
}

void HashTable::naive_chain(int item)
{
  // Home position lamada
  auto hash_func = [=, this]() { return item % m_capacity; };

  // Calculate home position
  int pos = hash_func();

  // If linked list is not empty, alert of collision
  if (!m_chain[pos].empty())
  {
    std::cout << "WARN: Collision detected when tring to store item " << item
              << " at list " << pos << "\n";

    m_chain[pos].push_back(item);
    m_currentSize += 1;
  }
  // Else, store item
  else
  {

    std::cout << "Item: " << item << " is to be stored at list: " << pos
              << "\n";

    m_chain[pos].push_back(item);
    m_currentSize += 1;
  }
}

void HashTable::naive_hash(int item)
{
  // Home position lamada
  auto hash_func = [=, this]() { return item % m_capacity; };

  // Calculate home position
  int pos = hash_func();

  // If collision is detected, panic
  if (m_list[pos] != 0)
  {
    std::cout << "ERROR: Collision detected when tring to store item " << item
              << "at positon " << pos << "\n";

    std::cout << m_list[pos] << " and " << item
              << " have the same home location!\n";
  }
  // Else, store item
  else
  {

    std::cout << "Item: " << item << " is to be stored at index: " << pos
              << "\n";

    m_list[pos] = item;
    m_currentSize += 1;
  }
}

void HashTable::delete_item(int item)
{
  // Home position lamada
  auto hash_func = [=, this]() { return item % m_capacity; };

  // Calculate home position
  int pos            = hash_func();
  int numberOfChecks = 0;

  // If postion is taken, then handle collision
  if (m_list[pos] != item)
  {
    {
      std::cout << "\nWARN: Collision detected when tring to find item " << item
                << " at positon " << pos << "\n";

      std::cout << m_list[pos] << " and " << item
                << " have the same home location!\n\n";

      // Find a valid position (if we look everywhere without finding, halt)
      bool itemFound = false;
      while (!itemFound && numberOfChecks != m_capacity)
      {
        std::cout << "Attempting to delete item at location "
                  << (pos + 1) % m_capacity << "\n";
        // If next index is empty (bounded by HT capacity), store item here
        if ((m_list[(pos + 1) % m_capacity]) == item)
        {
          std::cout << "Deleting resolved item " << item << " at location "
                    << (pos + 1) % m_capacity << "\n\n";
          m_list[(pos + 1) % m_capacity] = 0;
          m_currentSize -= 1;

          itemFound = true;
        }
        // Else, advance to next position
        else
        {
          std::cout << "Location " << (pos + 1) % m_capacity << " is not item "
                    << item << "! \n\n";
          pos = (pos + 1);
          numberOfChecks += 1;
        }
      }
    }
  }
  // Best case, no collision to resolve
  else
  {
    std::cout << "Item: " << item << " is to be deleted at index: " << pos
              << "\n";

    m_list[pos] = 0;
    m_currentSize -= 1;
  }
}

void HashTable::linear_probe(int item)
{ // Alert user if table is full
  if (m_currentSize == m_capacity)
    std::cout << "ERROR: HT is full!\n";
  else
  {
    // Home position lamada
    auto hash_func = [=, this]() { return item % m_capacity; };

    // Calculate home position
    int pos = hash_func();

    // If postion is taken, then handle collision
    if (m_list[pos] != 0)
    {
      // Check for duplicate keys
      if (m_list[pos] == item)
        std::cout << "WARN: duplicate keys are not allowed!\n";
      else
      {
        std::cout << "\nWARN: Collision detected when tring to store item "
                  << item << " at positon " << pos << "\n";

        std::cout << m_list[pos] << " and " << item
                  << " have the same home location!\n\n";

        // Find a valid position
        bool validPos = false;
        while (!validPos)
        {
          std::cout << "Attempting store item at location "
                    << (pos + 1) % m_capacity << "\n";

          // If next index is empty (bounded by HT capacity), store item here
          if ((m_list[(pos + 1) % m_capacity]) == 0)
          {
            std::cout << "Storing resolved item " << item << " at location "
                      << (pos + 1) % m_capacity << "\n\n";

            m_list[(pos + 1) % m_capacity] = item;
            m_currentSize += 1;

            validPos = true;
          }
          // Else, advance to next position
          else
          {
            std::cout << "Location " << (pos + 1) % m_capacity
                      << " is not empty!\n\n";

            pos = (pos + 1);
          }
        }
      }
    }
    // Best case, no collision to resolve
    else
    {
      std::cout << "Item: " << item << " is to be stored at index: " << pos
                << "\n";

      m_list[pos] = item;
      m_currentSize += 1;
    }
  }
}

void HashTable::random_probe(int item)
{
  // Alert user if table is full
  if (m_currentSize == std::ceil(m_capacity / 2))
    std::cout << "ERROR: HT is full!\n";
  else
  {
    // Home position lamada
    auto hash_func = [=, this]() { return item % m_capacity; };

    // Calculate home position
    int pos = hash_func();

    // If postion is taken, then handle collision
    if (m_list[pos] != 0)
    {
      // Check for duplicate keys
      if (m_list[pos] == item)
        std::cout << "WARN: duplicate keys are not allowed!\n";
      else
      {

        std::cout << "\nWARN: Collision detected when tring to store item "
                  << item << " at positon " << pos << "\n";

        std::cout << m_list[pos] << " and " << item
                  << " have the same home location!\n\n";

        // Find a valid position
        bool validPos = false;
        while (!validPos)
        {
          std::cout << "Attempting store item at location "
                    << (int)(pos + std::rand()) % m_capacity << "\n";

          // If next index is empty (bounded by HT capacity), store item here
          if ((m_list[(int)(pos + std::rand()) % m_capacity]) == 0)
          {
            std::cout << "Storing resolved item " << item << " at location "
                      << (int)(pos + std::rand()) % m_capacity << "\n\n";

            m_list[(int)(pos + std::rand()) % m_capacity] = item;
            m_currentSize += 1;

            validPos = true;
          }
          // Else, advance to new random position by seeding
          else
          {
            std::cout << "Location " << (int)(pos + std::rand()) % m_capacity
                      << " is not empty!\n\n";

            std::srand(std::rand());
          }
        }
      }
    }
    // Best case, no collision to resolve
    else
    {
      std::cout << "Item: " << item << " is to be stored at index: " << pos
                << "\n";

      m_list[pos] = item;
      m_currentSize += 1;
    }
  }
}

void HashTable::quadratic_probe(int item)
{
  // Alert user if table is full
  if (m_currentSize == std::ceil(m_capacity / 2))
    std::cout << "ERROR: HT is full!\n";
  else
  {
    // Home position lamada
    auto hash_func = [=, this]() { return item % m_capacity; };

    // Calculate home position
    int pos = hash_func();

    // If postion is taken, then handle collision
    if (m_list[pos] != 0)
    {
      // Check for duplicate keys
      if (m_list[pos] == item)
        std::cout << "WARN: duplicate keys are not allowed!\n";
      else
      {

        std::cout << "\nWARN: Collision detected when tring to store item "
                  << item << " at positon " << pos << "\n";

        std::cout << m_list[pos] << " and " << item
                  << " have the same home location!\n\n";

        // Find a valid position
        bool validPos = false;
        int idx       = 1;
        while (!validPos)
        {
          std::cout << "Attempting store item at location "
                    << (int)(pos + std::pow(idx, 2)) % m_capacity << "\n";

          // If next index is empty (bounded by HT capacity), store item here
          if ((m_list[(int)(pos + std::pow(idx, 2)) % m_capacity]) == 0)
          {
            std::cout << "Storing resolved item " << item << " at location "
                      << (int)(pos + pow(idx, 2)) % m_capacity << "\n\n";

            m_list[(int)(pos + std::pow(idx, 2)) % m_capacity] = item;
            m_currentSize += 1;

            validPos = true;
          }
          // Else, advance to next position
          else
          {
            std::cout << "Location "
                      << (int)(pos + std::pow(idx, 2)) % m_capacity
                      << " is not empty!\n\n";

            idx += 1;
          }
        }
      }
    }
    // Best case, no collision to resolve
    else
    {
      std::cout << "Item: " << item << " is to be stored at index: " << pos
                << "\n";

      m_list[pos] = item;
      m_currentSize += 1;
    }
  }
}
HashTable::HashTable()
{
  // Defaults
  m_capacity    = 10;
  m_currentSize = 0;

  m_list       = new int[m_capacity];
  m_list_state = new int[m_capacity];
  m_chain      = new std::list<int>[m_capacity];
}

HashTable::HashTable(int capacity)
{
  if (capacity <= 0)
  {
    std::cout << "\nWARN: HT Capacity must be greater than 0.\n";
    std::cout << "Setting HT to default size of 10.\n\n\n";

    m_capacity = 10;
  }
  else
    m_capacity = capacity;

  m_currentSize = 0;
  m_list        = new int[m_capacity];
  m_list_state  = new int[m_capacity];
  m_chain       = new std::list<int>[m_capacity];
}

HashTable::~HashTable()
{
  delete[] m_list;
  delete[] m_list_state;
  delete[] m_chain;
}

std::ostream& operator<<(std::ostream& os, HashTable& hs)
{
  os << "[";
  for (int i = 0; i < hs.m_capacity; i++)
  {
    if (i == hs.m_capacity - 1)
      os << hs.m_list[i];
    else
      os << hs.m_list[i] << ", ";
  }
  os << "]\n";

  return os;
}

HashTable& HashTable::operator=(const HashTable& otherTable)
{

  if (this != &otherTable)
  {
    m_capacity    = otherTable.m_capacity;
    m_currentSize = otherTable.m_currentSize;

    delete[] m_list;
    delete[] m_list_state;

    m_list       = new int[m_capacity];
    m_list_state = new int[m_capacity];

    for (int i = 0; i < otherTable.get_capacity(); i++)
    {
      m_list[i]       = otherTable.m_list[i];
      m_list_state[i] = otherTable.m_list_state[i];
    }
  }

  return *this;
}

HashTable::HashTable(const HashTable& otherTable)
{
  // Copy members
  m_capacity    = otherTable.m_capacity;
  m_currentSize = otherTable.m_currentSize;

  // Allocate space
  m_list       = new int[m_capacity];
  m_list_state = new int[m_capacity];

  // Item-wise deep copy
  for (int i = 0; i < otherTable.get_capacity(); i++)
  {
    m_list[i]       = otherTable.m_list[i];
    m_list_state[i] = otherTable.m_list_state[i];
  }
}
