#pragma once

#include "table.h"
#include "../list/list.h"
#include "../tree/binary_tree.h"
#include <stdexcept>

namespace structures
{

	/// <summary> Binarny vyhladavaci strom. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T>
	{
	public:
		typedef typename BinaryTreeNode<TableItem<K, T>*> BSTTreeNode;
	public:
		/// <summary> Konstruktor. </summary>
		BinarySearchTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> BinarySearchTree, z ktoreho sa prevezmu vlastnosti. </param>
		BinarySearchTree(BinarySearchTree<K, T>& other);

		/// <summary> Destruktor. </summary>
		~BinarySearchTree();

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>
		T& find(const K& key) override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>
		void insert(const K& key, const T& data) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>
		T remove(const K& key) override;

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() override;

	protected:
		/// <summary> Najde vrchol binarneho vyhladavacieho stromu s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Vrchol binarneho vyhladavacieho stromu s danym klucom. Ak sa kluc v tabulke nenachadza, vrati otca, ktoreho by mal mat vrchol s takym klucom. </returns>
		typename BSTTreeNode* findBSTNode(K key, bool& found);

	protected:
		/// <summary> Binarny strom s datami. </summary>
		BinaryTree<TableItem<K, T>*>* binaryTree_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;

		/// <summary> Vlozi vrchol do stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vlozeny. </param>
		/// <returns> true, ak sa podarilo vrchol vlozit (teda v strome nie je vrchol s rovnakym klucom), false inak. </returns>
		bool tryToInsertNode(BSTTreeNode* node);

		/// <summary> Bezpecne vyjme zo stromu vrchol stromu tak, aby nedoslo k naruseniu usporiadania BST. </summary>
		/// <param name = "node"> Vrchol stromu, ktory ma byt vyjmuty. </param>
		/// <remarks> Vrchol nebude zruseny, iba odstraneny zo stromu a ziadne vrcholy nebudu ukazovat na neho a ani on nebude ukazovat na ziadne ine vrcholy. </remarks>
		void extractNode(BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree():
		Table<K, T>(),
		binaryTree_(new BinaryTree<TableItem<K, T>*>()),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(BinarySearchTree<K, T>& other):
		BinarySearchTree()
	{
		assign(other);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree()
	{
		clear();
		delete binaryTree_;
		binaryTree_ = nullptr;
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size()
	{
		return size_;
	}

	template<typename K, typename T>
	inline Structure& BinarySearchTree<K, T>::assign(Structure& other)
	{
		if (this != &other) {
			BinarySearchTree<K, T>& otherBST = dynamic_cast<BinarySearchTree<K, T>&>(other);
			clear();
			auto iteratorBegin = new BinaryTree<TableItem<K, T>*>::PreOrderTreeIterator(otherBST.binaryTree_->getRoot());
			auto iteratorEnd = new BinaryTree<TableItem<K, T>*>::PreOrderTreeIterator(nullptr);
			while (*iteratorBegin != *iteratorEnd)
			{
				TableItem<K, T>* tableItem = **iteratorBegin;
				insert(tableItem->getKey(), tableItem->accessData());
				++*iteratorBegin;
			}
			delete iteratorBegin;
			delete iteratorEnd;
			//nikdy nepouzivat for each pri stromoch
			/*for (auto item : *other.list_) {
				list_->add(new TableItem<K, T>(*item));
			}*/
		}


		return *this;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::equals(Structure& other)
	{
		return Table<K, T>::equalsTable(dynamic_cast<BinarySearchTree<K, T>*>(&other));
	}

	template<typename K, typename T>
	inline T& BinarySearchTree<K, T>::find(const K& key)
	{
		bool found = false;
		auto node = findBSTNode(key, found);
		if (found)
		{
			return node->accessData()->accessData();
		}
		else
		{
			throw std::out_of_range("no such key!");
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K& key, const T& data)
	{
		TableItem<K, T>* item = new TableItem<K, T>(key, data);
		BSTTreeNode* node = new BSTTreeNode(item);
		if (!tryToInsertNode(node))
		{
			delete node;
			delete item;
			throw std::logic_error("Key already exists!");
		}
	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K& key)
	{
		bool found = false;
		BinaryTreeNode<TableItem<K, T>*>* nodeToRemove = findBSTNode(key, found);
		if (found)
		{
			extractNode(nodeToRemove);
			T result = nodeToRemove->accessData()->accessData();
			delete nodeToRemove->accessData();
			delete nodeToRemove;

			size_--;
			return result;
		}
		else
		{
			throw std::logic_error("Key not found");
		}
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K& key, T& data)
	{
		bool found;
		auto node = findBSTNode(key, found);
		if (found)
		{
			data = node->accessData()->accessData();
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K& key)
	{
		bool found;
		findBSTNode(key, found);
		return found;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear()
	{
		for (auto item : *binaryTree_) {
			delete item;
		}
		binaryTree_->clear();
		size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator()
	{
		return new BinaryTree<TableItem<K,T>*>::InOrderTreeIterator(binaryTree_->getRoot());
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator()
	{
		return new BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(nullptr);
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K,T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(K key, bool& found)
	{
		found = false;
		BSTTreeNode* current = dynamic_cast<BSTTreeNode*>(binaryTree_->getRoot());
		BSTTreeNode* ifSon = current;
		while (current != nullptr && key != current->accessData()->getKey())
		{
			if (key < current->accessData()->getKey())
			{
				current = current->getLeftSon();
				if (current != nullptr)
				{
					ifSon = current;
				}
			}
			else
			{		
				current = current->getRightSon();
				if (current != nullptr)
				{
					ifSon = current;
				}
			}
		}
		found = current != nullptr && current->accessData()->getKey() == key;
		return ifSon;

	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node)
	{
		bool found;
		auto parent = findBSTNode(node->accessData()->getKey(), found);
		if (!found)
		{
			if (parent == nullptr)
			{
				binaryTree_->replaceRoot(node);
			}
			else
			{
				if (node->accessData()->getKey() < parent->accessData()->getKey())
				{
					parent->setLeftSon(node);
				}
				else
				{
					parent->setRightSon(node);
				}
			}
			size_++;
			return true;
		}
		else
		{
			return false;
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node)
	{
		BSTTreeNode* parent = node->getParent();
		BSTTreeNode* son = nullptr;

		if (!node->hasLeftSon() && !node->hasRightSon())
		{
			parent == nullptr ? binaryTree_->replaceRoot(son) : node->isLeftSon() ? parent->setLeftSon(son) : parent->setRightSon(son);
		}
		else if (node->hasLeftSon() && node->hasRightSon())
		{
			son = node->getLeftSon();
			while (son->hasRightSon())
			{
				son = son->getRightSon();
			}
			extractNode(son);
			son->setRightSon(node->changeRightSon(nullptr));
			son->setLeftSon(node->changeLeftSon(nullptr));
			parent == nullptr ? binaryTree_->replaceRoot(son) : node->isLeftSon() ? parent->setLeftSon(son) : parent->setRightSon(son);
			son->setParent(parent);
		}
		else if (node->hasRightSon() || node->hasLeftSon())
		{
			if (node->hasLeftSon())
			{
				son = node->changeLeftSon(nullptr);
				parent == nullptr ? binaryTree_->replaceRoot(son) : node->isLeftSon() ? parent->setLeftSon(son) : parent->setRightSon(son);
				son->setParent(parent);
			}
			else if (node->hasRightSon())
			{
				son = node->changeRightSon(nullptr);
				parent == nullptr ? binaryTree_->replaceRoot(son) : node->isLeftSon() ? parent->setLeftSon(son) : parent->setRightSon(son);
				son->setParent(parent);
			}
		}
	}
}