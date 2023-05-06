#pragma once
#include "KriteriumUJ.h"

//template <typename ResultType>
class KriteriumUJNadradena : public KriteriumUJ <UzemJednotka*> {
public:
	UzemJednotka* evaluate(UzemJednotka& uzemJednotka) override {
		return uzemJednotka.getPredka();
	}
};
