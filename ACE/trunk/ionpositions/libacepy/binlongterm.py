from scipy import zeros
inname="/data/wimmer/ace/lowpaps/axlv2_sumwhol_1999.dat"
outname="axlv2_sumwhol_1999_bin.dat"
infile=open(inname)
outfile=open(outname,"w")
outfile.write("*****\n")
for step in range(58):
    print "step : ",step
    s=infile.readline()
    k=s.split()
    xdim,ydim=int(k[0]),int(k[1])
    et_mat=zeros([xdim,ydim])
    for x in range(xdim):
        s=infile.readline()
        k=s.split()
        for y in range(len(k)):
            et_mat[x][y]=float(k[y])
    et_mat_bin_1=zeros([xdim,ydim/2])
    et_mat_bin_2=zeros([xdim/2,ydim/2])
    #print xdim,ydim
    #print xdim/2,ydim/2

    for x in range(xdim):
        et_mat_bin_1[x][0]=et_mat[x][0]
    for x in range(xdim):
        for y in range(1,ydim-1):
            #print y,(y+1)/2
            et_mat_bin_1[x][(y+1)/2]+=et_mat[x][y]

    for y in range(ydim/2):
        et_mat_bin_2[0][y]=et_mat_bin_1[0][y]
    for y in range(ydim/2):
        for x in range(1,xdim-1):
            et_mat_bin_2[(x+1)/2][y]+=et_mat_bin_1[x][y]
    outfile.write("%i\t%i\n"%(xdim/2,ydim/2))
    for x in range(xdim/2):
        for y in range(ydim/2):
            outfile.write("%.3f "%(et_mat_bin_2[x][y]))
        outfile.write("\n")

outfile.close()

