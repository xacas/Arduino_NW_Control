# SLIP_Networked_Control

[Arduino Nanoで作る小さな制御理論実験環境](https://qiita.com/HppyCtrlEngnrng/items/38047016944f60724da8) を
ネットワーク化制御系に拡張して遊ぶためのプログラム群です．

# DEMO
 
 <blockquote class="twitter-tweet"><p lang="ja" dir="ltr">Arduino でネットワーク化制御系が出来た <a href="https://t.co/Vlnlm74yZW">pic.twitter.com/Vlnlm74yZW</a></p>&mdash; にちか (@lxacas) <a href="https://twitter.com/lxacas/status/1294636316978634752?ref_src=twsrc%5Etfw">August 15, 2020</a></blockquote> <script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>
 
# Features
 
Ethernet shield など追加部品を用いることなく，ネットワーク化制御系で遊ぶことができます．
 
# Requirement
 
* SerialIP 1.0
 
# Installation

↓の[リンク先](https://github.com/Inokinoki/SerialIP)を DL し，Arduino Library にインポートしてください．

# Usage
 
デモ動画のサンプル
 
* Arduino 側

C/example/P_Control/P_Control.ino を Arduino に書き込む

* Linux 側

PI 制御器サーバの実行

```bash
git clone https://github.com/xacas/SLIP_NW_Control.git
cd C
make
cd example/P_Control
sudo sh Run.sh
```
 
 各信号のリアルタイムプロット
 
 ```bash
 julia
 ```
 
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
 
* 作成者：Masahiro Kusaka
* 所属：？？
* E-mail：masahiro906@gmail.com
