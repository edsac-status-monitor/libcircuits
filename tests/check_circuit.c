#include <check.h>
#include <unistd.h>

#include "check_macros.h"
#include "../include/circuit.h"

//#define TEST_FILE "./example_input.asc"
#define TEST_FILE "./example_inputs/test_flip_flop.asc"

/* Test: test_circuit_parse_file
 *  covers:
 *  assumes working:
 */

// TODO - need to finish these tests!

START_TEST (test_circuit_parse_file)
{
    FILE* fp;
    circuit_t circuit;


    // Check the input file exists
    ck_assert_msg(access(TEST_FILE, F_OK) != -1, "Could not open file " TEST_FILE );

    // Open the file, and parse
    fp = fopen(TEST_FILE, "r");

    circuit_init(&circuit);
    circuit_parse_file(fp, &circuit);

    // Close the file
    fclose(fp);

    // Free dynamic memory
    circuit_free(&circuit);
}
END_TEST


START_CHECK_MAIN (circuit)
{
    CREATE_TEST_CASE(core);
    ADD_TEST(core, test_circuit_parse_file);
}
END_CHECK_MAIN


