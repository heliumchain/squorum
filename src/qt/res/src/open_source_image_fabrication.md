Processing path for sQuorum H logo.

Primary source is vector serialisation in `squorum-h-74ade8ff.svg`, exported as 1024 x 1024 `PNG` format to `squorum-h-74ade8ff.png`

Copy `squorum-h-74ade8ff.png` to `squorum-1024x1024.png`, then ...

```
#!/bin/sh
for b in 16 20 24 30 32 36 40 48 60 64 72 80 96 128 256 320 384 512
do
convert squorum-1024x1024.png -resize ${b}x${b} bitcoin${b}.png
convert squorum-1024x1024.png -resize ${b}x${b} bitcoin${b}.xpm
done
```

(See [Which icon sizes should my Windows application's icon include?
](https://stackoverflow.com/a/46053684) for a discussion of recommended sizes for supporting a variety of resolutions.)

Creating a Windows `ICO` format file is a matter of collating the resized images into a single resource:

```
icotool -c bitcoin*.png -o favicon.ico
```

Creating an OS X `ICNS` format file is a matter of collating the resized images into a single resource:

Create the png set by resizing `squorum-1024x1024.png` according to the following specification, in which `x2` means "twice the size" - if `icon_16x16.png` is 16 pixels x 16 pixels, the `x2` file will the same image resized to 32 pixels (16 * 2) x 32 pixels (16 * 2):

```
icon_16x16.png
icon_16x16@2x.png
icon_32x32.png
icon_32x32@2x.png
icon_128x128.png
icon_128x128@2x.png
icon_256x256.png
icon_256x256@2x.png
icon_512x512.png
icon_512x512@2x.png
```

