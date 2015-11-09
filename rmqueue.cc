#include "spooler.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    stringstream stream;
    stream << "usage: " << argv[0] << "filename1 filename2 ...";
    return error(stream.str());
  }

  int uid = getuid();

  if (setuid(UID) != 0) return error("Unable to set user ID");

  /* Build vector with filenames */
  vector<string> files(argv + 1, argv + argc);

  return RmQueue(uid, files);
}
