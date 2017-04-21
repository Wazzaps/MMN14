#!/bin/sh
# Note this runs from the project root

# No arguments [test 1]
./bin/mycompiler > /dev/null
if [ $? -eq 0 ]; then
	echo "Missing arguments returned success code [test 1]"
	exit 1;
fi

# Only help #1 [test 2]
./bin/mycompiler --help > /dev/null
if [ $? -ne 0 ]; then
	echo "Help flag returned error code [test 2]"
	exit 1;
fi

# Only help #2 [test 3]
./bin/mycompiler -h > /dev/null
if [ $? -ne 0 ]; then
	echo "Help flag returned error code [test 3]"
	exit 1;
fi

# All successful
exit 0;