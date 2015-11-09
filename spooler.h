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

bool error(const std::string& message);

bool AddQueue(int uid, const vector<string>& files);

bool ShowQueue();

bool RmQueue(int uid, const vector<string>& files);

int AddFile(int uid, const string& filename);

int RmFile(int uid, const string& filename);

int GetUniqueId();

#endif
