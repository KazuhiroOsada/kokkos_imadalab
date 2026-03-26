# 今田研GPUサーバでのKokkosの始め方

今田研究室のGPUサーバで、Kokkosライブラリを使用してGPU計算を始めるためのクイックスタートガイドです。

## 0. Kokkosとは

[Kokkos](https://github.com/kokkos/kokkos)は並列計算のためのC++ライブラリの一つで、その特長は同じコードが異なる環境(CPU(OpenMP)でもGPU(CUDA)でも)で実行可能である点にある。
また、CUDAやOpenMPと比較して、Kokkosはよりシンプルにコードを書くことができ、GPUプログラミングの初心者にとっても扱いやすい。
公式の[wiki](https://kokkos.org/kokkos-core-wiki/index.html)が非常に詳しいので、詳細はそちらを参照してほしい。
並列処理についてなども含めて、概要については[こちらの記事(日本語)](https://qiita.com/gandalfr-KY/items/acb23a50d423c49f08b3)がわかりやすい。

## 1. Kokkosのインストール

WSLで作業する。使い方はマニュアルを参照。cmake等が入っているものを使うとよい。
まずはgithubからKokkosをインストールする。
最新版は要求が厳しいので、少し古いバージョンをインストールする。
```bash
git clone　-b 4.4.01 https://github.com/kokkos/kokkos.git
cd kokkos
```
必要なパッケージをインストールする。
```bash
wsl -u root
sudo apt install nvidia-cuda-toolkit
sudo apt install -y gcc-12 g++-12
```
ビルドする。
```bash
mkdir build
cd build
cmake .. \
  -DCMAKE_CXX_COMPILER=g++-12 \
  -DKokkos_ENABLE_CUDA=ON \
  -DKokkos_ENABLE_SERIAL=ON \
  -DKokkos_ARCH_ADA89=ON \
  -DCMAKE_CXX_STANDARD=17 \
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
