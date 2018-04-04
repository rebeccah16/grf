/*-------------------------------------------------------------------------------
  This file is part of generalized-random-forest.

  grf is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  grf is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with grf. If not, see <http://www.gnu.org/licenses/>.
 #-------------------------------------------------------------------------------*/

#ifndef GRF_INSTRUMENTALSPLITTINGRULE_H
#define GRF_INSTRUMENTALSPLITTINGRULE_H

#include "commons/Data.h"
#include "commons/Observations.h"
#include "splitting/SplittingRule.h"

class InstrumentalSplittingRule: public SplittingRule {
public:
  InstrumentalSplittingRule(Data* data,
                            const Observations& observations,
                            double alpha,
                            double lambda);
  ~InstrumentalSplittingRule();

  bool find_best_split(size_t node,
                       const std::vector<size_t>& possible_split_vars,
                       const std::unordered_map<size_t, double>& labels_by_sample,
                       const std::vector<std::vector<size_t>>& samples,
                       std::vector<size_t>& split_vars,
                       std::vector<double>& split_values);

private:
  void find_best_split_value_small_q(size_t node,
                                     size_t var,
                                     double sum_node,
                                     size_t node_size,
                                     size_t min_child_size,
                                     double& best_value,
                                     size_t& best_var,
                                     double& best_decrease,
                                     const std::unordered_map<size_t, double>& responses_by_sample,
                                     const std::vector<std::vector<size_t>>& samples);
  void find_best_split_value_large_q(size_t node,
                                     size_t var,
                                     double sum_node,
                                     size_t node_size,
                                     size_t min_child_size,
                                     double& best_value,
                                     size_t& best_var,
                                     double& best_decrease,
                                     const std::unordered_map<size_t, double>& responses_by_sample,
                                     const std::vector<std::vector<size_t>>& samples);

  Data* data;
  const Observations& observations;

  size_t* counter;
  double* sums;

  double alpha;
  double lambda;

  DISALLOW_COPY_AND_ASSIGN(InstrumentalSplittingRule);
};


#endif //GRF_INSTRUMENTALSPLITTINGRULE_H
