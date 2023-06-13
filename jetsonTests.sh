#!/bin/bash

USERNAME="soca"
PASSWORD="soca"
HOST="10.0.1.40"

while true; do
    sshpass -p "$PASSWORD" ssh "$USERNAME@$HOST" exit
    if [ $? -eq 0 ]; then
        echo "SSH connection successful."
        break
    else
        echo "SSH connection failed. Retrying in 5 seconds..."
        sleep 5
    fi
done
