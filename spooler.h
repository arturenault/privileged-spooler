#ifndef __SPOOLER_H__
#define __SPOOLER_H__

#define UID 0
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

void log(const string& filename, bool error, const string& message);

void AddQueue(int uid, const vector<string>& files);

void ShowQueue();

void RmQueue(int uid, const vector<string>& files);

void AddFile(int uid, const string& filename);

void RmFile(int uid, const string& filename);

int GetUniqueId();

#endif
