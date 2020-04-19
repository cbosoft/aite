#include "compound.hpp"

Compound::Compound(std::initializer_list<std::pair<Element_ptr, int>> form)
  : form(form)
{
  // do nothing
}

Compound::~Compound()
{
  // do nothing
}


std::list<std::pair<Compound_ptr, double>> Compound::get_probable_compounds(std::list<std::pair<Element_ptr, double>> elemental_composition)
{

  double min_abundance = 1e9;
  for (auto ea : elemental_composition) {
    if (ea.second < min_abundance)
      min_abundance = ea.second;
  }

  std::list<int> number_ratio;
  for (auto ea : elemental_composition) {
    int rat = int(ea.second / min_abundance);
    number_ratio.push_back(rat);
  }

  elemental_composition.sort(CompositionSortByNumberElectrons());
  auto eait_i = elemental_composition.begin();
  auto ratit_i = number_ratio.begin();
  for (; eait_i != elemental_composition.end();  eait_i++, ratit_i++) {
    Element_ptr elem_i = (*eait_i).first;
    int ratio_i = (*ratit_i);

    auto eait_j = elemental_composition.begin();
    auto ratit_j = number_ratio.begin();
    for (; eait_j != elemental_composition.end();  eait_j++, ratit_j++) {
      Element_ptr elem_j = (*eait_j).first;

      if (elem_i->get_number_electrons() < elem_j->get_number_electrons())
        continue;

      int ratio_j = (*ratit_j);
      // TODO
      // use the valency of the two elements to create the forumula for a
      // potential compound
      //
      // use the ratio of the elements together to then decide on a probability
      // that this compound exists



    }

  }

}
