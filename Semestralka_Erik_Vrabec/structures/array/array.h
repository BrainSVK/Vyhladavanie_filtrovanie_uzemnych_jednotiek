#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T>
	class Array : public Structure
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& operator[](int index);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& at(int index);

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception>
		static void copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int index) const;
	};

	template<typename T>
	Array<T>::Array(size_t size) :
		vector_(new Vector(size * sizeof(T))),
		size_(size)
	{
	}

	template<typename T>
	Array<T>::Array(Array<T>& other) :
		vector_(new Vector(*(other.vector_))),
		size_(other.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete vector_;
		vector_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	Structure& Array<T>::assign(Structure& other)
	{
		// ak nie je identicky, tak
		//   pretypuj, nech sa pracuje s polom
		//   porovnam velkost
		//     rovnaka: priradim vektory pomocou assign
		//     rozna: vyhodim vynimku

		// vratim *this
		if (this != &other)
		{
			Array<T>& otherArray = dynamic_cast<Array<T>&>(other);
			if (size_ == otherArray.size_) {
				vector_->assign(*(otherArray.vector_));
				// *vector_ = *otherArray.vector_;	// to iste co o riadok hore
				// vector_ = otherArray.vector_;	// ZLE!!!
			}
			else {
				throw std::invalid_argument("Array sizes differ!");
			}
		}
		return *this;
	}

	template<typename T>
	inline bool Array<T>::equals(Structure& other)
	{
		// pretypujte
		Array<T>* otherArray = dynamic_cast<Array<T>*>(&other);
		// ak su zhodneho typu, porovnajte vektory cez equals
		//   inak return false
		
		if (otherArray != nullptr)
		{
			return vector_->equals(*(otherArray->vector_));
			// *vector_ == *otherArray->vector_;	// to iste co o riadok hore
			// vector_ == otherArray->vector_;		// ZLE!!!
		}
		return false;
	}

	template<typename T>
	size_t Array<T>::size()
	{
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](int index)
	{
		return at(index);
	}

	template<typename T>
	inline T& Array<T>::at(int index)
	{
		int indexInVector = mapFunction(index);
		byte* ptrByte = vector_->getBytePointer(indexInVector);
		T* ptrData = reinterpret_cast<T*>(ptrByte);
		return *ptrData;

		// return *reinterpret_cast<T*>(vector_->getBytePointer(mapFunction(index)))
	}

	template<typename T>
	void Array<T>::copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length)
	{
		Vector::copy(*src.vector_, src.mapFunction(srcStartIndex), *dest.vector_, dest.mapFunction(destStartIndex), length * sizeof(T));
	}

	template<typename T>
	inline int Array<T>::mapFunction(int index) const
	{
		Utils::rangeCheckExcept(index, size_, "Invalid index!");
		return index * sizeof(T);
	}
}


