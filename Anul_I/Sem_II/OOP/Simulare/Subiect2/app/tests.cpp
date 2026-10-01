#include "tests.h"
#include "domain.h"
#include "repo.h"
#include "service.h"
#include "validator.h"
#include <cassert>
#include <fstream>
#include <iostream>

void testDomain() {

}

void testRepo() {

}

void testService() {

}

void testAll() {
	testDomain();
	std::cout << "Teste domain trecute!\n";
	testRepo();
	std::cout << "Teste repo trecute!\n";
	testService();
	std::cout << "Teste service trecute!\n";
	std::cout << "\nToate testele au trecut!\n";
}