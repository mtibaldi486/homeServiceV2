NAME = Fusion
bis = bis
CC  = gcc

RM = rm -f
INC = inc/
CFLAGS = -Wall -Wextra -c -g

##MYSQL
#LDFLAGS += `mysql_config --cflags --libs`
#CFLAGS += `mysql_config --cflags --libs`

#SANITIZE
SAN = -fsanitize=address

SRCS = main.c utils.c list.c merge.c setup.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS) $(INC)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS): $(addprefix src/,$(SRCS))
	$(CC) $(CFLAGS) $(GTKLIB) $(addprefix src/,$(SRCS))

san: $(bis)

$(bis):	$(OBJS) $(INC)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS) $(SAN)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
