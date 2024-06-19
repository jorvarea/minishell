/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:53:03 by ana-cast          #+#    #+#             */
/*   Updated: 2024/06/19 19:43:05 by ana-cast         ###   ########.fr       */
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

/**
 * @struct Command List structure
 * @details
 * char **args: Contains the command and arguments as: args[0]="ls" args[1]="-l"
 * char *infile: If cmd uses (<), it stores the name of the input file 
 * char *outfile: If cmd uses (> or >>), it stores the name of the output file 
 * int	out_append: If there is an outfile. Value 1 for (>>) and 0 for (<)
 * char *heredoc: Stores the end delimiter (string) as: cat << hola --> heredoc="hola"
*/
typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	struct s_cmd	*next;
}	t_cmd;

/**
 * @struct Shell Structure
 * @details
 * char **env: Array that contains environment variables as: evn[n]="VAR=VAR_VALUE"
 * int exit_status: Stores the exit status of the last command executed (0 = OK | !0 = KO)
*/
typedef struct s_shell
{
	char	**env;
	int		exit_status;
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
t_cmd	init_command(void); // NOT STARTED
t_shell *init_shell(char **envp); // ?


// ------------------- FREE FUNCTIONS ------------------- //
void	free_array(char **array);
void	free_commands(t_cmd *command_lst);
void 	free_shell(t_shell *shell);


#endif /* MINISHELL_H */