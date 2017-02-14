#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )"

if [ ! -e "${DIR}/scripts/cppcheck.sh" ] ; then
    exit 1
fi

echo "running cppcheck..."
cppcheck --enable=all -f --inline-suppr --verbose --report-progress --xml -rp="${DIR}" "$DIR/src/"
