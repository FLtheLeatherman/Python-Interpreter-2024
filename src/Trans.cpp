#include "Trans.h"

bool anyToBoolean(std::any val) {
    if (val.type() == typeid(std::string)) {
        std::string tmp = std::any_cast<std::string>(val);
        return tmp != "";
    } else if (val.type() == typeid(bool)) {
        return std::any_cast<bool>(val);
    } else if (val.type() == typeid(double)) {
        return std::any_cast<double>(val);
    } else {
        int2048 tmp = std::any_cast<int2048>(val);
        return tmp.getBoolean();
    }
    return true;
}

std::string anyToString(std::any val) {
    if (val.type() == typeid(std::string)) {
        return std::any_cast<std::string>(val);
    } else if (val.type() == typeid(bool)) {
        return std::to_string(std::any_cast<bool>(val));
    } else if (val.type() == typeid(double)) {
        std::string tmp = "";
        double val1 = std::any_cast<double>(val);
        return std::to_string(val1);
    } else {
        int2048 tmp = std::any_cast<int2048>(val);
        return tmp.getString();
    }
}

int2048 anyToInt(std::any val) {
    if (val.type() == typeid(std::string)) {
        return int2048(std::any_cast<std::string>(val));
    } else if (val.type() == typeid(bool)) {
        return int2048(std::any_cast<bool>(val) ? 1 : 0);
    } else if (val.type() == typeid(double)) {
        return int2048(std::any_cast<double>(val));
    } else {
        return std::any_cast<int2048>(val);
    }
}

double anyToDouble(std::any val) {
    if (val.type() == typeid(std::string)) {
        return std::stod(std::any_cast<std::string>(val));
    } else if (val.type() == typeid(bool)) {
        return std::any_cast<bool>(val) ? 1.0 : 0.0;
    } else if (val.type() == typeid(double)) {
        return std::any_cast<double>(val);
    } else {
        int2048 tmp = std::any_cast<int2048>(val);
        return tmp.getDouble();
    }
}