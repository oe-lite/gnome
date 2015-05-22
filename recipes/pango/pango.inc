DESCRIPTION = "Pango is the core text and font handling library used in GNOME applications."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

DEPENDS = "cairo native:glib-utils ${DEPENDS_NATIVE} libiconv"
DEPENDS:>HOST_KERNEL_linux = " libxrender"
DEPENDS_NATIVE = "native:pango-utils"
DEPENDS_NATIVE:native = "gtk-doc"

inherit autotools-autoreconf library c++ pkgconfig

require conf/fetch/gnome.conf
SRC_URI = "${GNOME_MIRROR}/${PN}/${@'.'.join('${PV}'.split('.')[:2])}/${PN}-${PV}.tar.gz"

PACKAGES += "${PN}-utils"

DEPENDS_${PN} += "${DEPENDS}"
DEPENDS_${PN}-utils = "${PN}"

FILES_${PN} += "${sysconfdir}/pango*"
FILES_${PN} += "${libdir}/${PANGO_LIBPATH}"
FILES_${PN} += "${libdir}/${PANGO_LIBPATH}/modules/*${HOST_LIBRARY_EXT}"
FILES_${PN}-dev += "${libdir}/${PANGO_LIBPATH}/modules"
FILES_${PN}-dev += "!${libdir}/${PANGO_LIBPATH}/modules/*${HOST_LIBRARY_EXT}"
FILES_${PN}-utils += "${bindir}/pango*"
DEPENDS_${PN}-utils += "libiconv"
RDEPENDS_${PN}-utils += "libiconv"
FILES_${PN}-doc += "${datadir}/gtk-doc"

HOST_LIBRARY_EXT = ".so"
HOST_LIBRARY_EXT:HOST_LIBC_mingw = ".dll"

do_install[postfuncs] += "${DO_INSTALL_CACHE}"
DO_INSTALL_CACHE = ""
DO_INSTALL_CACHE:native = "do_install_cache"

PANGO_LIBPATH = "pango/1.6.0"

INSTALL_LD_LIBRARY_PATH = "LD_LIBRARY_PATH"
INSTALL_LD_LIBRARY_PATH:HOST_KERNEL_darwin = "DYLD_LIBRARY_PATH"
INSTALL_PANGO_ROOT = "${D}"
INSTALL_PANGO_LIB = "${INSTALL_PANGO_ROOT}/${libdir}"
INSTALL_PANGO_QUERY_MODULES = "${INSTALL_PANGO_ROOT}/${bindir}/pango-querymodules"

do_install_cache () {
	printf "[Pango]\nModulesPath=${INSTALL_PANGO_LIB}/${PANGO_LIBPATH}/modules" > ${B}/pango.rc
	mkdir -p ${D}/${sysconfdir}/pango/
	${INSTALL_LD_LIBRARY_PATH}=${INSTALL_PANGO_LIB}:$${INSTALL_LD_LIBRARY_PATH} \
	PANGO_RC_FILE=${B}/pango.rc \
	${INSTALL_PANGO_QUERY_MODULES} | \
	sed "s,${INSTALL_PANGO_ROOT}/,,g" > ${D}/${sysconfdir}/pango/pango.modules
	rm ${B}/pango.rc 
}
