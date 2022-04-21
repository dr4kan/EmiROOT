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


#ifndef EmiROOT_Algorithm_h
#define EmiROOT_Algorithm_h

#include "SearchSpace.h"
#include "Utility.h"
#include "Types.h"
#include "Population.h"
#include "Results.h"
#include "ProgressBar.h"
#include <string>
#include <fstream>

namespace EmiROOT {

  class Algorithm {
  public:
    Algorithm(Function);

    void setConstraints(const Constraints&);
    void setParameters(const Parameters&);
    void savePopulation(bool);
    void setSilent(bool);
    void setMaximize(bool);
    void setOOB(std::string);
    void setConstrainedMethod(std::string);
    void setInitialPopulation(const PopulationState&);
    void setAlgoName(std::string);
    void setPenaltyScaling(double);
    void setStartPenaltyCoeff(double);
    void setMaxPenaltyCoeff(double);
    void setCostrInitPop(bool);
    OptimizationResults   getResults();
    virtual void setSeed(uint64_t) = 0;
    virtual void minimize() = 0;

  protected:
    double rand();
    void addPopulationPosition(std::vector<std::vector<double> >);
    ProgressBar       m_progress_bar;

    Function          m_obj_function;
    Constraints       m_constraints;
    SearchSpace       m_search_space;
    ParametersName    m_parameter_names;
    ParametersRange   m_parameter_range;
    CostHistory       m_cost_history;
    std::string       m_pop_out_file_name;
    bool              m_save_population;
    bool              m_silent;
    bool              m_maximize;
    OOBMethod         m_oob_sol;
    std::string       m_algo_name;
    std::size_t       m_iter;
    Population        *m_population_base;
    PopulationState   m_initial_population;
    std::ofstream     m_out_file;
    std::string       m_constrained_method;
    double            m_penalty_scaling;
    double            m_start_penalty_param;
    double            m_max_penalty_param;
    PopulationHistory m_population_history;
  };

}
#endif
