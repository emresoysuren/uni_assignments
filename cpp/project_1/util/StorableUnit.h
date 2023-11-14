#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Utils.h"

class StorableUnit
{
private:
    std::string getFormatedArgs() const;

protected:
    std::string virtual getPath() const = 0;
    std::vector<std::string> virtual getArgs() const = 0;

    std::vector<std::string> getStored() const;
    static std::vector<std::string> getStored(std::string, std::string);

    void deleteStored() const;
    void save() const;
    void resave() const;

    static std::vector<std::vector<std::string>> getAllStored(std::string);

    static bool isKeyUnique(std::string, std::string);
    bool isKeyUnique(std::string) const;

    static void deleteOnAnyMatch(std::string, std::string);

public:
};
