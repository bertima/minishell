#include "minishell.h"

int strlen_av(char **av)
{
    int i;

    i = 0;
    if (!av)
        return (0);
    while(av[i])
        i++;
    return (i);
}

void dep_fd(char **av)
{
    char *target_dir = NULL;

    if (strlen_av(av) > 2)
    {
        printf("bash: cd: too many arguments\n");
        return;
    }

    if (strlen_av(av) == 1)
    {
        target_dir = getenv("HOME");
        if (!target_dir)
        {
            printf("bash: cd: HOME not set\n");
            return;
        }
    }
    else
    {
        target_dir = av[1];
         if (!target_dir)
        {
            printf("bash: cd: missing argument\n");
            return;
        }
    }
    if (chdir(target_dir) != 0)
    {
        printf("bash: cd: %s: %s\n", target_dir, strerror(errno));
        return;
    }
    char *cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
    }
    else 
    {
        printf("Répertoire actuel : %s\n", cwd);
        free(cwd);
    }
}

/*// Gère CDPATH : si le chemin ne commence pas par / ou ., cherche dans CDPATH
int try_cd_with_cdpath(const char *dir)
{
    if (!dir || dir[0] == '/' || dir[0] == '.') // Absolu ou relatif → pas de CDPATH
        return chdir(dir);

    char *cdpath = getenv("CDPATH");
    if (!cdpath)
        return chdir(dir); // Pas de CDPATH → chemin normal

    char *paths = strdup(cdpath);
    if (!paths)
        return chdir(dir);

    char *token = strtok(paths, ":");
    while (token)
    {
        char *full_path = malloc(strlen(token) + strlen(dir) + 2); // '/' + '\0'
        if (!full_path)
        {
            free(paths);
            return -1;
        }
        sprintf(full_path, "%s/%s", token, dir);

        if (chdir(full_path) == 0)
        {
            printf("%s\n", full_path); // Bash affiche le chemin s'il vient de CDPATH
            free(full_path);
            free(paths);
            return 0;
        }
        free(full_path);
        token = strtok(NULL, ":");
    }

    free(paths);
    return chdir(dir); // Dernière tentative normale
}

void dep_fd(char **av)
{
    char *target_dir = NULL;
    int argc = strlen_av(av);

    if (argc > 2)
    {
        printf("bash: cd: too many arguments\n");
        return;
    }

    // cas cd sans argument → HOME
    if (argc == 1)
    {
        target_dir = getenv("HOME");
        if (!target_dir)
        {
            printf("bash: cd: HOME not set\n");
            return;
        }
    }
    // cas cd -
    else if (strcmp(av[1], "-") == 0)
    {
        target_dir = getenv("OLDPWD");
        if (!target_dir)
        {
            printf("bash: cd: OLDPWD not set\n");
            return;
        }
        printf("%s\n", target_dir); // Bash affiche OLDPWD utilisé
    }
    else
    {
        target_dir = av[1];
    }

    // Sauvegarde du répertoire actuel
    char *prev_dir = getcwd(NULL, 0);
    if (!prev_dir)
    {
        perror("getcwd");
        return;
    }

    // Tentative de changement de dossier (avec support CDPATH)
    if (try_cd_with_cdpath(target_dir) != 0)
    {
        printf("bash: cd: %s: %s\n", target_dir, strerror(errno));
        free(prev_dir);
        return;
    }

    // Mise à jour des variables d’environnement
    char *new_dir = getcwd(NULL, 0);
    if (prev_dir)
        setenv("OLDPWD", prev_dir, 1);
    if (new_dir)
        setenv("PWD", new_dir, 1);

    printf("Répertoire actuel : %s\n", new_dir);

    free(prev_dir);
    free(new_dir);
}
    
int env_len(char **env)
{
    int i = 0;
    while (env && env[i])
        i++;
    return i;
}

// Compare nom=... avec nom
int var_match(const char *env_var, const char *name)
{
    size_t len = strlen(name);
    return (strncmp(env_var, name, len) == 0 && env_var[len] == '=');
}

// Supprime une variable d’environnement
void unset_var(char *name, char ***env)
{
    int len = env_len(*env);
    char **new_env = malloc(sizeof(char *) * len); // max: len-1 + NULL
    int i = 0, j = 0;

    if (!new_env)
        return;

    while ((*env)[i])
    {
        if (!var_match((*env)[i], name)) // si ≠ nom=...
        {
            new_env[j++] = (*env)[i];
        }
        else
        {
            free((*env)[i]); // libère la var supprimée
        }
        i++;
    }

    new_env[j] = NULL;
    free(*env);
    *env = new_env;
}

// La builtin unset
void builtin_unset(char **av, char ***env)
{
    int i = 1;

    while (av[i])
    {
        if (strchr(av[i], '='))
        {
            fprintf(stderr, "unset: '%s': not a valid identifier\n", av[i]);
        }
        else
        {
            unset_var(av[i], env);
        }
        i++;
    }
}*/
