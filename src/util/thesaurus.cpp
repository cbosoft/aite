#include <map>
#include <vector>
#include <array>
#include <regex>

#include "random.hpp"
#include "thesaurus.hpp"
#include "exception.hpp"

const static std::regex RE_THESA("\\{\\{([\\w\\s]*)(?:,(\\w+))?(?:,(\\w+))?\\}\\}");

// TODO read this from file
// not actually a fully fledged thesaurus, just fetches words from a category
static const std::map<std::string, std::vector<std::array<const char *, 5>>> THESAURUS = {

  // MOSTLY NOUNS
  {"start", {
              {"start", nullptr, "started", "starting", "start"},
              {"beginning", nullptr, "begun", "beginning", "begin"},
              {"Caledonia", nullptr, nullptr, nullptr, nullptr},
            }},
  {"phenomenon", {
                   {"phenomenon", nullptr, nullptr, nullptr, nullptr},
                   {"property", nullptr, nullptr, nullptr, nullptr}
                 }},

  // WEATHER
  {"weather", {
                {"weather", nullptr, nullptr, nullptr, nullptr},
                {"climate", nullptr, nullptr, nullptr, nullptr}
              }},
  {"rain", {
             {"rain", nullptr, "rained", "raining", "rain"},
             {"showers", nullptr, nullptr, "showering", nullptr},
             {"precipitation", nullptr, "precipitated", "precipitating", "precipitate"}
           }},
  {"winds", {
             {"winds", nullptr, "rained", "raining", "rain"},
             {"gusts", nullptr, "precipitated", "precipitating", "precipitate"}
           }},
  {"strong winds", {
             {"gales", nullptr, "precipitated", "precipitating", "precipitate"},
             {"cylcones", nullptr, "precipitated", "precipitating", "precipitate"},
             {"typhoons", nullptr, "precipitated", "precipitating", "precipitate"},
           }},

  // ADJECTIVES
  {"very small", {
            {nullptr, "very small", nullptr, nullptr, nullptr},
            {nullptr, "tiny", nullptr, nullptr, nullptr}
           }},
  {"small", {
            {nullptr, "small", nullptr, nullptr, nullptr},
            {nullptr, "slight", nullptr, nullptr, nullptr}
           }},
  {"big", {
            {nullptr, "big", nullptr, nullptr, nullptr},
            {nullptr, "large", nullptr, nullptr, nullptr},
            {nullptr, "not inconsiderably sized", nullptr, nullptr, nullptr},
            {nullptr, "sizeable", nullptr, nullptr, nullptr},
            {nullptr, "hefty", nullptr, nullptr, nullptr},
            {nullptr, "substantial", nullptr, nullptr, nullptr},
            {nullptr, "ample", nullptr, nullptr, nullptr},
          }},
  {"very big", {
            {nullptr, "very big", nullptr, nullptr, nullptr},
            {nullptr, "huge", nullptr, nullptr, nullptr},
            {nullptr, "enormous", nullptr, nullptr, nullptr},
            {nullptr, "tremendous", nullptr, nullptr, nullptr},
          }},
  {"very very big", {
            {nullptr, "colosal", nullptr, nullptr, nullptr},
            {nullptr, "immense", nullptr, nullptr, nullptr},
            {nullptr, "humongous", nullptr, nullptr, nullptr},
            {nullptr, "vast", nullptr, nullptr, nullptr},
            {nullptr, "brobdingnagian", nullptr, nullptr, nullptr},
          }},
  {"strong", {
            {nullptr, "strong", nullptr, nullptr, nullptr},
            {nullptr, "severe", nullptr, nullptr, nullptr},
            {nullptr, "intense", nullptr, nullptr, nullptr},
            {nullptr, "forceful", nullptr, nullptr, nullptr},
          }},
  {"lively", {
            {nullptr, "lively", nullptr, nullptr, nullptr},
            {nullptr, "active", nullptr, nullptr, nullptr}
           }},
  {"violent", {
            {nullptr, "violent", nullptr, nullptr, nullptr},
            {nullptr, "tumultuous", nullptr, nullptr, nullptr},
            {nullptr, "riotous", nullptr, nullptr, nullptr},
            {nullptr, "turbulent", nullptr, nullptr, nullptr},
           }},
  {"elaborate", {
            {nullptr, "elaborate", nullptr, nullptr, nullptr},
            {nullptr, "complex", nullptr, nullptr, nullptr},
            {nullptr, "labyrinthine", nullptr, nullptr, nullptr},
           }},


  // PHRASES
  {"occasionally", {
                   {"from time to time", nullptr, nullptr, nullptr, nullptr},
                   {"occasionally", nullptr, nullptr, nullptr, nullptr}
                 }},

};

static const char *FORM_TO_STR[] = {"Noun", "Adjective", "Verb (past tense)", "Verb (present tense)", "Verb (future tense)"};



std::string get_random_synonym(std::string word, NOUN_ADJECTIVE_VERB form, TENSE tense)
{
  // TODO: if keyword is capitalised, the result should be too.
  // TODO: if word is plural, result should be too
  

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
  for (int i = 0; synonym == nullptr; i++) {

    if (i > 100) {
      throw WordNotFoundError(Formatter() << "Could not find word for category " << word << " of type " << FORM_TO_STR[cindex] << "." );
    }

    int rindex = uniform_rand_i(0, rows.size()-1);
    auto row = rows[rindex];

    synonym = row[cindex];
  }

  return std::string(synonym);
}


TENSE str2tense(std::string tense)
{
  if (tense.compare("past") == 0) {
    return PAST_TENSE;
  }
  else if (tense.compare("present") == 0) {
    return PRESENT_TENSE;
  }
  else if (tense.compare("future") == 0) {
    return FUTURE_TENSE;
  }

  throw AuthorError(Formatter() << "Tense \"" << tense << "\" not understood.");
}


NOUN_ADJECTIVE_VERB str2type (std::string type)
{
  if (type.compare("noun") == 0) {
    return NOUN;
  }
  else if (type.compare("adjective") == 0) {
    return ADJECTIVE;
  }
  else if (type.compare("verb") == 0) {
    return VERB;
  }

  throw AuthorError(Formatter() << "Word type \"" << type << "\" not understood.");
}


bool is_vowel(char c)
{
  const char vowels[] = {
    'a', 'e', 'i', 'o', 'u',
    'A', 'E', 'I', 'O', 'U',
  };

  for (int i = 0; i < 10; i ++) {
    if (c == vowels[i])
      return true;
  }

  return false;
}

std::string get_indefinite_article(std::string word)
{
  char *chars = word.data();
  char first = chars[0];

  if (is_vowel(first))
    return "an";

  // TODO aspirated and unaspirated Hs, eu-, un- word inconsistency and so on...

  return "a";
}



std::string substitute_in_prototype(std::string prototype)
{
  auto beg = std::sregex_iterator(prototype.begin(), prototype.end(), RE_THESA);
  auto end = std::sregex_iterator();

  int i = 0, len = prototype.size();
  const char *cdata = prototype.data();
  std::stringstream ss;
  bool add_article = false;
  for (auto it = beg; it != end; it++) {
    
    auto match = (*it);
    for (; i < match.position(); i++)
      ss << cdata[i];

    i += match.length();
    std::string keyword = match[1];
    std::string type = match[2];
    std::string tense = match[3];
    std::string thesaurus_result = "";

    if (type.size() == 0) {
      if ((keyword.compare("a") == 0) or (keyword.compare("an") == 0)) {
        i++;
        add_article = true;
      }
      else {
        thesaurus_result = get_random_synonym(keyword);
      }
    }
    else{
      if (tense.size() == 0) {
        thesaurus_result = get_random_synonym(keyword, str2type(type));
      }
      else {
        thesaurus_result = get_random_synonym(keyword, str2type(type), str2tense(tense));
      }
    }

    if (thesaurus_result.size()) {
      if (add_article) {
        ss << get_indefinite_article(thesaurus_result) << " ";
        add_article = false;
      }

      ss << thesaurus_result;
    }

  }

  for (; i < len; i++)
    ss << cdata[i];

  std::string result = ss.str();
  return result;
}
