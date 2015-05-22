DESCRIPTION = "GTK+ Integration for the Mac OS X desktop, like the menubar, dock and app bundles."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

COMPATIBLE_HOST_ARCHS = ".*darwin.*"

DEPENDS = "native:glib-utils gtk+"

inherit autotools-autoreconf library pkgconfig

DEPENDS_${PN} += "${DEPENDS}"

FILES_${PN}-locale = "${datadir}/strings"
