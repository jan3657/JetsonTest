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
- [ ] lte connection strenght script test 
- [ ] USB relinking (soft link)
- [ ] stress testing (Open more http stream sockets)
- [ ] Stress testing ( 50 % extra cpu load )
- [ ] Speed test
- [ ] Watchdog (Spanje )



 
 
 # Get started  

 
 
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
