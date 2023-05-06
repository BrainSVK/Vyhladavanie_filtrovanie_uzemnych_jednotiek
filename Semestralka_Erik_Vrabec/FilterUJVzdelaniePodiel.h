#pragma once
#include "KriteriumUJVzdelaniePodiel.h"
#include "FilterInterval.h"


//template <typename ObjectType, typename ValueType>
class FilterUJVzdelaniePodiel : public FilterInterval<UzemJednotka, double> {
public:
	FilterUJVzdelaniePodiel(TypVzdelania vzdelanie, double vzdelaniePocetMin, double vzdelaniePocetMax) : FilterInterval(new KriteriumUJVzdelaniePodiel(vzdelanie), vzdelaniePocetMin, vzdelaniePocetMax) {}
};

