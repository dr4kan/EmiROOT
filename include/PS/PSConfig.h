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


#ifndef EmiROOT_PSConfig_h
#define EmiROOT_PSConfig_h

#include "Config.h"

namespace EmiROOT {

  class PSConfig : public Config {
  public:

    /// PSConfig default constructor
    PSConfig();

    void setAlpha(const std::vector<double>&);

    void setAlphaEvolution(double);

    /// Set the initial parameters
    void setCognitiveParameter(double);

    void setSocialParameter(double);

    void setInertia(double);

    const std::vector<double>& getAlpha() const;

    double getAlphaEvolution() const;

    /// Return the initial parameters
    double getCognitiveParameter() const;

    double getSocialParameter() const;

    double getInertia() const;

  private:

    std::vector<double> m_alpha;                /**< Maximum velocity in % of the range of parameters */
    double              m_h;                    /**< Parameter involved in updating velocities with iterations */
    double              m_social;               /**< Social parameter */
    double              m_cognitive;            /**< Cognitive parameter */
    double              m_inertia;              /**< Inertia factor */
  };

}
#endif
