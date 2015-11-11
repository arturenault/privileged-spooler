#include "spooler.h"

using namespace std;
using namespace boost::filesystem;

void log(const string& filename, bool error, const string& message) {
  cout << filename << ": " << (error ? "X " : "Y ") << message << endl;
}

/* Add a series of files to the spooler */
void AddQueue(int uid, const vector<string>& files) {
  if (!exists(path(ROOT_DIR))) {
    create_directory(path(ROOT_DIR));
    permissions(path(ROOT_DIR), no_perms);
  }

  for (auto iter = files.begin(); iter != files.end(); ++iter) {
    AddFile(uid, *iter);
  }
}

/* Add a single file by the given user to the spool */
void AddFile(int uid, const string& filename) {
  long unique_id = GetUniqueId();
  string internal_filename =
      ROOT_DIR "/" + to_string(uid) + "-" + to_string(unique_id);

  bool error = false;
  string message;

  seteuid(uid);
  ifstream external_file(filename);
  if (external_file.fail()) {
    external_file.close();
    message = "file cannot be opened";
    error = true;
    setuid(0);
  } else {
    setuid(0);
    ofstream internal_file(internal_filename);

    internal_file << external_file.rdbuf();
    internal_file.close();

    permissions(path(internal_filename), no_perms);
  }

  log(filename, error, message);
}

/* Remove a series of files from the spooler */
void RmQueue(int uid, const vector<string>& files) {
  for (auto iter = files.begin(); iter != files.end(); ++iter) {
    RmFile(uid, *iter);
  }
}

void RmFile(int uid, const string& filename) {
  stringstream internal_filename;
  internal_filename << ROOT_DIR "/" << uid << "-" << filename;

  path file_path(internal_filename.str());

  string message;
  bool error = false;

  if (!remove(file_path)) {
    message = "file does not exist or does not belong to user";
    error = true;
  }

  log(filename, error, message);
}

bool CompareByTime(path lhs, path rhs) {
  if (difftime(last_write_time(lhs), last_write_time(rhs)) > 0)
    return false;
  else
    return true;
}

void ShowQueue() {
  path root_dir(ROOT_DIR);

  if (!exists(root_dir)) return;

  directory_iterator end_iter;

  vector<path> paths;

  for (directory_iterator iter(root_dir); iter != end_iter; ++iter) {
    paths.push_back(iter->path());
  }

  sort(paths.begin(), paths.end(), &CompareByTime);

  for (auto iter = paths.begin(); iter != paths.end(); ++iter) {
    path filepath = *iter;
    if (filepath.filename() != UNIQUE_ID_FILE) {
      stringstream filename(filepath.filename().string());
      string user_id;
      string unique_id;

      getline(filename, user_id, '-');
      getline(filename, unique_id);

      char time_buf[17];
      time_t last_modified_time = last_write_time(filepath);
      strftime(time_buf, sizeof(time_buf), "%Y-%m-%d_%H:%M",
               localtime(&last_modified_time));

      cout << filepath.filename().string() << ' ';
      cout << user_id << ' ';
      cout << time_buf << ' ';
      cout << unique_id << endl;
    }
  }
}

/* Get a unique ID for the next added file to use;
 * Needs to be stored in a file in the spooler directory so it can be kept
 * across executions */
long GetUniqueId() {
  string unique_id_filename(ROOT_DIR "/" UNIQUE_ID_FILE);
  ifstream unique_id_infile(unique_id_filename, ios::binary);

  long last_unique_id, unique_id;

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
