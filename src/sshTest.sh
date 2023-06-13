#!/bin/bash

USERNAME="soca"
PASSWORD="soca"
HOST="10.0.1.40"

function test() {
  sshpass -p "$PASSWORD" ssh "$USERNAME@$HOST" exit
  if [ $? -eq 0 ]; then
      echo "SSH connection successful."
  else
      echo "SSH connection failed. "
      sleep 5
  fi
}
