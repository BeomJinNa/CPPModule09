#parameters====================================================================

CXX			= c++

COMMONFLAGS	=
CXXFLAGS	= $(COMMONFLAGS) -Wall -Wextra -Werror -std=c++98
LDFLAGS		= $(COMMONFLAGS)

NAME	= btc
INCLUDE	=


#sources=======================================================================

SRCS	= main.cpp \
		  BitcoinExchange.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET_OBJS = $(OBJS)

#rules=========================================================================

.PHONY: all
all :
	make $(NAME)

$(NAME) : $(TARGET_OBJS)
	$(CXX) -o $@ $(TARGET_OBJS) $(LDFLAGS)

#const options=================================================================

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean :
	rm -f $(OBJS)

.PHONY: fclean
fclean :
	make clean
	rm -f $(NAME)

.PHONY: re
re :
	make fclean
	make all
