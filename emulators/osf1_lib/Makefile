# $NetBSD: Makefile,v 1.29 2021/05/24 19:52:10 wiz Exp $

DISTNAME=	netscape-4.7-3.alpha
PKGNAME=	osf1_lib-1.1
PKGREVISION=	11
CATEGORIES=	emulators
#MASTER_SITES=	ftp://digital.com/pub/alphaserver/archive/linuxalphatools/netscape/
MASTER_SITES=	ftp://ftp.hp.com/pub/alphaserver/archive/linuxalphatools/netscape/
EXTRACT_SUFX=	.rpm

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	http://www.support.compaq.com/alpha-tools/software/index.html
COMMENT=	DEC/Compaq OSF-1/Tru64 compatibility package for netscape

RESTRICTED=		COMPAQ Licensed Software
NO_SRC_ON_CDROM=	${RESTRICTED}
NO_BIN_ON_CDROM=	${RESTRICTED}
NO_SRC_ON_FTP=		${RESTRICTED}
NO_BIN_ON_FTP=		${RESTRICTED}

EMUL_PLATFORMS=		osf1-alpha
ONLY_FOR_PLATFORM=	NetBSD-*-alpha

OSF1_PKG=		yes
WRKSRC=			${WRKDIR}
BUILD_DIRS=		# empty

EMUL_PKG_FMT=		rpm
RPM2PKG_PREFIX=		${DESTDIR}${PREFIX}
RPM2PKG_SUBPREFIX=	${EMULSUBDIR}
RPM2PKG_STAGE=		do-install
RPMIGNOREPATH=		usr/bin usr/lib
RPM2PKG_STRIP=		0

.include "../../x11/libX11/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
