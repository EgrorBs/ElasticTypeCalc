#include "pch.h"
#include "CalcFncVarController.h"
#include <cmath>

CalcFncVarController::CalcFncVarController() {
	this->setFnc("sin", new std::function<TypedNum(TypedNum)>(
		[](TypedNum num) {
			return num.binOperator([](ElasticType type, double val) {
				return std::pair<ElasticType, double>(
					ElasticType(""),
					sin(val*3.1415/180)
				);
			});
		}
	));

	this->setFnc("cos", new std::function<TypedNum(TypedNum)>(
		[](TypedNum num) {
			return num.binOperator([](ElasticType type, double val) {
				return std::pair<ElasticType, double>(
					ElasticType(""),
					cos(val*3.1415 / 180)
				);
			});
		}
	));

	this->setFnc("sqrt", new std::function<TypedNum(TypedNum)>(
		[](TypedNum num) {
			return num.binOperator([](ElasticType type, double val) {
				return std::pair<ElasticType, double>(
					type.binOperator([](std::string type, int val) {
						if (val % 2 == 0)
							return std::pair<std::string, int>(type, val / 2);
						else
							return std::pair<std::string, int>("sqrt(" + type + ")", 1);
					}),
					sqrt(val)
				);
			});
		}
	));
}


CalcFncVarController::~CalcFncVarController() {
}

void CalcFncVarController::setVar(std::string var, TypedNum value) {
	this->vars[var] = value;
}

void CalcFncVarController::setFnc(std::string name, std::function<TypedNum(TypedNum)>* fnc) {
	this->fncs[name] = fnc;
}

void CalcFncVarController::delVar(std::string var) {
	this->vars.erase(var);
}

void CalcFncVarController::delFnc(std::string fnc) {
	this->fncs.erase(fnc);
}

bool CalcFncVarController::isVar(std::string var) const {
	return this->vars.count(var);
}

bool CalcFncVarController::isFnc(std::string fnc) const {
	return this->fncs.count(fnc) > 0;
}

TypedNum CalcFncVarController::compVar(std::string var) const {
	return this->vars.at(var);
}

TypedNum CalcFncVarController::compFnc(std::string fnc, TypedNum par) const {
	return this->fncs.at(fnc)->operator()(par);
}

unsigned int CalcFncVarController::addOnChange(std::function<void(void)> cb) {
	unsigned int idx = 0;
	for (idx = 0; true; idx++) {
		if (this->onChange.count(idx) == 0) {
			this->onChange[idx] = cb;
			return idx;
		}
	}
}

void CalcFncVarController::delOnChange(unsigned int id) {
	this->onChange.erase(id);
}
