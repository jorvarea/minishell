/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2024/07/25 17:33:53 by ana-cast         ###   ########.fr       */
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

extern volatile sig_atomic_t	g_signal;

// ------------------- STRUCTURES ------------------- //

typedef enum e_quote_status
{
	NOT_QUOTE = -1,
	EMPTY = 0,
	CLOSED = 1,
	UNCLOSED = 2
}	t_quote_status;

typedef enum e_token
{
	CMD = 0,
	AND = 1,
	OR = 2,
	PIPE = 4,
	OPEN_PAR = 5,
	CLOSE_PAR = 6,
	REDIR = 7,
	UNKNOWN = -1
}	t_token;

typedef enum e_type_redir
{
	INFILE = 10,
	APPEND = 11,
	OUTFILE = 12,
	HEREDOC = 13,
	NOT_REDIR = -1
}	t_type_redir;

// IN PROGRESS
typedef enum e_type_error
{
	E_NOMEM = 12,
	E_UTOK = 258,
	E_UQUOTE = 259,
}	t_type_error;

typedef struct s_redir
{
	char				*file;
	int					fd;
	enum e_type_redir	type;
	struct s_redir		*next;	
	struct s_redir		*prev;
}	t_redir;

/**
 * @struct Command List structure
 * @details
 * enum e_token	type: Contains the type of token (AND OR CMD PIPE...);
 * char **args: Contains the command and arguments as: args[0]="ls" args[1]="-l"
 * char	*cmd: Contains a string with the complete command;
 * char	**args: Contains an array with command + command arguments;
 * t_redir *redir: Contains a redir list with the file, type and next/prev;
 * struct s_cmd	*next: Pointer to the next command;
 * struct s_cmd	*prev: Pointer to the previous command;
*/
typedef struct s_cmd
{
	enum e_token	type;
	char			**args;
	struct s_redir	*redir;
	int				infd;
	int				outfd;
	int				pid;
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
	int				original_stdin;
	int				original_stdout;
	int				parser_error;
	char			*err_msg;
	char			**env;
	struct s_env	*l_env;
	struct s_cmd	*tokens;
}	t_shell;

// ---------------------- EXEC STRUCTURES -------------------- //

typedef struct s_pids_array
{
	pid_t	*pids;
	int		size;
	int		capacity;
}			t_pids_array;

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
	int		n_args;
	int		maximum_size;
}			t_args_array;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //

// ---------------------- SIGNALS ----------------------- //
void	init_signal_handler_cli(void);
void	signal_handler_cli(int signal);
void	init_signal_handler_heredoc(void);
void	signal_handler_heredoc(int signal);
void	init_signal_handler_exec(void);
void	sigquit_handler(int signal);

// ------------------------------------------------------ //
//                     PARSER FOLDER                      //
// ------------------------------------------------------ //

// ---------------------- PARSER.C ---------------------- //
t_cmd	*parser(char *input, t_shell *shell);
void	remove_array_quotes(char **array);
void	remove_str_quotes(char **str);

// ----------------------- INIT.C ----------------------- //
t_shell	*init_shell(char **envp);

// ------------------------ ENV.C ----------------------- //
char	**init_shell_env(char **envp);
t_env	*assign_env_values(char *env, t_env *new_env);
t_env	*set_env_list(char **env);

	// -------------------------------------------------- //
	//                 TOKENIZER FOLDER                   //
	// -------------------------------------------------- //

		// ------------------ QUOTES.C ------------------ //
int		skip_quotes(char const *s, int *i);
char	*process_input(char *str, t_shell *shell);

		// --------------- SPLIT_PARSER.C --------------- //
char	**trim_split(char **split, int len);
char	**split_parser(char *input);

	// -------------------------------------------------- //
	//                   LEXER FOLDER                     //
	// -------------------------------------------------- //

		// --------------- TOKEN_LIST.C ----------------- //
int		new_token_list(char **input_array, t_shell *shell);

		// ----------------- REDIRS.C ------------------- //
int		redir_structs(t_shell *shell);

		// ----------- UPDATE_TOKEN_LIST.C -------------- //
void	update_token_list(t_shell *shell);

		// ---------------- GET_TYPE.C ------------------ //
int		get_token_type(char **args);
int		get_redir_type(char *type);

	// -------------------------------------------------- //
	//                PARSER UTILS FOLDER                 //
	// -------------------------------------------------- //

		// ------------------ ERROR.C ------------------- //
void	*parser_error(int error, char *str, int exit_code, t_shell *shell);
bool	check_redir_args(char **redir, t_shell *shell);
int		check_token_err(t_shell *shell);

		// ---------------- FREE_UTILS.C ---------------- //
void	*free_shell(t_shell **shell);
void	*free_tokens(t_cmd **command_lst);
void	free_array(char ***array);
void	free_env_list(t_env	**l_env);
void	free_redir(t_redir	**redir);

		// --------------- STRUCT_NODE.C ---------------- //
void	pop_node_from_list(t_cmd *node);
t_env	*env_last_node(t_env *l_env);
t_cmd	*token_last_node(t_cmd *cmd_lst);
t_redir	*redir_last_node(t_redir *redir);

		// --------------- PRINT_UTILS.C ---------------- //
void	print_array(char **array, char *type);
void	print_array_one_line(char **array, char *title);

		// --------------- PRINT_SHELL.C ---------------- //
void	print_type(int type);
void	print_redir_type(int type);
void	print_command_list(t_cmd *tokens);
void	print_shell_l_env(t_env *l_env);
void	print_shell(t_shell *shell, bool env, bool tokens);

		// ------------------- UTILS.C ------------------ //
void	exit_program_nl(void);
int		array_len(char **array);

// ------------------------------------------------------ //
//                     EXEC FOLDER                        //
// ------------------------------------------------------ //

	// ------------------- EXEC FUNCTIONS ------------------- //
void	exec(t_shell *shell, t_cmd *head, t_cmd *end_node);
void	exec_single_cmd(t_shell *shell);
void	execute_cmd(t_shell *shell, t_cmd *cmd);
void	execute_bin(t_shell *shell, char **args);
void	manage_parenthesis(t_shell *shell, t_cmd **cmd);
	// ---------------- REDIR FUNCTIONS -------------------- //
bool	open_file(t_shell *shell, t_redir *redir);
void	close_files(t_redir *redir);
void	change_std_io(t_redir *redir);
void	execute_redir(t_shell *shell, t_cmd *cmd);

	// ---------------- EXEC_UTILS FUNCTIONS ----------------- //
void	exec_one(t_shell *shell, t_cmd *cmd);
void	wait_pids(t_shell *shell, t_cmd *cmd, t_cmd *end_node);

	// ------------------- HEREDOC FUNCTIONS ------------------- //
void	save_heredocs(t_shell *shell);
void	remove_tmp_heredoc_files(t_shell *shell);
void	expand_arg_heredoc(t_shell *shell, char **ptr_arg);
char	*generate_filename(char *heredoc_num);

	// ------------------------------------------------------ //
	//                     UTILS FOLDER                       //
	// ------------------------------------------------------ //

		// ------------------- FLAG_UTILS FUNCTIONS ------------------- //
bool	char_in_str(char c, char *str);
bool	valid_flag(char *flag, char *valid_flags);
int		count_valid_flag_arg(char **args, char *valid_flags);
bool	found_flags(char **args);

		// ------------------- ENV_UTILS FUNCTIONS ------------------- //
char	*get_value(t_shell *shell, char *key);
bool	remove_key(t_shell *shell, char *key);
void	add_new_env(t_shell *shell, char *key, char *value);
bool	valid_key(char *key);
bool	update_env(t_shell *shell, char *key, char *value);

		// ------------------- UPDATE_ENVP FUNCTIONS ------------------- //
void	update_envp(t_shell *shell);

		// ------------------- UTILS FUNCTIONS ------------------- //
int		count_words(char **ptr);
bool	equal_str(char *s1, char *s2);
t_env	*find_last_env(t_env *lst);
bool	is_directory(t_shell *shell, char *path);
void	update_exit_status_process(t_shell *shell, int status);
void	exit_shell_child(t_shell *shell);

		// ------------------- FT_STRREP FUNCTIONS ------------------- //
char	*ft_strrep(char *str, char *insertion, int start_index, int end_index);

		// ------------------- ERROR_UTILS FUNCTIONS ------------------- //
void	ft_invalid_flag_error(t_shell *shell, char *cmd,
			char invalid_flag, char *usage);
void	ft_perror(t_shell *shell, char *function, char *arg);
void	ft_minishell_error(t_shell *shell, char *msg);
void	ft_command_not_found_error(t_shell *shell, char *cmd);
void	ft_permission_denied(t_shell *shell, char *filename);
void	ft_is_a_directory_error(t_shell *shell, char *path);

	// ------------------------------------------------------ //
	//                     BUILT_INS FOLDER                   //
	// ------------------------------------------------------ //
void	echo(t_shell *shell, char **args);
void	pwd(t_shell *shell, char **args);
void	env(t_shell *shell, char **args);
void	cd(t_shell *shell, char **args);
void	export(t_shell *shell, char **args);
void	unset(t_shell *shell, char **args);
void	exit_cmd(t_shell *shell, char **args);
void	exit_shell(t_shell *shell);

	// ------------------------------------------------------ //
	//                     EXPANSIONS FOLDER                  //
	// ------------------------------------------------------ //
void	expand_env_cmd(t_shell *shell, char **args);
void	expand_env_arg(t_shell *shell, char **ptr_arg);
void	replace_home(t_shell *shell, char **arg, int start_index);
void	replace_env(t_shell *shell, char **arg, int start_index);
void	replace_exit_status(t_shell *shell, char **arg, int start_index);
bool	matching_pattern(char *pattern, char *str);
void	expand_wildcards_cmd(t_cmd *cmd);

#endif /* MINISHELL_H */