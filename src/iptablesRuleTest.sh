#!/bin/bash

IP="${1:-}"
USERNAME="${2:-soca}"
PASSWORD="${3:-soca}"

# Check if IP address is provided
if [ -z "$IP" ]; then
    echo "Please provide the IP address as the first parameter."
    exit 1
fi

# SSH to the IP address with the given username and password
sshpass -p "$PASSWORD" ssh -o LogLevel=QUIET -tt "$USERNAME@$IP" -o ConnectTimeout=5 "echo '$PASSWORD' | sudo -S iptables -S" | grep -q "89.212.78.105"
if [ $? -eq 0 ]; then
    echo "successful"
else
    echo "ip table rule with ip '89.212.78.105' does not exist on $IP."
fi
