#pragma once
#include "KriteriumUJVzdelaniePocet.h"
#include "FilterInterval.h"

//template <typename ObjectType, typename ValueType>
class FilterUJVzdelaniePocet : public FilterInterval<UzemJednotka, int> {
public:
	FilterUJVzdelaniePocet(TypVzdelania vzdelanie, int vzdelaniePocetMin, int vzdelaniePocetMax) : FilterInterval(new KriteriumUJVzdelaniePocet(vzdelanie), vzdelaniePocetMin, vzdelaniePocetMax) {}
};

