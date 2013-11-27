DESCRIPTION = "The pixel-manipulation library for X and cairo."
LICENSE = "MIT"

RECIPE_TYPES = "machine native"

DEPENDS = "libz libpng12"

inherit autotools-autoreconf library pkgconfig

SRC_URI = "http://cairographics.org/releases/${PN}-${PV}.tar.gz"

EXTRA_OECONF:>TARGET_OS_mingw32 = " --enable-static-testprogs"
