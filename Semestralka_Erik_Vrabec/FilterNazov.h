#pragma once
#include "KriteriumUJNazov.h"
#include "FilterEquals.h"

//template <typename ObjectType, typename ValueType>
class FilterNazov : public FilterEquals<UzemJednotka, wstring> {
public:
	FilterNazov(wstring name) : FilterEquals(new KriteriumUJNazov(), name) {};
};
