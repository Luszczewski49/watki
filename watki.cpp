#include <iostream>
#include <process.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;
VOID WINAPI Sleep(DWORD dwMilliseconds);

int kod = 0;
int bufor = 0;
int czas[8] = {600, 400, 500, 700, 300, 800, 800, 1000};
int postep[8] = {0};

int gotowka = 1000000;

bool watekPodwozie = false;
bool watekNadwozie = false;
bool watekSamochod = false;


int silniki = 0;
int kola = 0;
int mosty = 0;

int kabiny = 0;
int fotele = 0;

int podwozia = 0;
int nadwozia = 0;

int samochody = 0;

void kod_klawisza(void * Args)
{
    while(true)
    {
        kod = getch();
        if(kbhit())
        {
            kod = getch();
        }
    }
}

void silnik(void * Args)
{
    int l = 0;

    while(true)
    {
        while(l < 100)
        {
            Sleep(czas[0]);
            l += 1;
            postep[0] = l;
        }

        silniki++;
        l = 0;
        postep[0] = 0;
    }
}

void kolo(void * Args)
{
    int l = 0;

    while(true)
    {
        while(l < 100)
        {
            Sleep(czas[1]);
            l += 1;
            postep[1] = l;
        }

        kola++;
        l = 0;
        postep[1] = 0;
    }
}

void most(void * Args)
{
    int l = 0;

    while(true)
    {
        while(l < 100)
        {
            Sleep(czas[2]);
            l += 1;
            postep[2] = l;
        }

        mosty++;
        l = 0;
        postep[2] = 0;
    }
}

void kabina(void * Args)
{
    int l = 0;

    while(true)
    {
        while(l < 100)
        {
            Sleep(czas[3]);
            l += 1;
            postep[3] = l;
        }

        kabiny++;
        l = 0;
        postep[3] = 0;
    }
}

void fotel(void * Args)
{
    int l = 0;

    while(true)
    {
        while(l < 100)
        {
            Sleep(czas[4]);
            l += 1;
            postep[4] = l;
        }

        fotele++;
        l = 0;
        postep[4] = 0;
    }
}

void podwozie(void * Args)
{
    watekPodwozie = true;
    int l = 0;

        while(l < 100)
        {
            Sleep(czas[5]);
            l += 1;
            postep[5] = l;
        }

        podwozia++;
        l = 0;
        postep[5] = 0;

    watekPodwozie = false;
    _endthread();
}

void nadwozie(void * Args)
{
    watekNadwozie = true;
    int l = 0;

        while(l < 100)
        {
            Sleep(czas[6]);
            l += 1;
            postep[6] = l;
        }

        nadwozia++;
        l = 0;
        postep[6] = 0;

    watekNadwozie = false;
    _endthread();
}

void samochod(void * Args)
{
    watekSamochod = true;
    int l = 0;

        while(l < 100)
        {
            Sleep(czas[7]);
            l += 1;
            postep[7] = l;
        }

        samochody++;
        l = 0;
        postep[7] = 0;

    watekSamochod = false;
    _endthread();
}

void synchronizacja(void * Args)
{
    while(true)
    {
        if(silniki >= 1 && kola >= 4 && mosty >= 2 && watekPodwozie == false)
        {
            silniki -= 1;
            kola -= 4;
            mosty -= 2;
            _beginthread( podwozie, 0, NULL );
        }

        if(kabiny >= 1 && fotele >= 5 && watekNadwozie == false)
        {
            kabiny -= 1;
            fotele -= 5;
            _beginthread( nadwozie, 0, NULL );
        }

        if(nadwozia >= 1 && podwozia >= 1 && watekSamochod == false)
        {
            nadwozia -= 1;
            podwozia -= 1;
            _beginthread( samochod, 0, NULL );
        }
    }
}

int main()
{
    _beginthread( synchronizacja, 0, NULL );
    _beginthread( kod_klawisza, 0, NULL );

    _beginthread( silnik, 0, NULL );
    _beginthread( kolo, 0, NULL );
    _beginthread( most, 0, NULL );

    _beginthread( kabina, 0, NULL );
    _beginthread( fotel, 0, NULL );

    while(kod != 27)
    {
        switch(kod)
        {
            case 49:
                if(czas[0] >= 20)
                {
                    czas[0] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 50:
                if(czas[1] >= 20)
                {
                    czas[1] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 51:
                if(czas[2] >= 20)
                {
                    czas[2] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 52:
                if(czas[3] >= 20)
                {
                    czas[3] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 53:
                if(czas[4] >= 20)
                {
                    czas[4] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 54:
                if(czas[5] >= 20)
                {
                    czas[5] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 55:
                if(czas[6] >= 20)
                {
                    czas[6] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 56:
                if(czas[7] >= 20)
                {
                    czas[7] -= 10;
                    gotowka -= 10000;
                }
                break;

            case 115:
                if(samochody >= 1)
                {
                    samochody -= 1;
                    gotowka += 100000;
                }
                break;

            case 120:
                for(int i = 0; i < 8; i++)
                {
                    czas[i] = 20;
                }
                break;

            default:
                break;
        }

        kod = 0;

        cout << "[Esc] Wyjscie" << endl << endl;
        cout << "____________________________________________________________________" << endl;
        cout << "Ulepszenia:     [1, 2, 3, 4, 5, 6, 7] - koszt:           10 000 zl" << endl;
        cout << "Sprzedaj auto:  [s]                   -  cena:          100 000 zl" << endl;
        cout << "                                      Gotowka:          " << gotowka << " zl" << endl;
        cout << "____________________________________________________________________" << endl;
        cout << endl;

        cout << "1. Silniki:   " << silniki << "      Postep: ( " << postep[0] << "% )" << "    Czas produkcji: " << czas[0] / 10 << " [s]" << endl;
        cout << "2. Kola:      " << kola << "      Postep: ( " << postep[1] << "% )" << "    Czas produkcji: " << czas[1] / 10 << " [s]" << endl;
        cout << "3. Mosty:     " << mosty << "      Postep: ( " << postep[2] << "% )" << "    Czas produkcji: " << czas[2] / 10 << " [s]" << endl;
        cout << endl;
        cout << "4. Kabiny:    " << kabiny << "      Postep: ( " << postep[3] << "% )" << "    Czas produkcji: " << czas[3] / 10 << " [s]" << endl;
        cout << "5. Fotele:    " << fotele << "      Postep: ( " << postep[4] << "% )" << "    Czas produkcji: " << czas[4] / 10 << " [s]" << endl << endl;
        cout << "____________________________________________________________________" << endl;

        cout << "6. Podwozia:  " << podwozia << "      Postep: ( " << postep[5] << "% )" << "    Czas produkcji: " << czas[5] / 10 << " [s]" << endl;
        cout << "7. Nadwozia:  " << nadwozia << "      Postep: ( " << postep[6] << "% )" << "    Czas produkcji: " << czas[6] / 10 << " [s]" << endl << endl;
        cout << "____________________________________________________________________" << endl;

        cout << "8. Samochody: " << samochody << "      Postep: ( " << postep[7] << "% )" << "    Czas produkcji: " << czas[7] / 10 << " [s]" << endl;


        Sleep(500);
        system("cls");
    }




    return 0;
}
