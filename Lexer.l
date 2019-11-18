%{ 
#include "symbols.h"
%} 
NEWLINE				 (\r|\n|\r\n)
DIGIT 				 ([0-9])
HEX_DIGIT 			 ([0-9A-Fa-f])
HEX_INTEGER			 (0[Xx]{HEX_DIGIT}+)
DEC_INTEGER			 ({DIGIT}+)
INTEGER				 ({HEX_INTEGER}|{DEC_INTEGER})
IDENTIFIER			 ([A-Za-z][_0-9A-Za-z]*)

S_COMMENT			 ("//"[^\r\n]*{NEWLINE})
WHITESPACE			 ([ \t]+)

%% 
{WHITESPACE}		{}
{NEWLINE}			{}
{S_COMMENT}			{}

"TURN"				    {  keyword(TURN);			}
"MOVE"				    {  keyword(MOVE);			}
"LOOP"				    {  keyword(LOOP);			}
"DEF"				    {  keyword(DEF);			}
"FUNC"				    {  keyword(FUNC);			}
"ADD"				    {  keyword(ADD);			}
"@POSITION"				{   keyword(ATPOSITION);			}
"@BACKGROUND"			{   keyword(ATBACKGROUND);			}
"@SIZE"				    {   keyword(ATSIZE);			}
"END LOOP"			    {   keyword(ENDLOOP);			}
"END FUNC"			    {   keyword(ENDFUNC);			}
"("                     {  keyword(LPAR);			}
")"                     {  keyword(RPAR);			}
"-"                     {  keyword(MINUS);			}

{INTEGER}			{  intConst(yytext);			}						    
{IDENTIFIER}		{  identifier(yytext);			}
.					{ issueError(yytext); }

%% 