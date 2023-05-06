#pragma once
#include "FilterSKriteriom.h"


template <typename ObjectType, typename ValueType>
class FilterEquals : public FilterSKriteriom<ObjectType, ValueType> {
public:
	FilterEquals(Kriterium<ObjectType, ValueType>* kriterium, ValueType value) : FilterSKriteriom<ObjectType, ValueType>(kriterium), value_(value) {} //{ value_ = value; } 
protected:
	bool passFilter(ValueType value) override {
		return value == value_;
	};
private:
	ValueType value_;
};

