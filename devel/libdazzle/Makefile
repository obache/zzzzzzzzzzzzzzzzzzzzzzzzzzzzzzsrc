# $NetBSD: Makefile,v 1.14 2021/05/17 14:51:44 nia Exp $

DISTNAME=	libdazzle-3.38.0
PKGREVISION=	1
CATEGORIES=	devel gnome
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/libdazzle/${PKGVERSION_NOREV:R}/}
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	https://gitlab.gnome.org/GNOME/libdazzle
COMMENT=	Companion library to GObject and Gtk+
LICENSE=	gnu-gpl-v3

USE_TOOLS+=	pkg-config

PYTHON_FOR_BUILD_ONLY=	tool

PKGCONFIG_OVERRIDE_STAGE=	pre-install
PKGCONFIG_OVERRIDE+=		output/meson-private/libdazzle-1.0.pc

# Solaris munmap() uses caddr_t instead of void *
BUILDLINK_TRANSFORM.SunOS+=	rm:-Werror=incompatible-pointer-types

BUILDLINK_DEPMETHOD.gobject-introspection?=	build
.include "../../devel/gobject-introspection/buildlink3.mk"
.include "../../devel/meson/build.mk"
BUILDLINK_DEPMETHOD.vala?=	build
.include "../../lang/vala/buildlink3.mk"
.include "../../x11/gtk3/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
