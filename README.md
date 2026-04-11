# 今田研GPUサーバでのKokkosの始め方

今田研究室のGPUサーバで、Kokkosライブラリを使用してGPU計算を始めるためのクイックスタートガイドです。

**2026/4/11 Linux環境への移行に合わせて修正**

## 0. Kokkosとは

[Kokkos](https://github.com/kokkos/kokkos)は並列計算のためのC++ライブラリの一つで、その特長は同じコードが異なる環境(CPU(OpenMP)でもGPU(CUDA)でも)で実行可能である点にある。
また、CUDAやOpenMPと比較して、Kokkosはよりシンプルにコードを書くことができ、GPUプログラミングの初心者にとっても扱いやすい。
公式の[wiki](https://kokkos.org/kokkos-core-wiki/index.html)が非常に詳しいので、詳細はそちらを参照してほしい。
並列処理についてなども含めて、概要については[こちらの記事(日本語)](https://qiita.com/gandalfr-KY/items/acb23a50d423c49f08b3)がわかりやすい。

## 1. Kokkosのインストール

まずはgithubからKokkos(最新版(2026/4/11現在))をインストールする。
```bash
cd ~
git clone -b 5.1.0 https://github.com/kokkos/kokkos.git
cd kokkos
```
ビルドする。
```bash
mkdir build
cd build
cmake .. \
  -DCMAKE_CXX_COMPILER=$PWD/../bin/nvcc_wrapper \
  -DKokkos_ENABLE_CUDA=ON \
  -DKokkos_ENABLE_CUDA_LAMBDA=ON \
  -DKokkos_ENABLE_SERIAL=ON \
  -DKokkos_ARCH_ADA89=ON \
  -DCMAKE_CXX_STANDARD=20 \
  -DCMAKE_INSTALL_PREFIX=$HOME/kokkos-install
make
make install
```
ホームディレクトリに`kokkos-install`というディレクトリができていれば成功。

## 2. Kokkosを動かす

GitHubからサンプルコードをクローンする。
```bash
git clone https://github.com/KazuhiroOsada/kokkos_imadalab.git
cd kokkos_imadalab
```
コンパイル。
```bash
mkdir build
cd build
cmake ..
make
```
`sample`という実行ファイルができていれば成功。実行すると計算結果が表示される。
```bash
./sample
```

## 3. サンプルの説明

サンプルプログラムでは、GPU上で一次元配列の初期化、合計値と最大値の算出を行っている。

### 3.1 Kokkos::initialize/finalize

* Kokkosの使用の開始と終了を宣言している。
* Kokkos::finalizeを呼ぶ前に、すべてのKokkosオブジェクトをメモリから解放する必要があるので、全体を{}で囲うのが作法。

### 3.2 Kokkos::View

* Kokkosにおいて配列の役割をするもの。型・次元・メモリ配置を設定できる。```Kokkos::View<double*> x("x", N);```では、長さNの倍精度実数の一次元配列を宣言している。
* (一般的には)CPUとGPUのメモリは独立している。データは実行環境に確保され、Viewは確保されたメモリへの参照の役割を果たす。
* サンプルでは、GPU側にメモリが確保されるので、CPU側でデータの出力を行うために、手元にデータをコピーしている。

### 3.3 Kokkos::parallel_for

* KOKKOS_LAMBDAで定義された処理を、指定した回数分、GPU上の各スレッドで並列に実行する。
* 当然、要素ごとに依存がない(計算順序に左右されない)処理でなければいけない。

### 3.4 Kokkos::parallel_reduce

* 配列の各要素に対して同じ演算を繰り返して一つの値を求める(いわゆるreduction)時に使う。例えば、総和を求めたいときや、最大最小を求めたい時など。
* ```Kokkos::Sum<double>```(デフォルト)や```Kokkos::Max<double>```などの"Reducer"を指定する必要がある。
