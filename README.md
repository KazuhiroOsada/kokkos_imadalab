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
cmake .. -DKokkos_ROOT=$HOME/kokkos-install
make
```
`sample`という実行ファイルができていれば成功。実行すると計算結果が表示される。
```bash
./sample
```
