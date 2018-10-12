#include <string>
#include <vector>

#ifndef COUNTDOWN_H
#define COUNTDOWN_H

using nums_with_expressions = std::vector< std::pair<int, std::vector<int> > >;

class Countdown {
public:
    const int POSSIBLE_OPERATORS_NUM = 7;

    Countdown(int , const std::vector<int>&);
    int solve(std::vector<int> &);
    static std::pair<int, std::string> evaluate_postfix(std::vector<int>);

private:
    int target;
    nums_with_expressions numbers;
    int _solve(std::vector<bool>, std::vector<int> &);
    static std::string binary_operation_presentation(const std::string&, const std::string&, const std::string&);
    static std::pair<int, std::string> operate(int, int, int);
};

#endif //COUNTDOWN_H
