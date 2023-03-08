#include "../minishell.h"

static int	ft_strcmp_to_space(char *a, char *b)
{
    int	i;

    i = 0;
    while (a[i] && a[i] != ' ')
    {
        if (a[i] != b[i])
            return (0);
        i++;
    }
    return (1);
}

int get_cmd_pipe(char *cmd)
{
    if (ft_strcmp_to_space("echo", cmd))
        return (1);
    else if (ft_strcmp_to_space("pwd", cmd))
        return (2);
    else if (ft_strcmp_to_space("exit", cmd))
        return (3);
    else if (ft_strcmp_to_space("env", cmd))
        return (4);
    else if (ft_strcmp_to_space("unset", cmd))
        return (5);
    else if (ft_strcmp_to_space("export", cmd))
        return (6);
    else if (ft_strcmp_to_space("cd", cmd))
        return (7);
    return (0);
}

char *get_cmds_path(char *cmds)
{
    int i;
    char *str;

    i = 0;
    while (cmds[i] && cmds[i] != ' ')
        i++;
    str = malloc(sizeof(char) * (i + 1));
    if (!str)
        return (0);
    i = 0;
    while (cmds[i] && cmds[i] != ' ') {
        str[i] = cmds[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char **get_args_cmds(char *cmds)
{
    char **strs;
    int i;

    i = 0;
    while (cmds[i] && cmds[i] != ' ')
        i++;
    i++;
    strs = ft_split(cmds + i, ' ');
    return (strs);
}
