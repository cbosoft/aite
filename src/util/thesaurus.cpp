#include <map>
#include <vector>
#include <array>
#include <regex>

#include "random.hpp"
#include "thesaurus.hpp"
#include "exception.hpp"
#include "sqlite.hpp"
#include "../resources/resources.hpp"


std::string Thesaurus::get_random_synonym(std::string word, std::string wordclass, std::string tense)
{
  return this->get_random_synonym(word, Thesaurus::str2class(wordclass), Thesaurus::str2tense(tense));
}


std::string Thesaurus::get_random_synonym(std::string word, WordClass wordclass, WordTense tense)
{
  // TODO: if keyword is capitalised, the result should be too.
  // TODO: if word is plural, result should be too

  std::string synonym;
  switch (wordclass) {
    case WC_Noun:
      synonym = this->get_random_noun_synonym(word);
      break;

    case WC_Adjective:
      synonym = this->get_random_adjective_synonym(word);
      break;

    case WC_Verb:
      synonym = this->get_random_verb_synonym(word, tense);
      break;

    case WC_Adverb:
      synonym = this->get_random_adverb_synonym(word);
      break;

    default:
    case WC_Default:
      synonym = this->get_random_default_synonym(word);
      break;
  };

  // TODO capitalise and pluralise here
  return synonym;

}


std::string Thesaurus::get_random_noun_synonym(std::string word)
{
  auto result = this->nouns.find(word);
  if (result == this->nouns.end())
    throw WordNotFoundError(Formatter() << "Could not find category " << word << "." );

  auto rows = (*result).second;
  return std::string(*select_randomly(rows.begin(), rows.end()));
}


std::string Thesaurus::get_random_adjective_synonym(std::string word)
{
  auto result = this->adjectives.find(word);
  if (result == this->adjectives.end())
    throw WordNotFoundError(Formatter() << "Could not find category " << word << "." );

  auto rows = (*result).second;
  return std::string(*select_randomly(rows.begin(), rows.end()));
}


std::string Thesaurus::get_random_verb_synonym(std::string word, WordTense tense)
{
  auto result = this->verbs.find(word);
  if (result == this->verbs.end())
    throw WordNotFoundError(Formatter() << "Could not find category " << word << "." );

  auto rows = (*result).second;
  return std::string( (*select_randomly(rows.begin(), rows.end()))[int(tense)] );
}


std::string Thesaurus::get_random_adverb_synonym(std::string word)
{
  auto result = this->adverbs.find(word);
  if (result == this->adverbs.end())
    throw WordNotFoundError(Formatter() << "Could not find category " << word << "." );

  auto rows = (*result).second;
  return (*select_randomly(rows.begin(), rows.end()));
}


std::string Thesaurus::get_random_default_synonym(std::string word)
{
  int classes = 0;
  WordClass cls = WC_Default;
  {
    auto result = this->nouns.find(word);
    if (result != this->nouns.end()) {
      classes ++;
      cls = WC_Noun;
    }
  }
  {
    auto result = this->adjectives.find(word);
    if (result != this->adjectives.end()) {
      classes ++;
      cls = WC_Adjective;
    }
  }
  {
    auto result = this->adverbs.find(word);
    if (result != this->adverbs.end()) {
      classes ++;
      cls = WC_Adverb;
    }
  }

  if (classes > 1) {
    AuthorError(Formatter() << "Ambiguous default for \"" << word << "\": use a class qualifier in prototype.");
  }
  else if (classes == 0) {
    throw WordNotFoundError(Formatter() << "Could not find category " << word << "." );
  }

  return this->get_random_synonym(word, cls);
}














WordTense Thesaurus::str2tense(std::string tense)
{
  if (tense.compare("past") == 0) {
    return WT_Past;
  }
  else if (tense.compare("present") == 0) {
    return WT_Present;
  }
  else if (tense.compare("future") == 0) {
    return WT_Future;
  }

  throw AuthorError(Formatter() << "Tense \"" << tense << "\" not understood.");
}


WordClass Thesaurus::str2class(std::string type)
{
  if (type.compare("noun") == 0) {
    return WC_Noun;
  }
  else if (type.compare("adjective") == 0) {
    return WC_Adjective;
  }
  else if (type.compare("verb") == 0) {
    return WC_Verb;
  }
  else if (type.compare("adverb") == 0) {
    return WC_Adverb;
  }
  else if (type.compare("default") == 0) {
    return WC_Default;
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


std::string Thesaurus::get_indefinite_article(std::string word)
{
  char *chars = word.data();
  char first = chars[0];

  if (is_vowel(first))
    return "an";

  // TODO aspirated and unaspirated Hs, eu-, un- word inconsistency and so on...

  return "a";
}


std::string Thesaurus::substitute_in_prototype(std::string prototype)
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
        thesaurus_result = this->get_random_synonym(keyword);
      }
    }
    else{
      if (tense.size() == 0) {
        thesaurus_result = this->get_random_synonym(keyword, type);
      }
      else {
        thesaurus_result = this->get_random_synonym(keyword, type, tense);
      }
    }

    if (thesaurus_result.size()) {
      if (add_article) {
        ss << Thesaurus::get_indefinite_article(thesaurus_result) << " ";
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


void Thesaurus::load()
{
  SQLiteInterface db(get_resource_path());
  SQLiteResults res = db.execute("SELECT DISTINCT Category FROM ThesaurusNouns;");
  std::list<std::string> categories;

  for (unsigned int i = 0; i < res.size(); i++) {
    categories.push_back(res[i]["Category"]);
  }

  for (auto category : categories) {
    this->nouns[category] = std::list<std::string>();

    res = db.execute(Formatter() << "SELECT Synonym FROM ThesaurusNouns WHERE Category=\"" << category << "\";");
    for (unsigned int i = 0; i < res.size(); i++) {
      this->nouns[category].push_back(res[i]["Synonym"]);
    }
  }

  res = db.execute("SELECT DISTINCT Category FROM ThesaurusAdjectives;");
  categories = std::list<std::string>();

  for (unsigned int i = 0; i < res.size(); i++) {
    categories.push_back(res[i]["Category"]);
  }

  for (auto category : categories) {
    this->adjectives[category] = std::list<std::string>();

    res = db.execute(Formatter() << "SELECT Synonym FROM ThesaurusAdjectives WHERE Category=\"" << category << "\";");
    for (unsigned int i = 0; i < res.size(); i++) {
      this->adjectives[category].push_back(res[i]["Synonym"]);
    }
  }

  res = db.execute("SELECT DISTINCT Category FROM ThesaurusAdverbs;");
  categories = std::list<std::string>();

  for (unsigned int i = 0; i < res.size(); i++) {
    categories.push_back(res[i]["Category"]);
  }

  for (auto category : categories) {
    this->adverbs[category] = std::list<std::string>();

    res = db.execute(Formatter() << "SELECT Synonym FROM ThesaurusAdverbs WHERE Category=\"" << category << "\";");
    for (unsigned int i = 0; i < res.size(); i++) {
      this->adverbs[category].push_back(res[i]["Synonym"]);
    }
  }

  res = db.execute("SELECT DISTINCT Category FROM ThesaurusVerbs;");
  categories = std::list<std::string>();

  for (unsigned int i = 0; i < res.size(); i++) {
    categories.push_back(res[i]["Category"]);
  }

  for (auto category : categories) {
    this->adjectives[category] = std::list<std::string>();

    res = db.execute(Formatter() << "SELECT Synonym FROM ThesaurusVerbs WHERE Category=\"" << category << "\";");
    for (unsigned int i = 0; i < res.size(); i++) {
      this->verbs[category].push_back({res[i]["PastTense"], res[i]["PresentTense"], res[i]["FutureTense"]});
    }
  }
}


static Thesaurus __thesaurus;
Thesaurus &Thesaurus::getref()
{
  if (not __thesaurus.is_loaded())
    __thesaurus.load();

  return __thesaurus;
}


bool Thesaurus::is_loaded()
{
  return this->loaded;
}

Thesaurus::~Thesaurus()
{
}

Thesaurus::Thesaurus()
{
  this->loaded = false;
}
