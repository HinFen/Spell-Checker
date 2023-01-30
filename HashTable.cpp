#include "HashTable.h"

// copy constructor
// constructs a hash table of size 101. with all array elements set to "". set h2 to
HashTable::HashTable()
{
	// sets private attributes
	words = 0;
	arrSize = 101;
	arr = new string[arrSize];

	secondHashPrime = getPrimeNum(arrSize/2);

	// fills the array with ""
	for(int i = 0; i < arrSize; i++){
		arr[i] = "";
	}
}

// constructs a hash table of size n. size of the underlying array prime >= 2n
// with all array elements to "". sets the h2 to
HashTable::HashTable(int n)
{
	// sets private attributes	
	words = 0;
	arrSize = getPrimeNum(2*n);
	arr = new string[arrSize];

	secondHashPrime = getPrimeNum(arrSize/2);

	// fills the array with ""
	for(int i = 0; i < arrSize; i++){
		arr[i] = "";
	}
}

// copy constructor
// constructs a deep copy of ht
HashTable::HashTable(const HashTable& ht)
{
	copyHashTable(ht);
}

// destructor deallocates the memory of the underlying array
HashTable::~HashTable()
{
	delete[] arr;
}

// overloaded assignment operator makes the object a deep copy of ht
HashTable& HashTable::operator=(const HashTable& ht)
{
	// protects against self assignment
	if(this != &ht){
		delete[] arr;
		copyHashTable(ht);
	}

	return *this;
}

// insert method: inserts the string parameter into the hashtable array resizing when necessary
void HashTable::insert(string word)
{
	// if the string is empty then do not insert it
	if(word.size() == 0){
		return;
	}

	// inserts the word into the hash table using hash functions
	insertWord(word);

	// if after insertion of the word the loadfactor is > 0.67 resizes the underlying array
	if(loadFactor() > 0.67){
		resizeTable();
	}
}

// find method returns true if the string parameter is in the hashtable otherwise returns false
bool HashTable::find(string word) const
{
	// if the string is empty then it does not exist in the hashtable
	if(word.size() == 0){
		return false;
	}
	
	// gets the first hash
	int firstHash = hash1(word);

	// the word was found then return true
	if(arr[firstHash] == word){
		return true;
	}

	// if the element at the index is "" than the word is not in the hashtable
	if(arr[firstHash] == ""){
		return false;
	}else{
		// if there is a word != the target word already at the first hash than double hash
		// until the target word is found or until "" is found
		int secondHash = hash2(word);
		while(arr[firstHash] != ""){
			// if the target word is found return true
			if(arr[firstHash] == word){
				return true;
			}else{
				// hashes to the next index using the second hash function
				firstHash += secondHash;
				// if the index pointed too by firsthash is outside
				// of the underlying array scope than loops back to the first index
				if(firstHash >= arrSize){
					firstHash -= arrSize;
				}
			}
		}

		// return false if the second hash find "" at the hash
		return false;
	}
}

// size method returns the numbers of items stored in the hashtable
int HashTable::size() const
{
	return words;
}

// maxSize method returns the size of the underlying array
int HashTable::maxSize() const
{
	return arrSize;
}

// loadFactor method returns the load factor of the hashtable
double HashTable::loadFactor() const
{
	// casts the integer variables as doubles so that the return is double
	return static_cast<double>(words)/static_cast<double>(arrSize);
}

// PRIVATE HELPER FUNCTIONS

// deep copies the values of the hashtable and all hashtables attirtes
void HashTable::copyHashTable(const HashTable &ht)
{
	//sets private attribues
	arrSize = ht.arrSize;
	words = ht.words;
	secondHashPrime = ht.secondHashPrime;

	// copies over array contents
	arr = new string[arrSize];
	for(int i = 0; i < arrSize; i++){
		arr[i] = ht.arr[i];
	}
}

// the first hash function: generates the first hash
int HashTable::hash1(string word) const
{
	//hash function: string value % arrsize
	return hornersMethod(word, arrSize);
}

// the second hash function: generates the second hash
int HashTable::hash2(string word) const
{
	// hash function: secondHashPrime - (string value & secondHashPrime)
	return secondHashPrime - hornersMethod(word, secondHashPrime);
}

// inserts the string parameter into the hastable using hash functions
void HashTable::insertWord(string word)
{
	// gets the firsthash of the word
	int firstHash = hash1(word);

	// if the element at the index is "" than insert the word there
	if(arr[firstHash] == ""){
		arr[firstHash] = word;
		words++;
	}else{
		// if their is a word already at the first hash than double hash
		// until a valid spot is found or until you find a duplicate word
		int secondHash = hash2(word);
		while(arr[firstHash] != ""){
			// protects against inserting duplicate strings
			if(arr[firstHash] == word){
				return;
			}else{
				// hashes to the next index using the second hash function
				firstHash += secondHash;
				// if the index pointed too by firsthash is outside
				// of the underlying array scope than loops back to the first index
				if(firstHash >= arrSize){
					firstHash -= arrSize;
				}
			}
		}

		// once a valid index is found using double hashing insert the word there
		arr[firstHash] = word;
		words++;
	}
}

// resizes the underlying array of the hashtable
void HashTable::resizeTable()
{
	// creates a deep copy of the current hash table's array
	int tempSize = arrSize;
	string* temp = new string[tempSize];

	for(int i = 0; i < arrSize; i++){
		temp[i] = arr[i];
	}

	// resize the current array
	arrSize = getPrimeNum(2*arrSize);

	// clears the underlying array and sets new memory space for it
	delete[] arr;
	arr = new string[arrSize];
	// resets the size and sets the new secondHashprime
	words = 0;
	secondHashPrime = getPrimeNum(arrSize/2);

	// fills the new underlying array with ""
	for(int i = 0; i < arrSize; i++){
		arr[i] = "";
	}

	// rehashes all words back into the new underlying array
	for(int i = 0; i < tempSize; i++){
		if(temp[i] != ""){
			insert(temp[i]);
		}
	}

	delete[] temp;
}

// returns the integer representation of a string moded by the int parameter
int HashTable::hornersMethod(string word, int modulo) const
{
	// gets the asci value of the left most char
	int stringValue = (word.at(0) - 96);

	// in the case where the left most char is the only char in the string
	// simply mod it
	if(word.size() == 1){
		stringValue %= modulo;
	}

	// otherwise apply horners method to the rest of the word
	for(int i = 1; i < word.size(); i++){
		stringValue *= 32;
		stringValue += (word.at(i) - 96);
		stringValue %= modulo;
	}

	return stringValue;
}

// returns the first prime number > num
int HashTable::getPrimeNum(int num) const
{
	// starts with a num that is greater than the number we are comparing it to
	int primeNum = num + 1;

	// increments the number until we find the first primenumber
	while(!isPrimeNum(primeNum)){
		primeNum++;
	}

	return primeNum;
}

// returns true if the passed in number is a prime number and false if otherwise
bool HashTable::isPrimeNum(int num) const
{
	// 0 and 1 are both not prime numbers
	if(num == 0 || num == 1){
		return false;
	}

	// if the number is divisible by 2 to num-1 then it is not a prime number
	for(int i = 2; i < num; i++){
		if(num % i == 0){
			return false;
		}
	}

	return true;
}