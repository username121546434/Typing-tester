#include <iostream>
#include "random_sentence.h"
#include <sstream>
#include <conio.h>
#include <algorithm>
#include <chrono>


const std::string grey = "\33[2m";
const std::string reset = "\33[0m";
const std::string red = "\33[31m";
const std::string green = "\33[92m";

// taken from https://stackoverflow.com/a/15181949/19581763
template<typename First, typename ... T>
bool is_in(First &&first, T && ... t)
{
    return ((first == t) || ...);
}

int main() {
    std::string sentence {generate_random_sentence()};
    std::string currently_typed {};
    size_t correct {}, wrong {};

    std::cout << "\33[2J" << "\33[H";
    std::cout << grey << sentence << reset << std::endl;
    std::cout << "\33[1F";

    char c;
    std::chrono::_V2::system_clock::time_point start_time;
    std::vector<bool> correct_or_wrong {};
    correct_or_wrong.reserve(sentence.size());
    for (size_t curr_char {0}; curr_char < sentence.size(); ++curr_char) {
        c = getch();
        if (curr_char == 0)
            start_time = std::chrono::system_clock::now();
        std::cout << "\33[H";
        if (c == 8) { // backspace character
            curr_char -= 2;
            currently_typed.erase(currently_typed.end() - 14, currently_typed.end());
            if (correct_or_wrong.at(correct_or_wrong.size() - 1))
                --correct;
            else
                --wrong;
            correct_or_wrong.pop_back();
        } else if (sentence[curr_char] == c) {
            currently_typed += green + c;
            ++correct;
            correct_or_wrong.push_back(true);
        } else {
            currently_typed += red + sentence[curr_char];
            ++wrong;
            correct_or_wrong.push_back(false);
        }
        currently_typed += reset;
        std::cout << currently_typed;
        std::for_each(sentence.begin() + curr_char + 1, sentence.end(), [](char x) { std::cout << x; });
        std::cout << "\33[" << curr_char + 2 << "G"; // reset cursor spot
    }
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> duration = end-start_time;
    double cps {sentence.size() / duration.count()};
    double cpm {cps * 60};
    double average_word_length {sentence.size() / 8.0}; // generate_random_sentence always generates 8 words
    double wpm {cpm / average_word_length};
    double accuracy {(static_cast<double>(correct) / sentence.size()) * 100};

    std::cout << "\nYour wpm is " << wpm << std::endl;
    std::cout << "You took " << duration.count() << " seconds" << std::endl;
    std::cout << "Your accuracy is " << accuracy << "%" << std::endl;
}