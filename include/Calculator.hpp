#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "MessageBag.hpp"
#include "Tokenizer.hpp"
#include "ParseTree.hpp"
#include "SyntaxAnalyzer.hpp"
#include "TreeOperations.hpp"
#include "ParenthesesCorrection.hpp"
#include "Evaluator.hpp"
#include "Reporter.hpp"
#include "Token.hpp"

namespace gba
{
    class Calculator
    {
        public:
            void calculate(std::string p_exp);
    };

}

#endif