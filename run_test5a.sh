#!/bin/bash
#chmod +x run_test_req5a.sh


./ftt foods.dat coins.dat < test_req5a.input > test_req5a.actual_output
diff -w test_req5a.actual_output test_req5a.expected_output





diff -w -y coins.dat test_req5a.expected_coins

# Check if test passed
if [ $? -eq 0 ]; then
    echo "Test Passed: All outputs and coins state are as expected."
else
    echo "Test Failed: Differences detected."
fi