#pragma once
#include "KriteriumUJ.h"

//template <typename ResultType>
class KriteriumUJNazov : public KriteriumUJ <wstring> {
public:
	wstring evaluate(UzemJednotka& uzemJednotka) override {
		return uzemJednotka.getNazov();
	}
};
