import sys
import subprocess
import time

f_input_name = 'input'
f_output_name = 'output'

with open("Config.txt") as f_config:
    try:
        path_pref = f_config.readline()[:-1]
        exe_path = f_config.readline()[:-1]        
        n_tests = int(f_config.readline()[:-1])
        timeout = int(f_config.readline())
    except Exception as e:
        print("Error in Config.txt: \n" + e)
        sys.exit(1)
        

f_input_name = path_pref + f_input_name
f_output_name = path_pref + f_output_name

def run_inst(i, input):
    return subprocess.run(exe_path, timeout=timeout, capture_output=True,input=input.encode('UTF-8')).stdout.decode('UTF-8')

for i in range(1,n_tests+1):
    with open(f_input_name+str(i)+".txt") as f_input, open(f_output_name+str(i)+".txt") as f_output:
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
                #print(f"{(result)}a{(expected_res)}a")
        except subprocess.TimeoutExpired:
            print(f"Test case {i}: Fail, Time limit exceeded")
        except:
            print(f"Test case {i}: Fail, Unknown Error (It's your program's fault, not mine. I think)")
