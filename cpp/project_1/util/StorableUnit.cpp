#include "StorableUnit.h"

void StorableUnit::save() const
{
    std::ofstream file(getPath(), std::ios::app);

    file << getFormatedArgs() << std::endl;

    file.close();
}

bool StorableUnit::isKeyUnique(std::string path, std::string key)
{
    std::ifstream file(path);

    std::string line;

    while (getline(file, line))
    {
        for (std::string word : Utils::spiltString(line, ';'))
        {
            if (word == key)
            {
                return false;
            }
        }
    }

    file.close();

    return true;
}

bool StorableUnit::isKeyUnique(std::string key) const
{
    return isKeyUnique(getPath(), key);
}

void StorableUnit::resave() const
{
    std::ifstream file(getPath());
    std::ofstream temp("temp.data");

    const std::string key = getArgs()[0];

    std::string line;

    while (getline(file, line))
    {
        if (line.substr(0, line.find(';')) == key)
        {
            temp << getFormatedArgs() << std::endl;
        }
        else
        {
            temp << line << std::endl;
        }
    }

    file.close();
    temp.close();

    remove(getPath().c_str());
    rename("temp.data", getPath().c_str());
}

std::string StorableUnit::getFormatedArgs() const
{
    std::string result = "";

    for (std::string arg : getArgs())
    {
        result += arg + ";";
    }

    return result;
}

std::vector<std::string> StorableUnit::getStored(std::string path, std::string key)
{
    std::ifstream file(path);

    std::string line;

    while (getline(file, line))
    {
        if (line.substr(0, line.find(';')) == key)
        {
            file.close();

            return Utils::spiltString(line, ';');
        }
    }

    throw std::invalid_argument("Key not found");
}

std::vector<std::string> StorableUnit::getStored() const
{
    return getStored(getPath(), getArgs()[0]);
}

std::vector<std::vector<std::string>> StorableUnit::getAllStored(std::string path)
{

    std::vector<std::vector<std::string>> result;

    std::ifstream file(path);

    std::string line;

    while (getline(file, line))
    {
        result.push_back(Utils::spiltString(line, ';'));
    }

    file.close();

    return result;
}

void StorableUnit::deleteStored() const
{
    std::ifstream rfile(getPath());
    std::ofstream temp("temp.data");

    const std::string key = getArgs()[0];

    std::string line;

    while (getline(rfile, line))
    {
        if (line.substr(0, line.find(';')) != key)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(getPath().c_str());
    rename("temp.data", getPath().c_str());
}

void StorableUnit::deleteOnAnyMatch(std::string path, std::string key)
{
    std::ifstream rfile(path);
    std::ofstream temp("temp.data");

    std::string line;

    while (getline(rfile, line))
    {
        bool isMatch = false;

        for (std::string word : Utils::spiltString(line, ';'))
        {
            if (word == key)
            {
                isMatch = true;
                break;
            }
        }

        if (!isMatch)
        {
            temp << line << std::endl;
        }
    }

    rfile.close();
    temp.close();

    remove(path.c_str());
    rename("temp.data", path.c_str());
}

std::vector<std::vector<std::string>> StorableUnit::findKeysContains(std::string path, std::string key)
{
    std::vector<std::vector<std::string>> result;

    std::ifstream rfile(path);

    std::string line;

    while (getline(rfile, line))
    {
        std::vector<std::string> words = Utils::spiltString(line, ';');

        for (std::string word : words)
        {
            if (word == key)
            {
                result.push_back(words);
                break;
            }
        }
    }

    rfile.close();

    return result;
}
