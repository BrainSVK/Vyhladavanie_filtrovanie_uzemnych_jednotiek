#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>

#include "structures/heap_monitor.h"
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/list/array_list.h"
#include "Nacitaj.h"
#include "UzemJednotka.h"
#include "Konzola.h"

#include "FilterNazov.h"
#include "FilterUJPrislusnost.h"
#include "FilterUJTyp.h"
#include "FilterUJVzdelaniePocet.h"
#include "FilterUJVzdelaniePodiel.h"

#include "structures/table/sorting/quick_sort.h"


using namespace std;

int main(int argc, char* argv[]) 
{
    initHeapMonitor();
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    UzemJednotka* slovakia = new UzemJednotka(TypUzemJednotky::STAT,L"SVK",L"Slovakia",L"SK");
    structures::SortedSequenceTable<wstring, UzemJednotka*>* kraje = new structures::SortedSequenceTable<wstring, UzemJednotka*>();
    structures::SortedSequenceTable<wstring, UzemJednotka*>* okresy = new structures::SortedSequenceTable<wstring, UzemJednotka*>();
    structures::SortedSequenceTable<wstring, UzemJednotka*>* obce = new structures::SortedSequenceTable<wstring, UzemJednotka*>();
    wstring kraj = L"kraje";
    wstring okres = L"okresy"; 
    wstring obec = L"obce";
    wstring vzdelanie = L"vzdelanie";

    //wcout << kraj << endl;
    Nacitaj *nacitajto = new Nacitaj();
    nacitajto->nacitaj(kraj, kraje);
    //wcout << okres << endl;
    nacitajto->nacitaj(okres, okresy);
    //wcout << obec << endl;
    nacitajto->nacitaj(obec, obce);
    nacitajto->nacitaj(vzdelanie, obce);
    //structures::ArrayList<int>* pocetPreOkresy = new structures::ArrayList<int>();
    for (auto obc : *obce)
    {
        for (auto okr : *okresy)
        {
            obc->accessData()->natavPredka(okr->accessData());
        }
    }
    for (auto okr : *okresy)
    {
        okr->accessData()->nastavPotokov(obce);
        for (auto krj : *kraje)
        {
            okr->accessData()->natavPredka(krj->accessData());
        }
    }
    for (auto krj : *kraje)
    {
        krj->accessData()->nastavPotokov(okresy);
        krj->accessData()->natavPredka(slovakia);
    }
    slovakia->nastavPotokov(kraje);
    for (auto okr : *okresy)
    {
        okr->accessData()->nastavPocetTypVzdelania();
    }
    for (auto krj : *kraje)
    {
        krj->accessData()->nastavPocetTypVzdelania();
    }
    slovakia->nastavPocetTypVzdelania();

    Konzola* konzola = new Konzola(slovakia, kraje, okresy, obce);
    konzola->spustiKonzolu();
   

    for (auto kraj: *kraje) {
        delete kraj->accessData();
    }
    delete kraje;
    for (auto okres : *okresy) {
        delete okres->accessData();
    }
    delete okresy;
    for (auto obec : *obce) {
        delete obec->accessData();
    }
    delete obce;
    delete nacitajto;
    delete slovakia;
    delete konzola;
    return 0;
}
