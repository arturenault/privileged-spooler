#ifndef __SPOOLER_H__
#define __SPOOLER_H__

#define UID 0
#define ROOT_DIR "/spooler"
#define UNIQUE_ID_FILE "last_unique_id"

#include <boost/filesystem.hpp>
#include <ctime>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

using namespace std;

bool exists(const std::string& filename);

int error(const std::string& message);

int AddQueue(int uid, const vector<string>& files);

int ShowQueue();

int AddFile(int uid, const string& filename);

int GetUniqueId();

#endif
