#!/bin/bash

	echo "Starting the program"

	for i in {1..3}; do
		mosquitto_pub -h "ip address" -t test -m "1"
		sleep 10
		mosquitto_pub -h "ip address" -t test -m "2"
		sleep 10
	done

	echo "Ending the program"
	mosquitto_pub -h "ip address" -t test -m "3"
