#include "Calculator.hpp"

void gba::Calculator::calculate(std::string p_exp)
{
    Tokenizer tokenizer;
    ParseTree *parse_tree;
    SyntaxAnalyzer syntax_analyzer;
    TreeOperations tree_operations;
    Reporter *reporter = new Reporter;

    TreeOperation *parentheses_correction;
    TreeOperation *evaluator;

    p_exp = "(" + p_exp + ")";
    std::vector<Token*> *tokens = tokenizer.tokenize(p_exp);
    
    try
    {
        syntax_analyzer.analyze(tokens);

        parse_tree = new ParseTree();
        parse_tree->create(tokens);

        parentheses_correction = new gba::ParenthesesCorrection;
        evaluator = new gba::Evaluator;

        tree_operations.add(parentheses_correction);
        tree_operations.add(evaluator);

        tree_operations.execute(parse_tree);

        reporter->report(&tree_operations);

        delete parse_tree;
        parse_tree = 0;

        delete parentheses_correction;
        parentheses_correction = 0;

        delete evaluator;
        evaluator = 0;
    }
    catch(std::exception *ex)
    {
        MessageBag reportable;
        std::string error_message = "Syntax Error. Please check your expression.";
        reportable.add(error_message);

        reporter->report(&reportable);
    }
    
    int num_tokens = tokens->size();
    for(int i = 0; i < num_tokens; ++i)
    {
        delete (*tokens)[i];
        (*tokens)[i] = 0;
    }

    delete tokens;
    tokens = 0;

    delete reporter;
    reporter = 0;
}