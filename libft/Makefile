
# 정적 라이브러리 libft 생성
NAME = libft.a

CC = cc

# 플래그 지정
CFLAGS = -Wall -Wextra -Werror

# ar: 라이브러리 아카이브 생성 및 수정 명령어 
# r: 아카이브에 새로운 파일 추가, 기존 파일 교체 / c: 아카이브 파일 존재하지 않으면 새로 생성 / s: 아카이브 파일에 인덱스 생성(링크시 검색 속도 향상)
AR = ar rcs

SRCS = ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c \
       ./ft_isprint.c ./ft_toupper.c ./ft_tolower.c ./ft_strlen.c \
       ./ft_strlcpy.c ./ft_strlcat.c ./ft_strchr.c ./ft_strrchr.c \
       ./ft_strncmp.c ./ft_strnstr.c ./ft_substr.c ./ft_strjoin.c \
       ./ft_strtrim.c ./ft_split.c ./ft_strmapi.c ./ft_striteri.c \
       ./ft_memset.c ./ft_bzero.c ./ft_memcpy.c ./ft_memmove.c \
       ./ft_memchr.c ./ft_memcmp.c ./ft_calloc.c ./ft_strdup.c \
       ./ft_putchar_fd.c ./ft_putstr_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c \
       ./ft_atoi.c ./ft_itoa.c

OBJS = $(SRCS:.c=.o)

# all이라는 목표가 $(NAME)이라는 다른 목표에 의존하여, all 목표를 실행할 때 $(NAME) 목표를 먼저 만들어야 함을 의미
all: $(NAME)

# $(NAME)을 생성하기 위해서는 $(OBJS)가 필요하다 => .o 파일들을 라이브러리로 묶어서 $(NAME) 파일을 생성하라
$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS)

# .c 파일을 .o 파일로 컴파일하기 위한 규칙 정의
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 중간 오브젝트 파일들을 삭제
clean:
		rm -f $(OBJS)

# clean 목표를 먼저 실행한 후 빌드된 실행 파인 $(NAME) 삭제
fclean: clean
		rm -f $(NAME)

# fclean 목표르 먼저 실행한 후 all 목표를 실행하여 전체 빌드 프로세스 다시 시작
re: fclean all

# 특수한 목표로 해당 목표가 실제 파일의 이름이 아니라 명령어의 이름이라는 것을 Make 에게 알려줌
.PHONY: all clean fclean re


# $<: 현재 Target이 의존하는 대상들 중 변경된 것들의 목록
# $^: 현재 Target이 의존하는 대상들의 전체 목록
# $@: 현재 Target 이름