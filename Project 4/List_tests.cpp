// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"
#include <iostream>


using namespace std;


// Student ADT definition
struct Student {
  string uniqname;
  string location;
};

/* LIST FUNCTIONS */


TEST(List_assignment_empty_rhs_full_lhs) {
  List<int> numbers;
  List<int> nums;

  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  ASSERT_FALSE(numbers.empty());
  ASSERT_TRUE(nums.empty());

  numbers = nums;
  ASSERT_TRUE(numbers.empty());
  ASSERT_TRUE(numbers.size() == nums.size());
}

TEST(List_assignment_full_rhs_empty_lhs) {
  List<int> numbers;
  List<int> nums;

  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  ASSERT_FALSE(numbers.empty());
  ASSERT_TRUE(nums.empty());

  nums = numbers;
  ASSERT_FALSE(nums.empty());
  ASSERT_TRUE(numbers.size() == nums.size());
}

TEST(List_assignment_full_rhs_full_lhs) {
  List<int> numbers;
  List<int> nums;

  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }
  
  nums.push_back(12);

  ASSERT_FALSE(nums.size() == numbers.size());
  ASSERT_FALSE(nums.empty());
  ASSERT_FALSE(numbers.empty());
  
  nums = numbers;
  
  List<int>::Iterator orig_it = numbers.begin();
  List<int>::Iterator copy_it = nums.begin();

  for (int j = 0; j < 5; ++j) {
    ASSERT_TRUE(*orig_it == *copy_it);
    ASSERT_FALSE(orig_it == copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST(List_assignment_empty_rhs_empty_lhs) {//check this //it works!
  List<int> numbers;
  List<int> nums;

  nums = numbers;
  ASSERT_TRUE(nums.empty());
}

TEST(List_copy_ctor_filled_List) {
  List<int> numbers;

  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  List<int> num_copy(numbers);

  List<int>::Iterator orig_it = numbers.begin();
  List<int>::Iterator copy_it = num_copy.begin();

  for (int j = 0; j < 5; ++j) {
    ASSERT_TRUE(*orig_it == *copy_it);
    ASSERT_FALSE(orig_it == copy_it);
    ++orig_it;
    ++copy_it;
  }
}

TEST(List_copy_ctor_empty_List) {
  List<int> numbers;
  List<int> num_copy(numbers);
  
  ASSERT_TRUE(num_copy.size() == numbers.size());

  List<int>::Iterator orig_it = numbers.begin();
  List<int>::Iterator copy_it = num_copy.begin();

  ASSERT_TRUE(orig_it == copy_it);
}


TEST(List_clear_multiple_Nodes) {
  List<int> numbers;

  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  ASSERT_FALSE(numbers.empty());

  numbers.clear();
  ASSERT_TRUE(numbers.empty());
  ASSERT_TRUE(numbers.size() == 0);
}

TEST(List_clear_one_Node) {
  List<int> numbers;
  numbers.push_back(0);

  ASSERT_FALSE(numbers.empty());

  numbers.clear();
  ASSERT_TRUE(numbers.empty());
  ASSERT_TRUE(numbers.size() == 0);
}


/* ITERATOR FUNCTIONS */

/*
// TO DO:
// iterator_insert_from_middle_of_list (broken)
// iterator_private_ctor function
*/

TEST(Iterator_erase_List_one_Node) {
  List<int> numbers;
  numbers.push_back(2);

  List<int>::Iterator it = numbers.begin();
  
  ASSERT_FALSE(numbers.empty());
  
  numbers.erase(it);

  ASSERT_TRUE(numbers.size() == 0);
  ASSERT_TRUE(numbers.empty());
}


TEST(Iterator_erase_first_Node) {
  List<int> numbers;
  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  List<int>::Iterator it = numbers.begin();
  numbers.erase(it);

  int counter = 1;
  for (List<int>::Iterator it2 = numbers.begin(); it2 != numbers.end(); ++it2) {
    ASSERT_TRUE(*it2 == counter++);
  }

  ASSERT_TRUE(numbers.size() == 4);
}

TEST(Iterator_erase_last_Node) {
  List<int> numbers;
  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  List<int>::Iterator it = numbers.begin();
  ++++++++it;
  numbers.erase(it);

  int counter = 0;
  for (List<int>::Iterator it2 = numbers.begin(); it2 != numbers.end(); ++it2) {
    ASSERT_TRUE(*it2 == counter++);
  }

  ASSERT_TRUE(numbers.size() == 4);
}

TEST(Iterator_erase_middle_Node) {
    List<int> numbers;
  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  List<int>::Iterator it = numbers.begin();
  ++++it;
  numbers.erase(it);

  int arr[] = {0, 1, 3, 4};
  int counter = 0;
  for (List<int>::Iterator it2 = numbers.begin(); it2 != numbers.end(); ++it2) {
    ASSERT_TRUE(*it2 == arr[counter++]);
  }

  ASSERT_TRUE(numbers.size() == 4);
}


//NEEDS FIXING. UGH.
TEST(Iterator_insert_middle) {
  List<int> numbers;

  for (int i = 0; i < 3; ++i) {
    numbers.push_back(i);
  }

  List<int>::Iterator it = numbers.begin();
  ++it;
  numbers.insert(it, 99);

  ASSERT_TRUE(numbers.size() == 4);

  int arr[] = {0, 99, 1, 2};

  List<int>::Iterator walker = numbers.begin();
  for (int i = 0; i < 4; ++i) {
    ASSERT_TRUE(*walker == arr[i]);
    ++walker;
  }
}


/*TEST(Iterator_private_ctor_null_Iterator) {

}

TEST(Iterator_private_ctor) {
  List<int> numbers;
  numbers.push_back(2);

  List<int>::Iterator it = numbers.begin();
  List<int>::Iterator it2 = numbers.use_private_constructor(it);

  ASSERT_TRUE(it == it2);
  ASSERT_TRUE(*it == *it2);
}
*/

TEST(Iterator_insert_before_first) {
  List<int> numbers;
  numbers.push_back(0);

  for (int i = 1; i < 5; ++i) {
    List<int>::Iterator start = numbers.begin();
    numbers.insert(start, i);
    ASSERT_TRUE(numbers.size() == i + 1);
  }

  int counter = 4;
  for (List<int>::Iterator it = numbers.begin(); it != numbers.end(); ++it) {
    ASSERT_TRUE(*it == counter--);
  }
} 

TEST(Iterator_insert_nullpointing_Iterator) {
  List<int> numbers;
  List<int>::Iterator dump = numbers.end();

  for (int i = 0; i < 5; ++i) {
    numbers.insert(dump, i);
    ASSERT_TRUE(numbers.size() == i + 1);
  }

  int counter = 0;
  for (List<int>::Iterator it = numbers.begin(); it != numbers.end(); ++it) {
    ASSERT_TRUE(*it == counter++);
  }
} 

TEST(Iterator_default_ctor_end_funcs_empty_nonempty_List) {
  List<int> numbers;
  List<int>::Iterator null_begin = numbers.begin();
  List<int>::Iterator end = numbers.end();

  ASSERT_TRUE(null_begin == end);

  numbers.push_back(2);
  List<int>::Iterator nonnull_begin = numbers.begin();
  ASSERT_TRUE(nonnull_begin != null_begin);
  ASSERT_TRUE(nonnull_begin != end);
}


TEST(Iterator_deref_List_push_pop_back_order) {
  List<int> numbers;
  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
    List<int>::Iterator deref1 = numbers.begin();

    for (int j = 0; j < i; ++j) {
      ++deref1;
    }

    ASSERT_TRUE(*deref1 == i);
    ASSERT_FALSE(*deref1 != i);
    ASSERT_EQUAL(numbers.size(), i + 1); 
  }

  ASSERT_FALSE(numbers.empty());

  for (int k = 0; k < 5; ++k) {
    numbers.pop_back();
    List<int>::Iterator deref2 = numbers.begin();

    for (int l = 0; l < (4 - k); ++l) {
      ASSERT_TRUE(*deref2 == l);
      ASSERT_FALSE(*deref2 != l);
      ASSERT_EQUAL(numbers.size(), (4 - k));
      ++deref2;
    }
  }

  List<int>::Iterator it1 = numbers.begin();
  List<int>::Iterator it2 = numbers.end();

  ASSERT_TRUE(it1 == it2);
  ASSERT_TRUE(numbers.empty());
}


TEST(Iterator_deref_List_push_pop_front_order) {
  List<int> numbers;
  for (int i = 0; i < 5; ++i) {
    numbers.push_front(i);
    List<int>::Iterator deref1 = numbers.begin();

    ASSERT_TRUE(*deref1 == i);
    ASSERT_FALSE(*deref1 != i);
    ASSERT_EQUAL(numbers.size(), i + 1);
  }

  ASSERT_FALSE(numbers.empty());

  for (int l = 0; l < 5; ++l) {
    numbers.pop_front();
    List<int>::Iterator deref2 = numbers.begin();
    
    for(int k = (3 - l); k > -1; --k) {
      ASSERT_TRUE(*deref2 == k);
      ASSERT_FALSE(*deref2 != k);
      ASSERT_EQUAL(numbers.size(), (4 - l));
      ++deref2;
    }
  }

  List<int>::Iterator it1 = numbers.begin();
  List<int>::Iterator it2 = numbers.end();

  ASSERT_TRUE(it1 == it2);
  ASSERT_TRUE(numbers.empty());
}

TEST(Iterator_incrementing_chaining) {
    List<Student> basic;
    Student suzy = {"Suzy", "Library, First Floor"};
    Student paul = {"Paul", "Unmarked White Van"};
    Student susan = {"Susan", "Big Red Corvette"};
    Student lonnie = {"Lonnie", "Some Alley"};
    Student maddie = {"Maddie", "Beneath a Tree"};

    basic.push_back(suzy);
    basic.push_back(paul);
    basic.push_back(susan);
    basic.push_back(lonnie);
    basic.push_back(maddie);

    List<Student>::Iterator stepper = basic.begin();
    List<Student>::Iterator jumper = basic.begin();
    List<Student>::Iterator beginner = basic.begin();

    ++stepper;
    --++++jumper; //note: when chaining, compiler works inside-out
    ASSERT_TRUE(stepper == jumper);

    ++stepper;
    ++stepper;
    ASSERT_TRUE(stepper != jumper);
    ASSERT_FALSE(stepper == jumper);
    --++++++jumper;
    ASSERT_TRUE(stepper == jumper);
    ASSERT_FALSE(stepper != jumper);

    ----jumper;
    ++--++++jumper;
    ASSERT_TRUE(stepper == jumper);

    ----jumper;
    ++++--++jumper;
    ASSERT_TRUE(stepper == jumper);

    ------jumper;
    ASSERT_TRUE(jumper == beginner);
    ASSERT_FALSE(jumper != beginner);
}

/* PUSH_BACK()/_FRONT() and POP_BACK()/_FRONT() FUNCTIONS */

//Definitely want to check with iterators
TEST(List_push_pop_funcs_two_Nodes) {
    List<Student> basic;
    Student suzy = {"Suzy", "Library, First Floor"};
    Student paul = {"Paul", "Unmarked White Van"};

    basic.push_back(suzy);
    ASSERT_EQUAL(basic.size(), 1);
    basic.push_back(paul);
    ASSERT_EQUAL(basic.size(), 2);    

    basic.pop_back();
    ASSERT_EQUAL(basic.size(), 1);
    basic.pop_back();
    ASSERT_EQUAL(basic.size(), 0);

    basic.push_front(suzy);
    ASSERT_EQUAL(basic.size(), 1);
    basic.push_front(paul);
    ASSERT_EQUAL(basic.size(), 2);

    basic.pop_front();
    ASSERT_EQUAL(basic.size(), 1);
    basic.pop_front();
    ASSERT_EQUAL(basic.size(), 0);
}

TEST(List_push_pop_funcs_one_Node) {
    List<Student> basic;
    ASSERT_TRUE(basic.empty());
    ASSERT_EQUAL(basic.size(), 0);

    Student suzy = {"Suzy", "Library, First Floor"};
    basic.push_back(suzy);
    ASSERT_FALSE(basic.empty());
    ASSERT_EQUAL(basic.size(), 1);

    basic.pop_back();
    ASSERT_TRUE(basic.empty());
    ASSERT_EQUAL(basic.size(), 0);

    basic.push_front(suzy);
    ASSERT_FALSE(basic.empty());
    ASSERT_EQUAL(basic.size(), 1);

    basic.pop_front();
    ASSERT_TRUE(basic.empty());
    ASSERT_EQUAL(basic.size(), 0);
}

//BROKEN ITERATOR FUNCTIONS
/*
TEST(Iterator_begin) {
  List<int> numbers;
  for (int i = 0; i < 5; ++i) {
    numbers.push_back(i);
  }

  for (int j = 0; j < 5; ++j) {
    numbers.pop_front();
    List<int>::Iterator deref = numbers.begin();
    ASSERT_TRUE(*deref == j + 1);
  }
}
*/

/*
// Double free??? BROKEN
TEST(Iterator_insert_before_middle) {
  List<int> numbers;
  
  for (int i = 0; i < 5; ++i) {
    numbers.push_front(i);
  }

  List<int>::Iterator jump = numbers.begin();
  ++++++jump;
  numbers.insert(jump, 99);

  int arr[] = {4, 3, 2, 99, 1, 0 };

  int counter = 0;
  for (List<int>::Iterator it = numbers.begin(); it != numbers.end(); ++it) {
    ASSERT_TRUE(*it == arr[counter++]);
  }
}
*/

TEST_MAIN()
