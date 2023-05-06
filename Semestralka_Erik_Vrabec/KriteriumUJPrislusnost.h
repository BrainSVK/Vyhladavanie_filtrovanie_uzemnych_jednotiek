#pragma once
#include "KriteriumUJ.h"

//template <typename ResultType>
class KriteriumUJPrislusnost : public KriteriumUJ <bool> {
public:
	KriteriumUJPrislusnost(UzemJednotka& aVyssiCelok) : vyssiCelok(aVyssiCelok) {}
	bool evaluate(UzemJednotka& uzemJednotka) override {
		return uzemJednotka.ciJePredok(vyssiCelok);
	}
private:
	UzemJednotka& vyssiCelok;
};
