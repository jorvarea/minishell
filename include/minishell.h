/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorvarea <jorvarea@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/16 22:23:09 by jorvarea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ------------------- EXT LIBRARIES ------------------- //

# include <libft.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>

// ------------------ COLOR MACROS ------------------ //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ------------------ CONSTANT MACROS ------------------ //

# define MAX_ENV_SIZE 4096

// ---------- GLOBAL VAR: Signal Reception ---------- //
extern pid_t	g_signal;

// ------------------- STRUCTURES ------------------- //

typedef enum e_quote_status
{
	NOT_QUOTE = -1,
	EMPTY = 0,
	CLOSED = 1,
	UNCLOSED = 2
}	t_quote_status;

// NOT FINISHED
typedef enum e_token
{
	CMD = 0,
	AND = 1,
	OR = 2,
	PIPE = 4,
	OPEN_PAR = 5,
	CLOSE_PAR = 6,
	UNKNOWN = -1
}	t_token;

typedef enum e_type_redir
{
	NOT_REDIR = 0,
	INFILE = 1,
	APPEND = 2,
	OUTFILE = 3,
	HEREDOC = 4
}	t_type_redir;

/*
ESTA ESTRUCTURA CONTIENE LAS REDIRECCIONES DE CADA COMANDO
*/
typedef struct s_redir
{
	char				*file;
	int					fd;
	enum e_type_redir	type;
	struct s_redir		*next;	
	struct s_redir		*prev;
}	t_redir;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

/**
 * @struct Command List structure
 * @details
 * char **args: Contains the command and arguments as: args[0]="ls" args[1]="-l"
 * char *infile: If cmd uses (<), it stores the name of the input file 
 * char *outfile: If cmd uses (> or >>), it stores the name of the output file 
 * int	out_append: If there is an outfile. Value 1 for (>>) and 0 for (<)
 * char *heredoc: Stores the end delimiter (string) as: 
 *		cat << hola --> heredoc="hola"
 * t_token	type: Contains the type of command (AND OR CMD PIPE...);
 * char	*cmd: Contains a string with the complete command;
 * char	**args: Contains an array with command + command arguments;
 * t_redir *redir: Contains a redir list with the file, type and next/prev;
 * struct s_cmd	*next: Pointer to the next command;
 * struct s_cmd	*prev: Pointer to the previous command;
*/
/*
EJEMPLO COMPLETO:
COMANDO: echo hola > que * > tal && echo Malaga
1.
 - type = commando
 - cmd = echo hola *
 - args -> args[0] = "echo", args[1] = "hola", args[2] = "*"
 - redir -> 1: infile file="que" next -> infile file="tal"
 - next: siguiente comando (2.)
 - prev: NULL
2.
 - type = &&
 - todo lo demas NULL excepto el next
 - next: siguiente comando (3.)
 - prev: anterior comando (1.)
3. 
 - type = COMMAND
 - cmd = "echo Malaga"
 - args -> args[0] = "echo", args[1] = "Malaga"
 - redir -> NULL
 - next: NULL
 - prev: anterior comando (2.)
 */
typedef struct s_cmd
{
	enum e_token	type;
	char			*cmd;
	char			**args;
	struct s_redir	*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

/**
 * @struct Shell Structure
 * @details
 * char **env: Contains environment variables as: evn[n]="VAR=VAR_VALUE"
 * int exit_status: Exit status of the last command executed (0 = OK | !0 = KO)
 * t_cmd	*tokens: Contains the list of commands/tokens;
 * t_env	*l_env: Contains the env array as a list/structure;
 * t_args	*files: List with the wildcards file to introduce in the token (?);
*/
typedef struct s_shell
{
	int				exit_status;
	char			**env;
	struct s_env	*l_env;
	struct s_cmd	*tokens;
	struct s_args	*files;
}	t_shell;

// ------------------- EXPANSION STRUCTURES ------------------- //

typedef enum e_inner_quotes
{
	NONE = 0,
	SINGLE = 1,
	DOUBLE = 2,
}					t_inner_quotes;

typedef struct s_quotes
{
	bool			single_quotes;
	bool			double_quotes;
	t_inner_quotes	inner_q;
}					t_quotes;

typedef struct s_args_array
{
	char	**args;
	int		size;
	int		maximum_size;
}			t_args_array;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //

char	*read_input(void);
void	exit_program_nl(void);
void	signal_handler(int signal);

// ------------------------------------------------------ //
//                     PARSER FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- PARSER.C ---------------------- //
t_cmd	*parser(char *input, t_shell *shell);

// ----------------------- INIT.C ----------------------- //
t_shell	*init_shell(char **envp);

// ------------------------ ENV.C ----------------------- //
char	**init_shell_env(char **envp);
t_env	*assign_env_values(char *env, t_env *new_env);
t_env	*set_env_list(char **env);

// ----------------- SPLIT_INPUT/CMD.C ------------------ //
char	**trim_split(char **split, int len);
char	**split_input(char *input);
char	**split_cmd(char *input);

// ------------------- COMMAND_LIST.C ------------------- //
void	create_command_list(char **input_array, t_shell *shell);

// ------------------------------------------------------ //
//                  PARSER UTILS FOLDER                   //
// ------------------------------------------------------ //

// --------------- FREE.C && FREE_UTILS.C --------------- //
void	free_shell(t_shell *shell);
void	free_commands(t_cmd *command_lst);
void	free_array(char ***array);
void	free_env_list(t_env	*l_env);
void	free_redir(t_redir	*redir);
void	free_arg_lst(t_args *l_args); // ELIMINAR
void	sh_free_str(char *str);

// -------------------- LAST_NODE.C --------------------- //
t_env	*env_last_node(t_env *l_env);
t_cmd	*cmd_last_node(t_cmd *cmd_lst);
t_redir	*redir_last_node(t_redir *redir);

// ---------------------- PRINT.C ----------------------- //
void	print_command_list(t_cmd *tokens);
void	print_shell_l_env(t_env *l_env);
void	print_array(char **array, char *type);
void	print_shell(t_shell *shell, bool env, bool tokens);

// --------------------- QUOTES.C ---------------------- //
int		skip_quotes(char const *s, int *i);
int		check_quotes(char const *s, int *i);
int		only_space(char *s, int *start, int *end);
char	*remove_empty_quotes(char *str, t_shell *shell);
void	ft_quotes_error(const char *cmd, t_shell *shell);

// ---------------- EXIT_PROGRAM_NL.C ------------------ //
void	exit_program_nl(void);

// ------------------------------------------------------ //
//                     EXEC FOLDER                        //
//                     EXEC FOLDER                        //
// ------------------------------------------------------ //

	// ------------------- EXEC FUNCTIONS ------------------- //
	// ------------------- EXEC FUNCTIONS ------------------- //
void	exec(t_shell *shell, t_cmd *cmd);
void	execute_cmd(t_shell *shell, t_cmd *cmd);
void	execute_bin(t_shell *shell, char **args);
void	execute_redir(t_shell *shell, t_cmd *cmd);

	// ------------------- HEREDOC FUNCTIONS ------------------- //
void	save_heredocs(t_shell *shell, t_redir *redir);
void	remove_tmp_heredoc_files(t_redir *redir);

	// ------------------------------------------------------ //
	//                     UTILS FOLDER                       //
	// ------------------------------------------------------ //

		// ------------------- FLAG_UTILS FUNCTIONS ------------------- //
		// ------------------- FLAG_UTILS FUNCTIONS ------------------- //
bool	char_in_str(char c, char *str);
bool	valid_flag(char *flag, char *valid_flags);
int		count_valid_flag_arg(char **args, char *valid_flags);
bool	found_flags(char **args);

		// ------------------- ENV_UTILS FUNCTIONS ------------------- //
		// ------------------- ENV_UTILS FUNCTIONS ------------------- //
char	*get_value(t_shell *shell, char *key);
bool	remove_key(t_shell *shell, char *key);
void	add_new_env(t_shell *shell, char *key, char *value);
bool	valid_key(char *key);
bool	update_env(t_shell *shell, char *key, char *value);

		// ------------------- UPDATE_ENVP FUNCTIONS ------------------- //
		// ------------------- UPDATE_ENVP FUNCTIONS ------------------- //
void	update_envp(t_shell *shell);

		// ------------------- UTILS FUNCTIONS ------------------- //
		// ------------------- UTILS FUNCTIONS ------------------- //
int		count_words(char **ptr);
bool	equal_str(char *s1, char *s2);
t_env	*find_last_env(t_env *lst);
void	*safe_malloc(size_t size);
pid_t	safe_fork(void);
pid_t	safe_fork(void);

		// ------------------- FT_STRREP FUNCTIONS ------------------- //
		// ------------------- FT_STRREP FUNCTIONS ------------------- //
char	*ft_strrep(char *str, char *insertion, int start_index, int end_index);

		// ------------------- ERROR_UTILS FUNCTIONS ------------------- //
		// ------------------- ERROR_UTILS FUNCTIONS ------------------- //
void	ft_invalid_flag_error(t_shell *shell, char *cmd,
			char invalid_flag, char *usage);
void	ft_perror(t_shell *shell, char *function, char *arg);
void	ft_minishell_error(t_shell *shell, char *msg);
void	ft_command_not_found_error(t_shell *shell, char *cmd);

	// ------------------------------------------------------ //
	//                     BUILT_INS FOLDER                   //
	// ------------------------------------------------------ //
	// ------------------------------------------------------ //
	//                     BUILT_INS FOLDER                   //
	// ------------------------------------------------------ //
void	echo(t_shell *shell, char **args);
void	pwd(t_shell *shell, char **args);
void	env(t_shell *shell, char **args);
void	cd(t_shell *shell, char **args);
void	export(t_shell *shell, char **args);
void	unset(t_shell *shell, char **args);
bool	exit_cmd(t_shell *shell, char **args);

	// ------------------------------------------------------ //
	//                     EXPANSIONS FOLDER                  //
	// ------------------------------------------------------ //
	// ------------------------------------------------------ //
	//                     EXPANSIONS FOLDER                  //
	// ------------------------------------------------------ //
void	expand_cmd(t_shell *shell, char **args);
void	replace_home(t_shell *shell, char **arg, int start_index);
void	replace_env(t_shell *shell, char **arg, int start_index);
void	replace_exit_status(t_shell *shell, char **arg, int start_index);
bool	matching_pattern(char *pattern, char *str);
void	expand_wildcards(t_cmd *cmd);

#endif /* MINISHELL_H */