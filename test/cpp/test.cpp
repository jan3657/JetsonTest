#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>


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
        "10.0.1.78",
        "46.122.11.22",
        "46.122.11.23"
        //"46.122.11.24",
        //"46.122.11.25",
        //"46.122.11.26",
        //"46.122.11.27"
    };


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

using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

void getStatus(const std::string& ip) {
    CURL* curl = curl_easy_init();
    std::string url = ip + "/status";
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            // Parse the JSON response
            json data = json::parse(response);

            // Extract the required values
            bool isListeningToYOLO = data["appState"]["isListeningToYOLO"];
            bool isRecording = data["appState"]["recordingStatus"]["isRecording"];
            bool isStarted = data["appState"]["yoloStatus"]["isStarted"];
            bool isStarting = data["appState"]["yoloStatus"]["isStarting"];

            // Print the values
            std::cout << "isListeningToYOLO: " << isListeningToYOLO << std::endl;
            std::cout << "isRecording: " << isRecording << std::endl;
            std::cout << "isStarted: " << isStarted << std::endl;
            std::cout << "isStarting: " << isStarting << std::endl;
        } else {
            std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
}
