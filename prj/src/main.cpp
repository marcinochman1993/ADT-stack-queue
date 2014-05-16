#include "Benchmark.hpp"
#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include "Simplex.hpp"

int main(int argc, char* argv[])
{
	std::cout<<"******************************\n";
	Constraint<double> c11, c12, c13;
	const int PROBLEMSIZE1 = 2, PROBLEMSIZE2 = 3;
	c11.size(PROBLEMSIZE1);c12.size(PROBLEMSIZE1);c13.size(PROBLEMSIZE1);
	c11.setCoeff(0, 1);c11.setCoeff(1, 0);c11.setB(4);
	c12.setCoeff(0, 0);c12.setCoeff(1, 2);c12.setB(12);
	c13.setCoeff(0, 3);c13.setCoeff(1, 2);c13.setB(18);
	std::vector<Constraint<double>> constraints1 = { c11, c12, c13 };
	ObjectiveFunction<double> fun1 = { 3000, 5000 };
	std::cout<<"PROBLEM nr 1:\n\nMaksymalizacja: "<<fun1<<std::endl<<"Przy ograniczeniach:\n"
			<<c11<<std::endl<<c12<<std::endl<<c13<<std::endl<<std::endl;
	Matrix<double> simplexTab(constraints1.size() + 1,
			fun1.size() + constraints1.size() + 2);
	FunctionArguments<double> solution1 = simplex(constraints1, fun1);
	std::cout <<"Rozwiazanie: "<< solution1 << "\nWartosc funkcji: "<<fun1.calculate(solution1)
					<<"\n\n******************************\n";
	Constraint<double> c21,c22;
	c21.size(PROBLEMSIZE2);c22.size(PROBLEMSIZE2);
	c21.setCoeff(0,2);c21.setCoeff(1,3);c21.setCoeff(2,2);c21.setB(1000);
	c22.setCoeff(0,1);c22.setCoeff(1,1);c22.setCoeff(2,2);c22.setB(800);
	ObjectiveFunction<double> fun2 = {7,8,10};
	std::vector<Constraint<double>> constraints2={c21,c22};
	std::cout<<"PROBLEM nr 2:\n\nMaksymalizacja: "<<fun2<<std::endl<<"Przy ograniczeniach:\n"
			<<c21<<std::endl<<c22<<std::endl<<std::endl;
	FunctionArguments<double> solution2 = simplex(constraints2, fun2);
	std::cout <<"Rozwiazanie: "<< solution2 <<"\nWartosc funkcji: "
			<<fun2.calculate(solution2)<<"\n\n******************************\n";
	return 0;
}
