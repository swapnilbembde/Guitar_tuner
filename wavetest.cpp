#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#include<simplecpp>
#include"processing.cpp"

using namespace std;

HWAVEIN wavehandle;
HANDLE  eventhandle;


void CALLBACK waveInProc(HWAVEIN hwi,UINT uMsg,DWORD_PTR dwInstance,DWORD_PTR dwParam1,DWORD_PTR dwParam2)
{
    if(uMsg==WIM_DATA)
    {
        cout<<"working";
        WAVEHDR *m= (WAVEHDR*)dwParam1;
        cout<<process(m->lpData,8192);
        BOOL checkevent =SetEvent(eventhandle);

    }
    return;
}

int main()
{
    eventhandle=CreateEvent(NULL,TRUE,FALSE,NULL);
    WAVEFORMATEX WaveFormat;
    WaveFormat.wFormatTag      = WAVE_FORMAT_PCM;
    WaveFormat.nChannels       = 1;
    WaveFormat.nSamplesPerSec  = 8000;
    WaveFormat.wBitsPerSample  = 8;
    WaveFormat.nAvgBytesPerSec = 8000;
    WaveFormat.nBlockAlign     = 1;
    WaveFormat.cbSize          = 0;
    int res;
    res=waveInOpen(&wavehandle,WAVE_MAPPER,&WaveFormat,(DWORD)waveInProc,0,CALLBACK_FUNCTION);
    int bfsize=8192;
    char wavedata[3][bfsize];
    WAVEHDR wavehdr[3];
    for(int i=0; i<2; i++)
    {
        wavehdr[i].dwBufferLength=bfsize;
        wavehdr[i].dwFlags=0;
        wavehdr[i].lpData=wavedata[i];
        res=waveInPrepareHeader(wavehandle,&wavehdr[i],sizeof(WAVEHDR));
        res=waveInAddBuffer(wavehandle,&wavehdr[i],sizeof(WAVEHDR));
    }

    res=waveInStart(wavehandle);
    int i=0;
    while(i<5)
    {
          DWORD time=WaitForSingleObject(eventhandle,INFINITE);
          BOOL checkevent =ResetEvent(eventhandle);
          res=waveInAddBuffer(wavehandle,&wavehdr[i%3],sizeof(WAVEHDR));


          i++;
         // int userinput=cin.peek();
          //if(userinput==EOF)
           // break;
    }
    res=waveInStop(wavehandle);
    res=waveInClose(wavehandle);
    cout<<"finished working";
    return (0);







}
