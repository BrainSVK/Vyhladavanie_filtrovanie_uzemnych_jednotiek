#pragma once
#include "Filter.h"
#include "structures/list/array_list.h"

template<typename ObjectType>
class FilterKompozitny : public Filter<ObjectType>
{
public:
	~FilterKompozitny() { delete filtre; };
	void pridajFilter(Filter<ObjectType>* filter) { filtre->add(filter);};
protected:
	structures::ArrayList<Filter<ObjectType>*>* filtre = new structures::ArrayList<Filter<ObjectType>*>();



};
