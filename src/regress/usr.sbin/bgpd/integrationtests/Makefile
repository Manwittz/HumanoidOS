# $OpenBSD: Makefile,v 1.21 2023/07/12 15:34:59 claudio Exp $

REGRESS_TARGETS	= 	network_statement md5 ovs mrt pftable \
			maxprefix maxprefixout maxcomm \
			as0 med eval_all policy l3vpn attr

BGPD ?=			/usr/sbin/bgpd

CLEANFILES +=		*.mrt *.out exabgp.*.conf *.log *.fifo \
			api-exabgp api-exabgp.d

api-exabgp: api-exabgp.c

network_statement:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

md5:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

ovs:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

policy:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

pftable:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

mrt:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11

maxprefix:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

maxprefixout:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

maxcomm:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

l3vpn:
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12 13 14

.if ! exists(/usr/local/bin/exabgp)
as0:
	# install exabgp from ports for additional tests
	@echo SKIPPED

med:
	# install exabgp from ports for additional tests
	@echo SKIPPED

eval_all:
	# install exabgp from ports for additional tests
	@echo SKIPPED

attr:
	# install exabgp from ports for additional tests
	@echo SKIPPED

.else

.SUFFIXES: .conf .in
.in.conf:
	sed -e 's|##OBJDIR##|${.OBJDIR}|g' \
	    ${.IMPSRC} > ${.TARGET} || \
	(rm ${.TARGET} && exit 1)

as0: api-exabgp exabgp.as0.test1.conf exabgp.as0.test2.conf
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

med: api-exabgp exabgp.med.conf
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

eval_all: api-exabgp exabgp.eval_all.conf
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

attr: api-exabgp exabgp.attr.conf
	${SUDO} ksh ${.CURDIR}/$@.sh ${BGPD} ${.CURDIR} 11 12 pair11 pair12

.endif

.include <bsd.regress.mk>
