#!/bin/bash

# Set default values
DEFAULT_USERNAME="soca"
DEFAULT_PASSWORD="soca"
DEFAULT_HOST="10.0.1.40"

HOST=${1:-$DEFAULT_HOST}
USERNAME=${2:-$DEFAULT_USERNAME}
PASSWORD=${3:-$DEFAULT_PASSWORD}


# Connect using SSH
sshpass -p "$PASSWORD" ssh "$USERNAME@$HOST" exit
if [ $? -eq 0 ]; then
    echo "successful"
else
    echo "SSH connection failed."
    sleep 5
fi

