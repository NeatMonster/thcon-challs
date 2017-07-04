#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "heapboard.h"

int threads;

void delete_thread(thread_t *thread) {
    comment_t *comment, *next_comment;
    
    comment = thread->comments;
    while (comment) {
        next_comment = comment->next;
        comment->delete_func(comment->text);
        comment->delete_func(comment);
        comment = next_comment;
    }

    free(thread->author);
    free(thread->title);
    free(thread->content);
    free(thread);
}

void delete_comment(comment_t *comment) {
    free(comment);
}

void action_delete(thread_t *thread) {
    comment_t *comment;

    if (thread->size > 0) {
        comment = thread->comments;
        while (comment) {
            comment->delete_func = delete_comment;
            comment = comment->next;
        }
    }

    //if (thread->prev)
    thread->prev->next = thread->next;
    //if (thread->next)
    thread->next->prev = thread->prev;
    thread->delete_func(thread);
}

void action_modify(thread_t *thread) {
    memset(thread->author, 0, 0x100);
    memset(thread->title, 0, 0x100);

    printf("Author: ");
    fgets(thread->author, 250, stdin);
    int len = strlen(thread->author);
    thread->author[len - 1] = '\0';

    printf("Title: ");
    fgets(thread->title, 250, stdin);
    len = strlen(thread->title);
    thread->title[len - 1] = '\0';
}

void action_comment(thread_t *thread) {
    comment_t *comment, *new_comment;

    ++thread->size;
    new_comment = (comment_t *)malloc(sizeof(comment_t));
    new_comment->next = NULL;
    new_comment->index = thread->size;
    new_comment->text = (char *)malloc(120);

    printf("Comment: ");
    fgets(new_comment->text, 100, stdin);
    int len = strlen(new_comment->text);
    new_comment->text[len - 1] = '\0';

    if (thread->comments) {
        comment = thread->comments;
        while (comment->next)
            comment = comment->next;
        comment->next = new_comment;
    } else
        thread->comments = new_comment;
}

void action_options(thread_t *thread) {
    int ret = 0;
    char action;

    while (!ret) {
        printf("\nWhat do you want to do?\n");
        printf("  1. Comment in the thread\n");
        printf("  2. Modify the thread\n");
        printf("  3. Delete the thread\n");
        printf("  4. Go back to main menu\n");
        printf("\n> ");
        action = getchar();
        while (getchar() != '\n');
        printf("\n");

        ret = 1;
        switch (action) {
        case '1':
            action_comment(thread);
            break;
        case '2':
            action_modify(thread);
            break;
        case '3':
            action_delete(thread);
            break;
        case '4':
            break;
        default:
            ret = 0;
            printf("Invalid action!\n");
            break;
        }
    }
}

void action_display(thread_t **board) {
    int ret = 0, index;
    thread_t *thread;
    comment_t *comment;

    while (!ret) {
        printf("\nWhich thread would you like to see?\n");
        printf("\n> ");
        scanf("%d", &index);
        while (getchar() != '\n');
        printf("\n");

        thread = *board;
        while (thread) {
            if (thread->index == index) {
                ret = 1;

                printf("-------------------------------------------------------\n");
                printf("| %5d | %-20s | %-20s |\n", thread->index, thread->author, thread->title);
                printf("-------------------------------------------------------\n");
                printf("| %-51s |\n", thread->content);
                printf("-------------------------------------------------------\n");

                comment = thread->comments;
                if (!comment)
                    printf("| NO COMMENTS IN THIS THREAD                          |\n");
                while (comment) {
                    printf("| %-51s |\n", comment->text);
                    comment = comment->next;
                }
                printf("-------------------------------------------------------\n");

                action_options(thread);
            }
            thread = thread->next;
        }

        if (!ret)
            printf("Invalid index!\n");
    }
}

void action_read(thread_t **board) {
    thread_t *thread;

    if (*board) {
        printf("-------------------------------------------------------\n");
        printf("| %s | %-20s | %-20s |\n", "index", "author", "title");
        printf("-------------------------------------------------------\n");

        thread = *board;
        while (thread) {
            printf("| %5d | %-20s | %-20s |\n", thread->index, thread->author, thread->title);
            thread = thread->next;
        }
        printf("-------------------------------------------------------\n");

        action_display(board);
    } else
        printf("The board is empty!\n");
}

void fill_thread(thread_t *thread) {
    char buf[0x2000] = { 0 };

    printf("Author: ");
    fgets(thread->author, 250, stdin);
    int len = strlen(thread->author);
    thread->author[len - 1] = '\0';

    printf("Title: ");
    fgets(thread->title, 250, stdin);
    len = strlen(thread->title);
    thread->title[len - 1] = '\0';

    printf("Content: ");
    fgets(buf, 8000, stdin);
    len = strlen(buf);
    thread->content = (char *)malloc(len);
    memcpy(thread->content, buf, len);
    len = strlen(thread->content);
    thread->content[len - 1] = '\0';
}

void init_thread(thread_t *thread) {
    ++threads;

    thread->prev = NULL;
    thread->next = NULL;

    thread->index = threads;
    thread->author = (char *)malloc(0x100);
    thread->title = (char *)malloc(0x100);
    thread->content = NULL;

    thread->size = 0;
    thread->comments = NULL;

    thread->delete_func = delete_thread;
}

int is_full(thread_t *board) {
    int threads = 0;
    thread_t *thread;

    if (board) {
        thread = board;
        while (thread) {
            ++threads;
            thread = thread->next;
        }
        return threads >= 8;
    } else
        return 0;
}

void action_write(thread_t **board) {
    thread_t *thread, *new_thread;

    if (is_full(*board)) {
        printf("The board is full!\n");
        return;
    }

    new_thread = (thread_t *)malloc(sizeof(thread_t));
    init_thread(new_thread);
    fill_thread(new_thread);

    if (*board) {
        thread = *board;
        while (thread->next)
            thread = thread->next;
        thread->next = new_thread;
        new_thread->prev = thread;
    } else
        *board = new_thread;
}

void print_header() {
    printf(" _    _                  ____                      _ \n");
    printf("| |  | |                |  _ \\                    | |\n");
    printf("| |__| | ___  __ _ _ __ | |_) | ___   __ _ _ __ __| |\n");
    printf("|  __  |/ _ \\/ _` | '_ \\|  _ < / _ \\ / _` | '__/ _` |\n");
    printf("| |  | |  __/ (_| | |_) | |_) | (_) | (_| | | | (_| |\n");
    printf("|_|  |_|\\___|\\__,_| .__/|____/ \\___/ \\__,_|_|  \\__,_|\n");
    printf("                  | |                                \n");
    printf("                  |_|                                \n");
}

void handle_fault(int);

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    signal(SIGSEGV, handle_fault);

    int ret = 0;
    char action;
    thread_t *board = NULL;
    threads = 0;

    print_header();
    while (!ret) {
        printf("\nWhat do you want to do?\n\n");
        printf("  1. Create a new thread\n");
        printf("  2. Display all threads\n");
        printf("  3. Exit the board\n");
        printf("\n> ");
        action = getchar();
        while (getchar() != '\n');
        printf("\n");
        switch (action) {
        case '1':
            action_write(&board);
            break;
        case '2':
            action_read(&board);
            break;
        case '3':
            printf("Exiting...\n");
            ret = 1;
            break;
        default:
            printf("Invalid action!\n");
            break;
        }
    }

    exit(0);
}

void handle_fault(int signum) {
    system("/usr/bin/clear");
    main(0, NULL);
}
