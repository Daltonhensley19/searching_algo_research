#include "hash_table.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

int main()
{
  HashTable ht(5);
    
  for (int i = 0; i < 10; i++)
      ht.naive_chain(rand());

  ht.print_chain();





  return 0;
}

