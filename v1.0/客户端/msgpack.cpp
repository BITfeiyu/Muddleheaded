#include "msgpack.h"
#include "headers.h"

QString MsgPack::getMsgKind()
{
    return this->msgKind;
}

QStringList MsgPack::getDataList()
{
    return this->dataList;
}

MsgPack::MsgPack(QString msgStr)
{
    QStringList ls= msgStr.split("#");
    this->msgKind = ls.first();
    ls.removeFirst();
    this->dataList = ls;
}

QString MsgPack::toString()
{
    QString msgStr;
    msgStr = this->msgKind;
    for(int i = 0; i < this->dataList.size(); i++){
        msgStr.append("#").append(this->dataList.at(i));
    }
    return msgStr;
}

void MsgPack::debug()
{
    qDebug() << "msgKind:" << msgKind;
    for(int i = 0; i < this->dataList.size(); i++){
        qDebug() << "msgData" << i << this->dataList.at(i);
    }
}

QString MsgPack::getDataAt(int count)
{
    return dataList.at(count);
}

