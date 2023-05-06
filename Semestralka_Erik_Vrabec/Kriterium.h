#pragma once
using namespace std;

template <typename ObjectType, typename ResultType>
class Kriterium {
public:
	virtual ResultType evaluate(ObjectType& object) = 0;
};
