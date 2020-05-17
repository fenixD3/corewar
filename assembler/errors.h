
#ifndef ERRORS_H
# define ERRORS_H

# define NAME_MISSING		"ERROR: Champion's file does not contain name"

# define CMNT_MISSING		"ERROR: Champion's file does not contain comment"

# define NL_MISSING			"ERROR: New line is missing"

# define CMD_MISS	"ERROR: Arguments should be preceded by command token"

# define EXTR_SPRTR	"ERROR: Arguments shouldn't be separated from command"

# define SPRTR_MISS	"ERROR: Arguments should be separated"

# define NAME_CMT	"ERROR: Champion's name and/or comment placed incorrectly"

# define DOUBLE_COMMENT		"ERROR: Champion can have double comment"

# define DOUBLE_NAME		"ERROR: Champion can have double name"

# define WRONG_SEPARATOR	"ERROR: Arguments separated incorrectly"

# define LONG_NAME			"ERROR: Champion's name is too long"

# define LONG_CMNT			"ERROR: Champion's comment is too long"

# define ERR_ARGS			"ERROR: Command followed by wrong arguments"

# define INVALID_STR_PLACE	"ERROR: Token string in invalid placement"

# define INVALID_STR		"ERROR: invalid string token"

# define NOCODE				"ERROR: program has no code after string"

# define NO_LABEL			"ERROR: Label doesn't exist"

# define INVALID_CMD		"ERROR: Command is invalid"

# define TREG_INVALID_NUM	"ERROR: argument T_REG has invalid number"

/*
** WARNINGS
*/

# define WRNNG_TREG_INVALID_NUM	"WARNING: argument T_REG has unsupported number"

#endif
