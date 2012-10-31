DESCRIPTION = "GTK+, or the GIMP Toolkit, is a multi-platform toolkit for creating graphical user interface."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

DEPENDS = "${DEPENDS_NATIVE} cairo pango atk gdk-pixbuf native:gdk-pixbuf-utils"
DEPENDS_NATIVE = "native:gtk+-utils"
DEPENDS_NATIVE:native = ""
DEPENDS:>TARGET_OS_linux-gnu = " libX11 libXext libXrender"

inherit autotools-autoreconf library pkgconfig c++

EXTRA_OECONF:>TARGET_OS_darwin = " --with-gdktarget=quartz"

EXTRA_OECONF += " --disable-glibtest \
                  --disable-cups \
"
EXTRA_OECONF:>TARGET_OS_mingw32 = " lt_cv_deplibs_check_method='pass_all'"

DEPENDS_${PN} += "cairo pango atk gdk-pixbuf"
DEPENDS_${PN}-utils += "gdk-pixbuf"
RDEPENDS_${PN} += "cairo pango atk gdk-pixbuf"
RDEPENDS_${PN}-dev += "cairo-dev pango-dev atk-dev gdk-pixbuf-dev"

PACKAGES += "${PN}-utils"

GTK_LIBPATH = "gtk-2.0"

HOST_LIBRARY_EXT = ".so"
HOST_LIBRARY_EXT:HOST_OS_mingw32 = ".dll"

FILES_${PN} += "${sysconfdir}/gtk*"
FILES_${PN}-utils += "${bindir}/gtk*"
FILES_${PN}-doc += "${datadir}/gtk*"
FILES_${PN} += "${libdir}/${GTK_LIBPATH}/*${HOST_LIBRARY_EXT}"
FILES_${PN} += "${libdir}/${GTK_LIBPATH}/modules/*${HOST_LIBRARY_EXT}"
FILES_${PN} += "${libdir}/${GTK_LIBPATH}/2.10.0/engines/*${HOST_LIBRARY_EXT}"
FILES_${PN} += "${libdir}/${GTK_LIBPATH}/2.10.0/immodules/*${HOST_LIBRARY_EXT}"
FILES_${PN} += "${libdir}/${GTK_LIBPATH}/2.10.0/printbackends/*${HOST_LIBRARY_EXT}"
FILES_${PN} += "${datadir}/themes"
FILES_${PN}-dev += "${libdir}/${GTK_LIBPATH}/"
FILES_${PN}-dev += "!${libdir}/${GTK_LIBPATH}/modules/*${HOST_LIBRARY_EXT}"
FILES_${PN}-dev += "!${libdir}/${GTK_LIBPATH}/2.10.0/engines/*${HOST_LIBRARY_EXT}"
FILES_${PN}-dev += "!${libdir}/${GTK_LIBPATH}/2.10.0/immodules/*${HOST_LIBRARY_EXT}"
FILES_${PN}-dev += "!${libdir}/${GTK_LIBPATH}/2.10.0/printbackends/*${HOST_LIBRARY_EXT}"

GDKPIXBUF_LIBPATH = "gdk-pixbuf-2.0/2.10.0"
do_compile[prefuncs] += "do_compile_pre_cache"
do_compile[postfuncs] += "do_compile_post_cache"

export GDK_PIXBUF_MODULE_FILE = "${B}/loaders.cache" 

do_compile_pre_cache () {
	cat ${STAGE_DIR}/native/${stage_libdir}/${GDKPIXBUF_LIBPATH}/loaders.cache | \
	sed "s#/lib/${GDKPIXBUF_LIBPATH}#${STAGE_DIR}/native/${stage_libdir}/${GDKPIXBUF_LIBPATH}#g" > ${B}/loaders.cache
}

do_compile_post_cache () {
	rm ${B}/loaders.cache
}
