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


#include <MFO/MFOPopulation.h>

using namespace EmiROOT;

MFOPopulation::MFOPopulation(Function func) : Population(func) {
  m_a = 0.;
  m_n_flame = 0;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();
  m_individuals.resize(pop_size, Moth(d));

  if (m_initial_population.size() > 0) {

    // Load the positions provided by the user
    for (std::size_t i = 0; i < (std::size_t) m_initial_population.size(); ++i) {
      m_individuals[i].setPosition(m_initial_population[i]);
    }

  } else {

    // Generate randomly the position of the individuals
    if (!m_silent) std::cout << "Generating the initial population...\n";
    for (std::size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
    }

  }

  // Dummy assignment of the best individual. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::setConfig(const MFOConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double> > MFOPopulation::getPopulationPosition() {
  std::vector<std::vector<double> > positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


Moth* MFOPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::createFlames() {
  m_flames = m_individuals;
  std::sort(m_flames.begin(), m_flames.end());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::updateParameters(std::size_t t) {
  m_a       = -1. + t*(-1./m_config.getNMaxIterations());
  m_n_flame = (std::size_t) round(m_individuals.size() - t*((m_individuals.size() - 1.)/m_config.getNMaxIterations()));
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::moveMoths() {
  double d_flame, r, b = 1.;
  // Loop on the population of moths
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {

    // Loop on dimension
    for (std::size_t j = 0; j < m_individuals[0].getDimension(); ++j) {

      d_flame = fabs(m_flames[i][j] - m_individuals[i][j]);
      r       = (m_a - 1.)*m_random.rand() + 1.;

      if (i <= m_n_flame) {
        m_individuals[i][j] = d_flame*exp(b*r)*cos(r*2*M_PI) + m_flames[i][j];
      } else {
        m_individuals[i][j] = d_flame*exp(b*r)*cos(r*2*M_PI) + m_flames[m_n_flame][j];
      }

      // boundary check
      checkBoundary(m_individuals[i]);
    }
  }

  // combine moths with flames and sort them
  m_flames.insert(m_flames.end(), m_individuals.begin(), m_individuals.end());
  std::sort(m_flames.begin(), m_flames.end());

  // keep the best
  m_flames.resize(m_individuals.size());
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void MFOPopulation::evaluate(Moth& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (value < m_best_solution.getCost()) {
    if (ckeckViolateConstraints(solution.getPosition()) == false) {
      m_best_solution = solution;
    }
  };

}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
