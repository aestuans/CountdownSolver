#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "countdown/countdown.cpp"

void prompt_usage() {
    std::cout << "Usage: countdown <number_of_numbers> <n1> <n2> ... <nn> <target>" << std::endl;
}

int main(int argc, char** argv)
{
    std::string x = argv[1];
    int number_of_numbers, target;
    try {
        number_of_numbers = stoi(x);
    }
    catch(std::invalid_argument& e) {
        prompt_usage();
        return 0;
    }

    if(argc != number_of_numbers + 3){
        prompt_usage();
        return 0;
    }

    std::vector<int> nums;
    for(int i = 2; i < argc - 1; i++) {
        try{
            nums.push_back(std::stoi((std::string)argv[i]));
        }
        catch(std::invalid_argument& e) {
            prompt_usage();
            return 0;
        }
    }

    try{
        target = stoi((std::string)argv[argc - 1]);
    }
    catch(std::invalid_argument& e) {
        prompt_usage();
        return 0;
    }

    nums_with_expressions numbers;
    for(int num : nums)
        numbers.push_back(std::make_pair(num, std::vector<int>(1, num) ));

    std::vector<int> solution;
    solve_countdown(target, numbers, std::vector<bool>(static_cast<size_t>(number_of_numbers), false), solution);

    std::cout << std::endl << evaluate_postfix(solution).second << std::endl;

    return 0;
}