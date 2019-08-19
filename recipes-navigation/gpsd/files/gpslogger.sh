#!/bin/bash

# First check if a past log exists. If it does, save it.
if [ -f /var/log/gps.json ]; then
	gzip /var/log/gps.json
	mv /var/log/gps.json.gz /var/log/gps.json".$(date +"%Y%m%d-%H%M%S").gz"
fi

exec /usr/bin/gpspipe -w -o /var/log/gps.json localhost:2947

