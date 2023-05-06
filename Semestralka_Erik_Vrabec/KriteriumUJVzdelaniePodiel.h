#pragma once
#include "KriteriumUJ.h"

//template <typename ResultType>
class KriteriumUJVzdelaniePodiel : public KriteriumUJ <double> {
public:
	KriteriumUJVzdelaniePodiel(TypVzdelania typVzdelania) { typ = typVzdelania; };
	double evaluate(UzemJednotka& uzemJednotka) override {
		return 100.0 * uzemJednotka.getPocetTypVzdelania(typ) / uzemJednotka.getPocetObyvatelov();
	}
private:
	TypVzdelania typ;
};
