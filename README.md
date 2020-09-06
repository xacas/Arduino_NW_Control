# SLIP_Networked_Control

[Arduino Nanoで作る小さな制御理論実験環境](https://qiita.com/HppyCtrlEngnrng/items/38047016944f60724da8) を
ネットワーク化制御系に拡張して遊ぶためのプログラム群です．

# DEMO
 
 
# Features
 
Ethernet shield など追加部品を用いることなく，ネットワーク化制御系で遊ぶことができます．
 
# Requirement
 
* SerialIP 1.0
 
# Installation

↓のリンク先を DL し，Arduino Library にインポートしてください．
https://github.com/Inokinoki/SerialIP

# Usage
 
* デモ動画のサンプル
 
* Arduino 側

C/example/P_Control/P_Control.ino を Arduino に書き込む

* Linux 側

** PI 制御器サーバの実行

```bash
git clone https://github.com/xacas/SLIP_NW_Control.git
cd C
make
cd example/P_Control
sudo Run.sh
```
 
 ** 各信号のリアルタイムプロット
 
 ```julia
 include("SigPlot.jl")
 main()
 ```
 
# Note
 
 Run.sh は，Arduino と SLIP 通信するため，
 slattach や ifconfig を使用します．
 sudo で実行してください．
 
 本リポジトリは，ubuntu 20.04 上で動作を確認しています．
 
# Author
 
* 作成者：日下雅博
* 所属：？？
* E-mail：masahiro906@gmail.com
