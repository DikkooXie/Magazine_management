# Magazine_management
一款由C语言编写的，用控制台运行的轻量级杂志管理软件（大嘘

# 用途
便于企业完成杂志订阅情况的记录、修改、删除、查询、统计等工作。

# 功能
1. 建立订阅信息库，包括：信息编号（UDI）、杂志代码、订阅户名、（订阅户）身份证号、订阅份数、单价、小计等信息。
2. 程序将会将订阅信息存入文件“data.txt”中，每次使用程序会自动将文件中信息读入内存并进行管理，每次正常退出程序都会将信息再次存入文件。
3. 新增订阅信息：此程序可以新建订阅信息，并输入订阅信息中的杂志代码、订阅户名、（订阅户）身份证号、订阅份数、单价等信息，系统自动分配信息编号（UID）并计算单价。每次新增订阅信息后自动将当前内存中的信息保存至文件。
4. 修改订阅信息：此程序可以通过信息编号（UID）修改对应的信息。用户输入信息编号（UID）确认目标信息后，可以自行选择修改信息的杂志代码、订阅户名、（订阅户）身份证号、订阅份数、单价等信息。如果修改了订阅份数或单价，程序会自动计算新的小计。修改完成后自动将当前内存中的信息保存至文件。
5. 删除订阅信息：此程序可以通过信息编号（UID）删除对应的信息。删除完成后自动将当前内存中的信息保存至文件。
6. 查找订阅信息：此程序可以选择通过信息编号（UID）、杂志代码、订阅户名、（订阅户）身份证等检索条件查找符合条件的全部信息。
7. 统计：此程序可以统计杂志销量、用户支出信息、当前收入信息。
8. 打印：此程序可以将所有内存中的信息打印输出。

# 设计图

![image](https://user-images.githubusercontent.com/58894349/216817606-9db1207f-ba00-4b8e-b7e7-de3534da8ffc.png)
