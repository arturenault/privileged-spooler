#include "spooler.h"

int main(int argc, char** argv) {
  if (argc < 2) return error("At least two command line arguments needed");

  int uid = getuid();

  if (setuid(UID) != 0) return error("Unable to set user ID");

  /* Build vector with filenames */
  vector<string> files(argv + 1, argv + argc);

  AddQueue(uid, files);
}
