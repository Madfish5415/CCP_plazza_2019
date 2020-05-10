/*
** EPITECH PROJECT, 2020
** CCP_plazza_2019
** File description:
** SizesTests.cpp
*/

#include <criterion/criterion.h>
#include <fstream>
#include <iostream>
#include <cstdio>

#include "../src/pizza/Sizes.hpp"

Test(Sizes, Load_01)
{
    std::string fileName = "./data/testSizes1.txt";
    std::ofstream outfile (fileName);

    outfile << "S" << std::endl << "M" << std::endl << "L" << std::endl;

    outfile.close();

    pizza::Sizes::load(fileName);

    remove(fileName.c_str());

    auto sizes = pizza::Sizes::get();

    if (sizes.size() == 3 && sizes.count("S") == 1 && sizes.count("M") == 1 && sizes.count("L") == 1)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Sizes, Load_02)
{
    std::string fileName = "./data/testSizes2.txt";
    std::ofstream outfile (fileName);

    outfile << "S 1" << std::endl << "M 2" << std::endl << "L 3" << std::endl;

    outfile.close();

    pizza::Sizes::load(fileName);

    auto sizes = pizza::Sizes::get();

    remove(fileName.c_str());

    if (sizes.size() == 3 && sizes.count("S 1") == 1 && sizes.count("M 2") == 1 && sizes.count("L 3") == 1)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}

Test(Sizes, Load_03)
{
    std::string fileName = "./data/testSizes3.txt";
    std::ofstream outfile (fileName);

    outfile << "SS 01" << std::endl << "MX 02" << std::endl << "XXL 03" << std::endl;

    outfile.close();

    pizza::Sizes::load(fileName);

    remove(fileName.c_str());

    auto sizes = pizza::Sizes::get();

    if (sizes.size() == 3 && sizes.count("SS 01") == 1 && sizes.count("MX 02") == 1 && sizes.count("XXL 03") == 1)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}
