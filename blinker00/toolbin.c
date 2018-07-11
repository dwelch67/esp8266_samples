
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char data[0x10000];
FILE *fp;

int main ( int argc, char *argv[] )
{
    unsigned int ra;
    unsigned int rb;
    unsigned int sum;

    if(argc<3)
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
    memset(data,0,sizeof(data));
    rb=fread(data,1,sizeof(data),fp);
    fclose(fp);
    printf("read %u bytes 0x%08X\n",rb,rb);

    rb+=3;
    rb&=(~3);

    fp=fopen(argv[2],"wb");
    if(fp==NULL)
    {
        printf("Error creating file [%s]\n",argv[2]);
        return(1);
    }
    ra=0xE9;
    fwrite(&ra,1,1,fp);
    ra=3;
    fwrite(&ra,1,1,fp);
    ra=0;
    fwrite(&ra,1,1,fp);
    ra=0;
    fwrite(&ra,1,1,fp);
    ra=0x40100100;
    fwrite(&ra,1,4,fp);

    ra=0x40100000;
    fwrite(&ra,1,4,fp);
    ra=rb;
    fwrite(&ra,1,4,fp);
    fwrite(data,1,rb,fp);

    ra=0x3FFE8000;
    fwrite(&ra,1,4,fp);
    ra=4;
    fwrite(&ra,1,4,fp);
    ra=0x00000001;
    fwrite(&ra,1,4,fp);

    ra=0x3FFE8004;
    fwrite(&ra,1,4,fp);
    ra=16;
    fwrite(&ra,1,4,fp);
    ra=0x00000000;
    fwrite(&ra,1,4,fp);
    fwrite(&ra,1,4,fp);
    fwrite(&ra,1,4,fp);
    fwrite(&ra,1,4,fp);

    ra=0;
    for(;(rb&0xF)!=0xF;rb++)
    {
        fwrite(&ra,1,1,fp);
    }
    sum=0xEF;
    sum^=0x01;
    for(ra=0;ra<rb;ra++) sum^=data[ra];
printf("0x%02X\n",sum);
    fwrite(&sum,1,1,fp);
    fclose(fp);
    printf("Done.\n");
    return(0);
}
