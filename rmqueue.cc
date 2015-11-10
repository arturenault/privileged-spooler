#include "spooler.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "usage: " << argv[0] << " unique_id1 unique_id2 ...";
    return 1;
  }

  int uid = getuid();

  if (setuid(UID) != 0) {
    cerr << "Cannot set userid" << endl;
    return 1;
  }

  /* Build vector with filenames */
  vector<string> files(argv + 1, argv + argc);

  RmQueue(uid, files);
}
