README
Artur Upton Renault
COMS W4187 hw2

INSTALLATION
This program uses make to install. Almost all targets need to be run with sudo
to function properly.

make compile
Compiles the program and creates three executables (addqueue, showqueue, and
rmqueue).

make build (default)
runs make compile, and then moves executables to PATH.

make clean
removes object files and executables

make all
runs clean followed by build

LIBRARIES
This program uses the Boost Filesystem library. It was installed on the vm using
apt-get libboost-all-dev, and is therefore not included in the submission.

EXECUTION

make test
This runs all tests in the tests/ directory. Assumes make build has already been run (does not run build automatically since build requires sudo).

ARG="files" make exec
Assumes args contains a list of files containing a sequence of commands. Also assumes that make build has already been run.

addqueue <filename1> <filename2> ...
Adds the files pointed by the filenames to the queue. If one file is not found, the
other files are still added.

rmqueue <unique_id1> <unique_id2> ...
Removes the files pointed to by the filenames to the queue. Will not remove
files that don't belong to the user. If one file fails, the others will still be
removed.

showqueue
Prints the contents of the queue in the following format:
internal_file_name    uid    date_time_added    unique_identifier
