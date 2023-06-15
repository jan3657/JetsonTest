# JetsonTest
Repo dedicated to writing test scripts for nvidia jetson nano

<h3> Testing principle </h3>
Calling the bash script from c++ and using doctest to do the unit testing.
 

<h3> Units </h3>

- [x] Pinging the device  
- [x] SSH 
- [ ] Firewall 
- [ ] VDS service status  
- [ ] Sauron status  
- [ ] http server test  
- [ ] lte connection strenght script test 
- [ ] USB relinking (soft link)
- [ ] stress testing (Open more http stream sockets)
- [ ] Stress testing ( 50 % extra cpu load )
- [ ] Speed test 


<h3> Command line options </h3>  

--list-test-cases          //List test case names
--test-case= <math>,<util> //Execute only matching tests   
--abort-after=10           //stop tests after 10 failures   
--out=<string>             //output resoults to file  
--count                    //get number of tests  
--help                     //get list of all command line options  
 
 
 # Documentation
 
 
 
