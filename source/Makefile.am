AUTOMAKE_OPTIONS = subdir-objects
CLEANFILES = res/z2se.cc
EXTRA_DIST = res/palace.ico res/palace.xpm res/windows.rc res/z2se.pjd \
	res/z2se.xrc

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

