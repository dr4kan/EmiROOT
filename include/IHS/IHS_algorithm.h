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


#ifndef EmiROOT_IHS_algorithm_h
#define EmiROOT_IHS_algorithm_h

#include "Algorithm.h"
#include "IHSConfig.h"
#include "IHSPopulation.h"

namespace EmiROOT {

  class IHS_algorithm : public Algorithm {
  public:
    IHS_algorithm(const Function&, const IHSConfig&);

    void setSeed(uint64_t);

    void minimize();

  private:

    IHSConfig m_algo_config;
    IHSPopulation m_population;
  };

}
#endif
