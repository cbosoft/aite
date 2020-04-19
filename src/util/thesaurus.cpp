#include "random.hpp"
#include "thesaurus.hpp"
#include "exception.hpp"

#include <map>
#include <vector>
#include <array>


// not actually a fully fledged thesaurus, just fetches words from a category
static const std::map<std::string, std::vector<std::array<const char *, 5>>> THESAURUS = {
  { 
    "start", {
      {"start", NULL, "started", "starting", "start"},
      {"beginning", NULL, "begun", "beginning", "begin"},
      {"Caledonia", NULL, NULL, NULL, NULL},
    },
  }
};

static const char *FORM_TO_STR[] = {"Noun", "Adjective", "Verb (past tense)", "Verb (present tense)", "Verb (future tense)"};



std::string get_random_synonym(std::string word, NOUN_ADJECTIVE_VERB form, TENSE tense)
{
  auto result = THESAURUS.find(word);
  if (result == THESAURUS.end())
    throw WordNotFoundError(Formatter() << "Could not find category " << word << "." );

  auto rows = (*result).second;
  int cindex = 0;

  switch (form) {

    case VERB:
      cindex += int(tense);
      /* fall through */
    case NOUN:
    case ADJECTIVE:
      cindex += int(form);
      break;
  }

  const char *synonym = nullptr;
  for (int i = 0; synonym != nullptr; i++) {

    if (i > 100) {
      throw WordNotFoundError(Formatter() << "Could not find word for category " << word << " of type " << FORM_TO_STR[cindex] << "." );
    }

    int rindex = uniform_rand_i(0, rows.size()-1);
    auto row = rows[rindex];

    synonym = row[cindex];
  }

  return std::string(synonym);
}
