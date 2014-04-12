/*
 * BinaryST.hpp
 *
 *  Created on: Apr 9, 2014
 *      Author: mochman
 */

#ifndef BINARYST_HPP_
#define BINARYST_HPP_

/*!
 * \brief Reprezentuje tablicę asocjacyjną, zbudowaną na drzewie BST
 */
template <typename KeyType, typename ValueType>
class BinaryST
{
	public:

		/*!
		 * \brief Domyślny konstruktor drzewa BST
		 */
		BinaryST():m_root(nullptr), m_size(0){}

		/*!
		 * \brief Pozwala dodać węzeł o podanym kluczu i danych
		 *
		 * \param key - klucz
		 * \param value - dane
		 */
		void add(const KeyType& key, const ValueType& value);

		/*!
		 * \brief Pozwala na usunięcie węzła o podanym kluczu
		 *
		 * \param key - klucz węzła, który ma być usunięty
		 */
		void remove(const KeyType& key);

		/*!
		 * \brief Pozwala pobrać dane przechowywane pod podanym kluczem
		 *
		 * Jeśli nie ma takiego klucza, zostanie zgłoszony wyjątek const char*
		 *
		 * \param key - klucz, po którym ma się odbyć poszukiwanie
		 */
		const ValueType& find(const KeyType& key) const;

		/*!
		 * \brief Przeciążony operator indeksu, pozwala na dostanie się do danych za pomocą klucza
		 *
		 * Patrz BinaryST::find
		 * \param key - klucz, po którym ma się odbyć poszukiwanie
		 */
		const ValueType& operator[](const KeyType& key) const { return find(key); }

		/*!
		 * \brief Pozwala pobrać rozmiar drzewa
		 */
		unsigned long size() const { return m_size; }

		/*!
		 * \brief Usuwa wszystkie węzły z drzewa
		 */
		void clear();
	private:

		/*!
		 * \brief Reprezentuje węzeł drzewa
		 */
		class Node
		{
			public:
			/*!
			 * \brief Konstruktor węzła, pozwalający ustawić klucz i przechowywane dane
			 */
			Node(const KeyType& key, const ValueType& value)
			:m_left(nullptr),m_right(nullptr),m_parent(nullptr),m_key(key), m_value(value) {}

			/*!
			 * \brief Sprawdza czy węzeł ma przynajmniej jedno dziecko
			 */
			bool hasChildren() const { return m_left!=nullptr || m_right!=nullptr; }

			/*!
			 * \brief Pobiera lewe dziecko węzła
			 *
			 * Jeśli węzeł nie ma dziecka, zwraca nullptr
			 */
			const Node* left() const { return m_left; }

			/*!
			 * \brief Pobiera lewe dziecko węzła
			 *
			 * Jeśli węzeł nie ma dziecka, zwraca nullptr
			 */
			Node* left() { return m_left; }

			/*!
			 * \brief Pozwala ustawić lewe dziecko węzła
			 *
			 * \param node - nowe lewe dziecko węzła
			 */
			void left(Node* node) { m_left=node; }

			/*!
			 * \brief Pobiera prawe dziecko węzła
			 *
			 * Jeśli węzeł nie ma prawego dziecka, zwraca nullptr
			 */
			const Node* right() const { return m_right;}

			/*!
			 * \brief Pobiera prawe dziecko węzła
			 *
			 * Jeśli węzeł nie ma prawego dziecka, zwraca nullptr
			 */
			Node* right() { return m_right; }

			/*
			 * \brief Pozwala ustawić lewe dziecko węzła
			 *
			 * \param node - nowe lewe dziecko węzła
			 */
			void right(Node* node) { m_right=node; }

			/*!
			 * \brief Sprawdza czy węzeł ma lewego syna
			 */
			bool hasLeft() const { return m_left!=nullptr; }

			/*!
			 * \brief Sprawdza czy węzeł ma prawego syna
			 */
			bool hasRight() const { return m_right!=nullptr; }

			/*!
			 * \brief Sprawdza czy węzeł ma rodzica
			 */
			bool hasParent() const { return m_parent!=nullptr; }

			/*!
			 * \brief Pobiera rodzica węzła
			 *
			 * Jeśli węzeł nie ma rodzica, zwraca nullptr
			 */
			Node* parent() { return m_parent; }

			/*!
			 * \brief Pobiera rodzica węzła
			 *
			 * Jeśli węzeł nie ma rodzica, zwraca nullptr
			 */
			const Node* parent() const { return m_parent; }

			/*!
			 * \brief Pozwala ustawić rodzica węzła
			 *
			 * \param parent - nowy rodzic węzła
			 */
			void parent(Node* parent) { m_parent=parent; }

			/*!
			 * \brief Pozwala pobrać przechowywane dane w węźle
			 */
			const ValueType& value() const { return m_value; }

			/*
			 * \brief Pozwala ustawić przechowywane dane w węźle
			 *
			 * \param value - nowe dane
			 */
			void value(const ValueType& value) { m_value=value; }

			/*!
			 * \brief Pozwala pobrać klucz węzła
			 */
			const KeyType& key() const { return m_key; }

			/*!
			 * \brief Pozwala zmienić klucz węzła
			 *
			 * \param key - nowy klucz węzła
			 */
			void key(const KeyType& key) { m_key=key; }

			/*!
			 * \brief Pozwala znaleźć węzeł o minimalnym kluczu w drzewie o początku w naszym węźle
			 */
			Node* findMinNode();

			/*!
			 * \brief Pozwala znaleźć węzeł o maksymalnym kluczu w drzewie o początku w naszym węźle
			 */
			Node* findMaxNode();

			/*!
			 * \brief Pozwala znaleźć poprzednika węzła
			 */
			Node* predecessor();

			/*!
			 * \brief Pozwala znaleźć następik węzła
			 */
			Node* successor();
			private:

			/*!
			 * \brief Pole przechowujące lewe dziecko
			 */
			Node* m_left;

			/*!
			 * \brief Pole przechowujące prawe dziecko
			 */
			Node* m_right;

			/*!
			 * \brief Pole przechowujące rodzica
			 */
			Node* m_parent;

			/*!
			 * \brief Przechowywany klucz węzła
			 */
			KeyType m_key;

			/*!
			 * \brief Przechowywane dane węzła
			 */
			ValueType m_value;
		};

		/*!
		 * \brief Pozwala znaleźć węzeł o podanym kluczu, w podanym poddrzewie
		 *
		 * \param node - korzeń poddrzewa
		 * \param key - poszukiwany klucz
		 */
		const Node* find(const Node* node,const KeyType& key) const;

		/*!
		 * \brief Pozwala znaleźć węzeł o podanym kluczu, w podanym poddrzewie
		 *
		 * \param node - korzeń poddrzewa
		 * \param key - poszukiwany klucz
		 */
		Node* find(Node* node,const KeyType& key);

		/*!
		 * \brief Pozwala znaleźć węzeł za którym zostanie dodany kolejny
		 *
		 * \param node - korzeń poddrzewa
		 * \param key - poszukiwany klucz
		 */
		Node* findInsertNode(Node* node, const KeyType& key);

		/*!
		 * \brief Czyści poddrzewo usuwając z niego wszystkie węzły
		 *
		 * \param root - korzeń poddrzewa
		 */
		void clear(Node* root);

		/*!
		 * \brief Usuwa podany węzeł
		 *
		 * \param node - węzeł do usunięcia
		 */
		Node* remove(Node* node);

		/*!
		 * \brief Przechowuje korzeń całego drzewa
		 */
		Node* m_root;

		/*!
		 * \brief Przechowuje rozmiar całego drzewa
		 */
		unsigned long m_size;
};

template <typename KeyType, typename ValueType>
void BinaryST<KeyType,ValueType>::add(const KeyType& key, const ValueType& value)
{
	m_size++;
	if(!m_root)
	{
		m_root=new Node(key,value);
	}
	else
	{
		Node* foundNode=nullptr,*newNode=new Node(key,value);
		foundNode=findInsertNode(m_root,key);
		newNode->parent(foundNode);
		if(key!=foundNode->key())
			if(key<foundNode->key())
				foundNode->left(newNode);
			else
				foundNode->right(newNode);
		else
			foundNode->value(value);
	}
}

template <typename KeyType, typename ValueType>
void BinaryST<KeyType,ValueType>::remove(const KeyType& key)
{
	if(m_root)
	{
		Node* rmNode=find(m_root,key);
		if(rmNode)
		{
			remove(rmNode);
			m_size--;
		}
	}
}

template <typename KeyType, typename ValueType>
const ValueType& BinaryST<KeyType,ValueType>::find(const KeyType& key) const
{
	if(!m_root)
		throw "Key not found";
	const Node* foundNode=find(m_root,key);
	if(foundNode)
		return foundNode->value();
	throw "Key not found";
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::find(const Node* node,
		const KeyType& key) const -> const Node*
{
	if(node->key()==key)
		return node;
	if(node->hasLeft() && key<node->key())
		return find(node->left(),key);
	if(node->hasRight() && key>node->key())
		return find(node->right(),key);
	return nullptr;
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::find(Node* node,
		const KeyType& key) -> Node*
{
	if(node->key()==key)
		return node;
	if(node->hasLeft() && key<node->key())
		return find(node->left(),key);
	if(node->hasRight() && key>node->key())
		return find(node->right(),key);
	return nullptr;
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::findInsertNode(Node* node,const KeyType& key)->Node*
{
	if(!node->hasChildren())
		return node;
	if(node->key()==key)
		return node;
	if(!node->hasLeft() && node->key()>key)
		return node;
	if(!node->hasRight() && node->key()<key)
		return node;
	if(node->hasRight() && key>node->key())
		return findInsertNode(node->right(),key);
	return findInsertNode(node->left(),key);
}


template <typename KeyType, typename ValueType>
void BinaryST<KeyType,ValueType>::clear()
{
	clear(m_root);
	m_root=nullptr;
	m_size=0;
}

template <typename KeyType, typename ValueType>
void BinaryST<KeyType,ValueType>::clear(Node* root)
{
	if(root)
	{
		Node* left=root->left(),*right=root->right();
		delete root;
		clear(left);
		clear(right);
	}
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::Node::findMinNode() -> Node*
{
	Node* temp=this;
	while(temp->hasLeft())
			temp=temp->left();

	return temp;
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::Node::findMaxNode() -> Node*
{
	Node* temp=this;
	while(temp->hasRight())
		temp=temp->right();
	return temp;
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::Node::predecessor() -> Node*
{
	if(hasLeft())
		return left()->findMaxNode();
	Node* child=this,*par=parent();
	while(par && par->right()!=par)
	{
		child=par;
		par=par->parent();
	}
	return par;
}

template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::Node::successor() -> Node*
{
	if(hasRight())
		return right()->findMinNode();
	Node* child=this,*par=parent();
	while(par && par->left()!=par)
	{
		child=par;
		par=par->parent();
	}
	return par;
}


template <typename KeyType, typename ValueType>
auto BinaryST<KeyType,ValueType>::remove(Node* node) -> Node*
{
	Node* par=node->parent(),*temp;
	if(node->hasLeft() && node->hasRight())
	{
		temp=(rand()%2)? remove(node->predecessor()):remove(node->successor());
		temp->left(node->left());
		if(temp->hasLeft())
			temp->left()->parent(temp);
		temp->right(node->right());
		if(temp->hasRight())
			temp->right()->parent(temp);
	}
	else
		if(node->hasLeft())
			temp=node->left();
		else
			temp=node->right();

	if(temp)
		temp->parent(par);

	if(!par)
		m_root=temp;
	else
		if(par->left()==node)
			par->left(temp);
		else
			par->right(temp);

	return node;
}

#endif /* BINARYST_HPP_ */
