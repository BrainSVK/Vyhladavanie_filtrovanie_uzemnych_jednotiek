#pragma once
#include "UzemJednotka.h"
#include <string>
#include <iostream>
#include "structures/table/sorted_sequence_table.h"
#include "structures/table/unsorted_sequence_table.h"
#include "structures/table/sorting/quick_sort.h"

#include "FilterAnd.h"
#include "FilterOr.h"
#include "structures/list/array_list.h"
#include "FilterNazov.h"
#include "FilterUJPrislusnost.h"
#include "KriteriumUJNadradena.h"
#include "FilterUJTyp.h"
#include "FilterUJVzdelaniePocet.h"
#include "FilterUJVzdelaniePodiel.h"

using namespace std;

class Konzola
{
public:
	Konzola(UzemJednotka* slovakia ,structures::SortedSequenceTable<wstring, UzemJednotka*>* kraj, structures::SortedSequenceTable<wstring, UzemJednotka*>* okres, structures::SortedSequenceTable<wstring, UzemJednotka*>* obec);
	~Konzola();
	void spustiKonzolu();
	void vyhladavaj();
	void filtruj();
	UzemJednotka* najdiUzemJednotku(wstring nazov);

private:
	UzemJednotka* slovakia_;
	structures::SortedSequenceTable<wstring, UzemJednotka*>* kraj_;
	structures::SortedSequenceTable<wstring, UzemJednotka*>* okres_;
	structures::SortedSequenceTable<wstring, UzemJednotka*>* obec_;
	UzemJednotka* vyhladavana;
	
};

