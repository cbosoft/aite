#include "feature.hpp"


Feature::Feature(std::string name, std::string description, RandomLikelihood existence_likelihood, 
    RandomLikelihood occurence_likelihood)
  : Feature(name, description, existence_likelihood, occurence_likelihood, nullptr)
{
  // do nothing
}



Feature::Feature(std::string name, std::string description, RandomLikelihood existence_likelihood, 
    RandomLikelihood occurence_likelihood, HistoryElement_ptr associated_history)
  : name(name), description(description), existence_likelihood(existence_likelihood), 
  occurence_likelihood(occurence_likelihood), associated_history(associated_history)
{
  // do nothing
}


Feature::~Feature()
{
  // do nothing
}


bool Feature::has_history() const
{
  return this->associated_history == nullptr;
}


HistoryElement_ptr Feature::get_history() const
{
  return this->associated_history;
}


std::string Feature::describe() const
{
  return this->description;
}
