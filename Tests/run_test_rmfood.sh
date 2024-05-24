#!/bin/bash

# Switch to the parent directory to access data files
cd ..

# Execute the ftt program and output the results to the appropriate file in the subdirectory
./ftt foods.dat coins.dat < Tests/test_rmfood.input > Tests/test_rmfood.actual_output

# Return to the Tests subdirectory
cd Tests

# Compare the actual output with the expected output
diff -w test_rmfood.actual_output test_rmfood.expected_output

# Compare the coins.dat file from the parent directory with the expected coins file
diff -w -y ../coins.dat test_rmfood.expected_coins

# Check the exit status of the diff command to determine if the test passed
if [ $? -eq 0 ]; then
    echo "Test Passed: All outputs and coins state are as expected."
else
    echo "Test Failed: Differences detected."
fi
