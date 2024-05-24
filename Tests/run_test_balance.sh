#!/bin/bash
cd ..
./ftt foods.dat coins.dat < Tests/test_balance.input > Tests/test_balance.actual_output
cd Tests
diff -w test_balance.actual_output test_balance.expected_output
diff -w -y ../coins.dat test_balance.expected_coins

# Check if test passed
if [ $? -eq 0 ]; then
    echo "Test Passed: All outputs and coins state are as expected."
else
    echo "Test Failed: Differences detected."
fi
