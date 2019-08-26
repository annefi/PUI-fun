#
# File: recipes/makefile
#
# Description:
#   Makefile for Numerical Recipes in C++ version 2.11.
#
# Author(s):  Numerical Recipes in C++ (nr)
#             Jim Raines (jmr) University of Michigan Space Phys. Res. Lab
#
# Method:
#   
# Revision controlled by CVS:
# $Id:$
#
# Major Modification History:
#               nr    initial coding
#   09Nov2004   jmr   added changed library name, added NRTYPE, added dbg lib
#
#------------------------------------------------------------------------------

.SUFFIXES:
.SUFFIXES: .reslt .res .out .o .cpp
# Set the path and parameters below to the correct values when needed
export LOCAL=$(HOME)/ace
NRROOT=$(LOCAL)/nr_211/recipes_cpp
TNT=$(LOCAL)/tnt_122
NRTYPE=c++
VPATH=$(NRROOT)/demo/src:$(NRROOT)/recipes:$(NRROOT)/utils:$(NRROOT)/demo/responses
CC=gcc
CFLAGS= -I$(NRROOT)/utils -I. -I$(TNT)
NRDIFF=$(NRROOT)/utils/nrdiff.pl
NRANS=$(NRROOT)/demo/answers
NRDAT=$(NRROOT)/demo/data
NRLIBS=-lstdc++ -lm
.cpp.o: ; $(CC) $(CFLAGS) -c $<
.o.out: ; $(CC) $(CFLAGS) -o $@ $^ $(NRLIBS)

## allow command line option for adding debugging symbol info
## usage note: do 'make dbglib' rather than doing this define explicitly
ifdef DEBUG
  CFLAGS += -g -DDEBUG -Wall
  # CPPFLAGS will get this too, automatically, because of make's 
  # deferred expansion of variables (see 'info make' for details)
else
  # optimize if not debugging
  CFLAGS += -O3
endif

all : dat \
xairy.reslt \
xamebsa.reslt \
xamoeba.reslt \
xanneal.reslt \
xarcode.reslt \
xavevar.reslt \
xbalanc.reslt \
xbandec.reslt \
xbanmul.reslt \
xbcucof.reslt \
xbcuint.reslt \
xbeschb.reslt \
xbessi.reslt \
xbessi0.reslt \
xbessi1.reslt \
xbessik.reslt \
xbessj.reslt \
xbessj0.reslt \
xbessj1.reslt \
xbessjy.reslt \
xbessk.reslt \
xbessk0.reslt \
xbessk1.reslt \
xbessy.reslt \
xbessy0.reslt \
xbessy1.reslt \
xbeta.reslt \
xbetai.reslt \
xbico.reslt \
xbnldev.reslt \
xbrent.reslt \
xbroydn.reslt \
xbsstep.reslt \
xcaldat.reslt \
xchder.reslt \
xchebev.reslt \
xchebft.reslt \
xchebpc.reslt \
xchint.reslt \
xcholsl.reslt \
xchsone.reslt \
xchstwo.reslt \
xcisi.reslt \
xcntab1.reslt \
xcntab2.reslt \
xconvlv.reslt \
xcorrel.reslt \
xcosft1.reslt \
xcosft2.reslt \
xcovsrt.reslt \
xcrank.reslt \
xcyclic.reslt \
xdawson.reslt \
xdbrent.reslt \
xddpoly.reslt \
xdecchk.reslt \
xdf1dim.reslt \
xdfpmin.reslt \
xdfridr.reslt \
xdftint.reslt \
xdlinmin.reslt \
xeclass.reslt \
xeclazz.reslt \
xei.reslt \
xeigsrt.reslt \
xelle.reslt \
xellf.reslt \
xellpi.reslt \
xelmhes.reslt \
xerfcc.reslt \
xerff.reslt \
xerffc.reslt \
xeulsum.reslt \
xevlmem.reslt \
xexpdev.reslt \
xexpint.reslt \
xf1dim.reslt \
xfactln.reslt \
xfactrl.reslt \
xfasper.reslt \
xfgauss.reslt \
xfit.reslt \
xfitexy.reslt \
xfixrts.reslt \
xfleg.reslt \
xflmoon.reslt \
xfour1.reslt \
xfourfs.reslt \
xfourn.reslt \
xfpoly.reslt \
xfred2.reslt \
xfredin.reslt \
xfrenel.reslt \
xfrprmn.reslt \
xftest.reslt \
xgamdev.reslt \
xgammln.reslt \
xgammp.reslt \
xgammq.reslt \
xgasdev.reslt \
xgaucof.reslt \
xgauher.reslt \
xgaujac.reslt \
xgaulag.reslt \
xgauleg.reslt \
xgaussj.reslt \
xgcf.reslt \
xgolden.reslt \
xgser.reslt \
xhpsel.reslt \
xhpsort.reslt \
xhqr.reslt \
xhuffman.reslt \
xhunt.reslt \
xhypgeo.reslt \
xicrc.reslt \
xigray.reslt \
xindexx.reslt \
xirbit1.reslt \
xirbit2.reslt \
xjacobi.reslt \
xjulday.reslt \
xkendl1.reslt \
xkendl2.reslt \
xks2d1s.reslt \
xks2d2s.reslt \
xksone.reslt \
xkstwo.reslt \
xlaguer.reslt \
xlfit.reslt \
xlinbcg.reslt \
xlinmin.reslt \
xlocate.reslt \
xlubksb.reslt \
xludcmp.reslt \
xmachar.reslt \
xmedfit.reslt \
xmemcof.reslt \
xmgfas.reslt \
xmglin.reslt \
xmidpnt.reslt \
xmiser.reslt \
xmmid.reslt \
xmnbrak.reslt \
xmnewt.reslt \
xmppi.reslt \
xmoment.reslt \
xmprove.reslt \
xmrqcof.reslt \
xmrqmin.reslt \
xnewt.reslt \
xodeint.reslt \
xorthog.reslt \
xpade.reslt \
xpccheb.reslt \
xpcshft.reslt \
xpearsn.reslt \
xperiod.reslt \
xpiksr2.reslt \
xpiksrt.reslt \
xplgndr.reslt \
xpoidev.reslt \
xpolcoe.reslt \
xpolcof.reslt \
xpoldiv.reslt \
xpolin2.reslt \
xpolint.reslt \
xpowell.reslt \
xpredic.reslt \
xprobks.reslt \
xpsdes.reslt \
xpzextr.reslt \
xqgaus.reslt \
xqrdcmp.reslt \
xqromb.reslt \
xqromo.reslt \
xqroot.reslt \
xqrsolv.reslt \
xqrupdt.reslt \
xqsimp.reslt \
xqtrap.reslt \
xquad3d.reslt \
xran.reslt \
xran4.reslt \
xrank.reslt \
xratint.reslt \
xratlsq.reslt \
xrc.reslt \
xrd.reslt \
xrealft.reslt \
xrf.reslt \
xrj.reslt \
xrk4.reslt \
xrkdumb.reslt \
xrkqs.reslt \
xrlft3.reslt \
xrofunc.reslt \
xrtbis.reslt \
xrtflsp.reslt \
xrtnewt.reslt \
xrtsafe.reslt \
xrtsec.reslt \
xrzextr.reslt \
xsavgol.reslt \
xscrsho.reslt \
xselect.reslt \
xselip.reslt \
xshell.reslt \
xsimplx.reslt \
xsimpr.reslt \
xsinft.reslt \
xsncndn.reslt \
xsobseq.reslt \
xsor.reslt \
xsort.reslt \
xsort2.reslt \
xsort3.reslt \
xspctrm.reslt \
xspear.reslt \
xsphbes.reslt \
xsphfpt.reslt \
xsplie2.reslt \
xsplin2.reslt \
xspline.reslt \
xsplint.reslt \
xsprsax.reslt \
xsprsin.reslt \
xsprspm.reslt \
xsprstm.reslt \
xsprstp.reslt \
xsprstx.reslt \
xstifbs.reslt \
xstiff.reslt \
xstoerm.reslt \
xsvbksb.reslt \
xsvdcmp.reslt \
xsvdfit.reslt \
xsvdvar.reslt \
xtoeplz.reslt \
xtptest.reslt \
xtqli.reslt \
xtrapzd.reslt \
xtred2.reslt \
xtridag.reslt \
xttest.reslt \
xtutest.reslt \
xtwofft.reslt \
xvander.reslt \
xvegas.reslt \
xvoltra.reslt \
xwt1.reslt \
xwtn.reslt \
xzbrac.reslt \
xzbrak.reslt \
xzbrent.reslt \
xzrhqr.reslt \
xzriddr.reslt \
xzroots.reslt \
badluk.reslt \
fredex.reslt \
sfroid.reslt \
sphoot.reslt


xairy.out : xairy.o airy.o bessik.o bessjy.o beschb.o chebev.o
xamebsa.out : xamebsa.o amebsa.o amotsa.o ran1.o
xamoeba.out : xamoeba.o amoeba.o amotry.o bessj0.o
xanneal.out : xanneal.o anneal.o revcst.o reverse.o trncst.o trnspt.o metrop.o irbit1.o ran3.o
xarcode.out : xarcode.o arcode.o arcmak.o arcsum.o
xavevar.out : xavevar.o avevar.o gasdev.o ran1.o
xbalanc.out : xbalanc.o balanc.o
xbandec.out : xbandec.o banbks.o bandec.o banmul.o ran1.o
xbanmul.out : xbanmul.o banmul.o
xbcucof.out : xbcucof.o bcucof.o
xbcuint.out : xbcuint.o bcuint.o bcucof.o
xbeschb.out : xbeschb.o beschb.o chebev.o gammln.o
xbessi.out : xbessi.o bessi.o bessi0.o
xbessi0.out : xbessi0.o bessi0.o
xbessi1.out : xbessi1.o bessi1.o
xbessik.out : xbessik.o bessik.o beschb.o chebev.o
xbessj.out : xbessj.o bessj.o bessj0.o bessj1.o
xbessj0.out : xbessj0.o bessj0.o
xbessj1.out : xbessj1.o bessj1.o
xbessjy.out : xbessjy.o bessjy.o beschb.o chebev.o
xbessk.out : xbessk.o bessk.o bessi0.o bessi1.o bessk0.o bessk1.o
xbessk0.out : xbessk0.o bessk0.o bessi0.o
xbessk1.out : xbessk1.o bessk1.o bessi1.o
xbessy.out : xbessy.o bessy.o bessy1.o bessy0.o bessj1.o bessj0.o
xbessy0.out : xbessy0.o bessy0.o bessj0.o
xbessy1.out : xbessy1.o bessy1.o bessj1.o
xbeta.out : xbeta.o beta.o gammln.o
xbetai.out : xbetai.o betai.o betacf.o gammln.o
xbico.out : xbico.o bico.o factln.o gammln.o
xbnldev.out : xbnldev.o bnldev.o ran1.o gammln.o
xbrent.out : xbrent.o brent.o mnbrak.o bessj0.o bessj1.o
xbroydn.out : xbroydn.o broydn.o lnsrch.o qrdcmp.o qrupdt.o rotate.o rsolv.o fdjac.o fmin.o
xbsstep.out : xbsstep.o bsstep.o odeint.o mmid.o pzextr.o bessj0.o bessj1.o bessj.o
xcaldat.out : xcaldat.o caldat.o julday.o
xchder.out : xchder.o chder.o chebft.o chebev.o
xchebev.out : xchebev.o chebev.o chebft.o
xchebft.out : xchebft.o chebft.o
xchebpc.out : xchebpc.o chebpc.o chebft.o
xchint.out : xchint.o chint.o chebft.o chebev.o
xcholsl.out : xcholsl.o choldc.o cholsl.o
xchsone.out : xchsone.o chsone.o expdev.o gammq.o gcf.o gser.o ran1.o gammln.o
xchstwo.out : xchstwo.o chstwo.o expdev.o gammq.o gcf.o gser.o ran1.o gammln.o
xcisi.out : xcisi.o cisi.o
xcntab1.out : xcntab1.o cntab1.o gammq.o gcf.o gser.o gammln.o
xcntab2.out : xcntab2.o cntab2.o
xconvlv.out : xconvlv.o convlv.o realft.o four1.o
xcorrel.out : xcorrel.o correl.o realft.o four1.o
xcosft1.out : xcosft1.o cosft1.o realft.o four1.o
xcosft2.out : xcosft2.o cosft2.o realft.o four1.o
xcovsrt.out : xcovsrt.o covsrt.o
xcrank.out : xcrank.o crank.o sort2.o
xcyclic.out : xcyclic.o cyclic.o tridag.o lubksb.o ludcmp.o ran2.o
xdawson.out : xdawson.o dawson.o
xdbrent.out : xdbrent.o dbrent.o mnbrak.o bessj0.o bessj1.o
xddpoly.out : xddpoly.o ddpoly.o factrl.o gammln.o
xdecchk.out : xdecchk.o decchk.o
xdf1dim.out : xdf1dim.o df1dim.o scrsho.o
xdfpmin.out : xdfpmin.o dfpmin.o lnsrch.o
xdfridr.out : xdfridr.o dfridr.o
xdftint.out : xdftint.o dftint.o dftcor.o polint.o realft.o four1.o
xdlinmin.out : xdlinmin.o dlinmin.o dbrent.o f1dim.o df1dim.o mnbrak.o
xeclass.out : xeclass.o eclass.o
xeclazz.out : xeclazz.o eclazz.o
xei.out : xei.o ei.o
xeigsrt.out : xeigsrt.o eigsrt.o jacobi.o
xelle.out : xelle.o elle.o rf.o rd.o
xellf.out : xellf.o ellf.o rf.o
xellpi.out : xellpi.o ellpi.o rf.o rj.o rc.o
xelmhes.out : xelmhes.o elmhes.o balanc.o
xerfcc.out : xerfcc.o erfcc.o
xerff.out : xerff.o erff.o gammp.o gser.o gcf.o gammln.o
xerffc.out : xerffc.o erffc.o gammp.o gammq.o gser.o gcf.o gammln.o
xeulsum.out : xeulsum.o eulsum.o
xevlmem.out : xevlmem.o evlmem.o memcof.o
xexpdev.out : xexpdev.o expdev.o ran1.o
xexpint.out : xexpint.o expint.o
xf1dim.out : xf1dim.o f1dim.o scrsho.o
xfactln.out : xfactln.o factln.o gammln.o
xfactrl.out : xfactrl.o factrl.o gammln.o
xfasper.out : xfasper.o fasper.o spread.o realft.o four1.o avevar.o gasdev.o ran1.o
xfgauss.out : xfgauss.o fgauss.o
xfit.out : xfit.o fit.o gammq.o gammln.o gcf.o gser.o gasdev.o ran1.o
xfitexy.out : xfitexy.o fitexy.o chixy.o fit.o brent.o zbrent.o gammq.o gammln.o gcf.o gser.o mnbrak.o avevar.o gasdev.o ran1.o
xfixrts.out : xfixrts.o fixrts.o zroots.o laguer.o
xfleg.out : xfleg.o fleg.o plgndr.o
xflmoon.out : xflmoon.o flmoon.o caldat.o julday.o
xfour1.out : xfour1.o four1.o
xfourfs.out : xfourfs.o fourfs.o fourew.o fourn.o ran1.o
xfourn.out : xfourn.o fourn.o ran1.o
xfpoly.out : xfpoly.o fpoly.o
xfred2.out : xfred2.o fred2.o gauleg.o lubksb.o ludcmp.o
xfredin.out : xfredin.o fredin.o fred2.o gauleg.o lubksb.o ludcmp.o
xfrenel.out : xfrenel.o frenel.o
xfrprmn.out : xfrprmn.o frprmn.o linmin.o mnbrak.o brent.o f1dim.o bessj0.o bessj1.o
xftest.out : xftest.o ftest.o avevar.o betai.o gasdev.o betacf.o gammln.o ran1.o
xgamdev.out : xgamdev.o gamdev.o ran1.o
xgammln.out : xgammln.o gammln.o
xgammp.out : xgammp.o gammp.o gser.o gcf.o gammln.o
xgammq.out : xgammq.o gammq.o gser.o gcf.o gammln.o
xgasdev.out : xgasdev.o gasdev.o ran1.o
xgaucof.out : xgaucof.o gaucof.o tqli.o pythag.o eigsrt.o
xgauher.out : xgauher.o gauher.o
xgaujac.out : xgaujac.o gaujac.o gammln.o ellf.o rf.o
xgaulag.out : xgaulag.o gaulag.o gammln.o bessj0.o
xgauleg.out : xgauleg.o gauleg.o
xgaussj.out : xgaussj.o gaussj.o
xgcf.out : xgcf.o gcf.o gammln.o
xgolden.out : xgolden.o golden.o mnbrak.o bessj0.o bessj1.o
xgser.out : xgser.o gser.o gammln.o
xhpsel.out : xhpsel.o hpsel.o select.o sort.o
xhpsort.out : xhpsort.o hpsort.o
xhqr.out : xhqr.o hqr.o elmhes.o balanc.o
xhuffman.out : xhuffman.o hufmak.o hufapp.o hufenc.o hufdec.o
xhunt.out : xhunt.o hunt.o
xhypgeo.out : xhypgeo.o hypgeo.o hypdrv.o hypser.o odeint.o bsstep.o mmid.o pzextr.o
xicrc.out : xicrc.o icrc.o icrc1.o
xigray.out : xigray.o igray.o
xindexx.out : xindexx.o indexx.o
xirbit1.out : xirbit1.o irbit1.o
xirbit2.out : xirbit2.o irbit2.o
xjacobi.out : xjacobi.o jacobi.o
xjulday.out : xjulday.o julday.o
xkendl1.out : xkendl1.o kendl1.o erfcc.o ran0.o ran1.o ran2.o ran3.o ran4.o psdes.o
xkendl2.out : xkendl2.o kendl2.o irbit1.o irbit2.o erfcc.o
xks2d1s.out : xks2d1s.o ks2d1s.o quadct.o quadvl.o pearsn.o probks.o shell.o betai.o betacf.o gammln.o ran1.o
xks2d2s.out : xks2d2s.o ks2d2s.o quadct.o pearsn.o probks.o betai.o betacf.o gammln.o gasdev.o ran1.o
xksone.out : xksone.o ksone.o gasdev.o probks.o sort.o ran1.o erff.o erfcc.o gcf.o gammln.o gser.o gammp.o
xkstwo.out : xkstwo.o kstwo.o gasdev.o probks.o sort.o ran1.o
xlaguer.out : xlaguer.o laguer.o
xlfit.out : xlfit.o lfit.o covsrt.o gaussj.o gasdev.o ran1.o
xlinbcg.out : xlinbcg.o linbcg.o snrm.o atimes.o asolve.o sprstx.o sprsax.o
xlinmin.out : xlinmin.o linmin.o brent.o f1dim.o mnbrak.o
xlocate.out : xlocate.o locate.o
xlubksb.out : xlubksb.o lubksb.o ludcmp.o
xludcmp.out : xludcmp.o ludcmp.o
xmachar.out : xmachar.o machar.o
xmedfit.out : xmedfit.o medfit.o fit.o rofunc.o select.o gammq.o gammln.o gcf.o gser.o gasdev.o ran1.o
xmemcof.out : xmemcof.o memcof.o
xmgfas.out : xmgfas.o mgfas.o slvsm2.o relax2.o lop.o matadd.o matsub.o anorm2.o rstrct.o interp.o copy.o
xmglin.out : xmglin.o mglin.o addint.o slvsml.o relax.o resid.o rstrct.o interp.o copy.o
xmidpnt.out : xmidpnt.o midpnt.o
xmiser.out : xmiser.o miser.o ranpt.o ran1.o
xmmid.out : xmmid.o mmid.o bessj0.o bessj1.o bessj.o
xmnbrak.out : xmnbrak.o mnbrak.o bessj0.o
xmnewt.out : xmnewt.o mnewt.o ludcmp.o lubksb.o
xmoment.out : xmoment.o moment.o
mpdivtest.out : mpdivtest.o mpinv.o mpdiv.o mpmul.o mpops.o realft.o four1.o
xmppi.out : xmppi.o mppi.o mpsqrt.o mp2dfr.o mpinv.o mpdiv.o mpmul.o mpops.o realft.o four1.o
xmprove.out : xmprove.o lubksb.o ludcmp.o mprove.o ran3.o
xmrqcof.out : xmrqcof.o mrqcof.o fgauss.o gasdev.o ran1.o
xmrqmin.out : xmrqmin.o mrqmin.o mrqcof.o covsrt.o fgauss.o gaussj.o gasdev.o ran1.o
xnewt.out : xnewt.o newt.o fdjac.o fmin.o lnsrch.o ludcmp.o lubksb.o
xodeint.out : xodeint.o odeint.o rkqs.o rkck.o bessj0.o bessj1.o bessj.o
xorthog.out : xorthog.o orthog.o gaucof.o tqli.o pythag.o eigsrt.o
xpade.out : xpade.o pade.o ratval.o ludcmp.o lubksb.o mprove.o
xpccheb.out : xpccheb.o pccheb.o pcshft.o chebpc.o
xpcshft.out : xpcshft.o pcshft.o chebft.o chebpc.o
xpearsn.out : xpearsn.o pearsn.o betai.o betacf.o gammln.o
xperiod.out : xperiod.o period.o avevar.o gasdev.o ran1.o
xpiksr2.out : xpiksr2.o piksr2.o
xpiksrt.out : xpiksrt.o piksrt.o
xplgndr.out : xplgndr.o plgndr.o
xpoidev.out : xpoidev.o poidev.o ran1.o gammln.o
xpolcoe.out : xpolcoe.o polcoe.o
xpolcof.out : xpolcof.o polcof.o polint.o
xpoldiv.out : xpoldiv.o poldiv.o
xpolin2.out : xpolin2.o polin2.o polint.o
xpolint.out : xpolint.o polint.o
xpowell.out : xpowell.o powell.o linmin.o bessj0.o brent.o f1dim.o mnbrak.o
xpredic.out : xpredic.o predic.o fixrts.o memcof.o zroots.o laguer.o
xprobks.out : xprobks.o probks.o
xpsdes.out : xpsdes.o psdes.o
xpzextr.out : xpzextr.o pzextr.o
xqgaus.out : xqgaus.o qgaus.o
xqrdcmp.out : xqrdcmp.o qrdcmp.o
xqromb.out : xqromb.o qromb.o trapzd.o polint.o
xqromo.out : xqromo.o qromo.o midinf.o midsql.o midsqu.o midexp.o polint.o
xqroot.out : xqroot.o qroot.o poldiv.o
xqrsolv.out : xqrsolv.o qrsolv.o qrdcmp.o rsolv.o
xqrupdt.out : xqrupdt.o qrupdt.o qrdcmp.o rotate.o
xqsimp.out : xqsimp.o qsimp.o trapzd.o
xqtrap.out : xqtrap.o qtrap.o trapzd.o
xquad3d.out : xquad3d.o quad3d.o qgaus.o
xran.out : xran.o ran0.o ran1.o ran2.o ran3.o
xran4.out : xran4.o ran4.o psdes.o
xrank.out : xrank.o rank.o indexx.o
xratint.out : xratint.o ratint.o
xratlsq.out : xratlsq.o ratlsq.o ratval.o svbksb.o svdcmp.o pythag.o
xrc.out : xrc.o rc.o
xrd.out : xrd.o rd.o
xrealft.out : xrealft.o realft.o four1.o
xrf.out : xrf.o rf.o
xrj.out : xrj.o rj.o rc.o rf.o
xrk4.out : xrk4.o rk4.o bessj0.o bessj1.o bessj.o
xrkdumb.out : xrkdumb.o rkdumb.o rk4.o bessj0.o bessj1.o bessj.o
xrkqs.out : xrkqs.o rkqs.o rkck.o bessj0.o bessj1.o bessj.o
xrlft3.out : xrlft3.o rlft3.o fourn.o ran1.o
xrofunc.out : xrofunc.o rofunc.o select.o sort.o gasdev.o ran1.o
xrtbis.out : xrtbis.o rtbis.o zbrak.o bessj0.o
xrtflsp.out : xrtflsp.o rtflsp.o zbrak.o bessj0.o
xrtnewt.out : xrtnewt.o rtnewt.o zbrak.o bessj0.o bessj1.o
xrtsafe.out : xrtsafe.o rtsafe.o zbrak.o bessj0.o bessj1.o
xrtsec.out : xrtsec.o rtsec.o zbrak.o bessj0.o
xrzextr.out : xrzextr.o rzextr.o
xsavgol.out : xsavgol.o savgol.o ludcmp.o lubksb.o
xscrsho.out : xscrsho.o scrsho.o bessj0.o
xselect.out : xselect.o select.o selip.o shell.o
xselip.out : xselip.o selip.o shell.o
xshell.out : xshell.o shell.o
xsimplx.out : xsimplx.o simplx.o simp1.o simp2.o simp3.o
xsimpr.out : xsimpr.o simpr.o jacobn.o lubksb.o ludcmp.o
xsinft.out : xsinft.o sinft.o realft.o four1.o
xsncndn.out : xsncndn.o sncndn.o
xsobseq.out : xsobseq.o sobseq.o
xsor.out : xsor.o sor.o
xsort.out : xsort.o sort.o
xsort2.out : xsort2.o sort2.o
xsort3.out : xsort3.o sort3.o indexx.o
xspctrm.out : xspctrm.o spctrm.o four1.o
xspear.out : xspear.o spear.o betai.o betacf.o erfcc.o crank.o sort2.o gammln.o
xsphbes.out : xsphbes.o sphbes.o bessjy.o beschb.o chebev.o
xsphfpt.out : xsphfpt.o sphfpt.o shootf.o odeint.o rkqs.o rkck.o newt.o fdjac.o fmin.o lnsrch.o lubksb.o ludcmp.o
xsplie2.out : xsplie2.o splie2.o spline.o
xsplin2.out : xsplin2.o splie2.o splin2.o spline.o splint.o
xspline.out : xspline.o spline.o
xsplint.out : xsplint.o spline.o splint.o
xsprsax.out : xsprsax.o sprsax.o sprsin.o
xsprsin.out : xsprsin.o sprsin.o
xsprspm.out : xsprspm.o sprspm.o sprstp.o sprsin.o indexx.o
xsprstm.out : xsprstm.o sprstm.o sprstp.o sprsin.o indexx.o
xsprstp.out : xsprstp.o sprstp.o sprsin.o indexx.o
xsprstx.out : xsprstx.o sprstx.o sprsin.o
xstifbs.out : xstifbs.o stifbs.o simpr.o pzextr.o jacobn.o odeint.o lubksb.o ludcmp.o
xstiff.out : xstiff.o stiff.o jacobn.o odeint.o lubksb.o ludcmp.o
xstoerm.out : xstoerm.o stoerm.o
xsvbksb.out : xsvbksb.o svbksb.o svdcmp.o pythag.o
xsvdcmp.out : xsvdcmp.o svdcmp.o pythag.o
xsvdfit.out : xsvdfit.o svdfit.o svdvar.o fpoly.o fleg.o svdcmp.o pythag.o svbksb.o gasdev.o ran1.o
xsvdvar.out : xsvdvar.o svdvar.o
xtoeplz.out : xtoeplz.o toeplz.o
xtptest.out : xtptest.o tptest.o avevar.o betai.o gasdev.o betacf.o gammln.o ran1.o
xtqli.out : xtqli.o tqli.o pythag.o tred2.o
xtrapzd.out : xtrapzd.o trapzd.o
xtred2.out : xtred2.o tred2.o
xtridag.out : xtridag.o tridag.o
xttest.out : xttest.o ttest.o avevar.o betai.o gasdev.o betacf.o gammln.o ran1.o
xtutest.out : xtutest.o tutest.o avevar.o betai.o gasdev.o betacf.o gammln.o ran1.o
xtwofft.out : xtwofft.o twofft.o four1.o
xvander.out : xvander.o vander.o
xvegas.out : xvegas.o vegas.o rebin.o ran2.o
xvoltra.out : xvoltra.o voltra.o lubksb.o ludcmp.o
xwt1.out : xwt1.o wt1.o pwtset.o pwt.o daub4.o select.o
xwtn.out : xwtn.o wtn.o pwtset.o pwt.o
xzbrac.out : xzbrac.o zbrac.o bessj0.o
xzbrak.out : xzbrak.o zbrak.o bessj0.o
xzbrent.out : xzbrent.o zbrent.o zbrak.o bessj0.o
xzrhqr.out : xzrhqr.o zrhqr.o balanc.o hqr.o
xzriddr.out : xzriddr.o zriddr.o zbrak.o bessj0.o
xzroots.out : xzroots.o zroots.o laguer.o
badluk.out : badluk.o flmoon.o julday.o
fredex.out : fredex.o quadmx.o kermom.o wwghts.o lubksb.o ludcmp.o
sfroid.out : sfroid.o solvde.o plgndr.o bksub.o difeq.o pinvs.o red.o
sphoot.out : sphoot.o shoot.o odeint.o rkqs.o rkck.o newt.o fdjac.o fmin.o lnsrch.o lubksb.o ludcmp.o

# Recipes dependencies - NR routines only
addint.o : addint.cpp nr.h
airy.o : airy.cpp nr.h
amebsa.o : amebsa.cpp nr.h
amoeba.o : amoeba.cpp nr.h
amotry.o : amotry.cpp nr.h
amotsa.o : amotsa.cpp nr.h
anneal.o : anneal.cpp nr.h
anorm2.o : anorm2.cpp nr.h
arcmak.o : arcmak.cpp nr.h
arcode.o : arcode.cpp 
arcsum.o : arcsum.cpp nr.h
asolve.o : asolve.cpp nr.h
atimes.o : atimes.cpp nr.h
avevar.o : avevar.cpp nr.h
badluk.o : badluk.cpp nr.h
balanc.o : balanc.cpp nr.h
banbks.o : banbks.cpp nr.h
bandec.o : bandec.cpp nr.h
banmul.o : banmul.cpp nr.h
bcucof.o : bcucof.cpp nr.h
bcuint.o : bcuint.cpp nr.h
beschb.o : beschb.cpp nr.h
bessi.o : bessi.cpp 
bessi0.o : bessi0.cpp nr.h
bessi1.o : bessi1.cpp nr.h
bessik.o : bessik.cpp 
bessj.o : bessj.cpp 
bessj0.o : bessj0.cpp nr.h
bessj1.o : bessj1.cpp nr.h
bessjy.o : bessjy.cpp nr.h
bessk.o : bessk.cpp 
bessk0.o : bessk0.cpp nr.h
bessk1.o : bessk1.cpp nr.h
bessy.o : bessy.cpp 
bessy0.o : bessy0.cpp nr.h
bessy1.o : bessy1.cpp nr.h
beta.o : beta.cpp nr.h
betacf.o : betacf.cpp 
betai.o : betai.cpp 
bico.o : bico.cpp nr.h
bksub.o : bksub.cpp nr.h
bnldev.o : bnldev.cpp nr.h
brent.o : brent.cpp nr.h
broydn.o : broydn.cpp nr.h
bsstep.o : bsstep.cpp nr.h
caldat.o : caldat.cpp nr.h
chder.o : chder.cpp nr.h
chebev.o : chebev.cpp 
chebft.o : chebft.cpp nr.h
chebpc.o : chebpc.cpp nr.h
chint.o : chint.cpp nr.h
chixy.o : chixy.cpp nr.h
choldc.o : choldc.cpp 
cholsl.o : cholsl.cpp nr.h
chsone.o : chsone.cpp 
chstwo.o : chstwo.cpp nr.h
cisi.o : cisi.cpp nr.h
cntab1.o : cntab1.cpp nr.h
cntab2.o : cntab2.cpp nr.h
convlv.o : convlv.cpp nr.h
copy.o : copy.cpp nr.h
correl.o : correl.cpp nr.h
cosft1.o : cosft1.cpp nr.h
cosft2.o : cosft2.cpp nr.h
covsrt.o : covsrt.cpp nr.h
crank.o : crank.cpp nr.h
cyclic.o : cyclic.cpp nr.h
daub4.o : daub4.cpp nr.h
dawson.o : dawson.cpp nr.h
dbrent.o : dbrent.cpp nr.h
ddpoly.o : ddpoly.cpp nr.h
decchk.o : decchk.cpp nr.h
df1dim.o : df1dim.cpp nr.h
dfpmin.o : dfpmin.cpp nr.h
dfridr.o : dfridr.cpp nr.h
dftcor.o : dftcor.cpp 
dftint.o : dftint.cpp nr.h
difeq.o : difeq.cpp nr.h
dlinmin.o : dlinmin.cpp nr.h
eclass.o : eclass.cpp nr.h
eclazz.o : eclazz.cpp nr.h
ei.o : ei.cpp 
eigsrt.o : eigsrt.cpp nr.h
elle.o : elle.cpp nr.h
ellf.o : ellf.cpp nr.h
ellpi.o : ellpi.cpp nr.h
elmhes.o : elmhes.cpp nr.h
erfcc.o : erfcc.cpp nr.h
erff.o : erff.cpp nr.h
erffc.o : erffc.cpp nr.h
eulsum.o : eulsum.cpp nr.h
evlmem.o : evlmem.cpp nr.h
expdev.o : expdev.cpp nr.h
expint.o : expint.cpp 
f1dim.o : f1dim.cpp nr.h
factln.o : factln.cpp 
factrl.o : factrl.cpp 
fasper.o : fasper.cpp nr.h
fdjac.o : fdjac.cpp nr.h
fgauss.o : fgauss.cpp nr.h
fit.o : fit.cpp nr.h
fitexy.o : fitexy.cpp nr.h
fixrts.o : fixrts.cpp nr.h
fleg.o : fleg.cpp nr.h
flmoon.o : flmoon.cpp 
fmin.o : fmin.cpp nr.h
four1.o : four1.cpp nr.h
fourew.o : fourew.cpp nr.h
fourfs.o : fourfs.cpp nr.h
fourn.o : fourn.cpp nr.h
fpoly.o : fpoly.cpp nr.h
fred2.o : fred2.cpp nr.h
fredex.o : fredex.cpp nr.h
fredin.o : fredin.cpp nr.h
frenel.o : frenel.cpp nr.h
frprmn.o : frprmn.cpp nr.h
ftest.o : ftest.cpp nr.h
gamdev.o : gamdev.cpp 
gammln.o : gammln.cpp nr.h
gammp.o : gammp.cpp 
gammq.o : gammq.cpp 
gasdev.o : gasdev.cpp nr.h
gaucof.o : gaucof.cpp nr.h
gauher.o : gauher.cpp 
gaujac.o : gaujac.cpp 
gaulag.o : gaulag.cpp 
gauleg.o : gauleg.cpp nr.h
gaussj.o : gaussj.cpp nr.h
gcf.o : gcf.cpp 
golden.o : golden.cpp nr.h
gser.o : gser.cpp 
hpsel.o : hpsel.cpp 
hpsort.o : hpsort.cpp nr.h
hqr.o : hqr.cpp nr.h
hufapp.o : hufapp.cpp nr.h
hufdec.o : hufdec.cpp nr.h
hufenc.o : hufenc.cpp 
hufmak.o : hufmak.cpp nr.h
hunt.o : hunt.cpp nr.h
hypdrv.o : hypdrv.cpp nr.h
hypgeo.o : hypgeo.cpp nr.h
hypser.o : hypser.cpp nr.h
icrc.o : icrc.cpp nr.h
icrc1.o : icrc1.cpp nr.h
igray.o : igray.cpp nr.h
indexx.o : indexx.cpp nr.h
interp.o : interp.cpp nr.h
irbit1.o : irbit1.cpp nr.h
irbit2.o : irbit2.cpp nr.h
jacobi.o : jacobi.cpp nr.h
jacobn.o : jacobn.cpp nr.h
julday.o : julday.cpp 
kendl1.o : kendl1.cpp nr.h
kendl2.o : kendl2.cpp nr.h
kermom.o : kermom.cpp nr.h
ks2d1s.o : ks2d1s.cpp nr.h
ks2d2s.o : ks2d2s.cpp nr.h
ksone.o : ksone.cpp nr.h
kstwo.o : kstwo.cpp nr.h
laguer.o : laguer.cpp nr.h
lfit.o : lfit.cpp nr.h
linbcg.o : linbcg.cpp nr.h
linmin.o : linmin.cpp nr.h
lnsrch.o : lnsrch.cpp nr.h
locate.o : locate.cpp nr.h
lop.o : lop.cpp nr.h
lubksb.o : lubksb.cpp nr.h
ludcmp.o : ludcmp.cpp nr.h
machar.o : machar.cpp nr.h
matadd.o : matadd.cpp nr.h
matsub.o : matsub.cpp nr.h
medfit.o : medfit.cpp nr.h
memcof.o : memcof.cpp nr.h
metrop.o : metrop.cpp nr.h
mgfas.o : mgfas.cpp nr.h
mglin.o : mglin.cpp nr.h
midexp.o : midexp.cpp nr.h
midinf.o : midinf.cpp nr.h
midpnt.o : midpnt.cpp nr.h
midsql.o : midsql.cpp nr.h
midsqu.o : midsqu.cpp nr.h
miser.o : miser.cpp nr.h
mmid.o : mmid.cpp nr.h
mnbrak.o : mnbrak.cpp nr.h
mnewt.o : mnewt.cpp nr.h
moment.o : moment.cpp 
mp2dfr.o : mp2dfr.cpp nr.h
mpdiv.o : mpdiv.cpp nr.h
mpinv.o : mpinv.cpp nr.h
mpmul.o : mpmul.cpp nr.h
mpops.o : mpops.cpp nr.h
mppi.o : mppi.cpp nr.h
mprove.o : mprove.cpp nr.h
mpsqrt.o : mpsqrt.cpp nr.h
mrqcof.o : mrqcof.cpp nr.h
mrqmin.o : mrqmin.cpp nr.h
newt.o : newt.cpp nr.h
odeint.o : odeint.cpp nr.h
orthog.o : orthog.cpp nr.h
pade.o : pade.cpp nr.h
pccheb.o : pccheb.cpp nr.h
pcshft.o : pcshft.cpp nr.h
pearsn.o : pearsn.cpp nr.h
period.o : period.cpp nr.h
piksr2.o : piksr2.cpp nr.h
piksrt.o : piksrt.cpp nr.h
pinvs.o : pinvs.cpp nr.h
plgndr.o : plgndr.cpp 
poidev.o : poidev.cpp nr.h
polcoe.o : polcoe.cpp nr.h
polcof.o : polcof.cpp nr.h
poldiv.o : poldiv.cpp nr.h
polin2.o : polin2.cpp nr.h
polint.o : polint.cpp nr.h
powell.o : powell.cpp nr.h
predic.o : predic.cpp nr.h
probks.o : probks.cpp nr.h
psdes.o : psdes.cpp nr.h
pwt.o : pwt.cpp nr.h
pwtset.o : pwtset.cpp 
pythag.o : pythag.cpp nr.h
pzextr.o : pzextr.cpp nr.h
qgaus.o : qgaus.cpp nr.h
qrdcmp.o : qrdcmp.cpp nr.h
qromb.o : qromb.cpp 
qromo.o : qromo.cpp 
qroot.o : qroot.cpp nr.h
qrsolv.o : qrsolv.cpp nr.h
qrupdt.o : qrupdt.cpp nr.h
qsimp.o : qsimp.cpp 
qtrap.o : qtrap.cpp 
quad3d.o : quad3d.cpp nr.h
quadct.o : quadct.cpp nr.h
quadmx.o : quadmx.cpp nr.h
quadvl.o : quadvl.cpp nr.h
ran0.o : ran0.cpp nr.h
ran1.o : ran1.cpp nr.h
ran2.o : ran2.cpp nr.h
ran3.o : ran3.cpp nr.h
ran4.o : ran4.cpp nr.h
rank.o : rank.cpp nr.h
ranpt.o : ranpt.cpp nr.h
ratint.o : ratint.cpp nr.h
ratlsq.o : ratlsq.cpp nr.h
ratval.o : ratval.cpp nr.h
rc.o : rc.cpp nr.h
rd.o : rd.cpp nr.h
realft.o : realft.cpp nr.h
rebin.o : rebin.cpp nr.h
red.o : red.cpp nr.h
relax.o : relax.cpp nr.h
relax2.o : relax2.cpp nr.h
resid.o : resid.cpp nr.h
revcst.o : revcst.cpp nr.h
reverse.o : reverse.cpp nr.h
rf.o : rf.cpp nr.h
rj.o : rj.cpp nr.h
rk4.o : rk4.cpp nr.h
rkck.o : rkck.cpp nr.h
rkdumb.o : rkdumb.cpp nr.h
rkqs.o : rkqs.cpp nr.h
rlft3.o : rlft3.cpp 
rlftfrag.o : rlftfrag.cpp nr.h
rofunc.o : rofunc.cpp nr.h
rotate.o : rotate.cpp nr.h
rsolv.o : rsolv.cpp nr.h
rstrct.o : rstrct.cpp nr.h
rtbis.o : rtbis.cpp 
rtflsp.o : rtflsp.cpp 
rtnewt.o : rtnewt.cpp 
rtsafe.o : rtsafe.cpp 
rtsec.o : rtsec.cpp 
rzextr.o : rzextr.cpp nr.h
savgol.o : savgol.cpp nr.h
scrsho.o : scrsho.cpp nr.h
select.o : select.cpp nr.h
selip.o : selip.cpp nr.h
sfroid.o : sfroid.cpp nr.h
shell.o : shell.cpp nr.h
shoot.o : shoot.cpp nr.h
shootf.o : shootf.cpp nr.h
simp1.o : simp1.cpp nr.h
simp2.o : simp2.cpp nr.h
simp3.o : simp3.cpp nr.h
simplx.o : simplx.cpp nr.h
simpr.o : simpr.cpp nr.h
sinft.o : sinft.cpp nr.h
slvsm2.o : slvsm2.cpp nr.h
slvsml.o : slvsml.cpp nr.h
sncndn.o : sncndn.cpp nr.h
snrm.o : snrm.cpp nr.h
sobseq.o : sobseq.cpp nr.h
solvde.o : solvde.cpp nr.h
sor.o : sor.cpp 
sort.o : sort.cpp nr.h
sort2.o : sort2.cpp nr.h
sort3.o : sort3.cpp nr.h
spctrm.o : spctrm.cpp nr.h
spear.o : spear.cpp nr.h
sphbes.o : sphbes.cpp 
sphfpt.o : sphfpt.cpp nr.h
sphoot.o : sphoot.cpp nr.h
splie2.o : splie2.cpp nr.h
splin2.o : splin2.cpp nr.h
spline.o : spline.cpp nr.h
splint.o : splint.cpp 
spread.o : spread.cpp nr.h
sprsax.o : sprsax.cpp 
sprsin.o : sprsin.cpp 
sprspm.o : sprspm.cpp 
sprstm.o : sprstm.cpp 
sprstp.o : sprstp.cpp nr.h
sprstx.o : sprstx.cpp 
stifbs.o : stifbs.cpp nr.h
stiff.o : stiff.cpp nr.h
stoerm.o : stoerm.cpp nr.h
svbksb.o : svbksb.cpp nr.h
svdcmp.o : svdcmp.cpp nr.h
svdfit.o : svdfit.cpp nr.h
svdvar.o : svdvar.cpp nr.h
toeplz.o : toeplz.cpp nr.h
tptest.o : tptest.cpp nr.h
tqli.o : tqli.cpp nr.h
trapzd.o : trapzd.cpp nr.h
tred2.o : tred2.cpp nr.h
tridag.o : tridag.cpp nr.h
trncst.o : trncst.cpp nr.h
trnspt.o : trnspt.cpp nr.h
ttest.o : ttest.cpp nr.h
tutest.o : tutest.cpp nr.h
twofft.o : twofft.cpp nr.h
vander.o : vander.cpp nr.h
vegas.o : vegas.cpp nr.h
voltra.o : voltra.cpp nr.h
wt1.o : wt1.cpp nr.h
wtn.o : wtn.cpp nr.h
wwghts.o : wwghts.cpp nr.h
zbrac.o : zbrac.cpp 
zbrak.o : zbrak.cpp nr.h
zbrent.o : zbrent.cpp nr.h
zrhqr.o : zrhqr.cpp nr.h
zriddr.o : zriddr.cpp nr.h
zroots.o : zroots.cpp nr.h


# Driver dependencies - NR routines only
xairy.o : xairy.cpp nr.h
xamebsa.o : xamebsa.cpp nr.h
xamoeba.o : xamoeba.cpp nr.h
xanneal.o : xanneal.cpp nr.h
xarcode.o : xarcode.cpp nr.h
xavevar.o : xavevar.cpp nr.h
xbalanc.o : xbalanc.cpp nr.h
xbandec.o : xbandec.cpp nr.h
xbanmul.o : xbanmul.cpp nr.h
xbcucof.o : xbcucof.cpp nr.h
xbcuint.o : xbcuint.cpp nr.h
xbeschb.o : xbeschb.cpp nr.h
xbessi.o : xbessi.cpp nr.h
xbessi0.o : xbessi0.cpp nr.h
xbessi1.o : xbessi1.cpp nr.h
xbessik.o : xbessik.cpp nr.h
xbessj.o : xbessj.cpp nr.h
xbessj0.o : xbessj0.cpp nr.h
xbessj1.o : xbessj1.cpp nr.h
xbessjy.o : xbessjy.cpp nr.h
xbessk.o : xbessk.cpp nr.h
xbessk0.o : xbessk0.cpp nr.h
xbessk1.o : xbessk1.cpp nr.h
xbessy.o : xbessy.cpp nr.h
xbessy0.o : xbessy0.cpp nr.h
xbessy1.o : xbessy1.cpp nr.h
xbeta.o : xbeta.cpp nr.h
xbetai.o : xbetai.cpp nr.h
xbico.o : xbico.cpp nr.h
xbnldev.o : xbnldev.cpp nr.h
xbrent.o : xbrent.cpp nr.h
xbroydn.o : xbroydn.cpp nr.h
xbsstep.o : xbsstep.cpp nr.h
xcaldat.o : xcaldat.cpp nr.h
xchder.o : xchder.cpp nr.h
xchebev.o : xchebev.cpp nr.h
xchebft.o : xchebft.cpp nr.h
xchebpc.o : xchebpc.cpp nr.h
xchint.o : xchint.cpp nr.h
xcholsl.o : xcholsl.cpp nr.h
xchsone.o : xchsone.cpp nr.h
xchstwo.o : xchstwo.cpp nr.h
xcisi.o : xcisi.cpp nr.h
xcntab1.o : xcntab1.cpp nr.h
xcntab2.o : xcntab2.cpp nr.h
xconvlv.o : xconvlv.cpp nr.h
xcorrel.o : xcorrel.cpp nr.h
xcosft1.o : xcosft1.cpp nr.h
xcosft2.o : xcosft2.cpp nr.h
xcovsrt.o : xcovsrt.cpp nr.h
xcrank.o : xcrank.cpp nr.h
xcyclic.o : xcyclic.cpp nr.h
xdawson.o : xdawson.cpp nr.h
xdbrent.o : xdbrent.cpp nr.h
xddpoly.o : xddpoly.cpp nr.h
xdecchk.o : xdecchk.cpp nr.h
xdf1dim.o : xdf1dim.cpp nr.h
xdfpmin.o : xdfpmin.cpp nr.h
xdfridr.o : xdfridr.cpp nr.h
xdftint.o : xdftint.cpp nr.h
xdlinmin.o : xdlinmin.cpp nr.h
xeclass.o : xeclass.cpp nr.h
xeclazz.o : xeclazz.cpp nr.h
xei.o : xei.cpp nr.h
xeigsrt.o : xeigsrt.cpp nr.h
xelle.o : xelle.cpp nr.h
xellf.o : xellf.cpp nr.h
xellpi.o : xellpi.cpp nr.h
xelmhes.o : xelmhes.cpp nr.h
xerfcc.o : xerfcc.cpp nr.h
xerff.o : xerff.cpp nr.h
xerffc.o : xerffc.cpp nr.h
xeulsum.o : xeulsum.cpp nr.h
xevlmem.o : xevlmem.cpp nr.h
xexpdev.o : xexpdev.cpp nr.h
xexpint.o : xexpint.cpp nr.h
xf1dim.o : xf1dim.cpp nr.h
xfactln.o : xfactln.cpp nr.h
xfactrl.o : xfactrl.cpp nr.h
xfasper.o : xfasper.cpp nr.h
xfgauss.o : xfgauss.cpp nr.h
xfit.o : xfit.cpp nr.h
xfitexy.o : xfitexy.cpp nr.h
xfixrts.o : xfixrts.cpp nr.h
xfleg.o : xfleg.cpp nr.h
xflmoon.o : xflmoon.cpp nr.h
xfour1.o : xfour1.cpp nr.h
xfourfs.o : xfourfs.cpp nr.h
xfourn.o : xfourn.cpp nr.h
xfpoly.o : xfpoly.cpp nr.h
xfred2.o : xfred2.cpp nr.h
xfredin.o : xfredin.cpp nr.h
xfrenel.o : xfrenel.cpp nr.h
xfrprmn.o : xfrprmn.cpp nr.h
xftest.o : xftest.cpp nr.h
xgamdev.o : xgamdev.cpp nr.h
xgammln.o : xgammln.cpp nr.h
xgammp.o : xgammp.cpp nr.h
xgammq.o : xgammq.cpp nr.h
xgasdev.o : xgasdev.cpp nr.h
xgaucof.o : xgaucof.cpp nr.h
xgauher.o : xgauher.cpp nr.h
xgaujac.o : xgaujac.cpp nr.h
xgaulag.o : xgaulag.cpp nr.h
xgauleg.o : xgauleg.cpp nr.h
xgaussj.o : xgaussj.cpp nr.h
xgcf.o : xgcf.cpp nr.h
xgolden.o : xgolden.cpp nr.h
xgser.o : xgser.cpp nr.h
xhpsel.o : xhpsel.cpp nr.h
xhpsort.o : xhpsort.cpp nr.h
xhqr.o : xhqr.cpp nr.h
xhuffman.o : xhuffman.cpp nr.h
xhunt.o : xhunt.cpp nr.h
xhypgeo.o : xhypgeo.cpp nr.h
xicrc.o : xicrc.cpp nr.h
xigray.o : xigray.cpp nr.h
xindexx.o : xindexx.cpp nr.h
xirbit1.o : xirbit1.cpp nr.h
xirbit2.o : xirbit2.cpp nr.h
xjacobi.o : xjacobi.cpp nr.h
xjulday.o : xjulday.cpp nr.h
xkendl1.o : xkendl1.cpp nr.h
xkendl2.o : xkendl2.cpp nr.h
xks2d1s.o : xks2d1s.cpp nr.h
xks2d2s.o : xks2d2s.cpp nr.h
xksone.o : xksone.cpp nr.h
xkstwo.o : xkstwo.cpp nr.h
xlaguer.o : xlaguer.cpp nr.h
xlfit.o : xlfit.cpp nr.h
xlinbcg.o : xlinbcg.cpp nr.h
xlinmin.o : xlinmin.cpp nr.h
xlocate.o : xlocate.cpp nr.h
xlubksb.o : xlubksb.cpp nr.h
xludcmp.o : xludcmp.cpp nr.h
xmachar.o : xmachar.cpp nr.h
xmedfit.o : xmedfit.cpp nr.h
xmemcof.o : xmemcof.cpp nr.h
xmgfas.o : xmgfas.cpp nr.h
xmglin.o : xmglin.cpp nr.h
xmidpnt.o : xmidpnt.cpp nr.h
xmiser.o : xmiser.cpp nr.h
xmmid.o : xmmid.cpp nr.h
xmnbrak.o : xmnbrak.cpp nr.h
xmnewt.o : xmnewt.cpp nr.h
xmoment.o : xmoment.cpp nr.h
xmppi.o : xmppi.cpp nr.h
xmprove.o : xmprove.cpp nr.h
xmrqcof.o : xmrqcof.cpp nr.h
xmrqmin.o : xmrqmin.cpp nr.h
xnewt.o : xnewt.cpp nr.h
xodeint.o : xodeint.cpp nr.h
xorthog.o : xorthog.cpp nr.h
xpade.o : xpade.cpp nr.h
xpccheb.o : xpccheb.cpp nr.h
xpcshft.o : xpcshft.cpp nr.h
xpearsn.o : xpearsn.cpp nr.h
xperiod.o : xperiod.cpp nr.h
xpiksr2.o : xpiksr2.cpp nr.h
xpiksrt.o : xpiksrt.cpp nr.h
xplgndr.o : xplgndr.cpp nr.h
xpoidev.o : xpoidev.cpp nr.h
xpolcoe.o : xpolcoe.cpp nr.h
xpolcof.o : xpolcof.cpp nr.h
xpoldiv.o : xpoldiv.cpp nr.h
xpolin2.o : xpolin2.cpp nr.h
xpolint.o : xpolint.cpp nr.h
xpowell.o : xpowell.cpp nr.h
xpredic.o : xpredic.cpp nr.h
xprobks.o : xprobks.cpp nr.h
xpsdes.o : xpsdes.cpp nr.h
xpzextr.o : xpzextr.cpp nr.h
xqgaus.o : xqgaus.cpp nr.h
xqrdcmp.o : xqrdcmp.cpp nr.h
xqromb.o : xqromb.cpp nr.h
xqromo.o : xqromo.cpp nr.h
xqroot.o : xqroot.cpp nr.h
xqrsolv.o : xqrsolv.cpp nr.h
xqrupdt.o : xqrupdt.cpp nr.h
xqsimp.o : xqsimp.cpp nr.h
xqtrap.o : xqtrap.cpp nr.h
xquad3d.o : xquad3d.cpp nr.h
xran.o : xran.cpp nr.h
xran4.o : xran4.cpp nr.h
xrank.o : xrank.cpp nr.h
xratint.o : xratint.cpp nr.h
xratlsq.o : xratlsq.cpp nr.h
xrc.o : xrc.cpp nr.h
xrd.o : xrd.cpp nr.h
xrealft.o : xrealft.cpp nr.h
xrf.o : xrf.cpp nr.h
xrj.o : xrj.cpp nr.h
xrk4.o : xrk4.cpp nr.h
xrkdumb.o : xrkdumb.cpp nr.h
xrkqs.o : xrkqs.cpp nr.h
xrlft3.o : xrlft3.cpp nr.h
xrofunc.o : xrofunc.cpp nr.h
xrtbis.o : xrtbis.cpp nr.h
xrtflsp.o : xrtflsp.cpp nr.h
xrtnewt.o : xrtnewt.cpp nr.h
xrtsafe.o : xrtsafe.cpp nr.h
xrtsec.o : xrtsec.cpp nr.h
xrzextr.o : xrzextr.cpp nr.h
xsavgol.o : xsavgol.cpp nr.h
xscrsho.o : xscrsho.cpp nr.h
xselect.o : xselect.cpp nr.h
xselip.o : xselip.cpp nr.h
xshell.o : xshell.cpp nr.h
xsimplx.o : xsimplx.cpp nr.h
xsimpr.o : xsimpr.cpp nr.h
xsinft.o : xsinft.cpp nr.h
xsncndn.o : xsncndn.cpp nr.h
xsobseq.o : xsobseq.cpp nr.h
xsobseq2.o : xsobseq2.cpp nr.h
xsor.o : xsor.cpp nr.h
xsort.o : xsort.cpp nr.h
xsort2.o : xsort2.cpp nr.h
xsort3.o : xsort3.cpp nr.h
xspctrm.o : xspctrm.cpp nr.h
xspear.o : xspear.cpp nr.h
xsphbes.o : xsphbes.cpp nr.h
xsphfpt.o : xsphfpt.cpp 
xsplie2.o : xsplie2.cpp nr.h
xsplin2.o : xsplin2.cpp nr.h
xspline.o : xspline.cpp nr.h
xsplint.o : xsplint.cpp nr.h
xsprsax.o : xsprsax.cpp nr.h
xsprsin.o : xsprsin.cpp nr.h
xsprspm.o : xsprspm.cpp nr.h
xsprstm.o : xsprstm.cpp nr.h
xsprstp.o : xsprstp.cpp nr.h
xsprstx.o : xsprstx.cpp nr.h
xstifbs.o : xstifbs.cpp nr.h
xstiff.o : xstiff.cpp nr.h
xstoerm.o : xstoerm.cpp nr.h
xsvbksb.o : xsvbksb.cpp nr.h
xsvdcmp.o : xsvdcmp.cpp nr.h
xsvdfit.o : xsvdfit.cpp nr.h
xsvdvar.o : xsvdvar.cpp nr.h
xtoeplz.o : xtoeplz.cpp nr.h
xtptest.o : xtptest.cpp nr.h
xtqli.o : xtqli.cpp nr.h
xtrapzd.o : xtrapzd.cpp nr.h
xtred2.o : xtred2.cpp nr.h
xtridag.o : xtridag.cpp nr.h
xttest.o : xttest.cpp nr.h
xtutest.o : xtutest.cpp nr.h
xtwofft.o : xtwofft.cpp nr.h
xvander.o : xvander.cpp nr.h
xvegas.o : xvegas.cpp nr.h
xvoltra.o : xvoltra.cpp nr.h
xwt1.o : xwt1.cpp nr.h
xwtn.o : xwtn.cpp nr.h
xzbrac.o : xzbrac.cpp nr.h
xzbrak.o : xzbrak.cpp nr.h
xzbrent.o : xzbrent.cpp nr.h
xzrhqr.o : xzrhqr.cpp nr.h
xzriddr.o : xzriddr.cpp nr.h
xzroots.o : xzroots.cpp nr.h

xairy.reslt : xairy.out fncval.dat
	xairy.out > xairy.reslt && \
	$(NRDIFF) xairy.reslt $(NRANS)

xamebsa.reslt : xamebsa.resp xamebsa.out
	xamebsa.out < $< > xamebsa.reslt && \
	$(NRDIFF) xamebsa.reslt $(NRANS)

xamoeba.reslt : xamoeba.out
	xamoeba.out > xamoeba.reslt && \
	$(NRDIFF) xamoeba.reslt $(NRANS)

xanneal.reslt : xanneal.out
	xanneal.out > xanneal.reslt && \
	$(NRDIFF) xanneal.reslt $(NRANS)

xarcode.reslt : xarcode.resp xarcode.out text.dat
	xarcode.out < $< > xarcode.reslt && \
	$(NRDIFF) xarcode.reslt $(NRANS)

xavevar.reslt : xavevar.out
	xavevar.out > xavevar.reslt && \
	$(NRDIFF) xavevar.reslt $(NRANS)

xbalanc.reslt : xbalanc.out
	xbalanc.out > xbalanc.reslt && \
	$(NRDIFF) xbalanc.reslt $(NRANS)

xbandec.reslt : xbandec.out
	xbandec.out > xbandec.reslt && \
	$(NRDIFF) xbandec.reslt $(NRANS)

xbanmul.reslt : xbanmul.out
	xbanmul.out > xbanmul.reslt && \
	$(NRDIFF) xbanmul.reslt $(NRANS)

xbcucof.reslt : xbcucof.out
	xbcucof.out > xbcucof.reslt && \
	$(NRDIFF) xbcucof.reslt $(NRANS)

xbcuint.reslt : xbcuint.out
	xbcuint.out > xbcuint.reslt && \
	$(NRDIFF) xbcuint.reslt $(NRANS)

xbeschb.reslt : xbeschb.resp xbeschb.out
	xbeschb.out < $< > xbeschb.reslt && \
	$(NRDIFF) xbeschb.reslt $(NRANS)

xbessi.reslt : xbessi.out fncval.dat
	xbessi.out > xbessi.reslt && \
	$(NRDIFF) xbessi.reslt $(NRANS)

xbessi0.reslt : xbessi0.out fncval.dat
	xbessi0.out > xbessi0.reslt && \
	$(NRDIFF) xbessi0.reslt $(NRANS)

xbessi1.reslt : xbessi1.out fncval.dat
	xbessi1.out > xbessi1.reslt && \
	$(NRDIFF) xbessi1.reslt $(NRANS)

xbessik.reslt : xbessik.out fncval.dat
	xbessik.out > xbessik.reslt && \
	$(NRDIFF) xbessik.reslt $(NRANS)

xbessj.reslt : xbessj.out fncval.dat
	xbessj.out > xbessj.reslt && \
	$(NRDIFF) xbessj.reslt $(NRANS)

xbessj0.reslt : xbessj0.out fncval.dat
	xbessj0.out > xbessj0.reslt && \
	$(NRDIFF) xbessj0.reslt $(NRANS)

xbessj1.reslt : xbessj1.out fncval.dat
	xbessj1.out > xbessj1.reslt && \
	$(NRDIFF) xbessj1.reslt $(NRANS)

xbessjy.reslt : xbessjy.out fncval.dat
	xbessjy.out > xbessjy.reslt && \
	$(NRDIFF) xbessjy.reslt $(NRANS)

xbessk.reslt : xbessk.out fncval.dat
	xbessk.out > xbessk.reslt && \
	$(NRDIFF) xbessk.reslt $(NRANS)

xbessk0.reslt : xbessk0.out fncval.dat
	xbessk0.out > xbessk0.reslt && \
	$(NRDIFF) xbessk0.reslt $(NRANS)

xbessk1.reslt : xbessk1.out fncval.dat
	xbessk1.out > xbessk1.reslt && \
	$(NRDIFF) xbessk1.reslt $(NRANS)

xbessy.reslt : xbessy.out fncval.dat
	xbessy.out > xbessy.reslt && \
	$(NRDIFF) xbessy.reslt $(NRANS)

xbessy0.reslt : xbessy0.out fncval.dat
	xbessy0.out > xbessy0.reslt && \
	$(NRDIFF) xbessy0.reslt $(NRANS)

xbessy1.reslt : xbessy1.out fncval.dat
	xbessy1.out > xbessy1.reslt && \
	$(NRDIFF) xbessy1.reslt $(NRANS)

xbeta.reslt : xbeta.out fncval.dat
	xbeta.out > xbeta.reslt && \
	$(NRDIFF) xbeta.reslt $(NRANS)

xbetai.reslt : xbetai.out fncval.dat
	xbetai.out > xbetai.reslt && \
	$(NRDIFF) xbetai.reslt $(NRANS)

xbico.reslt : xbico.out fncval.dat
	xbico.out > xbico.reslt && \
	$(NRDIFF) xbico.reslt $(NRANS)

xbnldev.reslt : xbnldev.resp xbnldev.out
	xbnldev.out < $< > xbnldev.reslt && \
	$(NRDIFF) xbnldev.reslt $(NRANS)

xbrent.reslt : xbrent.out
	xbrent.out > xbrent.reslt && \
	$(NRDIFF) xbrent.reslt $(NRANS)

xbroydn.reslt : xbroydn.out
	xbroydn.out > xbroydn.reslt && \
	$(NRDIFF) xbroydn.reslt $(NRANS)

xbsstep.reslt : xbsstep.out
	xbsstep.out > xbsstep.reslt && \
	$(NRDIFF) xbsstep.reslt $(NRANS)

xcaldat.reslt : xcaldat.out dates1.dat
	xcaldat.out > xcaldat.reslt && \
	$(NRDIFF) xcaldat.reslt $(NRANS)

xchder.reslt : xchder.resp xchder.out
	xchder.out < $< > xchder.reslt && \
	$(NRDIFF) xchder.reslt $(NRANS)

xchebev.reslt : xchebev.resp xchebev.out
	xchebev.out < $< > xchebev.reslt && \
	$(NRDIFF) xchebev.reslt $(NRANS)

xchebft.reslt : xchebft.resp xchebft.out
	xchebft.out < $< > xchebft.reslt && \
	$(NRDIFF) xchebft.reslt $(NRANS)

xchebpc.reslt : xchebpc.resp xchebpc.out
	xchebpc.out < $< > xchebpc.reslt && \
	$(NRDIFF) xchebpc.reslt $(NRANS)

xchint.reslt : xchint.resp xchint.out
	xchint.out < $< > xchint.reslt && \
	$(NRDIFF) xchint.reslt $(NRANS)

xcholsl.reslt : xcholsl.out
	xcholsl.out > xcholsl.reslt && \
	$(NRDIFF) xcholsl.reslt $(NRANS)

xchsone.reslt : xchsone.out
	xchsone.out > xchsone.reslt && \
	$(NRDIFF) xchsone.reslt $(NRANS)

xchstwo.reslt : xchstwo.out
	xchstwo.out > xchstwo.reslt && \
	$(NRDIFF) xchstwo.reslt $(NRANS)

xcisi.reslt : xcisi.out fncval.dat
	xcisi.out > xcisi.reslt && \
	$(NRDIFF) xcisi.reslt $(NRANS)

xcntab1.reslt : xcntab1.out table1.dat
	xcntab1.out > xcntab1.reslt && \
	$(NRDIFF) xcntab1.reslt $(NRANS)

xcntab2.reslt : xcntab2.out table1.dat
	xcntab2.out > xcntab2.reslt && \
	$(NRDIFF) xcntab2.reslt $(NRANS)

xconvlv.reslt : xconvlv.out
	xconvlv.out > xconvlv.reslt && \
	$(NRDIFF) xconvlv.reslt $(NRANS)

xcorrel.reslt : xcorrel.out
	xcorrel.out > xcorrel.reslt && \
	$(NRDIFF) xcorrel.reslt $(NRANS)

xcosft1.reslt : xcosft1.resp xcosft1.out
	xcosft1.out < $< > xcosft1.reslt && \
	$(NRDIFF) xcosft1.reslt $(NRANS)

xcosft2.reslt : xcosft2.resp xcosft2.out
	xcosft2.out < $< > xcosft2.reslt && \
	$(NRDIFF) xcosft2.reslt $(NRANS)

xcovsrt.reslt : xcovsrt.resp xcovsrt.out
	xcovsrt.out < $< > xcovsrt.reslt && \
	$(NRDIFF) xcovsrt.reslt $(NRANS)

xcrank.reslt : xcrank.resp xcrank.out table2.dat
	xcrank.out < $< > xcrank.reslt && \
	$(NRDIFF) xcrank.reslt $(NRANS)

xcyclic.reslt : xcyclic.out
	xcyclic.out > xcyclic.reslt && \
	$(NRDIFF) xcyclic.reslt $(NRANS)

xdawson.reslt : xdawson.out fncval.dat
	xdawson.out > xdawson.reslt && \
	$(NRDIFF) xdawson.reslt $(NRANS)

xdbrent.reslt : xdbrent.out
	xdbrent.out > xdbrent.reslt && \
	$(NRDIFF) xdbrent.reslt $(NRANS)

xddpoly.reslt : xddpoly.resp xddpoly.out
	xddpoly.out < $< > xddpoly.reslt && \
	$(NRDIFF) xddpoly.reslt $(NRANS)

xdecchk.reslt : xdecchk.resp xdecchk.out
	xdecchk.out < $< > xdecchk.reslt && \
	$(NRDIFF) xdecchk.reslt $(NRANS)

xdf1dim.reslt : xdf1dim.resp xdf1dim.out
	xdf1dim.out < $< > xdf1dim.reslt && \
	$(NRDIFF) xdf1dim.reslt $(NRANS)

xdfpmin.reslt : xdfpmin.out
	xdfpmin.out > xdfpmin.reslt && \
	$(NRDIFF) xdfpmin.reslt $(NRANS)

xdfridr.reslt : xdfridr.resp xdfridr.out
	xdfridr.out < $< > xdfridr.reslt && \
	$(NRDIFF) xdfridr.reslt $(NRANS)

xdftint.reslt : xdftint.resp xdftint.out
	xdftint.out < $< > xdftint.reslt && \
	$(NRDIFF) xdftint.reslt $(NRANS)

xdlinmin.reslt : xdlinmin.out
	xdlinmin.out > xdlinmin.reslt && \
	$(NRDIFF) xdlinmin.reslt $(NRANS)

xeclass.reslt : xeclass.out
	xeclass.out > xeclass.reslt && \
	$(NRDIFF) xeclass.reslt $(NRANS)

xeclazz.reslt : xeclazz.out
	xeclazz.out > xeclazz.reslt && \
	$(NRDIFF) xeclazz.reslt $(NRANS)

xei.reslt : xei.out fncval.dat
	xei.out > xei.reslt && \
	$(NRDIFF) xei.reslt $(NRANS)

xeigsrt.reslt : xeigsrt.out
	xeigsrt.out > xeigsrt.reslt && \
	$(NRDIFF) xeigsrt.reslt $(NRANS)

xelle.reslt : xelle.out fncval.dat
	xelle.out > xelle.reslt && \
	$(NRDIFF) xelle.reslt $(NRANS)

xellf.reslt : xellf.out fncval.dat
	xellf.out > xellf.reslt && \
	$(NRDIFF) xellf.reslt $(NRANS)

xellpi.reslt : xellpi.out fncval.dat
	xellpi.out > xellpi.reslt && \
	$(NRDIFF) xellpi.reslt $(NRANS)

xelmhes.reslt : xelmhes.out
	xelmhes.out > xelmhes.reslt && \
	$(NRDIFF) xelmhes.reslt $(NRANS)

xerfcc.reslt : xerfcc.out fncval.dat
	xerfcc.out > xerfcc.reslt && \
	$(NRDIFF) xerfcc.reslt $(NRANS)

xerff.reslt : xerff.out fncval.dat
	xerff.out > xerff.reslt && \
	$(NRDIFF) xerff.reslt $(NRANS)

xerffc.reslt : xerffc.out fncval.dat
	xerffc.out > xerffc.reslt && \
	$(NRDIFF) xerffc.reslt $(NRANS)

xeulsum.reslt : xeulsum.resp xeulsum.out
	xeulsum.out < $< > xeulsum.reslt && \
	$(NRDIFF) xeulsum.reslt $(NRANS)

xevlmem.reslt : xevlmem.out spctrl.dat
	xevlmem.out > xevlmem.reslt && \
	$(NRDIFF) xevlmem.reslt $(NRANS)

xexpdev.reslt : xexpdev.out
	xexpdev.out > xexpdev.reslt && \
	$(NRDIFF) xexpdev.reslt $(NRANS)

xexpint.reslt : xexpint.out fncval.dat
	xexpint.out > xexpint.reslt && \
	$(NRDIFF) xexpint.reslt $(NRANS)

xf1dim.reslt : xf1dim.resp xf1dim.out
	xf1dim.out < $< > xf1dim.reslt && \
	$(NRDIFF) xf1dim.reslt $(NRANS)

xfactln.reslt : xfactln.out fncval.dat
	xfactln.out > xfactln.reslt && \
	$(NRDIFF) xfactln.reslt $(NRANS)

xfactrl.reslt : xfactrl.out fncval.dat
	xfactrl.out > xfactrl.reslt && \
	$(NRDIFF) xfactrl.reslt $(NRANS)

xfasper.reslt : xfasper.out
	xfasper.out > xfasper.reslt && \
	$(NRDIFF) xfasper.reslt $(NRANS)

xfgauss.reslt : xfgauss.out
	xfgauss.out > xfgauss.reslt && \
	$(NRDIFF) xfgauss.reslt $(NRANS)

xfit.reslt : xfit.out
	xfit.out > xfit.reslt && \
	$(NRDIFF) xfit.reslt $(NRANS)

xfitexy.reslt : xfitexy.out
	xfitexy.out > xfitexy.reslt && \
	$(NRDIFF) xfitexy.reslt $(NRANS)

xfixrts.reslt : xfixrts.out
	xfixrts.out > xfixrts.reslt && \
	$(NRDIFF) xfixrts.reslt $(NRANS)

xfleg.reslt : xfleg.out
	xfleg.out > xfleg.reslt && \
	$(NRDIFF) xfleg.reslt $(NRANS)

xflmoon.reslt : xflmoon.resp xflmoon.out
	xflmoon.out < $< > xflmoon.reslt && \
	$(NRDIFF) xflmoon.reslt $(NRANS)

xfour1.reslt : xfour1.resp xfour1.out
	xfour1.out < $< > xfour1.reslt && \
	$(NRDIFF) xfour1.reslt $(NRANS)

xfourfs.reslt : xfourfs.out
	xfourfs.out > xfourfs.reslt && \
	$(NRDIFF) xfourfs.reslt $(NRANS)

xfourn.reslt : xfourn.out
	xfourn.out > xfourn.reslt && \
	$(NRDIFF) xfourn.reslt $(NRANS)

xfpoly.reslt : xfpoly.out
	xfpoly.out > xfpoly.reslt && \
	$(NRDIFF) xfpoly.reslt $(NRANS)

xfred2.reslt : xfred2.out
	xfred2.out > xfred2.reslt && \
	$(NRDIFF) xfred2.reslt $(NRANS)

xfredin.reslt : xfredin.resp xfredin.out
	xfredin.out < $< > xfredin.reslt && \
	$(NRDIFF) xfredin.reslt $(NRANS)

xfrenel.reslt : xfrenel.out fncval.dat
	xfrenel.out > xfrenel.reslt && \
	$(NRDIFF) xfrenel.reslt $(NRANS)

xfrprmn.reslt : xfrprmn.out
	xfrprmn.out > xfrprmn.reslt && \
	$(NRDIFF) xfrprmn.reslt $(NRANS)

xftest.reslt : xftest.out
	xftest.out > xftest.reslt && \
	$(NRDIFF) xftest.reslt $(NRANS)

xgamdev.reslt : xgamdev.resp xgamdev.out
	xgamdev.out < $< > xgamdev.reslt && \
	$(NRDIFF) xgamdev.reslt $(NRANS)

xgammln.reslt : xgammln.out fncval.dat
	xgammln.out > xgammln.reslt && \
	$(NRDIFF) xgammln.reslt $(NRANS)

xgammp.reslt : xgammp.out fncval.dat
	xgammp.out > xgammp.reslt && \
	$(NRDIFF) xgammp.reslt $(NRANS)

xgammq.reslt : xgammq.out fncval.dat
	xgammq.out > xgammq.reslt && \
	$(NRDIFF) xgammq.reslt $(NRANS)

xgasdev.reslt : xgasdev.out
	xgasdev.out > xgasdev.reslt && \
	$(NRDIFF) xgasdev.reslt $(NRANS)

xgaucof.reslt : xgaucof.resp xgaucof.out
	xgaucof.out < $< > xgaucof.reslt && \
	$(NRDIFF) xgaucof.reslt $(NRANS)

xgauher.reslt : xgauher.resp xgauher.out
	xgauher.out < $< > xgauher.reslt && \
	$(NRDIFF) xgauher.reslt $(NRANS)

xgaujac.reslt : xgaujac.resp xgaujac.out
	xgaujac.out < $< > xgaujac.reslt && \
	$(NRDIFF) xgaujac.reslt $(NRANS)

xgaulag.reslt : xgaulag.resp xgaulag.out
	xgaulag.out < $< > xgaulag.reslt && \
	$(NRDIFF) xgaulag.reslt $(NRANS)

xgauleg.reslt : xgauleg.out
	xgauleg.out > xgauleg.reslt && \
	$(NRDIFF) xgauleg.reslt $(NRANS)

xgaussj.reslt : xgaussj.resp xgaussj.out matrx1.dat
	xgaussj.out < $< > xgaussj.reslt && \
	$(NRDIFF) xgaussj.reslt $(NRANS)

xgcf.reslt : xgcf.out fncval.dat
	xgcf.out > xgcf.reslt && \
	$(NRDIFF) xgcf.reslt $(NRANS)

xgolden.reslt : xgolden.out
	xgolden.out > xgolden.reslt && \
	$(NRDIFF) xgolden.reslt $(NRANS)

xgser.reslt : xgser.out fncval.dat
	xgser.out > xgser.reslt && \
	$(NRDIFF) xgser.reslt $(NRANS)

xhpsel.reslt : xhpsel.resp xhpsel.out tarray.dat
	xhpsel.out < $< > xhpsel.reslt && \
	$(NRDIFF) xhpsel.reslt $(NRANS)

xhpsort.reslt : xhpsort.out tarray.dat
	xhpsort.out > xhpsort.reslt && \
	$(NRDIFF) xhpsort.reslt $(NRANS)

xhqr.reslt : xhqr.out
	xhqr.out > xhqr.reslt && \
	$(NRDIFF) xhqr.reslt $(NRANS)

xhuffman.reslt : xhuffman.resp xhuffman.out text.dat
	xhuffman.out < $< > xhuffman.reslt && \
	$(NRDIFF) xhuffman.reslt $(NRANS)

xhunt.reslt : xhunt.out
	xhunt.out > xhunt.reslt && \
	$(NRDIFF) xhunt.reslt $(NRANS)

xhypgeo.reslt : xhypgeo.resp xhypgeo.out
	xhypgeo.out < $< > xhypgeo.reslt && \
	$(NRDIFF) xhypgeo.reslt $(NRANS)

xicrc.reslt : xicrc.resp xicrc.out
	xicrc.out < $< > xicrc.reslt && \
	$(NRDIFF) xicrc.reslt $(NRANS)

xigray.reslt : xigray.resp xigray.out
	xigray.out < $< > xigray.reslt && \
	$(NRDIFF) xigray.reslt $(NRANS)

xindexx.reslt : xindexx.out tarray.dat
	xindexx.out > xindexx.reslt && \
	$(NRDIFF) xindexx.reslt $(NRANS)

xirbit1.reslt : xirbit1.out
	xirbit1.out > xirbit1.reslt && \
	$(NRDIFF) xirbit1.reslt $(NRANS)

xirbit2.reslt : xirbit2.out
	xirbit2.out > xirbit2.reslt && \
	$(NRDIFF) xirbit2.reslt $(NRANS)

xjacobi.reslt : xjacobi.resp xjacobi.out
	xjacobi.out < $< > xjacobi.reslt && \
	$(NRDIFF) xjacobi.reslt $(NRANS)

xjulday.reslt : xjulday.resp xjulday.out dates1.dat
	xjulday.out < $< > xjulday.reslt && \
	$(NRDIFF) xjulday.reslt $(NRANS)

xkendl1.reslt : xkendl1.out
	xkendl1.out > xkendl1.reslt && \
	$(NRDIFF) xkendl1.reslt $(NRANS)

xkendl2.reslt : xkendl2.out
	xkendl2.out > xkendl2.reslt && \
	$(NRDIFF) xkendl2.reslt $(NRANS)

xks2d1s.reslt : xks2d1s.resp xks2d1s.out
	xks2d1s.out < $< > xks2d1s.reslt && \
	$(NRDIFF) xks2d1s.reslt $(NRANS)

xks2d2s.reslt : xks2d2s.resp xks2d2s.out
	xks2d2s.out < $< > xks2d2s.reslt && \
	$(NRDIFF) xks2d2s.reslt $(NRANS)

xksone.reslt : xksone.out
	xksone.out > xksone.reslt && \
	$(NRDIFF) xksone.reslt $(NRANS)

xkstwo.reslt : xkstwo.out
	xkstwo.out > xkstwo.reslt && \
	$(NRDIFF) xkstwo.reslt $(NRANS)

xlaguer.reslt : xlaguer.out
	xlaguer.out > xlaguer.reslt && \
	$(NRDIFF) xlaguer.reslt $(NRANS)

xlfit.reslt : xlfit.resp xlfit.out
	xlfit.out < $< > xlfit.reslt && \
	$(NRDIFF) xlfit.reslt $(NRANS)

xlinbcg.reslt : xlinbcg.resp xlinbcg.out
	xlinbcg.out < $< > xlinbcg.reslt && \
	$(NRDIFF) xlinbcg.reslt $(NRANS)

xlinmin.reslt : xlinmin.out
	xlinmin.out > xlinmin.reslt && \
	$(NRDIFF) xlinmin.reslt $(NRANS)

xlocate.reslt : xlocate.out
	xlocate.out > xlocate.reslt && \
	$(NRDIFF) xlocate.reslt $(NRANS)

xlubksb.reslt : xlubksb.resp xlubksb.out matrx1.dat
	xlubksb.out < $< > xlubksb.reslt && \
	$(NRDIFF) xlubksb.reslt $(NRANS)

xludcmp.reslt : xludcmp.resp xludcmp.out matrx1.dat
	xludcmp.out < $< > xludcmp.reslt && \
	$(NRDIFF) xludcmp.reslt $(NRANS)

xmachar.reslt : xmachar.out
	xmachar.out > xmachar.reslt && \
	$(NRDIFF) xmachar.reslt $(NRANS)

xmedfit.reslt : xmedfit.out
	xmedfit.out > xmedfit.reslt && \
	$(NRDIFF) xmedfit.reslt $(NRANS)

xmemcof.reslt : xmemcof.out spctrl.dat
	xmemcof.out > xmemcof.reslt && \
	$(NRDIFF) xmemcof.reslt $(NRANS)

xmgfas.reslt : xmgfas.out
	xmgfas.out > xmgfas.reslt && \
	$(NRDIFF) xmgfas.reslt $(NRANS)

xmglin.reslt : xmglin.out
	xmglin.out > xmglin.reslt && \
	$(NRDIFF) xmglin.reslt $(NRANS)

xmidpnt.reslt : xmidpnt.out
	xmidpnt.out > xmidpnt.reslt && \
	$(NRDIFF) xmidpnt.reslt $(NRANS)

xmiser.reslt : xmiser.resp xmiser.out
	xmiser.out < $< > xmiser.reslt && \
	$(NRDIFF) xmiser.reslt $(NRANS)

xmmid.reslt : xmmid.resp xmmid.out
	xmmid.out < $< > xmmid.reslt && \
	$(NRDIFF) xmmid.reslt $(NRANS)

xmnbrak.reslt : xmnbrak.out
	xmnbrak.out > xmnbrak.reslt && \
	$(NRDIFF) xmnbrak.reslt $(NRANS)

xmnewt.reslt : xmnewt.resp xmnewt.out
	xmnewt.out < $< > xmnewt.reslt && \
	$(NRDIFF) xmnewt.reslt $(NRANS)

xmoment.reslt : xmoment.out
	xmoment.out > xmoment.reslt && \
	$(NRDIFF) xmoment.reslt $(NRANS)

xmppi.reslt : xmppi.resp xmppi.out
	xmppi.out < $< > xmppi.reslt && \
	$(NRDIFF) xmppi.reslt $(NRANS)

xmprove.reslt : xmprove.out
	xmprove.out > xmprove.reslt && \
	$(NRDIFF) xmprove.reslt $(NRANS)

xmrqcof.reslt : xmrqcof.out
	xmrqcof.out > xmrqcof.reslt && \
	$(NRDIFF) xmrqcof.reslt $(NRANS)

xmrqmin.reslt : xmrqmin.resp xmrqmin.out
	xmrqmin.out < $< > xmrqmin.reslt && \
	$(NRDIFF) xmrqmin.reslt $(NRANS)

xnewt.reslt : xnewt.out
	xnewt.out > xnewt.reslt && \
	$(NRDIFF) xnewt.reslt $(NRANS)

xodeint.reslt : xodeint.out
	xodeint.out > xodeint.reslt && \
	$(NRDIFF) xodeint.reslt $(NRANS)

xorthog.reslt : xorthog.resp xorthog.out
	xorthog.out < $< > xorthog.reslt && \
	$(NRDIFF) xorthog.reslt $(NRANS)

xpade.reslt : xpade.resp xpade.out
	xpade.out < $< > xpade.reslt && \
	$(NRDIFF) xpade.reslt $(NRANS)

xpccheb.reslt : xpccheb.out
	xpccheb.out > xpccheb.reslt && \
	$(NRDIFF) xpccheb.reslt $(NRANS)

xpcshft.reslt : xpcshft.resp xpcshft.out
	xpcshft.out < $< > xpcshft.reslt && \
	$(NRDIFF) xpcshft.reslt $(NRANS)

xpearsn.reslt : xpearsn.out
	xpearsn.out > xpearsn.reslt && \
	$(NRDIFF) xpearsn.reslt $(NRANS)

xperiod.reslt : xperiod.out
	xperiod.out > xperiod.reslt && \
	$(NRDIFF) xperiod.reslt $(NRANS)

xpiksr2.reslt : xpiksr2.resp xpiksr2.out tarray.dat
	xpiksr2.out < $< > xpiksr2.reslt && \
	$(NRDIFF) xpiksr2.reslt $(NRANS)

xpiksrt.reslt : xpiksrt.out tarray.dat
	xpiksrt.out > xpiksrt.reslt && \
	$(NRDIFF) xpiksrt.reslt $(NRANS)

xplgndr.reslt : xplgndr.out fncval.dat
	xplgndr.out > xplgndr.reslt && \
	$(NRDIFF) xplgndr.reslt $(NRANS)

xpoidev.reslt : xpoidev.resp xpoidev.out
	xpoidev.out < $< > xpoidev.reslt && \
	$(NRDIFF) xpoidev.reslt $(NRANS)

xpolcoe.reslt : xpolcoe.resp xpolcoe.out
	xpolcoe.out < $< > xpolcoe.reslt && \
	$(NRDIFF) xpolcoe.reslt $(NRANS)

xpolcof.reslt : xpolcof.resp xpolcof.out
	xpolcof.out < $< > xpolcof.reslt && \
	$(NRDIFF) xpolcof.reslt $(NRANS)

xpoldiv.reslt : xpoldiv.out
	xpoldiv.out > xpoldiv.reslt && \
	$(NRDIFF) xpoldiv.reslt $(NRANS)

xpolin2.reslt : xpolin2.out
	xpolin2.out > xpolin2.reslt && \
	$(NRDIFF) xpolin2.reslt $(NRANS)

xpolint.reslt : xpolint.resp xpolint.out
	xpolint.out < $< > xpolint.reslt && \
	$(NRDIFF) xpolint.reslt $(NRANS)

xpowell.reslt : xpowell.out
	xpowell.out > xpowell.reslt && \
	$(NRDIFF) xpowell.reslt $(NRANS)

xpredic.reslt : xpredic.out
	xpredic.out > xpredic.reslt && \
	$(NRDIFF) xpredic.reslt $(NRANS)

xprobks.reslt : xprobks.out
	xprobks.out > xprobks.reslt && \
	$(NRDIFF) xprobks.reslt $(NRANS)

xpsdes.reslt : xpsdes.out
	xpsdes.out > xpsdes.reslt && \
	$(NRDIFF) xpsdes.reslt $(NRANS)

xpzextr.reslt : xpzextr.out
	xpzextr.out > xpzextr.reslt && \
	$(NRDIFF) xpzextr.reslt $(NRANS)

xqgaus.reslt : xqgaus.out
	xqgaus.out > xqgaus.reslt && \
	$(NRDIFF) xqgaus.reslt $(NRANS)

xqrdcmp.reslt : xqrdcmp.resp xqrdcmp.out matrx1.dat
	xqrdcmp.out < $< > xqrdcmp.reslt && \
	$(NRDIFF) xqrdcmp.reslt $(NRANS)

xqromb.reslt : xqromb.out
	xqromb.out > xqromb.reslt && \
	$(NRDIFF) xqromb.reslt $(NRANS)

xqromo.reslt : xqromo.out
	xqromo.out > xqromo.reslt && \
	$(NRDIFF) xqromo.reslt $(NRANS)

xqroot.reslt : xqroot.out
	xqroot.out > xqroot.reslt && \
	$(NRDIFF) xqroot.reslt $(NRANS)

xqrsolv.reslt : xqrsolv.resp xqrsolv.out matrx1.dat
	xqrsolv.out < $< > xqrsolv.reslt && \
	$(NRDIFF) xqrsolv.reslt $(NRANS)

xqrupdt.reslt : xqrupdt.resp xqrupdt.out matrx1.dat
	xqrupdt.out < $< > xqrupdt.reslt && \
	$(NRDIFF) xqrupdt.reslt $(NRANS)

xqsimp.reslt : xqsimp.out
	xqsimp.out > xqsimp.reslt && \
	$(NRDIFF) xqsimp.reslt $(NRANS)

xqtrap.reslt : xqtrap.out
	xqtrap.out > xqtrap.reslt && \
	$(NRDIFF) xqtrap.reslt $(NRANS)

xquad3d.reslt : xquad3d.out
	xquad3d.out > xquad3d.reslt && \
	$(NRDIFF) xquad3d.reslt $(NRANS)

xran.reslt : xran.resp xran.out
	xran.out < $< > xran.reslt && \
	$(NRDIFF) xran.reslt $(NRANS)

xran4.reslt : xran4.out
	xran4.out > xran4.reslt && \
	$(NRDIFF) xran4.reslt $(NRANS)

xrank.reslt : xrank.resp xrank.out tarray.dat
	xrank.out < $< > xrank.reslt && \
	$(NRDIFF) xrank.reslt $(NRANS)

xratint.reslt : xratint.out
	xratint.out > xratint.reslt && \
	$(NRDIFF) xratint.reslt $(NRANS)

xratlsq.reslt : xratlsq.resp xratlsq.out
	xratlsq.out < $< > xratlsq.reslt && \
	$(NRDIFF) xratlsq.reslt $(NRANS)

xrc.reslt : xrc.out fncval.dat
	xrc.out > xrc.reslt && \
	$(NRDIFF) xrc.reslt $(NRANS)

xrd.reslt : xrd.out fncval.dat
	xrd.out > xrd.reslt && \
	$(NRDIFF) xrd.reslt $(NRANS)

xrealft.reslt : xrealft.resp xrealft.out
	xrealft.out < $< > xrealft.reslt && \
	$(NRDIFF) xrealft.reslt $(NRANS)

xrf.reslt : xrf.out fncval.dat
	xrf.out > xrf.reslt && \
	$(NRDIFF) xrf.reslt $(NRANS)

xrj.reslt : xrj.out fncval.dat
	xrj.out > xrj.reslt && \
	$(NRDIFF) xrj.reslt $(NRANS)

xrk4.reslt : xrk4.out
	xrk4.out > xrk4.reslt && \
	$(NRDIFF) xrk4.reslt $(NRANS)

xrkdumb.reslt : xrkdumb.out
	xrkdumb.out > xrkdumb.reslt && \
	$(NRDIFF) xrkdumb.reslt $(NRANS)

xrkqs.reslt : xrkqs.out
	xrkqs.out > xrkqs.reslt && \
	$(NRDIFF) xrkqs.reslt $(NRANS)

xrlft3.reslt : xrlft3.out
	xrlft3.out > xrlft3.reslt && \
	$(NRDIFF) xrlft3.reslt $(NRANS)

xrofunc.reslt : xrofunc.out
	xrofunc.out > xrofunc.reslt && \
	$(NRDIFF) xrofunc.reslt $(NRANS)

xrtbis.reslt : xrtbis.out
	xrtbis.out > xrtbis.reslt && \
	$(NRDIFF) xrtbis.reslt $(NRANS)

xrtflsp.reslt : xrtflsp.out
	xrtflsp.out > xrtflsp.reslt && \
	$(NRDIFF) xrtflsp.reslt $(NRANS)

xrtnewt.reslt : xrtnewt.out
	xrtnewt.out > xrtnewt.reslt && \
	$(NRDIFF) xrtnewt.reslt $(NRANS)

xrtsafe.reslt : xrtsafe.out
	xrtsafe.out > xrtsafe.reslt && \
	$(NRDIFF) xrtsafe.reslt $(NRANS)

xrtsec.reslt : xrtsec.out
	xrtsec.out > xrtsec.reslt && \
	$(NRDIFF) xrtsec.reslt $(NRANS)

xrzextr.reslt : xrzextr.out
	xrzextr.out > xrzextr.reslt && \
	$(NRDIFF) xrzextr.reslt $(NRANS)

xsavgol.reslt : xsavgol.out
	xsavgol.out > xsavgol.reslt && \
	$(NRDIFF) xsavgol.reslt $(NRANS)

xscrsho.reslt : xscrsho.resp xscrsho.out
	xscrsho.out < $< > xscrsho.reslt && \
	$(NRDIFF) xscrsho.reslt $(NRANS)

xselect.reslt : xselect.resp xselect.out tarray.dat
	xselect.out < $< > xselect.reslt && \
	$(NRDIFF) xselect.reslt $(NRANS)

xselip.reslt : xselip.resp xselip.out tarray.dat
	xselip.out < $< > xselip.reslt && \
	$(NRDIFF) xselip.reslt $(NRANS)

xshell.reslt : xshell.out tarray.dat
	xshell.out > xshell.reslt && \
	$(NRDIFF) xshell.reslt $(NRANS)

xsimplx.reslt : xsimplx.out
	xsimplx.out > xsimplx.reslt && \
	$(NRDIFF) xsimplx.reslt $(NRANS)

xsimpr.reslt : xsimpr.out
	xsimpr.out > xsimpr.reslt && \
	$(NRDIFF) xsimpr.reslt $(NRANS)

xsinft.reslt : xsinft.resp xsinft.out
	xsinft.out < $< > xsinft.reslt && \
	$(NRDIFF) xsinft.reslt $(NRANS)

xsncndn.reslt : xsncndn.out fncval.dat
	xsncndn.out > xsncndn.reslt && \
	$(NRDIFF) xsncndn.reslt $(NRANS)

xsobseq.reslt : xsobseq.out
	xsobseq.out > xsobseq.reslt && \
	$(NRDIFF) xsobseq.reslt $(NRANS)

xsor.reslt : xsor.out
	xsor.out > xsor.reslt && \
	$(NRDIFF) xsor.reslt $(NRANS)

xsort.reslt : xsort.out tarray.dat
	xsort.out > xsort.reslt && \
	$(NRDIFF) xsort.reslt $(NRANS)

xsort2.reslt : xsort2.resp xsort2.out tarray.dat
	xsort2.out < $< > xsort2.reslt && \
	$(NRDIFF) xsort2.reslt $(NRANS)

xsort3.reslt : xsort3.out tarray.dat
	xsort3.out > xsort3.reslt && \
	$(NRDIFF) xsort3.reslt $(NRANS)

xspctrm.reslt : xspctrm.out spctrl.dat
	xspctrm.out > xspctrm.reslt && \
	$(NRDIFF) xspctrm.reslt $(NRANS)

xspear.reslt : xspear.resp xspear.out table2.dat
	xspear.out < $< > xspear.reslt && \
	$(NRDIFF) xspear.reslt $(NRANS)

xsphbes.reslt : xsphbes.out fncval.dat
	xsphbes.out > xsphbes.reslt && \
	$(NRDIFF) xsphbes.reslt $(NRANS)

xsphfpt.reslt : xsphfpt.resp xsphfpt.out
	xsphfpt.out < $< > xsphfpt.reslt && \
	$(NRDIFF) xsphfpt.reslt $(NRANS)

xsplie2.reslt : xsplie2.out
	xsplie2.out > xsplie2.reslt && \
	$(NRDIFF) xsplie2.reslt $(NRANS)

xsplin2.reslt : xsplin2.out
	xsplin2.out > xsplin2.reslt && \
	$(NRDIFF) xsplin2.reslt $(NRANS)

xspline.reslt : xspline.out
	xspline.out > xspline.reslt && \
	$(NRDIFF) xspline.reslt $(NRANS)

xsplint.reslt : xsplint.resp xsplint.out
	xsplint.out < $< > xsplint.reslt && \
	$(NRDIFF) xsplint.reslt $(NRANS)

xsprsax.reslt : xsprsax.out
	xsprsax.out > xsprsax.reslt && \
	$(NRDIFF) xsprsax.reslt $(NRANS)

xsprsin.reslt : xsprsin.out
	xsprsin.out > xsprsin.reslt && \
	$(NRDIFF) xsprsin.reslt $(NRANS)

xsprspm.reslt : xsprspm.out
	xsprspm.out > xsprspm.reslt && \
	$(NRDIFF) xsprspm.reslt $(NRANS)

xsprstm.reslt : xsprstm.out
	xsprstm.out > xsprstm.reslt && \
	$(NRDIFF) xsprstm.reslt $(NRANS)

xsprstp.reslt : xsprstp.out
	xsprstp.out > xsprstp.reslt && \
	$(NRDIFF) xsprstp.reslt $(NRANS)

xsprstx.reslt : xsprstx.out
	xsprstx.out > xsprstx.reslt && \
	$(NRDIFF) xsprstx.reslt $(NRANS)

xstifbs.reslt : xstifbs.resp xstifbs.out
	xstifbs.out < $< > xstifbs.reslt && \
	$(NRDIFF) xstifbs.reslt $(NRANS)

xstiff.reslt : xstiff.resp xstiff.out
	xstiff.out < $< > xstiff.reslt && \
	$(NRDIFF) xstiff.reslt $(NRANS)

xstoerm.reslt : xstoerm.out
	xstoerm.out > xstoerm.reslt && \
	$(NRDIFF) xstoerm.reslt $(NRANS)

xsvbksb.reslt : xsvbksb.resp xsvbksb.out matrx1.dat
	xsvbksb.out < $< > xsvbksb.reslt && \
	$(NRDIFF) xsvbksb.reslt $(NRANS)

xsvdcmp.reslt : xsvdcmp.resp xsvdcmp.out matrx3.dat
	xsvdcmp.out < $< > xsvdcmp.reslt && \
	$(NRDIFF) xsvdcmp.reslt $(NRANS)

xsvdfit.reslt : xsvdfit.out
	xsvdfit.out > xsvdfit.reslt && \
	$(NRDIFF) xsvdfit.reslt $(NRANS)

xsvdvar.reslt : xsvdvar.out
	xsvdvar.out > xsvdvar.reslt && \
	$(NRDIFF) xsvdvar.reslt $(NRANS)

xtoeplz.reslt : xtoeplz.out
	xtoeplz.out > xtoeplz.reslt && \
	$(NRDIFF) xtoeplz.reslt $(NRANS)

xtptest.reslt : xtptest.out
	xtptest.out > xtptest.reslt && \
	$(NRDIFF) xtptest.reslt $(NRANS)

xtqli.reslt : xtqli.resp xtqli.out
	xtqli.out < $< > xtqli.reslt && \
	$(NRDIFF) xtqli.reslt $(NRANS)

xtrapzd.reslt : xtrapzd.out
	xtrapzd.out > xtrapzd.reslt && \
	$(NRDIFF) xtrapzd.reslt $(NRANS)

xtred2.reslt : xtred2.out
	xtred2.out > xtred2.reslt && \
	$(NRDIFF) xtred2.reslt $(NRANS)

xtridag.reslt : xtridag.resp xtridag.out matrx2.dat
	xtridag.out < $< > xtridag.reslt && \
	$(NRDIFF) xtridag.reslt $(NRANS)

xttest.reslt : xttest.out
	xttest.out > xttest.reslt && \
	$(NRDIFF) xttest.reslt $(NRANS)

xtutest.reslt : xtutest.out
	xtutest.out > xtutest.reslt && \
	$(NRDIFF) xtutest.reslt $(NRANS)

xtwofft.reslt : xtwofft.resp xtwofft.out
	xtwofft.out < $< > xtwofft.reslt && \
	$(NRDIFF) xtwofft.reslt $(NRANS)

xvander.reslt : xvander.out
	xvander.out > xvander.reslt && \
	$(NRDIFF) xvander.reslt $(NRANS)

xvegas.reslt : xvegas.resp xvegas.out
	xvegas.out < $< > xvegas.reslt && \
	$(NRDIFF) xvegas.reslt $(NRANS)

xvoltra.reslt : xvoltra.out
	xvoltra.out > xvoltra.reslt && \
	$(NRDIFF) xvoltra.reslt $(NRANS)

xwt1.reslt : xwt1.resp xwt1.out
	xwt1.out < $< > xwt1.reslt && \
	$(NRDIFF) xwt1.reslt $(NRANS)

xwtn.reslt : xwtn.out
	xwtn.out > xwtn.reslt && \
	$(NRDIFF) xwtn.reslt $(NRANS)

xzbrac.reslt : xzbrac.out
	xzbrac.out > xzbrac.reslt && \
	$(NRDIFF) xzbrac.reslt $(NRANS)

xzbrak.reslt : xzbrak.out
	xzbrak.out > xzbrak.reslt && \
	$(NRDIFF) xzbrak.reslt $(NRANS)

xzbrent.reslt : xzbrent.out
	xzbrent.out > xzbrent.reslt && \
	$(NRDIFF) xzbrent.reslt $(NRANS)

xzrhqr.reslt : xzrhqr.out
	xzrhqr.out > xzrhqr.reslt && \
	$(NRDIFF) xzrhqr.reslt $(NRANS)

xzriddr.reslt : xzriddr.out
	xzriddr.out > xzriddr.reslt && \
	$(NRDIFF) xzriddr.reslt $(NRANS)

xzroots.reslt : xzroots.out
	xzroots.out > xzroots.reslt && \
	$(NRDIFF) xzroots.reslt $(NRANS)

badluk.reslt : badluk.out
	badluk.out > badluk.reslt && \
	$(NRDIFF) badluk.reslt $(NRANS)

fredex.reslt : fredex.out
	fredex.out > fredex.reslt && \
	$(NRDIFF) fredex.reslt $(NRANS)

sfroid.reslt : sfroid.resp sfroid.out
	sfroid.out < $< > sfroid.reslt && \
	$(NRDIFF) sfroid.reslt $(NRANS)

sphoot.reslt : sphoot.resp sphoot.out
	sphoot.out < $< > sphoot.reslt && \
	$(NRDIFF) sphoot.reslt $(NRANS)

dates1.dat : $(NRDAT)/dates1.dat
	/bin/cp $< $@

fncval.dat : $(NRDAT)/fncval.dat
	/bin/cp $< $@

matrx1.dat : $(NRDAT)/matrx1.dat
	/bin/cp $< $@

matrx2.dat : $(NRDAT)/matrx2.dat
	/bin/cp $< $@

matrx3.dat : $(NRDAT)/matrx3.dat
	/bin/cp $< $@

spctrl.dat : $(NRDAT)/spctrl.dat
	/bin/cp $< $@

table1.dat : $(NRDAT)/table1.dat
	/bin/cp $< $@

table2.dat : $(NRDAT)/table2.dat
	/bin/cp $< $@

tarray.dat : $(NRDAT)/tarray.dat
	/bin/cp $< $@

text.dat : $(NRDAT)/text.dat
	/bin/cp $< $@

dat: dates1.dat fncval.dat matrx1.dat matrx2.dat matrx3.dat spctrl.dat table1.dat table2.dat tarray.dat text.dat

# Target for recipes library
OBJECTS = addint.o airy.o amebsa.o amoeba.o amotry.o amotsa.o anneal.o \
	anorm2.o arcmak.o arcode.o arcsum.o asolve.o atimes.o avevar.o \
	balanc.o banbks.o bandec.o banmul.o bcucof.o bcuint.o beschb.o \
	bessi.o bessi0.o bessi1.o bessik.o bessj.o bessj0.o bessj1.o \
	bessjy.o bessk.o bessk0.o bessk1.o bessy.o bessy0.o bessy1.o \
	beta.o betacf.o betai.o bico.o bksub.o bnldev.o brent.o broydn.o \
	bsstep.o caldat.o chder.o chebev.o chebft.o chebpc.o chint.o \
	chixy.o choldc.o cholsl.o chsone.o chstwo.o cisi.o cntab1.o \
	cntab2.o convlv.o copy.o correl.o cosft1.o cosft2.o covsrt.o \
	crank.o cyclic.o daub4.o dawson.o dbrent.o ddpoly.o decchk.o \
	df1dim.o dfpmin.o dfridr.o dftcor.o dftint.o difeq.o \
	dlinmin.o \
	eclass.o eclazz.o ei.o eigsrt.o elle.o ellf.o ellpi.o \
	elmhes.o erfcc.o erff.o erffc.o eulsum.o evlmem.o expdev.o \
	expint.o f1dim.o factln.o factrl.o fasper.o fdjac.o fgauss.o \
	fit.o fitexy.o fixrts.o fleg.o flmoon.o fmin.o four1.o \
	fourew.o fourfs.o fourn.o fpoly.o fred2.o fredin.o frenel.o \
	frprmn.o ftest.o gamdev.o gammln.o gammp.o gammq.o gasdev.o \
	gaucof.o gauher.o gaujac.o gaulag.o gauleg.o gaussj.o gcf.o \
	golden.o gser.o hpsel.o hpsort.o hqr.o hufapp.o hufdec.o \
	hufenc.o hufmak.o hunt.o hypdrv.o hypgeo.o hypser.o icrc.o \
	icrc1.o igray.o indexx.o interp.o irbit1.o irbit2.o \
	jacobi.o jacobn.o julday.o kendl1.o kendl2.o kermom.o ks2d1s.o \
	ks2d2s.o ksone.o kstwo.o laguer.o lfit.o linbcg.o linmin.o \
	lnsrch.o locate.o lop.o lubksb.o ludcmp.o machar.o matadd.o \
	matsub.o medfit.o memcof.o metrop.o mgfas.o mglin.o midexp.o \
	midinf.o midpnt.o midsql.o midsqu.o miser.o mmid.o mnbrak.o \
	mnewt.o moment.o mp2dfr.o mpdiv.o mpinv.o mpmul.o mpops.o mppi.o \
	mprove.o mpsqrt.o mrqcof.o mrqmin.o newt.o odeint.o orthog.o \
	pade.o pccheb.o pcshft.o pearsn.o period.o piksr2.o piksrt.o \
	pinvs.o plgndr.o poidev.o polcoe.o polcof.o poldiv.o polin2.o \
	polint.o powell.o predic.o probks.o psdes.o pwt.o pwtset.o \
	pythag.o pzextr.o qgaus.o qrdcmp.o qromb.o qromo.o qroot.o \
	qrsolv.o qrupdt.o qsimp.o qtrap.o quad3d.o quadct.o quadmx.o \
	quadvl.o ran0.o ran1.o ran2.o ran3.o ran4.o rank.o ranpt.o \
	ratint.o ratlsq.o ratval.o rc.o rd.o realft.o rebin.o red.o \
	relax.o relax2.o resid.o revcst.o reverse.o rf.o rj.o rk4.o \
	rkck.o rkdumb.o rkqs.o rlft3.o rofunc.o rotate.o rsolv.o \
	rstrct.o rtbis.o rtflsp.o rtnewt.o rtsafe.o rtsec.o rzextr.o \
	savgol.o scrsho.o select.o selip.o shell.o shoot.o shootf.o \
	simp1.o simp2.o simp3.o simplx.o simpr.o sinft.o slvsm2.o \
	slvsml.o sncndn.o snrm.o sobseq.o solvde.o sor.o sort.o sort2.o \
	sort3.o spctrm.o spear.o sphbes.o splie2.o splin2.o spline.o \
	splint.o spread.o sprsax.o sprsin.o sprspm.o sprstm.o sprstp.o \
	sprstx.o stifbs.o stiff.o stoerm.o svbksb.o svdcmp.o svdfit.o \
	svdvar.o toeplz.o tptest.o tqli.o trapzd.o tred2.o tridag.o \
	trncst.o trnspt.o ttest.o tutest.o twofft.o vander.o vegas.o \
	voltra.o wt1.o wtn.o wwghts.o zbrac.o zbrak.o zbrent.o zrhqr.o \
	zriddr.o zroots.o

lib: $(OBJECTS)
	$(AR) rv librecipes_$(NRTYPE).a $^
# ranlib not done because it is obsolete

dbglib: $(OBJECTS)
	$(MAKE) clean
	$(MAKE) DEBUG=TRUE lib
	$(AR) rv librecipes_dbg$(NRTYPE).a $^

clean : ;
	/bin/rm *.o *.out
