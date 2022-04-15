#!/usr/bin/python
#------------------------------------------------------------------------------
# reads input .xsv file with the scan results
# first line is the scale factor
# the other (X,Y) (X,Y-sigma) (X,Y+sigma)
# output file is stored in the same directory with the input file
#------------------------------------------------------------------------------
import codecs, argparse, sys, os, time
# from chardet import detect
# open it with utf-8 encoding 
# f=codecs.open("myfile.txt","r",encoding='utf-8')

#------------------------------------------------------------------------------
def parse_parameters():
    desc = 'read thermal measurements'
    
    parser = argparse.ArgumentParser(description=desc)

    if (len(sys.argv) == 1):
        parser.print_help()
        sys.exit()

    parser.add_argument('--file'    , type=str, help='expanded .fcl file name', default = None)
    parser.add_argument('--verbose' , type=int, help='verbose'                , default = 0   )

    args = parser.parse_args()

    fn            = args.file
    # self.fVerbose = args.verbose
    return fn

#------------------------------------------------------------------------------
def process(fn):
#    f    = codecs.open(fn,"r",encoding='utf-16')
    f    = codecs.open(fn,"r",encoding='utf-8')
    fout = open(fn.replace('.txt','.dat'),'w')

    il = 0;
    scale = 1.;
    for line in f:
        print (line)
        # skip comment lines
        if (line[0] == '#') : continue;
        words = line.strip('\n').strip('\r').strip('').split(',');
        nw = len(words);
        print ('nw=',nw,words);
        if (nw == 3) and (words[0] != '') :
            # data
            il = il+1
            print(il,nw,words)
            x0 = float(words[0]);
            x1 = float(words[1]);
            scale = x0/x1;
            # fout.write(str(il)+' '+' '.join(words[1:320])+'\n')
        elif (nw == 7):
            t  = float(words[0])
            x0 = float(words[1])/scale;
            x1 = float(words[3])/scale;
            x2 = float(words[5])/scale;
            sigma = (x2-x1)/2;
            fout.write("%10.3f %10.3f %10.3f\n"%(t,x0,sigma));

    f.close()
    fout.close();
    #
        # for line in f.readlines():
#        print(line)
            
#        if (words[0] == 'Time'):
#            # reformat first line
#            l='Time/I:Pressure/I:Flow/C:Heater1/F:Heater2/F:Comment/C:Smth/F'
#            for i in range(1,41):
#                l += ':t%i/F'%i
#        else:
#            utc_time   = datetime.strptime(words[0], "%m/%d/%Y %H:%M:%S")
#            epoch_time = (utc_time - datetime(1970, 1, 1)).total_seconds()
#            words[0]   ='%i'%epoch_time
#            words[2]   = '"'+words[2]+'"';  # for ROOT, strings have to be enclosed in double quotes
#            words[5]   = '"'+words[5]+'"';
#            l = ','.join(words)
#        print(l)

if (__name__ == '__main__'):

    # fn = "/projects/cms/data/ti400/csv/FB_01255.csv";
    fn = parse_parameters();
    
    process(fn);  # 90.1 C
