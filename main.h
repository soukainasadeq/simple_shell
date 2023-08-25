#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* VVVVVVVVVVVVo */
extern char **environ;

/**
 * struct sep_list_s - BBBB BBBBBBB BBBBBBB BBBBB BBBBB BBBBBBB BB
 * @sep: HHHHHHHH HHHH (;, |, or &)
 * @next: MMMM hhhhhhh hhhhhh hhhhh hhhhh hhhhh hhhhh
 * Description: hhhhhh hhhhh hhhhhh hhhhhhhhh hhhhh hhh
 *              hhhhhhhhhh hhhhh
 *              zzzzzzzzzzz z hhhhhhh hhhhhhhh hhhhhl.
 */
typedef struct sep_list_s
{
	char sep;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_ls_s - mmmmm mmmmmmm mmmmmm mmmmm mmmmm
 *                    zzzzzzz zzzzz
 * @line: ddddddd dddd ddd
 * @next: pppppppp pppppppppp oooo ooo ooo ooooo oooo
 *
 * Description: ddddd bbbbbbbb bbbbbbbbb bbbbbb bbbbbbe
 *              mmmmmm lllll lll
 *              uuuuuuu uuuuuuuuuu uuuu uuuuu uuuuuu uuuu
 */
typedef struct line_ls_s
{
	char *line;
	struct line_ls_s *next;
} line_list;

/**
 * struct shell_dt - Czzz zzzzzzzzzz zzzzzz
 *                     ffffffff ff fffffff ffffff f
 * @argv: ffffffffffff fffffffffff fffffffff ffffgggss
 * @input: Tss ssssssssssss sssssssss sssssss ssssssss
 * @args: dddddddddd ddddddddddd dddddddddd dddddd d
 * @stat: xxxxxxxxxx xxxxxxxx x xxxxxl
 * @counter: kkkkkkkkkk kkkkkkkkkk kkkkkkkkk kkkk kkkkkkkk kkkkkkkkkk kk
 * @_env: hhhhh hhhhhhhhhh hhhhhhhs
 * @pid: ssssssss sssss ssssss sssss
 */
typedef struct shell_dt
{
	char **argv;
	char *input;
	char **args;
	int stat;
	int counter;
	char **_env;
	char *pid;
} shll_comm;

/**
 * struct rvar_ls - vvvvvvv vvvvvvvvvv vvvvvvvvvvvvvv vvvvvvvv
 * @len_var: dddddddd dddddddd dddd
 * @val: ddddddd ddddddddd ddd
 * @len_val: gggggg ggg ggggggue
 * @next: zzzzzzzzzzz zzzzzzzzzzzz zz zzzzzz zzzz zzz
 *
 * Description: zzzzzzzz zzzzzzzzzzzzz zzzzzzzzzzz zzzzzzz zzz
 *              xxxt xxxe
 *              mmmmm mmm mmmm mmmm mmm mmm mmm mmm m
 */
typedef struct rvar_ls
{
	int len_var;
	char *val;
	int len_val;
	struct rvar_ls *next;
} r_var;

/**
 * struct builtin_s - ssssssssss ssssss sss sss
 * @commname: dddddddddd ddddddddddd ddddddddddddd dddddddddd ddd d
 * @f: ppppppp pppppppppp pp pp  nnn nnnn nnn nn nnn nnn nn
 * Description: HHHHHHHHH HHHHHHHHHHHH HHHHHHHHHHH HHHH H HHHHHHHHHHHHHHH
 * ZZZZZZZZZZZZZZ  name of thHNNNNNNNNNNNNNNNNNNNNNNNNN BBBBBBBBBBhhhh hh
 * mmmmmmmmmmmmmmmmmmmmmmmmm mmmmmmmmmmm
 */
typedef struct builtin_s
{
	char *commname;
	int (*f)(shll_comm *datash);
} builtin_t;

/* gd gd gd gd gd g dgd gd*/
sep_list *add_node_en(sep_list **head, char sep);
void free_sp_ls(sep_list **head);
line_list *add_ln_nd_end(line_list **head, char *line);
void free_line_ls(line_list **head);
r_var *add_var_nd(r_var **head, int lvar, char *var, int lval);
void free_value_ls(r_var **head);

/* string hhh h h h h h h h h h*/
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strspn(char *s, char *accept);
char *_strdup(const char *s);
int _strlen(const char *s);
int compare_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_string(char *s);
int get_length(int n);
char *conv_itoa(int n);
int _atoi(char *s);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);

/* hbjhbjvusvv js ghvs jsvvsv shvubsjjs*/
int dupl_chars(char *input, int i);
int sep_oper_error(char *input, int i, char last);
int first_character(char *input, int *i);
void disp_syn_err(shll_comm *data_sh, char *input, int i, int bool);
int ch_syn_err(shll_comm *data_sh, char *input);
char *without_cmt(char *in);
void looping_shll(shll_comm *datash);

/* nbshbjbsbubsjhkhsb s bhs hse */
char *read_line(int *i_eof);

/* zhbzbhz jz  z z z uhk zz jz jz j zj jz jz */
int verify_vars(r_var **h, char *in, char *st, shll_comm *data);
char *rpl_inp(r_var **head, char *input, char *new_input, int nlen);
char *get_environ(const char *name, char **_env);
int display_env(shll_comm *datash);
char *cp_info(char *name, char *value);
void set_env(char *name, char *value, shll_comm *datash);
int _setenv(shll_comm *datash);
int _unsetenv(shll_comm *datash);
int compare_envname(const char *name_env, const char *name_ptr);
void verify_env(r_var **h, char *in, shll_comm *data);
char *replace_str(char *input, shll_comm *datash);

/* pappapapap apapap papappa  */
char *swp_character(char *input, int bool);
void move_nxt(sep_list **list_s, line_list **list_l, shll_comm *datash);
int split_cmds(shll_comm *datash, char *input);
void add_nd(sep_list **head_s, line_list **head_l, char *input);
char **splt_ln(char *input);

/* mamama mamama almamama mamama */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void get_ln(char **lineptr, size_t *n, char *buffer, size_t j);

/* abjhaj abak ,akba kabjknjkks */
int execute_line(shll_comm *datash);
int check_error_command(char *dir, shll_comm *datash);
int command_exec(shll_comm *datash);
int check_cdir(char *path, int *i);
char *_whch(char *cmd, char **_env);
int is_exec(shll_comm *datash);

/* pappapa pappapa ppaps */
void chandir_dor(shll_comm *datash);
void cd_to_dist(shll_comm *datash);
void changedir_prev(shll_comm *datash);
void changedir_to_home(shll_comm *datash);
int changedir_shell(shll_comm *datash);

/* mamama mamama mamamma mma*/
void empty_data(shll_comm *datash);
void set_datashell(shll_comm *datash, char **av);

/* hahbah ha ahbahb bajajajajj j */
int (*get_bltn(char *cmd))(shll_comm *datash);
int exit_sh(shll_comm *datash);

/* Eddhbd hdh hd hd hhhh hhhhd hhhhdpp */
int get_err(shll_comm *datash, int eval);
void get_sigint(int sig);
char *error_get_alias(char **args);
char *err_environ(shll_comm *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *err_path126(shll_comm *datash);
char *conc_err_msg(shll_comm *, char *, char *, char *);
char *err_gcd(shll_comm *datash);
char *error_404(shll_comm *datash);
char *err_shell_exit(shll_comm *datash);

/* zzzz z  zzzzzz zzzzzzypes */
void disp_help_env(void);
void disp_help_setenv(void);
void display_unsetenv(void);
void disp_help_general(void);
void disp_help_exit(void);
void disp_help(void);
void disp_help_alias(void);
void disp_help_cd(void);
int get_hlp(shll_comm *datash);

#endif
