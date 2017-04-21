#!/bin/sh
# Note this runs from the project root
./bin/mycompiler assemblytest1 --tofolder temp > /dev/null
exit 0; # 0 means success, 1 means fail