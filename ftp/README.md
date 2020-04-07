1. 第一次提交的代码只是考虑实现主要功能，如上传文件和目录，下载文件和目录，以及本地主机和远程主机的一些目录操作，不一一列举了。

2. 开发的时候用到了[Qssh](https://github.com/lvklabs/QSsh)，这是在github上的一个项目。不知道为什么作者没有实现REALPATH这条命令，开发的时候觉得没有这条命令不是太方便，于是自己加了这条命令。大体上也是依样画葫芦，同时也参照了sftp的RFC文档。增添的内容比较零散，也没有打算给原版提交，所以就把更改过后的整个qssh的代码目录附在这里了。

3. Qssh用到了botan，这个库的编译本身没有什么问题。只是在调试程序的时候碰到了这么一个错误：

  ```bash
  SSH Protocol error: Server and client capabilities don't match. Client list was: aes128-cbc,3des-cbc.Server list was chacha20-poly1305@openssh.com,aes128-ctr,aes192-ctr,aes256-ctr,aes128-gcm@openssh.com,aes256-gcm@openssh.com.
  ```

  我的server端是macos，一番搜索之后，在/etc/ssh/sshd_config文件中增加了一行`Ciphers aes128-ctr,aes192-ctr,aes256-ctr,aes128-cbc,3des-cbc`,于是问题解决。然而，一则不能保证将来碰到的server端都允许做这样的修改，如果需要的话，二则当我用qt自带的sftp工具测试连接的时候，并没有做这样的修改，也能正常操作。所以，这里的可能一个是win7系统的ssl库的问题，另一个是botan编译时库选择的问题。这是一个需要解决的问题，不过并不急迫。
  
4. 2020/4/7增加了joblog，界面也相应做了些调整。这都是小问题。接下来要考虑的是增加drag和drop，以及远程主机管理，这是功能性的，在界面上则是要考虑文件显示排序和隐藏文件显示。


