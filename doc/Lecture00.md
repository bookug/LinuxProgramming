# Linux 服务器运维

<span id="start"></span>

用作服务器时最好用终端 ssh 连接，而不用开远程桌面

<!-- markdown jump in a page -->
<!-- https://blog.csdn.net/scythe666/article/details/51956450 -->

## 目录

- [入门材料](#material)
- [发行版本](#release)
- [电源管理](#battery)
- [系统状态](#status)
- [设备管理](#device)
- [硬件驱动](#driver)
- [用户管理](#user)
- [网络管理](#network)
- [任务调度](#schedule)
- [版本控制](#version)
- [安全问题](#safety)
- [相关社区](#community)
- [故障记录](#bugs)

---

### 入门材料

<span id="material"></span>

最好的方法就是强制自己只使用 Linux

#### 书籍

鸟哥的 Linux 私房菜

---

### 各种发行版的主要区别

<span id="release"></span>

```
查看发行版本
uname -r
uname -a
cat /proc/version
cat /etc/issue
yum -y install redhat-lsb
lsb_release
```

首先是包管理器不一样，社区不一样，理念不一样。
其中 Gentoo 和Archlinux 是支持滚动升级的。

CentOS 稳定但软件版本较低，更新慢，比如 CentOS 7 的 GCC 版本至今只是 4.8.5 。

Gentoo 性能高，可滚动升级，版本控制方便；但配置麻烦，性能提升不一定明显且耗电量高

Archlinux 过于激进，不够稳定，维护代价高

Ubuntu 过于在乎桌面，有些华而不实，性能和稳定性都是其缺陷

---

### 文件系统

<span id="filesystem"></span>

ls -al 查看全部文件并列出属性，包括隐藏文件

-h 有时指的是human-readable, 有时指的是 --help

-v 有时指的是verbose，输出详细信息，有时指的是version，查看版本信息

用ls -l命令可以看到，软链接的属性首位是l表示软链接，显示的大小恰好是软链接指向的文件的名的字节数。
这说明软链接确实是很简单的链接方式，使用软链接时仅仅是告诉操作系统要找的文件名是啥，而没有直接指向文件系统中的I-node。
如果是用ls -l查看目录，属性首位应该是d。
在ls -l命令的输出中，文件的引用数至少是1，目录的引用数至少是2，因为除了其自身外，目录下面还有一个`.`引用也指向其自身，`..`则指向上层目录。

---

### 电源管理

<span id="battery"></span>

UPS 备用电源

夜冷或风冷

grub 引导

安装后可制作恢复光盘，紧急情况下可用于抢救

断电前要关机

查看电源电量，如何降低消耗

---

### 系统状态

<span id="status"></span>

free -h

top

iotop

uptime

htop

df -h

blkid

mount

uptime不需要sudo用户，但如果加上sudo，又没有管理员权限，即无法使用。
默认这种情况，系统管理员会收到一封邮件，但也没有关系。

---

### 设备管理

<span id="device"></span>

mount

ntfs-3g

fstab设置自动挂载若开机时找不到会无法启动，此时需要用启动盘进入修改fstab文件

ssd挂载时的各种选项，文件系统，是否启用日志等等

---

### 硬件驱动

<span id="driver"></span>

如何选购

网卡

显卡

其他硬件如手写板等

---

### 用户管理

<span id="user"></span>

密码设置

shell 设置

用户操作历史记录，有时可用来检测是哪个误操作导致的问题

sshpass

bash alias

ssh-keygen    

https://www.jb51.net/article/101191.htm

ssh pkuteach 需要修改 ~/.ssh/config文件

还可以更改用户名，如 ssh xxx@pkuteach

~/.ssh 的权限应是700，其下面文件的权限应是600 （新建文件的默认权限是644）

---

### 网络管理

<span id="network"></span>

禁用 firewalld ，统一使用 iptables

禁用root登录(防止暴力攻击)，sshd 只允许指定用户登录，最好能限制域名登录(比如大部分服务器只允许内网访问)，设置ip黑名单

lastlog

nfs

多机之间的通信

ping tcping

---

### 任务调度

<span id="schedule"></span>

定时任务  crontab

进程的优先级  nice

ulimit 软硬设置

进程和线程都是走内核的 vfork() 接口，不过是用不一样的选项，线程也要占用 ulimit 里面的进程 ID

ps aux|grep name   查看某进程，可获取进程PID

ps -eLF

kill -9

killall

---

### 版本控制

<span id="version"></span>

各种版本的软件

各种版本的库  动态库与静态库

---

### 安全问题

<span id="safety"></span>

rm 命令

ls.sh 脚本

setuid/setgid

LD_LIBRARY_PATH

/tmp sticky bit

---

### 相关社区

<span id="community"></span>

各种开源社区

北京大学  Linux 俱乐部

---

### 故障记录

<span id="bugs"></span>

#### CentOS系统：abrt-hook-ccpp 占用太大

这是因为内核收集的关于 core dump 的信息太多，造成后台的收集程序本身占用太大内存。
可以直接用 `kill -9` 关闭这几个占用特别大的 abrt-hook-ccpp 程序。

#### CentOS系统： `yum remove vim-* -y` 会卸载所有vim的套件，甚至连sudo也删除了，而且没有提示。

会出现这种情况，是Linux上的库依赖导致的问题。
首先 `yum remove vim-*` 和 `yum remove vim` 不同，会把所有 vim 相关的套件都删除，包括 vim-minimal。
用 `yum deplist sudo` 会发现，sudo 是依赖于 vim-minimal 的，具体是 visudo 这个命令，需要调用 vim-minimal里面的编辑器的功能。
这样当 vim-minimal被移除后，sudo 无法正常工作，所以也会被移除。
注意，Linux上删除一个软件时，会把所有依赖于这个软件的也会删除，所以一般不建议直接删除所有套件。

sudo是用来临时获得管理员权限的重要途径，必须重新装回来。
但此时sudo已经被删掉了，无法通过sudo来获得管理员权限安装sudo本身。
可用su root命令进入root，重新安装sudo，这要求输入root账户的密码。
安装好sudo后可用sudo -i命令进入root账户，这要求当前用户在sudoers中且输入该用户的密码。
`su - xxx` 可进入xxx账户，要求输入xxx账户的密码，如果当前用户是root账户，则无需输入密码。

添加或删除用户的管理员权限，可通过编辑`/etc/sudoers`文件来实现。
这个文件默认对所有用户都只是只读的，即便拥有管理员权限，也必须先将其设置为root账户可写，再修改，最后再移除写权限。
如果忘记移除sudoers的写权限，可能导致操作系统认为这不安全而禁用sudo，此时也只能登录root账户来修改。
比较推荐的是另一种做法，使用`visudo`命令来修改管理员权限，不需要其他额外操作，修改完保存退出即可，当然这个命令本身需要管理员权限才能运行。

如果忘记root密码？
很麻烦，可以尝试使用安装系统后配套的Linux恢复光盘，或者通过另一个Linux U盘启动盘(推荐archlinux的启动盘)来进入文件系统并修改。
一般建议不要轻易使用root密码，不要外泄，不要更改。
将root密码手写并离线保存在安全的地方，只在必要时取出使用，使用后马上封存。
不推荐用打印机是因为打印机里可能有信息记录，也不够安全。
需要提供远程登录的服务器，建议禁止root用户远程登录，因为这是暴力攻击最常用的账户了。

如果用 tmux 管理会话，在tmux里某个窗口(window, 或者session, pane)登录了root账户，那么这个账户会一直保存在那里，不会退出。
这提供了很大的便利，但也可能带来安全问题，比如别人通过在你打开的tmux会话里操作，不需要输入密码也可以使用root权限。

yum 的常用命令如下：

- yum deplist libcurl    查看 libcurl 依赖于哪些软件包
- rpm -qf /usr/lib64/libcurl.so 
- yum search libcurl   查看哪些软件包依赖于 libcurl
- yum check-update 检查可更新的所有软件包
- yum update 下载更新系统已安装的所有软件包
- yum upgrade 大规模的版本升级,与yum update不同的是,连旧的淘汰的包也升级
- yum install 安装新软件包
- yum update 更新指定的软件包
- yum remove 卸载指定的软件包
- yum groupinstall 安装指定软件组中的软件包
- yum groupupdate 更新指定软件组中的软件包
- yum groupremove 卸载指定软件组中的软件包
- yum grouplist 查看系统中已经安装的和可用的软件组
- yum list 列出资源库中所有可以安装或更新以及已经安装的rpm包
- yum list 列出资源库中与正则表达式匹配的可以安装或更新以及已经安装的rpm包
- yum list available 列出资源库中所有可以安装的rpm包
- yum list available 列出资源库中与正则表达式匹配的所有可以安装的rpm包
- yum list updates 列出资源库中所有可以更新的rpm包
- yum list updates 列出资源库中与正则表达式匹配的所有可以更新的rpm包
- yum list installed 列出资源库中所有已经安装的rpm包
- yum list installed 列出资源库中与正则表达式匹配的所有已经安装的rpm包
- yum list extras 列出已经安装的但是不包含在资源库中的rpm包
- yum list extras 列出与正则表达式匹配的已经安装的但是不包含在资源库中的rpm包
- yum list recent 列出最近被添加到资源库中的软件包
- yum search 检测所有可用的软件的名称、描述、概述和已列出的维护者，查找与正则表达式匹配的值
- yum provides 检测软件包中包含的文件以及软件提供的功能，查找与正则表达式匹配的值
- yum clean headers 清除缓存中的rpm头文件
- yum clean packages 清除缓存中rpm包文件
- yum clean all 清除缓存中的rpm头文件和包文件

---

[回到顶部](#start)

