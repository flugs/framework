#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )"

if [ ! -e "${DIR}/scripts/sloccount.sh" ] ; then
    exit 1
fi

sloccount --duplicates --wide --details "$DIR/src/"
