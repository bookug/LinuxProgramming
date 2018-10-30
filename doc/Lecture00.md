## Linux 服务器运维

用作服务器时最好用终端 ssh 连接，而不用开远程桌面

---

### 入门材料

最好的方法就是强制自己只使用 Linux

#### 书籍

鸟哥的 Linux 私房菜

---

### 各种发行版的主要区别

首先是包管理器不一样，社区不一样，理念不一样。
其中 Gentoo 和Archlinux 是支持滚动升级的。

CentOS 稳定但软件版本较低，更新慢，比如 CentOS 7 的 GCC 版本至今只是 4.8.5 。

Gentoo 性能高，可滚动升级，版本控制方便；但配置麻烦，性能提升不一定明显且耗电量高

Archlinux 过于激进，不够稳定，维护代价高

Ubuntu 过于在乎桌面，有些华而不实，性能和稳定性都是其缺陷

---

### 电源管理

UPS 备用电源

夜冷或风冷

grub 引导

安装后可制作恢复光盘，紧急情况下可用于抢救

断电前要关机

查看电源电量，如何降低消耗

---

### 系统状态

free -h

top

iotop

df -h

blkid

mount

---

### 设备管理

mount

ntfs-3g

fstab设置自动挂载若开机时找不到会无法启动，此时需要用启动盘进入修改fstab文件

ssd挂载时的各种选项，文件系统，是否启用日志等等

---

### 硬件驱动

如何选购

网卡

显卡

其他硬件如手写板等

---

### 用户管理


密码设置

shell 设置

用户操作历史记录，有时可用来检测是哪个误操作导致的问题

---

### 网络管理

禁用 firewalld ，统一使用 iptables

禁用root登录(防止暴力攻击)，sshd 只允许指定用户登录，最好能限制域名登录(比如大部分服务器只允许内网访问)，设置ip黑名单

lastlog

nfs

多机之间的通信

ping tcping

---

### 任务调度

进程的优先级  nice

ulimit 软硬设置

进程和线程都是走内核的 vfork() 接口，不过是用不一样的选项，线程也要占用 ulimit 里面的进程 ID

ps aux|grep name   查看某进程，可获取进程PID

ps -eLF

kill -9

killall

---

### 版本控制

各种版本的软件

各种版本的库  动态库与静态库

---

### 安全问题

rm 命令

ls.sh 脚本

setuid/setgid

LD_LIBRARY_PATH

/tmp sticky bit

### 其他

定时任务  crontab

---

### 相关社区

各种开源社区

北京大学  Linux 俱乐部

---
### 故障记录
1. yum remove vim-* -y 会卸载所有vim的依赖项，包括sudo，而且没有提示。
解决方案：用su命令进入root，重新安装sudo
