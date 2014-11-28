#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int currentLevel=0;
int maxLevel=1;
FILE *ofp;
const char **includedirs;

static FILE *openFileSomewhere(const char *filename) {
        const char **p=includedirs;
        while(*p) {
                //build name
                char name[256];
                strcpy(name,*p);
                strcat(name,"/");
                strcat(name,filename);

                FILE *ifp=fopen(name,"rt");
                if(ifp) 
                        return ifp;
                p++;
        }
        return NULL;
}

static FILE *openFileHere(const char *filename) {
        FILE *ifp=fopen(filename,"rt");
        if(ifp) 
                return ifp;
        else
                return openFileSomewhere(filename);
}

static int defDump(const char *line) {
        if(fputs(line,ofp)==EOF) {
                fprintf(stderr,"hdrexp: write error\n");
                return -1;
        } else
                return 0;
}

static int expandFile(FILE *ifp);

static int processLine(const char *line) {
        if(currentLevel>maxLevel) return defDump(line);

        const char *p=line;
        while(*p==' ' || *p=='\t') p++;
        if(*p!='#') return defDump(line);
        p++;
        while(*p==' ' || *p=='\t') p++;
        if(p[0]!='i' ||
           p[1]!='n' ||
           p[2]!='c' ||
           p[3]!='l' ||
           p[4]!='u' ||
           p[5]!='d' ||
           p[6]!='e')
                return defDump(line);
        p+=7;
        while(*p==' ' || *p=='\t') p++;

        char echar;
        if(*p=='<')
                echar='>';
        else if(*p=='"')
                echar='"';
        else
                return defDump(line);

        const char *start=p+1;
        const char *end=start+1;
        while(*end && *end!=echar) end++;
        if(!*end)
                return defDump(line);

        char incName[256];
        char *d=incName;
        while(start<end) {
                *d++=*start++;
        }
        *d='\0';

        FILE *ifp;
        if(*p=='"')
                ifp=openFileHere(incName);
        else
                ifp=openFileSomewhere(incName);
        if(ifp)
                return expandFile(ifp);
        else
                return defDump(line);
}



static int expandFile(FILE *ifp) {
        currentLevel++;
        char line[256];
        int r=0;
        while(fgets(line,256,ifp) && r==0) 
                r=processLine(line);
        currentLevel--;
        return r;
}


int main(int argc, const char *argv[]) {
        if(argc<3) {
                printf("hdrexp - v1.0\n");
                printf("Usage: hdrexp <infile> <outfile> [-<maxlevel>] [includedir...]\n");
                printf(" infile       input header file\n");
                printf(" outfile      output header file\n");
                printf(" maxlevel     maximum expand level (default=1)\n");
                printf(" includedir   include directories\n");
                return 1;
        }

        FILE *ifp=fopen(argv[1],"rt");
        if(!ifp) {
                fprintf(stderr,"hdrexp: could not open %s\n",argv[1]);
                return 2;
        }

        ofp=fopen(argv[2],"wt");
        if(!ofp) {
                fprintf(stderr,"hdrexp: could not create %s\n",argv[2]);
                return 3;
        }

        int r;
        if(argv[3] && argv[3][0]=='-') {
                maxLevel=atoi(argv[3]+1);
                includedirs=argv+4;
        } else
                includedirs=argv+3;

        r=expandFile(ifp);

        fclose(ifp);
        fclose(ofp);

        if(r) {
                remove(argv[2]);
        }
        return r;
}

