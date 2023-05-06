#pragma once
using namespace std;

template <typename ObjectType>
class Filter {
public:
	virtual bool pass(ObjectType& object) = 0; // const
};

