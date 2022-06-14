/*  NOTE:
 *      A tokenList is a vector of Atoms
 *      tokenList ==>  vec 
 *                      |   
 *                    Atom
 *                  /   |  \
 *              name  index type
 */


#ifndef LEXER
#define LEXER value

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include <map>
#include "./Core/Instructions.cpp"
#include "../frontend/StringView.cpp"

/*  NOTE:
 *      A atom is a identifier for each word
 *      name is the name itself
 *      type is str/int types likely
 *      and index is the positio in the text
 */

class Atom{
public:
    std::string atomName;
    std::string atomType;
    uint64_t      atomIndex;
    uint64_t      atomIndexLine;
    uint64_t      atomLinkedIndex;
};
typedef enum Token_Type{
    NUMBER,
    BINARY_OPERAND,
    STRING,
    NAME
} Token_Type;
typedef struct Token{
    Token_Type       type;
    Atom             head;
} Token;

static std::map<std::string, std::vector<Token>> Macros;
namespace Lexer{
    std::string Token_Type_To_String(Token_Type tk){
	switch(tk){
	    case NAME:
		return "Identifier";
		break;
	    case STRING: 
		return "String";
		break;
	    case BINARY_OPERAND: 
		return "BINARY_OPERAND";
		break;
	    case NUMBER:
		return "Number";
		break;
	    default:
		assert(false && "Unreachable");
	}
    }
    std::string Tokenize(std::string word, Token_Type &op){
	if (word == "\""){
	    std::cout << "OK\n";
	    exit(1);
	} else if( is_number(word)){
            op = NUMBER;
            return ("NUMERICAL_TYPE");
        } else if (word == "+"){
            op = BINARY_OPERAND;
            return ("OP_PLUS");
        } else if (word == "-"){
            op = BINARY_OPERAND;
            return ("OP_MINUS");
        } else if (word == "*"){
	    op = BINARY_OPERAND;
	    return ("OP_MULT");
	} else if (word == "<"){
            op = BINARY_OPERAND;
            return ("OP_CMP_LT");
        } else if (word == ">"){
            op = BINARY_OPERAND;
            return ("OP_CMP_GT");
        } else{
            op = NAME;
            return ("NAME_TYPE");
        }
    }
    void lex_line(std::vector<Token> &tokenVector, std::string source, uint64_t line){
        SV::stringView src = SV::SV(source);
        uint64_t  start = src.count;
        uint64_t  pos{};
        Token_Type           actualType;
        std::string          actualWord;
        std::string          token;
        std::vector<Token>   tokenList;
        while(src.count > src.minimunValue){
            actualWord = SV::separateByTokens(src);
	    if (actualWord.length() ==  0 ) continue;
            pos = start - src.count;
            token = Lexer::Tokenize(actualWord, actualType);
	    {
		tokenList.push_back(
            	    Token{
            	        .type = actualType,
            	        .head = Atom{
            	            actualWord, 
            	            token, 
            	            pos - actualWord.length(),
            	            line,
            	            0
            	        },
            	    }
            	);
	    }
        }
        for(auto& token_after_lex : tokenList)
            tokenVector.push_back(token_after_lex);
    }
    auto lex(std::fstream& file) -> std::vector<Token>
    {
	std::vector<Token> pre_result;
	std::string line_string;
	uint64_t    line_count = 0;
	while( getline(file, line_string)){
	    Lexer::lex_line(pre_result, line_string, line_count);
	    ++line_count;
	}
	file.close();
	std::vector<Token> result;
	for(auto i = pre_result.begin(); i != pre_result.end(); ++i){
	  if( i->head.atomName == "define" ){
	    ++i;
	    std::string m_name = i->head.atomName;
	    if( Macros.find(m_name) != Macros.end()){
	      printf("%lu:%lu: ERROR: Redefinition of macro\n", 
	          i->head.atomIndexLine, 
	          i->head.atomIndex);
	      printf("	NOTE: previous declared here %lu:%lu\n", 
	          Macros[m_name].begin()->head.atomIndexLine, 
	          Macros[m_name].begin()->head.atomIndex);
	      exit(1);
	    }
	    ++i;
	    if( i->head.atomName != "as" ){
	      printf("%lu:%lu: ERROR: Macro definition must follow the keyword `as`\nExample: define <macro-name> as <macro-body> end\n", i->head.atomIndexLine, i->head.atomIndex);
	      exit(1);
	    }
	    ++i;
	    std::vector<Token> m__body;
	    uint64_t do_counts{0};
	    while(i->head.atomName != "end" || do_counts > 0){ 
	      if (i->head.atomName == "do"){
	        ++do_counts;
	      } else if ( i->head.atomName == "end" ){
	        --do_counts;
	      }
	      m__body.push_back(
	            Token{
	              .type=i->type,
	              .head=i->head
	            }
	          );
	      ++i; 
	    }
	    Macros[m_name] = m__body;
	  }
	  else if (i->head.atomName != "define")
	  {
	    result.push_back(
		Token{ 
		  .type=i->type,
		  .head=i->head
		}
	    );
	  }
	}


	for(auto& x: result){
	  std::cout
	    << x.head.atomName 
	    << "\t"
	    << x.head.atomIndexLine << "  <- line\t"
	    << x.head.atomIndex	    << "  <- col\t"
	    << " after macro-parsing\n";
	}
	return result;
    }
}


#endif /* ifndef LEXER */
