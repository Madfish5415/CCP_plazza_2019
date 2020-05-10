/*
** EPITECH PROJECT, 2020
** CPP_plazza_2019
** File description:
** Sizes.cpp
*/

#include "Sizes.hpp"

#include <fstream>
#include <filesystem>

std::set<std::string>& pizza::Sizes::_sizes()
{
    static std::set<std::string> sizes;

    return sizes;
}

std::set<std::string>& pizza::Sizes::get()
{
    return Sizes::_sizes();
}

void pizza::Sizes::load(const std::string& path)
{
    if (!pizza::Sizes::filewatcher(path)) {
        return;
    }

    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line))
        Sizes::_sizes().emplace(line);
}

bool pizza::Sizes::filewatcher(const std::string& path)
{
    static std::string path_to_file;
    static std::filesystem::file_time_type file_time = std::filesystem::last_write_time(path);

    if (path_to_file != path) {
        path_to_file = path;
        file_time = std::filesystem::last_write_time(path);
        return true;
    } else if (file_time != std::filesystem::last_write_time(path)) {
        file_time = std::filesystem::last_write_time(path);
        return true;
    } else {
        return false;
    }
}
