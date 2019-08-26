EXTRA_DIST = apidocs docs/*.txt Doxyfile Info.plist PkgInfo \
	vc.net/z2se/z2se.sln vc.net/z2se/z2se.vcproj
SUBDIRS = source

.PHONY: allclean apidocs touch

allclean: clean
	-rm -rf apidocs
	-rm -f *.bz2 *.gz
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen

touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;

