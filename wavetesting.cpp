#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#include"processing.cpp"
#include"nearest.cpp"

using namespace std;

HWAVEIN wavehandle;
HANDLE  eventhandle;


void CALLBACK waveInProc(HWAVEIN hwi,UINT uMsg,DWORD_PTR dwInstance,DWORD_PTR dwParam1,DWORD_PTR dwParam2)
{
    if(uMsg==WIM_DATA)
    {
        cout<<"working"<<endl;
        WAVEHDR *m= (WAVEHDR*)dwParam1;
        short int bffr[8192];
        for(int i=0; i<8192; i++)
            bffr[i]=m->lpData[i];
        int a=process(bffr,8192);
        nearest_note(a);
        BOOL checkevent =SetEvent(eventhandle);

    }
    return;
}

void realtime()
{
    double time;
    cout<<"Enter the time in sec you want to record for ";
    cin>>time;

    eventhandle=CreateEvent(NULL,TRUE,FALSE,NULL);
    WAVEFORMATEX WaveFormat;
    WaveFormat.wFormatTag      = WAVE_FORMAT_PCM;
    WaveFormat.nChannels       = 1;
    WaveFormat.nSamplesPerSec  = 16000;
    WaveFormat.wBitsPerSample  = 16;
    WaveFormat.nAvgBytesPerSec = WaveFormat.nSamplesPerSec*2;
    WaveFormat.nBlockAlign     = WaveFormat.wBitsPerSample/8;
    WaveFormat.cbSize          = 0;
    int res;
    res=waveInOpen(&wavehandle,WAVE_MAPPER,&WaveFormat,(DWORD)waveInProc,0,CALLBACK_FUNCTION);
    int bfsize=8192;
    short int wavedata[3][bfsize];
    WAVEHDR wavehdr[3];

    int numloops=time*WaveFormat.nSamplesPerSec/bfsize;


    for(int i=0; i<2; i++)
    {
        wavehdr[i].dwBufferLength=bfsize;
        wavehdr[i].dwFlags=0;
        wavehdr[i].lpData=(LPSTR)wavedata[i];
        res=waveInPrepareHeader(wavehandle,&wavehdr[i],sizeof(WAVEHDR));
        res=waveInAddBuffer(wavehandle,&wavehdr[i],sizeof(WAVEHDR));
    }

    res=waveInStart(wavehandle);
    int i=0;
    while(i<numloops+1)
    {
        DWORD time=WaitForSingleObject(eventhandle,INFINITE);
        BOOL checkevent =ResetEvent(eventhandle);
        res=waveInAddBuffer(wavehandle,&wavehdr[i%3],sizeof(WAVEHDR));


        i++;

    }
    res=waveInStop(wavehandle);
    res=waveInClose(wavehandle);
    cout<<"finished working";

}
