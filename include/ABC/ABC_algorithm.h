/*
###############################################################################
# Emir: EmiR: Evolutionary minimization forR                                  #
# Copyright (C) 2021 Davide Pagano & Lorenzo Sostero                          #
#                                                                             #
# This program is free software: you can redistribute it and/or modify        #
# it under the terms of the GNU General Public License as published by        #
# the Free Software Foundation, either version 3 of the License, or           #
# any later version.                                                          #
#                                                                             #
# This program is distributed in the hope that it will be useful, but         #
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY  #
# or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    #
# for more details: <https://www.gnu.org/licenses/>.                          #
###############################################################################
*/


#ifndef EmiROOT_ABC_algorithm_h
#define EmiROOT_ABC_algorithm_h

#include "Algorithm.h"
#include "ABCConfig.h"
#include "ABCPopulation.h"

namespace EmiROOT {

  class ABC_algorithm : public Algorithm {
  public:
    ABC_algorithm(const Function&, const ABCConfig&);

    void setSeed(uint64_t);

    void minimize();

  private:

    ABCConfig m_algo_config;
    ABCPopulation m_population;
  };

}
#endif
