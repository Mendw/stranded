#include "main.h"
#define INPUT_W 6
#define INPUT_H 8

TreeNode* get_dictionary(char* filename) {
    FILE* file_p = fopen(filename, "r");
    char buffer[21];
    TreeNode* dictionary = NULL;

    while(!feof(file_p)) {
        fgets(buffer, 20, file_p);
        buffer[strcspn(buffer, "\r\n")] = '\0';
        st_insert_value(&dictionary, buffer);
    }

    fclose(file_p);
    return dictionary;
}

bool is_valid_position(int x, int y) {
    return x >= 0 && x < INPUT_W && y >= 0 && y < INPUT_H;
}

char* unravel_path(char letters[INPUT_H][INPUT_W], VectorLLNode* path) {
    int path_len = vector_list_length(path);
    if (path_len == 0) return NULL;

    char* buffer = malloc(sizeof(char) * (path_len + 1));
    
    int i = 0;
    for (; path != NULL; i++, path = path->next) {
        buffer[i] = letters[path->value.y][path->value.x];
    }

    buffer[i] = '\0';
    return buffer;
}

bool _find_words_for(TreeNode* dictionary, char letters[INPUT_H][INPUT_W], WordLLNode** word_list, VectorLLNode** path_ptr, int x, int y, int max_length) {
    if (!is_valid_position(x, y)) return false;
    if (vector_list_has(*path_ptr, x, y)) return false;

    add_vector_value(path_ptr, x, y);

    int word_length = vector_list_length(*path_ptr);
    if (word_length > 3) {
        char* word = unravel_path(letters, *path_ptr);
        int match_type = search_tree(dictionary, word);

        if (match_type == TOTAL_MATCH) {
            add_word_value(word_list, (*path_ptr)->value.x, (*path_ptr)->value.y, word);
        }  else {
            free(word);
            if (match_type == NO_MATCH) return true;
        };
    }

    bool should_pop_path = false;
    if (word_length < max_length) {
        for (int dy = -1; dy < 2; dy++) {
            for (int dx = -1; dx < 2; dx++) {
                if (dx == 0 && dy == 0) continue;
                bool should_pop_path = _find_words_for(dictionary, letters, word_list, path_ptr, x+dx, y+dy, max_length);
                if(should_pop_path) pop_vector_list(path_ptr);
            }
        }
    }

    return true;
}

void repeat_character(const char character, const int ammount) {
    for(int i = 0; i < ammount; i++) putchar(character);
}

void print_doneness(const int x, const int y) {
    int ammount_done = y * INPUT_W + x + 1;
    int total = INPUT_W * INPUT_H;
    float percentage = ((float)ammount_done/(float)total) * 100.0f;

    printf("\r%5.2f%%", percentage);
    int n_bars = (ammount_done * 100) / (total * 2);
    repeat_character('.', n_bars);
}

void find_words_for(TreeNode* dictionary, char letters[INPUT_H][INPUT_W], WordLLNode** word_list, int x, int y, int max_length) {
    VectorLLNode* path = NULL;
    _find_words_for(dictionary, letters, word_list, &path, x, y, max_length);
    print_doneness(x, y);
    free_vector_list(path);
}

WordLLNode* find_words(char letters[INPUT_H][INPUT_W], TreeNode* dictionary, int max_length) {
    WordLLNode* word_list = NULL;
    int n_found = 0;

    for (int i = 0; i < INPUT_H; i++) {
        for(int j = 0; j < INPUT_W; j++) {
            find_words_for(dictionary, letters, &word_list, j, i, max_length);
        }       
    }

    return word_list;
}

void print_words(WordLLNode* words) {
    while (words != NULL) {
        printf("[%d, %d] %s, ", words->start.x + 1, words->start.y + 1, words->word);
        words = words->next;
    }
}

void save_words(WordLLNode* words) {
    FILE* file = fopen("found_words.txt", "w");
    while (words != NULL) {
        fprintf(file, "[%d, %d] %s\n", words->start.x + 1, words->start.y + 1, words->word);
        words = words->next;
    }

    fclose(file);
}

int main() {
    char letters[INPUT_H][INPUT_W];
    FILE* input_file = fopen("input.txt", "r");
    int max_length;

    fscanf(input_file, "%d\n", &max_length);
    for (int i = 0; i < INPUT_H; i++) {
        for (int j = 0; j < INPUT_W; j++) {
            letters[i][j] = getc(input_file);
        }
        getc(input_file);
    }

    fclose(input_file);
    TreeNode* dictionary = get_dictionary("dictionary.txt");
    VectorLLNode* path = NULL;

    WordLLNode* words_found = find_words(letters, dictionary, max_length);
    save_words(words_found);
}