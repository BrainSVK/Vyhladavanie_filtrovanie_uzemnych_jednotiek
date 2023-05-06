#pragma once
#include "Kriterium.h"
#include "Filter.h"

template <typename ObjectType, typename ValueType>
class FilterSKriteriom : public Filter<ObjectType> {
public:
	FilterSKriteriom(Kriterium<ObjectType, ValueType>* kriterium) {kriterium_ = kriterium; };
	~FilterSKriteriom() { delete kriterium_ ; };
	bool pass(ObjectType& object) override { //const
		return passFilter(kriterium_->evaluate(object));
	};
protected:
	virtual bool passFilter(ValueType value) = 0;
private:
	Kriterium<ObjectType, ValueType>* kriterium_;
};
