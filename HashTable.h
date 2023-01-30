#pragma once
#include <string>
using std::string;

class HashTable
{
public:
	// default constructor
	// constructs a hash table of size 101. with all array elements set to "". set h2 to
	HashTable();

	// constructs a hash table of size n. size of the underlying array prime >= 2n
	// with all array elements to "". sets the h2 to
	HashTable(int n);

	// copy constructor
	// constructs a deep copy of ht
	HashTable(const HashTable& ht);

	// destructor deallocates the memory of the underlying array
	~HashTable();

	// overloaded assignment operator makes the object a deep copy of ht
	HashTable& operator=(const HashTable& ht);

	// insert method: inserts the string parameter into the hashtable array resizing when necessary
	void insert(string word);

	// find method returns true if the string parameter is in the hashtable otherwise returns false
	bool find(string word) const;

	// size method returns the numbers of items stored in the hashtable
	int size() const;

	// maxSize method returns the size of the underlying array
	int maxSize() const;

	// loadFactor method returns the load factor of the hashtable
	double loadFactor() const;

private:
	// PRIVATE ATTRIBUTES

	// pointer to the array of words
	string* arr;
	// records the underlying array size
	int arrSize;
	// records the number of words stored in the underlying array
	int words;
	// stores the prime number used by the second hash function
	int secondHashPrime;

	// PRIVATE HELPER METHODS
	
	// deep copies the values of the hashtable and all hashtables attirtes
	void copyHashTable(const HashTable& ht);

	// the first hash function: generates the first hash
	int hash1(string word) const;
	// the second hash function: generates the second hash
	int hash2(string word) const;

	// inserts the string parameter into the hastable using hash functions
	void insertWord(string word);
	// resizes the underlying array of the hashtable
	void resizeTable();

	// returns the integer representation of a string moded by the int parameter
	int hornersMethod(string word, int modulo) const;
	// returns the first prime number >= num
	int getPrimeNum(int num) const;
	// returns true if the passed in number is a prime number and false if otherwise
	bool isPrimeNum(int num) const;
};