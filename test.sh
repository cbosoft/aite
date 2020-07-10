#!/usr/bin/env bash

while :; do
    echo "aite_server" | entr -s "pkill -x aite_server; ./aite_server&"
    sleep 1
done
