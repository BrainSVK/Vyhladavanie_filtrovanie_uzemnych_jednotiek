#pragma once
#include "KriteriumUJ.h"

//template <typename ResultType>
class KriteriumUJTyp : public KriteriumUJ <TypUzemJednotky> {
public:
	TypUzemJednotky evaluate(UzemJednotka& uzemJednotka) override {
		return uzemJednotka.getTyp();
	}
}; 