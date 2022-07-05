// TODO:
//  provide location
//  make pure functions to help report errors

#ifndef TypeChecker
#define TypeChecker
#include <array>
#include <vector>
#include <algorithm>
#include "./Core/Instructions.cpp"
#include "./Lexer.cpp"
#define __token &ins[i].second

static std::string        proc_ctx;
static std::vector<Token> proc_args;
static std::vector<Token> proc_ret;

enum Types{
  INT,
  PTR,
  BOOL
};
std::vector<Types> string_to_type(std::string pname){
  std::vector<Types> ret;
  if(pname == "int"){
    ret.push_back(Types::INT);
  }
  else if (pname == "str"){
    ret.push_back(Types::INT);
    ret.push_back(Types::PTR);
  }
  else if (pname == "bool"){
    ret.push_back(Types::BOOL);
  }
  else if (pname == "ptr"){
    ret.push_back(Types::PTR);
  }    
  else if (pname == "void"){
  }
  else{
    assert(false);
  }
    return ret;
}

std::string get_loc_from_Token(Token *token){
  return std::to_string(token->head.atomIndexLine) 
    + ":" 
    + std::to_string(token->head.atomIndex);
}
void compiler_note(Token *token, std::string note){
  printf("OBS: location is based on macros location, please update the lexer\n");
  printf(
	 "%s\n",
	 (get_loc_from_Token(token)
	  + ": NOTE: "
	  + note).c_str()
	 );
}
void compiler_error(Token *token, std::string note){
  printf("OBS: location is based on macros location, please update the lexer\n");
  printf(
	 "%s\n",
	 (get_loc_from_Token(token)
	  + ": ERROR: "
	  + note).c_str()
	 );
  exit(1);
}
void compiler_not_enough_arguments(Token *token, std::string note){
  compiler_error(token, "not enough arguments: " + note);
  exit(1);
}
std::string Types_to_human_readable(Types type){
  switch(type){
  case Types::INT:
    return "integer";
  case Types::PTR:
    return "pointer";
  case Types::BOOL:
    return "boolean";
  }
  assert(false && "unreachable");
}
void compiler_expected_but_got(Token *token, Types expected, Types got){
  compiler_error(
		 token, 
		 "expected `" 
		 + Types_to_human_readable(expected)
		 + "` but got `"
		 + Types_to_human_readable(got)
		 + "`\n"
		 );  
  exit(1);
}
void dump_stack(std::vector<Types> *stack){
  printf("stack : (");
  for(auto& type: *stack){
    printf("<%s>, ",
	   Types_to_human_readable(type).c_str()
	   );
  }
  printf(")\n");
}
void type_checking_walk(std::vector<std::pair<VR, Token>> ins){
  // TODO: type cheking doesnt track the current location

  std::vector<Types>		    stack;
  std::vector<std::vector<Types>>   stack_snapshot;
  for(uint64_t i =  0; i < ins.size(); ++i){
    switch(ins[i].first.op){
    case CAST:
      {
	if( stack.size() < 1 ){
	  compiler_not_enough_arguments(__token, "for casting");
	}

	stack.pop_back();
	if( ins[i].first.op_string	== "cast(int)"	) stack.push_back(Types::INT);
	else if( ins[i].first.op_string == "cast(ptr)"	) stack.push_back(Types::PTR);
	else if( ins[i].first.op_string == "cast(bool)" ) stack.push_back(Types::BOOL);
	break;
      }
    case PUSH_INT:
      stack.push_back(Types::INT);
      break;
    case OP_PLUS:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for the PLUS intrisic");
	}
	auto a = stack.back();
	if( a != Types::INT ){
	  compiler_expected_but_got(__token, Types::INT, a);
	}
	stack.pop_back();
	auto b = stack.back();
	stack.pop_back();
	if (a == Types::INT && b == Types::INT)
	  stack.push_back(Types::INT);
	else if( a == Types::INT && b == Types::PTR){
	  stack.push_back(Types::PTR);
	}
	else if( a == Types::PTR && b == Types::INT){
	  stack.push_back(Types::PTR);
	}
	else{
	  compiler_error(__token, 
			 "expected `INT` and `INT` or `PTR` and `INT` on the top of the stack but got"
			 + Types_to_human_readable(a)
			 + ", "
			 + Types_to_human_readable(b)
			 +"\n"
			 );
	}
	break;
      } 
    case DUMP:
      {
	if(stack.size() < 1){
	  compiler_not_enough_arguments(__token, "for the DUMP operation");
	}
	auto a = stack.back();
	if( a != Types::INT ){
	  compiler_note(__token, "wrong data-type for DUMP operation");
	  compiler_expected_but_got(__token, Types::INT, a);
	}
	stack.pop_back();
	break;
      }
    case DROP:
      {
	if( stack.size() < 1 ){
	  compiler_note(__token, "DROP operation can works with any data type");
	  compiler_not_enough_arguments(__token, "for DROP operation");
	}
	stack.pop_back();
	break;
      }
    case PUSH_STR: 
      {
	stack.push_back(Types::INT);
	stack.push_back(Types::PTR);
        break;
      }
    case OP_MINUS:
      {
	if(stack.size() < 2){	  
	  compiler_not_enough_arguments(__token, "for MINUS operation");
	  exit(1);
	}
	auto a = stack.back();
	stack.pop_back();
	auto b = stack.back();
	stack.pop_back();

	if( a == b && a == Types::INT )
	  stack.push_back(Types::INT);
	else if ((a == Types::INT && b == Types::PTR)
		 || (b == Types::PTR && a == Types::INT))
	  {
	    stack.push_back(Types::PTR);
	  }
	break;
      }
    case OP_DIVMOD:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for divmod operation");
	}
	if( stack.back() != Types::INT ){
	  compiler_expected_but_got(__token, Types::INT, stack.back());
	}
	stack.pop_back();
	if( stack.back() != Types::INT ){
	  compiler_expected_but_got(__token, Types::INT, stack.back());
	}
	stack.pop_back();
	stack.push_back(Types::INT);
	stack.push_back(Types::INT);
	break;
      }
    case OP_IDIVMOD:
      {
	compiler_error(__token, "IDIVMOD is not implemented yet");
	break;
      }
    case OP_EQUALS:
      {
	if(stack.size() < 2){
	  compiler_not_enough_arguments(__token, "for EQUALS intrisic");
	}
	auto a = stack.back(); stack.pop_back();
	auto b = stack.back(); stack.pop_back();
	if( a == b && a == Types::INT ){
	  stack.push_back(Types::BOOL);
	}
	else{
	  compiler_expected_but_got(__token, Types::INT, b);
	}


	break;
      }
    case OP_NOT_EQUALS:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for NOT EQUALS intrisic");
	}
	auto a = stack.back();
	stack.pop_back();
	auto b = stack.back();
	stack.pop_back();
	if( a == b && a == Types::INT ){
	  stack.push_back(Types::BOOL);
	}
	else{
	  compiler_expected_but_got(__token, Types::BOOL, a);
	}


	break;
      }
    case OP_MULT:
      {
        if(stack.size() < 2){	  
	  compiler_not_enough_arguments(__token, "for MINUS intrisic\n");
        }
        auto a = stack.back();
        if( a != Types::INT ){
	  compiler_expected_but_got(__token, Types::INT, a);
        }
        stack.pop_back();
        a = stack.back();
        stack.pop_back();
        stack.push_back(Types::INT);
        break;
      }



    case OP_GTHAN:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for GTHAN `>` intrisic");
	  exit(1);
	}
	auto a_t = stack.back();
	stack.pop_back();
	auto b_t = stack.back();
	stack.pop_back();
	if(a_t == Types::INT && b_t == Types::INT)
	  stack.push_back(Types::BOOL);
	else if (a_t == Types::PTR && b_t == Types::PTR)
	  stack.push_back(Types::BOOL);
	else{
	  compiler_error(__token, 
			 "`>` intrisic only works between "
			 + Types_to_human_readable(Types::INT)
			 + " and with "
			 + Types_to_human_readable(Types::INT)
			 + " with "
			 + Types_to_human_readable(Types::PTR)
			 );
	}
	break;
      }
    case OP_LTHAN:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for LTHAN `<` intrisic");
	}
	auto a_t = stack.back();
	stack.pop_back();
	auto b_t = stack.back();
	stack.pop_back();
	if(a_t == Types::INT && b_t == Types::INT)
	  stack.push_back(Types::BOOL);
	else if (a_t == Types::PTR && b_t == Types::PTR)
	  stack.push_back(Types::BOOL);
	else{
	  compiler_error(__token, 
			 "`<` intrisic only works between "
			 + Types_to_human_readable(Types::INT)
			 + " and with "
			 + Types_to_human_readable(Types::INT)
			 + " with "
			 + Types_to_human_readable(Types::PTR)
			 );
	}
	break;
      }
    case OP_MEM:
      {
	stack.push_back(Types::PTR);
	break;
      }
    case ARGC:
      {
	stack.push_back(Types::PTR);
	break;
      }
    case ARGV:
      {
	stack.push_back(Types::PTR);
	break;
      }
    case DUP:
      {
	if( stack.size() < 1){
	  compiler_not_enough_arguments(__token, "for DUP intrisic\n");
	  exit(1);
	}
	auto a =  stack.back();
	stack.push_back(a);
	break;
      }
    case OVER:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for OVER intrisic\n");
	  exit(1);
	}

	auto a = stack.back(); stack.pop_back();
	auto b = stack.back(); stack.pop_back();
	stack.push_back(b);
	stack.push_back(a);
	stack.push_back(b);
	break;
      }
    case SWAP:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for SWAP intrisic\n");
	}

	// a b
	// b a
	auto b = stack.back(); stack.pop_back();
	auto a = stack.back(); stack.pop_back();

	stack.push_back(b);
	stack.push_back(a);
	break;
      }

    case ROT:
      {
	if( stack.size() < 3 ){
	  compiler_not_enough_arguments(__token, "for ROT intrisic");
	  exit(1);
	}
	// b c a 
	// b c a

	auto a = stack.back(); stack.pop_back();
	auto b = stack.back(); stack.pop_back();
	auto c = stack.back(); stack.pop_back();

	stack.push_back(b);
	stack.push_back(c);
	stack.push_back(a);
	
	break;
      }
    case PUSH_PTR:
      {
	stack.push_back(Types::PTR);
	break;
      }
      ////  -----
    case SHIFT_LEFT:
      {
	if( stack.size() < 1 ){
	  compiler_not_enough_arguments(__token, "for shl `<<` intrisic");
	  exit(1);
	}
	stack.pop_back();
	break;
      }
    case SHIFT_RIGHT:
      {
	if( stack.size() < 1 ){
	  compiler_not_enough_arguments(__token, "for shr `>>` operation\n");
	}
	stack.pop_back();
	break;
      }
    case AND:
    case OR:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(__token, "for logical intrisic");
	}
	if( stack.back() != Types::BOOL ){
	  compiler_expected_but_got(__token, Types::BOOL, stack.back());
	}
	stack.pop_back();
	if( stack.back() != Types::BOOL ){
	  compiler_expected_but_got(__token, Types::BOOL, stack.back());
	}

	stack.pop_back(); 
	stack.push_back(Types::BOOL);
	break;
      }

    case NOT:
      {
	if( stack.size() < 1 ){
	  compiler_not_enough_arguments(__token, "for OR operation");
	}
	if( stack.back() != Types::BOOL ){
	  compiler_expected_but_got(__token, Types::BOOL, stack.back());
	}
	break;
      }
      //// -----


    case OP_IF:
      {
	stack_snapshot.push_back(stack);
	break;
      }
    case OP_ELSE:
      {
	stack_snapshot.pop_back();
	stack_snapshot.push_back(stack);
	break;
      }
    case OP_DO:
      {
	if(stack.size() < 1){
	  compiler_not_enough_arguments(__token, "for DO operation");
	}
	auto tmp = stack.back();
	if( tmp != Types::BOOL ){
	  compiler_expected_but_got(__token, Types::BOOL, tmp);
	}
	stack.pop_back();
	break;
      }
    case OP_WHILE:
      {
	// Do expects a boolean on the top of the stack
	stack_snapshot.push_back(stack);
	break;
      }
    case OP_END:
      {
	if(stack != stack_snapshot.back() ){
	  printf("expected\t");
	  dump_stack(&stack_snapshot.back());
	  printf("got\t\t");
	  dump_stack(&stack);
	  compiler_error(__token, "blocks are not allowed to change the outside stack");
	}
	stack = stack_snapshot.back();
	stack_snapshot.pop_back();
	break;
      }


    case OP_SYSCALL:
      {
	if (stack.size() < ins[i].first.operand + 1){
	  compiler_not_enough_arguments(__token, "for the syscall\n");
	}
	for(uint64_t iter = 0; iter <= ins[i].first.operand; ++iter){
	  stack.pop_back();
	}
	stack.push_back(Types::INT);
	break;
      }


    case OP_LOADBYTE:
      {
	if( stack.size() < 1 ){
	  compiler_not_enough_arguments(__token, "for loadbyte intrisic");
	}
	if( stack.back() != Types::PTR ){
	  compiler_expected_but_got(__token, Types::PTR, stack.back());
	}
	stack.pop_back();
	stack.push_back(Types::INT);
	break;
      }
    case OP_STOREBYTE:
      {
	if( stack.size() < 2 ){
	  compiler_not_enough_arguments(
					__token, 
					"expected at least 2 elements on the top of the stack "
					+ Types_to_human_readable(Types::PTR)
					+ " followed by a "
					+ Types_to_human_readable(Types::INT)
					);
	}
	auto a = stack.back(); stack.pop_back();
	if( a != Types::INT ){
	  compiler_note(
			__token, 
			"Trying to use loadbyte? hint, use like this: "
			+ Types_to_human_readable(Types::PTR)
			+ " "
			+ Types_to_human_readable(Types::INT)
			+ " store-byte"
			);
	  compiler_expected_but_got(__token, Types::INT, a);
	}
	auto b = stack.back(); stack.pop_back();
	if( b != Types::PTR ){
	  compiler_expected_but_got(__token, Types::PTR, b);
	}
	break;
      }
    case PUSH_LOCAL_MEM:
      stack.push_back(Types::PTR);
      break;
    case ALLOC_LOCAL_MEM:
      // TODO
    case PROC_LEAVE:
      // TODO
    case PROC_SKIP:
      // TODO
      break;
    case CALL_PROC:
      break;
    case PROC_ENTRY:

      break;
    case PROC_RETURN:
      break;
    case NUM_OF_OPERANDS:     
    default:
      compiler_error(__token, "OP_TYPE not handled in type checking phase, please update the TypeCheck.cpp");
    }
  }
  if( stack.size() != 0 ){
    printf("ERROR: Unhandled data on the stack\n");
    exit(1);
  }
  if( stack_snapshot.size() != 0 ){
    printf("ERROR: Unhandled data on the stack stack_snapshot this might be a bug on the type cheking\n");
    exit(1);
  }
}
#endif /* TypeChecker */
