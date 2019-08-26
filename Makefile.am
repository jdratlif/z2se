# $Id: Makefile.am,v 1.5 2008/12/17 06:20:46 jdratlif Exp $

SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt Doxyfile sav \
	vstudio/z2se/z2se.sln vstudio/z2se/z2se.vcproj

sav:
	-mkdir sav
	-cp source/res/Zelda\ II\ -\ The\ Adventure\ of\ Link\ \(U\).sav sav

.PHONY: allclean apidocs bundle touch

allclean: clean
	-rm -rf source/z2se.app
	-rm -rf apidocs
	-rm -f *.bz2
	-find -iname "*~" -exec rm -f {} \;

apidocs: Doxyfile
	@doxygen

bundle:
	-cd source && make z2se.app

touch:
	-find -iname "*.cc" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;

