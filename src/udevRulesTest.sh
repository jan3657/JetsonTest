#!/bin/bash

IP="${1:-}"
USERNAME="${2:-soca}"
PASSWORD="${3:-soca}"

# Check if IP address is provided
if [ -z "$IP" ]; then
    echo "Please provide the IP address to iptablesRuleTest script as the first parameter."
    exit 1
fi

# Array of lines to check
lines=("ttyMODEM_AT" "ttyMODEM_AUDIO" "ttyMODEM_DIAGNOSTIC" "ttyMODEM_GPS" "ttyMODEM_PORT")

# SSH command to execute on the remote device
#ssh_command="for line in ${lines[@]}; do if [ -e \"/dev/\$line\" ]; then echo \"The line '/dev/\$line' exists.\"; else echo \"The line '/dev/\$line' does not exist.\"; fi; done"
ssh_command="found=0; for line in ${lines[@]}; do if [ -e \"/dev/\$line\" ]; then found=1; else found=0; break; fi; done; if [ \$found -eq 1 ]; then echo \"successful\"; else echo \"udev rule \"99-usb-lte.rules\" does not exist on $IP.\"; fi"
#ssh_command= "iptables -S"
# SSH to the device and execute the command

sshpass -p "$PASSWORD" ssh "$USERNAME@$IP" "$ssh_command"
