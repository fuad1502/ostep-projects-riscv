#! /bin/bash
if ! [[ -d $XV6_DIR ]]; then
    echo "The src/ dir does not exist."
    echo "Your xv6 code should be in the src/ directory"
    echo "to enable the automatic tester to work."
    exit 1
fi

../tester/run-tests.sh $*


