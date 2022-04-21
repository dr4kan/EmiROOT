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


#ifndef EmiROOT_SearchSpace_h
#define EmiROOT_SearchSpace_h

#include "Parameter.h"
#include "Constraint.h"
#include "Random.h"

namespace EmiROOT {

  class SearchSpace {
  public:
    /// Empty constructor
    SearchSpace();

    /// SearchSpace constructor
    SearchSpace(int n);

    /// Set the seed for the random generator
    void setSeed(uint64_t);

    /// Set a parameter
    void setParameter(std::size_t, const std::string&, double, double, bool);
    void setParameter(std::size_t, const Parameter&);

    void setConstraints(const Constraints&);

    void setCostrInitPop(bool);

    /// Return the number of parameters
    std::size_t getNumberOfParameters() const;

    /// Return the specified component a random point in the search space
    double getRandom(std::size_t);

    /// Return a random point in the search space
    Point getRandom();

    /// Access the specified parameter
    Parameter &operator[](std::size_t t) { return m_par[t]; };

    /// Return a random number in [0, 1]
    double rand();

  private:
    bool ckeckConstraint();

    std::vector<Parameter> m_par;
    Random                 m_random;
    Constraints            m_constraints;
    Point                  m_gen_point;
    bool                   m_constr_init_pop;
  };

}
#endif
