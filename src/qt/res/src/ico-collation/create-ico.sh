#!/bin/sh
# Requires imagemagick https://imagemagick.org/
cp ../icons/bitcoin.png helium-1024x1024.png
for b in 16 20 24 30 32 36 40 48 60 64 72 80 96 128 256 320 384 512
do
convert helium-1024x1024.png -resize ${b}x${b} bitcoin${b}.png
done
convert bitcoin16.png bitcoin20.png bitcoin24.png bitcoin30.png bitcoin320.png bitcoin32.png bitcoin36.png bitcoin40.png bitcoin48.png bitcoin128.png bitcoin60.png bitcoin64.png bitcoin72.png bitcoin80.png bitcoin96.png bitcoin256.png bitcoin384.png bitcoin512.png favicon.ico
rm -f bitcoin*.png helium-1024x1024.png
