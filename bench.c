#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
static double now(void){struct timespec t;clock_gettime(CLOCK_MONOTONIC,&t);return t.tv_sec+t.tv_nsec*1e-9;}
static long fib(int n){return n<2?n:fib(n-1)+fib(n-2);}
static long sieve(int n){char*s=malloc(n+1);memset(s,1,n+1);s[0]=s[1]=0;
 for(long i=2;i*i<=n;i++)if(s[i])for(long j=i*i;j<=n;j+=i)s[j]=0;
 long c=0;for(int i=0;i<=n;i++)c+=s[i];free(s);return c;}
static double matmul(int n){double*a=malloc(sizeof(double)*n*n),*b=malloc(sizeof(double)*n*n),*c=calloc(n*n,sizeof(double));
 for(int i=0;i<n;i++)for(int j=0;j<n;j++){a[i*n+j]=(i+j)%7;b[i*n+j]=(i*j)%5;}
 for(int i=0;i<n;i++)for(int k=0;k<n;k++){double x=a[i*n+k];for(int j=0;j<n;j++)c[i*n+j]+=x*b[k*n+j];}
 double t=0;for(int i=0;i<n*n;i++)t+=c[i];free(a);free(b);free(c);return t;}
int main(int argc,char**argv){
 if(argc<2){puts("ok");return 0;}
 int reps=atoi(argv[2]);const char*w=argv[1];
 for(int r=0;r<reps;r++){double t0=now(),res;
  if(!strcmp(w,"fib"))res=fib(32);else if(!strcmp(w,"sieve"))res=sieve(5000000);else res=matmul(200);
  printf("%s %.6f %.0f\n",w,now()-t0,res);}
 return 0;}
