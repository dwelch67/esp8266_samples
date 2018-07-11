

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char data[1000000000];
FILE *fp;

int main ( int argc, char *argv[] )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int rc;
    unsigned int nsegs;
    unsigned int ns;
    unsigned int entry;
    unsigned int soff;
    unsigned int ssize;
    unsigned int sum;

    if(argc<2)
    {
        printf("What?\n");
        return(1);
    }
    fp=fopen(argv[1],"rb");
    if(fp==NULL)
    {
        printf("Error opening file [%s]\n",argv[1]);
        return(1);
    }
    rb=fread(data,1,sizeof(data),fp);
    fclose(fp);
    printf("read %u bytes 0x%08X\n",rb,rb);

rc=0xEF;
for(ra=0;ra<rb;ra++) rc^=data[ra];
printf("0x%02X\n",rc);
rc=0xEF;
for(ra=8;ra<rb;ra++) rc^=data[ra];
printf("0x%02X\n",rc);


    if(data[0]!=0xE9)
    {
        printf("bad start byte\n");
        return(1);
    }




    nsegs=data[1];
    printf("segments %u\n",nsegs);
    switch(data[2])
    {
        case 0x0: printf("QIO\n"); break;
        case 0x1: printf("QOUT\n"); break;
        case 0x2: printf("DIO\n"); break;
        case 0x3: printf("DOUT\n"); break;
        default: printf("UNKNOWN\n"); break;
    }

    switch((data[3]>>4)&0xF)
    {
        case 0x0: printf("512K\n"); break;
        case 0x1: printf("256K\n"); break;
        case 0x2: printf("1M\n"); break;
        case 0x3: printf("2M\n"); break;
        case 0x4: printf("4M\n"); break;
        default: printf("UNKNOWN\n"); break;

    }
    switch((data[3]>>0)&0xF)
    {
        case 0x0: printf("40MHz\n"); break;
        case 0x1: printf("26MHZ\n"); break;
        case 0x2: printf("20MHz\n"); break;
        case 0x3: printf("80MHz\n"); break;
        default: printf("UNKNOWN\n"); break;
    }
    entry=0;
    entry<<=8; entry|=data[7];
    entry<<=8; entry|=data[6];
    entry<<=8; entry|=data[5];
    entry<<=8; entry|=data[4];
    printf("entry 0x%08X\n",entry);


    ra=8;
    sum=0xEF;
    for(ns=0;ns<nsegs;ns++)
    {
        soff=0;
        soff<<=8; soff|=data[ra+3];
        soff<<=8; soff|=data[ra+2];
        soff<<=8; soff|=data[ra+1];
        soff<<=8; soff|=data[ra+0];
        ra+=4;
        ssize=0;
        ssize<<=8; ssize|=data[ra+3];
        ssize<<=8; ssize|=data[ra+2];
        ssize<<=8; ssize|=data[ra+1];
        ssize<<=8; ssize|=data[ra+0];
        ra+=4;
        printf("segment %u\n",ns);
        printf("offset 0x%08X\n",soff);
        printf("size 0x%08X %u\n",ssize,ssize);
//break;
        for(rc=0;rc<20;rc++)
        {
            printf("0x%02X\n",data[ra+rc]);
        }
        for(rc=0;rc<ssize;rc++) sum^=data[ra+rc];

        ra+=ssize;





    }
    for(;ra<rb;ra++) sum^=data[ra];

    printf("0x%08X\n",sum);



    return(0);
}
