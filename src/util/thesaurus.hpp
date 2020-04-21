#pragma once

#include <string>

enum TENSE { PAST_TENSE, PRESENT_TENSE, FUTURE_TENSE };
enum NOUN_ADJECTIVE_VERB {NOUN, ADJECTIVE, VERB};

TENSE str2tense(std::string);
NOUN_ADJECTIVE_VERB str2type(std::string);

std::string get_indefinite_article(std::string word);

std::string get_random_synonym(std::string word, NOUN_ADJECTIVE_VERB form = NOUN, TENSE tense = PAST_TENSE); // tense is ignored for nouns and adjectives
std::string substitute_in_prototype(std::string prototype);
