/*
###############################################################################
# EmiROOT: Evolutionary minimization for ROOT                                  #
# Copyright (C) 2022 Davide Pagano & Lorenzo Sostero                          #
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


#ifndef EmiROOT_CS_algorithm_h
#define EmiROOT_CS_algorithm_h

#include "Algorithm.h"
#include "CSConfig.h"
#include "CSPopulation.h"

namespace EmiROOT {

  class CS_algorithm : public Algorithm {
  public:
    CS_algorithm(const Function&, const CSConfig&);

    void setSeed(uint64_t);

    void minimize();

  private:

    CSConfig m_algo_config;
    CSPopulation m_population;
  };

}
#endif
