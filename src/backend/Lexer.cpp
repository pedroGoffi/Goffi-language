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
    NAME
} Token_Type;
typedef struct Token{
    Token_Type	      type;
    Atom	      head;
} Token;

static std::map<std::string, std::vector<Token>> Macros;
static std::map<uint64_t , std::string> Words;
static std::map<std::string, uint64_t> static_addresses;
static int words_count{0};
static int static_mem_capacity{0};
namespace Lexer{
    std::string Token_Type_To_String(Token_Type tk){
	switch(tk){
	    case NAME:
		return "Identifier";
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
    std::string Tokenize(std::string& word, Token_Type &op){
	if( is_number(word)){
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
    void extend_macro(std::vector<Token>& result, Token &it){
      if (Macros.find(it.head.atomName) != Macros.end()){
	for(Token& tk: Macros[it.head.atomName]){
	  if( Macros.find(tk.head.atomName) != Macros.end()){
	    extend_macro(result, tk);
	  }
	  else
	    result.push_back(tk);
	}
      }
      else
	result.push_back(it);
    }
    std::vector<uint64_t> extend_static_definition_body(std::vector<Token> vec){        
        std::vector<uint64_t> mem_vec;
	std::vector<Token>::iterator i = vec.begin();
        while(i != vec.end()){
          if (i->type == BINARY_OPERAND){
            if( i->head.atomName == "+" ){
              auto a = mem_vec.back(); mem_vec.pop_back();auto b = mem_vec.back(); mem_vec.pop_back();
              mem_vec.push_back(a + b);
            }
            else if( i->head.atomName == "-" ){
              auto a = mem_vec.back(); mem_vec.pop_back();auto b = mem_vec.back(); mem_vec.pop_back();
              mem_vec.push_back(b - a);
                                                                                                       
            }
            else if( i->head.atomName == "*" ){
              auto a = mem_vec.back(); mem_vec.pop_back();auto b = mem_vec.back(); mem_vec.pop_back();
              mem_vec.push_back(b*a);
            }
            else if( i->head.atomName == "/" ){
              auto a = mem_vec.back(); mem_vec.pop_back();auto b = mem_vec.back(); mem_vec.pop_back();
              mem_vec.push_back(b / a);
            }
          } 
          
          else if( SV::str_is_num(i->head.atomName) ){
            mem_vec.push_back(std::stoul(i->head.atomName));
          }
          ++i;
	}
        if( mem_vec.size() > 1 ){
          fprintf(stderr, "%lu:%lu:ERROR: after static definition not empty stack of operations\n",
              i->head.atomIndexLine, i->head.atomIndex);
          exit(1);
        }
	return mem_vec;
                                                                                                       
    }
    void lex_line(std::vector<Token> &tokenVector, std::string source, uint64_t line){
        SV::stringView src = SV::SV(source);
        uint64_t  start = src.count;
        uint64_t  pos{};
        Token_Type           actualType;
        std::string          actualWord;
        std::string          token;
        std::vector<Token>   tokenList;
        while(src.count > 1){
            actualWord = SV::separateByTokens(src);
            pos = start - src.count;
            token = Lexer::Tokenize(actualWord, actualType);
	    if(actualWord.length() > 0){
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
	      printf("MACRO NAME: %s\n", m_name.c_str());
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


	  else if ( Macros.find(i->head.atomName) != Macros.end()){
	    for(Token& tk: Macros[i->head.atomName]){
	      extend_macro(result, tk);
	    }
	  }
	  else if ( i->head.atomName == "include" ){
	    ++i;

	    i->head.atomName = i->head.atomName.substr(1, i->head.atomName.length() - 2);
	    std::fstream include_file(i->head.atomName, std::ios::in);
	    std::vector<Token> __include__content = Lexer::lex(include_file);
	    for(auto& content: __include__content){
	      result.push_back(content);
	    }
	  } 
	  else if ( i->head.atomName == "static" ){

	    ++i;
	    if( i->type != NAME ){
	      fprintf(stderr, 
	          "%lu:%lu: ERROR: expected token kind NAME after static keyword but got %s\n",
	          i->head.atomIndexLine, i->head.atomIndex, Token_Type_To_String( i->type ).c_str()
	      );
	      // TODO: report definition of static address
	      // TODO: report redefinition of intrisics
	      // i = mem_name 
	      // sintax: static steq.mem 8 end
	      exit(1);
	    }
	    // 
	    std::string mem_name = i->head.atomName;
	    ++i;
	    std::vector<Token> static_vec;
	    while( i->head.atomName != "end" ){
	      if( Macros.find(i->head.atomName) != Macros.end() ){
		for(Token& tk: Macros[i->head.atomName]){
		  extend_macro(static_vec, tk);
		}
	      }
	      else{
		static_vec.push_back(Token{
		    .type=i->type,
		    .head=i->head
		    });
	      }
	      ++i;
	    }
	    std::vector<uint64_t> static_resb_result = extend_static_definition_body(static_vec);

	    static_addresses[mem_name] = (size_t)static_mem_capacity; // - (size_t)(static_resb_result.back());
	    static_mem_capacity += (int)static_resb_result.back();

	  }
	  else
	  {
	    result.push_back(
		Token{ 
		  .type=i->type,
		  .head=i->head
		}
	    );
	  }
	}
	return result;
    }
}


#endif /* ifndef LEXER */
