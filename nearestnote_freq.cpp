#include<simplecpp>

char nearest_note(int a)
{
            cout<<"Frequency of the sound   ="<<a<<endl;

    if(a<=91)
    {
        cout<<"Nearest note is  E"<<endl;
        return('e');
        cout<<"Frequency of the note is    =82"<<endl;

    }

    else if(91<a&&a<=128)
    {
        cout<<"Nearest note is  A"<<endl;
        return('A');
        cout<<"Frequency of the note is    =110"<<endl;
    }

    else if(128<a&&a<=171)
    {
        cout<<"Nearest note is  D"<<endl;
        return('D');
        cout<<"Frequency of the note is    =147"<<endl;
    }

    else if(171<a&&a<=221)
    {
        cout<<"Nearest note is  G"<<endl;
        return('G');
        cout<<"Frequency of the note is    =196"<<endl;
    }

    else if(221<a&&a<=288)
    {
        cout<<"Nearest note is  B"<<endl;
        return('B');
        cout<<"Frequency of the note is    =247"<<endl;
    }

    else if(288<a&&a<=400)
    {
        cout<<"Nearest note is  E"<<endl;
        return('E');
        cout<<"Frequency of the note is    =329"<<endl;
    }

    else cout<<"No nearest note.";
}

int notefreq(char a)
{
    if(a=='A')
        return(82);
    else if(a=='B')
        return(247);
    else if(a=='D')
        return(147);
    else if(a=='E')
        return(329);
    else if(a=='G')
        return(196);
    else if(a=='e')
        return(82);
}
