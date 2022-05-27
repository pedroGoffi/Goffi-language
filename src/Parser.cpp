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
    ID_WHILE,
    ID_IF,
    ID_DO,
    ID_ELIF,
    ID_ELSE,
    ID_END,
    ID_MEM,
    ID_LOAD,
    ID_STORE
}Identifiers;
typedef enum{
    B_PLUS,
    B_MINUS,
    B_CMP_GT,
    B_CMP_LT
} BinOpId;
namespace Parser{
    BinOpId parseBinOp(std::vector<Token>::iterator boid){
        if      (boid->head.atomName == "+")    return B_PLUS;
        else if (boid->head.atomName == "-")    return B_MINUS;
        else if (boid->head.atomName == "<")    return B_CMP_LT;
        else if (boid->head.atomName == ">")    return B_CMP_GT;

        fprintf(stderr, "%lu:%lu: Error: Unreachable binary operand (%s)\n", 
            boid->head.atomIndexLine,
            boid->head.atomIndex,
            boid->head.atomName.c_str()
        );
        exit(1);
    }
    Identifiers parseIdentifier(std::vector<Token>::iterator id){
        if      (id->head.atomName == "dump")  return ID_INTRISIC_DUMP;
        else if (id->head.atomName == "=")     return ID_INTRISIC_EQUALS; 
        else if (id->head.atomName == "dup")   return ID_INTRISIC_DUP;
        else if (id->head.atomName == "store") return ID_STORE;
        else if (id->head.atomName == "load")  return ID_LOAD;
        else if (id->head.atomName == "mem")   return ID_MEM;
        else if (id->head.atomName == "if")    return ID_IF;
        else if (id->head.atomName == "while") return ID_WHILE;
        else if (id->head.atomName == "do")    return ID_DO;
        else if (id->head.atomName == "elif")  return ID_ELIF;
        else if (id->head.atomName == "else")  return ID_ELSE;
        else if (id->head.atomName == "end")   return ID_END;
        


        fprintf(stderr, "%lu:%lu: Error: Unreachable identifier at `%s` in the Parsing stage.\n", 
                id->head.atomIndexLine,
                id->head.atomIndex,
                id->head.atomName.c_str()
        );
        exit(1);
    }
    std::vector<VR> parse(std::vector<Token> tokens){
        std::vector<Token>::iterator Node = tokens.begin();
        std::vector<VR> output;
        while( Node != tokens.end()){
            switch(Node->type){ 
                case STRING:{                                        
                    Identifiers id = Parser::parseIdentifier(Node);
                    switch(id){
                        case ID_STORE:{
                            ++Node;
                            uint64_t storeType;
                            try{
                                storeType = stoi64(Node->head.atomName);
                            } catch(std::invalid_argument& err){
                                fprintf(stderr, "%lu:%lu: Error: `store` operand accepts the next value as the store capacity in bytes\n",
                                    Node->head.atomIndexLine,
                                    Node->head.atomIndex
                                );
                                fprintf(stderr, "   Note: Excpected `size_t` but receive: `%s`\n",
                                        typeid(Node->head.atomName).name());
                                exit(1);
                            }
                            switch(storeType){
                                case (8):
                                    output.push_back(VR{OP_STOREBYTE,   8});
                                    break;
                                default:
                                    fprintf(stderr, "%lu:%lu: Error: `store` op does not support the given type\n",
                                        Node->head.atomIndexLine,
                                        Node->head.atomIndex
                                    );
                                    fprintf(stderr, "   Note: For now `store` only supports store8\n");
                                    exit(1);
                                    break;
                            }
                            ++Node;
                            break;
                        }
                        case ID_LOAD:{
                            ++Node;
                            uint64_t loadType;
                            try{
                                loadType = stoi64(Node->head.atomName);
                            }
                            catch(std::invalid_argument& err){
                                fprintf(stderr, "%lu:%lu: Error: `load` operand accepts the next value as the load type\n",
                                    Node->head.atomIndexLine,
                                    Node->head.atomIndex
                                );
                                fprintf(stderr, "   Note: Excpected: `size_t` but receive: `%s`\n",
                                        typeid(Node->head.atomName).name());
                                exit(1);
                            }
                            switch(loadType){
                                case (8):{
                                    output.push_back(VR{OP_LOADBYTE,    8});                                    
                                    break;
                                }    
                                default:{
                                    fprintf(stderr, "%lu:%lu: Error: `load` op does not suport the given type\n",
                                        Node->head.atomIndexLine,
                                        Node->head.atomIndex
                                    );
                                    fprintf(stderr, "   Note: For now only suport load8\n");
                                    exit(1);
                                    break;
                                }
                                break;
                            }
                        case ID_MEM:
                          output.push_back(VR{OP_MEM,   0});
                          ++Node;
                          break;
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
                            printf("`elif` Not implemented yet\n");
                            fprintf(stderr, "%lu:%lu: Error: Internal keyword `elif` not implemented yet\n",
                                Node->head.atomIndexLine,
                                Node->head.atomIndex
                            );
                            exit(1);
                            ++Node;
                            break;
                        case ID_ELSE:
                            output.push_back(VR{OP_ELSE,    static_cast<uint64_t>(Node->head.atomLinkedIndex)});
                            ++Node;
                            break;
                        case ID_IF:
                            output.push_back(VR{OP_IF,  0});
                            ++Node;
                            break;
                        case ID_INTRISIC_DUMP:
                            output.push_back(VR{DUMP, 0});
                            ++Node;
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
                    switch(Parser::parseBinOp(Node)){
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
