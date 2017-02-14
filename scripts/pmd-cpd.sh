#`/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && cd .. && pwd )"

if [ ! -e "${DIR}/scripts/pmd-cpd.sh" ] ; then
    exit 1
fi

gjl_package=pmd
gjl_main="net.sourceforge.pmd.cpd.CPD"
gjl_java_args="-Xmx512m"
source /usr/share/java-config-2/launcher/launcher.bash --minimum-tokens 100 --files "${DIR}/src" --language cpp --skip-duplicate-files --format net.sourceforge.pmd.cpd.XMLRenderer
