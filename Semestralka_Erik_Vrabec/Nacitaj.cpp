#include "Nacitaj.h"
#include <iostream>

void Nacitaj::nacitaj(wstring subor, structures::SortedSequenceTable<wstring, UzemJednotka*>* uzemJednotka)
{
    setlocale(LC_ALL, "sk_SK.UTF-8");
    locale svk("sk_SK.UTF-8");
    wfstream file;
    wstring words;
    wstring code;
    wstring note;
    wstring oficialTitle;
    TypUzemJednotky typ;
    TypVzdelania typVzdelania;
    file.imbue(svk);
    file.open(subor + L".csv");
    int indexCode = 1;
    int indexOficialTitle = 2;
    int indexRiadku = 0;
    int AkKlucExistuje = 49;
    int pocitatlo = 0;
    int randomChyba = 0;
    int pokracuj = 0;
    wstring cislo;
    if (subor == L"vzdelanie")
    {
        getline(file, words);
        while (file.good()) 
        {
            getline(file, words);
            structures::Array<int> *vzdel = new structures::Array<int>(8);
            pocitatlo++;

            for (size_t i = 0; i < words.length(); i++)
            {
                if (words.at(i) != wchar_t(';') && indexRiadku == 0)
                {
                    code += words.at(i);
                }
                if (words.at(i) == wchar_t(';'))
                {
                    indexRiadku++;
                    cislo = L"";
                }
                if (indexRiadku > 1)
                {
                    if (words.at(i) != wchar_t(';'))
                    {
                        indexRiadku = indexRiadku - 2;
                        cislo += words.at(i);
                        vzdel->at(indexRiadku) = stoi(cislo);
                        indexRiadku = indexRiadku + 2;
                    }
                }
            }
            
            for (auto obec : *uzemJednotka)
            {
                if (obec->accessData()->getCode() == code)
                {
                    for (size_t i = 0; i < vzdel->size(); i++)
                    {
                        typVzdelania = static_cast<TypVzdelania>(i);
                        obec->accessData()->setPocetTypVzdelania(typVzdelania, vzdel->at(i));
                        //obec->accessData()->getPredka()->setPocetTypVzdelania(typVzdelania, vzdel->at(i) += vzdel->at(i))
                        vzdel->at(i) = 0;
                        pokracuj = 1;
                    }

                }
                if (pokracuj == 1)
                {
                    pokracuj = 0;
                    code = L"";
                    indexRiadku = 0;
                    randomChyba = 0;
                    break;
                }
            }
            delete vzdel;
            //cout << pocitatlo << endl;
        }
    }
    else
    {
        subor == L"kraje" ? typ = TypUzemJednotky::KRAJ : subor == L"okresy" ? typ = TypUzemJednotky::OKRES : subor == L"obce" ? typ = TypUzemJednotky::OBEC : typ = TypUzemJednotky::STAT;
        getline(file, words);
        while (file.good()) {
            getline(file, words);

            for (size_t i = 0; i < words.length(); i++)
            {

                if (indexRiadku == 1)
                {
                    words.at(i) != wchar_t(';') ? code += words.at(i) : code;
                }
                if (indexRiadku == 2)
                {
                    words.at(i) != wchar_t(';') ? oficialTitle += words.at(i) : oficialTitle;
                }
                if (indexRiadku == 5)
                {
                    words.at(i) != wchar_t(';') ? note += words.at(i) : note;
                }
                if (i == words.size()-1 && indexRiadku == 5)
                {
                    while (uzemJednotka->containsKey(oficialTitle))
                    {
                        if (AkKlucExistuje == 49)
                        {
                            oficialTitle += wchar_t(AkKlucExistuje);
                        }
                        oficialTitle.at(oficialTitle.size() - 1) = wchar_t(AkKlucExistuje);
                        AkKlucExistuje++;
                    }
                    UzemJednotka* uzemJednotka1 = new UzemJednotka(typ, code, oficialTitle, note);
                    uzemJednotka->insert(oficialTitle, uzemJednotka1);
                    AkKlucExistuje = 49;
                }
                if (words.at(i) == wchar_t(';'))
                {
                    words.at(i) = wchar_t(' ');
                    indexRiadku++;
                }
            }
            indexRiadku = 0;
            code = L"";
            oficialTitle = L"";
            note = L"";
        }
    }

    /*if (subor == L"obce")
    {

    }
    else if (subor == L"vzdelanie")
    {
        for (auto uzemJednotka : *uzemJednotka)
        {
                                                                                                          
            wcout << uzemJednotka->getKey() << wchar_t(' ') << uzemJednotka->accessData()->getCode() << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(0)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(1)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(2)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(3)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(4)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(5)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(6)) << wchar_t(' ') << uzemJednotka->accessData()->getPocetTypVzdelania(static_cast<TypVzdelania>(7)) << endl;
        }
    }
    else
    {
        for (auto uzemJednotka : *uzemJednotka) 
        {
            wcout << uzemJednotka->getKey() << wchar_t(' ') << uzemJednotka->accessData()->getCode() << wchar_t(' ') << uzemJednotka->accessData()->getNote() << endl;
        }
    }
    wcout << endl;*/
    file.close();
}


