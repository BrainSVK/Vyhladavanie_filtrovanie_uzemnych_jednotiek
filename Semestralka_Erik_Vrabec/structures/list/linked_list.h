#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"

namespace structures
{
    /// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class LinkedListItem : public DataItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        LinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
        LinkedListItem(LinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        ~LinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        LinkedListItem<T>* getNext();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name�= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(LinkedListItem<T>* next);

    private:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        LinkedListItem<T>* next_;
    };

    /// <summary> Jednostranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    template<typename T>
    class LinkedList : public List<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        LinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        LinkedList(LinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        ~LinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
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
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    private:
        /// <summary> Pocet prvkov v zozname. </summary>
        size_t size_;
        /// <summary> Prvy prvok zoznamu. </summary>
        LinkedListItem<T>* first_;
        /// <summary> Posledny prvok zoznamu. </summary>
        LinkedListItem<T>* last_;

    private:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </summary>
        /// <returns> Prvok zoznamu na danom indexe. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        LinkedListItem<T>* getItemAtIndex(int index);

    private:
        /// <summary> Iterator pre LinkedList. </summary>
        class LinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            LinkedListIterator(LinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~LinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator= (Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            LinkedListItem<T>* position_;
        };
    };

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(LinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::~LinkedListItem()
    {
        next_ = nullptr;
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline void LinkedListItem<T>::setNext(LinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline LinkedList<T>::LinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)       //dynamick� �trukt�ra, nevytv�rame ni� dopredu
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedList(LinkedList<T>& other) : LinkedList()
    {
        assign(other);
    }

    template<typename T>
    inline LinkedList<T>::~LinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t LinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& LinkedList<T>::assign(Structure& other)
    {
        if (this != &other) { // test identity
            LinkedList<T>& otherLinkedList = dynamic_cast<LinkedList<T>&>(other);
            clear(); //vyma�eme p�vodn�
            for (T data : otherLinkedList) {
                add(data);
            }
        }
        return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::equals(Structure& other)
    {
        if (this == &other) {
            return true;
        }

        LinkedList<T>* otherLinkedList = dynamic_cast<LinkedList<T>*>(&other);

        if (otherLinkedList == nullptr) {
            return false;
        }

        if (size_ != otherLinkedList->size_) {
            return false;
        }

        LinkedListItem<T>* curThis = first_;
        LinkedListItem<T>* curOther = otherLinkedList->first_;

        while (curThis != nullptr) {
            if (curThis->accessData() != curOther->accessData()) {
                return false;
            }
            curThis = curThis->getNext();
            curOther = curOther->getNext();
        }
        return true;
    }

    template<typename T>
    inline T& LinkedList<T>::at(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index!");
        return getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void LinkedList<T>::add(const T& data)  //vlo�enie na za�iatok
    {
        size_++;
        LinkedListItem<T>* newLLI = new LinkedListItem<T>(data);
        if (first_ == nullptr) {
            first_ = newLLI;
        }
        else {
            last_->setNext(newLLI);
        }
        last_ = newLLI;
    }

    template<typename T>
    inline void LinkedList<T>::insert(const T& data, int index)
    {
        if (index == size_) {
            add(data);
        }
        else {
            Utils::rangeCheckExcept(index, size_, "Invalid index!");
            LinkedListItem<T>* newLLI = new LinkedListItem<T>(data);

            if (index == 0) {
                newLLI->setNext(first_);
                first_ = newLLI;
            }
            else {
                LinkedListItem<T>* prevLLI = getItemAtIndex(index - 1); //ulo��me si predchodcu
                newLLI->setNext(prevLLI->getNext());
                prevLLI->setNext(newLLI);
            }
            size_++;
        }
    }

    template<typename T>
    inline bool LinkedList<T>::tryRemove(const T& data)
    {
        if (getIndexOf(data) < 0) {
            return false;
        }
        else {
            removeAt(getIndexOf(data)); //dvakr�t to prech�dza, zlo�itos� 2*n
            return true;
        }
    }

    template<typename T>
    inline T LinkedList<T>::removeAt(int index)
    {
        Utils::rangeCheckExcept(index, size_, "Invalid index!");
        LinkedListItem<T>* delItem;
        if (size_ == 1) {
            delItem = first_;
            first_ = nullptr;
            last_ = nullptr;
        }
        else {
            if (index == 0) {
                delItem = first_;
                first_ = first_->getNext();
            }
            else {
                LinkedListItem<T>* prevItem = getItemAtIndex(index - 1);
                delItem = prevItem->getNext();
                prevItem->setNext(delItem->getNext());

                if (last_ == delItem) {
                    last_ = prevItem;
                }
            }
        }
        T result = delItem->accessData();
        delete delItem;
        size_--;
        return result;
    }

    template<typename T>
    inline int LinkedList<T>::getIndexOf(const T& data)
    {
        LinkedListItem<T>* current = first_;
        for (size_t i = 0; i < size_; i++) {
            if (current->accessData() == data) {
                return i;
            }
            current = current->getNext();
        }
        return -1;


        /*
        inak
        int i =0;
        for(;current != nullptr && current->accessData() != data; current = current->getNext()) {
            i++;
         }
         retrun current != nullptr ? i : -1;

         inak
        int i =0;
        while(current != nullptr && current->accessData() != data) {
            i++;
            current = current->getNext();
         }
         retrun current != nullptr ? i : -1;
        */
    }

    template<typename T>
    inline void LinkedList<T>::clear()
    {
        //ma�eme od first_ po last_
        // prid�me si current, ukazovate� za first_

        LinkedListItem<T>* current = first_;
        while (current != nullptr) {
            current = current->getNext();
            delete first_;
            first_ = current;
        }
        last_ = nullptr;
        size_ = 0;
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getBeginIterator()
    {
        return new LinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getEndIterator()
    {
        return new LinkedListIterator(nullptr);
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index)
    {
        LinkedListItem<T>* current = first_;
        if (index == size_ - 1) {
            current = last_;
        }
        else {
            for (int i = 0; i < index; i++) {
                current = current->getNext();  //ideme po zre�azenom zozname ku tomu �o chceme
            }
        }
        return current;
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T>* position) :
        position_(position)
    { //Iterator v�eobecne: ukazuje na polo�ku, r�chlo spr�stupn� polo�ku a r�chlo sa presunie na �al�iu
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
    {
        position_ = nullptr;        // delete nie, lebo zma�eme LinkedListItem
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(Iterator<T>& other)
    {
        if (this != &other) {
            LinkedListIterator& otherIterator = dynamic_cast<LinkedListIterator&>(other);
            position_ = otherIterator.position_;
        }
        return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::LinkedListIterator::operator!=(Iterator<T>& other)
    {
        LinkedListIterator* otherIterator = dynamic_cast<LinkedListIterator*>(&other);
        return otherIterator == nullptr || position_ != otherIterator->position_;
    }

    template<typename T>
    inline T LinkedList<T>::LinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
    {
        position_ = position_->getNext();
        return *this;
    }

}