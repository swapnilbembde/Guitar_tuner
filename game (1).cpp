#include<simplecpp>
#include<stdlib.h>

void playA()
{
    PlaySound(A.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='a') cout<<"You are correct";
    else cout<<"You are not correct";
}

void playb()
{
    PlaySound(B.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='b') cout<<"You are correct";
    else cout<<"You are not correct";
}

void playC()
{
    PlaySound(C.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='c') cout<<"You are correct";
    else cout<<"You are not correct";
}

void playD()
{
    PlaySound(D.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='d') cout<<"You are correct";
    else cout<<"You are not correct";
}

void playE()
{
    PlaySound(E.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='e') cout<<"You are correct";
    else cout<<"You are not correct";
}

void playF()
{
    PlaySound(F.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='f') cout<<"You are correct";
    else cout<<"You are not correct";
}

void playG()
{
    PlaySound(G.wav,NULL,SND_SYNC);
    char a;
    cin>>a;
    if(a=='g') cout<<"You are correct";
    else cout<<"You are not correct";
}

int main()
{
    int a=rand() % 7;
    switch(a)
    {
    case 0: playA();
    case 1: playB();
    case 2: playC();
    case 3: playD();
    case 4: playE();
    case 5: playF();
    case 6: playG();
    }
}
