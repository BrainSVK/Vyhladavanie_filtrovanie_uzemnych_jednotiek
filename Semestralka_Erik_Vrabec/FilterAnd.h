#pragma once
#include "FilterKompozitny.h"

template<typename ObjectType>
class FilterAnd : public FilterKompozitny<UzemJednotka>
{
public:
	bool pass(ObjectType& object) override {
		for (auto item : *filtre)
		{
			if (!item->pass(object))
			{
				return false;
			}
		}
		return true;
	}
};