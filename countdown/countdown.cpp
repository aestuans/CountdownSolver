//Solves Countdown numbers game.

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <numeric>
#include <bitset>

int POSSIBLE_OPERATORS_NUM = 7;

using nums_with_expressions = std::vector< std::pair<int, std::vector<int> > >;


std::string binary_operation_presentation(const std::string &lhs, const std::string &op, const std::string &rhs) {
    return lhs + " " + op + " " + rhs;
}

std::pair<int, std::string> operate(int lhs, int rhs, int op) {
    /*
     * Evaluates and returns the value and string representation of a
     * binary operation.
     */
    int res = 0;
    std::string presentation;
    switch(op){
        case -1:
            res = lhs + rhs;
            presentation = binary_operation_presentation(std::to_string(lhs), "+", std::to_string(rhs));
            return std::make_pair(res, presentation);
        case -2:
            if(rhs > lhs)
                return std::make_pair(-1, "");
            res = lhs - rhs;
            presentation = binary_operation_presentation(std::to_string(lhs), "-", std::to_string(rhs));
            return std::make_pair(res, presentation);
        case -3:
            res = lhs * rhs;
            presentation = binary_operation_presentation(std::to_string(lhs), "*", std::to_string(rhs));
            return std::make_pair(res, presentation);
        case -4:
            if(rhs == 0 or lhs % rhs)
                return std::make_pair(-1, "");
            res = lhs / rhs;
            presentation = binary_operation_presentation(std::to_string(lhs), "/", std::to_string(rhs));
            return std::make_pair(res, presentation);
        case -5:
            if(rhs < lhs)
                return std::make_pair(-1, "");
            res = rhs - lhs;
            presentation = binary_operation_presentation(std::to_string(rhs), "-", std::to_string(lhs));
            return std::make_pair(res, presentation);
        case -6:
            if(lhs == 0 or rhs % lhs)
                return std::make_pair(-1, "");
            res = rhs / lhs;
            presentation = binary_operation_presentation(std::to_string(rhs), "/", std::to_string(lhs));
            return std::make_pair(res, presentation);
        case -7:
            return std::make_pair(lhs, std::to_string(lhs));
        default:
            break;
    }
}

std::pair<int, std::string> evaluate_postfix(std::vector<int> expression)
{
    /*
     * Evaluate a postfix expression with negative integers indicating operations:
     * -1: +
     * -2: -
     * -3: *
     * -4: /
     * -5: Ignore lhs.
     * Returns the evaluated value and a string indicating the steps.
     * If an operation is illegal (i.e division by zero, or any operation resulting
     * a non-integer or a negative number) returns (-1, "").
     */
    std::stack<int> evaluation_stack;
    std::string presentation;

    for (int i : expression) {
        if(i > 0){ // A number, not an operator
            evaluation_stack.push(i);
        }
        else{
            int rhs = evaluation_stack.top();
            evaluation_stack.pop();
            int lhs = evaluation_stack.top();
            evaluation_stack.pop();

            std::pair<int, std::string> temp = operate(lhs, rhs, i);
            int res = temp.first;
            presentation += temp.second;

            evaluation_stack.push(res);
            presentation += " = " + std::to_string(res) + "\n";
        }
    }
    return make_pair(evaluation_stack.top(), presentation);
}

int solve_countdown(int target, nums_with_expressions numbers,
                    std::vector<bool> used, std::vector<int> &solution) {
    /*
     * Recursively creates and evaluates all possible expressions from numbers
     * and stores any possible solution to solution.
     * Returns 0 if solution found, 1 otherwise.
     */
    nums_with_expressions _numbers = numbers;
    for(int i = 0; i < numbers.size(); i++) {
        for(int j = i + 1; j < numbers.size(); j++){
            if(used[i] || used[j])
                continue;
            used[j] = true;

            //Shorter names for convenience
            int& numi = numbers[i].first;
            std::vector<int>& numi_expression = numbers[i].second;
            int& numj = numbers[j].first;
            std::vector<int>& numj_expression = numbers[j].second;

            for(int op = -POSSIBLE_OPERATORS_NUM; op < 0; op++) {

                //Result is saved to the lhs operand's place
                //rhs operand is set to used.
                numi = operate(numi, numj, op).first;

                //append numj_expr to numi_expr and add operator
                numi_expression.insert(numi_expression.end(), numj_expression.begin(), numj_expression.end());
                numi_expression.push_back(op);

                if(numi < 0)
                    continue;

                if(numi == target) {
                    solution = numi_expression;
                    return 0;
                }

                if(!solve_countdown(target, numbers, used, solution))
                    return 0;

                numi = _numbers[i].first;
                numi_expression = _numbers[i].second;
            }
            used[j] = false;

        }
    }
    return 1;

}
