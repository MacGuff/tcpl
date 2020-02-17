#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define VERSION "1.0.0"
#define PROGRAM_NAME "tail"

#define LINE_BUF 100
enum {
    sometimes, quiet, verbose
} flag_verbosity = sometimes;

static int flag_skip = 0;
static unsigned long number = 10L;

static const char *optstring = "n:l:qvVh";
static struct option long_options[] = {
    {"lines", required_argument, 0, 'n'},
    {"quiet", no_argument, 0, 'q'},
    {"silent", no_argument, 0, 'q'},
    {"verbose", no_argument, 0, 'v'},
    {"help",no_argument, 0, 'h'},
    {"version", no_argument, 0, 'V'},
    {0,0,0,0}
};

void help()
{
    puts("Print the last 10 lines of each FILE to standard output.");
    puts("");
    puts("Usage: tail [-lnqvVh]... [FILE]...");
}

void version(void)
{
    puts(VERSION);
}

void parse_opt(int argc, char **argv)
{
    int op;
    char *p;
    while (1) {
        op = getopt_long(argc, argv, optstring, long_options, NULL);
        if(op == -1)
            break;

        switch (op) {
        case 'l':
        case 'n': {
            char *endp;
            p = optarg;
            if (*p == '+') {
                flag_skip = 1;
                p++;
            }

            number = strtol(p, &endp, 10);
            if (*endp != '\0') {
                fprintf(stderr, "invalid number of lines: %s\n", p);
                exit(1);
            }
            break;
        }
        case 'q':
            flag_verbosity = quiet;
            break;
        case 'v':
            flag_verbosity = verbose;
            break;
        case 1:
        case 'h':
            help();
            exit(EXIT_SUCCESS);
            break;
        case 'V':
            version();
            exit(EXIT_SUCCESS);
            break;
        case '?':
            exit(1);
            break;
        default:
            exit (1);
        }
    }
}

char *xgetline(FILE *f)
{
    char *buf;
    long size, allocated;
    int c;

    size =  0;
    buf = malloc(LINE_BUF);
    allocated = LINE_BUF;

    while ((c = getc(f)) != EOF) {
        if (c != '\n') {
            if (size == allocated -1) {
                allocated += LINE_BUF;
                buf = realloc(buf, allocated);
            }
            buf[size++] = c;
        } else {
            buf[size] = '\0';
            return buf;
        }
    }

    return NULL;
}

typedef struct queue_el {
    char *line;
    struct queue_el *next;
} queue_el_t;

typedef struct {
    queue_el_t *first, *last;
    size_t size;
} queue_t;

#define QUEUE_INIT(queue) {\
    queue.first = NULL;\
    queue.last = NULL;\
    queue.size = 0;\
}

void enq(queue_t *q, char *s)
{
    queue_el_t *el = malloc(sizeof(queue_el_t));
    el->line = s;
    el->next = NULL;

    if (q->first == NULL && q->last == NULL) {
        q->first = q->last = el;
        q->size = 1;
    } else {
        q->last->next = el;
        q->last = el;
        q->size++;
    }

}

char *deq(queue_t *q)
{
    queue_el_t *first = q->first;
    char *s = first->line;
    // empty
    if (first == NULL)
        return NULL;

    if(q->first == q->last) {
        q->first = q->last = NULL;
    } else {
        q->first = q->first->next;
    }
    q->size--;
    free(first);
    return s;
}

void tail(FILE *f)
{
    char buf[LINE_BUF];
    int c;
    size_t skipped = 0;
    size_t num_read;
    char *line;
    //long lineno = 0;
    queue_t q;

    QUEUE_INIT(q);

    if(flag_skip) {
        while((c =getc(f)) != EOF) {
            if (c == '\n')
                skipped++;
            if(skipped >= number )
                break;
        }

        while(!feof(f)) {
            num_read = fread(buf, 1, LINE_BUF, f);
            fwrite(buf, 1, num_read, stdout);
        }
    } else {
        while((line = xgetline(f)) != NULL) {
            enq(&q, line);
            if(q.size > number)
                free(deq(&q));
        }

        char *p;
        while(q.size > 0) {
            p = deq(&q);
            puts(p);
            free(p);
        }
    }
}
int main(int argc, char **argv)
{
    FILE *f;
    parse_opt(argc, argv);

    if (optind == argc || (optind == argc - 1 && strcmp(argv[optind], "-") == 0)) {
        if (flag_verbosity == verbose)
            puts("==> stdin <==");
        tail(stdin);
    } else if (optind == argc - 1) {
        f = fopen(argv[optind], "r");
        if (f == NULL) {
            fprintf(stderr, "%s: Can't open file %s\n",
                    PROGRAM_NAME, argv[optind]);
            abort();
        }
        if (flag_verbosity == verbose)
            printf("==> %s <==\n", argv[optind]);
        tail(f);
        fclose(f);
    } else {
        for(; optind < argc; optind++) {
            if (strcmp(argv[optind], "-") == 0) {
                f = stdin;
                if (flag_verbosity != quiet)
                    puts("==> stdin <==");

            } else {
                f = fopen(argv[optind], "r");
                if (!f) {
                    fprintf(stderr, "%s: Can't open file %s\n",
                            PROGRAM_NAME, argv[optind]);
                    abort();

                }
                if (flag_verbosity != quiet)
                    printf("==> %s <==\n", argv[optind]);
            }
            tail(f);
            if (f != stdin)
                fclose(f);
        }
    }

//     printf("flag_verbosity = %d, "
//            "flag_skip = %d, number = %lu\n",
//            flag_verbosity, flag_skip, number
//           );
    return 0;
}
