#include "spooler.h"

using namespace std;
using namespace boost::filesystem;

int error(const string& message) {
  cerr << message << endl;
  if (errno != 0) {
    cerr <<  ": " << strerror(errno);
  }
  cerr << endl;
  return 1;
}

/* Add a series of files to the spooler */
int AddQueue(int uid, const vector<string>& files) {
  if (!exists(path(ROOT_DIR))) {
    create_directory(path(ROOT_DIR));
    permissions(path(ROOT_DIR), no_perms);
  }

  for (auto iter = files.begin(); iter != files.end(); ++iter) {
    AddFile(uid, *iter);
  }

  return 0;
}

/* Add a single file by the given user to the spool */
int AddFile(int uid, const string& filename) {
  int unique_id = GetUniqueId();
  string internal_filename =
      ROOT_DIR "/" + to_string(uid) + "-" + to_string(unique_id);

  ifstream external_file(filename);
  if (external_file.fail()) {
    external_file.close();
    return error(filename);
  }

  ofstream internal_file(internal_filename);

  internal_file << external_file.rdbuf();
  internal_file.close();

  permissions(path(internal_filename), no_perms);

  return 0;
}

/* Remove a series of files from the spooler */
int RmQueue(int uid, const vector<string>& files) {
  if (!exists(path(ROOT_DIR))) {
    return error("Cannot read spooler");
  }

  for (auto iter = files.begin(); iter != files.end(); ++iter) {
    RmFile(uid, *iter);
  }

  return 0;
}

int RmFile(int uid, const string& filename) {
  stringstream internal_filename;
  internal_filename << ROOT_DIR "/" << uid << "-" << filename;

  path file_path(internal_filename.str());

  if (!remove(file_path)) {
    return error(filename);
  }

  return 0;
}

int ShowQueue() {
  path root_dir(ROOT_DIR);

  if (!exists(root_dir)) return 0;

  directory_iterator end_iter;

  for (directory_iterator iter(root_dir); iter != end_iter; ++iter) {
    path filepath = iter->path();
    if (filepath.filename() != UNIQUE_ID_FILE) {
      stringstream filename(filepath.filename().string());
      string user_id;
      string unique_id;

      getline(filename, user_id, '-');
      getline(filename, unique_id);

      time_t last_modified_time = last_write_time(filepath);
      string last_modified_string(ctime(&last_modified_time));
      int pos = last_modified_string.find_last_not_of("\n") + 1;
      last_modified_string.erase(pos);

      cout << filepath.filename().string() << '\t';
      cout << user_id << '\t';
      cout << last_modified_string << '\t';
      cout << unique_id << endl;
    }
  }
  return 0;
}

/* Get a unique ID for the next added file to use;
 * Needs to be stored in a file in the spooler directory so it can be kept
 * across executions */
int GetUniqueId() {
  string unique_id_filename(ROOT_DIR "/" UNIQUE_ID_FILE);
  ifstream unique_id_infile(unique_id_filename, ios::binary);

  int last_unique_id, unique_id;

  if (unique_id_infile.fail()) {
    last_unique_id = 0;
  } else {
    unique_id_infile.read(reinterpret_cast<char*>(&last_unique_id),
                          sizeof(last_unique_id));
  }
  unique_id_infile.close();

  unique_id = last_unique_id + 1;

  ofstream unique_id_outfile(ROOT_DIR "/last_unique_id", ios::binary);
  unique_id_outfile.write(reinterpret_cast<const char*>(&unique_id),
                          sizeof(unique_id));
  unique_id_outfile.close();

  permissions(path(unique_id_filename), no_perms);
  return unique_id;
}
