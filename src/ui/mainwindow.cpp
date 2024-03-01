#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../datastorage.h"
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::MainWindow), m_storage(nullptr), m_model(nullptr) {
    m_ui->setupUi(this);

    m_storage = new DataStorage();
    m_storage->initializeDatabase();
    m_model = m_storage->makeModel();
    m_ui->tableView->setModel(m_model);

    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(m_ui->saveButton, &QAbstractButton::clicked, this, &MainWindow::saveEntry);
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

MainWindow::~MainWindow() {
    delete m_ui;
    delete m_storage;
    m_model->deleteLater();
}
