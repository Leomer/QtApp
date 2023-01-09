#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gameList_itemDoubleClicked(QListWidgetItem *item);

    void on_progressiveList_itemDoubleClicked(QListWidgetItem *item);

    void on_game_itemDoubleClicked(QListWidgetItem *item);

    void on_display_itemDoubleClicked(QListWidgetItem *item);

    void on_progressive_itemDoubleClicked(QListWidgetItem *item);

    void on_btnClear_clicked();

    void on_btnStart_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
