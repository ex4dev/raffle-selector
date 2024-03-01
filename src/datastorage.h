#ifndef DATASTORAGE_H
#define DATASTORAGE_H
#include <QSqlTableModel>
#include <QtSql/QSqlDatabase>

class DataStorage {
public:
    DataStorage();
    void initializeDatabase();

    QSqlTableModel *makeModel(QObject *parent = nullptr);

    ~DataStorage();
private:
    QSqlDatabase m_connection;
}; // DataStorage

#endif //DATASTORAGE_H
