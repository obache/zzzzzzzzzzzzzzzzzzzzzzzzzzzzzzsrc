# $NetBSD: Makefile,v 1.36 2021/05/24 19:54:57 wiz Exp $

DISTNAME=	YAML-Syck-1.34
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	1
CATEGORIES=	textproc perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=YAML/}

MAINTAINER=	bad@NetBSD.org
HOMEPAGE=	https://metacpan.org/release/AUDREYT/YAML-Syck-1.07
COMMENT=	Fast, lightweight YAML loader and dumper
LICENSE=	mit AND 2-clause-bsd

PERL5_PACKLIST=		auto/YAML/Syck/.packlist
PERL5_MODULE_TYPE=	Module::Install::Bundled

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
