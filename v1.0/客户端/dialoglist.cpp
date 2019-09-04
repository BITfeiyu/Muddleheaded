#include "dialoglist.h"
#include "ui_dialoglist.h"
#include "headers.h"
#include <QToolButton>
#include "widget.h"
#include <QMessageBox>


DialogList::DialogList(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    setWindowTitle("IM");//设置标题；
    setWindowIcon(QPixmap(":/imags/qq.png"));//设置图标

    int length = allUserInfo.length() / 3;

    QList<QString> namelist;
    for(int i = 0; i < length;i++){
        namelist << allUserInfo.at(i * 3);
    }
    QStringList iconNameList; //图标资源
    iconNameList <<"dr"<<"Cherry"<<"spqy"<<"wy"<<"ymrl"<<"lswh"<<"qmnn"<<"qq"<<"jj";


    QVector<QToolButton * > vToolbtn;//创建容器
    for(int i=0; i < length; i++)
    {
        QToolButton * btn = new QToolButton;//设置图像
        btn->setFixedSize(290, 80);
        btn->setText(namelist[i]);//设置名称
        QString str =QString(":/images/%1.png").arg(iconNameList.at(i));
        btn->setIcon(QPixmap(str));//设置图片
        btn->setIconSize(QPixmap(str).size());//设置头像大小
        btn->setAutoRaise(true);//设置按钮风格
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//文字图片一起显示
        ui->VLayout->addWidget(btn);//加入垂直布局
        vToolbtn.push_back(btn);//容器保存
        isShow.push_back(false);
     }
    ui->VLayout->addStretch();
    //添加信号槽连接
    for(int i = 0; i < vToolbtn.size(); i++ )
    {
       connect(vToolbtn[i], &QToolButton::clicked,[=](){
            if(isShow[i])
            {
                QString str = QString("%1窗口已经打开").arg(vToolbtn[i] -> text());
                QMessageBox::warning(this,"警告",str);
                return;
            }
            isShow[i] = true;
            Widget *widget = new Widget(0,vToolbtn[i] -> text());
            widget -> setWindowTitle(vToolbtn[i] -> text());
            widget -> setWindowIcon(vToolbtn[i] -> icon());
            //this->close();
            widget->exec();

            connect(widget,&Widget::closeWidget,[=](){
                isShow[i] =false;
          });

        }); //弹出对话框
    }

   }

DialogList::~DialogList()
{
    delete ui;
}
