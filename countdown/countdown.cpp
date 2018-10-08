//Solves Countdown numbers game.

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <tuple>
#include <numeric>

int POSSIBLE_OPERATORS_NUM = 5;

std::string binary_operation_presentation(const std::string &lhs, const std::string &op, const std::string &rhs) {
    return lhs + " " + op + " " + rhs;
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

            int res = -1;

            switch(i){
                case -1:
                    res = lhs + rhs;
                    presentation += binary_operation_presentation(std::to_string(lhs), "+", std::to_string(rhs));
                    break;
                case -2:
                    if(rhs > lhs)
                        return std::make_pair(-1, "");
                    res = lhs - rhs;
                    presentation += binary_operation_presentation(std::to_string(lhs), "-", std::to_string(rhs));
                    break;
                case -3:
                    res = lhs * rhs;
                    presentation += binary_operation_presentation(std::to_string(lhs), "*", std::to_string(rhs));
                    break;
                case -4:
                    if(rhs == 0 or lhs % rhs)
                        return std::make_pair(-1, "");
                    res = lhs / rhs;
                    presentation += binary_operation_presentation(std::to_string(lhs), "/", std::to_string(rhs));
                    break;
                case -5:
                    res = lhs;
                    break;
                default:
                    break;
            }
            evaluation_stack.push(res);
            presentation += " = " + std::to_string(res) + "\n";
        }
    }
    return make_pair(evaluation_stack.top(), presentation);
}

int make_operations(int n, int target, std::vector<int> ops,
                    std::vector<int> ops_distribution, std::vector<int> nums) {
    /*
     * Recursively makes all possible operations to fill ops_distribution, constructs
     * the expression and compares it with target.
     * Returns 0 if expression evaluated in target is found.
     * Returns 1 otherwise.
     */
    if(ops.size() < n) {
        for(int i = -POSSIBLE_OPERATORS_NUM; i < 0; i++) {
            ops.push_back(i);
            if(!make_operations(n, target, ops, ops_distribution, nums))
                return 0;
            ops.pop_back();
        }
    }
    else {
        std::vector<int> temp;
        temp.push_back(nums[0]);
        temp.push_back(nums[1]);

        int k = 0;
        for(int i = 0; i < 5; i++){
            for(int l = 0; l < ops_distribution[i]; l++){
                temp.push_back(ops[k]);
                k++;
            }
            if(i < 4)
                temp.push_back(nums[i + 2]);
        }

        int res = evaluate_postfix(temp).first;
        if(res == target){
            for (int i : temp)
                std::cout << i << " ";
            std::cout << std::endl;
            std::cout << evaluate_postfix(temp).second;
            return 0;
        }

    }
    return 1;
}

int make_expressions(int target, std::vector<int> ops_distribution, std::vector<int> &numbers) {
    /*
     * Recursively makes all possible operators distribution and calls make_operations
     * To fill the distribution and evaluate.
     * Returns 0 if target found, 1 otherwise.
     */
    auto ops_num = static_cast<int>(numbers.size() - 1);
    auto ops_size = static_cast<int>(ops_distribution.size());
    if(ops_size < ops_num - 1) {
        int sum = accumulate(ops_distribution.begin(), ops_distribution.end(), 0);

        // Number of spots left for operators
        int remaining_spots = (ops_size == 0) ? 2 : std::min(ops_size, ops_size - sum) + 2;

        for(int x = 0; x < remaining_spots; x++) {
            ops_distribution.push_back(x);
            if(!make_expressions(target, ops_distribution, numbers))
                return 0;
            ops_distribution.pop_back();
        }
    }
    else {
        int sum = accumulate(ops_distribution.begin(), ops_distribution.end(), 0);
        ops_distribution.push_back(ops_num - sum);

        if(!make_operations(ops_num, target, std::vector<int>(), ops_distribution, numbers))
            return 0;
    }
    return 1;
}
