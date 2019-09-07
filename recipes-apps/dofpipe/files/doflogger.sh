#!/bin/bash

log_path="/var/log/"
log_filename="lsm9ds1.json"
original_log_file=${log_path}${log_filename}
log_rotate_conf="/etc/logrotate.d/doflogd"

if [ -f "${original_log_file}" ]; then

	# Read the maximum number of logs from the config
	number_of_logs=$(cat ${log_rotate_conf} | grep "rotate [[:digit:]]" | sed 's/[^0-9]*//g')

	# Check for the last rotated log.
	last_log=$(find "${log_path}" -name "${log_filename}.[[:digit:]].gz" | sort -n | tail -1)
	last_log_count=$(echo $last_log | sed 's/[^0-9]*//g')

	# If the last log is found the restart
	log_count="${last_log_count}"
	if [ "${last_log_count}" == "${number_of_logs}" ]; then
		log_count="1"
	else
		log_count=$(("${log_count}" + 1))
	fi

	gzip "${original_log_file}"
	mv "${original_log_file}".gz "${original_log_file}.${log_count}.gz"
fi

exec dofpipe -t 100 -f "${original_log_file}"

