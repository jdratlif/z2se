SUBDIRS = source
EXTRA_DIST = apidocs docs/*.txt Doxyfile sav \
	vstudio/z2se.sln vstudio/z2se.vcxproj \
	vstudio/z2se.vcxproj.filters vstudio/z2se.vcxproj.user

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
	-find -iname "*.cpp" -exec touch {} \;
	-find -iname "*.hh" -exec touch {} \;
	-find -iname "*.xrc" -exec touch {} \;
