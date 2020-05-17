SHELL = /bin/sh

ASM = asm
VM = corewar

ASM_PATH = ./assembler/
VM_PATH = ./vm/

export CFLAGS = -Wall -Wextra -Werror -O3

.PHONY: all clean fclean re
all:
	$(MAKE) -C $(ASM_PATH)
	$(MAKE) -C $(VM_PATH)

clean:
	$(MAKE) -C $(ASM_PATH) clean
	$(MAKE) -C $(VM_PATH) clean

fclean:
	$(MAKE) -C $(ASM_PATH) fclean
	$(MAKE) -C $(VM_PATH) fclean

re:
	$(MAKE) -C $(ASM_PATH) re
	$(MAKE) -C $(VM_PATH) re
