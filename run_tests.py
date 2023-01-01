import sys
import subprocess
import time
from os.path import isfile
from os.path import isdir
from os import access
from os import X_OK

# Function to test if the given path corresponds to an executable
def is_exe(fpath):
    return isfile(fpath) and access(fpath, X_OK)


# Handles fatal errors. Displays custom message to user until enter is pressed and then terminates
def fatal_error_handler(name):
    print(name)
    input("\nPress enter to exit:")
    sys.exit(1)

f_input_name = 'input'
f_output_name = 'output'

# Check if Config.txt exists
if not isfile("Config.txt"): fatal_error_handler(
    """Error: Config.txt not provided. Please provide the file with the following format:
    Path to folder containing test cases
    Path to executable being tested
    Number of test cases checked
    Timeout in seconds"""
    )

# Configure from Config.txt
with open("Config.txt") as f_config:
    try:
        path_pref = f_config.readline()[:-1]
        exe_path = f_config.readline()[:-1]        
        n_tests = int(f_config.readline())
        timeout = int(f_config.readline())
    except Exception as e:
        fatal_error_handler("Error in Config.txt")

# Check if folder exists
if not isdir(path_pref): fatal_error_handler("Error: Test case folder not found")

# Check if executable exists
if not is_exe(exe_path): fatal_error_handler("Error: Path given for executable does not correspond to an executable")

# Construct pathnames
f_input_name = path_pref + f_input_name
f_output_name = path_pref + f_output_name

# Function to run each instance
def run_inst(i, input):
    return subprocess.run(exe_path, timeout=timeout, capture_output=True,input=input.encode('UTF-8')).stdout.decode('UTF-8')


# MAIN CHECK LOOP
for i in range(1,n_tests+1):
    # Construct full names and check if they exist
    f_in = f_input_name+str(i)+".txt"
    if not isfile(f_in):
        print(f"Test case {i}: Fail, input file not found")
        continue
    f_out = f_output_name+str(i)+".txt"
    if not isfile(f_out):
        print(f"Test case {i}: Fail, output file not found")
        continue
    
    with open(f_in) as f_input, open(f_out) as f_output:
        try:
            time_start = time.time()
            result = run_inst(i,f_input.read())
            execution_time = time.time()-time_start
            result = str(result).replace("\r",'')
            expected_res = str(f_output.read())
            if (result==expected_res):
                print(f"Test case {i}: Success, {execution_time:.4f} seconds")
            else:
                print(f"Test case {i}: Fail, Wrong answer {execution_time:.4f} seconds")
        except subprocess.TimeoutExpired:
            print(f"Test case {i}: Fail, Time limit exceeded")
        except:
            print(f"Test case {i}: Fail, Unknown Error (It's probably the exe's fault, e.g. segmentation fault)")
input("\nPress enter to exit:")
