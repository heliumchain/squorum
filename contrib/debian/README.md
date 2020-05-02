
Debian
====================
This directory contains files used to package squorumd/squorum-qt
for Debian-based Linux systems. If you compile squorumd/squorum-qt yourself, there are some useful files here.

## squorum: URI support ##


squorum-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install squorum-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your squorum-qt binary to `/usr/bin`
and the `../../share/pixmaps/squorum128.png` to `/usr/share/pixmaps`

squorum-qt.protocol (KDE)

