#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <vector>

#include "load.h"

std::vector<std::string> games;
std::vector<std::string> display;
std::vector<std::string> progressive;
int rev = 0;

bool duplicate = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    readInfo();

    //ui variables
    QListWidget* gameList = ui->gameList;
    QListWidget* progList = ui->progressiveList;

    //Initialization
    for(const auto& [key, value] : infoList){
        gameList->addItem(key.c_str());
    }

    for(const auto& [key, value] : progressiveList) {
        progList->addItem(key.c_str());
    }

    ui->btnStart->setDisabled(true);

    ui->rbUk->setChecked(true);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_gameList_itemDoubleClicked(QListWidgetItem *item) {

    std::string tmpKey, tmpValue;
    duplicate = false;

    for(const auto& [key, value] : infoList) {
        if(key.c_str() ==  item->text()) {
            tmpKey = key.c_str();
            tmpValue = value.c_str();
            break;
        }
    }


    //Se busca el duplicado de key en el vector games
    if(!games.empty()){
        for(auto& g : games) {
            if(g == tmpKey)
                duplicate = true;
        }
    }

    //Si no existe duplicado se agrega el dato al vector y se reordenara, luego se agregara a la lista
    if(!duplicate) {
        games.emplace_back(tmpKey);
        sort(games.begin(), games.end());

        ui->game->clear();

        for(auto& g : games)
            ui->game->addItem(g.c_str());
    }

    duplicate = false;

    //Se busca el duiplicado de value en el vector Display
    if(!display.empty()){
        for ( auto& d : display) {
            if (d == tmpValue)
                duplicate = true;
        }
    }

    //Si no existe duplicado y no tiene valor 0, se agrega el dato al vector y se reordenara, luego se agregara a la lista
    if(!duplicate and tmpValue != "0") {
        display.emplace_back(tmpValue);
        sort(display.begin(), display.end());

        ui->display->clear();

        for(auto& d : display)
            ui->display->addItem(d.c_str());
    }


    if(!games.empty() and !progressive.empty())
        ui->btnStart->setEnabled(true);
}


void MainWindow::on_progressiveList_itemDoubleClicked(QListWidgetItem *item) {

    std::string tmpKey, tmpValue;
    duplicate = false;

    for(const auto& [key, value] : progressiveList) {
        if(key.c_str() ==  item->text()) {
            tmpKey = key.c_str();
            tmpValue = value.c_str();
            break;
        }
    }

    //Se busca el duplicado de key en el vector progressive
    if(!progressive.empty()) {
        for(auto& prog : progressive) {
            if(prog.c_str() == tmpKey)
                duplicate = true;
        }
    }

    //Si no existe duplicado se agrega el dato al vector y se reordenara, luego se agregara a la lista
    if(!duplicate) {
        progressive.emplace_back(tmpKey);

        sort(progressive.begin(), progressive.end());

        ui->progressive->clear();

        for(auto& prog : progressive) {
            ui->progressive->addItem(prog.c_str());
        }
    }

    duplicate = false;

    //Se busca el duplicado de key en el vector Display
    if(!display.empty()) {
        for(auto& d : display) {
            if(d.c_str() == tmpValue)
                duplicate = true;
        }
    }

    //Si no existe duplicado se agrega el dato al vector y se reordenara, luego se agregara a la lista
    if(!duplicate and tmpValue != "0") {
        display.emplace_back(tmpValue);

        sort(display.begin(), display.end());

        ui->display->clear();

        for(auto& d : display) {
            ui->display->addItem(d.c_str());
        }
    }

    if(!games.empty() and !progressive.empty())
        ui->btnStart->setEnabled(true);
}


void MainWindow::on_game_itemDoubleClicked(QListWidgetItem *item) {

    auto data = item->text();

    for(unsigned int i = 0; i < games.size(); i++) {
        if(data == games[i].c_str()) {
            games.erase(games.begin() + i);
        }
    }

    delete item;
}


void MainWindow::on_display_itemDoubleClicked(QListWidgetItem *item) {
    auto data = item->text();

    for(unsigned int i = 0; i < display.size(); i++) {
        if(data == display[i].c_str()) {
            display.erase(display.begin() + i);
        }
    }

    delete item;
}


void MainWindow::on_progressive_itemDoubleClicked(QListWidgetItem *item) {
    auto data = item->text();

    for(unsigned int i = 0; i < progressive.size(); i++) {
        if(data == progressive[i].c_str()) {
            progressive.erase(progressive.begin() + i);
        }
    }

    delete item;
}

void MainWindow::on_btnClear_clicked() {
    //se limpia los vectores
    games.clear();
    progressive.clear();
    display.clear();

    //Se limpia las listas
    ui->game->clear();
    ui->display->clear();
    ui->progressive->clear();
    ui->lbRev->clear();

    //Deshabilita el boton Start
    ui->btnStart->setDisabled(true);
}

void MainWindow::on_btnStart_clicked() {

    constexpr char path[] = "Document/%s";
    char temp[100];
    char command[100];

    rev = ui->lbRev->text().toInt();

    if (ui->rbTrunk->isChecked()) {

        sprintf(temp, path, "Trunk/MainProject/%s");

        for (auto& g : games) {
            sprintf(command, temp, g.c_str());
            std::cout<<command<<std::endl;
        }

    } else {
        if (ui->rbClass2->isChecked()) {
            sprintf(temp, path, "Branch/ClassII/M");
        }

        if (ui->rbClass3->isChecked()) {
            sprintf(temp, path, "Branch/ClassIII/M");
        }

        if (ui->rbUk->isChecked()) {
            sprintf(temp, path, "Branch/UK/M");
        }

    }

    //std::cout<<path<<std::endl;

    /*for (unsigned int i = 0 ; i < games.size(); i++) {
        for(auto &n : games[i]){
            n = tolower(n);
        }
    }

    for(auto &n : games){
        std::cout<<n<<std::endl;
    }*/
}

