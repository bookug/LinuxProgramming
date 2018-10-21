# 目录结构
Linux 系统默认的文件系统格式是 ext4。
和其他操作系统一样，Linux 的文件系统采用的也是树形结构，树的根就是根目录(root directory)，用一个正斜杠 `/` 表示，树的叶子
是文件，中间结点则是目录。
要注意的是，Linux 的路径名中用正斜杠 `/` 分隔目录名，而 Windows 中用的则是反斜杠`\`。

Linux 系统的根目录下通常有下面一些子目录：
- `/bin`：供所有用户使用的完成基本任务（在单人维护模式下还能够被操作的指令）的可执行文件，如bash, mv, cp, touch, more, chmod, ls, which；
- `/boot`：启动Linux时使用的一些核心文件。如操作系统内核、引导程序Grub等；
- `/cdrom`：空，可以将光驱文件系统挂在这个目录；
- `/dev`：所有系统设备文件，从此目录可以访问各种系统设备；
- `/etc`：系统和应用软件的全局配置文件，如passwd, shadow, hosts, timezone；
- `/home`：普通用户的家目录所在的位置；
- `/lib`：系统动态连接共享库文件和内核模块，相当于.dll文件；
- `/lib64`：64位系统动态连接共享库文件；
- `/lost+found`：几乎每个分区都有，储存发生意外后丢失的文件，只有root用户才能打开；
- `/media`：可移动设备的挂载点，如光盘，u盘；
- `/mnt`：空，可以作为外挂设备的挂接点；
- `/opt`：一些第三方软件的安装位置，/usr/local/；
- `/proc`：存在于内存中的虚拟文件系统，保存内核和进程的状态信息；
- `/root`：超级用户的家目录；
- `/run`：系统开机后所产生的各项信息放置到 /var/run 目录下，新版的 FHS 则规范到 /run 下面；
- `/sbin`：供超级用户用的可执行程序，如reboot, shutdown, ifconfig；
- `/snap`：ubuntu的新软件包管理方式，snap软件包；
- `/srv`：网络服务所需要取用的，提供给网络任何人浏览的，数据目录；
- `/sys`：Linux2.6内核中的虚拟文件系统sysfs，记录核心系统硬件信息；
- `/tmp`：创建临时文件或目录；
- `/usr`：静态的用户级应用程序数据；
  - `/usr/bin/`：供一般用户用的非必需的可执行程序；
  - `/usr/games/`：与游戏比较相关的数据放置处；
  - `/usr/include/`：存放编写程序需要的头文件的目录；
  - `/usr/lib/`：系统的非必需的库文件；
  - `/usr/local/`：空，安装本地程序的默认路径
  - `/usr/sbin/`：供超级用户用的非必需的可执行程序；
  - `/usr/share/`：放置只读架构的数据文件，包括共享文件；
  - `/usr/src/`：内核和软件的源代码的位置；
- `/var`：动态的应用程序数据；
  - `/var/cache`：应用程序的缓存文件；
  - `/var/lib`：应用程序的信息、数据，如数据库的数据等都存放在此文件夹。
  - `/var/local`：`/usr/local`中程序的信息、数据
  - `/var/lock`：锁定文件，许多程序遵循在 `/var/lock` 中产生一个锁定文件的约定，以用来支持他们正在使用某个特定的设备或文件。其他程序注意到这个锁定文件时，就不会再使用这个设备或文件；
  - `/var/log`：系统日志文件，如登录文件；
  - `/var/opt`：/opt中程序的信息、数据；
  - `/var/run`：正在执行着的程序的信息，如PID文件应存放于此；
  - `/var/spool`：存放程序的假脱机数据（即spool data）
  - `/var/tmp`：临时文件；

# 文件权限

## 文件类型
- `-`表示普通文件
- `d`表示目录
- `l`表示符号链接
- `s`表示具有 SUID 属性的文件
- `b`表示块设备
- `c`表示字符设备
- `p`表示管道

## 链接
Linux链接分两种，一种被称为硬链接（Hard Link），另一种被称为符号链接（Symbolic Link），即软链接。
只有软链接的类型为l。

默认情况下，`ln 对象 链接名`命令产生硬链接。`ln -s 对象 链接名`命令产生软链接。

### 硬链接
在你选定的位置上生成一个和源文件大小相同的文件
- 硬链接以文件副本的形式存在。但不占用实际空间
- 不允许给目录创建硬链接
- 硬链接只有在同一个文件系统中才能创建

### 符号链接
在你选定的位置上生成一个文件的镜像，不会占用磁盘空间
- 以路径的形式存在。类似于Windows操作系统中的快捷方式
- 可以 跨文件系统
- 可以对一个不存在的文件名进行链接
- 可以对目录进行链接

硬链接文件与原文件的inode节点相同，软链接仅仅是一个链接
```
touch afile
ln afile linkh
ln -s afile links
ls -l -i

echo "i am a file" >> afile
cat afile linkh links
rm afile
cat linkh links
ls

touch afile
echo "i am another file" >> afile
cat linkh links
```
目录不能创建硬链接：你创建一个目录的硬连接之后，操作系统需要把这个目录下所有的文件都要做一次硬链接，这样操作系统在访问这个链接的时候要不断去遍历，大大增加复杂度，而且很容易进入死循环。
```
mkdir folder 
cp quote.txt folder
ln -s folder alink 
ln -s ./folder blink 
ln -s ~/test/folder clink 
mkdir infolder
ln -s infolder dlink 
cp -r *link infolder/
cd infolder
ls -l
mkdir folder 
ls -l
```
现在 `alink` 和 `blink` 都是指向 `./infolder/folder` 的
```
ln -s . thislink 
ln -s .. uplink
cd thislink
cd uplink
cd dlink
cd uplink/dlink # ...
pwd
pwd -P
cd -P .
```

## 用户
### 用户组
为了便于管理，Linux 系统中的用户被分成一个个的用户组，每个用户可以同时属于多个用户组，
`/etc/passwd` 中给出的用户组是该用户的默认用户组。用户组的信息存储在文件
`/etc/group` 中。

### 文件的用户
系统中的每个文件都有属主(owner)，即拥有该文件的用户。大部分系统文件的属主是超级用户，
普通用户无权修改它们。每个文件除了有属主以外，还有一个用户组的属性。
默认情况下，文件的组就是属主的默认组。这样，对于一个文件来说，系统上的所有用户
被分成三类：第一类是该文件的属主。第二类是该文件的用户组中的用户，第三类是所有其他用户。 

### 修改文件用户和用户组
```
chown user:group FILE
chown -R ...
```

##权限
### 访问权限
第一列除第一个字符外的其余 9 个字符用于描述不同用户对文件的访问权限，
它们每三个字符构成一组，共三组，分别表示属主(owner)、用户组成员(group)和其他用户
(other)对该文件的访问权限。每组三个字符依次是r (read, 表示读的权限)、
w (write, 表示写的权限) 和x (execute, 表示执行权限)，如果具有该权限，
则显示相应的字符，如果不具有该权限，则显示一个短横线`-`。

### 特殊访问权限
- SetUID(SUID)：出现在文件所有者的 x 权限上，仅对二进制程序有效，
程序的执行者在执行该程序过程中具有程序所有者的权限。
```
passwd
```
- SetGID(SGID)：出现在文件用户组的 x 权限上，仅对二进制程序和目录有效。
  - 程序的执行者在执行该程序过程中具有程序用户组的权限
  - 用户在此目录下的有效用户组将变成该目录的用户组，即使你不属于它
- StickyBIT(SBIT)：出现在文件其他用户的 x 权限上，仅对目录有效。当用户在该目录下创建新文件或目录时，
仅有自己和 root 才有权力删除。
```
ls -l /tmp
```

### 修改访问权限
**只有文件的 owner 才能修改这个权限**
```
chmod [ugoa][+-][rwx] # 如果只想增加或去除目录的执行权限，大写
chmod -R  ...         # 递归修改
```
`chmod` 命令用三个八进制数来表示三类用户的权限，分别对应属主、用户组和其他用户，
可读加4，可写加2，可执行加1，如果是去除权限就减去相应位上的数。

### 文件 attribute
- a 写操作的时候只能添加，不能删除现有内容。
- c 内核会自动对文件进行压缩。
- i 不能删除、移动、链接、写入。
- s 文件删除时，磁盘空间也会清理乾净。
- S 修改时直接写入磁盘，而不是写在缓冲区中。

# 特殊设备
## 标准读写设备
- stdin：标准输入0，使用 `<` 或 `<<` 或 `<<<`。
- stdout：标准输出1，使用 `>` 或 `>>`。
- stderr：标准错误输出2，使用 `2>` 或 `2>>`。
默认情况下，基本输入输出文件通常对应于用户的终端：标准输入就是键盘，
而标准输出和标准错误则是屏幕或窗口。在shell 命令行上可以用字符`>`、`<` 和 `&` 对基本输入输出进行重新定向.
- `<` 输入重定向
```
wc -l quote.txt
wc -l < quote.txt
tr "a" "A" < quote.txt
tr a-z A-Z < quote.txt > quate.txt
```
- `<<` 输入重定向并指定分隔符
```
cat << EOF
Working dir "$PWD" `pwd`
EOF
```
- `<<<` 输入重定向，用于字符串
```
tr a-z A-Z <<< "one two three"
```
- 输出重定向
```
tr "a" "A" < quote.txt
tr "a" "A" < quote.txt > quate.txt
cat quote.txt quate.txt 
cat quote.txt quate.txt > test.txt
cat quote.txt qubte.txt > test.txt
cat quote.txt qubte.txt 2>&1 > test.txt
cat quote.txt qubte.txt > test.txt 2>&1
cat quote.txt qubte.txt &> test.txt
```
## 读写设备
- null：黑洞设备，丢弃一切写入其中数据；
```
cat quote.txt quate.txt > /dev/null
```
- zero：读取时提供无限的空字符`\0x00`；
```
dd if=/dev/zero of=输出 count=1024 bs=1024
```
- full：常满设备，写入时返回设备无剩余空间（ENOSPC）；
```
cat 文件 > /dev/full
```
## 随机数熵池
- random：存储着系统当前运行的环境的实时数据。它可以看作是系统某个时候唯一值数据，因此可以用作随机数元数据。我们可以通过文件读取方式，读得里面数据;
- urandom：这个设备数据与 random 里面一样。只是，它是非阻塞的随机数发生器，读取操作不会产生阻塞;
```
echo "$(cat /dev/urandom | head -c 10 | cksum | awk -F ' ' '{print $1}') % 1000" | bc
```
- loop：Loop设备可以把文件作为块设备挂载使用，
```
mount -o loop 文件 位置
```