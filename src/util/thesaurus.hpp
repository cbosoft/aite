#pragma once

#include <string>
#include <map>
#include <list>
#include <array>
#include <regex>

enum WordTense { WT_Past, WT_Present, WT_Future };
enum WordClass { WC_Default, WC_Noun, WC_Adjective, WC_Verb, WC_Adverb };


class Thesaurus {

  private:

    std::regex RE_THESA = std::regex("\\{\\{([\\w\\s]*)(?:,(\\w+))?(?:,(\\w+))?\\}\\}");

    std::map<std::string, std::list<std::string>> nouns;
    std::map<std::string, std::list<std::string>> adjectives;
    std::map<std::string, std::list<std::string>> adverbs;
    std::map<std::string, std::list<std::array<std::string, 3>>> verbs;
    bool loaded;
    void load();

    static std::string get_indefinite_article(std::string word);
    static WordTense str2tense(std::string);
    static WordClass str2class(std::string);
    std::string get_random_verb_synonym(std::string word, WordTense tense);
    std::string get_random_adjective_synonym(std::string word);
    std::string get_random_noun_synonym(std::string word);
    std::string get_random_adverb_synonym(std::string word);
    std::string get_random_default_synonym(std::string word);

  public:

    Thesaurus();
    ~Thesaurus();

    static Thesaurus& getref();
    bool is_loaded();

    std::string get_random_synonym(std::string word, std::string form="default", std::string tense="past"); // tense is ignored for nouns and adjectives
    std::string get_random_synonym(std::string word, WordClass wordclass, WordTense tense=WT_Present); // tense is ignored for nouns and adjectives
    std::string substitute_in_prototype(std::string prototype);

};
