#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL
#include <string>  //for OHQueue and Student class tests

template <typename T>
class List
{
  // OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  // Default List constructor
  List()
      : first(nullptr), last(nullptr), num_nodes(0) {}

  // Copy List constructor
  List(const List<T> &other)
      : first(nullptr), last(nullptr), num_nodes(0)
  {
    copy_all(other);
  }

  // Custom List destructor
  ~List()
  {
    clear();
  }

  // EFFECTS:  returns true if the list is empty
  bool empty() const
  {

    return !first;
  }

  // EFFECTS: returns the number of elements in this List
  // HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //          with a private member variable.  That's how std::list does it.
  int size() const
  {

    return num_nodes;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    assert(!empty());

    return first->datum; // do I want datum here or just dereferenced first?
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    assert(!empty());

    return last->datum;
  }

  // EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum)
  {

    Node *temp = new Node;

    temp->datum = datum;
    temp->prev = nullptr;

    if (empty())
    {
      temp->next = nullptr;
      last = temp;
    }
    else
    {
      first->prev = temp;
      temp->next = first;
    }

    first = temp;

    ++num_nodes;
  }

  // EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {

    Node *temp = new Node;

    temp->datum = datum;
    temp->next = nullptr;

    if (empty())
    {
      temp->prev = nullptr;
      first = temp;
    }
    else
    {
      last->next = temp;
      temp->prev = last;
    }

    last = temp;

    ++num_nodes;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the front of the list
  void pop_front()
  {

    assert(!empty());

    if (size() == 1)
    {
      delete first;

      first = nullptr;
      last = nullptr;
    }
    else
    {
      first = first->next;

      delete first->prev;

      first->prev = nullptr;
    }

    --num_nodes;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the back of the list
  void pop_back()
  {

    assert(!empty());
    if (size() == 1)
    {
      delete last;

      first = nullptr;
      last = nullptr;
    }
    else
    {
      last = last->prev;

      delete last->next;

      last->next = nullptr;
    }

    --num_nodes;
  }

  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes all items from the list
  void clear()
  {

    while (size() > 0)
    {
      pop_back();
    }
  }

  // Overloaded assignment operator for List objects
  void operator=(const List<T> &rhs)
  {

    clear();
    copy_all(rhs);
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  // a private type
  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
  };

  // REQUIRES: list is empty
  // EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other)
  {
    assert(empty());

    for (const Node *ptr = other.first; ptr; ptr = ptr->next)
    {
      push_back(ptr->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int num_nodes; // number of Nodes in List

public:
  ////////////////////////////////////////
  class Iterator
  {
    // OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // Iterator default constructor
    Iterator()
        : node_ptr(nullptr) {}

    // Overloaded ++ operator
    Iterator &operator++()
    {
      assert(node_ptr);
      node_ptr = node_ptr->next;

      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator &operator--()
    {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    // Overloaded * operator
    T &operator*() const
    {
      assert(node_ptr);

      return node_ptr->datum; // allowed to access Nodes like this? done above, so yeah.
    }

    // Overloaded == operator
    bool operator==(Iterator rhs) const
    {

      return node_ptr == rhs.node_ptr;
    }

    // Overloaded != operator
    bool operator!=(Iterator rhs) const
    {

      return node_ptr != rhs.node_ptr;
    }

  private:
    Node *node_ptr; // current Iterator position is a List node

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p)
        : node_ptr(p) {}

  }; // List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {

    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {

    return Iterator();
  }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: may invalidate other list iterators
  // EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
    assert(i.node_ptr);

    if (i.node_ptr == first)
    {
      pop_front(); // respecting interface?
    }
    else if (i.node_ptr == last)
    {
      pop_back();
    }
    else
    {
      i.node_ptr->next->prev = i.node_ptr->prev; // respecting interface?
      i.node_ptr->prev->next = i.node_ptr->next;
      delete i.node_ptr;
      --num_nodes;
    }

    i.node_ptr = nullptr;
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {

    if (i.node_ptr == first)
    {
      push_front(datum); // respecting interface?
    }
    else if (i.node_ptr == last || i.node_ptr == nullptr)
    {
      push_back(datum);
    }
    else
    {
      Node *temp = new Node;

      temp->datum = datum; // respecting interface?
      temp->next = i.node_ptr;
      temp->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = temp;
      i.node_ptr->prev = temp;

      ++num_nodes;
    }
  }
}; // List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
