#!/bin/sh
for b in 16 22 32 48 64 96 128 256 512 1024
do
convert squorum-1024x1024.png -resize ${b}x${b} bitcoin${b}.png
convert squorum-1024x1024.png -resize ${b}x${b} bitcoin${b}.xpm
done

cp squorum-1024x1024.png icon_512x512@2x.png
png2icns bitcoin.icns icon_16x16.png icon_32x32.png icon_128x128.png icon_256x256.png icon_512x512.png icon_512x512@2x.png
rm -f icon_* squorum-1024x1024.png