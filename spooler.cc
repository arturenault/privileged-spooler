#include "spooler.h"

using namespace std;

int die(const string& message) {
  if (errno != 0) {
    cerr << strerror(errno) << ": ";
  }
  cerr << message << endl;
  return 1;
}

int AddQueue(const vector<string>& files) { exit(0); }
