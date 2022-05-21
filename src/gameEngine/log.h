//
// Created by sashi0034 on 2022/05/07.
//

#ifndef FILL_TILES_LOG_H
#define FILL_TILES_LOG_H

#include <iostream>

#define DEBUG_BUILD

#define LOG_COUT std::cout << std::endl << " [OUT] " << __FILE__  << " ** " << __FUNCTION__ << " ** " << __LINE__ << std::endl
#define LOG_CERR std::cerr << std::endl << " [ERR] " << __FILE__  << " ** " << __FUNCTION__ << " ** " << __LINE__ << std::endl

#endif //FILL_TILES_LOG_H
