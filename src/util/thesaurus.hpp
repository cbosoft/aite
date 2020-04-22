#pragma once

#include <string>
#include <map>
#include <list>
#include <array>
#include <regex>

enum TENSE { PAST_TENSE, PRESENT_TENSE, FUTURE_TENSE };
enum NOUN_ADJECTIVE_VERB {NOUN, ADJECTIVE, VERB};


class Thesaurus {

  private:

    std::regex RE_THESA = std::regex("\\{\\{([\\w\\s]*)(?:,(\\w+))?(?:,(\\w+))?\\}\\}");

    std::map<std::string, std::list<std::string>> nouns;
    std::map<std::string, std::list<std::string>> adjectives;
    std::map<std::string, std::list<std::array<std::string, 3>>> verbs;
    bool loaded;
    void load();

    static std::string get_indefinite_article(std::string word);
    static TENSE str2tense(std::string);
    static NOUN_ADJECTIVE_VERB str2type(std::string);
    std::string get_random_verb_synonym(std::string word, TENSE tense, bool capitalised);
    std::string get_random_adjective_synonym(std::string word, bool capitalised);
    std::string get_random_noun_synonym(std::string word, bool capitalised);

  public:

    Thesaurus();
    ~Thesaurus();

    static Thesaurus& getref();
    bool is_loaded();

    std::string get_random_synonym(std::string word, std::string form="noun", std::string tense="past"); // tense is ignored for nouns and adjectives
    std::string get_random_synonym(std::string word, NOUN_ADJECTIVE_VERB form, TENSE tense); // tense is ignored for nouns and adjectives
    std::string substitute_in_prototype(std::string prototype);

};
