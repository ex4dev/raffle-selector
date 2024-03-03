#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../datastorage.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void saveEntry();
    void drawWinner();

int selectRandomWinner();

private:
    Ui::MainWindow *m_ui;
    DataStorage *m_storage;
    QSqlTableModel *m_model;
};


#endif //MAINWINDOW_H
