#ifndef heapboard_h
#define heapboard_h

struct thread;
struct comment;

typedef struct comment {
    struct comment *next;
    
    int index;
    char *text;

    void (*create_func)(struct comment *);
    void (*delete_func)(struct comment *);
} comment_t;

typedef struct thread {
    struct thread *prev;
    struct thread *next;

    int index;
    char *author;
    char *title;
    char *content;

    char size;
    struct comment *comments;
    
    void (*create_func)(struct thread *);
    void (*delete_func)(struct thread *);
} thread_t;

#endif
