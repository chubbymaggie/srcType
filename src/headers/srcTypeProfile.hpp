#ifndef INCLUDED_SRCTYPEPROFILE_HPP
#define INCLUDED_SRCTYPEPROFILE_HPP

#include <string>
#include <iostream>
#include <exception>
#include <unordered_map>
namespace srcTypeNS{    
    enum PrimTypes{INT, UINT, SIINT, SHINT, SISINT, USISINT, LINT, SLINT, USILINT, SILINT, LDOUBLE, WCHAR, CHAR, UCHAR, SCHAR, VOID, FLOAT, BOOL, DOUBLE, SIZE_T};
    enum VarCategory {primitive=0, userdefined=1};
    
    static const std::unordered_map<std::string, PrimTypes> cppPrimTypes{
    {"int", INT},
    {"unsigned int", UINT},
    {"signed int", SIINT},
    {"short int", SHINT},
    {"signed short int", SISINT},
    {"unsigned short int", USISINT},
    {"long int", LINT},
    {"signed long int", SILINT},
    {"unsigned long int", USILINT},
    {"float", FLOAT},
    {"double", DOUBLE},
    {"long double", LDOUBLE},
    {"wchar_t", WCHAR},
    {"char", CHAR},
    {"unsigned char", UCHAR},
    {"signed char", SCHAR},
    {"void", VOID},
    {"float", FLOAT},
    {"bool", BOOL},
    {"double", DOUBLE},
    {"size_t", SIZE_T}};
};
#endif