# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/25 13:32:25 by hanmpark          #+#    #+#              #
#    Updated: 2023/03/29 15:33:44 by hanmpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- COLORS ---------------------------------- #
DEF = \033[0m
BOLD = \033[1m
CUR = \033[3m
UL = \033[4m
UP = \033[A

ORANGE = \033[38;5;216m
LBLUE = \033[38;5;153m
LYELLOW = \033[38;5;222m
BEIGE = \033[38;5;223m

# --------------------------------- SOURCES ---------------------------------- #
SRC_PATH = ./src/

MAIN_PATH = ${SRC_PATH}main/
SRCS_MAIN = ${addprefix ${MAIN_PATH}, check.c \
										execCommand.c \
										pipex.c}

OBJS_MAIN = ${SRCS_MAIN:.c=.o}

# --------------------------------- COMPILER --------------------------------- #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
ifdef DEBUG
CFLAGS += -fsanitize=address -g3
endif
HEADER_PATH = ./inc/

SRCS_COUNT = 0
SRCS_TOT = ${shell find ./src/ -type f -name '*.c' | wc -l}
SRCS_PRCT = ${shell expr 100 \* ${SRCS_COUNT} / ${SRCS_TOT}}

%.o:%.c ${HEADER_PATH}
	@${eval SRCS_COUNT = ${shell expr ${SRCS_COUNT} + 1}}
	@${CC} ${CFLAGS} -I ${HEADER_PATH} -c $< -o ${<:.c=.o}
	@echo " ${BOLD}${CUR}${BEIGE}-> Compiling ${DEF}${BOLD}${LYELLOW}[LIBFT]${DEF}"
	@printf " ${BEIGE}  [%d/%d files (%d%%)]${DEF}" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
	@echo "${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
LIBFT_PATH = ./libft/
NAME = pipex

all: ${NAME}

${NAME}:	${OBJS_MAIN}
	@echo "\n\n"
	@${MAKE} -C ${LIBFT_PATH}
	@${CC} ${CFLAGS} ${LIBFT_PATH}libft.a ${OBJS_MAIN} -o ${NAME}
	@echo "\n\n\n   ${BOLD}${CUR}${LYELLOW}${NAME} COMPILED ✨${DEF}\n"

debug:
	@${MAKE} DEBUG=1

clean:
	@echo "\n\t${BOLD}${CUR}${ORANGE}CLEANING...${DEF}\n"
	@rm -f ${OBJS_MAIN} ${OBJS_BONUS}
	@${MAKE} -C ${LIBFT_PATH} clean
	@echo "${LBLUE}${BOLD}${CUR}- Deleted object files${DEF}\n"

fclean: clean
	@${eval SRCS_COUNT = 0}
	@rm -f ${LIBFT_PATH}libft.a
	@rm -f ${NAME}
	@echo "${LBLUE}${BOLD}${CUR}- Deleted libft.a ${NAME}${DEF}\n\n"

re: fclean all

.PHONY: all clean fclean re debug