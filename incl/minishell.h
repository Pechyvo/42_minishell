/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../ft_destructor/ft_alloc.h"
# include "../libft/libft.h"
# include "../42_pipex/incl/pipex.h"
# include "../42_pipex/ft_printf/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <termcap.h>  
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define PATH_MAX 4096

// COLORS
# define RESET		"\033[0m"
# define BLACK		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define PURPLE		"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[1;37m"
# define UNDERLINE	"\033[4m"
# define CROSSED	"\033[9m"

// ERRORS
# define ER			"\033[1;31m\n  ERROR » \033[1;34m"
# define ER_MHELL	"\033[1;31mminishell: \033[1;34m"
# define ER_ARG		"Minishell can't take arguments\n\n\033[0m"
# define ER_ALLOC	"Allocation failed\n\n\033[0m"
# define ER_FORK	"Fork failed\n\n\033[0m"
# define ER_OPEN	"Heredoc opening failed\n\n\033[0m"
# define ER_EXIT	"exit: numeric argument required\n\033[0m"
# define ER_EXIT_AR	"exit: too many arguments\n\033[0m"
# define ER_QUOTE_S	"single quatation is not closed\n\033[0m"
# define ER_QUOTE_D	"double quatation is not closed\n\033[0m"
# define ER_SX_CHR	"syntax error near unexpected token `%c'\n\033[0m"
# define ER_SX_STR	"syntax error near unexpected token `%s'\n\033[0m"

extern int				g_sig;

typedef struct s_env	t_env;
typedef struct s_tkn	t_tkn;
typedef struct s_cmd	t_cmd;

typedef struct s_mhell
{
	char	*cmd_line;
	int		exit_code;
	char	**envp;
	t_env	*env;
	int		tkn_l;
	t_tkn	*tkn;
	int		cmd_l;
	t_cmd	*cmd;
}	t_mhell;

typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	_null,
	_text,
	_pipe,
	_hrdc,
	_rdin,
	_append,
	_rdout,
}	t_type;

typedef struct s_tkn
{
	char	*token;
	t_type	type;
}	t_tkn;

typedef struct s_cmd_alloc
{
	char		**args;
	int			num_args;
	const char	*in_rd;
	const char	*out_rd;
	int			append;
	int			heredoc;
}	t_cmd_alloc;

typedef struct s_cmd
{
	char			**args;	// An array of command arguments["ls", "-l", NULL]
	char			*in_rd;	// Input redirection file, e.g., "input.txt"
	char			*out_rd;// Output redirection file, e.g., "output.txt"
	int				append;	// Flag for append mode (1 for >>, 0 for >)
	int				heredoc;
	struct s_cmd	*next;	// Pointer to the next command in case of pipes
	char			**envp;
}	t_cmd;

// PARSER
void	ft_init_env(t_mhell *mhell, char **envp);
// char	*ft_input_prompt(t_mhell *mhell);
bool	ft_input_parse(t_mhell *mhell);
void	ft_substr_dollar(t_mhell *mhell, char **str, int *state);
void	ft_tokenize(t_mhell *mhell, char *str);
char	*ft_get_prompt(t_mhell *mhell);
bool	ft_handle_heredocs(t_mhell *mhell);

// EXECUTOR
int		execute_builtin(t_cmd *cmd);
int		start_exec(t_cmd *cmd);
int		execute_cmd(t_cmd *cmd);
int		env_builtins(t_cmd *cmd);
void	sigint_handler(int signum);
void	sigquit_handler(int signum);
int		builtin_cd(t_cmd *cmd);
int		builtin_echo(t_cmd *cmd);
int		builtin_pwd(void);
int		builtin_env(t_cmd *cmd);
int		builtin_export(t_cmd *cmd);
int		builtin_unset(t_cmd *cmd);
int		custom(t_cmd *cmd);
char	*get_env_var(char **envr, const char *name);
void	set_env_var(char **envr, const char *name, const char *value);
int		resolve_full_path(t_cmd *cmd, char **full_path);
int		out_rd(t_cmd *cmd);
int		in_rd(t_cmd *cmd);
int		open_for_fd(int *fd, t_cmd *cmd, int *saved_stdout);
int		open_file_ro_and_pid(int *fd, t_cmd *cmd, pid_t *pid);
void	setup_env(t_cmd *cmd);
int		create_pipes(int **pipefd, int num_cmds);
int		handle_builtin_commands(t_cmd *cmd);
void	close_all_pipes(int *pipefd, int num_cmds);
int		setup_child_pipes(int *pipefd, int i, int num_cmds);
int		count_commands(t_cmd *cmd);
int		fork_and_execute(t_cmd *it, int *pipefd, int i, int num_cmds);
int		wait_for_children(int num_cmds);

// PIPEX
void	ft_validate_cmd(char **argv);
void	ft_validate_file(char **argv);
void	ft_error_output(char *path, char *msg, int code);
void	ft_free_array(char **array);
char	*ft_find_path(char *cmd, char *path);
char	**ft_separate(char *a, char d);

// UTILITY
bool	ft_input_error(t_mhell *mhell, char	*input);
void	ft_open_quotes(t_mhell *mhell);
void	ft_create_cmd(t_mhell *mshell);
void	ft_free_mhell(t_mhell *mhell);

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_cmdlast(t_cmd *lst);
void	ft_cmdclear(t_cmd **lst, void (*del)(void*));
void	ft_cmddelone(t_cmd *lst, void (*del)(void*));

t_env	*ft_find_env(t_env *env, char *var);
void	ft_envadd(t_env **env, char *var, char *val);
void	ft_envclean(t_env **env);
char	*ft_envcut(char *str);

char	**ft_split_savediv(char *str, char c);
int		ft_strchr_pos(char *s, int c);

char	*ft_arrjoin(char **arr);
void	ft_free_array(char **arr);

bool	ft_is_empty(char *str);
bool	ft_is_space(char c);
void	ft_skip_spaces(char **str);
int		ft_conc_space(char curr, char next);
bool	ft_is_quote(char c);
void	ft_quote_state(int c, int *state);
int		ft_is_spec(char *str);
int		ft_isdigit_loop(char *str);

void	ft_print_cmd(t_cmd *cmd);

#endif
