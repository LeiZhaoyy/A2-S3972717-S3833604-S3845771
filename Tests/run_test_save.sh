#!/bin/bash

# Change directory to parent directory to access data files
cd ..

# Backup original data files
cp foods.dat foods_backup.dat
cp coins.dat coins_backup.dat

# Run the program with the test input from Tests directory
./ftt foods.dat coins.dat < Tests/test_save.input > Tests/test_save.input.actual_output

# Compare the actual output to the expected output in the Tests directory
diff -w Tests/test_save.input.actual_output Tests/test_save.expected_output
output_diff=$?

# Verify that data files are correctly updated, comparing them in the current directory
diff -w -y foods.dat Tests/test_save.expected_foods
foods_diff=$?
diff -w -y coins.dat Tests/test_save.expected_coins
coins_diff=$?

# Restore original data files
mv foods_backup.dat foods.dat
mv coins_backup.dat coins.dat

# Return to Tests directory
cd Tests

# Check if test passed
if [ $output_diff -eq 0 ] && [ $foods_diff -eq 0 ] && [ $coins_diff -eq 0 ]; then
    echo "Test Passed: All files are correctly updated and program exited without error."
else
    echo "Test Failed: Differences detected or errors occurred."
fi
