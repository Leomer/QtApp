#include "load.h"
#include "Tinyxml2/tinyxml2.h"
#include <iostream>

std::map<std::string, std::string> infoList;
std::vector<std::string> progressiveList;

void readInfo() {
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile("Info.xml");

    if(result != tinyxml2::XML_SUCCESS) {
        std::cout<<"Archivo no existe\n";
        return;
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement("Games")->FirstChildElement("Game");

    for ( ; root != NULL ; root = root->NextSiblingElement()) {
        std::string key = root->Attribute("id");
        std::string value = root->FirstChildElement("Display")->GetText();

        infoList.insert(std::pair<std::string, std::string>(key,value));
    }

    root = doc.FirstChildElement("Progressive")->FirstChildElement("Prog");

    for( ; root != NULL ;root = root->NextSiblingElement()){
        std::string prog = root->GetText();
        progressiveList.emplace_back(prog);
    }

    doc.Clear();
}
