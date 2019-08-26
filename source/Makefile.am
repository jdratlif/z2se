.rc.o:
	windres -o $@ $<

AUTOMAKE_OPTIONS = subdir-objects
EXTRA_DIST = xrc/z2se.xrc res/palace.ico res/palace.xpm res/palace16x16.bmp \
             res/palace32x32.bmp

bin_PROGRAMS = z2se
z2se_SOURCES = GenApp.cc GenApp.hh \
	view/MainFrame.cc view/MainFrame.hh \
	view/FileDropTarget.cc view/FileDropTarget.hh \
	model/SaveSlot.cc model/SaveSlot.hh \
	model/SRAMFile.cc model/SRAMFile.hh

if WINDOWS
z2se_SOURCES += windows.rc
endif

