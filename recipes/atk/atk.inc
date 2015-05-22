SUMMARY = "ATK, Provides a set of interfaces for accessibility."
DESCRIPTION = "ATK provides the set of accessibility interfaces that are implemented by other toolkits and applications."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

inherit autotools-autoreconf library pkgconfig

DEPENDS += "glib-libgobject gnome-common-dev"
DEPENDS_${PN} += "libc libffi libglib libgobject libgthread libpcre libpthread"
RDEPENDS_${PN} += "libc libffi libglib libgobject libgthread libpcre libpthread"

FILES_${PN}-doc += "${datadir}/gtk-doc"
