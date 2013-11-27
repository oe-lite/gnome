DESCRIPTION = "Cairo is a 2D graphics library with support for multiple output devices"
LICENSE = "GPLV2"

RECIPE_TYPES = "machine native"

DEPENDS = "libpng libfontconfig libglib libgthread libgobject libgmodule libgio pixman"
DEPENDS:>TARGET_OS_linux-gnu = " libX11 libXrender libxcb"

inherit autotools-autoreconf library pkgconfig

SRC_URI = "http://cairographics.org/releases/${PN}-${PV}.tar.gz"

EXTRA_OECONF:>TARGET_OS_linux-gnu = " --enable-xcb --enable-xlib-xcb"
EXTRA_OECONF:>TARGET_OS_darwin = " --enable-quartz=yes"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "cairo-trace"

FILES_${PN}-cairo-trace += "${libdir}/cairo/libcairo-trace*" 

DEPENDS_${PN} += "${DEPENDS}"
RDEPENDS_${PN} += "${DEPENDS}"
RDEPENDS_${PN}-dev += "libpng-dev libfontconfig-dev libglib-dev libgthread-dev libgobject-dev libgmodule-dev libgio-dev pixman-dev"

FILES_${PN}-doc += "${datadir}/gtk-doc"
