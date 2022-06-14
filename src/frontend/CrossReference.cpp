#ifndef	CROSS_REFERENCE 
#define	CROSS_REFERENCE 

#include<iostream>
#include <vector>
#include "../backend/Lexer.cpp"

namespace Crossreference{
    void analyze(std::vector<Token> &src){
        std::vector<uint64_t> blocks;
	
        uint64_t currentPosition{};
//        for(std::vector<Token>::iterator x = src.begin(); x !=  src.end(); ++x){
        for(auto x = src.begin(); x != src.end(); ++x){
	    std::string ipname = x->head.atomName;
	    if (ipname == "if"
		|| ipname == "while"
		|| ipname == "do"
		)
	    {
		blocks.push_back(currentPosition);
	    } 
	    else if (ipname == "end") {
		//if (blocks.size() < 1) continue;
		auto last_block = blocks.back();
		blocks.pop_back();



		if (src[last_block].head.atomName == "do"){
		    auto before_do = blocks.back();

		    blocks.pop_back();
		    if (src[before_do].head.atomName == "if"){

			src[last_block].head.atomLinkedIndex = currentPosition;
		    }
		    else if (src[before_do].head.atomName == "while"){

			src[currentPosition].head.atomLinkedIndex  = before_do + 1; // end
			src[last_block].head.atomLinkedIndex = currentPosition + 1; // do
		    }

		}
	    }
	    ++currentPosition;
        }
	if(0){
	    size_t i = 0;
	    for(auto vr = src.begin(); vr != src.end(); ++vr){
		printf("NAME:\t`%s`\tLINE:`%lu`\tINDEX:`%lu`\tLINKED_TO:`%lu`\tINST:`%lu`\n", 
			vr->head.atomName.c_str(), 
			vr->head.atomIndexLine,
			vr->head.atomIndex,
			vr->head.atomLinkedIndex,
			i
			);
		++i;
	    }
	}
	if (blocks.size() > 1){
	    uint64_t unclosedBlock = blocks.back();
	    fprintf(stderr, "%lu:%lu: ERROR: Unclosed do-end blocks.\n",
		    src[unclosedBlock].head.atomIndexLine,
		    src[unclosedBlock].head.atomIndex
		    );
	    exit(1);
	}
    }
}
#endif /* ifndef CROSS_REFERENCE */
