#pragma once
#include "KriteriumUJTyp.h"
#include "FilterEquals.h"

//template <typename ObjectType, typename ValueType>
class FilterUJTyp : public FilterEquals<UzemJednotka, TypUzemJednotky> {
public:
	FilterUJTyp(TypUzemJednotky typ) : FilterEquals(new KriteriumUJTyp(), typ) {}
};
