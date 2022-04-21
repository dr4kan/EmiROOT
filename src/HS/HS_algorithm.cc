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


#include <HS/HS_algorithm.h>

using namespace EmiROOT;

HS_algorithm::HS_algorithm(const Function& obj_function, const HSConfig& config) :
Algorithm(obj_function),
m_population(HSPopulation(obj_function)) {
  m_algo_config = config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void HS_algorithm::setSeed(uint64_t t_seed) {
  m_search_space.setSeed(t_seed);
  m_population.setSeed(t_seed);
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void HS_algorithm::minimize() {
  m_iter = 0;
  std::size_t n_iter = m_algo_config.getNMaxIterations();
  double tolerance = m_algo_config.getAbsoluteTol();

  // Initialization of the population
  m_population.setConfig(m_algo_config);
  m_population.setSearchSpace(m_search_space);
  m_population.setConstraints(m_constraints);
  m_population.setConstrainedMethod(m_constrained_method);
  m_population.setPenaltyScaling(m_penalty_scaling);
  m_population.setStartPenaltyCoeff(m_start_penalty_param);
  m_population.setMaxPenaltyCoeff(m_max_penalty_param);
  m_population.setOOB(m_oob_sol);
  m_population.setMaximization(m_maximize);
  m_population.setInitialPopulation(m_initial_population);
  m_population.setSilent(m_silent);
  m_population.init();

  // Initialize the progress bar
  m_progress_bar.clear();

  // Evaluate the cost for the population
  m_population.evaluate();

  // Sort the population
  m_population.sort();

  // Update the cost history
  double current_best_cost = m_maximize ? -m_population.getBestSolution()->getCost() : m_population.getBestSolution()->getCost();
  m_cost_history.resize(n_iter);
  m_cost_history[0] = current_best_cost;

  // Update the population position history
  if (m_save_population) addPopulationPosition(m_population.getPopulationPosition());

  // Check if it is necessary to control the number of iterations at the same cost
  bool do_check_same_cost = false;
  if (n_iter > m_algo_config.getNMaxIterationsSameCost()) do_check_same_cost = true;

  std::size_t n_sc = 0;
  for (m_iter = 1; m_iter < n_iter; ++m_iter) {

    // scale the penalty coefficient for
    // constrained optimization
    m_population.scalePenaltyCoeff();

    // Generate a new harmony
    m_population.generateNewHarmony();

    // Sort the population
    m_population.sort();

    // Update the cost history
    current_best_cost = m_maximize ? -m_population.getBestSolution()->getCost() : m_population.getBestSolution()->getCost();
    m_cost_history[m_iter] = current_best_cost;

    // Update the population position history
    if (m_save_population) addPopulationPosition(m_population.getPopulationPosition());

    // Check on same cost iterations
    if (do_check_same_cost) {
      if (m_iter > 0 && tolerance == 0 && Utility::areEqual(m_cost_history[m_iter-1], m_cost_history[m_iter], 2) ) { //check machine defined precision
        n_sc++;
      } else if (m_iter > 0 && tolerance != 0 && (m_cost_history[m_iter-1] - m_cost_history[m_iter]) < tolerance) { //check using user defined precision
        n_sc++;
      }  else {
        n_sc = 0;
      };
      if (n_sc > m_algo_config.getNMaxIterationsSameCost()) {
        m_cost_history.resize(m_iter+1);
        break;
      }
    }

    // Update progress bar
    if (!m_silent && m_iter % 10 == 0) m_progress_bar.update(100.*m_iter/n_iter);
  }

  m_population_base = &m_population;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
