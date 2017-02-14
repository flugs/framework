#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )"

if [ ! -e "$DIR/scripts/codingstyle.sh" ] ; then
    exit 1
fi

echo "Applying clang-format..."
find "$DIR/src" \( -iname "*.h" -or -iname "*.c" -or -iname "*.cpp" -or -iname "*.hpp" \) -exec clang-format -style=file -i {} \;

