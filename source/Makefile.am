# $Id: Makefile.am,v 1.10 2008/12/17 06:20:46 jdratlif Exp $

AUTOMAKE_OPTIONS = subdir-objects
CLEANFILES = res/z2se.cc
EXTRA_DIST = res/icon32x32.ico res/icon32x32.xpm res/Info.plist res/windows.rc \
	res/z2se.icns res/z2se.xrc

bin_PROGRAMS = z2se
z2se_SOURCES = GenApp.cc GenApp.hh \
	model/SaveSlot.cc model/SaveSlot.hh \
	model/SRAMFile.cc model/SRAMFile.hh \
	res/z2se.cc \
	view/FileDropTarget.cc view/FileDropTarget.hh \
	view/MainFrame.cc view/MainFrame.hh

if WINDOWS
z2se_SOURCES += res/windows.rc
endif

.rc.o:
	windres @WX_INCLUDES@ -o $@ $<

.xrc.cc:
	wxrc -c -o $@ $<

z2se.app: z2se res/z2se.icns res/Info.plist
	-mkdir z2se.app
	-mkdir z2se.app/Contents
	-mkdir z2se.app/Contents/MacOS
	-mkdir z2se.app/Contents/Resources
	cp z2se z2se.app/Contents/MacOS
	cp res/Info.plist z2se.app/Contents
	cp res/z2se.icns z2se.app/Contents/Resources
	echo -n 'APPL????' > z2se.app/Contents/PkgInfo

