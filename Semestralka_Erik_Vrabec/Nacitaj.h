#pragma once
#include <fstream>
#include "structures/table/sorted_sequence_table.h"
#include "UzemJednotka.h"

using namespace std;

class Nacitaj {
public:
	void nacitaj(wstring subor, structures::SortedSequenceTable<wstring, UzemJednotka*>* uzemJednotka);
};
