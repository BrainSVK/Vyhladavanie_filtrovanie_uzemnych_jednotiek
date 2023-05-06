#pragma once
#include "Filter.h"
#include "FilterEquals.h"
#include "FilterSKriteriom.h"
#include "KriteriumUJPrislusnost.h"

//template <typename ObjectType, typename ValueType>
class FilterUJPrislusnost : public FilterEquals<UzemJednotka, bool> {
public:
	FilterUJPrislusnost(UzemJednotka& prislusnost , bool result) : FilterEquals(new KriteriumUJPrislusnost(prislusnost), result) {};
};
