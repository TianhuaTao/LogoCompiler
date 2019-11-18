%{ 

%} 
NEWLINE				 (\r|\n|\r\n)
DIGIT 				 ([0-9])
HEX_DIGIT 			 ([0-9A-Fa-f])
HEX_INTEGER			 (0[Xx]{HEX_DIGIT}+)
DEC_INTEGER			 ({DIGIT}+)
INTEGER				 ({HEX_INTEGER}|{DEC_INTEGER})
IDENTIFIER			 ([A-Za-z][_0-9A-Za-z]*)
SIMPLE_OPERATOR		 ("+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"."|","|";"|"!"|"("|")"|"["|"]"|"{"|"}")
S_COMMENT			 ("//"[^\r\n]*{NEWLINE})
WHITESPACE			 ([ \t]+)

%% 
{WHITESPACE}		{}
{NEWLINE}			{}
{S_COMMENT}			{}

"TURN"				{ return keyword(Parser.VOID);			}
"MOVE"				{ return keyword(Parser.VOID);			}
"LOOP"				{ return keyword(Parser.VOID);			}
"DEF"				{ return keyword(Parser.VOID);			}
"FUNC"				{ return keyword(Parser.VOID);			}
"ADD"				{ return keyword(Parser.VOID);			}
"@POSITION"				{ return keyword(Parser.VOID);			}
"@BACKGROUND"				{ return keyword(Parser.VOID);			}
"@SIZE"				{ return keyword(Parser.VOID);			}
"END LOOP"			{ return keyword(Parser.VOID);			}
"END FUNC"			{ return keyword(Parser.VOID);			}

{SIMPLE_OPERATOR}	{ return operator((int)yycharat(0));	}
"true"				{ return boolConst(true);										}
"false"				{ return boolConst(false);										}
{INTEGER}			{ return intConst(yytext());			}						    
{IDENTIFIER}		{ return identifier(yytext());			}
.					{ issueError(new UnrecogCharError(getLocation(), yycharat(0))); }

%% 