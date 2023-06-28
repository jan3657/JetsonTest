// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// #include "doctest.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

std::string executeCommand(const std::string &command)
{
    std::string filename = "output.txt";
    std::string fullCommand = command + " > " + filename;

    int status = std::system(fullCommand.c_str());
    if (status == -1)
    {
        return "Failed to execute the command";
    }

    std::ifstream inputFile(filename);
    std::string output;

    if (inputFile)
    {
        std::getline(inputFile, output);
        inputFile.close();
        std::remove(filename.c_str());
    }
    else
    {
        return "Failed to open the temp output file";
    }

    if (!output.empty())
    {
        return output;
    }
    else
    {
        return "No output from the script";
    }
}

using json = nlohmann::json;

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output)
{
    size_t total_size = size * nmemb;
    output->append(static_cast<char *>(contents), total_size);
    return total_size;
}

std::array<bool, 4> *getStatus(const std::string &ip)
{
    CURL *curl = curl_easy_init();
    std::string url = ip + "/status";
    std::string response;

    std::array<bool, 4> *statusArray = new std::array<bool, 4>();
    (*statusArray)[0] = false;
    (*statusArray)[1] = false;
    (*statusArray)[2] = false;
    (*statusArray)[3] = false;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        CURLcode res = curl_easy_perform(curl);
        if (res == CURLE_OK)
        {
            // Parse the JSON response
            json data = json::parse(response);

            // Extract the required values
            (*statusArray)[0] = data["appState"]["isListeningToYOLO"];
            (*statusArray)[1] = data["appState"]["recordingStatus"]["isRecording"];
            (*statusArray)[2] = data["appState"]["yoloStatus"]["isStarted"];
            (*statusArray)[3] = data["appState"]["yoloStatus"]["isStarting"];
        }
        else
        {
            std::cerr << "Failed to perform request: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return (statusArray);
}

std::vector<std::string> readIPAddressesFromFile(const std::string &filename)
{
    std::vector<std::string> ipAddresses;
    std::ifstream file(filename);

    if (file.is_open())
    {
        std::string ipAddress;
        while (std::getline(file, ipAddress))
        {
            ipAddresses.push_back(ipAddress);
        }
        file.close();
    }
    else
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
    }

    return ipAddresses;
}

std::vector<std::string> ipAddresses = readIPAddressesFromFile("devices.txt");
std::string ip = ipAddresses[0];

void test_header(std::string test_case, std::string test_message)
{
    std::cout << "\033[1;33m TEST CASE:\033[1;0m  ";
    std::cout << " " + test_case << std::endl;
    std::cout << "  " + test_message << std::endl;
    std::cout << std::endl;
}
void test_body(std::string command, std::string condition)
{
    if (executeCommand(command) == condition)
    {
        std::cout << "  Status: \033[1;32mPASS \033[1;36m CHECK(" + executeCommand(command) + " == " + condition + ")\033[1;0m" << std::endl;
    }
    else
    {
        std::cout << "  Status: \033[1;31mFAIL \033[1;36m CHECK(" + executeCommand(command) + " == " + condition + ")\033[1;0m" << std::endl;
    }
    std::cout << "\033[1;33m=======================================================================+========\033[1;0m" << std::endl;
}

void test_device(std::string ip)
{
    std::string command = std::string("");
    std::cout << std::endl;
    std::cout << "\033[1;33mTESTING DEVICE:\033[1;0m " + ip << std::endl;
    std::cout << "\033[1;33m--------------------------------------------------------------------------------\033[1;0m" << std::endl;

    // Test Ping
    test_header("Ping", "This test verifies the ability to ping the specified IP address");
    command = std::string("bash ../../src/pingTest.sh ").append(ip);
    test_body(command, "successful");

    // Test SSH
    test_header("SSH", "This test verifies the ability to establish an SSH connection to the specified IP address");
    command = std::string("bash ../../src/sshTest.sh ").append(ip);
    test_body(command, "successful");

    // Test IP rule
    test_header("IP Rule", "This test verifies the existance of firewall rule");
    command = std::string("bash ../../src/iptablesRuleTest.sh ").append(ip);
    test_body(command, "successful");

    // Sauron
    test_header("Sauron", "This test retrieves the status of various components of the Sauron system on the device");
    std::array<bool, 4> *sauronSatus = getStatus(ip);

    std::cout << std::endl;
    std::cout << "  Suron is isListeningToYOLO" << std::endl;
    if ((*sauronSatus)[0] == 1)
    {
        std::cout << "  Status: \033[1;32mPASS\033[1;0m" << std::endl;
    }
    else
    {
        std::cout << "  Status: \033[1;31mFAIL\033[1;0m" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  Suron is Recording" << std::endl;
    if ((*sauronSatus)[1] == 1)
    {
        std::cout << "  Status: \033[1;32mPASS\033[1;0m" << std::endl;
    }
    else
    {
        std::cout << "  Status: \033[1;31mFAIL\033[1;0m" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "  Yolo is Started" << std::endl;
    if ((*sauronSatus)[2] == 1)
    {
        std::cout << "  Status: \033[1;32mPASS\033[1;0m" << std::endl;
    }
    else
    {
        std::cout << "  Status: \033[1;31mFAIL\033[1;0m" << std::endl;
    }

    // Signal strenght
    test_header("Signal strenght", "This test checks the signal quality of the specified device");
    command = std::string("bash ../../src/signalQualityTest.sh ").append(ip);
    std::cout << "  Status: \033[1;33m \033[1;36m" + executeCommand(command) + "\033[1;0m" << std::endl;
    std::cout << "\033[1;33m=======================================================================+========\033[1;0m" << std::endl;

    // Test IP rule
    test_header("USB-Softlink (udev rules)", "This test verifies the existance of USB-Softlink udev rules on the specified IP address");
    command = std::string("bash ../../src/udevRulesTest.sh ").append(ip);
    test_body(command, "successful");
}

int main()
{
    test_device("10.0.1.81");
}

/*
TEST_CASE("Ping")
{
    std::string command = std::string("bash ../../src/pingTest.sh ").append(ip);
    test_device(ip);
    CHECK(executeCommand(command) == "successful");
}

TEST_CASE("SSH")
{
    std::string command = std::string("bash ../../src/sshTest.sh ").append(ip);
    CHECK(executeCommand(command) == "successful");
}

TEST_CASE("IP rule")
{
    std::string command = std::string("bash ../../src/iptablesRuleTest.sh ").append(ip);
    CHECK(executeCommand(command) == "successful");
}

TEST_CASE("Sauron")
{
    std::array<bool, 4> *sauronSatus = getStatus(ip);
    SUBCASE("Suron is isListeningToYOLO")
    {
        CHECK((*sauronSatus)[0] == 1);
    }
    SUBCASE("Recording")
    {
        CHECK((*sauronSatus)[1] == 1);
    }
    SUBCASE("Yolo is Started")
    {
        CHECK((*sauronSatus)[2] == 1);
    }
    SUBCASE("Yolo is Starting")
    {
        CHECK((*sauronSatus)[3] == 0);
    }
}

TEST_CASE("Signal strenght")
{
    std::string command = std::string("bash ../../src/signalQualityTest.sh ").append(ip);
    WARN(executeCommand(command) != "0");
}
TEST_CASE("USB-Softlink (udev rules)")
{
    std::string command = std::string("bash ../../src/udevRulesTest.sh ").append(ip);
    CHECK(executeCommand(command) == "successful");
}
*/
/*TEST_CASE("Testing devices")
{
    for (const auto &ip : ipAddresses)
    {
        INFO("Device ip :", ip);

        SUBCASE("Testing Ping")
        {
            std::string command = std::string("bash ../../src/pingTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful");
        }
        SUBCASE("Testing SSH")
        {
            std::string command = std::string("bash ../../src/sshTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful");
        }
        SUBCASE("Testing if ip rule is up")
        {
            std::string command = std::string("bash ../../src/iptablesRuleTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful");
        }
        std::array<bool, 4> *sauronSatus = getStatus(ip);
        SUBCASE("Suron is isListeningToYOLO")
        {
            CHECK((*sauronSatus)[0] == 1);
        }
        SUBCASE("Suron is Recording")
        {
            CHECK((*sauronSatus)[1] == 1);
        }
        SUBCASE("Suron Yolo is Started")
        {
            CHECK((*sauronSatus)[2] == 1);
        }
        SUBCASE("Suron Yolo is Starting")
        {
            CHECK((*sauronSatus)[3] == 0);
        }
        SUBCASE("Signal strenght")
        {
            std::string command = std::string("bash ../../src/signalQualityTest.sh ").append(ip);
            WARN(executeCommand(command) != "0");
        }
        SUBCASE("USB-Softlink (udev rules)")
        {
            std::string command = std::string("bash ../../src/udevRulesTest.sh ").append(ip);
            CHECK(executeCommand(command) == "successful");
        }
    }
}*/