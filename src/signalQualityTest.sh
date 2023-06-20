#!/bin/bash

# SSH connection details
# Set default values
DEFAULT_USERNAME="soca"
DEFAULT_PASSWORD="soca"
DEFAULT_HOST="10.0.1.78"

HOST=${1:-$DEFAULT_HOST}
USERNAME=${2:-$DEFAULT_USERNAME}
PASSWORD=${3:-$DEFAULT_PASSWORD}

# SSH command
ssh_command="sshpass -p '$PASSWORD' ssh -o StrictHostKeyChecking=no $USERNAME@$HOST 'systemctl status lte_connection.service'"

# Run the SSH command and capture the output
output=$(eval "timeout 10s $ssh_command")

# Extract the latest "Signal quality" value using grep and awk

signal_quality=$(echo "$output" | grep 'Signal quality:' |awk '/Signal quality: ([0-9]|[12][0-9]|30)\/30/ { value=$NF } END { gsub("/30", "", value); print value }')

# Print the extracted signal quality value
echo "Latest Signal Quality: $signal_quality"
