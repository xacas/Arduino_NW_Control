# Arduino_Networked_Control

[Arduino Nanoで作る小さな制御理論実験環境](https://qiita.com/HppyCtrlEngnrng/items/38047016944f60724da8) を
ネットワーク化制御系に拡張して遊ぶためのプログラム群です．

# DEMO
 
 [![thumbnail](https://pbs.twimg.com/ext_tw_video_thumb/1294636262259748870/pu/img/Vcg0JoUhMITbztZ9.jpg)](https://twitter.com/i/status/1294636316978634752)
 
# Features
 
 Linux PC と Arduino で tcp/ip 通信をおこないつつ，RC 回路の電圧制御をおこないます．
 シリアル通信路上で SLIP 回線を構築するため，Ethernet shield など追加部品を用いることなく，ネットワーク化制御系で遊ぶことができます．
 
# Requirement
 
* SerialIP 1.0
 
# Installation

[リンク先](https://github.com/Inokinoki/SerialIP)を DL し，Arduino Library にインポートしてください．

# Usage
 
デモ動画のサンプル
 
* Arduino 側

C/example/P_Control/P_Control.ino を Arduino に書き込む

* Linux 側

比例制御器サーバの実行

```bash
modprobe slip
git clone https://github.com/xacas/SLIP_NW_Control.git
cd C
make
cd example/P_Control
sudo sh Run.sh
```
 
 各信号のリアルタイムプロット．詳細は[こちら](https://qiita.com/lxacas/items/4f0ab61e59981dcb3cdd)
 
 ```bash
 julia
 ```
 
 ```julia
 include("SigPlot.jl")
 main()
 ```
 
# Note
 
 * Run.sh は，Arduino と SLIP 通信するため，
 slattach や ifconfig を実行します．
 実行には sudo 権限が必要です．
 
 * 当リポジトリは，ubuntu 20.04 上で動作を確認しています．
 
 * 当リポジトリのご利用は，利用者の責任においておこなってください．
 当リポジトリの利用により生じた損害に対する責任を負いません．
 要望・不具合は Issue にてご連絡ください．
 
# License
 
 当リポジトリのコードは，LGPL 2.1 ライセンスで公開します．詳しくは，LICENSE を参照してください．
 
 当リポジトリのコードで利用する SerialIP wrapper library は， Adam Nielsen 氏 <malvineous@shikadi.net>
によって書かれています．

また， SerialIP が参照する uIP library は，the Networked Embedded Systems group at the 
Swedish Institute of Computer Science の Adam Dunkels 氏によって書かれています．
 
# Author
 
* 作成者：Masahiro Kusaka
* 所属：UEC
* E-mail：masahiro906@gmail.com
