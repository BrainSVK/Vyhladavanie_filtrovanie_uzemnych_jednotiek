#include "UzemJednotka.h"

UzemJednotka::UzemJednotka(TypUzemJednotky typ, wstring code, wstring nazov, wstring node) :
	typ(typ), code(code), nazov(nazov), node(node)
{
	potomok = new structures::SortedSequenceTable<wstring, UzemJednotka*>();
	vzdelanie = new structures::Array<int>(8);
}

UzemJednotka::~UzemJednotka()
{
	delete vzdelanie;
	delete potomok;
}

TypUzemJednotky UzemJednotka::getTyp()
{
	return typ;
}

wstring UzemJednotka::getCode()
{
	return code;
}

wstring UzemJednotka::getNazov()
{
	return nazov;
}

wstring UzemJednotka::getNote()
{
	return node;
}

int UzemJednotka::getPocetTypVzdelania(TypVzdelania typ)
{
	if (typ == TypVzdelania::BEZ_UKONCENIA_VZDELANIA)
	{
		return vzdelanie->at(0);
	}
	else if (typ == TypVzdelania::ZAKLADNE)
	{
		return vzdelanie->at(1);
	}
	else if (typ == TypVzdelania::UCNOVSKE)
	{
		return vzdelanie->at(2);
	}
	else if (typ == TypVzdelania::STREDNE)
	{
		return vzdelanie->at(3);
	}
	else if (typ == TypVzdelania::VYSSIE)
	{
		return vzdelanie->at(4);
	}
	else if (typ == TypVzdelania::VYSOKOSKOLSKE)
	{
		return vzdelanie->at(5);
	}
	else if (typ == TypVzdelania::BEZ_VZDELANIA)
	{
		return vzdelanie->at(6);
	}
	else if (typ == TypVzdelania::NEZISTENE)
	{
		return vzdelanie->at(7);
	}
}

void UzemJednotka::setPocetTypVzdelania(TypVzdelania typ, int pocet)
{
	if (typ == TypVzdelania::BEZ_UKONCENIA_VZDELANIA)
	{
		vzdelanie->at(0) = pocet;
	}
	else if (typ == TypVzdelania::ZAKLADNE)
	{
		vzdelanie->at(1) = pocet;
	}
	else if (typ == TypVzdelania::UCNOVSKE)
	{
		vzdelanie->at(2) = pocet;
	}
	else if (typ == TypVzdelania::STREDNE)
	{
		vzdelanie->at(3) = pocet;
	}
	else if (typ == TypVzdelania::VYSSIE)
	{
		vzdelanie->at(4) = pocet;
	}
	else if (typ == TypVzdelania::VYSOKOSKOLSKE)
	{
		vzdelanie->at(5) = pocet;
	}
	else if (typ == TypVzdelania::BEZ_VZDELANIA)
	{
		vzdelanie->at(6) = pocet;
	}
	else if (typ == TypVzdelania::NEZISTENE)
	{
		vzdelanie->at(7) = pocet;
	}
}

void UzemJednotka::nastavPotokov(structures::SortedSequenceTable<wstring, UzemJednotka*>* aPotomok)
{
	wstring ptmk;
	if (getTyp() == TypUzemJednotky::STAT)
	{
		for (auto potomk : *aPotomok)
		{
			if (potomk->accessData()->getTyp() == TypUzemJednotky::KRAJ)
			{
				potomok->insert(potomk->getKey(), potomk->accessData());
			}
		}
	}
	if (getTyp() == TypUzemJednotky::KRAJ)
	{
		for (auto potomk : *aPotomok)
		{
			if (potomk->accessData()->getTyp() == TypUzemJednotky::OKRES)
			{
				if (potomk->accessData()->getNote().at(0) == getCode().at(0))
				{
					potomok->insert(potomk->getKey(), potomk->accessData());
				}
			}
		}
	}
	else if (getTyp() == TypUzemJednotky::OKRES)
	{
		for (auto potomk : *aPotomok)
		{
			if (potomk->accessData()->getTyp() == TypUzemJednotky::OBEC)
			{
				ptmk = L"";
				for (size_t i = 0; i < getCode().size(); i++)
				{
					ptmk += potomk->accessData()->getCode().at(i);
				}
				if (ptmk == getCode())
				{
					potomok->insert(potomk->getKey(), potomk->accessData());
				}
			}
		}
	}
}

void UzemJednotka::natavPredka(UzemJednotka* aPredok)
{
	if (aPredok->getTyp() == TypUzemJednotky::STAT && getTyp() == TypUzemJednotky::KRAJ)
	{
		predok = aPredok;
	}
	else if (aPredok->getTyp() == TypUzemJednotky::KRAJ && getTyp() == TypUzemJednotky::OKRES)
	{
		if (aPredok->getCode().at(0) == getNote().at(0))
		{
			predok = aPredok;
		}
	}
	else if (aPredok->getTyp() == TypUzemJednotky::OKRES && getTyp() == TypUzemJednotky::OBEC)
	{
		wstring prdk = L"";
		for (size_t i = 0; i < aPredok->getCode().size(); i++)
		{
			prdk += getCode().at(i);
		}
		if (prdk == aPredok->getCode())
		{
			predok = aPredok;
		}
	}
}

UzemJednotka* UzemJednotka::getPredka()
{
	if (getTyp() != TypUzemJednotky::STAT)
	{
		return predok;
	}
	return nullptr;
}

UzemJednotka* UzemJednotka::getPotomka(int index)
{
	int i = 0;
	for (auto potomk : *potomok)
	{
		if (index == i)
		{
			return potomk->accessData();
		}
		i++;
	}
	return nullptr;
}

void UzemJednotka::nastavPocetTypVzdelania()
{
	if (getTyp() != TypUzemJednotky::OBEC)
	{
		int novaHodnota = 0;
		for (size_t i = 0; i < 8; i++)
		{
			for (size_t j = 0; j < getPocetPotomkov(); j++)
			{
				novaHodnota += getPotomka(j)->getPocetTypVzdelania(static_cast<TypVzdelania>(i));
			}
			setPocetTypVzdelania(static_cast<TypVzdelania>(i), novaHodnota);
			novaHodnota = 0;
		}

	}
}

int UzemJednotka::getPocetPotomkov()
{
	return potomok->size();
}

int UzemJednotka::getPocetObyvatelov()
{
	int j = 0;
	for (size_t i = 0; i < vzdelanie->size(); i++)
	{
		j += vzdelanie->at(i);
	}
	return j;
}

bool UzemJednotka::ciJePredok(UzemJednotka& aPredok)
{
	if (aPredok.getTyp() < getTyp())
	{
		if (aPredok.getTyp() == TypUzemJednotky::STAT)
		{
			if (aPredok.getNazov() == getPredka()->getNazov() || aPredok.getNazov() == getPredka()->getPredka()->getNazov() || aPredok.getNazov() == getPredka()->getPredka()->getPredka()->getNazov())
			{
				return true;
			}
			return false;
		}
		else if (aPredok.getTyp() == TypUzemJednotky::KRAJ)
		{
			if (aPredok.getNazov() == getPredka()->getNazov() || aPredok.getNazov() == getPredka()->getPredka()->getNazov())
			{
				return true;
			}
			return false;
		}
		else if (aPredok.getTyp() == TypUzemJednotky::OKRES)
		{
			if (aPredok.getNazov() == getPredka()->getNazov())
			{
				return true;
			}
			return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}







