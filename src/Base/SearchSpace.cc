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


#include <Base/SearchSpace.h>
#include <iostream>

using namespace EmiROOT;

SearchSpace::SearchSpace() : m_par(0), m_constr_init_pop(false) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


SearchSpace::SearchSpace(int n) : m_par(n), m_gen_point(n), m_constr_init_pop(false) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SearchSpace::setSeed(uint64_t t_seed) {
  if (t_seed > 0) m_random = Random(t_seed);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SearchSpace::setParameter(std::size_t t, const std::string& t_name, double t_min, double t_max, bool integer) {
  if (t_name == "") {
    m_par[t].setName("p" + std::to_string(t));
  } else {
    m_par[t].setName(t_name);
  }
  m_par[t].setRange(t_min, t_max);
  m_par[t].setIsInteger(integer);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SearchSpace::setParameter(std::size_t t, const Parameter& t_par) {
  m_par[t] = t_par;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SearchSpace::setConstraints(const Constraints& constraints) {
  m_constraints = constraints;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::size_t SearchSpace::getNumberOfParameters() const {
  return m_par.size();
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void SearchSpace::setCostrInitPop(bool t) {
  m_constr_init_pop = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


bool SearchSpace::ckeckConstraint() {
  Function g;
  Inequality inequality;
  double tmp_d;
  for (size_t i = 0; i < m_constraints.size(); ++i) {
    g = m_constraints[i].getFunction();
    inequality = m_constraints[i].getInequality();
    tmp_d = g(m_gen_point);

    if (inequality == Inequality::L && tmp_d >= 0) {
      return true;
    } else if (inequality == Inequality::LEQ && tmp_d > 0) {
      return true;
    } else if (inequality == Inequality::GEQ && tmp_d < 0) {
      return true;
    } else if (inequality == Inequality::G && tmp_d <= 0) {
      return true;
    }
  }
  return false;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double SearchSpace::getRandom(std::size_t i) {
  double value = m_random.rand(m_par[i].getMin(), m_par[i].getMax());;
  return value;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Point SearchSpace::getRandom() {
  for (std::size_t i = 0; i < m_gen_point.size(); ++i) m_gen_point[i] = getRandom(i);

  // in case of a constrained optimization, check is
  // the solution violates any constraint
  if (m_constr_init_pop) {
    if (ckeckConstraint()) return getRandom();
  }

  return m_gen_point;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double SearchSpace::rand() {
  return m_random.rand();
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
