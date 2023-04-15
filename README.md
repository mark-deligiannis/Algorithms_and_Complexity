# Algorithms_and_Complexity
Solutions to programming tasks in ECE NTUA course "Algorithms and Complexity".

## run_tests.py
Can test and create a performance report for any program by redirecting files to stdin and checking the output. Configurable from Config.txt.
## Config.txt
Located in the same folder as run_tests.py.
Must contain 4 lines that correspond to:

* Path of the folder containing input & output files
* Path of executable to be tested
* How many input & output files there are
* Timeout in seconds

_See the file provided for an example_

Note that all test files must be located in the same folder. The names for the i-st pair must be "inputi.txt" and "outputi.txt".
