#ifndef PARSER
#define PARSER value
#include <iostream>
#include <vector>
#include "./Lexer.cpp"
#include <typeinfo>

#define stoi64(x) static_cast<uint64_t>(std::stoi(x))
typedef enum{
    ID_INTRISIC_DUMP,
    ID_INTRISIC_DUP,
    ID_INTRISIC_EQUALS,
    ID_EXIT,
    ID_WHILE,
    ID_IF,
    ID_DO,
    ID_ELIF,
    ID_ELSE,
    ID_END
}Identifiers;
typedef enum{
    B_PLUS,
    B_MINUS,
    B_CMP_GT,
    B_CMP_LT
} BinOpId;
namespace Parser{
    BinOpId parseBinOp(std::string boi){
        if      (boi == "+")    return B_PLUS;
        else if (boi == "-")    return B_MINUS;
        else if (boi == "<")    return B_CMP_LT;
        else if (boi == ">")    return B_CMP_GT;

        fprintf(stderr, "Error: Unreachable binary operand (%s)\n", boi.c_str());
        exit(1);
    }
    Identifiers parseIdentifier(std::string id){
        if      (id == "dump")  return ID_INTRISIC_DUMP;
        else if (id == "=")     return ID_INTRISIC_EQUALS; 
        else if (id == "dup")   return ID_INTRISIC_DUP;

       
       

        else if (id == "exit")  return ID_EXIT;

        else if (id == "if")    return ID_IF;
        else if (id == "while") return ID_WHILE;
        else if (id == "do")    return ID_DO;
        else if (id == "elif")  return ID_ELIF;
        else if (id == "else")  return ID_ELSE;
        else if (id == "end")   return ID_END;
        


        fprintf(stderr, "Error: Unreachable identifier at `%s` in the Parsing stage.\n", id.c_str());
        exit(1);
    }
    std::vector<VR> parse(std::vector<Token> tokens){
        std::vector<Token>::iterator Node = tokens.begin();
        std::vector<VR> output;
        while( Node != tokens.end()){

            switch(Node->type){
                
                case STRING_LITERAL:{                                        
                    Identifiers id = Parser::parseIdentifier(Node->head.atomName);
                    switch(id){
                        case ID_WHILE:
                            output.push_back(VR{WHILE,  0});
                            ++Node;
                            break;
                        case ID_INTRISIC_DUP:
                            output.push_back(VR{DUP, 0});
                            ++Node;
                            break;
                        case ID_END:
                            output.push_back(VR{OP_END, static_cast<uint64_t>(Node->head.atomLinkedIndex)});
                            ++Node;
                            break;
                        case ID_DO:
                            output.push_back(VR{OP_DO,  static_cast<uint64_t>(Node->head.atomLinkedIndex)});
                            ++Node;
                            break;
                        case ID_ELIF:
                            fprintf(stdout, "[`ELIF` PARSER - LINKED INDEX] : %lu", Node->head.atomLinkedIndex);
                            printf("`elif` Not implemented yet\n");
                            fprintf(stderr, "Error: Internal keyword `elif` not implemented yet\n");
                            exit(1);
                            ++Node;
                            break;
                        case ID_ELSE:
                            output.push_back(VR{OP_ELSE,    static_cast<uint64_t>(Node->head.atomLinkedIndex)});
                            ++Node;
                            break;
                        case ID_IF:
                            ++Node;
                            break;
                        case ID_INTRISIC_DUMP:
                            output.push_back(VR{DUMP, 0});
                            ++Node;
                            break;
                        case ID_EXIT:{
                            Node += 2; 
                            try{
                                output.push_back(VR{EXIT, stoi64(Node->head.atomName)});
                            }catch(...){
                                fprintf(
                                    stderr, 
                                    "Error: `exit` expects (uint64_t) but receive (%s)\n"
                                    "   Column: %zu\n",
                                    typeid(Node->head.atomName).name(),
                                    Node->head.atomIndex
                                );
                            }
                            Node += 2; 
                            break;
                        }
                        case ID_INTRISIC_EQUALS: 
                            output.push_back(VR{OP_EQUALS,  0});
                            ++Node;
                            break;
                        
                    }
                    break;
                }
                case NUMBER:
                    output.push_back(VR{PUSH_INT, stoi64(Node->head.atomName)});
                    ++Node;
                    break;
                case BINARY_OPERAND:
                    switch(Parser::parseBinOp(Node->head.atomName)){
                        case B_PLUS:
                            output.push_back(VR{OP_PLUS,    0});
                            break;
                        case B_MINUS:
                            output.push_back(VR{OP_MINUS,   0});
                            break;
                        case B_CMP_LT:
                            output.push_back(VR{OP_LTHAN,   0});
                            break;
                        case B_CMP_GT:
                            output.push_back(VR{OP_GTHAN,   0});
                            break;
                    }
                    ++Node;
                    break;
            }
        }
        return output;
    }
}
#endif /* ifndef PARSER */
