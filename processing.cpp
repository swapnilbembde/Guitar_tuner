#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<fstream>
#include<iostream>
#include<math.h>
#include<stdlib.h>
# define PI  3.14159265358979323846


using namespace std;

struct complex
{
    double re,im;
    complex ()
    {
        re=0;
        im=0;
    }
    complex (int re1,int im1)
    {
        re=re1;
        im=im1;
    }
    complex operator+ (complex num2)
    {
        complex sum;
        sum.re=re+num2.re;
        sum.im=im+num2.im;
        return sum;
    }
    complex operator- (complex num2)
    {
        complex sub;
        sub.re=re-num2.re;
        sub.im=im-num2.im;
        return sub;
    }
    complex operator* (complex num2)
    {
        complex mul;
        mul.re=re*num2.re-im*num2.im;
        mul.im=im*num2.re+re*num2.im;
        return mul;
    }

};

complex cis(double theta)
{
    complex num;
    num.re=cos(theta);
    num.im=sin(theta);
    return num;
}

double abso(complex num)
{
    double abs;
    abs=sqrt(num.re*num.re+num.im*num.im);
    return abs;
}

int bitreverse(int n, int numbits)
{
    int reversed = 0;
    for (int i = 0; i < numbits; i++)
    {
        int lastbit=n&1;
        n >>= 1;
        reversed <<= 1;
        reversed |= lastbit;
    }
    return reversed;
}

complex* fft(double y[],int N)
{
    complex x[N];
    for(int i=0;i<N;i++)
    {
        int j=bitreverse(i,log2(N));
        x[j].re=y[i];
        x[j].im=0;
    }
    int bitslength=log2(N);
    int n=1;
    for(int i=0; i<bitslength; i++)
    {
        for(int j=0; j<n; j++)
        {
            complex twiddle=cis(-double(PI*j)/n);
            for(int k=j; k<N; k+=(2*n))
            {
                complex even=x[k];
                complex odd=twiddle*x[k+n];
                x[k]=even+odd;
                x[k+n]=even-odd;
            }
        }
        n*=2;
    }
    return x;
}

complex* downsampling(complex x[],int N)
{
    complex sum[N/8];
    for(int k=0; k<N/8; k++)
        sum[k]=(x[k]*x[2*k])*x[3*k];
    return sum;
}

int maxval(complex x[],int N)
{
    double maxval=0;
    int indice=0;
    for(int i=0; i<N/2; i++)
    {
        double ab=abso(x[i]);
        if(maxval<ab)
        {
            maxval=ab;
            indice=i;
        }

    }
    return indice;
}

double window(double num,double n)
{
    double res;
    res=num*sin(PI*n/2047)*sin(PI*n/2047);
    return res;
}

double freqconvert(int indice,int N,int BSize)
{
    double freq;
    freq=double(N/BSize)*indice;
    return freq;
}

double* filter(double x[],int N)
{
    for(int i=0;i<N-100;i++)
    {
        int sum=0;
        for(int j=0;j<100;j++)
        {
            sum+=x[(i+j)%N];
        }
        x[i]=sum/100;
    }
    return x;
}

int process(char data[],int N)
{
    double comp[N];
    for(int i=0;i<N;i++) comp[i]=data[i];
    complex *a;
    a=fft(comp,N);
    int max=maxval(a,N);
    int frequency=freqconvert(max,N,N);
    return frequency;
}
