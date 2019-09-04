#include "dialoglist.h"
#include "ui_dialoglist.h"
#include <QToolButton>
#include "chat.h"
#include <QMessageBox>


DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    setWindowTitle("IM");//设置标题；
    setWindowIcon(QPixmap(":/imags/qq.png"));//设置图标


    QList<QString> namelist;
    namelist <<"friend_1       IP address"<<"friend_2       IP address"<<"friend_3       IP address"<<"friend_4       IP address"<<"friend_5       IP address"<<"friend_6       IP address"<<"friend_7       IP address"<<"friend_8       IP address"<<"friend_9       IP address";

    QStringList iconNameList; //图标资源
    iconNameList <<"dr"<<"Cherry"<<"spqy"<<"wy"<<"ymrl"<<"lswh"<<"qmnn"<<"qq"<<"jj";


    QVector<QToolButton * > vToolbtn;//创建容器
    for(int i=0; i<9; i++)
    {
        QToolButton * btn = new QToolButton;//设置图像
        btn->setText(namelist[i]);//设置名称
        QString str =QString(":/images/%1.png").arg(iconNameList.at(i));
        btn->setIcon(QPixmap(str));//设置图片
        btn->setIconSize(QPixmap(str).size());//设置头像大小
        btn->setAutoRaise(true);//设置按钮风格
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//文字图片一起显示
        ui->VLayout->addWidget(btn);//加入垂直布局
        vToolbtn.push_back(btn);//容器保存
        //isShow.push_back(false);
        //添加信号槽连接
        for(int i = 0; i < vToolbtn.size(); i++ )
        {
           connect(vToolbtn[i], &QToolButton::clicked,[=](){
                /*if(isShow[i])
                {
                    QString str = QString("%1窗口已经打开").arg(vToolbtn[i] -> text());
                    QMessageBox::warning(this,"警告",str);
                    return;
                }
                isShow[i] = true;*/
                Chat *chat = new Chat(0,vToolbtn[i] -> text());
                chat -> setWindowTitle(vToolbtn[i] -> text());
                chat -> setWindowIcon(vToolbtn[i] -> icon());
                chat -> show();

                /*connect(chat,&Chat::closeWidget,[=](){
                    isShow[i] =false;
              });*/

            }); //弹出对话框
        }

    }
}

DialogList::~DialogList()
{
    delete ui;
}
