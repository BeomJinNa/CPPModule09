#parameters====================================================================

CXX			= c++

COMMONFLAGS	=
CXXFLAGS	= $(COMMONFLAGS) -Wall -Wextra -Werror -std=c++98 $(LOG_ON_FLAGS)
LDFLAGS		= $(COMMONFLAGS)
LOGFILES	= output_vector.txt output_list.txt

NAME	= PmergeMe
INCLUDE	=


#sources=======================================================================

SRCS	= main.cpp \
		  PmergeMe.cpp

OBJS	= $(SRCS:.cpp=.o)

TARGET_OBJS = $(OBJS)

ifdef LOG_ON
	LOG_ON_FLAGS = -DLOG_ON
endif

#rules=========================================================================

.PHONY: all
all :
	make $(NAME)

$(NAME) : $(TARGET_OBJS)
	$(CXX) -o $@ $(TARGET_OBJS) $(LDFLAGS)

.PHONY: logon
logon :
	make $(NAME) LOG_ON=0

#const options=================================================================

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean :
	rm -f $(OBJS)

.PHONY: fclean
fclean :
	make clean
	rm -f $(NAME) $(LOGFILES)

.PHONY: re
re :
	make fclean
	make all

.PHONY: lre
lre :
	make fclean
	make logon
