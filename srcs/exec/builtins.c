/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c		                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 22:22:44 by ******           #+#    #+#              */
/*   Updated: 2024/07/22 00:43:38 by ******           ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int builtin_cd(t_cmd *cmd) {
    char *home_dir;
    char *oldpwd;
    char cwd[1024];
    char *path;

    // If no argument, cd to the HOME directory
    if (cmd->args[1] == NULL) {
        home_dir = get_env_var(cmd->envp, "HOME");
        if (home_dir == NULL) {
            ft_printf("cd: HOME not set\n");
            return 1;
        }
        path = home_dir;
    } else if (ft_strcmp(cmd->args[1], "-") == 0) {
        // Handle 'cd -' to change to the previous directory
        oldpwd = get_env_var(cmd->envp, "OLDPWD");
        if (oldpwd == NULL) {
            ft_printf("cd: OLDPWD not set\n");
            return 1;
        }
        path = oldpwd;
    } else {
        // Check if the path starts with '~'
        if (cmd->args[1][0] == '~') {
            home_dir = get_env_var(cmd->envp, "HOME");
            if (home_dir == NULL) {
                ft_printf("cd: HOME not set\n");
                return 1;
            }
            // Allocate enough space for the expanded path
            path = malloc(ft_strlen(home_dir) + ft_strlen(cmd->args[1]));
            if (path == NULL) {
                perror("malloc");
                return 1;
            }
            // Concatenate the home directory with the rest of the path (skip the '~')
            ft_strcpy(path, home_dir);
            ft_strlcat(path, cmd->args[1] + 1, ft_strlen(home_dir) + ft_strlen(cmd->args[1]));
        } else {
            path = cmd->args[1];
        }
    }

    // Change directory to the expanded path
    if (chdir(path) != 0) {
        perror("cd");
        if (cmd->args[1][0] == '~') free(path); // Free memory if '~' expansion was used
        return 1;
    }
    
    // Update the OLDPWD and PWD environment variables
    oldpwd = get_env_var(cmd->envp, "PWD");
    if (oldpwd != NULL) {
        set_env_var(cmd->envp, "OLDPWD", oldpwd);
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        set_env_var(cmd->envp, "PWD", cwd);
    } else {
        perror("getcwd");
        return 1;
    }

    // Free memory if '~' expansion was used
    if (cmd->args[1] && cmd->args[1][0] == '~') {
        free(path);
    }

    return 0;
}


int builtin_echo(t_cmd *cmd) {
    int newline = 1;
    int i = 1;

    if (ft_strncmp(cmd->args[1], "-n", 3) == 0) {
        newline = 0;
        i = 2;
    }

    for (; cmd->args[i]; i++) {
        ft_printf("%s", cmd->args[i]);
        if (cmd->args[i + 1] != NULL) { 
            ft_printf(" ");
        }
    }

    if (newline) {
        ft_printf("\n");
    }

    return 0;
}

int builtin_pwd() {
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        ft_printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    return 0;
}

int builtin_env(t_cmd *cmd) {
    for (int i = 0; cmd->envp[i] != NULL; i++) {
        ft_printf("%s\n", cmd->envp[i]);
    }
	return (0);
}

int builtin_export(t_cmd *cmd) {
    int i = 1;

    while (cmd->args[i]) {
        char *name = ft_strdup(cmd->args[i]);
        char *value = ft_strchr(name, '=');

        if (value) {
            *value = '\0';
            value++;
            set_env_var(cmd->envp, name, value);
               
        } else {
            if (getenv(name)) {
            } else {
                ft_printf("export: %s: not found\n", name);
                return 1; 
            }
        }
        i++;
    }

    return 0; 
}

int builtin_unset(t_cmd *cmd) {
    
     if (cmd->args[0] == NULL || *(cmd->args[0]) == '\0' || ft_strchr(cmd->args[0], '=') != NULL) {
        ft_printf("unsetenv: invalid variable name\n");
        return -1;
    }

    size_t len = ft_strlen(cmd->args[1]);
    char **env = cmd->envp;
    char **next_env = cmd->envp;

    while (*env) {
        if (ft_strncmp(*env, cmd->args[1], len) == 0 && (*env)[len] == '=') {
            env++;
            continue;
        }
        *next_env++ = *env++;
    }
    *next_env = NULL;
    return 0;
}

int custom(t_cmd *cmd)
{
    char *full_path;
        if (resolve_full_path(cmd, &full_path) == 1) {
            
            ft_printf("Command not found: %s\n", cmd->args[0]);
            return 127;
        }
        
        if (execve(full_path, cmd->args, cmd->envp) == 1) {
            
            free(full_path);
            perror("execve");
            return 1;
        }
        free(full_path);
    
    return(0);
}