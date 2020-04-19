#include <list>
#include "electrons.hpp"


static std::list<std::pair<int, int>> possible_configs = {
  {1, 2},
  {2, 2},
  {2, 6},
  {3, 2},
  {3, 6},
  {4, 2},
  {3, 10},
  {4, 6},
  {5, 2},
  {4, 10},
  {5, 6},
  {6, 2},
  {4, 14},
  {5, 10},
  {6, 6},
  {7, 2},
  {5, 14},
  {6, 10},
  {7, 6}
};


int get_number_valence_electrons(int total_number_electrons)
{

  int highest_occupied = 0;
  int electron_shells[7] = {0};
  int running_number = total_number_electrons;

  for (auto lv : possible_configs) {
    int level = lv.first;
    int electrons_in_level = lv.second;

    if (level-1 > highest_occupied)
      highest_occupied = level-1;

    if (running_number < electrons_in_level) {
      electron_shells[level-1] += running_number;
      break;
    }
    else {
      running_number -= electrons_in_level;
      electron_shells[level-1] += electrons_in_level;
    }

    if (!running_number)
      break;
  }

  return electron_shells[highest_occupied];
}
