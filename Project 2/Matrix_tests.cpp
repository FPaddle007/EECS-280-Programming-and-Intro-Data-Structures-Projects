// Project UID af1f95f547e44c8ea88730dfb185559d
#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>
#include <string>
using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(Matrix_fill_basic)
{
    Matrix* mat = new Matrix; // create a Matrix in dynamic memory
    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);
    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h
// as needed.

TEST(Matrix_init_basic)
{
    Matrix* mat = new Matrix;
    
    Matrix_init(mat, 3, 5);
    ASSERT_EQUAL(Matrix_width(mat), 3);
    ASSERT_EQUAL(Matrix_height(mat), 5);

    delete mat;
}

TEST(Matrix_print_basic)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);

    *Matrix_at(mat, 0, 0) = 42;
    ostringstream expected;

    expected << "1 1\n"
        << "42 \n";

    ostringstream actual;

    Matrix_print(mat, actual);
    ASSERT_EQUAL(expected.str(), actual.str());

    delete mat;
}

TEST(Matrix_width_basic)
{
    Matrix* mat = new Matrix;
   
    Matrix_init(mat, 3, 5);

    ASSERT_EQUAL(Matrix_width(mat), 3);
   
    delete mat;
}

TEST(Matrix_height_basic)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 5);

    ASSERT_EQUAL(Matrix_height(mat), 5);
    
    delete mat;
}

TEST(Matrix_row_basic)
{
    Matrix* mat = new Matrix;
 
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 7);
    const int* ptr = Matrix_at(mat, 1, 2);

    ASSERT_EQUAL(Matrix_row(mat, ptr), 1);
    
    delete mat;
}

TEST(Matrix_column_basic)
{
    Matrix* mat = new Matrix;

    Matrix_init(mat, 4, 6);
    Matrix_fill(mat, 0);
    const int* ptr = Matrix_at(mat, 0, 2);

    ASSERT_EQUAL(Matrix_column(mat, ptr), 2);
    
    delete mat;
}

TEST(Matrix_at_basic)
{
    Matrix* mat = new Matrix;
  
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 0);
    *Matrix_at(mat, 0, 0) = 42;
    *Matrix_at(mat, 0, 1) = 37;
    *Matrix_at(mat, 1, 0) = 13;
    *Matrix_at(mat, 1, 1) = 5;

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 42);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 37);
    ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 13);
    ASSERT_EQUAL(*Matrix_at(mat, 1, 1), 5);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 0);
    
    delete mat;
}

TEST(Matrix_fill_border_basic)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 1);
    Matrix_fill_border(mat, 2);

    ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 2);
    ASSERT_EQUAL(*Matrix_at(mat, 2, 1), 2);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 2);

    delete mat;
}

TEST(Matrix_fill_border_2x2)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 2, 2);
    Matrix_fill(mat, 0);
    Matrix_fill_border(mat, 30);

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 30);
    ASSERT_EQUAL(*Matrix_at(mat, 0, 1), 30);
    ASSERT_EQUAL(*Matrix_at(mat, 1, 0), 30);
    ASSERT_EQUAL(*Matrix_at(mat, 1, 1), 30);

    delete mat;
}

TEST(Matrix_fill_border_1x1)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 1, 1);
    Matrix_fill_border(mat, 115);
    
    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 115);

    delete mat;
}
TEST(Matrix_max_basic)
{
    Matrix* mat = new Matrix;
 
    Matrix_init(mat, 2, 2);
    Matrix_fill(mat, 0);

    *Matrix_at(mat, 0, 0) = 34;
    *Matrix_at(mat, 0, 1) = 45;
    *Matrix_at(mat, 1, 0) = 2;
    *Matrix_at(mat, 1, 1) = 69;

    ASSERT_EQUAL(Matrix_max(mat), 69);

    delete mat;

}

TEST(Matrix_column_of_min_value_in_row_basic) 
{
    Matrix* mat = new Matrix;
   
    Matrix_init(mat, 5, 5);
    Matrix_fill(mat, 4);
    *Matrix_at(mat, 0, 1) = 3;

    ASSERT_EQUAL(1, Matrix_column_of_min_value_in_row(mat, 0, 0, 3));

    delete mat;
}

TEST(Matrix_column_of_min_value_in_row_two_mins)
{
    Matrix* mat = new Matrix;
    Matrix_init(mat, 5, 5);
    Matrix_fill(mat, 9);
    *Matrix_at(mat, 4, 0) = 6;
    *Matrix_at(mat, 4, 1) = 6;

    ASSERT_EQUAL(0, Matrix_column_of_min_value_in_row(mat, 4, 0, 3));

    delete mat;
}
TEST(Matrix_min_value_in_row_basic) {
    Matrix* mat = new Matrix;

    Matrix_init(mat, 5, 5);
    Matrix_fill(mat, 5);
    *Matrix_at(mat, 0, 1) = 3;

    ASSERT_EQUAL(3, Matrix_min_value_in_row(mat, 0, 0, 3));

    delete mat;
}

TEST(Matrix_min_value_in_row_1x1)
{
    Matrix* mat = new Matrix;

    Matrix_init(mat, 1, 1);
    Matrix_fill(mat, 7);
    
    ASSERT_EQUAL(7, Matrix_min_value_in_row(mat, 0, 0, 0));

    delete mat;
}


// NOTE: The unit test framework tutorial in Lab 2 originally

// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here