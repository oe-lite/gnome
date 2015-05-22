DESCRIPTION = "GTK+ Integration for the Mac OS X desktop, like the menubar, dock and app bundles."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

COMPATIBLE_HOST_ARCHS = ".*darwin.*"

DEPENDS = "native:glib-utils gtk+"

inherit autotools library pkgconfig

DEPENDS_${PN} += "${DEPENDS}"

SRC_URI = "http://ftp.gnome.org/pub/GNOME/sources/gtk-mac-integration/2.0/${PN}-${PV}.tar.xz"

FILES_${PN}-locale = "${datadir}/strings"

do_compile[prefuncs] += "do_compile_clean"

do_compile_clean () {
  oe_runmake clean
}
