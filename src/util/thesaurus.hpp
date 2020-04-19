#pragma once

#include <string>

enum TENSE { PAST_TENSE, PRESENT_TENSE, FUTURE_TENSE };
enum NOUN_ADJECTIVE_VERB {NOUN, ADJECTIVE, VERB};

std::string get_random_synonym(std::string word, NOUN_ADJECTIVE_VERB form = NOUN, TENSE tense = PAST_TENSE); // tense is ignored for nouns and adjectives
