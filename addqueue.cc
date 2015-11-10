#include "spooler.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "usage: " << argv[0] << " filename1 filename2 ..." << endl;
    return 1;
  }

  int uid = getuid();

  if (setuid(UID) != 0) {
    cerr << "Unable to set user ID" << endl;
    return 1;
  }

  /* Build vector with filenames */
  vector<string> files(argv + 1, argv + argc);

  AddQueue(uid, files);
}
