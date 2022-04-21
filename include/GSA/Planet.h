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


#ifndef EmiROOT_Planet_h
#define EmiROOT_Planet_h

#include "Individual.h"

namespace EmiROOT {

  class Planet : public Individual {
  public:
    /// Empty constructor
    Planet();

    /// Planet default constructor
    Planet(int n);

    void setVelocity(std::size_t, double);

    void setMass(double);

    double getVelocity(std::size_t);

    double& getVelocityAddress(std::size_t t) { return m_velocity[t]; };

    double getMass();

  private:
    double              m_mass;
    std::vector<double> m_velocity; /**<Vector storing the velocity components*/
  };

}
#endif
