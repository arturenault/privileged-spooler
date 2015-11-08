#include "spooler.h"

using namespace std;

int error(const string& message) {
  if (errno != 0) {
    cerr << strerror(errno) << ": ";
  }
  cerr << message << endl;
  return 1;
}

bool exists(const std::string& filename) {
  struct stat buf;
  return (stat(filename.c_str(), &buf) == 0);
}

/* Add a series of files to the spooler */
int AddQueue(int uid, const vector<string>& files) {
  if (!exists(ROOT_DIR)) {
    mkdir(ROOT_DIR, 700);
  }

  for(auto iter = files.begin(); iter != files.end(); ++iter) {
    AddFile(uid, *iter);
  }

  return 0;
}

/* Get a unique ID for the next added file to use;
 * Needs to be stored in a file in the spooler directory so it can be kept
 * across executions */ 
int GetUniqueId() {
  ifstream unique_id_infile(ROOT_DIR "/last_unique_id", ios::binary);
  
  int last_unique_id, unique_id;

  if (unique_id_infile.fail()) {
    last_unique_id = 0;
  } else {
    unique_id_infile.read(reinterpret_cast<char *>(&last_unique_id), sizeof(last_unique_id)); 
    cout << "read from file: ";
  }
  cout << last_unique_id << endl;
  unique_id_infile.close();

  unique_id = last_unique_id + 1;

  ofstream unique_id_outfile(ROOT_DIR "/last_unique_id", ios::binary);
  unique_id_outfile.write(reinterpret_cast<const char *>(&unique_id), sizeof(unique_id));
  unique_id_outfile.close();

  return unique_id;
}


/* Add a single file by the given user to the spool */
int AddFile(int uid, const string& filename) {
  int unique_id = GetUniqueId();
  string internal_filename = to_string(uid) + "-" + to_string(unique_id);

  ifstream external_file(filename);
  if (external_file.fail()) {
    external_file.close();
    return error("File " + filename + " cannot be read");
  }
  
  ofstream internal_file(ROOT_DIR "/" + internal_filename);

  internal_file << external_file.rdbuf();

  return 0;
}
