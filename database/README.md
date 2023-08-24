### 数据库部分

#### 概述
存在`InsertResult,DeleteResult,UpdateResult,SelectResult`四个类  
每个类含有`error_code`和`error_mes`两个成员,分别用于存放错误代码和错误信息
`SelectResult`类含有`data`成员,用于存放数据


#### 初始化
1. sqlite:需要下载sqlite,在命令行中输入`sudo apt-get install libsqlite3-dev
`  
2. 数据库路径: 使用相对路径
3. 数据库:数据库已经上传,在`/database/database_files`中的`future_chat.db`即是数据库文件  
        若已删除,可以取消`init_database.cpp`的注释，注释`test_database.cpp`后运行`make init_database`，也可以直接运行编辑好的`init_database`  
4. 测试: 编译并运行`test_database`以确定配置完成

#### 使用
使用步骤:  
1. 用数据库路径初始化数据库,定义`string`类型的SQL代码
2. 进行X操作前,创建一个`XResult`对象
3. 使用`XResult`的成员函数执行SQL,批量执行可以使用`batch_execute`形式  
4. 使用`check_result`函数检查是否执行成功

具体操作可以查看test_database.cpp  

