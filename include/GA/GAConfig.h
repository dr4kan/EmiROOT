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


#ifndef EmiROOT_GAConfig_h
#define EmiROOT_GAConfig_h

#include "Config.h"
#include <string>

namespace EmiROOT {

  class GAConfig : public Config {
  public:

    /// Default empty constructor
    GAConfig();

    /// Set the mutation rate
    void setMutationRate(double);

    /// Set the selection rate
    void setKeepFraction(double);

    /// Set the values for m_keep and m_prob
    void setConfigCrossover();

    /// Return the mutation rate
    double getMutationRate() const;

    /// Return the selection rate
    double getKeepFraction() const;

    /// Return m_keep
    int getKeep() const;

    /// Return m_prob
    double getProb(int) const;

  private:

    double m_keep_fraction;     /**< Selection rate */
    double m_mutation_rate;     /**< Mutation rate */

    int                 m_keep; /**< Number of chromosomes that survives to selection */
    std::vector<double> m_prob; /**< Vector of probabilities used in the Roulette Wheel selection */
  };

}
#endif
