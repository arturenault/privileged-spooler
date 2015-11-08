#include "spooler.h"

int main(int argc, char** argv) {
  if (setuid(UID) != 0) return error("Unable to set user ID");

  return ShowQueue();
}
