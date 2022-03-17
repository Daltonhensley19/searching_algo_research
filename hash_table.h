#include <iostream>
#include <list>

class HashTable
{

public:
  HashTable();
  HashTable(int capacity);

  HashTable(const HashTable& otherTable);
  HashTable& operator=(const HashTable& otherTable);
  ~HashTable();

  void naive_hash(int item);
  void naive_chain(int item);
  void linear_probe(int item);
  void quadratic_probe(int item);
  void random_probe(int item);

  friend std::ostream& operator<<(std::ostream& os, HashTable& ht);
  void print_chain() const;  


  int get_capacity() const;
  int get_current_size() const;

  void delete_item(int item);

private:
  int* m_list;
  int* m_list_state;  
  std::list<int>* m_chain; 

  int m_capacity;
  int m_currentSize;
};

