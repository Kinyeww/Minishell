#ifndef MINISHELL_H
# define MINISHELL_H

/* ============ Libraries ===========*/
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ============ Libft_Utils ===========*/
# include "libft_utils.h"

/* ============ parsing ===========*/
# include "parsing.h"
# include "signals.h"
# include "heredoc.h"

/* =============== env =============== */
typedef struct s_env	t_env;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* =============== MainStruct =============== */

typedef struct s_data
{
	int		exit_code;
	int		fd_copy[2];
	t_env	*envp_list;
	bool	exit_flag;

}	t_data;

/* ==== main setup and cleanup utils====*/
void	init_data(t_data *data, char **envp);
void	data_clean(t_data *data);
void	create_stdin_stdout_cpy(t_data *data);

/* ============================ EXECUTION =================================*/

/* ==== pipeline setup ====*/
int		traverse_pipe_cmd(t_cmd *cmd, t_data *data);
int		setup_pipe_parent(int pid, int pipefd[2], int prev_read_end, t_cmd *cmd);
void	setup_pipe_child(int prev_read_end, int pipefd[2], t_cmd *cmd, t_data *data);
int		wait_child(int last_child_pid);

/* ===== execute redirections =====*/
int		execute_cmd(t_cmd *cmd, t_data *data);
int		built_in_redir_setup(t_cmd *cmd, t_data *data, int i);
int		binary_setup_and_execute(t_cmd *cmd, t_data *data);

/* ===== execute redirection setup =====*/
int		setup_redirections(t_cmd *cmd);
int		setup_redir_in(char *file_name);
int		setup_redir_out(char *file_name);
int		setup_redir_append(char *file_name);
int		setup_redit_heredoc(char *heredoc_file);

/* ===== execute redirection helper =====*/
void	dup_restore_fd(t_data *data);
void	print_err_redir(char *file_name);
int		check_built_in(char *argv1);

/* ============ execute_binary ============= */
int		execute_binary(char **argv, t_data *data);
char	*get_path(char *arg, char *envp_path);

/* ======== execute_binary helper funcitons ========*/
void	print_err_binary(char *file_dir);
void	free_str_arr(char **str_arr);
char	*get_key_value(char *key, t_env *envp_list);
char	*strjoin_envp(char *key, char *value);
char	**create_envp_arr(t_env *envp_list);

/* =================== envp_utils ====================== */

void	list_add_back(t_env **envp_list, t_env *new);
t_env	*list_get_last(t_env *envp_list);
void	envp_list_clean(t_env **envp_list);
void	print_env_list(t_env *list); //debug purpose
void	envp_bubble_sort_list(t_env **temp_list);
void	create_envp_list(t_env **envp_list, char **envp);

/* ===================== built_ins ==================== */
int		execute_built_ins(char **argv, t_data *data);

/* =============== export =============== */
int		export(char **argv, t_data *data);
void	envp_list_dup(t_env *original_list, t_env **temp_list);
void	print_export_list(t_env *list);
bool	is_valid_key(char *argv);
void	add_key_to_list(char *argv, t_env *envp_list);

/* =============== unset =============== */
int		unset(char **argv, t_data *data);
void	envp_list_remove(t_env **envp_list, char *argv_key);

/* =============== env =============== */
int		env(char **argv, t_data *data);

/* =============== pwd =============== */
int		pwd(char **argv, t_data *data);

/* =============== echo =============== */
int		echo(char **argv, t_data *data);

/* =============== cd =============== */
int		cd(char **argv, t_data *data);
char	*get_env_value(t_data *data, char *key);
int		change_dir(char *path, char *old_path, t_data *data);
void	update_env(t_data *data, char *key, char *value);
void	print_err_cd(char *path);

/* =============== exit =============== */
int		built_in_exit(char **argv, t_data *data);

/* ============================ PARSING ===================================== */

/* =============== heredoc ================ */
int		prepare_heredoc(t_cmd *cmds, t_env *envp, int last_status);
int		read_heredoc(t_redir *redir, t_env *envp, int last_status);
int		process_heredoc_q(t_cmd *cmds);
int		run_heredoc_with_signal(t_cmd *cmds, t_data *data);
char	*remove_quotes(char *str);
int		has_quotes(char *str);
char	*create_hd_filename(void);
int		open_hd_file(t_redir *redir);
char	*expand_heredoc(char *line, t_env *envp, int last_status);
int		expand_heredoc_line(char **line, t_env *envp, int last_status);
int		handle_heredoc_eof(t_redir *redir, int fd);
int		process_heredoc_line(t_redir *redir, char **line,
			t_env *envp, int last_status);

/* =============== expansion ============== */
int		expand_cmds(t_cmd *cmd, t_env *envp, int last_status);
char	*expand_var(char *str, int *i, t_env *envp, int last_status);
char	*get_env_val(char *name, t_env *envp);
int		is_var_char(char c);
int		ft_varlen(char *str);
char	*append_char(char *result, char c);
char	*append_str(char *result, char *to_add);
int		expand_argv(t_cmd *cmd, t_env *envp, int last_status);
int		expand_redir(t_cmd *cmd, t_env *envp, int last_status);

/* ================ parsing =============== */
void	assign_meaning(t_token *tokens);

/* =============== tokenising ============== */
t_token	*tokenising(char *line);
void	skip_spaces(char *line, int *i);
int		get_next_token_len(char *line, int i);
t_token	*handle_unclosed_quote(t_token *head);
int		add_token_to_list(t_token **head, t_token **last, char *str, int len);
int		is_operator(char c);
int		get_operator_len(char *line, int i);
int		get_token_length(char *line, int index);
t_token	*new_token(char *start, int len);

#endif
