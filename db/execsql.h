#ifndef EXECSQL_H
#define EXECSQL_H

#include "createDatabase.h"

static QSqlQuery querySql(QSqlDatabase execSqlDB){
    if(!createConnection()){
        qDebug() << "Unable to create databse connection!";
        return(false);
    }
    QSqlQuery execSqlQuery(execSqlDB);
    return execSqlQuery;
}

static bool execSql(QSqlDatabase execSqlDB, QString sql){
    querySql(execSqlDB).exec(sql);
    qDebug() << "Sql command executed!";
    return(true);
}


#endif // EXECSQL_H

