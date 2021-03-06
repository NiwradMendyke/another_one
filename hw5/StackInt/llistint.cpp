/*
* Darwin Mendyke
* mendyke@usc.edu
* CS104
*
* Integer Linked list class. 
* Contains functions for inserting, removing, setting, getting, and clearing data.
* Also contains overloading functions for copying, assignment, and concatenation. 
*/

#include "llistint.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using namespace std;

// constructor for the linked list
LListInt::LListInt(): head_(NULL), tail_(NULL), size_(0) {};

//Copy constructor (deep copy)
LListInt::LListInt(const LListInt& other): head_(NULL), tail_(NULL), size_(0) {  
  Item *other_tail = other.tail_;

  while (other_tail != NULL) { // inserts items from other list into this list
    insert(0, other_tail->val);
    other_tail = other_tail->prev;
  }
};

// deconstructor
LListInt::~LListInt() {
  clear();
}

// checks if the list is empty
bool LListInt::empty() const {
  return size_ == 0;
}

// checks the size of the list
int LListInt::size() const {
  return size_;
}

// Function to place a new element into the list
void LListInt::insert(int loc, const int& val) {
  if (size_ == 0 && loc == 0) { // if there is nothing in the array
    head_ = new Item(val, NULL, NULL);
    tail_ = head_;
    size_++;
  }
  else if (loc < 0 || loc > (size_)){ // if new position is out of bounds
    throw std::invalid_argument("bad location");
  }
  else if (size_ == 1 && loc == 1) { // if there is one item in list
    tail_ = new Item(val, head_, NULL);
    head_->next = tail_;
    size_++;
  }
  else if (size_ == 1 && loc == 0) {
    Item *newNode = new Item(val, NULL, tail_);
    tail_->prev = newNode;
    head_ = newNode;
    size_++;
  }
  else if (loc == size_) { // if adding to end of list
    Item *temp = new Item(val, tail_, NULL);
    tail_->next = temp;
    tail_ = temp;
    size_++;
  }
  else if (loc == 0 && size_ > 1) { // if adding to the beginning of list
    Item *newNode = new Item(val, NULL, head_);
    head_->prev = newNode;
    head_ = newNode;
    size_++;
  }
  else { // if adding into middle of the list
    Item *temp = getNodeAt(loc);
    Item *newNode = new Item(val, temp->prev, temp);
    temp->prev->next = newNode;
    temp->prev = newNode;
    size_++;
  }

  return;
}

// Function to remove an element from a specified location in the list
void LListInt::remove(int loc) {
  if (size_ == 0) { // if there is nothing to remove
    throw std::invalid_argument("no items to remove");
  }
  else if(loc < 0 || loc >= size_){ // if specified position is out of bounds
    throw std::invalid_argument("bad location");
  }
  else if (loc == 0 && size_ == 1) { // if only one item in list
    Item *temp = head_;
    delete temp;
    head_ = NULL;
    tail_ = NULL;
    size_--;
  }
  else if (loc == 0 && size_ > 1) { // if removing item at the start of list
    Item *temp = head_;
    head_->next->prev = NULL;
    head_ = temp->next;
    delete temp;
    size_--;
  }
  else if (loc == (size_ - 1)) { // if removing item at end of list
    Item *temp = tail_;
    tail_->prev->next = NULL;
    tail_ = temp->prev;
    delete temp;
    size_--;
  }
  else { // if removing an item from middle of the list
    Item *temp = getNodeAt(loc);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
    size_--;
  }
}

// Function to change the value of an element in the list
void LListInt::set(int loc, const int& val) {
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

// Function to check the value of an element at a specific location
int& LListInt::get(int loc) {
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const {
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}


//Assignment Operator (deep copy)
LListInt& LListInt::operator=(const LListInt& other) {
	if (head_ == other.head_) // checks if this and other are the same list
    return *this;

  clear(); // clears this list first

  Item *other_tail = other.tail_;

  while (other_tail != NULL) { // then copies over elements from the other list
      insert(0, other_tail->val);
      other_tail = other_tail->prev;
  }

  return *this;
}

//Concatenation Operator (other should be appended to the end of this)
LListInt LListInt::operator+(const LListInt& other) const {
  LListInt new_list = LListInt(); // creates a new list
  Item *this_item = head_;
  Item *other_item = other.head_;

  while (this_item != NULL) { // adds items from this list to the new lists
    new_list.insert(new_list.size_, this_item->val);
    this_item = this_item->next;
  }

  while (other_item != NULL) { // adds items from other list to the new list
    new_list.insert(new_list.size_, other_item->val);
    other_item = other_item->next;
  }
  
  return new_list;
}

// Access Operator
int const & LListInt::operator[](int position) const {
  return get(position);
}


// Function to iterate through list and delete each item
void LListInt::clear() {
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

// private Function to retrieve a pointer to the item at a specified location
// used by other methods to access node at a particular loc
LListInt::Item* LListInt::getNodeAt(int loc) const {
  Item *temp = head_;
  
  while (loc != 0) { // iterates through the list until reaches loation
    temp = temp->next;
    loc--;
  }

  return temp;
}
