
## ANA NOTES:

### Regarding parenthesis:

EXAMPLE OF COMMAND THAT CHANGES OUTPUT DUE TO THE PARENTHESIS USAGE:
echo A || echo B && (echo C && echo D) >>> ACD
echo A || (echo B && echo C) && echo D >>> AD
echo A || (echo B && echo C && echo D) >>> A



### Regarding signals:
See: https://man7.org/linux/man-pages/man7/signal.7.html

Un shell es interactivo cuando: 

#### General Info (for implementing in minishell)
SIGINT: Ctrl + C -> quits minishell, but it should quit the current execution and display a new shell
SIGQUIT: Ctrl + \ -> ignore this signal so it doesnt do anything when INTERACTIVE
Ctrl + D (not signal) -> EOF || nvm, Ctrl+D already finishes the shell

#### Useful:
SIG_IGN -> For ignoring signals
See: https://en.cppreference.com/w/c/program/SIG_strategies
Example:
int main(void)
{
    /* ignoring the signal */
    signal(SIGTERM, SIG_IGN);
    raise(SIGTERM);
    printf("Exit main()\n"); # Even after SIGTERM is raised before, this line is executed
}



## take into account

tratar parentesis como tokens

echo hola > que *

1º
cmd = comando completo (echo hola *)
2º
args[0] echo  - args[1] hola - args[2] *
3º
wildcards	lista de tipo args (archives)
4º
args[2] lo sustituyes por files
5º
	expandes variables y redivides en arguments
6º
	buscas el path del args[0] y lo metes en cmd


Tras terminar de asignar args l_args y redir, cmd se actualiza a la ruta del comando?


## ANA TASKS TO-DO

Develop following functions: 
```c
## Signal handling
void signal_handler(int sig);
## Shell functions
t_shell *init_shell(char **envp);
void free_shell(t_shell *shell);
## Parsing functions
t_command *parse_input(char *line);
void free_command(t_command *cmd);

## helper functions:
char **split_line(char *line, char *delim);
t_command *create_command(char **tokens);
int handle_redirections(char **tokens, t_command *cmd);
char *strip_quotes(char *str);
void handle_heredoc(t_command *cmd);
```

 - Add argc check to main (argc == 1)

#### SPLIT PARSER EXAMPLES:

1. echo hola que 'tal' "como 'estass'" 'todo bien?' ""
	> ["echo", "hola", "que", "tal", "como 'estas'", "todo bien?"]


#### NOTA BASH:
1. echo hola que 'tal' "como 'estass'" todo bien? ""
	> zsh: no matches found: bien?

2. echo hola que 'tal' "como 'estass'" 'todo bien?' ""
	> hola que tal como 'estass' todo bien? 

3. input: echo "hola que"' tal'
	> hola que tal

4. input: echo 'hola "que"' tal
	> hola "que" tal
