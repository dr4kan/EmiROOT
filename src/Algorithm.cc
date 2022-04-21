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


#include "Algorithm.h"

using namespace EmiROOT;

Algorithm::Algorithm(Function obj_function) :
  m_obj_function(obj_function),
  m_pop_out_file_name(""),
  m_save_population(false),
  m_silent(false),
  m_maximize(false),
  m_oob_sol(RBC),
  m_algo_name("") {
    m_progress_bar.set_bar_width(50);
    m_progress_bar.fill_bar_progress_with("■");
    m_progress_bar.fill_bar_remainder_with(" ");
  }
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setConstraints(const Constraints& constraints) {
  m_constraints = constraints;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setParameters(const Parameters& parameters) {
  int n = parameters.size();
  m_search_space = SearchSpace(n);
  m_search_space.setConstraints(m_constraints);
  m_parameter_range = std::vector<std::vector<double> >(n);

  for (int i = 0; i < n; ++i) {
    m_search_space.setParameter(i, parameters[i].getName(), parameters[i].getMin(), parameters[i].getMax(), parameters[i].isInteger());
    m_parameter_range[i] = {parameters[i].getMin(), parameters[i].getMax()};
    m_parameter_names.push_back(parameters[i].getName());
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::savePopulation(bool t) {
  m_save_population = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setSilent(bool t) {
  m_silent = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setMaximize(bool t) {
  m_maximize = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setOOB(std::string t) {
  if (t == "PBC") {
    m_oob_sol = PBC;
  } else if (t == "BAB") {
    m_oob_sol = BAB;
  } else if (t == "DIS") {
    m_oob_sol = DIS;
  } else if (t == "RBC") {
    m_oob_sol = RBC;
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setConstrainedMethod(std::string t) {
  m_constrained_method = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setInitialPopulation(const PopulationState& t) {
  m_initial_population = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setAlgoName(std::string t) {
  m_algo_name = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setPenaltyScaling(double t) {
  m_penalty_scaling = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setStartPenaltyCoeff(double t) {
  m_start_penalty_param = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setMaxPenaltyCoeff(double t) {
  m_max_penalty_param = t;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::setCostrInitPop(bool t) {
  m_search_space.setCostrInitPop(t);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


double Algorithm::rand() {
  return m_search_space.rand();
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void Algorithm::addPopulationPosition(std::vector<std::vector<double> > v) {
  m_population_history.push_back(v);
};
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


OptimizationResults Algorithm::getResults() {
  OptimizationResults result;
  result.algorithm       = m_algo_name;
  result.iterations      = m_iter;
  result.population_size = m_population_base->getSize();
  result.obj_function    = m_obj_function;
  result.constraints     = m_constraints;
  result.best_cost       = m_maximize ? -m_population_base->getBestSolution()->getCost() : m_population_base->getBestSolution()->getCost();
  result.best_parameters = m_population_base->getBestSolution()->getParameters();
  result.parameter_range = m_parameter_range;
  result.pop_history     = m_population_history;
  result.parameter_names = m_parameter_names;
  result.cost_history    = m_cost_history;
  result.is_maximization = m_maximize;
  return result;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
