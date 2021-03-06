/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 13:36:51 by rsharipo          #+#    #+#             */
/*   Updated: 2018/10/13 09:00:28 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/errno.h>
# include <stdio.h>

/* enable ft_malloc wrapper */
// # define LIBFT_MEM_ALLOC
/* enable ft_malloc debug info */
// # define LIBFT_MEM_DEBUG
/* enable ft_malloc verbal info */
// # define LIBFT_MEM_VERBAL

# define LIBFT_BUFF				256
# define LIBFT_ERRBUF			1024
# define LIBFT_HT_SIZE			512
# define LIBFT_HT_FACTOR		16

# define COLOR_RED				"\x1b[31m"
# define COLOR_GREEN			"\x1b[32m"
# define COLOR_YELLOW			"\x1b[33m"
# define COLOR_BLUE				"\x1b[34m"
# define COLOR_MAGENTA			"\x1b[35m"
# define COLOR_CYAN				"\x1b[36m"
# define COLOR_RED_BOLD			"\033[1m\033[31m"
# define COLOR_RESET			"\x1b[0m"

# define TXT_RED(STR_LITERAL)	COLOR_RED STR_LITERAL COLOR_RESET
# define TXT_GREEN(STR_LITERAL)	COLOR_GREEN STR_LITERAL COLOR_RESET
# define TXT_YELL(STR_LITERAL)	COLOR_YELLOW STR_LITERAL COLOR_RESET
# define TXT_CYAN(STR_LITERAL)	COLOR_CYAN STR_LITERAL COLOR_RESET
# define TXT_MAG(STR_LITERAL)	COLOR_MAGENTA STR_LITERAL COLOR_RESET

# define FLOOR(X,Y)				((X)-((X)%(Y)))
# define CEIL(X,Y)				(((X)%(Y)==0)?(X):((X)+((Y)-((X)%(Y)))))
# define MAX(A,B)				((A)>(B)?(A):(B))
# define MIN(A,B)				((A)<(B)?(A):(B))
# define ASC(X)					(X - 48)
# define ABS(X)					((X)>=(0)?(X):(-X))

enum e_libft_err
{
	LIBFT_OK	= 0,
	LIBFT_ERR	= -1,
	LIBFT_MEM	= -2,
	LIBFT_FATAL	= -3,
};

typedef struct		s_node
{
	char			*key;
	void			*content;
	size_t			size;
	struct s_node	*next;
	struct s_node	*nodes;
}					t_node;

typedef struct		s_queue
{
	t_node			*first;
	t_node			*last;
}					t_queue;

typedef struct		s_stack
{
	t_node			*top;
}					t_stack;

typedef struct		s_htbl
{
	void 			**arr;
	int				size;
}					t_htbl;

void		*ft_malloc(const char *memkey, size_t memsize);
void		ft_free(const char *memkey, void *memptr);
void		ft_free_all(void);

uint32_t	ft_hash(const char *, size_t);
void		*ft_htbl_init(int);
t_node		*ft_htbl_iter(t_htbl *);
void		ft_htbl_add(t_htbl *, const char *, void *);
void		*ft_htbl_get(t_htbl *, const char *);
void		ft_htbl_assign(t_htbl *, const char *, void *);
void		ft_htbl_del(t_htbl *);
void		ft_htbl_raw_add(t_htbl *, void *, size_t, void *);
void		*ft_htbl_raw_get(t_htbl *, void *, size_t);
void		ft_htbl_raw_assign(t_htbl *, void *, size_t, void *);

t_node		*ft_node_init(void);
t_node		*ft_node_new(const char *, void *, size_t);
void		ft_node_del(t_node *, void (*f_del)(t_node *));
int			ft_node_is_parent(t_node *);

void		ft_lst_append(t_node **, t_node *);
void		ft_lst_prepend(t_node **, t_node *);
void		ft_lst_del(t_node *, void (*f_del)(t_node *));
void		ft_lst_del_first(t_node **, void (*f_del)(t_node *));
void		ft_lst_del_last(t_node **, void (*f_del)(t_node *));
void		ft_lst_del_one(t_node **, t_node *, void (*f_del)(t_node *));
int			ft_lst_size(t_node *);
void		ft_lst_map(t_node *, void *farg, void (*f)(t_node *, void *));
t_htbl		*ft_lst_htable(t_node *);

t_stack		*ft_stack_init(void);
void		*ft_stack_pop(t_stack *);
void		ft_stack_push(t_stack *, const char *, void *, size_t);
t_node		*ft_stack_peek(t_stack *);
int			ft_stack_size(t_stack *);
void		ft_stack_clear(t_stack *);
void		ft_stack_del(t_stack *, void (*f_del)(t_node *));
t_htbl		*ft_stack_htable(t_stack *);

t_queue		*ft_queue_init(void);
void		ft_queue_enqueue(t_queue *, t_node *);
void		*ft_queue_dequeue(t_queue *);
t_node		*ft_queue_peek(t_queue *);
int			ft_queue_is_empty(t_queue *);
int			ft_queue_size(t_queue *);
void		ft_queue_del(t_queue *, void (*f)(t_node *));
void		ft_queue_del(t_queue *, void (*f)(t_node *));
t_htbl		*ft_queue_htable(t_queue *);

t_node		*ft_ntree_construct(const char *);
void		*ft_ntree_dfs(t_node *, void *, int (*f)(t_node *, void *));
void		*ft_ntree_bfs(t_node *, void *, int (*f)(t_node *, void *));
void		ft_ntree_del(t_node *, void (*f_del)(t_node *));
void		ft_ntree_print(t_node *, void (*f_print)(t_node *, int));
int			ft_ntree_size(t_node *);
t_node		*ft_ntree_iter(t_node *);
t_htbl		*ft_ntree_htable(t_node *);

void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memzcpy(void *dst, const void *src, size_t, size_t);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memdup(void *, size_t);
void		ft_memdel(void **ap);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *, const char *, size_t);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strcoll(char *src);
long long	ft_atoi(const char *str);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_iseol(int c);
int			ft_iseolws(int c);
int			ft_iswspace(int c);
int			ft_isblank(int c);
int			ft_ishex(int c);
int			ft_str_isalpha(const char *s);
int			ft_str_isalnum(const char *s);
int			ft_str_isdigit(const char *s);
int			ft_str_isascii(const char *s);
int			ft_str_isprint(const char *s);
int			ft_str_ishex(const char *s);
void		ft_strup(char *s);
void		ft_strlow(char *s);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_itoa_base(intmax_t value, int base);
void		ft_putchar(char c);
void		ft_putstr(char const *s);
int			ft_putendl(char const *, size_t);
int			ft_putendl_fd(int fd, char const *, size_t);
void		ft_putnbr(int n);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(int fd, char const *s);
void		ft_putnbr_fd(int fd, int n);
int			get_next_line(int fd, char **line);
int			ft_printf(const char *format, ...);
int			ft_strlst(const char *s, int num, ...);
void		ft_binhex(char *hex, const void *bin, size_t binsize);
void		ft_hexbin(void *bin, const char *hex, size_t hexsize);
void		ft_revbits(void *src, size_t size);
char		*ft_intchar(char *buf, intmax_t integer, int int_bytes);
void		ft_2darray_del(void **, int);
int			ft_2darray_len(void **);
char		*ft_2darray_merge_cstr(char **, int);

int			ft_error(const char *, const char *);
void		ft_exit(void);

extern int	global_ft_malloc_error;

# if defined (LIBFT_MEM_ALLOC) && defined (LIBFT_MEM_VERBAL)

#  define LIBFT_FREE(PTR) \
	do \
	{ \
		if (NULL != PTR) \
		{ \
			ft_printf(TXT_MAG("%s\n"), __func__); \
			ft_free(#PTR, PTR); \
			PTR = NULL; \
		} \
		if (LIBFT_FATAL == global_ft_malloc_error) \
		{ \
			 ft_exit(); \
		} \
	} \
	while (0)

#  define LIBFT_ALLOC(PTR, SZ) \
	do \
	{ \
		ft_printf(TXT_MAG("%s\n"), __func__); \
		PTR = ft_malloc(#PTR, SZ); \
		if (LIBFT_FATAL == global_ft_malloc_error) \
		{ \
			 ft_exit(); \
		} \
	} \
	while (0)

#  define LIBFT_REALLOC(PTR, SZ, NSZ) \
	do \
	{ \
		ft_printf(TXT_MAG("%s\n"), __func__); \
		void	*NEWPTR; \
		NEWPTR = ft_malloc(#PTR "_realloc", NSZ); \
		if (LIBFT_FATAL == global_ft_malloc_error) \
		{ \
			 ft_exit(); \
		} \
		if (NULL != PTR) \
		{ \
			ft_memcpy(NEWPTR, PTR, SZ); \
			ft_free(#PTR, PTR); \
		} \
		PTR = NEWPTR; \
	} \
	while (0)

# elif defined (LIBFT_MEM_ALLOC)

#  define LIBFT_FREE(PTR) \
	do \
	{ \
		if (NULL != PTR) \
		{ \
			ft_free(#PTR, PTR); \
			PTR = NULL; \
			\
			if (LIBFT_OK != global_ft_malloc_error) \
			{ \
				ft_printf("%@\t%s in %s:%d\n", __func__, __FILE__, __LINE__); \
			} \
			if (LIBFT_FATAL == global_ft_malloc_error) \
			{ \
				 ft_exit(); \
			} \
		} \
	} \
	while (0)

#  define LIBFT_ALLOC(PTR, SZ) \
	do \
	{ \
		PTR = ft_malloc(#PTR, SZ); \
		if (LIBFT_OK != global_ft_malloc_error) \
		{ \
			ft_printf("%@\t%s in %s:%d\n", __func__, __FILE__, __LINE__); \
		} \
		if (LIBFT_FATAL == global_ft_malloc_error) \
		{ \
			 ft_exit(); \
		} \
	} \
	while (0)

#  define LIBFT_REALLOC(PTR, SZ, NSZ) \
	do \
	{ \
		void	*NEWPTR; \
		NEWPTR = ft_malloc(#PTR "_realloc_", NSZ); \
		if (LIBFT_OK != global_ft_malloc_error) \
		{ \
			ft_printf("%@\t%s in %s:%d\n", __func__, __FILE__, __LINE__); \
		} \
		if (LIBFT_FATAL == global_ft_malloc_error) \
		{ \
			 ft_exit(); \
		} \
		if (NULL != PTR) \
		{ \
			ft_memcpy(NEWPTR, PTR, SZ); \
			ft_free(#PTR, PTR); \
		} \
		PTR = NEWPTR; \
	} \
	while (0)

# else

#  define LIBFT_FREE(PTR) \
	do \
	{ \
		if (NULL != PTR) \
		{ \
			free(PTR); \
			PTR = NULL; \
		} \
	} \
	while (0)

#  define LIBFT_ALLOC(PTR, SZ) \
	do \
	{ \
		PTR = calloc(SZ, 1); \
		if (ENOMEM == errno) \
		{ \
			perror(TXT_RED("fatal error")); \
			ft_exit(); \
		} \
	} \
	while (0)

#  define LIBFT_REALLOC(PTR, SZ, NSZ) \
	do \
	{ \
		void	*NEWPTR; \
		LIBFT_ALLOC(NEWPTR, NSZ); \
		if (NULL != PTR) \
		{ \
			ft_memcpy(NEWPTR, PTR, SZ); \
			free(PTR); \
		} \
		PTR = NEWPTR; \
	} \
	while (0)

# endif

#endif
