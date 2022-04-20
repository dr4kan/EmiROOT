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


#ifndef EmiROOT_Types_h
#define EmiROOT_Types_h

#include "Parameter.h"
#include "Constraint.h"
#include <functional>

namespace EmiROOT {

  typedef std::vector<double> Point;

  typedef std::function<double(Point)> Function;

  /// - L  : <
  /// - LEQ: <=
  /// - G  : >
  /// - GEQ: >=
  enum Inequality {L, LEQ, G, GEQ};

  /// Possible treatment of out-of-boundary solutions:
  /// - PBC: Periodic Boundary Condition
  /// - RBC: Reflective Boundary Condition
  /// - BAB: Back At boundaries
  /// - DIS: Disregard the solution and generate a new one
  enum OOBMethod {PBC, RBC, BAB, DIS};

}
#endif
