#include "spooler.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    return die("At least two command line arguments needed");

  } else if (setuid(0) != 0) {
    return die("Unable to set user ID");

  } else {
    /* Build vector with filenames */
    vector<string> files(argv + 1, argv + argc);

    AddQueue(files);
  }
}
