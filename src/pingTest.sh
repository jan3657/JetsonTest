#!/bin/bash

# Check if an IP address is provided as a command-line argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <ip_address>"
    exit 1
fi

# Extract the IP address from the command-line argument
ip_address=$1

# Ping the IP address
ping -c 1 $ip_address > /dev/null

# Check the exit status of the ping command
if [ $? -eq 0 ]; then
    echo "successful"
else
    echo "Failed"
fi

