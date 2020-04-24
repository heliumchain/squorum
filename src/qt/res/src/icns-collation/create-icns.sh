#!/bin/sh
# Requires: imagemagick https://imagemagick.org/ and
# icnsutils from Debian linux distro or compiled binary
# from sources: https://github.com/kornelski/libicns
cp ../icons/bitcoin.png squorum-1024x1024.png
for b in 16 32 128 256 512
do
convert squorum-1024x1024.png -resize ${b}x${b} icon_${b}x${b}.png
# *Should* be:
# convert squorum-1024x1024.png -unsharp 0 -resize $((b*2))x$((b*2)) icon_${b}x${b}@2x.png
# except that icon_32x32.png is reported as dupe of 16x16@x2.png, hslting the conversion,
# so I guess some resolution changing is required.
done
# When the above all workis nicely, until then ...
# png2icns bitcoin.icns icon_16x16.png icon_16x16@2x.png icon_32x32.png icon_32x32@2x.png icon_128x128.png icon_128x128@2x.png icon_256x256.png icon_256x256@2x.png icon_512x512.png icon_512x512@2x.png
cp squorum-1024x1024.png icon_512x512@2x.png
png2icns bitcoin.icns icon_16x16.png icon_32x32.png icon_128x128.png icon_256x256.png icon_512x512.png icon_512x512@2x.png
rm -f icon_* squorum-1024x1024.png
