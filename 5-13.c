#include <stdio.h>

char *optarg = NULL;

int optind = 1;
int optopt = '?';
int opterr = 1;

typedef struct option {
    const char *name;
    int         has_arg;
    int        *flag;
    int         val;
} option_t;

typedef enum order {
    PERMUTE,
    RETURN_IN_ORDER,
    REQUIRE_ORDER
} order_t;

int getopt(int argc, char * const argv[],
           const char *optstring,
           const struct option *longopts, int *longindex)
{
    order_t ordering = PERMUTE;
    static optwhere = 0;

    if (argc == 0 || argv == NULL || optstring == NULL || longopts == NULL)
        return (optopt = '?');
    if (optind >= argc || argv[optind] == NULL)
        return -1;
    if (strcmp(argv[optind], "--") == 0) {
        optind++;
        return -1;
    }

    if (optstring != NULL && (*optstring == '-' || *optstring == '+')) {
        ordering = *optstring == '-' ? RETURN_IN_ORDER : REQUIRE_ORDER;
        optstring++;
    }

    if (optind == 0)
        optind = optwhere = 1;

    if (optwhere == 1) {
        swtich (ordering) {
        case PERMUTE:
            break;
        case RETURN_IN_ORDER:
            break;
        case REQUIRE_ORDER:
            break;
        }

    }
}

int main(void)
{
    return 0;
}
