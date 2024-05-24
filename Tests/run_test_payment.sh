
#chmod +x run_test_payment.sh


#./ftt foods.dat coins.dat < test_payment.input > test_payment.actual_output
#diff -w test_payment.actual_output test_payment.expected_output





#diff -w -y coins.dat test_payment.expected_coins

# Check if test passed
#if [ $? -eq 0 ]; then
#   echo "Test Passed: All outputs and coins state are as expected."
#else
#   echo "Test Failed: Differences detected."
#fi



#!/bin/bash

# Define an array of test cases
declare -a tests=("test_payment" "test_overpayment" )
test_passed=true

# Switch to the parent directory to access data files
cd ..

# Loop through all test cases
for test in "${tests[@]}"; do
    echo "Running test: $test"
    ./ftt foods.dat coins.dat < Tests/"${test}.input" > Tests/"${test}.actual_output"
    
    # Compare outputs
    diff -w Tests/"${test}.actual_output" Tests/"${test}.expected_output"
    if [ $? -ne 0 ]; then
        echo "Test $test Failed: Differences detected."
        test_passed=false
    else
        echo "Test $test Passed."
    fi
done

# Return to the Tests directory
cd Tests

# Final result
if [ "$test_passed" = true ]; then
    echo "All tests passed."
else
    echo "Some tests failed."
fi
