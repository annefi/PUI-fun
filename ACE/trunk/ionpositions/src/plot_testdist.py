#!/usr/bin/python
from scipy import zeros, exp,sqrt,mean
from Gnuplot import Gnuplot, GridData, Data

dim=1000
xdim=512
ydim=128
ionname=''
allcounts1=[]
allcounts2=[]
mode=0

f=open("/home/ivar/berger/projects/ionpositions/test_analyse_data/ion_para.dat")
print "loading ion_para.dat"

s=f.readline()
k=s.split()
s=f.readline()
numberions=int(k[5])
nomcounts=zeros([numberions])
fitval=zeros([numberions,dim])
normval=zeros([numberions,dim])
fitval2=zeros([numberions,dim])
normval2=zeros([numberions,dim])

sollsum=0
summ=[]
sumnorm=[]
summ2=[]
sumnorm2=[]

mittelwert=[]
mittelwert2=[]
mwnorm=[]
mwnorm2=[]
sigma=[]
sigma2=[]
signorm=[]
signorm2=[]

for i in range(numberions):
    mittelwert.append(0.)
    mittelwert2.append(0.)
    mwnorm.append(0.)
    mwnorm2.append(0.)
    sigma.append(0.)
    sigma2.append(0.)
    signorm.append(0.)
    signorm2.append(0.)

for ion in range(numberions):
    s=f.readline()
    k=s.split()
    ionname+= ' '+k[0]
    nomcounts[ion]=int(float(k[10])+0.5)
    sollsum+=int(float(k[10])+0.5)

ion_names=ionname.split()
f.close()

#load first erg-file


f=open("/home/ivar/berger/projects/ionpositions/test_analyse_data/erg_testdata30_1000_fm0.dat")
for step in range(dim):
    s=f.readline()
    k=s.split()
    s=f.readline()
    tmpsum=0.
    tmpsumnorm=0.
    for ion in range(int(k[5])):
        s=f.readline()
        k=s.split()
        fitval[ion][step]=int(float(k[10])+0.5)
        normval[ion][step]=int(float(k[11])+0.5)
        mittelwert[ion]+=float(k[10])
        mwnorm[ion]+=float(k[11])
        tmpsum+=float(k[10])
        tmpsumnorm+=float(k[11])
    summ.append(int(tmpsum+0.5))
    sumnorm.append(int(tmpsumnorm+0.5))
f.close()

#berechne mittelwert und standardabweichung

for ion in range(numberions):
    mittelwert[ion]=mittelwert[ion]/float(dim)
    mwnorm[ion]=mwnorm[ion]/float(dim)

f=open("/home/ivar/berger/projects/ionpositions/test_analyse_data/erg_testdata30_1000_fm0.dat")
for step in range(dim):
    s=f.readline()
    k=s.split()
    s=f.readline()
    for ion in range(int(k[5])):
        s=f.readline()
        k=s.split()
        sigma[ion]+=(mittelwert[ion]-float(k[10]))*(mittelwert[ion]-float(k[10]))
        signorm[ion]+=(mwnorm[ion]-float(k[11]))*(mwnorm[ion]-float(k[11]))

f.close()

for ion in range(numberions):
    sigma[ion]=sqrt(sigma[ion]/float(dim-1))
    signorm[ion]=sqrt(signorm[ion]/float(dim-1))

    
#erzeuge histogram

diffrange=zeros([numberions])
diffrangenorm=zeros([numberions])

for ion in range(numberions):
    for step in range(dim):
        diff=abs(fitval[ion][step]-nomcounts[ion])
        diffnorm=abs(normval[ion][step]-nomcounts[ion])
        if (int(diff)>diffrange[ion]):
            diffrange[ion]=int(diff)
        if (int(diffnorm)>diffrangenorm[ion]):
            diffrangenorm[ion]=int(diffnorm)

    diffrange[ion]=diffrange[ion]+1
    diffrangenorm[ion]=diffrangenorm[ion]+1

hist=[]
histnorm=[]
for ion in range(numberions):
    histtmp=[]
    histtmpnorm=[]
    for val in range(-diffrange[ion],diffrange[ion]):
        histtmp.append([(nomcounts[ion]+val),0])
    hist.append(histtmp)
    for val in range(-diffrangenorm[ion],diffrangenorm[ion]):
        histtmpnorm.append([(nomcounts[ion]+val),0])
    histnorm.append(histtmpnorm)

for ion in range(numberions):
    for step in range(dim):
        for val in range((diffrange[ion]*2)):
            if (fitval[ion][step]==hist[ion][val][0]):
                hist[ion][val][1]+=1
        for val in range((diffrangenorm[ion]*2)):
            if (normval[ion][step]==histnorm[ion][val][0]):
                histnorm[ion][val][1]+=1


        
gphist=[]
gphistnorm=[]
for ion in range(numberions):
    gphisttmp=Data(hist[ion])
    gphisttmp.set_option_colonsep("using", "1:2")
#    gphisttmp.set_option_colonsep("title",  "'fm0 %s rc:%f mw:%f sig:%f'" %(ion_names[ion],nomcounts[ion],mittelwert[ion],sigma[ion]))
    gphisttmp.set_option_colonsep("title",  "'%s (%i counts generated)'" %(ion_names[ion],nomcounts[ion]))
    gphisttmp.set_option_colonsep("with","boxes")
    gphist.append(gphisttmp)
for ion in range(numberions):
    gphisttmp=Data(histnorm[ion])
    gphisttmp.set_option_colonsep("using", "1:2")
#    gphisttmp.set_option_colonsep("title",  "'norm fm0 %s rc:%f mw:%f sig:%f'" %(ion_names[ion],nomcounts[ion],mwnorm[ion],signorm[ion]))
    gphisttmp.set_option_colonsep("title",  "'%s'" %(ion_names[ion]))
    gphisttmp.set_option_colonsep("with","boxes")
    gphistnorm.append(gphisttmp)

#load 2. erg-file

f=open("/home/ivar/berger/projects/ionpositions/test_analyse_data/erg_testdata30_1000_fm1.dat")
for step in range(dim):
    s=f.readline()
    k=s.split()
    s=f.readline()
    tmpsum=0.
    tmpsumnorm=0.
    for ion in range(int(k[5])):
        s=f.readline()
        k=s.split()
        fitval2[ion][step]=int(float(k[10])+0.5)
        normval2[ion][step]=int(float(k[11])+0.5)
        mittelwert2[ion]+=float(k[10])
        mwnorm2[ion]+=float(k[11])
        tmpsum+=float(k[10])
        tmpsumnorm+=float(k[11])
    summ2.append(int(tmpsum+0.5))
    sumnorm2.append(int(tmpsumnorm+0.5))

f.close()


for ion in range(numberions):
    mittelwert2[ion]=mittelwert2[ion]/float(dim)
    mwnorm2[ion]=mwnorm2[ion]/float(dim)

f=open("/home/ivar/berger/projects/ionpositions/test_analyse_data/erg_testdata30_1000_fm1.dat")
for step in range(dim):
    s=f.readline()
    k=s.split()
    s=f.readline()
    for ion in range(int(k[5])):
        s=f.readline()
        k=s.split()
        sigma2[ion]+=(mittelwert2[ion]-float(k[10]))*(mittelwert2[ion]-float(k[10]))
        signorm2[ion]+=(mwnorm2[ion]-float(k[11]))*(mwnorm2[ion]-float(k[11]))

f.close()

for ion in range(numberions):
    sigma2[ion]=sqrt(sigma2[ion]/float(dim-1))
    signorm2[ion]=sqrt(signorm2[ion]/float(dim-1))

#ereuge histogram

diffrange2=zeros([numberions])
diffrangenorm2=zeros([numberions])

for ion in range(numberions):
    for step in range(dim):
        diff=abs(fitval2[ion][step]-nomcounts[ion])
        diffnorm=abs(normval2[ion][step]-nomcounts[ion])
        if (int(diff)>diffrange2[ion]):
            diffrange2[ion]=int(diff)
        if (int(diffnorm)>diffrangenorm2[ion]):
            diffrangenorm2[ion]=int(diffnorm)

    diffrange2[ion]=diffrange2[ion]+1
    diffrangenorm2[ion]=diffrangenorm2[ion]+1

hist2=[]
histnorm2=[]
for ion in range(numberions):
    histtmp=[]
    histtmpnorm=[]
    for val in range(-diffrange[ion],diffrange[ion]):
        histtmp.append([(nomcounts[ion]+val),0,0])
    hist2.append(histtmp)
    for val in range(-diffrangenorm[ion],diffrangenorm[ion]):
        histtmpnorm.append([(nomcounts[ion]+val),0,0])
    histnorm2.append(histtmpnorm)


for ion in range(numberions):
    for step in range(dim):
        for val in range((diffrange[ion]*2)):
            if (fitval2[ion][step]==hist2[ion][val][0]):
                hist2[ion][val][1]+=1
        for val in range((diffrangenorm[ion]*2)):
            if (normval2[ion][step]==histnorm2[ion][val][0]):
                histnorm2[ion][val][1]+=1


for ion in range(numberions):
    for val in range((diffrange[ion]*2)):
        hist2[ion][val][2]=int(sqrt(hist2[ion][val][1]+0.5))
    for val in range((diffrangenorm[ion]*2)):
        histnorm2[ion][val][2]=int(sqrt(histnorm2[ion][val][1]+0.5))



gphist2=[]
gphistnorm2=[]
print "hist2[1] = ",hist2[1]
for ion in range(numberions):
    gphisttmp=Data(hist2[ion])
    gphisttmp.set_option_colonsep("using", "1:2")
#    gphisttmp.set_option_colonsep("title",  "'fit fm1 %s rc:%f mw:%f sig:%f'" %(ion_names[ion],nomcounts[ion],mittelwert2[ion],sigma2[ion]))
    gphisttmp.set_option_colonsep("title",  "'%s'" %(ion_names[ion]))
    gphisttmp.set_option_colonsep("with","boxes")
#    gphisttmp.set_option_colonsep("with","yerrorbars")
    gphist2.append(gphisttmp)
for ion in range(numberions):
    gphisttmp=Data(histnorm2[ion])
    gphisttmp.set_option_colonsep("using", "1:2")
#    gphisttmp.set_option_colonsep("title",  "'norm fm1 %s rc:%f mw:%f sig:%f'" %(ion_names[ion],nomcounts[ion],mwnorm2[ion],signorm2[ion]))
    gphisttmp.set_option_colonsep("title",  "'%s'" %(ion_names[ion]))
    gphisttmp.set_option_colonsep("with","boxes")
#    gphisttmp.set_option_colonsep("with","yerrorbars")
    gphistnorm2.append(gphisttmp)

#erzeuge histogram für summenabweichung
diffsum=0
diffsumnorm=0
diffsum2=0
diffsumnorm2=0
for step in range(dim):
    tmpdiffsum=abs(summ[step]-sollsum)
    tmpdiffsumnorm=abs(sumnorm[step]-sollsum)
    tmpdiffsum2=abs(summ2[step]-sollsum)
    tmpdiffsumnorm2=abs(sumnorm2[step]-sollsum)
    if (int(tmpdiffsum)>diffsum):
        diffsum=int(tmpdiffsum)
    if (int(tmpdiffsumnorm)>diffsumnorm):
        diffsumnorm=int(tmpdiffsumnorm)
    if (int(tmpdiffsum2)>diffsum2):
        diffsum2=int(tmpdiffsum2)
    if (int(tmpdiffsumnorm2)>diffsumnorm2):
        diffsumnorm2=int(tmpdiffsumnorm2)

diffsum=diffsum+1
diffsumnorm=diffsumnorm+1
diffsum2=diffsum2+1
diffsumnorm2=diffsumnorm2+1

histsum=[]
histsumnorm=[]
histsum2=[]
histsumnorm2=[]
for val in range(-diffsum,diffsum+1):
    histsum.append([(sollsum+val),0])
for val in range(-diffsumnorm,diffsumnorm+1):
    histsumnorm.append([(sollsum+val),0])
for val in range(-diffsum2,diffsum2+1):
    histsum2.append([(sollsum+val),0])
for val in range(-diffsumnorm2,diffsumnorm2+1):
    histsumnorm2.append([(sollsum+val),0])
for step in range(dim):
    for val in range(diffsum*2+1):
        if (summ[step]==histsum[val][0]):
            histsum[val][1]+=1
    for val in range((diffsumnorm*2+1)):
        if (sumnorm[step]==histsumnorm[val][0]):
            histsumnorm[val][1]+=1
    for val in range(diffsum2*2+1):
        if (summ2[step]==histsum2[val][0]):
            histsum2[val][1]+=1
    for val in range((diffsumnorm2*2+1)):
        if (sumnorm2[step]==histsumnorm2[val][0]):
            histsumnorm2[val][1]+=1

print "histsum = ",histsum
gphistsum=Data(histsum)
gphistsum.set_option_colonsep("using", "1:2")
gphistsum.set_option_colonsep("title",  "'sum soll:%f'" %(sollsum))
gphistsum.set_option_colonsep("with","boxes")
gphistsumnorm=Data(histsumnorm)
gphistsumnorm.set_option_colonsep("using", "1:2")
gphistsumnorm.set_option_colonsep("title",  "'sumnorm soll:%f'" %(sollsum))
gphistsumnorm.set_option_colonsep("with","boxes")
gphistsum2=Data(histsum2)
gphistsum2.set_option_colonsep("using", "1:2")
gphistsum2.set_option_colonsep("title",  "'sum2 soll:%f'" %(sollsum))
gphistsum2.set_option_colonsep("with","boxes")
gphistsumnorm2=Data(histsumnorm2)
gphistsumnorm2.set_option_colonsep("using", "1:2")
gphistsumnorm2.set_option_colonsep("title",  "'sumnorm2 soll:%f'" %(sollsum))
gphistsumnorm2.set_option_colonsep("with","boxes")


#!!!!!!!!!!!!!!!!!!!!!! plotte daten !!!!!!!!!!!!!!!!!!!!!!!!!!!!



        
ion=2
for ion in range(numberions):
    
    xrange=[nomcounts[ion]-diffrange[ion],nomcounts[ion]+diffrange[ion]]
    #xrange=[610,630]
    gp=Gnuplot()
    gp("set xlabel 'Fit Result'")
    gp("set ylabel 'Number of Fit Results' ")
    gp("set xrange[%i:%i]" % (xrange[0],xrange[1]))
    #gp("set title 'Fitergebnis 1000 Datensätze'")
    gp("set title ''")
    gp("set border 15 lw 2")

    print "ionnames = ",ionname
#    gp.plot(gphist[ion],gphist2[ion],gphistnorm[ion],gphistnorm2[ion])
    gp.plot(gphist[ion])
    #gp.plot(gphistsum,gphistsum2,gphistsumnorm,gphistsumnorm2)
    gp("set term postscript color 18")
    gp.hardcopy("%s.ps"%(ion_names[ion]), color=True, fontsize=18)
    #gp.hardcopy("Summe.ps", color=True)
