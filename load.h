#ifndef LOAD_H
#define LOAD_H

#include <map>
#include <string>
#include <vector>

extern std::map<std::string, std::string> infoList;
extern std::vector<std::string> progressiveList;

void readInfo();
void readPath(char* path, int n);

#endif // LOAD_H
