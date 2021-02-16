NAME	=	escape
PATH	= 	src/

SRC	= 	coordinates.cpp \
		fields.cpp \
		storage.cpp \
		iterator.cpp \
		player.cpp \
		ai_player.cpp \
		game.cpp \
		manual_game.cpp \
		ai_game.cpp \
		main.cpp \

OBJ		=	$(addprefix $(PATH), $(SRC:.cpp=.o))

DIR		=	include/

CFLAGS	=	-g -pedantic -Wall -Wextra -std=c++17  -I$(DIR)

CC		=	g++

RM		=	rm -f
ECHO	=	echo -e

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

all	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@$(ECHO) '\033[0;33m> Compiled\033[0m'

clean	:
	$(RM) $(OBJ)
	@$(ECHO) '\033[0;33m> Directory cleaned\033[0m'

fclean	: clean
	$(RM) $(NAME)
	@$(ECHO) '\033[0;33m> Remove executable\033[0m'

re	: fclean all