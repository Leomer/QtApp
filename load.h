#ifndef LOAD_H
#define LOAD_H

#include <map>
#include <string>
#include <vector>

extern std::map<std::string, std::string> infoList;
extern std::vector<std::string> progressiveList;

void readInfo();

#endif // LOAD_H
