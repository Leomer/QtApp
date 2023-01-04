#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include "load.h"
#include <vector>

std::vector<std::string> games;
std::vector<std::string> display;
std::vector<std::string> progressive;

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

    for(auto &i : progressiveList) {
        progList->addItem(i.c_str());
    }
}

MainWindow::~MainWindow() {
    delete ui;

    for(auto &n : games){
        std::cout<<n<<std::endl;
    }

    for(auto &n : display){
        std::cout<<n<<std::endl;
    }

    for(auto &n : progressive){
        std::cout<<n<<std::endl;
    }
}


void MainWindow::on_gameList_itemDoubleClicked(QListWidgetItem *item) {

    auto data = item->text();
    duplicate = false;

    for(const auto& [key, value] : infoList) {
        if(key.c_str() !=  data)
            continue;

        //Se busca el duplicado de key en el vector games
        if(!games.empty()){
            for( auto& g : games) {
                if(key.c_str() == g)
                    duplicate = true;
            }
        }

        //Si no existe duplicado se agrega el dato al vector y se reordenara, luego se agregara a la lista
        if(!duplicate) {
            games.emplace_back(data.toStdString());
            sort(games.begin(), games.end());

            ui->game->clear();

            for(auto& g : games)
                ui->game->addItem(g.c_str());
        }

        duplicate = false;

        //Se busca el duiplicado de value en el vector Display
        if(!display.empty()){
            for ( auto& d : display) {
                if (value.c_str() == d)
                    duplicate = true;
            }
        }

        //Si no existe duplicado y no tiene valor 0, se agrega el dato al vector y se reordenara, luego se agregara a la lista
        if(!duplicate and value != "0") {
            display.emplace_back(value.c_str());
            sort(display.begin(), display.end());

            ui->display->clear();

            for(auto& d : display)
                ui->display->addItem(d.c_str());
        }
    }
}


void MainWindow::on_progressiveList_itemDoubleClicked(QListWidgetItem *item) {

    auto data = item->text();
    duplicate = false;

    if(!progressive.empty()) {
        for(auto& prog : progressive) {
            if(prog.c_str() == data)
                duplicate = true;
        }
    }

    if(!duplicate) {
        progressive.emplace_back(data.toStdString());

        sort(progressive.begin(), progressive.end());

        ui->progressive->clear();

        for(auto& prog : progressive) {
            ui->progressive->addItem(prog.c_str());
        }
    }
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
}
