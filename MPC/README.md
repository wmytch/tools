1. 2020/4/29 第一次提交，也算是个备份吧，大体框架而已

2. 2020/5/2 最主要的是解决了qt中使用moveToThread引发的一个常见问题`QObject: Cannot create children for a parent that is in a different thread`。具体参见tcpworker.cpp中TcpWorker的构造函数，

    ​    
