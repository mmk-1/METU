#include "HashTable.h"

int main()
{
    KeyedHashTable ht;
    std::vector<int> A(4,2);
    ht.Insert("A", A);
    // ht.Insert("B", std::vector<int>());
    // ht.Insert("C", std::vector<int>());
    // ht.Insert("D", std::vector<int>());
    // ht.Insert("E", std::vector<int>());
    // ht.Insert("F", std::vector<int>());
    // ht.Insert("G", std::vector<int>());
    // ht.Insert("H", std::vector<int>());
    // ht.Insert("I", std::vector<int>());
    // ht.Insert("J", std::vector<int>());
    // ht.Insert("K", std::vector<int>());
    // ht.Insert("L", std::vector<int>());
    // ht.Insert("M", std::vector<int>());
    // ht.Insert("N", std::vector<int>());
    // ht.Insert("O", std::vector<int>());
    // ht.Insert("P", std::vector<int>());
    

    // ht.Print();
    // ht.PrintAll();
    ht.Print();
    ht.Remove("A");
    ht.Print();
    // KeyedHashTable ht2(ht);
    // ht2.Print();
    
}