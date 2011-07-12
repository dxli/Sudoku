// A small program to solve a square number puzzle
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<sys/time.h>
#include<time.h>
#include <sys/resource.h>


int rules(int,int);
void t0print(),unique1();
int t0[9][9], tflag0[9][9],tflag[9][9],tset[9][9][9]; // to store the real possiblities

struct rusage t_start,t_end;

int main()
{
    int i,j,k,i0;
    /* Initilize the random generator*/
    char random_buf[256+1],*filename1;
    struct timeval time0,time1;
    FILE *f1;
    unsigned int account=0;

    filename1=random_buf;
    initstate(1,random_buf,256);
    if ((f1=fopen("/dev/urandom","r"))!=NULL) {
        for (i=0;i<256;i++) *filename1++=fgetc(f1);
        fclose(f1);
    } else {
        gettimeofday(&time1,NULL);
        initstate(time1.tv_usec,random_buf,256);
    }
    /* */
    char *request_method ;
    int content_length;
    char *cgiinput ;
    char **cgivars ;
    char **pairlist ;
    int paircount ;
    char *nvpair ;
    char *eqpos ;

    /* strcasecmp() is not supported in Windows-- use strcmpi() instead */
    printf("Content-type: text/html\n\n");
    if ( strcasecmp(getenv("CONTENT_TYPE"), "application/x-www-form-urlencoded")) {
        printf("Content-Type: text/plain\n\n") ;
        printf("getcgivars(): Unsupported Content-Type.\n") ;
        exit(1) ;
    }
    if ( !(content_length = atoi(getenv("CONTENT_LENGTH"))) ) {
        printf("Content-Type: text/plain\n\n") ;
        printf("getcgivars(): No Content-Length was sent with the POST request.\n") ;
        exit(1) ;
    }
    if (content_length > 406) content_length=406;
    if ( !(cgiinput= (char *) malloc(content_length+1)) ) {
        printf("Content-Type: text/plain\n\n") ;
        printf("getcgivars(): Couldn't malloc for cgiinput.\n") ;
        exit(1) ;
    }
    if (!fread(cgiinput, content_length, 1, stdin)) {
        printf("Content-Type: text/plain\n\n") ;
        printf("getcgivars(): Couldn't read CGI input from STDIN.\n") ;
        exit(1) ;
    }
    cgiinput[content_length]='\0' ;
    for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            t0[i][j]=0;
        }
    }
    k=0;
    i0=0;
    int j0;
    j0=0;
//puts(cgiinput);
    while (k<content_length){
        if (cgiinput[k++]=='='){
            unsigned char xc;
            xc=cgiinput[k++];
            if ( xc >= (unsigned char) '1' && xc <= (unsigned char) '9') {
                i=i0/9;
                j=i0%9;
                t0[i][j]= xc - (unsigned char) '0';
                j0++;
            }
            if (++i0 == 81) break;
        }
    }
// to make the tflag and tset matrices

    for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            if (t0[i][j]) {
                tflag0[i][j]=tflag[i][j]=1;
                tset[i][j][0]=t0[i][j];
            } else {
                tflag[i][j]=9;
                for (k=0;k<9;k++) tset[i][j][k]=k+1;
            }
        }
    }
    printf("<html>\n");
    printf("<head>\n");
    printf("  <meta content=\"text/html; charset=ISO-8859-1\" http-equiv=\"content-type\">\n");
    printf("  <title>Solved</title>\n");
    printf("</head>\n");
    printf("<body style=\"color: rgb(0, 0, 0); background-color: rgb(255, 255, 204);\" alink=\"#000099\" link=\"#000099\" vlink=\"#990099\">\n");
    printf("<h1 style=\"text-align: center;\"><br> </h1>\n");
    for (i=0;i<9;i++){
        for (j=0;j<9;j++){
            if ( rules(i,j)== -1) {
                printf("<h1 style=\"text-align: center;\"><span style=\"color: rgb(255,0,0); background-color: rgb(0,255,0);\">Invalid digit found at position (%d , %d )</span></h1>\n",i+1,j+1);
                t0print();
                exit(0);
            }
        }
    }
    printf("<h1 style=\"text-align: center;\">My Answer</h1>\n");
    printf("<br>\n");
    printf("<hr style=\"width: 100%; height: 2px;\"><br>\n");
    printf("<div style=\"text-align: center;\"><span\n");
    printf(" style=\"color: rgb(255, 102, 102);\"></span><br>\n");

    if (j0<9) {
        printf("<center><h1><span style=\"color: rgb(235, 102, 100);\">I need some input!</span></h1></center>\n");
        goto end_point;
    }



    getrusage(RUSAGE_SELF,&t_start);

    for (;;){
// initialize the t0 matrix, to fill 0 for undecided
        int k0,k1,account=0;
point_start:
        account++;
        if ( account>>16) {
            goto end_point;
        }
        if (account) unique1();
        for (i=0;i<9;i++){
            for (j=0;j<9;j++){
                if (tflag[i][j]>1) {
                    t0[i][j]=0;
                    //randomly change the set order
                    k0=1+ (int) ( (double) random()/(RAND_MAX +1.0)*(tflag[i][j]-1));
                    k1=tset[i][j][0];
                    tset[i][j][0]=tset[i][j][k0];
                    tset[i][j][k0]=k1;
                }
            }
        }

        int k3;
        k3=0;

//check endpoint
point0:
        for (i=0;i<9;i++){
            for (j=0;j<9;j++){
                if (t0[i][j]==0) goto point1;
                if (rules(i,j)) goto point_start;
            }
        }
        /*
          for(i=0;i<9;i++){
                for(j=0;j<9;j++){
                        printf("%1d  ",rules(i,j));
                }
                putchar('\n');
        }
        */
end_point:
        getrusage(RUSAGE_SELF,&t_end);
        t0print();
        exit(0);
point1:
        do{
            i=(int) ((double) random()/(RAND_MAX+1.)*9.);
            j=(int) ((double) random()/(RAND_MAX+1.)*9.);
        }while (t0[i][j]);


        k=-1;
point2:
        k++;
        if ( k== tflag[i][j]) goto point_start;
        t0[i][j]= tset[i][j][k];
        k0=rules(i,j);
        //   printf("(%d %d) %d\n",i,j,k0);
        if (k0==1) {
            t0[i][j]=0;
            goto point2;
        }

        if (k0== -1) {
            //impossible
            tset[i][j][k]=tset[i][j][tflag[i][j] -1];
            tflag[i][j] --;
            /*
            printf("(%d %d) %d %d\n",i,j,t0[i][j],tset[i][j][k]);
            int k1;
            for(k1=0;k1<tflag[i][j];k1++) printf("%d ",tset[i][j][k1]);
            putchar('\n');
            */
            if (tflag[i][j]==1) t0[i][j]=tset[i][j][0];

            goto point_start;
        }
        goto point0;
    }
}

int rules(int x0,int y0)
{
    int i,j;

    for (i=0;i<9;i++){
        if (i!=x0 && t0[x0][y0] == t0[i][y0] ){
            if (tflag[i][y0] == 1) {
                //impossible
                return(-1);
            } else return(1);
        }
        if (i!=y0 && t0[x0][y0] == t0[x0][i] ){
            if (tflag[x0][i] == 1) {
                //impossible
                return(-1);
            } else return(1);
        }
    }
    i=(x0/3)*3;
    j=(y0/3)*3;
    int i0,j0;
    for (i0=0;i0<3;i0++){
        for (j0=0;j0<3;j0++){
            if (i!=x0 && j!=y0 && t0[x0][y0] == t0[i][j] ){
                if (tflag[i][j] == 1) {
                    //impossible
                    return(-1);
                } else return(1);
            }
            j++;
        }
        j-=3;
        i++;
    }
    return(0);

}


void t0print()
{
    int i,j,k;
    int flag=0;
    printf("<table style=\"background-color: rgb(255, 255, 255); margin-left: auto; margin-right: auto; width: 400px; text-align: center;\" border=\"2\" cellpadding=\"0\" cellspacing=\"0\">\n");
    printf("<tbody>\n");
    for (i=0;i<9;i++)
    {
        k=0;
        printf("<tr>\n");
        for (j=0;j<9;j++)
        {
            int ki,kj;
            ki=i/3;
            ki = (ki+1)%3;
            kj=j/3;
            kj = (kj+2)%3;


            if (tflag0[i][j]==1) printf("<td style=\"text-align: center; background-color: rgb(%d, %d, %d);\"><span style=\"background-color: rgb(255,255,255);\">%1d</span></td>\n",60*(ki+kj),240-60*(ki+kj),125-25*(ki-kj),t0[i][j]);
            else
                if (t0[i][j]==0) {
                    printf("<td style=\"text-align: center; background-color: rgb(%d, %d, %d); color: rgb(255,0,0);\"><span style=\"background-color: rgb(255,255,255);\">%1d</span></td>\n",60*(ki+kj),240-60*(ki+kj),125-25*(ki-kj),t0[i][j]);
                    flag=1;
                } else
                    printf("<td style=\"text-align: center; background-color: rgb(%d, %d, %d); color: rgb(0,0,255);\"><span style=\"background-color: rgb(255,255,255);\">%1d</span></td>\n",60*(ki+kj),240-60*(ki+kj),125-25*(ki-kj),t0[i][j]);
            k+=t0[i][j];
        }
        if (k!=45) flag=1;
        printf("<td><span style=\"text-align: center; color: rgb(0,255,0);\">%1d</span></td></tr>\n",k);
    }
    printf("<tr>");
    for (i=0;i<9;i++){
        k=0;
        for (j=0;j<9;j++) k += t0[j][i];
        if (k!=45) flag=1;
        printf("<td><span style=\"text-align: center; color: rgb(0,255,0);\">%1d</span></td>\n",k);
    }
    printf("<td></td></tr>");
    printf(" </tbody>\n");
    printf(" </table><br>\n");
    if (flag) printf("<center><h1><span style=\"color: rgb(255, 0, 0);\">Failed!</span></h1></center>\n");
    printf("<hr style=\"width: 100%; height: 100%; height: 2px; color: rgb(255, 102, 102);\">\n");
    printf("<p><center>CPU Time = %f Seconds",t_end.ru_utime.tv_sec-t_start.ru_utime.tv_sec+1.e-6*(t_end.ru_utime.tv_usec-t_start.ru_utime.tv_usec));
    printf("<h2>Back to the previous page to play again!<br>Or you can click to <a href=\"/index.html\">Play Again</a></h2></center>\n");
    printf("</body>\n");
    printf("</html>\n");

    putchar('\n');
}

void unique1()
{
    int i,j,k,tcountc[10],tcountp[10];
    int i0;
    int i1,j1;
    for (i=0;i<9;i++){
        //column
        for (i0=1;i0<=9;i0++) tcountc[i0]=0;
        for (j=0;j<9;j++) {
            for (k=0;k<tflag[i][j];k++) {
                tcountc[tset[i][j][k]]++;
                tcountp[tset[i][j][k]]=j;
            }
        }
        for (k=1;k<=9;k++) {
            if (tcountc[k]==1) {
                //unique
                t0[i][tcountp[k]]=k;
                tset[i][tcountp[k]][0]=k;
                tflag[i][tcountp[k]]=1;
            }
        }
        //row

        for (i0=1;i0<=9;i0++) tcountc[i0]=0;
        for (j=0;j<9;j++) {
            for (k=0;k<tflag[j][i];k++) {
                tcountc[tset[j][i][k]]++;
                tcountp[tset[j][i][k]]=j;
            }
        }
        for (k=1;k<=9;k++) {
            if (tcountc[k]==1) {
                //unique
                t0[tcountp[k]][i]=k;
                tset[tcountp[k]][i][0]=k;
                tflag[tcountp[k]][i]=1;
            }
        }

    }
    for (i=0;i<9;i+=3){
        for (j=0;j<9;j+=3){
            //group
            for (i0=1;i0<=9;i0++) tcountc[i0]=0;
            for (k=0;k<9;k++){
                i1=i+k/3;
                j1=j+k%3;
                int k1;
                for (k1=0;k1<tflag[i1][j1];k1++){
                    tcountc[tset[i1][j1][k1]]++;
                    tcountp[tset[i1][j1][k1]]=k;
                }
            }
            for (k=1;k<=9;k++){
                if (tcountc[k]==1) {
                    //unique
                    i1=i+tcountp[k]/3;
                    j1=j+tcountp[k]%3;
                    t0[i1][j1]=k;
                    tset[i1][j1][0]=k;
                    tflag[i1][j1]=1;
                }
            }
        }

    }
}

