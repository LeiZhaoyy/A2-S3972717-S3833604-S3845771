#!/bin/bash

# Backup original data files
cp foods.dat foods_backup.dat
cp coins.dat coins_backup.dat

# Run the program with the test input
./ftt foods.dat coins.dat < test_req6.input > test_req6.input.actual_output

# Compare the actual output to the expected output
diff -w test_req6.input.actual_output test_req6.expected_output
output_diff=$?

# Verify that data files are correctly updated
diff -w -y foods.dat test_req6.expected_foods
foods_diff=$?
diff -w -y coins.dat test_req6.expected_coins
coins_diff=$?

# Restore original data files
mv foods_backup.dat foods.dat
mv coins_backup.dat coins.dat

# Check if test passed
if [ $output_diff -eq 0 ] && [ $foods_diff -eq 0 ] && [ $coins_diff -eq 0 ]; then
    echo "Test Passed: All files are correctly updated and program exited without error."
else
    echo "Test Failed: Differences detected or errors occurred."
fi
