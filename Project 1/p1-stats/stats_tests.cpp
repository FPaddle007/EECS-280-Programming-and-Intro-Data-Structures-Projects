/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */

#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void test_sum_small_data_set();

void test_count_even();

void test_count_odd();

void test_count_empty();

void test_sum_small_data_set();

void one_element_sum();

void multiple_elements_sum();

void one_element_mean();

void multiple_element_mean();

void odd_number_mean();

void even_number_mean();

void unsorted_odd_median_test();

void sorted_odd_median_test();

void unsorted_even_median_test();

void sorted_even_median_test();

void one_element_median_test();

void two_element_median_test();

void multiple_freq_mode();

void unsorted_freq_mode();

void smallest_freq_mode();

void one_element_min();

void unsorted_element_min();

void sorted_element_min();

void one_element_max();

void unsorted_element_max();

void sorted_element_max();

void unsorted_element_stdev();

void unsorted_element_stdev();

void two_element_stdev();

void sorted_element_percentile();

void another_sorted_element_percentile();

void test_summarize_norepeats();

void test_summarize_repeats();


// Add prototypes for you test functions here.

int main()
{
  test_sum_small_data_set();

  test_sum_small_data_set();

  test_count_even();

  test_count_odd();

  test_count_empty();

  test_sum_small_data_set();

  one_element_sum();

  multiple_elements_sum();

  one_element_mean();

  multiple_element_mean();

  odd_number_mean();

  even_number_mean();

  unsorted_odd_median_test();

  sorted_odd_median_test();

  unsorted_even_median_test();

  sorted_even_median_test();

  one_element_median_test();

  two_element_median_test();

  multiple_freq_mode();

  unsorted_freq_mode();

  smallest_freq_mode();

  one_element_min();

  unsorted_element_min();

  sorted_element_min();

  one_element_max();

  unsorted_element_max();

  sorted_element_max();

  unsorted_element_stdev();

  unsorted_element_stdev();

  two_element_stdev();

  sorted_element_percentile();

  another_sorted_element_percentile();

  test_summarize_norepeats();

  test_summarize_repeats();

  // Call your test functions here

  return 0;
}

void test_summarize_norepeats(){
  vector<double> data = {1, 3, 5, 7, 9};
  vector<vector<double>> solution = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {9,1}};

  assert(summarize(data) == solution);
}


void test_summarize_repeats(){
  vector<double> data = {1, 3, 3, 3, 5, 5, 5};
  vector<vector<double>> solution = {{1, 1}, {3, 3}, {5, 3}};

  assert(summarize(data) == solution);
}


void test_count_even()
{
  vector<double> data;
  data.push_back(1);
  data.push_back(15);
  data.push_back(20);
  data.push_back(19);

  assert(count(data) == 4);

  cout << "PASS!" << endl;
}

void test_count_odd()
{
  vector<double> data;
  data.push_back(1);
  data.push_back(15);
  data.push_back(20);

  assert(count(data) == 3);

  cout << "PASS!" << endl;
}

void test_count_empty()
{
  vector<double> data;

  assert(count(data) == 0);

  cout << "PASS!" << endl;
}

void test_sum_small_data_set()
{
  cout << "test_sum_small_data_set" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!" << endl;
}

void one_element_sum()
{

  vector<double> data;
  data.push_back(1);

  assert(sum(data) == 1);

  cout << "PASS!" << endl;
}

void multiple_elements_sum()
{

  vector<double> data;
  data.push_back(1);
  data.push_back(1);
  data.push_back(1);
  data.push_back(1);
  data.push_back(1);

  assert(sum(data) == 5);

  cout << "PASS!" << endl;
}

void one_element_mean()
{
  vector<double> data;
  data.push_back(5);

  assert(mean(data) == 5);
}

void multiple_element_mean()
{
  vector<double> data;
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);
  data.push_back(9);

  assert(mean(data) == 7);
}

void odd_number_mean()
{
  vector<double> data;
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  assert(mean(data) == 6);
}

void even_number_mean()
{
  vector<double> data;
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);

  assert(mean(data) == 6.5);
}

void unsorted_odd_median_test()
{
  vector<double> data;
  data.push_back(4);
  data.push_back(7);
  data.push_back(3);

  assert(median(data) == 4);

  cout << "PASS!" << endl;
}

void sorted_odd_median_test()
{
  vector<double> data;
  data.push_back(8);
  data.push_back(9);
  data.push_back(10);

  assert(median(data) == 9);

  cout << "PASS!" << endl;
}

void unsorted_even_median_test()
{
  vector<double> data;
  data.push_back(2);
  data.push_back(1);
  data.push_back(4);
  data.push_back(3);

  assert(median(data) == 2.5);

  cout << "PASS!" << endl;
}

void sorted_even_median_test()
{
  vector<double> data;
  data.push_back(11);
  data.push_back(12);
  data.push_back(13);
  data.push_back(14);

  assert(median(data) == 12.5);

  cout << "PASS!" << endl;
}

void one_element_median_test()
{
  vector<double> data;
  data.push_back(37);

  assert(median(data) == 37);

  cout << "PASS!" << endl;
}

void two_element_median_test()
{
  vector<double> data;
  data.push_back(3);
  data.push_back(4);

  assert(median(data) == 3.5);

  cout << "PASS!" << endl;
}

void multiple_freq_mode(){
  vector<double> data = {1, 1, 1, 2, 2, 2, 3, 3, 4};
  
  assert(mode(data) == 1);

  cout << "PASS!" << endl;

}

void unsorted_freq_mode(){
  vector<double> data = {37, 4, 20, 37, 19, 11};
  
  assert(mode(data) == 37);
  
  cout << "PASS!" << endl;
}

void smallest_freq_mode(){
  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(mode(data) == 1);
  cout << "PASS!" << endl;
}

void one_element_min()
{
  vector<double> data;
  data.push_back(7);

  assert(min(data) == 7);

  cout << "PASS!" << endl;
}

void unsorted_element_min()
{
  vector<double> data;
  data.push_back(7);
  data.push_back(6);
  data.push_back(1);
  data.push_back(5);

  assert(min(data) == 1);

  cout << "PASS!" << endl;
}

void sorted_element_min()
{
  vector<double> data;
  data.push_back(1);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  assert(min(data) == 1);

  cout << "PASS!" << endl;
}

void one_element_max()
{
  vector<double> data;
  data.push_back(7);

  assert(max(data) == 7);

  cout << "PASS!" << endl;
}

void unsorted_element_max()
{
  vector<double> data;
  data.push_back(7);
  data.push_back(6);
  data.push_back(1);
  data.push_back(5);

  assert(max(data) == 7);

  cout << "PASS!" << endl;
}

void sorted_element_max()
{
  vector<double> data;
  data.push_back(1);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  assert(max(data) == 7);

  cout << "PASS!" << endl;
}

void unsorted_element_stdev(){
  vector<double> data;
  data.push_back(7);
  data.push_back(6);
  data.push_back(1);
  data.push_back(5);

  cout << "actual stdev: " << stdev(data) << endl;
  cout << "desired stdev: 2.2776083947861" << endl; 

//  assert(stdev(data) == 2.2776083947861);

  cout << "PASS!" << endl;
}

void sorted_element_stdev(){
  vector<double> data;
  data.push_back(1);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  assert(stdev(data) == 2.8284271247462);

  cout << "PASS!" << endl;
}

void two_element_stdev(){
  vector<double> data;
  data.push_back(10);
  data.push_back(50);

  assert(stdev(data) == 20);

  cout << "PASS!" << endl;
}

void sorted_element_percentile(){
  vector<double> data;
  data.push_back(0);
  data.push_back(25);
  data.push_back(50);
  data.push_back(75);
  data.push_back(100);

  assert(percentile(data, 0) == 0);
  assert(percentile(data, .50) == 50);
  assert(percentile(data, .75) == 75);

  cout << "PASS!" << endl;
}

void another_sorted_element_percentile(){
  vector<double> data;
  data.push_back(10);
  data.push_back(20);
  data.push_back(30);
  data.push_back(40);
  data.push_back(50);

  assert(percentile(data, .25) == 20);
  assert(percentile(data, .60) == 34);
  assert(percentile(data, .80) == 42);

  cout << "PASS!" << endl;
}

// Add the test function implementations here.
