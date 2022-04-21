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


#ifndef EmiROOT_CSConfig_h
#define EmiROOT_CSConfig_h

#include "Config.h"

namespace EmiROOT {

  class CSConfig : public Config {
  public:
    /// CSConfig default constructor
    CSConfig();

    void setPa(double);

    void setAlpha(double);

    double getPa() const;

    double getAlpha() const;

  private:
    double m_pa;     /**< Discovery rate */
    double m_alpha;  /**< Step size */
  };

}
#endif
