DESCRIPTION = "ATK provides the set of accessibility interfaces that are implemented by other toolkits and applications."
LICENSE = "LGPL-2.1"

RECIPE_TYPES = "machine native"

DEPENDS = "libgthread libgobject libgmodule libgio native:glib-utils gtk-doc"

inherit autotools-autoreconf library pkgconfig

DEPENDS_${PN} += "${DEPENDS}"
FILES_${PN}-doc += "${datadir}/gtk-doc"
