#pragma once
#include "FilterSKriteriom.h"


template <typename ObjectType, typename ValueType>
class FilterInterval : public FilterSKriteriom<ObjectType, ValueType> {
public:
	FilterInterval(Kriterium<ObjectType, ValueType>* kriterium, ValueType valueMin, ValueType valueMax) : FilterSKriteriom<ObjectType, ValueType>(kriterium), valueMin_(valueMin), valueMax_(valueMax) {}; //{ valueMin_ = valueMin ,valueMax_ = valueMax; }
protected:
	bool passFilter(ValueType value) override {
		return value >= valueMin_ && value <= valueMax_;
	};
private:
	ValueType valueMin_;
	ValueType valueMax_;
};

