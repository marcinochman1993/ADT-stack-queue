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
#include <queue>
#include <fstream>
#include <stack>
#include <list>
#include <algorithm>
/*!
 * \brief Klasa reprezentuje graf skierowany
 *
 * Graf jest zaimplementowany na podstawie list sąsiedztwa
 */
template<typename VType, typename EType>
class Graph
{
	public:
		/*!
		 * \brief Struktura pomocnicza przechowująca sąsiada wierzchołka oraz wagę połączenia
		 */
		struct Edge
		{
				/*!
				 * \brief Sąsiad wierzchołka
				 */
				VType neighbour;

				/*!
				 * \brief Waga krawędzi
				 */
				EType weight;

				/*!
				 * \brief Przeciążony operator < dla struktury
				 *
				 * Porównuje sąsiadów struktury
				 *
				 * \param edge - druga struktura do porównania
				 */
				bool operator<(const Edge& edge) const
				{
					return neighbour < edge.neighbour;
				}

				/*!
				 * \brief Przeciążony operator > dla struktury
				 *
				 * Porównuje sąsiadów struktury
				 *
				 * \param edge - druga struktura do porównania
				 */
				bool operator>(const Edge& edge) const
				{
					return neighbour > edge.neighbour;
				}

				/*!
				 * \brief Przeciążony operator != dla struktury
				 *
				 * Porównuje sąsiadów struktury
				 *
				 * \param edge - druga struktura do porównania
				 */
				bool operator!=(const Edge& edge) const
				{
					return neighbour != edge.neighbour;
				}

				/*!
				 * \brief Przeciążony operator równości dla struktury
				 *
				 * Porównuje sąsiadów struktury
				 *
				 * \param edge - druga struktura do porównania
				 */
				bool operator==(const Edge& edge) const
				{
					return neighbour == edge.neighbour;
				}
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
		void deleteVertice(const VType& v)
		{
			m_vertices.erase(v);
		}

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
		 * \brief Pozwala pobrać wagę krawędzi
		 *
		 * Jeśli taka krawędź nie istnieje, jest wyrzucany wyjątek const char*
		 */
		const EType& weight(const VType& v1, const VType& v2) const;

		/*!
		 * \brief Przechodzi graf w głąb.
		 *
		 * Jest wykonywany algorytm dfs, dla każdego odwiedzonego
		 * wierzchołka wykonywana jest odpowiednia funkcja
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param function - obiekt funkcyjny, który może być wywołany z param. VType
		 */
		template<typename F>
		void dfs(const VType& startVertice, F function);

		/*!
		 * \brief Przechodzi graf w głąb.
		 *
		 * Jest wykonywany algorytm dfs, jeśli zostanie napotkany wierzchołek
		 * endVertice, kończone jest działanie algorytmu i odbudowana zostaje
		 * ścieżka. Zwracana jest lista wierzchołków kolejno odwiedzanych na ścieżce.
		 * Jeśli lista jest pusta to nie została znaleziona ścieżka do podanego wierzchołka.
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param endVertice - wierzchołek końcowy ścieżki
		 *
		 */
		std::list<VType> dfs(const VType& startVertice, const VType& endVertice);

		/*!
		 * \brief Przechodzi graf w szerz.
		 *
		 * Jest wykonywany algorytm bfs, dla każdego odwiedzonego
		 * wierzchołka wykonywana jest odpowiednia funkcja
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param function - obiekt funkcyjny, który może być wywołany z param. VType
		 */
		template<typename F>
		void bfs(const VType& startVertice, F function);

		/*!
		 * \brief Przechodzi graf w szerz.
		 *
		 * Jest wykonywany algorytm bfs, jeśli zostanie napotkany wierzchołek
		 * endVertice, kończone jest działanie algorytmu i odbudowana zostaje
		 * ścieżka. Zwracana jest lista wierzchołków kolejno odwiedzanych na ścieżce.
		 * Jeśli lista jest pusta to nie została znaleziona ścieżka do podanego wierzchołka.
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param endVertice - wierzchołek końcowy ścieżki
		 */
		std::list<VType> bfs(const VType& startVertice, const VType& endVertice);

		/*!
		 * \brief Przechodzi graf metodą best first.
		 *
		 * Jest wykonywany algorytm best first search, dla każdego odwiedzonego
		 * wierzchołka wykonywana jest odpowiednia funkcja
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param function - obiekt funkcyjny, który może być wywołany z param. VType
		 */
		template<typename F, typename Comp>
		void bestFirstSearch(const VType& startVertice, F function,
				Comp comparator);

		/*!
		 * \brief Przechodzi graf metodą best first
		 * Jest wykonywany algorytm best first search, jeśli zostanie napotkany wierzchołek
		 * endVertice, kończone jest działanie algorytmu i odbudowana zostaje
		 * ścieżka. Zwracana jest lista wierzchołków kolejno odwiedzanych na ścieżce.
		 * Jeśli lista jest pusta to nie została znaleziona ścieżka do podanego wierzchołka.
		 *
		 * \param startVertice - wierzchołek początkowy, od którego algorytm startuje
		 * \param endVertice - wierzchołek końcowy ścieżki
		 * \param comparator - komparator, który porównuje dla wybranego kryterium obiekty Edge
		 */
		template<typename Comp>
		std::list<VType> bestFirstSearch(const VType& startVertice,
				const VType& endVertice, Comp comparator);

		/*!
		 * \brief Wyszukuje ścieżkę za pomocą algorytmu A*
		 *
		 * \param startVertice - wierzchołek początkowy
		 * \param endVertice - wierzchołek końcowy
		 * \param heuristicFun - funkcja heurystyczna, pobiera jeden argument - wierzchołek
		 */
		template <typename HFunction>
		std::list<VType> aStar(const VType& startVertice, const VType& endVertice,
				HFunction heuristicFun);

		/*!
		 * \brief Na podstawie struktury grafu, generuje plik GV
		 *
		 * Plik gv służy do generowania plików, dzięki którym można wygenerować
		 * pliki prezentujące graficznie podany graf.
		 */
		void genGVFile(std::ofstream& file) const;
	private:

		/*!
		 * \brief Struktura pomocnicza dla algorytmu A*
		 */
		struct VertFV
		{
			/*!
			 * \brief Określa aktualny wierzchołek
			 */
			VType vertice;

			/*!
			 * \brief Wartość funkcji f
			 */
			EType fFunctionValue;

			/*!
			 * \brief Wartość funkcji f
			 */
			EType gFunctionValue;

			/*!
			 * \brief Operator większości
			 *
			 * Porównuje wartości funkcji f
			 */
			bool operator>(const VertFV& vertFV) const { return fFunctionValue>vertFV.fFunctionValue; }

			/*!
			 * \brief Operator mniejszości
			 *
			 * Porównuje wartości funkcji f
			 */
			bool operator<(const VertFV& vertFV) const { return fFunctionValue<vertFV.fFunctionValue; }

			/*
			 * \brief Operator równości
			 *
			 * Porównuje aktualne wierzchołki
			 */
			bool operator==(const VertFV& vertFV) const { return vertice==vertFV.vertice; }

			/*
			 * \brief Operator różności
			 *
			 * Porównuje aktualne wierzchołki
			 */
			bool operator!=(const VertFV& vertFV) const { return vertice!=vertFV.vertice; }
		};

		/*!
		 * \brief Na podstawie rodziców wierzchołków generuje ścieżkę
		 */
		std::list<VType> retracePath(std::map<VType,VType>& parents, const VType& beginVert, const VType& endVert) const;

		/*!
		 * \brief Pole przechowujące informacje o wierzchołkach
		 */
		std::map<VType, std::set<Edge>> m_vertices;

};

template<typename VType, typename EType>
void Graph<VType, EType>::addVertice(const VType& v)
{
	std::pair<VType, std::set<Edge>> vertice;
	vertice.first = v;
	auto it = m_vertices.insert(vertice);
	it.first->second.clear();
}

template<typename VType, typename EType>
bool Graph<VType, EType>::addEdge(const VType& v1, const VType& v2,
		const EType& weight)
{
	auto itv1 = m_vertices.find(v1), itv2 = m_vertices.find(v2);
	if(itv1 != m_vertices.end() && itv2 != m_vertices.end())
	{
		Edge edge = { v2, weight };
		itv1->second.insert(edge);
		return true;
	}
	return false;
}

template<typename VType, typename EType>
void Graph<VType, EType>::deleteEdge(const VType& v1, const VType& v2)
{
	auto itv1 = m_vertices.find(v1), itv2 = m_vertices.find(v2);
	if(itv1 != m_vertices.end() && itv2 != m_vertices.end())
		itv1->second.erase(v2);
}

template<typename VType, typename EType>
bool Graph<VType, EType>::isNeighbour(const VType& v1, const VType& v2) const
{
	auto itv1 = m_vertices.find(v1);
	if(itv1 == m_vertices.end())
		return false;
	auto itv2 = itv1->second.find(v2);
	if(itv2 != itv1->second.end())
		return true;
	return false;
}

template<typename VType, typename EType>
bool Graph<VType, EType>::contains(const VType& v) const
{
	auto it = m_vertices.find(v);
	if(it != m_vertices.end())
		return true;
	return false;
}

template<typename VType, typename EType>
const std::set<typename Graph<VType, EType>::Edge>& Graph<VType, EType>::adj(
		const VType& v) const
{
	auto itv = m_vertices.find(v);
	if(itv != m_vertices.end())
		return itv->second;
	throw "Vertice not found";
}

template<typename VType, typename EType>
std::set<typename Graph<VType, EType>::Edge>& Graph<VType, EType>::adj(
		const VType& v)
{
	auto itv = m_vertices.find(v);
	if(itv != m_vertices.end())
		return itv->second;
	throw "Vertice not found";
}

template<typename VType, typename EType>
bool Graph<VType, EType>::contains(const VType& v1, const VType& v2) const
{
	auto itv1 = m_vertices.find(v1);
	Edge edge;
	edge.neighbour = v2;
	auto itv2 = itv1->second.find(edge);
	if(itv1 != m_vertices.end() && itv2 != itv1->second.end())
		return true;
	return false;
}

template<typename VType, typename EType>
const EType& Graph<VType, EType>::weight(const VType& v1, const VType& v2) const
{
	if(!contains(v1, v2))
		throw "Edge not found";
	Edge temp;
	temp.neighbour = v2;
	auto it = adj(v1).find(temp);
	return it->weight;
}

template<typename VType, typename EType>
template<typename F>
void Graph<VType, EType>::dfs(const VType& startVertice, F function)
{
	if(!contains(startVertice))
		throw "Vertice not found";
	std::stack<VType> stack;
	stack.push(startVertice);
	std::map<VType, bool> visited;
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		std::pair<VType, bool> pair = { it->first, false };
		visited.insert(pair);
	}
	while (!stack.empty())
	{
		VType vertice = stack.top();
		stack.pop();
		if(!visited[vertice])
		{
			visited[vertice] = true;
			function(vertice);
			std::set<Edge>& neighbours = adj(vertice);
			for (auto it = neighbours.begin(); it != neighbours.end(); it++)
				if(!visited[it->neighbour])
					stack.push(it->neighbour);
		}
	}
}

template<typename VType, typename EType>
std::list<VType> Graph<VType, EType>::dfs(const VType& startVertice,
		const VType& endVertice)
{
	if(!contains(startVertice) || !contains(endVertice))
		return std::list<VType>();
	std::stack<VType> stack;
	stack.push(startVertice);
	std::map<VType, bool> visited;
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		std::pair<VType, bool> pair = { it->first, false };
		visited.insert(pair);
	}
	std::map<VType,VType> parents;
	while (!stack.empty() && !visited[endVertice])
	{
		VType vertice = stack.top();
		stack.pop();
		if(!visited[vertice])
		{
			visited[vertice] = true;
			std::set<Edge>& neighbours = adj(vertice);
			for (auto it = neighbours.begin();
					it != neighbours.end() && !visited[endVertice]; it++)
				if(!visited[it->neighbour])
				{
					stack.push(it->neighbour);
					parents[it->neighbour]=vertice;
				}
		}
	}
	return retracePath(parents,startVertice,endVertice);
}

template<typename VType, typename EType>
template<typename F>
void Graph<VType, EType>::bfs(const VType& startVertice, F function)
{
	if(!contains(startVertice))
		throw "Vertice not found";
	std::priority_queue<VType> queue;
	queue.push(startVertice);
	std::map<VType, bool> visited;
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		std::pair<VType, bool> pair = { it->first, false };
		visited.insert(pair);
	}
	visited[startVertice] = true;
	function(startVertice);
	while (!queue.empty())
	{
		VType vertice = queue.top();
		queue.pop();
		std::set<Edge>& neighbours = adj(vertice);
		for (auto it = neighbours.begin(); it != neighbours.end(); it++)
			if(!visited[it->neighbour])
			{
				queue.push(it->neighbour);
				visited[it->neighbour] = true;
				function(vertice);
			}
	}
}

template<typename VType, typename EType>
std::list<VType> Graph<VType, EType>::bfs(const VType& startVertice,
		const VType& endVertice)
{
	if(!contains(startVertice))
		throw "Vertice not found";
	std::queue<VType> queue;
	queue.push(startVertice);
	std::map<VType, bool> visited;
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		std::pair<VType, bool> pair = { it->first, false };
		visited.insert(pair);
	}
	std::map<VType,VType> parents;
	visited[startVertice] = true;
	while (!queue.empty() && !visited[endVertice])
	{
		VType vertice = queue.front();
		queue.pop();
		std::set<Edge>& neighbours = adj(vertice);
		for (auto it = neighbours.begin();
				it != neighbours.end() && !visited[endVertice]; it++)
			if(!visited[it->neighbour])
			{
				queue.push(it->neighbour);
				visited[it->neighbour] = true;
				parents[it->neighbour]=vertice;
			}
	}
	return retracePath(parents,startVertice,endVertice);
}

template<typename VType, typename EType>
template<typename F, typename Comp>
void Graph<VType, EType>::bestFirstSearch(const VType& startVertice, F function,
		Comp comparator)
{
	if(!contains(startVertice))
		throw "Start vertice not found";
	std::stack<VType> stack;
	stack.push(startVertice);
	std::map<VType, bool> visited;
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		std::pair<VType, bool> pair = { it->first, false };
		visited.insert(pair);
	}
	std::list<VType> visitedVertList;
	while (!stack.empty())
	{
		VType vertice = stack.top();
		stack.pop();
		if(!visited[vertice])
		{
			visited[vertice] = true;
			function(vertice);
			visitedVertList.push_front(vertice);
			std::set<Edge, Comp> neighbours(adj(vertice).begin(), adj(vertice).end(),
					comparator);
			for (auto it = neighbours.begin(); it != neighbours.end(); it++)
				if(!visited[it->neighbour])
					stack.push(it->neighbour);
		}
	}
}

template<typename VType, typename EType>
template<typename Comp>
std::list<VType> Graph<VType, EType>::bestFirstSearch(const VType& startVertice,
		const VType& endVertice, Comp comparator)
{
	if(!contains(startVertice) || !contains(endVertice))
		return std::list<VType>();
	std::stack<VType> stack;
	stack.push(startVertice);
	std::map<VType, bool> visited;
	for (auto it = m_vertices.begin(); it != m_vertices.end(); it++)
	{
		std::pair<VType, bool> pair = { it->first, false };
		visited.insert(pair);
	}
	std::map<VType,VType> parents;
	while (!stack.empty() && !visited[endVertice])
	{
		VType vertice = stack.top();
		stack.pop();
		if(!visited[vertice])
		{
			visited[vertice] = true;
			std::set<Edge, Comp> neighbours(adj(vertice).begin(), adj(vertice).end(),
					comparator);
			for (auto it = neighbours.begin();
					it != neighbours.end() && !visited[endVertice]; it++)
				if(!visited[it->neighbour])
				{
					stack.push(it->neighbour);
					parents[it->neighbour]=vertice;
				}
		}
	}
	return retracePath(parents,startVertice,endVertice);
}

template<typename VType, typename EType>
void Graph<VType, EType>::genGVFile(std::ofstream& file) const
{
	file << "digraph \n{\n" << "\trankdir=LR;\n";
	for (auto verticeIt = m_vertices.begin(); verticeIt != m_vertices.end();
			verticeIt++)
	{
		for (auto neighbourIt = verticeIt->second.begin();
				neighbourIt != verticeIt->second.end(); neighbourIt++)
		{
			file << '\t' << verticeIt->first << " -> " << neighbourIt->neighbour
					<< "[label = " << neighbourIt->weight << "];\n";
		}
	}
	file << '}';
}

template <typename VType, typename EType>
std::list<VType> Graph<VType, EType>::retracePath(std::map<VType,VType>& parents,
		const VType& beginVert, const VType& endVert) const
{
	VType temp=endVert;
	std::list<VType> path;
	while(temp!=beginVert)
	{
		path.push_front(temp);
		temp=parents[temp];
	}
	path.push_front(beginVert);
	return path;
}

template <typename VType, typename EType>
template <typename HFunction>
std::list<VType> Graph<VType, EType>::aStar(const VType& startVertice, const VType& endVertice,
		HFunction heuristicFun)
{
	std::set<VType> closedSet;
	std::list<VertFV> openSet;
	VertFV tempVFV={startVertice,0,0};
	openSet.push_back(tempVFV);
	std::map<VType,VType> parents;
	while(openSet.size()>0)
	{
		VertFV currVertice=*std::min_element(openSet.begin(),openSet.end());openSet.pop_front();
		if(currVertice.vertice==endVertice)
			return retracePath(parents,startVertice,currVertice.vertice);
		tempVFV.vertice=currVertice.vertice;
		openSet.remove(tempVFV);
		closedSet.insert(currVertice.vertice);
		for(const auto& it:adj(currVertice.vertice))
		{
			if(closedSet.find(it.neighbour)==closedSet.end())//nie ma w closedSet
			{
				EType tentGScore=currVertice.gFunctionValue+weight(currVertice.vertice,it.neighbour);
				bool tentIsBetter=false;
				tempVFV.vertice=it.neighbour;
				auto neighbourIt=std::find(openSet.begin(),openSet.end(),tempVFV);
				if(neighbourIt==openSet.end())//nie ma w openSet
				{
					openSet.push_back(tempVFV);					tentIsBetter=true;
				}
				else
					if(tentGScore<neighbourIt->gFunctionValue)
						tentIsBetter=true;
				if(tentIsBetter)
				{
					if(neighbourIt==openSet.end())
					{
						parents[openSet.back().vertice]=currVertice.vertice;
						openSet.back().gFunctionValue=tentGScore;
						openSet.back().fFunctionValue=tentGScore+heuristicFun(openSet.back().vertice);
					}
					else
					{
						parents[neighbourIt->vertice]=currVertice.vertice;
						neighbourIt->gFunctionValue=tentGScore;
						neighbourIt->fFunctionValue=tentGScore+heuristicFun(neighbourIt->vertice);
					}
				}
			}
		}
	}
	return std::list<VType>();
}

#endif /* GRAPH_HPP_ */
