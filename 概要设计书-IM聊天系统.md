项目名称：IM聊天系统              
                          


 
__修 改 履 历__

| 修改编号	| 日期	| 修改人 |	版本号	| 修改内容 |
| -- | -- | -- | -- | -- |
| 1 |	8-30	| 申志宇	| 0.1 |	创建| 
| 2 |	8-30	| 吕相洋	| 0.2 |	修改| 
				
- [1	文档概述](#1文档概述)
	- [1.1	文档目的和范围](#11文档目的和范围)
	- [1.2	术语/缩略语](#12术语缩略语)
	- [1.3	参考文档](#13参考文档)
- [2	系统结构图](#2系统结构图)
- [3	模块概述](#3模块概述)
	- [3.1	模块功能定义](#31模块功能定义)
	- [3.2	模块结构](#32模块结构)
- [4    接口说明](#4接口说明)
	- [4.1	数据结构定义](#41数据结构定义)
	- [4.2	函数](#42函数)
		- [4.2.1	模块间接口函数](#421模块间接口函数)
		- [4.2.2	模块内接口函数](#422模块内接口函数)


-- - - -

# 1	文档概述    
## 1.1	文档目的和范围    
作为详细设计与程序设计的参考依据。
## 1.2	术语/缩略语    
| 序号	| 术语/缩略语 |	说明 |
| -- | -- | -- |
| 1 |	Qt |	Qt 是一种函数库是用来帮助制作图形交互界面的。|
| 2 |	Socket |	Socket 又称"套接字"，应用程序通常通过"套接字"向网络发出请求或者应答网络请求。|
| 3 |	MySQL	| MySQL   是一种关系数据库管理系统，关系数据库将数据保存在不同的表中。 |

## 1.3	参考文档    
|序号 |	文档名 |	作者 |	时间 |	版本 |
| -- | -- | -- | -- | -- |
| 1 |	概要设计模板.doc |	东软集团股份有限公司 |	2009.11.9 |	0.8.0-0.0.0 |
				

# 2	系统结构图    

![图片加载失败](https://note.youdao.com/yws/public/resource/9faf8ac862dc0c66e6ed286097c5bd8b/xmlnote/238B11FCF5114566AEB369AAAFD9772C/1194)



# 3	模块概述    
## 3.1	模块功能定义       

| 序号 |	模块 |	功能点 |	功能点详细内容 |
| -- | -- | -- | -- |
| 1 |	登陆模块 |	校验用户输入字符串 | 验证用户输入的帐号密码是否合法 |
| 2 |	|传送数据到服务端 | 将用户填写的数据从客户端提交到服务端 |
| 3 |	|返回匹配结果 | 返回结果：0,1,2,3。0表示成功；1表示用户名不存在；2表示密码错误；3表示已经登录。 |
| 4 | 	注册模块 |	校验用户输入字符串 |	验证用户输入的注册内容是否合法 |
| 5 |	|传送数据到服务端 |	将用户填写内容客户端提交到服务端 |
| 6 |	|验证注册ID |	如果用户ID已经被注册，则不允许注册，提示用户改变ID |
| 7 |	|存储到数据库 |	如果允许注册，则存储入数据库，返回注册成功 |
| 8 |	联系人模块 |	添加好友 |	用户输入ID，将添加好友请求发送给数据库验证，如果好友ID存在，向好友ID发送好友申请，如果好友ID不存在，提示用户好友不存在 |
| 9 |	|删除好友|在弹出菜单中可以删除好友，客户端将删除好友请求发送给数据库 |
| 10 |	|更改昵称 |	将用户修改的昵称上传到数据库 |
| 11 |	|进入聊天界面 |	点击好友，弹出与该好友的聊天界面 |
| 12 |	聊天模块|发送消息 |	客户端将消息、用户信息发给服务器，第一次与好友ip建立连接 |
| 14 |	|接收消息 |	服务器接收消息后将数据包转发给聊天对象 |
| 15 |	|显示用户信息 |	显示用户和聊天对象的ID、昵称和IP地址 |
| 16 |	|添加附件 |	从本地选中附件内容，向服务器发送附件 |


## 3.2	模块结构    
画图或列表说明各个模块的组成结构(可以使用中文描述或函数名)。

| 模块名称 |	模块类型 |	概要说明 |
| -- | -- | -- |
| 登陆注册界面 |	外部模块 |	
| 消息列表界面 |	外部模块 |	
| 聊天界面 |	外部模块  | 	
| 好友列表界面	| 外部模块	| 
| 聊天历史记录	| 外部模块	| 
| 个人信息	| 外部模块	| 
| 好友信息	| 外部模块 | 	
| 数据库模块	| 内部模块	| 数据库底层函数设计 | 
| Socket模块	| 内部模块 | 	数据传输函数设计 | 
 
# 4	接口说明    
## 4.1	数据结构定义    
给出模块所用数据结构的说明，以及全局变量和宏常量。
```php
typedef strcut userInfo
{
	char userID[25];//用户ID
	char userIP[25];//用户IP地址
	char nickName[50];//昵称,默认为字符串（“新用户”）
	char passwd[16];//密码
	int  iState;//登录状态
	char iconHead[500];//用户头像在数据库中的地址
	vector<user*> *friendList;//指向用户好友列表的指针
}user;
    typedef strcut messageHead
{
	char messageID[25];//消息标识ID
	char senderID[25];//发送用户ID
	char recverID[25];//接收用户ID
	char messageTitle[50];//消息标题
	char messageTime[50];//消息发送时间戳
	bool isFile;//发送消息是否为文件类型，默认值为false
	union messageSize{
		int length;//若isFile == false代表字符串长度
		double fileSize;//若ifFile == true 代表文件大小，以KB为单位
	}
msBody *messageBody;//指向消息内容的指针
}msHead;

typedef struct messageBody
{
	msHead *messageHead;//指向消息标题的指针
	bool isFile; //发送消息是否为文件类型，默认值为false
	union data{
		char[500] messageContent;//发送消息的内容
		char[50] fileAddress;//发送文件在数据库中的暂存地址
	}
}
}msBody;

```
![](https://note.youdao.com/yws/public/resource/9faf8ac862dc0c66e6ed286097c5bd8b/xmlnote/6DFF06F7FDE44946A97605ED28A2CF50/1238)

## 4.2	函数    
###  4.2.1	模块间接口函数    
#### 4.2.1.1	Send    
| 接口函数 | send |
| -- | -- |
| 函数名	| Send | 
| 功能概要	| 发送消息 | 
| 记述形式	| int Send (int socket_fd ,char* pcBuffer)

参数
| 类型	| 变量名	| I/O	| 说明 | 
| -- | -- | -- | -- |
| int	| socket_fd	| I	| 套接字标示符 | 
| char*	| pcBuffer	| I	| 缓冲区 | 
| 返回值|类型	|  Int	|  说明 | 
| 		| 值 | 0	| 发送成功；
| | | 1	| 发送失败 | 

#### 4.2.1.2	Receive    
| 接口函数 | Receive |
| -- | -- |
| 函数名	| Receive | 
| 功能概要	| 接收消息 | 
| 记述形式	| int Receive (int socket_fd ,char* pcBuffer) | 

参数
| 类型	| 变量名	| I/O	| 说明 | 
| -- | -- | -- | -- |
| int	| socket_fd	| I	| 套接字标示符 | 
| char*	| pcBuffer	| I	| 缓冲区 | 
| 返回值|类型	|  Int	|  说明 |
| 	 |值    |  	0	| 接收成功
| | | 1 | 	接收失败 | 

### 4.2.2	模块内接口函数    
#### 4.2.2.1	CheckLoginInput    
| 接口函数 | CheckLoginInput |
| -- | -- |
| 函数名	| CheckLoginInput | 
| 功能概要	| 检查用户输入的账号密码时候是否合法（客户端，模块内） | 
| 记述形式	| int CheckLoginInput (char *pcUserID, char* pcPasswd) | 
参数
| 类型	| 变量名	| I/O	| 说明 | 
| -- | -- | -- | -- |
| char*	| pcUserID	| I	| 账户 | 
| char*	| pcPasswd	| I	| 密码 | 
| 返回值|类型	|  Int	|  说明 |
| 	 |值 | 	0	| 输入合法 | 
| | | 		1	| 账户含有非法字符 | 
| | | 		2	| 密码不合法(长度或非法字符) | 

#### 4.2.2.2	CheckRegisterInput   
| 接口函数 | CheckRegisterInput |
| -- | -- | 
| 函数名	| CheckRegisterInput | 
| 功能概要	 | 检查用户输入注册信息是否正确（客户端，模块内） | 
| 记述形式	| int CheckRegisterInput (tagUSER_t *registerInfo) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- |
| tagUSER_t *	| registerInfo | 	I	| 用户注册的信息 | 
| 返回值|类型	|  Int	|  说明 | 
| 		|值 	| 0| 输入全部合法 | 
| | 			| 1| 注册信息不合法 | 

#### 4.2.2.3	CheckUserIdExist    
| 接口函数 | CheckUserIdExist |
| -- | -- | 
| 函数名	| CheckUserIdExist | 
| 功能概要	 | 调用socket函数判断是用户名是否存在（客户端，模块内） | 
| 记述形式	| int CheckUserIdExist (char *pcUserId)) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- |
| char*	| pcUserId | 	I	| 用户ID | 
| 返回值|类型	|  Int	|  说明 |
| 		| 值	|0 | 已经被注册 | 
| | 			|1 | 未被注册 | 

#### 4.2.2.4	GetMessage    
| 接口函数 | GetMessage |
| -- | -- | 
| 函数名	| GetMessage | 
| 功能概要	 | 获取未读消息信息 | 
| 记述形式	| Int GetMessage(stInform * pstMessage) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- |
| stInform *	| pstMessage | 	o	| 新消息信息 | 
| 返回值|类型	|  Int	|  说明 |
| 	| 值	|0 | 获取成功 | 
| | 		|1 | 无新消息 | 
| | 		|2| 通信失败 | 

#### 4.2.2.5	SendMessage   
| 接口函数 | SendMessage |
| -- | -- | 
| 函数名	| SendMessage| 
| 功能概要	 | 发送消息 | 
| 记述形式	| IntSendMali(char*pcUid,char*pcToUid,char*pcContent,char*pcAttach,int iSendType) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- |
| char*	| pcUid | 	i	| 发件者id | 
| char*	| pcToUid | 	i	| 接收者id | 
| char*	| pcContent | 	i	| 发件者id | 
| char*	| pcUid | 	i	| 消息内容 | 
| char*	| pcAttach | 	i	| 附件路径 | 
| int	| iSendType | 	i	| 发送方式 | 
| 返回值|类型	|  Int	|  说明 |
| 	| 值	| 0| 发送成功 | 
| | 		|1 | 发送失败 | 

#### 4.2.2.6	AddContact     
| 接口函数 | AddContact |
| -- | -- | 
| 函数名	| AddContact | 
| 功能概要	 | 添加联系人 | 
| 记述形式	| Int AddContact (char* pcUserId,char* pcContactId) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| char*	| pcUserId | 	i	| 用户id | 
| char*	| pcContactId | 	i	| 联系人id | 
| 返回值类型	| int | | 	说明 | 
| 	值	| 0	| | 添加成功 | 
| | 		1	| | 添加失败 | 

#### 4.2.2.7	DeleteContact    

| 接口函数 | DeleteContact |
| -- | -- | 
| 函数名	| DeleteContact | 
| 功能概要	 | 删除好友 | 
| 记述形式	| Int DeleteContact (char* pcUserId,char* pcContactId) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| char*	| pcUserId | 	i	| 用户id | 
| char*	| pcContactId | 	i	| 联系人id | 
| 返回值类型	| int | | 	说明 | 
| 	值	| 0	| | 删除成功 | 
| | 		1	| | 删除失败 | 

#### 4.2.2.8	OpenMysql     

| 接口函数 | OpenMysql |
| -- | -- | 
| 函数名	| OpenMysql | 
| 功能概要	 | 打开与数据库连接（服务端） | 
| 记述形式	| int OpenMysql () | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| 返回值类型	| int | | 	说明 | 
| 	值	| 0	| | 打开数据库成功 | 
| | 		1	| | 打开数据库失败 | 

#### 4.2.2.9	CloseMysql    

| 接口函数 | CloseMysql |
| -- | -- | 
| 函数名	| CloseMysql | 
| 功能概要	 | 关闭与数据库连接（服务端） | 
| 记述形式	| int CloseMysql () | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| 返回值类型	| int | | 	说明 | 
| 	值	| 0	| | 关闭数据库成功 | 
| | 		1	| | 关闭数据库失败 | 
			
#### 4.2.2.10	ExecSql   

| 接口函数 | ExecSql |
| -- | -- | 
| 函数名	| ExecSql | 
| 功能概要	 | 执行sql语句(服务端) | 
| 记述形式	| int ExecSql (char *sqltext) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| char * | sqltext | i | Sql查询字符串 |
| 返回值类型	| int | | 	说明 | 
| 	值	| 0	| | 查询成功 | 
| | 		1	| | 查询失败 | 

#### 4.2.2.11	GetNextRowData    

| 接口函数 | GetNextRowData |
| -- | -- | 
| 函数名	| GetNextRowData | 
| 功能概要	 | 取出表中的下一条数据 | 
| 记述形式	| MYSQL_ROW  GetNextRowData (MY_SQL_RES  *res_ptr) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| MY_SQL_RES* | res_ptr | i | 数据表地址 |
| 返回值类型	| int | | 	说明 | 
| 	值	| MYSQL_ROW	| | 传出一行数据 | 

#### 4.2.2.12	SelectTableData   

| 接口函数 | SelectTableData |
| -- | -- | 
| 函数名	| SelectTableData | 
| 功能概要	 | 获取表数据 | 
| 记述形式	| MYSQL_RES*  SelectTableData (char  *sqltext) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| char  * | 	sqltext | i | 连接字符串 |
| 返回值类型	| MYSQL_ROW | | 	说明 | 
| 	值	| MYSQL_RES*	| | 数据表地址 | 

#### 4.2.2.13	FreeMemoryData    
			
| 接口函数 | FreeMemoryData |
| -- | -- | 
| 函数名	| FreeMemoryData | 
| 功能概要	 | 释放内存 | 
| 记述形式	| Void FreeMemoryData (MY_SQL_RES  *res_ptr) | 

参数
| 类型	| 变量名	| I/O | 	说明 | 
| -- | -- | -- | -- | 
| MY_SQL_RES* | 	res_ptr | i | 表存储地址 |
| 返回值类型	| void | | 	说明 | 




