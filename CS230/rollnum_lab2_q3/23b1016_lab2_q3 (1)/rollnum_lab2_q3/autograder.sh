#!/bin/bash

# Create a results file (CSV format for Excel compatibility)
results_file="simulation_results.csv"
comparison_file="comparison_results.csv"
echo "Roll Number,Simulation Output" > $results_file
echo "Roll Number,Match" > $comparison_file

# First, run the base design (combinational_karatsuba.v) to get the reference output
iverilog -o base_design tb_combinational_karatsuba.v combinational_karatsuba.v
vvp base_design > base_output.txt
base_output=$(cat base_output.txt)

# Loop through all the roll number Verilog files in the directory
for file in 23b1016_combinational_karatsuba.v; do
    # Extract the roll number (part before "_combinational_karatsuba.v")
    roll_number=$(echo "$file" | sed 's/_combinational_karatsuba.v//')
    
    # Compile and run the simulation for the current roll number file
    iverilog -o my_design tb_combinational_karatsuba.v "$file"
    
    # Check if compilation was successful
    if [[ $? -ne 0 ]]; then
        # If there was an error in compilation, assign zero and print a message
        match_result=0
        echo "Graded $roll_number: Compilation failed, assigning 0"
        echo "$roll_number,$match_result" >> $comparison_file
        continue  # Skip to the next file
    fi
    
    # Run the compiled design if compilation succeeded
    vvp my_design > output.txt

    # Capture the output of the simulation
    simulation_output=$(cat output.txt)

    # Append the roll number and output to the results file
    echo "$roll_number,$simulation_output" >> $results_file
    
    # Compare the current output with the base output
    if [[ "$simulation_output" == "$base_output" ]]; then
        match_result=1
        echo "Graded $roll_number: Matching output"
    else
        match_result=0
        echo "Graded $roll_number: Not matching output"
    fi
    
    # Append the match result to the comparison file
    echo "$roll_number,$match_result" >> $comparison_file
done

# Optional: Clean up temporary files
rm output.txt my_design base_output.txt base_design

echo "Simulations completed. Results saved in $results_file and comparisons in $comparison_file."
