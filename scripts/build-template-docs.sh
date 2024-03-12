#!/bin/sh

mkdir -p $HOME/bin

curl -sSL https://github.com/rust-lang/mdBook/releases/download/v0.4.37/mdbook-v0.4.37-x86_64-unknown-linux-gnu.tar.gz | tar -xz --directory=$HOME/bin
wget -q https://github.com/rogeryoungh/preprocessor-md-tex/releases/download/v0.1.2/preprocessor-md-tex -O $HOME/bin/preprocessor-md-tex

chmod +x $HOME/bin/mdbook
chmod +x $HOME/bin/preprocessor-md-tex

export PATH="$HOME/bin:$PATH"

preprocessor-md-tex ./template/src/
python ./scripts/extract.py
cd ./template && mdbook build
