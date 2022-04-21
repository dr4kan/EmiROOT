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


#ifndef EmiROOT_PSParticle_h
#define EmiROOT_PSParticle_h

#include "Individual.h"

namespace EmiROOT {

  class PSParticle : public Individual {
  public:
    /// Empty constructor
    PSParticle();

    /// Particle Swarm default constructor
    PSParticle(int n);

    /// Update the best position and particle
    void setPersonalBest();

    void setVelocity(std::size_t, double);

    double getVelocity(std::size_t);

    double& getVelocityAddress(std::size_t t) { return m_velocity[t]; };

    double getBestPositionParticle(std::size_t);

    const std::vector<double>& getBestPositionParticle() const { return m_position_best; };

    friend bool operator<(const PSParticle &l, const PSParticle &r) { return l.m_cost_best < r.m_cost_best; };

  private:
    std::vector<double> m_velocity;
    std::vector<double> m_position_best;
    double              m_cost_best;
  };

}
#endif
