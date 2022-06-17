/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboehm <aboehm@42adel.org.au>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:44:11 by aboehm            #+#    #+#             */
/*   Updated: 2022/04/04 12:04:15 by aboehm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/file.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "typedefs.h"
# include <sys/stat.h>

//lexer
# define T_COMMAND 0
# define T_DOUBLE_QUOTES 1
# define T_SINGLE_QUOTES 2
# define T_PIPE 3
# define T_APPEND_RD 4
# define T_REDIR_TO_F 5
# define T_REDIR_FROM_H 6
# define T_REDIR_FROM_F 7
//One allowed Global variable, it's the hash table
// that stores the environment variables
# define ENV_SIZE 2048
# define LOCAL_ENV_SIZE 256

extern t_env	g_env_table[2048];

//expander
void		expandlst(t_token *lst);

void		expand(char **variable, bool dollar);

void		expand_variables(char **value);

//expander_utils
char		**split_in_two(const char *string, char c);

char		**split_in_two_by_pointer(const char *string, char *c_ptr);

char		*search_var(char *value, int *i);

int			get_var_size(const char *var, int *index);

void		handle_var_single_quote(t_var *var, char **value, int i);

//environment functions
void		insert(char *key, char *data);

t_env		search(char *key);

char		**get_env(t_env *envtab);

void		display(t_cmd *cmd);

void		free_env(void);

u_int64_t	hash(char *str, int env_len);

//local environment functions
void		local_insert(char *key, char *data, t_env *env_local);

t_env		local_search(char *key, t_env *env_local);

//pathlist struct functions
char		**init_pathlist(void);

void		destroy_pathlist(char **path);

//executor functions
void		executor(t_cmd *cmd);

bool		builtin(t_cmd *cmd);

char		*getfile(char *dir, char *name);

void		setup_fds(t_cmd *cmd);

void		close_all_streams_except_current(t_cmd *cmd);

//parser
t_cmd		*parse(t_token **lst);

t_token		*lex(char const *line);

void		make_redirs(t_token *tkn_lst, t_cmd *cmd);

//heredoc.c
void		heredoc(char *delimiter);
//parsingUtils2
int			open_temp(void);

void		exit_heredoc(int signal);

//parsingUtils
void		make_cmd(t_token *tkn_lst, t_cmd *cmd);

//tokenUtils
int			is_whitespace(char c);

void		skip_whitespace(t_lex *lex_data);

t_token		*new_token(t_token **list);

void		handle_quote(t_token *token, t_lex *lex_data);

//tokenUtils2
void		smoke_pipes(t_token *token, t_lex *lex_data);

void		redir_l(t_token *token, t_lex *lex_data);

void		redir_r(t_token *token, t_lex *lex_data);

void		handle_rest(t_token *token, t_lex *lex_data);

void		free_tkn_lst_array(t_token **tkn_lst);

//repl
void		loop_shell(void);

void		safe_exit(int status);

//builtins
void		cd(t_cmd *cmd);

void		pwd(t_cmd *cmd);

void		ft_export(t_cmd *cmd);

void		unset(t_cmd *cmd);

void		echo(t_cmd *cmd);

//signals
void		define_exec_signals(void);

void		define_input_signals(void);

#endif