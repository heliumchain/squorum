
Debian
====================
This directory contains files used to package heliumd/helium-qt
for Debian-based Linux systems. If you compile heliumd/helium-qt yourself, there are some useful files here.

## helium: URI support ##


helium-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install helium-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your heliumqt binary to `/usr/bin`
and the `../../share/pixmaps/helium128.png` to `/usr/share/pixmaps`

helium-qt.protocol (KDE)

