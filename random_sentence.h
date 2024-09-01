#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <random>

int random_number(int min, int max) {
    // Random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 eng(rd()); // Seed the generator
    std::uniform_int_distribution<> distr(min, max); // Define the range

    return distr(eng);
}

std::string random_of(const std::vector<std::string> &v) {
    return v.at(random_number(0, v.size()));
}

std::vector<std::string> getlines(std::string filename) {
    std::vector<std::string> words;
    std::ifstream file;
    std::string current_word;
    file.open(filename);

    if (!file) {
        std::cerr << "Error opening " << filename << std::endl;
        return words;
    }

    while (std::getline(file, current_word))
        words.push_back(current_word);
    
    file.close();
    return words;
}

std::string generate_random_sentence() {
    auto adjectives {getlines("./words/adjective.txt")};
    auto nouns {getlines("./words/noun.txt")};
    auto verbs {getlines("./words/verb.txt")};
    auto adverbs {getlines("./words/adverb.txt")};
    auto prepositions {getlines("./words/preposition.txt")};

    std::string sentence {};

    sentence += "The";
    sentence += " " + random_of(adjectives);
    sentence += " " + random_of(nouns);
    sentence += " " + random_of(adverbs);
    sentence += " " + random_of(verbs);
    sentence += " " + random_of(prepositions);
    sentence += " a " + random_of(nouns);

    return sentence;    
}