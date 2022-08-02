#include <iostream>
#include <list>
#include <vector>
 
using namespace std;

// Túlio Ferreira Franco Carvalho;
 
class HashTable{
private:
  list<int> *table;
  int total_elements;
 
  // Hash function to calculate hash for a value:
  int getHash(int key){
    return key % total_elements;
  }
 
public:
  // Constructor to create a hash table with 'n' indices:
  HashTable(int n){
    total_elements = n;
    table = new list<int>[total_elements];
  }
 
  // Insert data in the hash table:
  void insertElement(int key){
    table[getHash(key)].push_back(key);
  }
 
 
 
  void RemoveElement(int key){
    int x = getHash(key);
 
    list<int>::iterator i; 
    for (i = table[x].begin(); i != table[x].end(); i++) {
    
    }
 
 
    // If the item was found in the list, then delete it:
    if (i != table[x].end()) 
      table[x].erase(i);
  }
 
 
  // Remove data from the hash table:
  bool removeElement(int key){
    int x = getHash(key);
 
    list<int>::iterator i; 
    for (i = table[x].begin(); i != table[x].end(); i++) { 
      // Check if the iterator points to the required item:
      if (*i == key)
      
        break;
    }
 
    // If the item was found in the list, then delete it:
    if (i != table[x].end()){
      table[x].erase(i);
      return 1;
    }
    return 0;
  }
 
 
  void printAll(int index){
    
    for( int a: table[index] ){
      cout << " " << a;
    }
    
    /*
    // Traverse each index:
    for(int i = 0; i < total_elements; i++){
      cout << "Index " << i << ": ";
      // Traverse the list at current index:
      for(int j : table[i])
        cout << j << " => ";
 
      cout << endl;
    }
  */
  }
};
 
int main() {
    
  // Create a hash table with 3 indices:
  int size, number, removeNumber, index, count = 0;
  vector<int> listNumber;
  cin >> size;
  
  cin >> number;
  while(number >= 0){
    count++;
    listNumber.push_back(number);
    cin >> number;
  }
 
  cin >> removeNumber;
 
  cin >> index;
 
  HashTable ht(size);
  int a = ht.removeElement(removeNumber);
  // Insert the whole data into the hash table:
  for(int i = 0; i < count; i ++) ht.insertElement(listNumber[i]);
  if(!ht.removeElement(removeNumber)){
    cout << "Valor nao encontrado" << endl;
  }
  cout << "[" << index << "]";
  ht.printAll(index);
 
  return 0;
}