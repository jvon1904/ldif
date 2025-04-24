#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define INITIAL_CAP 32

typedef struct {
  size_t len;
  size_t cap;
  char *data;
} String;

void appendString(String *json, char c) {
  if (json->cap <= json->len) {
    json->cap *= 2;
    json->data = realloc(json->data, json->cap);
  }
  json->data[json->len++] = c;
  json->data[json->len] = '\0';
}

void initString(String *str) {
  String val;
  str->data = malloc(INITIAL_CAP);
  str->data[0] = '\0';
  str->len = 0;
  str->cap = INITIAL_CAP;
}

void freeString(String *str) {
  free(str->data);
}

void appendValue(String *json, String *val) {
  int is_int = 1;
  for (int i = 0; i < strlen(val->data); i++) {
    if (!(val->data[i] == '.' || 
        val->data[i] == '0' ||
        val->data[i] == '1' ||
        val->data[i] == '2' ||
        val->data[i] == '3' ||
        val->data[i] == '4' ||
        val->data[i] == '5' ||
        val->data[i] == '6' ||
        val->data[i] == '7' ||
        val->data[i] == '8' ||
        val->data[i] == '9')) {
          is_int = 0; 
        }
  }

  if (!is_int) {
    appendString(json, '"');
  }

  for (int i = 0; i < strlen(val->data); i++) {
    appendString(json, val->data[i]);
  }

  if (!is_int) {
    appendString(json, '"');
  }
}

int main() {
  int c;
  String json;
  initString(&json);
  String val;
  initString(&val);

  // Flags
  int nval = 0;
  int skip = 0;
  int eof = 0;
  int nwln = 0;
  int cmt = 0;

  // Add the first two characters
  appendString(&json, '{');
  appendString(&json, '"');

  while ((c = getchar()) && !eof) {
    if (c == '#') {
      cmt = 1;
    }
    if (c == ':') {
      if (!cmt) {
        if (nval) {
          appendString(&val, c);
        } else  {
          appendString(&json, '"');
          appendString(&json, ':');
          appendString(&json, ' ');
          nval = 1;
          skip = 1;
        }
      }
    } else if (c == ' ') {
      if (!cmt) {
        if (!skip) {
          appendString(&json, ' ');
        }
      }
    } else if (c == '\n') { // refresh everything
      nval = 0;
      appendValue(&json, &val);
      freeString(&val);
      initString(&val);
      skip = 0;
      nwln = 1;
      cmt = 0;
    } else if (c == EOF) {
      appendValue(&json, &val);
      appendString(&json, '}');
      eof = 1;
    } else {
      if (!cmt) {
        if (nwln) {
          appendString(&json, ',');
          appendString(&json, '"');
        }
        if (nval) {
          appendString(&val, c);
        } else {
          appendString(&json, c);
        }
        skip = 0;
        nwln = 0;
      }
    }
  }
  printf("%s", json.data);
  freeString(&json);
  freeString(&val);
}
