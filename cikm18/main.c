//
//  main.c
//  eventSummarization
//
//  Created by Vanessa Cedeño on 10/5/16.
//  Copyright © 2016 Vanessa Cedeño. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

int m,n,mm,nn;

//MaxInt
int MaxInt=9999999;
int MinInt=-9999999;
int maxValue=0;
float minValue=9999999;
int sumMedians=0;
int maxlog=0;
double dailyrate=0;

char    path[100];
char    filename[100];
char    cpath[200];

float logfactorial(float n)
{
    float value=0;
    if (n==0)
        return value;
    else
    {
        //printf("n:%f\n",n);
        //printf("value:%f\n",n*log(n)-n+((log(n*(1+4*n*(1+2*n))))/6)+log(M_PI)/2);
        value=n*log(n)-n+((log(n*(1+4*n*(1+2*n))))/6)+log(M_PI)/2;
        return(value);
    }
}

void print2dMatrix(int matrix[mm][nn],int row, int column)
{
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<column; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void print2dCol(int matrix[mm][2],int row, int column)
{
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<column; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}
void print2dSumm(int matrix[mm][3],int row, int column)
{
    int i,j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<column; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

//sorts events by frequency
void insertionSort(int matrix[mm][3])
{
    int i,j;
    int temp,temp2,temp3;
    for(i=2;i<=m;i++)
    {
        temp=matrix[i][1];
        temp2=matrix[i][0];
        temp3=matrix[i][2];
        j=i-1;
        while ((temp > matrix[j][1]) && (j >= 1))
        {
            matrix[j+1][0]=matrix[j][0];
            matrix[j+1][1]=matrix[j][1];
            matrix[j+1][2]=matrix[j][2];
            j=j-1;
        }
        matrix[j+1][0]=temp2;
        matrix[j+1][1]=temp;
        matrix[j+1][2]=temp3;
    }
}

void printMatrix(int matrix[n],int column)
{
    int i;
    for (i=0;i<column; i++)
    {
        printf("%d ", matrix[i]);
    }
    printf("\n");
}

void printfMatrix(float matrix[n],int column)
{
    int i;
    for (i=0;i<column; i++)
    {
        printf("%f ", matrix[i]);
    }
    printf("\n");
}


//file into the matrix
void generateMatrix(FILE *fstream, int mat[1500][1500])
{
    char buffer[16384] ;
    char *record,*line;
    int i=0,j=0;
    
    while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
        record = strtok(line,",");
        while(record != NULL)
        {
            if (atoi(record)>maxValue)
                maxValue=atoi(record);
            mat[i][j++] = atoi(record) ;
            record = strtok(NULL,",");
            
        }
        ++i ;
        n=j;
        nn=n+1;
        j=0;
    }
    m=i;
    mm=m+1;
    printf("m:%d n:%d\n",m,n);
    printf("Max value:%d\n",maxValue);
    //print2dMatrix(mat,m,n);
}

//repetition matrix ne based on the event matrix
void repetitionMatrix(int mat[][1500],int ne[mm][nn])
{
    int i,j;
    
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=m; j++)
        {
            ne[j][i]=ne[j][i-1]+mat[j-1][i-1];
        }
    }
}
//returns optimal localmodelcost
float localmodelcost(int summ[mm][3],int i, int j,float rr[mm],int ss[mm], int sumsegment)
{
    int a,b,c,maxv;
    int dailyvalue;
    double totalValue,localdata,occurrences,p1,p2,probability,logdaily,logfact,cost1;
    
    for(a=1;a<=m;a++)
    {
        totalValue=MaxInt;
        
        for(b=1;b<=a;b++)
        {
            occurrences=0;
            maxv=0;
            
            for(c=(a-b+1);c<=a;c++)
            {
                occurrences=occurrences+summ[c][1];
            }
            probability=occurrences/((i-j)*(b));
            p1=0;
            p2=0;
            if (maxValue!=0)
                p2=log(maxValue);
            if(probability!=0 && probability != 1)
            {
                p1=log(probability);
            }
            
            logdaily=0;
            if(dailyrate!=0 && dailyrate != 1)
            {
                logdaily=log(dailyrate);
            }
            //printf("prob: %f\n",probability);
            localdata=0;
            
            for(c=(a-b+1);c<=a;c++)
            {
                dailyvalue=ceil(summ[c][1]/(i-j));
                
                if (dailyvalue>maxlog)
                    maxlog=dailyvalue;
                logfact=logfactorial(dailyvalue);
                localdata=localdata+1/pow(exp(1),(fabs((i-j)*((dailyrate)-(dailyvalue*logdaily)+(logfact))-((i-j)*((probability)-(dailyvalue*p1)+(logfact))))));
                //localdata=localdata+(i-j)*((probability)-(dailyvalue*p1)+(logfact));
                //printf("dailyvalue:%d\n",dailyvalue);
                //printf("logfact:%f\n",logfact);
                //printf("localdata:%f\n",localdata);
                /*
                if(localdata<0)
                {
                    printf("dailyvalue:%d\n",dailyvalue);
                    //printf("logfact:%f\n",logfact);
                    printf("p1: %f\n",p1);
                    printf("localdata:%f\n",localdata);
                }
                */
            }
            //printf("localdata:%f\n",localdata+log(m)+(i-j)*log(m));
            //printf("dailyrate:%f\n",dailyrate);
            //cost1=0;
            //if (a<m)
                cost1=(1/pow(exp(1),(m*log(m)-a*log(m))));
            localdata=localdata+cost1;//+(i-j)*log(m);
            if(localdata<0)
                printf("localdata:%f\n",localdata);
            localdata=localdata+rr[a-b];
            
            if(localdata<totalValue)
            {
                totalValue=localdata;
                ss[a]=b;
            }
            
        }
        rr[a]=totalValue;
        
    }
    totalValue=rr[m];//+m*log(m)+(1/(m*log(m)-log(m)));
    
    /*
     printfMatrix(rr,mm);
     printf("\n");
     printMatrix(ss,mm);
     printf("\n");
     */
    return(totalValue);
}


//DP global segmenting
void globalSegment(int ne[mm][nn],float r[nn],int s[nn],int mat[][1500])
{
    
    int i,j,c,sumsegment;//,q
    float q,tvalue,tcost,cost1;
    
    int normsum[mm];
    memset(normsum, 0,(mm)*sizeof(int));
    
    //optimal values for cuts of size 0..n
    float rr[mm];
    rr[0]=0;
    memset(rr, 0,(mm)*sizeof(float));
    //optimal first cut for cuts of length 0..n
    int ss[mm];
    memset(ss, 0,(mm)*sizeof(int));
    
    
    for(j=1;j<=n;j++)
    {
        printf("j:%d\n",j);
        q=MaxInt;
        
        for (i=1;i<=j;i++)
        {
            //printf("i:%d\n",i);
            int summ[mm][3];
            memset( summ, 0, (mm)*(3)*sizeof(int));
            
            sumsegment=0;
            
            for (c=1;c<=m;c++)
            {
                summ[c][0]=c;
                summ[c][1]=(ne[c][j]-ne[c][j-i]);
                sumsegment=sumsegment+summ[c][1];
            }
            
            insertionSort(summ);
            
            tcost=localmodelcost(summ,j,j-i,rr,ss,sumsegment);
            
            //cost1=0;
            //if (j<n)
                cost1=(1/pow(exp(1),(n*log(n)-j*log(n))));
            tvalue= tcost+r[j-i]+cost1;
            if (tvalue<q)
            {
                q=tvalue;
                s[j]=i;
            }
        }
        r[j]=q;
    }
    //show the results for the global model cuts
    printfMatrix(r,nn);
    printf("\n");
    printMatrix(s,nn);
    printf("\n");
    
}

void PrintSolution(int ne[mm][nn],int mat[][1500])
{
    snprintf(cpath,sizeof cpath,"%s/%s.xml",path,filename);
    printf("%s\n",cpath);
    
    FILE *xmlFile = fopen(cpath,"w");
    
    if(xmlFile == NULL)
    {
        printf("\n xml file opening failed ");
    }
    
    int k,c, elimit, blimit,elocal,blocal,occurrences,intervalsize,sumsegment;
    float localcost,localvalue,totalcost=0,groupfactorial,logdaily,dailyvalue,probability,p1;
    
    fprintf(xmlFile,"<summarization>\n");
    //optimal values for cuts of size 0..n
    float r[nn];
    memset(r, 0,(nn)*sizeof(float));
    //optimal first cut for cuts of legnth 0..n
    int s[nn];
    memset(s, 0,(nn)*sizeof(int));
    
    //optimal values for cuts of size 0..m
    float rrr[mm];
    memset(rrr, 0,(mm)*sizeof(float));
    //optimal first cut for cuts of legnth 0..m
    int sss[mm];
    memset(sss, 0,(mm)*sizeof(int));
    
    globalSegment(ne,r,s,mat);
    elimit=n;
    while(elimit>0)
    {
        
        blimit=elimit-s[elimit]+1;
        intervalsize=elimit-blimit+1;
        fprintf(xmlFile,"<time_segment>\n<start_time>%d</start_time>\n<end_time>%d</end_time>\n", blimit, elimit);
        //generate values per event
        int summ[mm][3];
        memset(summ, 0,(mm)*3*sizeof(int));
        
        //printf("blimit-1 va:%d\n",blimit-1);
        //printf("elimit va:%d\n",elimit);
        
        sumsegment=0;
        for (c=1;c<=m;c++)
        {
            summ[c][0]=c;
            summ[c][1]=(ne[c][elimit]-ne[c][blimit-1]);
            sumsegment=sumsegment+summ[c][1];
            
        }
        
        insertionSort(summ);
        //print2dSumm(summ, mm, 3);
        localcost=localmodelcost(summ,elimit,blimit-1,rrr,sss,-1)+log(n);
        //printf("oi:%f\n",localcost);
        totalcost=totalcost+localcost;
        fprintf(xmlFile,"<totalsegmentcost>%f</totalsegmentcost>\n", localcost);
        elocal=m;
        groupfactorial=0;
        
        while(elocal>0)
        {
            blocal=elocal-sss[elocal]+1;
            fprintf(xmlFile,"<local_segment>\n");
            occurrences=0;
            //maxv=0;
            localvalue=0;
            groupfactorial=0;
            for(k=blocal; k<=elocal; k++)
            {
                occurrences=occurrences+summ[k][1];
            }
            probability=occurrences/(float)(intervalsize*(elocal-blocal+1));
            for(k=blocal; k<=elocal; k++)
            {
                //occurrences=occurrences+summ[k][1];
                dailyvalue=ceil(summ[k][1]/intervalsize);
                p1=0;
                if (probability!=0)
                    p1=log(probability);
                //printf("logdaily:%f\n",logdaily);
                localvalue=localvalue+intervalsize*((probability)-(dailyvalue*p1)+logfactorial(dailyvalue));
                fprintf(xmlFile,"<event_id>%d</event_id>\n", summ[k][0]);
            }
            
            localvalue=localvalue+groupfactorial+log(m)+intervalsize*log(m);
            //printf("localvalue:%f\n",localvalue);
            fprintf(xmlFile,"<dailyrate>%f</dailyrate>\n",probability);
            fprintf(xmlFile,"<cost>%f</cost>\n",localvalue);
            fprintf(xmlFile,"</local_segment>\n");
            
            elocal=blocal-1;
        }
        fprintf(xmlFile,"<segmentcost>%f</segmentcost>\n",m*log(m)+log(n));
        fprintf(xmlFile,"</time_segment>\n");
        
        elimit=blimit-1;
        
    }
    fprintf(xmlFile,"<totalmodelcost>%f</totalmodelcost>\n", totalcost);
    fprintf(xmlFile,"</summarization>\n");
}

int main()
{
    
    static int mat[1500][1500];
    
    printf("Enter the path of the file:");
    scanf( "%s", path );
    
    printf("Enter the name of the input file:");
    scanf( "%s", filename );
    
    printf("Enter daily rate:");
    scanf( "%lf", &dailyrate );
    
    snprintf(cpath,sizeof cpath,"%s/%s.txt",path,filename);
    
    //printf("%s",FileNam);
    //reading the datafile
    
    FILE *fstream = fopen(cpath,"r");
    if(fstream == NULL)
    {
        printf("\n file opening failed ");
        return -1 ;
    }
    generateMatrix(fstream,mat);
    
    int ne[mm][nn];
    memset( ne, 0, (mm)*(nn)*sizeof(int));
    int normIndex[mm][nn];
    memset( normIndex, 0, (mm)*(nn)*sizeof(int));
    int orderne[mm][nn];
    memset( orderne, 0, (mm)*(nn)*sizeof(int));
    
    repetitionMatrix(mat,ne);
    print2dMatrix(ne,mm,nn);
    PrintSolution(ne,mat);
    printf("maxlog:%d\n",maxlog);
    return 0;
}


