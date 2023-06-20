#!/bin/bash

IP="${1:-}"
USERNAME="${2:-soca}"
PASSWORD="${3:-soca}"


# Check if IP address is provided
if [ -z "$IP" ]; then
    echo "Please provide the IP address to vdsServiceRunningTest.sh script as the first parameter."
    exit 1
fi

# SSH to the IP address with the given username and password
sshpass -p "$PASSWORD" ssh -o LogLevel=QUIET -tt "$USERNAME@$IP" -o ConnectTimeout=5 "systemctl is-active --quiet vds.service"
if [ $? -eq 0 ]; then
    echo "successful"
else
    echo "vds.service is not running on $IP."
fi