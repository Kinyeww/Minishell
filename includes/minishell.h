#ifndef MINISHELL_H
# define MINISHELL_H

/* ============ Libraries ===========*/
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

/* ============ Libft_Utils ===========*/
#include "libft_utils.h"

/* ============ parsing ===========*/
#include "parsing.h"

/* =============== env =============== */
typedef struct s_env t_env;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
} t_env;

/* =============== MainStruct =============== */

typedef struct s_data
{
	//head of the list 
	int		fd_copy[2];
	t_env	*envp_list;
	bool	exit_flag;
	int		exit_code; //kinyew using 

} t_data;

/* =================== envp_utils ====================== */

void list_add_back(t_env **envp_list, t_env *new); 
t_env *list_get_last(t_env *envp_list);
void envp_list_clean(t_env **envp_list);
void print_env_list(t_env *list); //debug purpose
void envp_bubble_sort_list(t_env **temp_list);
void create_envp_list(t_env **envp_list, char **envp);

/* ===================== built_ins ==================== */
int execute_built_ins(char **argv, t_data *data);

/* =============== export =============== */
int export(char **argv, t_data *data);
void envp_list_dup(t_env *original_list, t_env **temp_list);
void print_export_list (t_env *list); 
bool is_valid_key(char *argv);
void add_key_to_list(char *argv, t_env *envp_list);

/* =============== unset =============== */
int unset(char **argv, t_data *data);
void envp_list_remove(t_env **envp_list, char *argv_key);

/* =============== env =============== */
int env(char **argv, t_data *data);

/* =============== pwd =============== */
int pwd(char **argv, t_data *data);

/* =============== echo =============== */
int	echo(char **argv, t_data *data);

/* =============== cd =============== */
int cd(char **argv, t_data *data);
char *get_env_value(t_data *data, char *key);
int change_dir(char *path, char *old_path, t_data *data);
void update_env(t_data *data, char *key, char *value);
void print_err_cd(char *path);

/* =============== exit =============== */
int built_in_exit(char **argv, t_data *data);

/* ============ execute_binary ============= */
int execute_binary(char **argv, t_data *data);
char *get_path(char *arg, char *envp_path);

/* ======== execute_binary helper funcitons ========*/
void	print_err_binary(char *file_dir);
void	free_str_arr(char **str_arr);
char	*get_key_value(char *key, t_env *envp_list);
char	*strjoin_envp(char *key, char *value);
char	**create_envp_arr(t_env *envp_list);

/* ==== pipeline setup ====*/
void	create_stdin_stdout_cpy(t_data *data);
int		traverse_pipe_cmd(t_cmd *cmd, t_data *data);

/* ===== execute redirections =====*/
void	dup_restore_fd(t_data *data);
void	print_err_redir(char *file_name);
int 	check_built_in(char *argv1);
int		execute_cmd(t_cmd *cmd, t_data *data);
int		setup_redirections(t_cmd *cmd);

int		built_in_redir_setup(t_cmd *cmd, t_data *data);
int		binary_setup_and_execute(t_cmd *cmd, t_data *data);
int		setup_redirections(t_cmd *cmd);



#endif


