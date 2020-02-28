NAME = HomeService
bis = bis
CC  = gcc

RM = rm -f
INC = inc/
CFLAGS = -Wall -Wextra -c -g

##GTKLIB
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS = $(PTHREAD) $(GTKLIB) -export-dynamic

##MYSQL
LDFLAGS += `mysql_config --cflags --libs`
CFLAGS += `mysql_config --cflags --libs`

##LIBQRENCODE
LIBS = -lqrencode

#SANITIZE
SAN = -fsanitize=address

SRCS = main.c home.c menu.c add.c gtk_utils.c list_provider.c \
profil.c add_form_process.c add_mysql.c add_make_qrcode.c \
configuration.c string.c


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
