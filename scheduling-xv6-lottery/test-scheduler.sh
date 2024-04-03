export XV6_DIR=~/code/hacked-xv6-riscv
export OSTEP_PROJECTS_DIR=~/code/ostep-projects-riscv
chmod +x ./tests/pre
chmod +x ./tests/run
./tests/pre
./tests/run > tests/scheduler-log.txt
cd tests
python3 ./plot.py
