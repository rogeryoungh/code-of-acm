#!/bin/sh

mkdir -p $HOME/bin

curl -sSL https://github.com/rust-lang/mdBook/releases/download/v0.4.37/mdbook-v0.4.37-x86_64-unknown-linux-gnu.tar.gz | tar -xz --directory=$HOME/bin
curl -sSL https://github.com/lzanini/mdbook-katex/releases/download/v0.6.0/mdbook-katex-v0.6.0-x86_64-unknown-linux-gnu.tar.gz | tar -xz --directory=$HOME/bin

chmod +x $HOME/bin/mdbook
chmod +x $HOME/bin/mdbook-katex

export PATH="$HOME/bin:$PATH"

python ./scripts/extract.py
cd ./template && mdbook build
