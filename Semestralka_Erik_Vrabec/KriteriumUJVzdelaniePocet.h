#pragma once
#include "KriteriumUJ.h"

//template <typename ResultType>
class KriteriumUJVzdelaniePocet : public KriteriumUJ <int> {
public:
	KriteriumUJVzdelaniePocet(TypVzdelania typVzdelania) { typ = typVzdelania; };
	int evaluate(UzemJednotka& uzemJednotka) override {
		return uzemJednotka.getPocetTypVzdelania(typ);
	}
private:
	TypVzdelania typ;

}; 
