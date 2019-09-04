#ifndef MSGPACK_H
#define MSGPACK_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <string.h>

class MsgPack : public QObject
{
    Q_OBJECT

private:
    QString msgKind;
    QStringList dataList;

public:
    MsgPack(QString str);
    QString toString();
    QString getMsgKind();
    QStringList getDataList();
    QString getDataAt(int count);
    void debug();
};

#endif // MSGPACK_H
