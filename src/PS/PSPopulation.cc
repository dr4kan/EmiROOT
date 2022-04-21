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


#include <PS/PSPopulation.h>

using namespace EmiROOT;

PSPopulation::PSPopulation(Function func) : Population(func) {}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::init() {
  std::size_t pop_size = m_config.getPopulationSize();
  std::size_t d = m_search_space.getNumberOfParameters();
  std::vector<double> alpha = m_config.getAlpha();

  // check on the size of alpha_vel
  if (alpha.size() == 1 && (std::size_t) alpha.size() < d) {
    std::vector<double> v(d);
    std::fill(v.begin(), v.end(), alpha[0]);
    alpha = v;
    m_config.setAlpha(alpha);
  } else if (alpha.size() > 1 && (std::size_t) alpha.size() != d) {
    std::cout << "Wrong size for parameter alpha_vel.\n";
    abort();
  }
  //////////////////////////////////////

  m_individuals.resize(pop_size, PSParticle(d));

  if (m_initial_population.size() > 0) {

    // Load the positions provided by the user
    for (std::size_t i = 0; i < (std::size_t) m_initial_population.size(); ++i) {
      m_individuals[i].setPosition(m_initial_population[i]);
    }

  } else {

    // Generate randomly the position of the Planets
    if (!m_silent) std::cout << "Generating the initial population...\n";
    double delta = 0.;
    for (std::size_t i = 0; i < m_individuals.size(); ++i) {
      m_individuals[i].setPosition(m_search_space.getRandom());
      for (std::size_t j = 0; j < d; ++j) {
        delta = m_search_space[j].getMax()-m_search_space[j].getMin();
        m_individuals[i].setVelocity(j, m_random.rand(-delta*alpha[j], delta*alpha[j]));
      }
    }
  }

  // Dummy assignment of the best planet. When the cost of
  // the population is actually evaluated this is fixed.
  m_best_solution = m_individuals[0];
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::setConfig(const PSConfig& t_config) {
  m_config = t_config;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


std::vector<std::vector<double>> PSPopulation::getPopulationPosition() {
  std::vector<std::vector<double>> positions(m_individuals.size());
  for (std::size_t i = 0; i < m_individuals.size(); ++i) positions[i] = m_individuals[i].getPosition();
  return positions;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


PSParticle* PSPopulation::getBestSolution() {
  return &m_best_solution;
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::setVelocity(std::size_t iter) {
  std::vector<double> alpha = m_config.getAlpha();
  double inertia_initial = m_config.getInertia();
  double h = m_config.getAlphaEvolution();
  std::size_t iter_max = m_config.getNMaxIterations();

  double cognitive_par = m_config.getCognitiveParameter();
  double social_par = m_config.getSocialParameter();
  double inertia = inertia_initial * (1.0 - 0.5 * ((double)(iter)/(double)iter_max));
  double k = std::pow(1.0 - ((double)(iter)/(double)iter_max), h);

  std::transform(alpha.begin(), alpha.end(), alpha.begin(), [k](double &c) { return c*k; });

  for (std::size_t j = 0; j < m_individuals[0].getDimension(); ++j) {

    double delta = m_search_space[j].getMax() - m_search_space[j].getMin();

    for (std::size_t i = 0; i < m_individuals.size(); ++i) {
      // Compute the step and assign if it satisfies the constraint on the maximum velocity
      double cognitive = cognitive_par * m_random.rand() *
      (m_individuals[i].getBestPositionParticle(j) - m_individuals[i][j]);
      double social = social_par * m_random.rand() *
      (m_best_solution[j] - m_individuals[i][j]);
      double vel = (m_individuals[i].getVelocity(j) * inertia + cognitive + social);

      if (fabs(vel) < alpha[j] * delta) {
        m_individuals[i].setVelocity(j, vel);
      } else {
        if (vel > alpha[j] * delta) {
          m_individuals[i].setVelocity(j, alpha[j] * delta);
        } else {
          m_individuals[i].setVelocity(j, - alpha[j] * delta);
        }
      }

    }
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::moveParticles(std::size_t iter) {
  // Change the velocity of the particles
  setVelocity(iter);

  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    for (std::size_t j = 0; j < m_individuals[0].getDimension(); ++j) {
      m_individuals[i][j] = m_individuals[i][j] + m_individuals[i].getVelocity(j);
    }

    // boundary check
    checkBoundary(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::evaluate() {
  for (std::size_t i = 0; i < m_individuals.size(); ++i) {
    evaluate(m_individuals[i]);
  }
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/


void PSPopulation::evaluate(PSParticle& solution) {
  double value = evaluateCost(solution.getPosition());
  solution.setCost(value);

  if (ckeckViolateConstraints(solution.getPosition()) == false) {

    // Update personal best solution
    solution.setPersonalBest();

    // Update the global best solution
    if (value < m_best_solution.getCost()) {
      m_best_solution = solution;
    }

  };
}
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
