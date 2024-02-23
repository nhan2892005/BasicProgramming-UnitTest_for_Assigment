#!/bin/bash

# List of commands to be executed
commands=(
    # Run program
    "g++ -o main main.cpp study_in_pink1.cpp -I . -std=c++11" 
    "./main 1 500"
    "rm -r ./main"
)

# Iterate over the commands and execute each one
for cmd in "${commands[@]}"; do
    echo "Executing: $cmd"
    eval "$cmd"
    if [ $? -eq 0 ]; then
        echo "Successfully!"
    else
        echo "Error executing command '$cmd'"
        exit 1
    fi
done

echo "All commands executed successfully"
