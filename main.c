#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAP 32

typedef struct {
  size_t len;
  size_t cap;
  char *data;
} Json;

void appendJson(Json *json, char c) {
  if (json->cap <= json->len) {
    json->cap *= 2;
    json->data = realloc(json->data, json->cap);
  }
  json->data[json->len++] = c;
  json->data[json->len] = '\0';
}

int main() {
  int c;
  Json json;
  int value = 0;
  int skip = 0;
  int cont = 1;
  json.data = malloc(INITIAL_CAP);
  json.data[0] = '\0';
  json.len = 0;
  json.cap = INITIAL_CAP;
  appendJson(&json, '{');
  appendJson(&json, '"');
  while ((c = getchar()) && cont) {
    if (c == ':') {
      appendJson(&json, '"');
      appendJson(&json, ':');
      appendJson(&json, ' ');
      appendJson(&json, '"');
      skip = 1;
      value = 1;
    } else if (c == ' ') {
      if (!skip) {
        appendJson(&json, ' ');
      }
    } else if (c == '\n') {
      appendJson(&json, '"');
      appendJson(&json, ',');
      appendJson(&json, '"');
      skip = 0;
      value = 0;
    } else if (c == EOF) {
      appendJson(&json, '"');
      appendJson(&json, '}');
      cont = 0;
    } else {
      appendJson(&json, c);
      skip = 0;
    }
  }
  printf("%s", json.data);
  free(json.data);
}
