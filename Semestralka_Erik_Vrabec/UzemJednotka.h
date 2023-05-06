#pragma once
#include "TypUzemJednotky.h"
#include "TypVzdelaniar.h"
#include "structures/array/array.h"
#include <string>
#include "TypVzdelaniar.h"
#include "structures/table/sorted_sequence_table.h"

using namespace std;

class UzemJednotka {

public:
	UzemJednotka(TypUzemJednotky typ, wstring code, wstring nazov, wstring node);
	~UzemJednotka();
	TypUzemJednotky getTyp();
	wstring getCode();
	wstring getNazov();
	wstring getNote();
	int getPocetTypVzdelania(TypVzdelania typ);
	void setPocetTypVzdelania(TypVzdelania typ, int pocet);
	void nastavPotokov(structures::SortedSequenceTable<wstring, UzemJednotka*>* aPotomok);
	void natavPredka(UzemJednotka* aPredok);
	UzemJednotka* getPredka();
	UzemJednotka* getPotomka(int index);
	void nastavPocetTypVzdelania();
	int getPocetPotomkov();
	int getPocetObyvatelov();
	bool ciJePredok(UzemJednotka& aPredok);
	bool operator==(UzemJednotka& aUzemJednotka) { return *this == aUzemJednotka; };

private:
	structures::Array<int>* vzdelanie;
	TypUzemJednotky typ;
	wstring code;
	wstring nazov;
	wstring node;
	structures::SortedSequenceTable<wstring, UzemJednotka*>* potomok;
	UzemJednotka* predok;

};

