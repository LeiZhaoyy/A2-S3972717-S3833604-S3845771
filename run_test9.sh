#!/bin/bash
./ftt foods.dat coins.dat < test_req9.input > test_req9.actual_output
diff -w test_req9.actual_output test_req9.expected_output





diff -w -y coins.dat test_req9.expected_coins

# Check if test passed
if [ $? -eq 0 ]; then
    echo "Test Passed: All outputs and coins state are as expected."
else
    echo "Test Failed: Differences detected."
fi