/**
 * \file dynamiclibrary.hpp
 * \author Thibault Schueller <thibault.schueller@islog.com>
 * \brief DynamicLibrary class
 */

#ifndef DYNAMICLIBRARY_HPP
#define DYNAMICLIBRARY_HPP

#include <dlfcn.h>

#include <string>

class DynamicLibrary
{
public:
    enum RelocationMode {
        Lazy = RTLD_LAZY,
        Now = RTLD_NOW
    };

public:
    DynamicLibrary(const std::string& file);
    ~DynamicLibrary();

public:
    void    open(RelocationMode mode = Lazy); // NOTE May throw DynLibException
    void    close(); // NOTE May throw DynLibException
    void*   getSymbol(const std::string& symbol); // NOTE May throw DynLibException

private:
    std::string _file;
    void*       _handle;
};

#endif // DYNAMICLIBRARY_HPP