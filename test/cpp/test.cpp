#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


std::string executeCommand(const std::string& command) {
    std::string filename = "output.txt";
    std::string fullCommand = command + " > " + filename;
    
    int status = std::system(fullCommand.c_str());
    if (status == -1) {
        return "Failed to execute the command";
    }
    
    std::ifstream inputFile(filename);
    std::string output;
    
    if (inputFile) {
        std::getline(inputFile, output);
        inputFile.close();
        std::remove(filename.c_str());

    } else {
        return "Failed to open the temp output file";
    }

    if (!output.empty()) {
        return output;
    } else {
        return "No output from the script" ;
    }
}


std::string ipAddresses[] = {
        "10.0.1.78"
        //"46.122.11.22",
        //"46.122.11.23",
        //"46.122.11.24",
        //"46.122.11.25",
        //"46.122.11.26",
        //"46.122.11.27"
    };


/*
TEST_CASE("Testing Ping"){
    for (const auto& ip : ipAddresses) {
        std::string command = std::string("bash ../../src/pingTest.sh ").append(ip);
        INFO("Device ip :",ip);
        CHECK(executeCommand(command) == "successful");
    }
}
TEST_CASE("Testing SSH"){
    for (const auto& ip : ipAddresses) {
        std::string command = std::string("bash ../../src/sshTest.sh ").append(ip);
        INFO("Device ip :",ip);
        CHECK(executeCommand(command) == "successful");      
    }
}

TEST_CASE("Testing if ip rule is up"){
    for (const auto& ip : ipAddresses) {
        std::string command = std::string("bash ../../src/iptablesRuleTest.sh ").append(ip);
        INFO("Device ip :",ip);
        CHECK(executeCommand(command) == "successful");
    }
}
*/

TEST_CASE("Testing devices"){
    for (const auto& ip : ipAddresses) {
        INFO("Device ip :",ip);

        SUBCASE("Testing Ping"){
            std::string command = std::string("bash ../../src/pingTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful");
        }
        SUBCASE("Testing SSH"){
            std::string command = std::string("bash ../../src/sshTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful"); 
        }
        SUBCASE("Testing if ip rule is up"){
            std::string command = std::string("bash ../../src/iptablesRuleTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful"); 
        }
    }
}



