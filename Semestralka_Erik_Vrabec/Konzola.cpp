#include "Konzola.h"
#include "structures/heap_monitor.h"

Konzola::Konzola(UzemJednotka* slovakia, structures::SortedSequenceTable<wstring, UzemJednotka*>* kraj, structures::SortedSequenceTable<wstring, UzemJednotka*>* okres, structures::SortedSequenceTable<wstring, UzemJednotka*>* obec)
{
	slovakia_ = slovakia;
	kraj_ = kraj;
	okres_ = okres;
	obec_ = obec;
    vyhladavana = nullptr;
}

Konzola::~Konzola()
{
}

void Konzola::spustiKonzolu()
{
    initHeapMonitor();
    bool pracuj = true;
    wstring moznost;
    while (pracuj)
    {
        wcout << L"existujúce príkazy - (vyh¾adajUJ), (filtrujUJ), (koniec)" << endl;
        wcout << L"Zadajte príkaz:" << endl;
        getline(wcin, moznost);
        system("CLS");
        if (moznost == L"koniec")
        {
            pracuj = false;
        }
        if (moznost == L"vyh¾adajUJ")
        {
            vyhladavaj();
        }
        if (moznost == L"filtrujUJ")
        {
            filtruj();
        }
    }
}

void Konzola::vyhladavaj()
{
    wstring nazovUJ;
    KriteriumUJTyp typ_;
    KriteriumUJNazov nazovUJ_;
    wcout << L"Zadajte územnú jednotku:" << endl;
    getline(wcin, nazovUJ);
    if (obec_->tryFind(nazovUJ, vyhladavana) == true && nazovUJ_.evaluate(*vyhladavana) == nazovUJ)
    {
        KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
        wcout << nazovUJ_.evaluate(*vyhladavana) << endl;
        if (typ_.evaluate(*vyhladavana) == TypUzemJednotky::OBEC)
        {
            wcout << L"Typ Územnej jednotky: OBEC" << endl;
        }
        wcout <<L"Patrí do okresu: " << nazovUJ_.evaluate(*nadradena_->evaluate(*vyhladavana)) << L", ktorý patrí do kraju " << nazovUJ_.evaluate(*nadradena_->evaluate(*nadradena_->evaluate(*vyhladavana))) << endl;
        wcout << L"Pocet jednotlivých vzdelaní:" << endl;
        for (size_t i = 0; i < 8; i++)
        {
            KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
            wcout <<  ToString(i) << L" " << pocet_->evaluate(*vyhladavana) << endl;
            delete pocet_;
        }
        wcout << endl;
        delete nadradena_;
    }
    else if (okres_->tryFind(nazovUJ, vyhladavana) == true && nazovUJ_.evaluate(*vyhladavana) == nazovUJ)
    {
        KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
        wcout << nazovUJ_.evaluate(*vyhladavana) << endl;
        if (typ_.evaluate(*vyhladavana) == TypUzemJednotky::OKRES)
        {
            wcout << L"Typ Územnej jednotky: OKRES" << endl;
        }
        wcout << L"Patrí do kraju " << nazovUJ_.evaluate(*nadradena_->evaluate(*vyhladavana)) << endl;
        wcout << L"Pocet jednotlivých vzdelaní:" << endl;
        for (size_t i = 0; i < 8; i++)
        {
            KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
            wcout << ToString(i) << L" " << pocet_->evaluate(*vyhladavana) << endl;
            delete pocet_;
        }
        wcout << endl;
        wcout << L"jeho obce:" << endl;
        for (auto okres : *okres_)
        {
            if (okres->getKey() == nazovUJ_.evaluate(*vyhladavana))
            {
                for (size_t i = 0; i < vyhladavana->getPocetPotomkov(); i++)
                {
                    wcout << nazovUJ_.evaluate(*vyhladavana->getPotomka(i)) << endl; //vyhladavana->getPotomka(i)->getNazov()
                }
            }
        }
        delete nadradena_;
    }
    else if (kraj_->tryFind(nazovUJ, vyhladavana) == true && nazovUJ_.evaluate(*vyhladavana) == nazovUJ)
    {
        KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();

        wcout << nazovUJ_.evaluate(*vyhladavana) << endl;
        if (typ_.evaluate(*vyhladavana) == TypUzemJednotky::KRAJ)
        {
            wcout << L"Typ Územnej jednotky: KRAJ" << endl;
        }
        wcout << L"Pocet jednotlivých vzdelaní:" << endl;
        for (size_t i = 0; i < 8; i++)
        {
            KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
            wcout << ToString(i) << L" " << pocet_->evaluate(*vyhladavana) << endl;
            delete pocet_;
        }
        wcout << endl;
        wcout << L"jeho okresy:" << endl;
        for (auto kraj : *kraj_)
        {
            if (kraj->getKey() == nazovUJ_.evaluate(*vyhladavana))
            {
                for (size_t i = 0; i < vyhladavana->getPocetPotomkov(); i++)
                {
                    wcout << nazovUJ_.evaluate(*vyhladavana->getPotomka(i)) << endl; //vyhladavana->getPotomka(i)->getNazov()
                }
            }
        }
        wcout << endl;
        wcout << L"jeho obce:" << endl;

        for (auto okres : *okres_ )
        {
            for (size_t i = 0; i < vyhladavana->getPocetPotomkov(); i++)
            {
                if (okres->getKey() == vyhladavana->getPotomka(i)->getNazov())
                {
                    for (size_t j = 0; j < vyhladavana->getPotomka(i)->getPocetPotomkov(); j++)
                    {
                        wcout << vyhladavana->getPotomka(i)->getPotomka(j)->getNazov() << endl; //vyhladavana->getPotomka(i)->getNazov()
                    }
                }
            }
        }
        delete nadradena_;
    }
    else if (nazovUJ_.evaluate(*slovakia_) == nazovUJ)
    {
        KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
        wcout << nazovUJ_.evaluate(*slovakia_) << endl;
        if (typ_.evaluate(*slovakia_) == TypUzemJednotky::STAT)
        {
            wcout << L"Typ Územnej jednotky: STAT" << endl;
        }
        for (size_t i = 0; i < 8; i++)
        {
            KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
            wcout << ToString(i) << L" " << pocet_->evaluate(*slovakia_) << endl;
            delete pocet_;
        }
        wcout << endl;
        wcout << L"jeho kraje:" << endl;
        for (size_t i = 0; i < slovakia_->getPocetPotomkov(); i++)
        {
            wcout << nazovUJ_.evaluate(*slovakia_->getPotomka(i)) << endl;
        }
        delete nadradena_;
    }
    else
    {
        wcout << L"Územná jednotka sa nenašla!" << endl;
    }
}

void Konzola::filtruj()
{
    KriteriumUJTyp typ;
    KriteriumUJNazov nazovUJ;
    TypVzdelania typVzdedlania;
    wstring wtyp;
    bool funguje = true;
    int pocetFiltrov = 0;
    UzemJednotka* hladana = nullptr;
    FilterAnd<UzemJednotka>* filterHlavny = new FilterAnd<UzemJednotka>();
    FilterUJTyp* filterTyp = nullptr;
    FilterUJPrislusnost* filterPrislusnost = nullptr;
    FilterUJVzdelaniePocet* filterVzdelaniePocet = nullptr;
    FilterUJVzdelaniePodiel* filterVzdelaniePodiel = nullptr;
    while (funguje && pocetFiltrov < 4)
    {
        wcout << L"Zadajte aký filter si prajete aplikova:" << endl;
        wcout << L"Filter typ - (typ)" << endl;
        wcout << L"Filter príslušnos - (príslušnos)" << endl;
        wcout << L"Filter vzdelanie poèet - (vzdelaniePoèet)" << endl;
        wcout << L"Filter vzdelanie podiel - (vzdelaniePodiel)" << endl;
        getline(wcin, wtyp);
        if (wtyp == L"typ")
        {

            if (filterTyp == nullptr)
            {
                wcout << L"Zadajte typ územnej jednotky, ktorú chete filtrova (OBEC), (OKRES), (KRAJ), (STAT)" << endl;
                getline(wcin, wtyp);
                wstring uzJednotka = wtyp;
                if (uzJednotka == L"OBEC")
                {
                    filterTyp = new FilterUJTyp(TypUzemJednotky::OBEC);
                    pocetFiltrov++;
                }
                else if (uzJednotka == L"OKRES")
                {
                    filterTyp = new FilterUJTyp(TypUzemJednotky::OKRES);
                    pocetFiltrov++;
                }
                else if (uzJednotka == L"KRAJ")
                {
                    filterTyp = new FilterUJTyp(TypUzemJednotky::KRAJ);
                    pocetFiltrov++;
                }
                else if (uzJednotka == L"STAT")
                {
                    filterTyp = new FilterUJTyp(TypUzemJednotky::STAT);
                    pocetFiltrov++;
                }
                else
                {
                    wcout << L"Takýto typ uzemnej jednotky neexistuje" << endl;
                }
            }
            else
            {
                wcout << L"Tento filter ste už zvolili" << endl;
            }

        }
        else if (wtyp == L"príslušnos")
        {

            if (filterPrislusnost == nullptr)
            {
                pocetFiltrov++;
                while (hladana == nullptr)
                {
                    wcout << L"zadajte názov ÚzemJednotky" << endl;
                    getline(wcin, wtyp);
                    hladana = najdiUzemJednotku(wtyp);
                    if (hladana != nullptr)
                    {
                        filterPrislusnost = new FilterUJPrislusnost(*hladana,true);
                    }
                    else
                    {
                        wcout << L"Takáto Územná Jednotka neexistuje zadajte znovu" << endl;
                    }
                }
            }
            else
            {
                wcout << L"Tento filter ste už zvolili" << endl;
            }

        }
        else if (wtyp == L"vzdelaniePoèet")
        {
            if (filterVzdelaniePocet == nullptr)
            {
                pocetFiltrov++;
                wcout << L"Zadaj typ vzdelania" << endl;
                for (size_t i = 0; i < 8; i++)
                {
                    wcout << i << L" - " << ToString(i) << endl;
                }
                bool zadaj = true;
                while (zadaj)
                {
                    getline(wcin, wtyp);
                    if (wtyp == L"0" || wtyp == L"1" || wtyp == L"2" || wtyp == L"3" || wtyp == L"4" || wtyp == L"5" || wtyp == L"6" || wtyp == L"7")
                    {
                        zadaj = false;
                    }
                    else
                    {
                        wcout << L"Zadali ste nesprávne vzdelanie" << endl;
                        wcout << L"Zadaj typ vzdelania" << endl;
                        for (size_t i = 0; i < 8; i++)
                        {
                            wcout << i << L" - " << ToString(i) << endl;
                        }
                    }
                }
                int j = stoi(wtyp);
                for (size_t i = 0; i < 8; i++)
                {
                    if (j == i)
                    {
                        typVzdedlania = (static_cast<TypVzdelania>(i));
                    }
                }
                int min = -1;
                while (min < 0)
                {
                    try
                    {
                        wcout << L"Zadajte minimum filtra vzdelanie pocet" << endl;
                        getline(wcin, wtyp);
                        min = stoi(wtyp);
                        if (min < 0)
                        {
                            wcout << L"Zadali ste nesprávny vstup" << endl;
                        }
                    }
                    catch (const std::exception&)
                    {
                        wcout << L"Zadali ste nesprávny vstup" << endl;
                    }
                }
                int max = -1;
                while (max < 0)
                {
                    try
                    {
                        wcout << L"Zadajte maximum filtra vzdelanie pocet" << endl;
                        getline(wcin, wtyp);
                        max = stoi(wtyp);
                        if (max < 0)
                        {
                            wcout << L"Zadali ste nesprávny vstup" << endl;
                        }
                    }
                    catch (const std::exception&)
                    {
                        wcout << L"Zadali ste nesprávny vstup" << endl;
                    }
                }
                filterVzdelaniePocet = new FilterUJVzdelaniePocet(typVzdedlania,min,max);
            }
            else
            {
                wcout << L"Tento filter ste už zvolili" << endl;
            }

        }
        else if (wtyp == L"vzdelaniePodiel")
        {
            if (filterVzdelaniePodiel == nullptr)
            {
                pocetFiltrov++;
                wcout << L"Zadaj typ vzdelania" << endl;
                for (size_t i = 0; i < 8; i++)
                {
                    wcout << i << L" - " << ToString(i) << endl;
                }
                bool zadaj = true;
                while (zadaj)
                {
                    getline(wcin, wtyp);
                    if (wtyp == L"0" || wtyp == L"1" || wtyp == L"2" || wtyp == L"3" || wtyp == L"4" || wtyp == L"5" || wtyp == L"6" || wtyp == L"7")
                    {
                        zadaj = false;
                    }
                    else
                    {
                        wcout << L"Zadali ste nesprávne vzdelanie" << endl;
                        wcout << L"Zadaj typ vzdelania" << endl;
                        for (size_t i = 0; i < 8; i++)
                        {
                            wcout << i << L" - " << ToString(i) << endl;
                        }
                    }
                }
                int j = stoi(wtyp);
                for (size_t i = 0; i < 8; i++)
                {
                    if (j == i)
                    {
                        typVzdedlania = (static_cast<TypVzdelania>(i));
                    }
                }
                double min_ = -1.0;
                while (min_ < 0 || min_ > 100)
                {
                    try
                    {
                        wcout << L"Zadajte minimum filtra vzdelanie podiel" << endl;
                        getline(wcin, wtyp);
                        min_ = stod(wtyp);
                        if (min_ < 0 || min_ > 100)
                        {
                            wcout << L"Zadali ste nesprávny vstup" << endl;
                        }
                    }
                    catch (const std::exception&)
                    {
                        wcout << L"Zadali ste nesprávny vstup" << endl;
                    }
                }
                double max_ = -1.0;
                while (max_ < 0 || max_ > 100)
                {
                    try
                    {
                        wcout << L"Zadajte maximum filtra vzdelanie podiel" << endl;
                        getline(wcin, wtyp);
                        max_ = stod(wtyp);
                        if (max_ < 0 || max_ > 100)
                        {
                            wcout << L"Zadali ste nesprávny vstup" << endl;
                        }
                    }
                    catch (const std::exception&)
                    {
                        wcout << L"Zadali ste nesprávny vstup" << endl;
                        wcout << L"Zadajte maximum filtra vzdelanie podiel" << endl;
                    }
                }
                filterVzdelaniePodiel = new FilterUJVzdelaniePodiel(typVzdedlania, min_, max_);
            }
            else
            {
                wcout << L"Tento filter ste už zvolili" << endl;
            }
        }
        else
        {
            wcout << L"Zadali ste nesprávny filter" << endl;
        }
        if (pocetFiltrov < 4)
        {
            wcout << L"Ak chcete prida ïalší filter zvolte (ano)" << endl;
            getline(wcin, wtyp);
            if (wtyp != L"ano")
            {
                funguje = false;
            }
        }
    }

    if (filterVzdelaniePodiel != nullptr)
    {
        filterHlavny->pridajFilter(filterVzdelaniePodiel);
    }

    if (filterPrislusnost != nullptr)
    {
        filterHlavny->pridajFilter(filterPrislusnost);
    }

    if (filterVzdelaniePocet != nullptr)
    {
        filterHlavny->pridajFilter(filterVzdelaniePocet);
    }

    if (filterTyp != nullptr)
    {
        filterHlavny->pridajFilter(filterTyp);
    }

    structures::UnsortedSequenceTable<wstring, UzemJednotka*>* unsortWstring = new structures::UnsortedSequenceTable<wstring, UzemJednotka*>();
    structures::UnsortedSequenceTable<int, UzemJednotka*>* unsortInt = new structures::UnsortedSequenceTable<int, UzemJednotka*>();
    structures::UnsortedSequenceTable<double, UzemJednotka*>* unsortDouble = new structures::UnsortedSequenceTable<double, UzemJednotka*>();

    int vyberZoradenia = 0;
    bool vyber = false;
    int vybraneVzdelanie;
    wcout << L"Chcete zoradi ? Ak ano - (ano)" << endl;
    getline(wcin, wtyp);
    if (wtyp == L"ano")
    {
        vyber = true;
    }
    while (vyber)
    {
        wcout << L"Zadajte pod¾a èoho chcete zoraïova (názvu), (vzdelaniePoètu), (vzdelaniePodielu)" << endl;
        getline(wcin, wtyp);
        if (wtyp == L"názvu")
        {
            vyber = false;
            vyberZoradenia = 1;
        }
        else if (wtyp == L"vzdelaniePoètu")
        {
            vyber = false;
            wcout << L"Zadaj typ vzdelania pod¾a, ktorého chete zoraïova" << endl;
            for (size_t i = 0; i < 8; i++)
            {
                wcout << i << L" - " << ToString(i) << endl;
            }
            bool zadaj = true;
            while (zadaj)
            {
                getline(wcin, wtyp);
                if (wtyp == L"0" || wtyp == L"1" || wtyp == L"2" || wtyp == L"3" || wtyp == L"4" || wtyp == L"5" || wtyp == L"6" || wtyp == L"7")
                {
                    zadaj = false;
                    vybraneVzdelanie = stoi(wtyp);
                }
                else
                {
                    wcout << L"Zadali ste nesprávne vzdelanie" << endl;
                    wcout << L"Zadaj typ vzdelania pod¾a, ktorého chete zoraïova" << endl;
                    for (size_t i = 0; i < 8; i++)
                    {
                        wcout << i << L" - " << ToString(i) << endl;
                    }
                }
            }
            vyberZoradenia = 2;

        }
        else if (wtyp == L"vzdelaniePodielu")
        {
            vyber = false;
            wcout << L"Zadaj typ vzdelania pod¾a, ktorého chete zoraïova" << endl;
            for (size_t i = 0; i < 8; i++)
            {
                wcout << i << L" - " << ToString(i) << endl;
            }
            bool zadaj = true;
            while (zadaj)
            {
                getline(wcin, wtyp);
                if (wtyp == L"0" || wtyp == L"1" || wtyp == L"2" || wtyp == L"3" || wtyp == L"4" || wtyp == L"5" || wtyp == L"6" || wtyp == L"7")
                {
                    zadaj = false;
                    vybraneVzdelanie = stoi(wtyp);
                }
                else
                {
                    wcout << L"Zadali ste nesprávne vzdelanie" << endl;
                    wcout << L"Zadaj typ vzdelania pod¾a, ktorého chete zoraïova" << endl;
                    for (size_t i = 0; i < 8; i++)
                    {
                        wcout << i << L" - " << ToString(i) << endl;
                    }
                }
            }
            vyberZoradenia = 3;
        }

    }
    if (filterHlavny->pass(*slovakia_))
    {
        for (size_t i = 0; i < 8; i++)
        {
            if (vyberZoradenia == 0)
            {
                wcout << L"Názov štátu:" << nazovUJ.evaluate(*slovakia_) << endl;
                KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
                KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(i));
                wcout << ToString(i) << " - " << pocet_->evaluate(*slovakia_) << "podiel: " << podiel_->evaluate(*slovakia_) << "%" << endl;
                delete pocet_;
                delete podiel_;
            }
            else if (vyberZoradenia == 1)
            {
                unsortWstring->insert(nazovUJ.evaluate(*slovakia_), slovakia_);
            }
            else if (vyberZoradenia == 2)
            {
                KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(vybraneVzdelanie));
                unsortInt->insert((pocet_->evaluate(*slovakia_)), slovakia_);
                delete pocet_;
            }
            else if (vyberZoradenia == 3)
            {
                KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(vybraneVzdelanie));
                double podiel = podiel_->evaluate(*slovakia_);
                unsortDouble->insert(podiel_->evaluate(*slovakia_), slovakia_);
                delete podiel_;
            }

        }
        wcout << endl;
    }
    for (auto kraj : *kraj_)
    {
        if (filterHlavny->pass(*kraj->accessData()))
        {
            if (vyberZoradenia == 0) 
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                wcout << L"Názov kraju:" << nazovUJ.evaluate(*kraj->accessData()) << endl;
                wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*kraj->accessData())) << endl;
                for (size_t i = 0; i < 8; i++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(i));
                    wcout << ToString(i) << " - " << pocet_->evaluate(*kraj->accessData()) << " podiel: " << podiel_->evaluate(*kraj->accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
            else if (vyberZoradenia == 1)
            {
                unsortWstring->insert(nazovUJ.evaluate(*kraj->accessData()), kraj->accessData());
            }
            else if (vyberZoradenia == 2)
            {
                KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(vybraneVzdelanie));
                unsortInt->insert(pocet_->evaluate(*kraj->accessData()), kraj->accessData());
                delete pocet_;
            }
            else if (vyberZoradenia == 3)
            {
                KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(vybraneVzdelanie));
                double podiel = podiel_->evaluate(*kraj->accessData());
                unsortDouble->insert(podiel_->evaluate(*kraj->accessData()), kraj->accessData());
                delete podiel_;
            }
        }
    }
    for (auto okres : *okres_ )
    {
        if (filterHlavny->pass(*okres->accessData()))
        {
            if (vyberZoradenia == 0) 
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                wcout << L"Názov okresu:" << nazovUJ.evaluate(*okres->accessData()) << endl; //okres->accessData()->getNazov()
                wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*okres->accessData())) << endl; //okres->accessData()->getPredka()->getNazov()
                for (size_t i = 0; i < 8; i++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(i));
                    wcout << ToString(i) << " - " << pocet_->evaluate(*okres->accessData()) << " podiel: " << podiel_->evaluate(*okres->accessData()) << "%" << endl; //okres->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(i)) << 100.0 * okres->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(i)) / okres->accessData()->getPocetObyvatelov()
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
            else if (vyberZoradenia == 1)
            {
                unsortWstring->insert(nazovUJ.evaluate(*okres->accessData()), okres->accessData());
            }
            else if (vyberZoradenia == 2)
            {
                KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(vybraneVzdelanie));
                unsortInt->insert(pocet_->evaluate(*okres->accessData()), okres->accessData());
                delete pocet_;
            }
            else if (vyberZoradenia == 3)
            {
                KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(vybraneVzdelanie));
                double podiel = podiel_->evaluate(*okres->accessData());
                unsortDouble->insert(podiel_->evaluate(*okres->accessData()), okres->accessData());
                delete podiel_;
            }
        }
    }
    for (auto obec : *obec_)
    {
        if (filterHlavny->pass(*obec->accessData()))
        {
            if (vyberZoradenia == 0) 
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                wcout << L"Názov obce:" << nazovUJ.evaluate(*obec->accessData()) << endl;
                wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*obec->accessData())) << endl;
                for (size_t i = 0; i < 8; i++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(i));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(i));
                    wcout << ToString(i) << " - " << pocet_->evaluate(*obec->accessData()) << " podiel: " << podiel_->evaluate(*obec->accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
            else if (vyberZoradenia == 1)
            {
                unsortWstring->insert(nazovUJ.evaluate(*obec->accessData()), obec->accessData());
            }
            else if (vyberZoradenia == 2)
            {
                KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(vybraneVzdelanie));
                unsortInt->insert(pocet_->evaluate(*obec->accessData()), obec->accessData());
                delete pocet_;
            }
            else if (vyberZoradenia == 3)
            {
                KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(vybraneVzdelanie));
                double podiel = podiel_->evaluate(*obec->accessData());
                unsortDouble->insert(podiel_->evaluate(*obec->accessData()), obec->accessData());
                delete podiel_;
            }
        }
    }

    bool sorting = false;
    if (vyberZoradenia != 0)
    {
        sorting = true;
    }
    int postupnost = 0;
    while (sorting)
    {
        wcout << L"Zadajte èi chcete (vzostupne) alebo (zostupne) ?" << endl;
        getline(wcin, wtyp);
        if (wtyp == L"vzostupne")
        {
            sorting = false;
            postupnost = 1;
        }
        else if (wtyp == L"zostupne")
        {
            sorting = false;
            postupnost = 2;
        }
    }

    structures::QuickSort<wstring, UzemJednotka*>* qSortWstring = new structures::QuickSort<wstring, UzemJednotka*>();
    structures::QuickSort<int, UzemJednotka*>* qSortInt = new structures::QuickSort<int, UzemJednotka*>();
    structures::QuickSort<double, UzemJednotka*>* qSortDouble = new structures::QuickSort<double, UzemJednotka*>();
    
    if (vyberZoradenia == 1)
    {
        if (unsortWstring->size() != 0)
        {
            qSortWstring->sort(*unsortWstring);
        }
        if (postupnost == 1)
        {
            for (size_t i = 0; i < unsortWstring->size(); i++)
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::STAT)
                {
                    wcout << L"Názov štátu: ";
                }
                else if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::KRAJ)
                {
                    wcout << L"Názov obce: ";
                }
                else if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::OKRES)
                {
                    wcout << L"Názov okresu: ";
                }
                else if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::OBEC)
                {
                    wcout << L"Názov obce: ";
                }
                wcout << nazovUJ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) << endl;
                if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) != TypUzemJednotky::STAT)
                {
                    wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*unsortWstring->getItemAtIndex(i).accessData())) << endl;
                }
                for (size_t j = 0; j < 8; j++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(j));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(j));
                    wcout << ToString(j) << " - " << pocet_->evaluate(*unsortWstring->getItemAtIndex(i).accessData()) << " podiel: " << podiel_->evaluate(*unsortWstring->getItemAtIndex(i).accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
        }
        else if (postupnost == 2)
        {
            for (int i = unsortWstring->size() - 1; i >= 0; i--)
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::STAT)
                {
                    wcout << L"Názov štátu: ";
                }
                else if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::KRAJ)
                {
                    wcout << L"Názov obce: ";
                }
                else if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::OKRES)
                {
                    wcout << L"Názov okresu: ";
                }
                else if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) == TypUzemJednotky::OBEC)
                {
                    wcout << L"Názov obce: ";
                }
                wcout << nazovUJ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) << endl;
                if (typ.evaluate(*unsortWstring->getItemAtIndex(i).accessData()) != TypUzemJednotky::STAT)
                {
                    wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*unsortWstring->getItemAtIndex(i).accessData())) << endl;
                }
                for (size_t j = 0; j < 8; j++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(j));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(j));
                    wcout << ToString(j) << " - " << pocet_->evaluate(*unsortWstring->getItemAtIndex(i).accessData()) << " podiel: " << podiel_->evaluate(*unsortWstring->getItemAtIndex(i).accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
        }
    }
    else if (vyberZoradenia == 2)
    {
        if (unsortInt->size() != 0)
        {
            qSortInt->sort(*unsortInt);
        }
        if (postupnost == 1)
        {
            for (size_t i = 0; i < unsortInt->size(); i++)
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::STAT)
                {
                    wcout << L"Názov štátu: ";
                }
                else if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::KRAJ)
                {
                    wcout << L"Názov obce: ";
                }
                else if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::OKRES)
                {
                    wcout << L"Názov okresu: ";
                }
                else if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::OBEC)
                {
                    wcout << L"Názov obce: ";
                }
                wcout << nazovUJ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) << endl;
                if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) != TypUzemJednotky::STAT)
                {
                    wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*unsortInt->getItemAtIndex(i).accessData())) << endl;
                }
                for (size_t j = 0; j < 8; j++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(j));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(j));
                    wcout << ToString(j) << " - " << pocet_->evaluate(*unsortInt->getItemAtIndex(i).accessData()) << " podiel: " << podiel_->evaluate(*unsortInt->getItemAtIndex(i).accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
        }
        else if (postupnost == 2)
        {
            for (int i = unsortInt->size() - 1; i >= 0; i--)
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::STAT)
                {
                    wcout << L"Názov štátu: ";
                }
                else if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::KRAJ)
                {
                    wcout << L"Názov obce: ";
                }
                else if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::OKRES)
                {
                    wcout << L"Názov okresu: ";
                }
                else if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) == TypUzemJednotky::OBEC)
                {
                    wcout << L"Názov obce: ";
                }
                wcout << nazovUJ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) << endl;
                if (typ.evaluate(*unsortInt->getItemAtIndex(i).accessData()) != TypUzemJednotky::STAT)
                {
                    wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*unsortInt->getItemAtIndex(i).accessData())) << endl;
                }
                for (size_t j = 0; j < 8; j++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(j));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(j));
                    wcout << ToString(j) << " - " << pocet_->evaluate(*unsortInt->getItemAtIndex(i).accessData()) << " podiel: " << podiel_->evaluate(*unsortInt->getItemAtIndex(i).accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
        }
    }
    else if (vyberZoradenia == 3)
    {
        if (unsortDouble->size() != 0)
        {
            qSortDouble->sort(*unsortDouble);
        }
        if (postupnost == 1)
        {
            for (size_t i = 0; i < unsortDouble->size(); i++)
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::STAT)
                {
                    wcout << L"Názov štátu: ";
                }
                else if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::KRAJ)
                {
                    wcout << L"Názov obce: ";
                }
                else if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::OKRES)
                {
                    wcout << L"Názov okresu: ";
                }
                else if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::OBEC)
                {
                    wcout << L"Názov obce: ";
                }
                wcout << nazovUJ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) << endl;
                if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) != TypUzemJednotky::STAT)
                {
                    wcout << L"Názov predku: " << nazovUJ.evaluate(*nadradena_->evaluate(*unsortDouble->getItemAtIndex(i).accessData())) << endl;
                }
                for (size_t j = 0; j < 8; j++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(j));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(j));
                    wcout << ToString(j) << " - " << pocet_->evaluate(*unsortDouble->getItemAtIndex(i).accessData()) << " podiel: " << podiel_->evaluate(*unsortDouble->getItemAtIndex(i).accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
        }
        else if (postupnost == 2)
        {
            for (int i = unsortDouble->size() - 1; i >= 0; i--)
            {
                KriteriumUJNadradena* nadradena_ = new KriteriumUJNadradena();
                if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::STAT)
                {
                    wcout << L"Názov štátu: ";
                }
                else if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::KRAJ)
                {
                    wcout << L"Názov obce: ";
                }
                else if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::OKRES)
                {
                    wcout << L"Názov okresu: ";
                }
                else if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) == TypUzemJednotky::OBEC)
                {
                    wcout << L"Názov obce: ";
                }
                wcout << nazovUJ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) << endl;
                if (typ.evaluate(*unsortDouble->getItemAtIndex(i).accessData()) != TypUzemJednotky::STAT)
                {
                    wcout << L"Názov predku:" << nazovUJ.evaluate(*nadradena_->evaluate(*unsortDouble->getItemAtIndex(i).accessData())) << endl;
                }
                for (size_t j = 0; j < 8; j++)
                {
                    KriteriumUJVzdelaniePocet* pocet_ = new KriteriumUJVzdelaniePocet(static_cast<TypVzdelania>(j));
                    KriteriumUJVzdelaniePodiel* podiel_ = new KriteriumUJVzdelaniePodiel(static_cast<TypVzdelania>(j));
                    wcout << ToString(j) << " - " << pocet_->evaluate(*unsortDouble->getItemAtIndex(i).accessData()) << " podiel: " << podiel_->evaluate(*unsortDouble->getItemAtIndex(i).accessData()) << "%" << endl;
                    delete pocet_;
                    delete podiel_;
                }
                wcout << endl;
                delete nadradena_;
            }
        }
    }

    delete qSortWstring;
    delete qSortInt;
    delete qSortDouble;
    delete unsortWstring;
    delete unsortInt;
    delete unsortDouble;
    delete filterPrislusnost;
    delete filterTyp;
    delete filterVzdelaniePocet;
    delete filterVzdelaniePodiel;
    delete filterHlavny;

}

UzemJednotka* Konzola::najdiUzemJednotku(wstring nazov)
{
    wstring nazovUJ = nazov;
    KriteriumUJNazov nazovUJ_;
    if (obec_->tryFind(nazovUJ, vyhladavana) == true && nazovUJ_.evaluate(*vyhladavana) == nazovUJ)
    {
        return vyhladavana;
    }
    else if (okres_->tryFind(nazovUJ, vyhladavana) == true && nazovUJ_.evaluate(*vyhladavana) == nazovUJ)
    {
        return vyhladavana;
    }
    else if (kraj_->tryFind(nazovUJ, vyhladavana) == true && nazovUJ_.evaluate(*vyhladavana) == nazovUJ)
    {
        return vyhladavana;
    }
    else if (nazovUJ_.evaluate(*slovakia_) == nazovUJ)
    {
        return slovakia_;
    }
    else
    {
        return nullptr;
    }
}
