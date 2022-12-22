# Accept the argument and store it in a variable
argument=$1

# Use the argument in place of the hard-coded value
$argument > ./leaks_locater/program_file && make -s --directory=leaks_locater run && rm -rf  ./leaks_locater/my_malloc.o  ./leaks_locater/program_file  ./leaks_locater/ALLOCATER  ./leaks_locater/allocation_log