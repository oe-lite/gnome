DESCRIPTION = "The pixel-manipulation library for X and cairo."
LICENSE = "MIT"

RECIPE_TYPES = "machine native"

DEPENDS = "zlib libpng12"

inherit autotools library pkgconfig

SRC_URI = "http://cairographics.org/releases/${PN}-${PV}.tar.gz"

EXTRA_OECONF = "--enable-static --enable-shared"
EXTRA_OECONF:>TARGET_OS_mingw32 = " --enable-static-testprogs"
