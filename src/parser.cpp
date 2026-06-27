// parser.cpp
#include "parser.hpp"
#include "errors.hpp"

#include <cstddef>
#include <string>

// Makes this function private.
namespace {

Expr parse_one(const std::vector<std::string>& tokens, std::size_t& position) {
    if (position >= tokens.size()) {
        throw SchemeSyntaxError("Unexpected end of input");
    }

    const std::string& token = tokens[position++];

    if (token == "(") {
        Expr::List expressions;

        while (true) {
            if (position >= tokens.size()) {
                throw SchemeSyntaxError("Missing ')'");
            }

            if (tokens[position] == ")") {
                position++;
                break;
            }

            expressions.push_back(parse_one(tokens, position));
        }

        return Expr {std::move(expressions)};
    }

    if (token == ")") {
        throw SchemeSyntaxError("Unexpected ')'");
    }

    try {
        std::size_t parsed_characters = 0;
        const double number = std::stod(token, &parsed_characters);

        if (parsed_characters == token.size()) {
            return Expr {number};
        }
    } catch (const std::invalid_argument&) {
        // Token not a number, treat it as a symbol.
    } catch (const std::out_of_range&) {
        throw SchemeSyntaxError("Number is out of range: " + token);
    }

    return Expr {token};
}

} // namespace

Expr parse(const std::vector<std::string>& tokens) {
    std::size_t position = 0;
    Expr result = parse_one(tokens, position);

    if (position != tokens.size()) {
        throw SchemeSyntaxError("Unexpected extra tokens");
    }

    return result;
}