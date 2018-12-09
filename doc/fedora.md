# Fedora Installation and Usage

Fedora is in the same series of RedHat and CentOS, and they all use `yum` package manager, which is very convenient.

CentOS is free and used widely for servers.

Therefore, we will get great profit if using Fedora as workstations.

---

## LaTex

Fedora 仓库自带的texlive有问题，应该从texlive官网下载安装，运行安装包中的tl-advance程序。
(the GUI version is not so easy to run, in terminal version you must do some settings, search on Internet)

英文用pdflatex编译，文献用bibtex编译。
中文的话用xelatex编译，亲测可用， 前提是中文字体要安装好。

可以在Makefile中用命令来编译latex，并用evince预览：

```
all: refman.pdf

pdf: refman.pdf

refman.pdf: clean refman.tex
        pdflatex refman
        makeindex refman.idx
        pdflatex refman
        latex_count=8 ; \
        while egrep -s 'Rerun (LaTeX|to get cross-references right)' refman.log && [ $$latex_count -gt 0 ] ;\
            do \
              echo "Rerunning latex...." ;\
              pdflatex refman ;\
              latex_count=`expr $$latex_count - 1` ;\                                        
            done
        makeindex refman.idx
        pdflatex refman


clean:
        rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg *.log *.out *.brf *.blg *.bbl refman.pdf

```

TexStudio 分双栏

Texmacs  不分双栏，与Typora写markdown类似

LyX

---

## Chinese

Fedora 中文社区软件源 

https://repo.fdzh.org/

rpmfusion  (free, non-free)

epel 

different sources(ustc, tsinghua, hust...)

安装中文字体：可以直接拷贝Windows系统中的字体，并在Fedora中生成字体的缓存。

---

## Draw

[Latex tikz](https://blog.csdn.net/xiahn1a/article/details/46547981)

Graphviz 适合画流程图

Gimp

Inkscape

Asymptote

Matlab 可在正版软件共享平台下载Linux版

Gunplot

Python Matplotlib

---

#! /bin/bash

# for svn diff: 修改~/.subversion/config，找到如下配置行：
# diff-cmd = diff_program (diff, gdiff, etc.)
# diff-cmd = ~/bin/diffwrap.sh

# 参数大于5时，去掉前5个参数；参数小于5，失败，什么也不做
shift 5

# 使用vimdiff比较
vimdiff "$@"

