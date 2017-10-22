
#include <stdlib.h>

//#include "config.h"

#include <check.h>
#include <time.h>

#include "check_macros.h"
#include "../include/vector.h"

#define VECTOR_LEN 100

/* Test: test_vector_create_destroy
 *  covers:
 *   vector_create
 *   vector_destroy
 *
 *  assumes working:
 *   vector_add
 *   vector_get
 *
 */
START_TEST (test_vector_create_destroy)
{
    vector_t a;
    size_t i;

    int test_values[VECTOR_LEN];
    int test_values_pre_free[VECTOR_LEN];

    vector_init(&a);

    // Check initial values are correct
    ck_assert_int_eq(a.length, 0);
    ck_assert_int_eq(a.capacity, 0);
    ck_assert_ptr_eq(a.data, NULL);

    srand(time(NULL));

    // Populate with some data
    for (i=0; i<VECTOR_LEN; i++)
    {
        test_values[i] = rand();
        test_values_pre_free[i] = test_values[i];

        vector_add(&a, &test_values[i]);
    }

    // Free the array
    vector_free(&a);

    // Ensure that values have been correctly set post-free
    ck_assert_int_eq(a.length, 0);
    ck_assert_int_eq(a.capacity, 0);
    ck_assert_ptr_eq(a.data, NULL);

    // Ensure that the source data has not been touched
    for (i=0; i<VECTOR_LEN; i++)
    {
        ck_assert_int_eq(test_values[i], test_values_pre_free[i]);
    }

}
END_TEST

/* Test: test_vector_clear
 *  covers:
 *   vector_clear
 *
 *  assumes working:
 *   vector_init
 *   vector_add
 *   vector_free
 */
START_TEST(test_vector_clear)
{
    vector_t a;
    size_t i;

    int test_values[VECTOR_LEN];
    int test_values_pre_clear[VECTOR_LEN];
    int capacity_pre_clear;

    // Covered in test_vector_create_destroy
    vector_init(&a);

    srand(time(NULL));

    // Populate with some data
    for (i=0; i<VECTOR_LEN; i++)
    {
        test_values[i] = rand();
        test_values_pre_clear[i] = test_values[i];

        vector_add(&a, &test_values[i]);
    }

    capacity_pre_clear = a.capacity;

    // Clear the array
    vector_clear(&a);

    // Ensure that values have been correctly set
    ck_assert_int_eq(a.length, 0);
    ck_assert_int_eq(a.capacity, capacity_pre_clear);
    ck_assert_ptr_ne(a.data, NULL);

    // Ensure that the source data has not been touched by the clear
    for (i=0; i<VECTOR_LEN; i++)
    {
        ck_assert_int_eq(test_values[i], test_values_pre_clear[i]);
    }

    // Free is checked elsewhere
    vector_free(&a);

}
END_TEST

/* Test: test_vector_add_pop_get_set
 *  covers:
 *   vector_add
 *   vector_get
 *   vector_pop
 *   vector_get
 *
 *  assumes working:
 *   vector_init
 *   vector_free
 */
START_TEST(test_vector_add_pop_get_set)
{
    vector_t a;
    size_t i;
    size_t j;

    int test_values_A[VECTOR_LEN];
    int test_values_B[VECTOR_LEN];

    int length_post_populate;
    int capacity_post_populate;

    // Covered in test_vector_create_destroy
    vector_init(&a);

    srand(time(NULL));

    // Populate with some data
    for (i=0; i<VECTOR_LEN; i++)
    {
        test_values_A[i] = rand();
        test_values_B[i] = rand();

        // Add the data
        vector_add(&a, &test_values_A[i]);

        // Check that the length is correct
        ck_assert_int_eq(a.length, i+1);
        ck_assert_int_ge(a.capacity, a.length);

        // Check that the added value is correct]
        ck_assert_ptr_eq(a.data[a.length-1], &test_values_A[i]);
    }

    // Check length is correct
    ck_assert_int_eq(a.length, VECTOR_LEN);
    ck_assert_int_ge(a.capacity, VECTOR_LEN);

    capacity_post_populate = a.capacity;
    length_post_populate = a.length;

    // Check vector contents are correct
    for (i=0; i<VECTOR_LEN; i++)
    {
        ck_assert_ptr_eq(&test_values_A[i], vector_get(&a, i));

        // Check that nothing has changed (it shouldn't have)
        ck_assert_int_eq(capacity_post_populate, a.capacity);
        ck_assert_int_eq(length_post_populate, a.length);
    }


    // Check that we can set data
    for (i=0; i<VECTOR_LEN; i++)
    {
        vector_set(&a, i, &test_values_B[i]);

        // Check that the data has been set
        ck_assert_ptr_eq(&test_values_B[i], vector_get(&a, i));

        // Check that nothing has changed (it shouldn't have)
        ck_assert_int_eq(capacity_post_populate, a.capacity);
        ck_assert_int_eq(a.length, length_post_populate);
    }

    // Set something out of range
    //  shouldn't change the data
    vector_set(&a, VECTOR_LEN+1, &test_values_B[0]);
    for (i=0; i<VECTOR_LEN; i++)
    {
        // Check that the data has been set
        ck_assert_ptr_eq(&test_values_B[i], vector_get(&a, i));

        // Check that nothing has changed (it shouldn't have)
        ck_assert_int_eq(capacity_post_populate, a.capacity);
        ck_assert_int_eq(a.length, length_post_populate);
    }


    // Pop the data out
    for (i=0; i<VECTOR_LEN; i++)
    {
        // Remove some data
        vector_pop(&a, 0);

        // Check the data has been correctly shifted down
        for (j=0; j<VECTOR_LEN-i-1; j++)
        {
            ck_assert_ptr_eq(&test_values_B[i+j+1], vector_get(&a, j));
        }

    }

    vector_free(&a);

}
END_TEST

START_CHECK_MAIN (vector)
{
    CREATE_TEST_CASE(core);
    ADD_TEST(core, test_vector_create_destroy);
    ADD_TEST(core, test_vector_clear);
    ADD_TEST(core, test_vector_add_pop_get_set);
}
END_CHECK_MAIN

