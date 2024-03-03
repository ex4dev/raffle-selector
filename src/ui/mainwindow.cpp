#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../datastorage.h"
#include <QSqlRecord>
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow), m_storage(nullptr), m_model(nullptr) {
    m_ui->setupUi(this);

    m_storage = new DataStorage();
    m_storage->initializeDatabase();
    m_model = m_storage->makeModel();
    m_ui->tableView->setModel(m_model);

    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_ui->saveButton, &QAbstractButton::clicked, this, &MainWindow::saveEntry);
    connect(m_ui->drawWinnerButton, &QAbstractButton::clicked, this, &MainWindow::drawWinner);
}

void MainWindow::saveEntry() {
    QSqlRecord record = m_model->record();
    record.setValue(QStringLiteral("name"), m_ui->nameLineEdit->text());
    record.setValue(QStringLiteral("contactInfo"), m_ui->contactLineEdit->text());
    record.setValue(QStringLiteral("numTickets"), m_ui->numTicketsSpinBox->value());
    record.setValue(QStringLiteral("comment"), m_ui->commentLineEdit->text());
    m_model->insertRecord(m_model->rowCount(), record);
    m_ui->nameLineEdit->clear();
    m_ui->contactLineEdit->clear();
    m_ui->numTicketsSpinBox->setValue(0);
    m_ui->commentLineEdit->clear();
}

int MainWindow::selectRandomWinner() {
    int sum = 0;
    for (int row = 0; row < m_model->rowCount(); row++) {
        sum += m_model->index(row, 2).data(Qt::DisplayRole).toInt();
    }
    int winningTicket = QRandomGenerator::global()->bounded(sum);
    sum = 0;
    for (int row = 0; row < m_model->rowCount(); row++) {
        sum += m_model->index(row, 2).data(Qt::DisplayRole).toInt();
        if (winningTicket < sum) {
            return row;
        }
    }
    return -1;
}

void MainWindow::drawWinner() {
    const int winner = selectRandomWinner();
    const QString winnerName = m_model->index(winner, 0).data(Qt::DisplayRole).toString();
    const QString winnerContact = m_model->index(winner, 1).data(Qt::DisplayRole).toString();
    QMessageBox::information(this, QStringLiteral("Winner Selected"), winnerName + QStringLiteral("\n") + winnerContact + QStringLiteral("\nRow ") + QString::number(winner + 1));
}

MainWindow::~MainWindow() {
    delete m_ui;
    delete m_storage;
    m_model->deleteLater();
}
