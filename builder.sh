#!/bin/bash

if [ $# -ne 2 ]
then
	echo "Usage DIR TYPE"
else
	DIR=$1
	REG=".*$DIR"
	if [[ ! $PWD =~ $REG ]]
	then
		if [ ! -d "$DIR" ]
		then
				mkdir "${1}"
		fi
		cd ${1}
	fi
	cmake .. -DCMAKE_BUILD_TYPE="$2"
	make
fi