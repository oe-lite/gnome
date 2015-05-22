SUMMARY = "Common scripts and macros to develop with GNOME or GNOME 2.0."
DESCRIPTION = "gnome-common is an extension to autoconf, automake and libtool for the GNOME environment and GNOME using applications. Included are gnome-autogen.sh and several macros to help in both GNOME and GNOME 2.0 source trees."
LICENSE = "GPL-2"

RECIPE_TYPES = "machine cross native"

inherit autotools-autoreconf pkgconfig
