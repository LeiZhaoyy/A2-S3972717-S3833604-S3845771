#!/bin/bash

# Switch to the parent directory to access data files
cd ..

# Run the ftt program with data files and input from the Tests directory
./ftt foods.dat coins.dat < Tests/test_overpayment.input > Tests/test_overpayment.actual_output

# Compare the actual output with the expected output in the Tests directory
diff -w Tests/test_overpayment.actual_output Tests/test_overpayment.expected_output

# Compare the current state of coins.dat with the expected state in the Tests directory
diff -w -y coins.dat Tests/test_overpayment.expected_coins

# Return to the Tests directory
cd Tests

# Check if the test passed
if [ $? -eq 0 ]; then
    echo "Test Passed: All outputs and coins state are as expected."
else
    echo "Test Failed: Differences detected."
fi
