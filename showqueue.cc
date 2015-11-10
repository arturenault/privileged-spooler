#include "spooler.h"

int main(int argc, char** argv) {
  if (setuid(UID) != 0) {
    cerr << "Unable to set user id" << endl;
    return 1;
  }

  ShowQueue();
}
