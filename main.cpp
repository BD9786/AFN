#include <iostream>
#include <fstream>
#include <set>
#include <string.h>

using namespace std;

class afd {
    int q,v,f,*F,***D;
    char m; //m reprezinta cel mai mic caracter al algabetului(este necesar pentru a putea implementa atat automate cu tranzitie prin litere sau prin cifre)
public:
    afd(){q=f=v=0;F=NULL;D=NULL;}
    afd(char *nume_fis)
    {
        ifstream fin(nume_fis);
        fin>>q>>v>>f>>m;
        F=new int[f];
        for (int i=0;i<f;i++) fin>>F[i];
        D=new int **[q];
        for (int i=0;i<q;i++) {
                D[i]=new int*[v];
                for (int j=0;j<v;j++) {
                        D[i][j]=new int[q];
                        for (int k=0;k<q;k++) D[i][j][k]=-1;
                }
        }
        int x,z;
        char y;
        while (fin>>x>>y>>z) {
                D[x][(int)y-(int)m][z]=1;
        }
        fin.close();
    }
    bool procesare(char *s);
};

bool afd::procesare(char *s)
{
    int j,k;
    set<int> x,y;
    set<int>::iterator i;
    x.insert(0);
    for (k=0;k<strlen(s);k++)
    {
        for (i=x.begin();i!=x.end();i++)
            for (j=0;j<q;j++) if (((int)s[k]-(int)m>=0&&(int)s[k]-(int)m<v) && D[*i][(int)s[k]-(int)m][j]==1) y.insert(j); //Daca cuvantul contine litere care nu se afla in alfabet le va sari.
                                else if (((int)s[k]-(int)m<0) || ((int)s[k]-(int)m>=v))
                                    {
                                cout<<"Cuvantul contine una sau mai multe litere care nu se afla in alfabet"<<endl;
                                return false;
                                }
        x.clear();
        x=y;
        y.clear();
        if (x.empty()) return false;
    }
    cout<<"Stari in care ajunge:";
    for (i=x.begin();i!=x.end();i++) cout<<*i<<" ";
    cout<<endl;
    for (i=x.begin();i!=x.end();i++)
        for (j=0;j<f;j++)
            if (*i==F[j]) return true;
    return false;
}

int main()
{
    afd a("intrare.txt");
    cout<<"\tObservatie:Starile automatului sunt numerotate de la 0 la q-1"<<endl;
    int opt,n;
    char *s2;
    do {
        cout<<"Alegeti:"<<endl<<"1.Verificare cuvant"<<endl<<"2.Iesire program"<<endl;
        do {
                cin>>opt;
        } while (opt<=0 && opt>=3);
        if (opt==1) {
            cout<<"Introduceti dimensiunea maxima a cuvantului:";
            cin>>n;
            s2=new char[n+1];
            cout<<"Introduceti cuvantul:";
            cin>>s2;
            s2[n]='\0';
            if (a.procesare(s2)) cout<<"Accept"<<endl;
                else cout<<"Gresit"<<endl;
            delete s2;
        }
    }while (opt==1);
    return 0;
}
