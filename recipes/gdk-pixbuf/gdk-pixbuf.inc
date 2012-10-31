DESCRIPTION = "GdkPixbuf is a library for image loading and manipulation."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

DEPENDS = "libgthread libgobject libgmodule libgio libpng libjpeg native:glib-utils ${DEPENDS_NATIVE}"
DEPENDS_NATIVE = "native:gdk-pixbuf-utils"
DEPENDS_NATIVE:native = ""

inherit autotools-autoreconf library pkgconfig

EXTRA_OECONF += " --disable-glibtest gio_can_sniff=yes --without-libtiff"
EXTRA_OECONF:>TARGET_OS_mingw32 = " lt_cv_deplibs_check_method='pass_all'"

PACKAGES += "${PN}-utils"
DEPENDS_${PN}-utils = "${PN}"
FILES_${PN}-utils += "${bindir}/gdk-pixbuf*"

DEPENDS_${PN} += "libgthread libgobject libgmodule libgio libpng libjpeg"
RDEPENDS_${PN} += "libgthread libgobject libgmodule libgio libpng libjpeg"
FILES_${PN} += "${libdir}/${GDKPIXBUF_LIBPATH}"
FILES_${PN} += "${libdir}/${GDKPIXBUF_LIBPATH}/loaders/*${HOST_LIBRARY_EXT}"
FILES_${PN}-dev += "${libdir}/${GDKPIXBUF_LIBPATH}/loaders"
FILES_${PN}-dev += "!${libdir}/${GDKPIXBUF_LIBPATH}/loaders/*${HOST_LIBRARY_EXT}"
FILES_${PN}-doc += "${datadir}/gtk-doc"

HOST_LIBRARY_EXT = ".so"
HOST_LIBRARY_EXT:HOST_OS_mingw32 = ".dll"

do_install[postfuncs] += "${DO_INSTALL_CACHE}"
DO_INSTALL_CACHE = ""
DO_INSTALL_CACHE:native = "do_install_cache"

GDKPIXBUF_LIBPATH = "gdk-pixbuf-2.0/2.10.0"

INSTALL_LD_LIBRARY_PATH = "LD_LIBRARY_PATH"
INSTALL_LD_LIBRARY_PATH:HOST_OS_darwin = "DYLD_LIBRARY_PATH"
INSTALL_GDK_PIXBUF_ROOT = "${STAGE_DIR}/native"
INSTALL_GDK_PIXBUF_ROOT:native = "${D}"
INSTALL_GDK_PIXBUF_LIB = "${INSTALL_GDK_PIXBUF_ROOT}/${stage_libdir}"
INSTALL_GDK_PIXBUF_LIB:native = "${INSTALL_GDK_PIXBUF_ROOT}/${libdir}"
INSTALL_GDK_PIXBUF_MODULEDIR = "${INSTALL_GDK_PIXBUF_LIB}/${GDKPIXBUF_LIBPATH}/loaders"
INSTALL_GDK_PIXBUF_MODULEDIR:native = "${INSTALL_GDK_PIXBUF_LIB}/${GDKPIXBUF_LIBPATH}/loaders"
INSTALL_GDK_PIXBUF_QUERY_LOADERS = "${INSTALL_GDK_PIXBUF_ROOT}/${stage_bindir}/gdk-pixbuf-query-loaders"
INSTALL_GDK_PIXBUF_QUERY_LOADERS:native = "${INSTALL_GDK_PIXBUF_ROOT}/${bindir}/gdk-pixbuf-query-loaders"

do_install_cache () {
	${INSTALL_LD_LIBRARY_PATH}=${INSTALL_GDK_PIXBUF_LIB}:$${INSTALL_LD_LIBRARY_PATH} \
	GDK_PIXBUF_MODULEDIR="${INSTALL_GDK_PIXBUF_MODULEDIR}" \
	${INSTALL_GDK_PIXBUF_QUERY_LOADERS} | \
	sed "s,${INSTALL_GDK_PIXBUF_ROOT}/,,g" > ${D}/${libdir}/${GDKPIXBUF_LIBPATH}/loaders.cache  
}

