#include "datastorage.h"

#include <iostream>
#include <QDir>
#include <QStandardPaths>
#include <QSqlQuery>

DataStorage::DataStorage() {
    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (!dataDir.mkpath(QStringLiteral("."))) {
        std::cout << "Failed to make path." << std::endl;
        exit(0);
    }
    QString path = dataDir.filePath("raffle.db");
    std::cout << path.toStdString() << std::endl;
    m_connection = QSqlDatabase::addDatabase("QSQLITE");
    m_connection.setDatabaseName(path);
    m_connection.open();
}

DataStorage::~DataStorage() {
    m_connection.close();
}

void DataStorage::initializeDatabase() {
    QSqlQuery query(QStringLiteral("create table `entries` (`name` VARCHAR(255) not null,`contactInfo` VARCHAR(255) not null,`numTickets` MEDIUMINT not null default 1,`comment` varchar(255) null)"), m_connection);
    query.exec();
}

QSqlTableModel *DataStorage::makeModel(QObject *parent) {
    QSqlTableModel *model = new QSqlTableModel(parent, m_connection);
    model->setTable("entries");
    model->select();
    return model;
}
