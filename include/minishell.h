/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/24 16:32:25 by ana-cast         ###   ########.fr       */
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

// ------------------ COLOR MACROS ------------------ //

# define WHITE "\033[0m"
# define BOLD "\033[1m"
# define GREEN "\033[0;32m"
# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define YELLOW "\033[33m"
# define MAGENTA "\033[35m"
# define TURQUOISE "\033[36m"

// ---------- GLOBAL VAR: Signal Reception ---------- //
extern pid_t	g_signal;

// ------------------- STRUCTURES ------------------- //

// NOT FINISHED
typedef enum e_token
{
	CMD = 0,
	AND = 1,
	OR = 2,
	PIPE = 4
}	t_token;

typedef enum e_type_redir
{
	INFILE = 0,
	OUTFILE = 1,
	HEREDOC = 2
}	t_type_redir;

/*
ESTA ESTRUCTURA CONTIENE LAS REDIRECCIONES DE CADA COMANDO
*/
typedef struct s_redir
{
	char				*file;
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
 * t_args *l_args: Contains the args array as a list (with wildcards + env);
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
 - l_args -> 1: arg="echo" next->arg="hola" next->(...) next -> arg="fileN"
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
 - l_args -> 1: arg="echo" next-> arg="Malaga"
 - redir -> NULL
 - next: NULL
 - prev: anterior comando (2.)

POR DECIDIR!!!
BORRADOR: Al expandir las wildcards en l_args, se actualiza args (?)
 - EJEMPLO CON EL PRIMER COMANDO:
 	- args -> args[0] = "echo", args[1] = "hola", args[2] = "*"
	- l_args -> 1: arg="echo" next->arg="hola" next->(...) next -> arg="fileN"
	- args -> args[0] = "echo", args[1] = "hola", (...), args[N + 2] = "fileN"
*/
typedef struct s_cmd
{
	enum e_token	type;
	char			*cmd;
	char			**args;
	struct s_args	*l_args;
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
	char			**env;
	int				exit_status;
	struct s_cmd	*tokens;
	struct s_env	*l_env;
	struct s_args	*files;
}	t_shell;

// ------------------------------------------------------ //
//                     MAIN FUNCTIONS                     //
// ------------------------------------------------------ //

char	*read_input(void);
void	exit_program_nl(void);
void	signal_handler(int signal);

// ------------------------------------------------------ //
//                     PARSER FOLDER                      //
// ------------------------------------------------------ //

// ------------------ PARSER FUNCTIONS ------------------ //
t_cmd	*parser(char *input); // ?

// ------------------- INIT FUNCTIONS ------------------- //
t_cmd	*init_command(void); // NOT STARTED
char	**init_shell_env(char **envp);
t_shell	*init_shell(char **envp); // ?

// ------------------- FREE FUNCTIONS ------------------- //
void	sh_free_str(char *str);
void	free_array(char **array);
void	free_arg_lst(t_args *l_args);
void	free_redir(t_redir	*redir);
void	free_commands(t_cmd *command_lst);
void	free_env_list(t_env	*l_env);
void	free_shell(t_shell *shell);

// ------------------- PRINT FUNCTIONS ------------------- //
void	print_shell_env(char **env);

#endif /* MINISHELL_H */