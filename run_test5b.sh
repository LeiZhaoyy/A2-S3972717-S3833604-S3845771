#!/bin/bash
./ftt foods.dat coins.dat < test_req5b.input > test_req5b.actual_output
diff -w test_req5b.actual_output test_req5b.expected_output





diff -w -y coins.dat test_req5b.expected_coins

# Check if test passed
if [ $? -eq 0 ]; then
    echo "Test Passed: All outputs and coins state are as expected."
else
    echo "Test Failed: Differences detected."
fi