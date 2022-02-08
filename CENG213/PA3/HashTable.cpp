#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    // TODO
    int hash = 0;
    for(int i = 0;i<key.size();i++){
        hash += key[i] * PRIME_LIST[i];
    }
    // if(tableSize != 0)
        hash %= tableSize;
    return hash;
}

void KeyedHashTable::ReHash()
{
    // TODO
    // using namespace std; 
    // cout << tableSize << " size before rehash" << endl;
    int oldSize = tableSize;
    int prime = FindNearestLargerPrime(tableSize * 2);
    tableSize = prime;
    // cout << tableSize << " after rehash" << endl;
    HashData *oldTable = table;
    table = new HashData[prime];
    // for(int i = 0; i < tableSize; i++){
    //     cout << table[i].key << "H ";
    // }
    // cout << endl;
    // int oldOccupiedElementCount = occupiedElementCount;
    occupiedElementCount = 0;
    for(int i = 0;i < oldSize;i++){
        if(oldTable[i].key != "" && oldTable[i].key != REMOVED)
        Insert(oldTable[i].key, oldTable[i].intArray);
    }
    delete[] oldTable;
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    // TODO
    int res;
    for(int i = 0;i<PRIME_TABLE_COUNT;i++){
        if(PRIME_LIST[i]>requestedCapacity){
            res = PRIME_LIST[i];
            break;
        }
    }
    return res;
}

KeyedHashTable::KeyedHashTable()
{
    // TODO
    this->tableSize = 2;
    this->table = new HashData[tableSize];
    this->occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    // TODO
    int prime = FindNearestLargerPrime(requestedCapacity);
    this->tableSize = prime;
    this->table = new HashData[prime];
    this->occupiedElementCount = 0;
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    // TODO
    this->tableSize = other.tableSize;
    this->occupiedElementCount = other.occupiedElementCount;
    this->table = new HashData[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        if (other.table[i].key != "")
        {
            this->table[i].key = other.table[i].key;
            this->table[i].intArray = other.table[i].intArray;
        }
    }
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    // TODO
    if(*this != other){
        //if not empty then empty it.
        if(this->tableSize > 0 || this->occupiedElementCount > 0){
            delete [] this->table;
        }
        this->tableSize = other.tableSize;
        this->occupiedElementCount = other.occupiedElementCount;
        this->table = new HashData[tableSize];
        for(int i = 0; i < tableSize ; i++) {
            if(other.table[i].key != ""){
                this->table[i].key = other.table[i].key;
                this->table[i].intArray = other.table[i].intArray;
            }
        }
        return *this;
    }
}

KeyedHashTable::~KeyedHashTable()
{
    // TODO
    tableSize = 0;
    occupiedElementCount = 0;
    delete [] table;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    // TODO
    // using namespace std;
    if (Contains(key))
    {
        return false;
    }
    int h = Hash(key);
    // cout << h << endl;
    int i = 0;
    for (; table[(h + pow(i, 2)) % tableSize].key != ""; i++)
        ;
    // if (key == "U")
        // cout << "i= " << i << endl;
    table[(h + pow(i, 2)) % tableSize].key = key;
    table[(h + pow(i, 2)) % tableSize].intArray = intArray;
    occupiedElementCount++;
    // cout << occupiedElementCount << " cnt after insert" << endl;
    if ((occupiedElementCount * EXPAND_THRESHOLD) >= tableSize)
    {
        ReHash();
    }
    return true;
}

bool KeyedHashTable::Remove(const std::string& key)
{
    // TODO
    if (!Contains(key))
        return false;
    int h = Hash(key);
    for (int i = 0; table[(h + pow(i, 2)) % tableSize].key != ""; i++)
    {
        if (table[(h + pow(i, 2)) % tableSize].key == key)
        {
            table[(h + pow(i, 2)) % tableSize].key = REMOVED;
            table[(h + pow(i, 2)) % tableSize].intArray.clear();
            return true;
        }
    }
    return false;
}

void KeyedHashTable::ClearTable()
{
   // TODO
   for(int i = 0; i < tableSize;i++){
        table[i].key = "";
        table[i].intArray.clear();
    }
    occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    // TODO
    if (!Contains(key))
        return false;
    int h = Hash(key);
    for (int i = 0; table[(h + pow(i, 2)) % tableSize].key != ""; i++)
    {
        if (table[(h + pow(i, 2)) % tableSize].key == key)
        {
            valueOut = table[(h + pow(i, 2)) % tableSize].intArray;
            return true;
        }
    }
    return false;
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}


// Custom functions

int KeyedHashTable::pow(int base, int exp) const
{
            int res = 1;
            while (exp)
            {
                if (exp & 1)
                    res*= base;
                exp >>= 1;
                base *= base;
            }

            return res;
}

bool KeyedHashTable::Contains(const std::string &key) const
{
            int h = Hash(key);
            for(int i = 0;table[(h+pow(i,2))%tableSize].key != "";i++){
                if(table[(h+pow(i,2))%tableSize].key == key){
                    return true;
                }
            }
            return false;
}