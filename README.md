# JetsonTest
Repo dedicated to writing test scripts for nvidia jetson nano

<h3> Testing principle </h3>
Calling the bash script from c++ and using doctest to do the unit testing.
 

<h3> Units </h3>

- [x] Pinging the device  
- [x] SSH 
- [x] Firewall 
- [x] VDS service status  
- [x] Sauron status  
- [x] http server test  
- [x] lte connection strenght script test 
- [x] USB relinking (soft link)



 
 
 # Getting started  

 1)Install <curl/curl.h> with `sudo apt-get install libcurl4-openssl-dev` for sending api requests  
 2) Install <nlohmann/json.hpp> with `sudo apt-get install libjsoncpp-dev` for json parsing  
 3) Clone the repo : `git clone https://github.com/jan3657/JetsonTest.git`  
 4) Build : `make`  
 5) Run the tests with : `./test`  
  

 <h3> Command line flag options </h3>  

`./test.exe --list-test-cases`          //List test case names  
`./test.exe --test-case= <math>,<util>` //Execute only matching tests   
`./test.exe --abort-after=10`           //stop tests after 10 failures   
`./test.exe --out=<string>`             //output resoults to file  
`./test.exe --count`                    //get number of tests  
`./test.exe--help`                      //get list of all command line options  


 # Documentation 

1) **Function:** `executeCommand`

**Description:**

This function executes a command in the shell and captures the output. It redirects the output to a temporary file and then reads the content of the file to retrieve the output. The function returns the output of the command as a string.

**parameters:**


    command (const std::string&): The command to be executed in the shell.

**Return Value:**

    std::string: The output of the executed command.

**Exceptions:**

    - If the command execution fails, the function returns the error message "Failed to execute the command".
    - If the temporary output file fails to open, the function returns the error message "Failed to open the temp output file".
    - If the output of the command is empty, the function returns the error message "No output from the script".

 **Example usage**
 ```c++

 std::string result = executeCommand("bash ../../src/pingTest.sh ");
```

2) **How to make new tests:**
    - Add a new TEST_CASE macro to define the new test case.
      Choose an appropriate name for the test case that describes its purpose.
    - Inside the new test case, use a loop to iterate over the ipAddresses.
    - Construct the command specific to the test case using the desired script or command and the IP address.
    - Use executeCommand function to execute the command and capture the output.
    - Compare the output with the expected result using the CHECK macro.
  
# **Test cases**

<h3>Ping</h3>
This test verifies the ability to ping the specified IP address.  

<h4>Test Steps</h4>

1) Execute the command bash ../../src/pingTest.sh <ip_address>.  
2) Capture the output of the command execution.   
3) Check if the output is equal to "successful".
   
<h4>Expected Result</h4>

The output of the command execution should be ``successful``.

<h3>SSH</h3>
This test verifies the ability to establish an SSH connection to the specified IP address.

<h4>Test Steps</h4>  

1) Execute the command bash ../../src/sshTest.sh <ip_address>.
2) Capture the output of the command execution.
3) Check if the output is equal to "successful".
 
<h4>Expected Result</h4>

The output of the command execution should be ``successful``.

<h3>IP rule</h3>
This test verifies the existence of a specific IP rule on the specified IP address.

<h4>Test Steps</h4>
1) Execute the command bash ../../src/iptablesRuleTest.sh <ip_address>.
2) Capture the output of the command execution.
3) Check if the output is equal to "successful".
 
<h4>Expected Result</h4>

The output of the command execution should be ``successful``.

<h3>Sauron</h3>
This test retrieves the status of various components of the Sauron system on the specified IP address.

<h4>Test Steps</h4>

1) Retrieve the status of Sauron components using the function getStatus(<ip_address>).  
2) Check the following status values:  
3) isListeningToYOLO: Check if it is equal to 1.  
4) isRecording: Check if it is equal to 1.  
5) isStarted: Check if it is equal to 1.  
6) isStarting: Check if it is equal to 0.  
 
<h4>Expected Results</h4>

isListeningToYOLO: Expected to be ``1``.  
isRecording: Expected to be ``1``.  
isStarted: Expected to be ``1``.  
isStarting: Expected to be ``0``.  
 
<h3>Signal strength</h3>
This test checks the signal quality of the specified IP address.

<h4>Test Steps</h4>

1) Execute the command bash ../../src/signalQualityTest.sh <ip_address>.  
2) Capture the output of the command execution.  
3) Check if the output is not equal to "0" (indicating a successful signal quality).  

<h4>Expected Result</h4>

The output of the command execution should not be ``0``.

<h3>USB-Softlink</h3> (udev rules)

This test verifies the existence of USB-Softlink udev rules on the specified IP address.

<h4>Test Steps</h4>

1) Execute the command bash ../../src/udevRulesTest.sh <ip_address>.  
2) Capture the output of the command execution.  
3) Check if the output is equal to "successful".  
 
<h4>Expected Result</h4>

The output of the command execution should be ``successful``.

Note: Replace <ip_address> with the actual IP address you want to test in each test case.

# **Test report on 10.0.1.81**

![Screenshot from 2023-06-27 12-35-29](https://github.com/jan3657/JetsonTest/assets/57140292/d82ac018-dd7c-478c-91f4-853b31ed0d73)
