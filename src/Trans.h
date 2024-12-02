#pragma once
#ifndef PYTHON_INTERPRETER_TRANS_H
#define PYTHON_INTERPRETER_TRANS_H

#include "int2048.h"
#include <any>
#include <string>

bool anyToBoolean(std::any);

std::string anyToString(std::any);

int2048 anyToInt(std::any);

double anyToDouble(std::any);

#endif