
#ifndef ERRORS_H

# define ERRORS_H


/*
 * Check for tokens sequence
 */
# define ASM_FILE_ERR			"ERROR: Champion's file contains error"

# define ASM_C_N_MISSING		"ERROR: Champion's file contains error - no name or comment"


# define ASM_NL_MISSING			"ERROR: Champion's file contains error - new line is missing"

# define ASM_ERR_CMP_COMMENT	"ERROR: Champion should have comment before label"

# define ASM_COMMAND_MISSING	"ERROR: Arguments should be preceded by command name"

# define ASM_EXTRA_SEPARATOR	"ERROR: Arguments shouldn't be separated from command"

# define ASM_SEPARATOR_MISSING	"ERROR: Arguments should be separated"

# define ASM_ERR_NAME_COMMENT	"ERROR: Champion's name and/or comment placed incorrectly"

# define ASM_DOUBLE_COMMENT		"ERROR: Champion can have only one comment"

# define ASM_DOUBLE_NAME		"ERROR: Champion can have only one name"

# define ASM_WRONG_SEPARATOR	"ERROR: File with champion contains error - arguments separated incorrectly"


/*
 * Check for commands' arguments correctness
 */

# define ASM_TOLONG_NAME		"ERROR: Champion's name is too long"

# define ASM_TOLONG_COMMENT		"ERROR: Champion's comment is too long"

# define ASM_ERR_ARGS			"ERROR: Command followed by wrong arguments"

///// Egor's errors

#define ASM_NO_LABEL			"ERROR: label doesn't exist"

///// Stop Egor's errors

//								" of types T_REG, T_REG/T_DIR/T_IND and T_REG/T_DIR"

//# define ASM_STI_ERR			"ERROR: Command 'sti' should be followed exactly by tree arguments,"
//								" of types T_REG, T_REG/T_DIR/T_IND and T_REG/T_DIR"
//
//# define ASM_LDI_ERR			"ERROR: Command 'ldi'/'lldi' should be followed exactly "
//								"by tree arguments, of types T_REG/T_DIR/T_IND, T_REG/T_DIR and T_REG"
//
//# define ASM_AND_ERR			"ERROR: Command 'and'/'or'/'xor' should be followed by 3 arguments,"
//								" of types T_REG/T_DIR/T_IND, T_REG/T_DIR/T_IND and T_REG"
//
//# define ASM_ADD_ERR			"ERROR: Command 'add'/'sub' should be followed exactly"
//								" by tree arguments each of type T_REG"
//
//# define ASM_ST_ERR				"ERROR: Command 'st' should be followed exactly"
//								" by two arguments of types T_REG, T_REG/T_IND"
//
//# define ASM_LD_ERR				"ERROR: Command 'ld'/'lld' should be followed exactly"
//								" by two arguments of types T_DIR/T_IND, T_REG"
//
//# define ASM_AFF_ERR			"ERROR: Command 'aff' should be followed exactly"
//								" by one argument of type T_REG"
//
//# define ASM_LIVE_ERR			"ERROR: Command 'live'/'zjmp'/'fork'/'lfork'"
//								" should be followed exactly by one argument"
//								" of type T_DIR"
//


#endif
