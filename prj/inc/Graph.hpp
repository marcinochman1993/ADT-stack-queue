/*
 * Graph.hpp
 *
 *  Created on: Apr 23, 2014
 *      Author: mochman
 */

#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <map>
#include <set>

/*!
 * \brief Klasa reprezentuje graf skierowany
 *
 * Graf jest zaimplementowany na podstawie list sąsiedztwa
 */
template <typename VType, typename EType>
class Graph
{
	public:
		struct Edge
		{
			VType neighbour;
			EType weight;
			bool operator<(const Edge& edge) const { return neighbour<edge.neighbour; }
			bool operator>(const Edge& edge) const { return neighbour>edge.neighbour; }
			bool operator!=(const Edge& edge) const { return neighbour!=edge.neighbour; }
			bool operator==(const Edge& edge) const { return neighbour==edge.neighbour; }
		};

		/*!
		 * \brief Pozwala na dodanie określonego wierzchołka
		 *
		 * Jeśli podany wierzcholek był już w grafie, to metoda
		 * pozostawia go, jednak usuwa wszystkie krawędzie,
		 * z którymi był połączony tzn. wierzchołek nie będzie
		 * połączony z żadnym innym wierzchołkiem
		 *
		 * \param v - wierzchołek, który ma zostać dodany do grafu
		 */
		void addVertice(const VType& v);

		/*! \brief Metoda usuwa z grafu podany wierzchołek
		 *
		 * \param v - wiezrchołek, który ma zostać usunięty z grafu
		 */
		void deleteVertice(const VType& v) { m_vertices.erase(v); }

		/*!
		 * \brief Pozwala na połączenie dwóch wierzchołków tzn. tworzy krawędź
		 *
		 * Jeśli wierzchołki nie mogą być połączone tzn. wtedy, gdy
		 * nie znaleziono jednego z wierzchołków w grafie, metoda zwraca false
		 * w.p.p true
		 *
		 * \param v1 - wierzchołek początkowy krawędzi
		 * \param v2 - wierzchołek końcowy krawędzi
		 *
		 */
		bool addEdge(const VType& v1, const VType& v2, const EType& weight);

		/*!
		 * \brief Pozwala na usunięcie krawędzi z grafu
		 *
		 * \param v1 - wierzchołek początkowy krawędzi
		 * \param v2 - wierzchołek końcowy krawędzi
		 */
		void deleteEdge(const VType& v1, const VType& v2);

		/*!
		 * \brief Sprawdza czy dwa wierzchołki są sąsiadami.
		 *
		 * Oznacza to, że metoda sprawdza czy istnieje krawędź
		 * skierowana od v1 do v2
		 *
		 * \param v1 - wierzchołek początkowy krawędzi
		 * \param v2 - wierzchołek końcowy krawędzi
		 */
		bool isNeighbour(const VType& v1, const VType& v2) const;

		/*!
		 * \brief Pobiera listę wierzchołków sąsiadujących z podanym wierzchołkiem
		 *
		 * Zwraca stały zbiór wierzchołków sąsiadujących
		 *
		 * \param v - wierzchołek, dla którego szukamy sąsiadów
		 */
		const std::set<Edge>& adj(const VType& v) const;

		/*!
		 * \brief Pobiera listę wierzchołków sąsiadujących z podanym wierzchołkiem
		 *
		 * Zwraca listę wierzchołków sąsiadujących
		 *
		 * \param v - wierzchołek, dla którego szukamy sąsiadów
		 */
		std::set<Edge>& adj(const VType& v);

		/*!
		 * \brief Sprawdza czy graf zawiera podany wierzchołek
		 *
		 * Zwraca true jeśli zawiera, w.p.p false
		 */
		bool contains(const VType& v) const;

		/*!
		 * \brief Sprawdza czy graf zawiera podaną krawędź
		 *
		 * Krawędź definiowana jest za pomocą dwóch wierzchołków
		 *
		 * \param v1 - wierzchołek startowy krawędzi
		 * \param v2 - wierzchołek końcowy krawędzi
		 */
		bool contains(const VType& v1, const VType& v2) const;

		/*!
		 * \brief Przechodzi graf w głąb.
		 *
		 * Jest wykonywany algorytm dfs, dla każdego odwiedzonego
		 * wierzchołka wykonywana jest odpowiednia funkcja
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param function - obiekt funkcyjny, który może być wywołany z param. VType
		 */
		template <typename F>
		void dfs(const VType& startVertice, F function);
	private:
		/*!
		 * \brief Przechodzi graf w głąb.
		 * Jest wykonywany algorytm dfs, dla każdego odwiedzonego
		 * wierzchołka wykonywana jest odpowiednia funkcja
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param function - obiekt funkcyjny, który może być wywołany z param. VType
		 * \param vertices - tablica asocjacyjna, w której zdefiniowane jest czy dany wierzcholek został już odwiedzony
		 *
		 */
		template <typename F>
		void dfs(const VType& vertice, F function, std::map<VType, bool>& vertices);

		/*!
		 * \brief Pole przechowujące informacje o wierzchołkach
		 */
		std::map<VType,std::set<Edge>> m_vertices;

};

template <typename VType, typename EType>
void Graph<VType,EType>::addVertice(const VType& v)
{
	std::pair<VType,std::set<Edge>> vertice;
	vertice.first=v;
	auto it=m_vertices.insert(vertice);
	it.first->second.clear();
}

template <typename VType, typename EType>
bool Graph<VType,EType>::addEdge(const VType& v1, const VType& v2, const EType& weight)
{
	auto itv1=m_vertices.find(v1),itv2=m_vertices.find(v2);
	if(itv1!=m_vertices.end() && itv2!=m_vertices.end())
	{
		Edge edge={v2,weight};
		itv1->second.insert(edge);
		return true;
	}
	return false;
}

template <typename VType, typename EType>
void Graph<VType,EType>::deleteEdge(const VType& v1, const VType& v2)
{
	auto itv1=m_vertices.find(v1),itv2=m_vertices.find(v2);
	if(itv1!=m_vertices.end() && itv2!=m_vertices.end())
		itv1->second.erase(v2);
}

template <typename VType, typename EType>
bool Graph<VType,EType>::isNeighbour(const VType& v1, const VType& v2) const
{
	auto itv1=m_vertices.find(v1);
	if(itv1==m_vertices.end())
		return false;
	auto itv2=itv1->second.find(v2);
	if(itv2!=itv1->second.end())
		return true;
	return false;
}

template <typename VType, typename EType>
bool Graph<VType,EType>::contains(const VType& v) const
{
	auto it=m_vertices.find(v);
	if(it!=m_vertices.end())
		return true;
	return false;
}

template <typename VType, typename EType>
const std::set<typename Graph<VType,EType>::Edge>& Graph<VType,EType>::adj(const VType& v) const
{
	auto itv=m_vertices.find(v);
	if(itv!=m_vertices.end())
		return itv->second;
	throw "Vertice not found";
}

template <typename VType, typename EType>
std::set<typename Graph<VType,EType>::Edge>& Graph<VType,EType>::adj(const VType& v)
{
	auto itv=m_vertices.find(v);
	if(itv!=m_vertices.end())
		return itv->second;
	throw "Vertice not found";
}

template <typename VType, typename EType>
bool Graph<VType,EType>::contains(const VType& v1, const VType& v2) const
{
	auto itv1=m_vertices.find(v1);
	Edge edge;
	edge.neighbour=v2;
	auto itv2=itv1->second.find(edge);
	if(itv1!=m_vertices.end() && itv2!=itv1->second.end())
		return true;
	return false;
}

template <typename VType, typename EType>
template <typename F>
void Graph<VType,EType>::dfs(const VType& startVertice, F function)
{
	std::map<VType,bool> vertices;
	for(auto it=m_vertices.begin();it!=m_vertices.end();it++)
	{
		std::pair<VType,bool> pair={it->first,false};
		vertices.insert(pair);
	}
	dfs(startVertice, function, vertices);
}

template <typename VType, typename EType>
template <typename F>
void Graph<VType,EType>::dfs(const VType& vertice, F function,
		std::map<VType, bool>& vertices)
{
	if(!contains(vertice))
		throw "Vertice not found";
	if(!vertices[vertice])
	{
		function(vertice);
		vertices[vertice]=true;
	}
	std::set<Edge>& neighbours=adj(vertice);
	for(auto it=neighbours.begin();it!=neighbours.end();it++)
	  if(!vertices[it->neighbour])
	    dfs(it->neighbour,function,vertices);
}
#endif /* GRAPH_HPP_ */
