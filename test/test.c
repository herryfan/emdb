#include <stdio.h>
#include <string.h>

#include "storage/memory.h"
#include "emdb.h"


#include "test.h"

int spec = 0;
int test_passed = 0;
int test_failed = 0;

int test_emdb ( ) {
  EMDB *db;
  Entry *entry;
  unsigned char ret;

  db = emdb_create_db(&MemoryStorage, 1024, NULL);

  check(db != NULL, "database is created");

  entry = emdb_read(db, (unsigned char *) "foo");

  check(entry == NULL, "entry is null after read");

  ret = emdb_write(db, (unsigned char *) "foo", (unsigned char *) "bar", 4);
  check(ret == 1, "write is successful");

  entry = emdb_read(db, (unsigned char *) "foo");

  check(entry->size == 4, "entry size is 4");
  check(strcmp(entry->ptr, "bar") == 0, "entry is correct");

  emdb_free_entry(entry);

  emdb_destroy_db(db);

  done();
}

int main (int argc, char **argv) {
  if (argc > 1) {
    if ((strcmp(argv[1], "--spec") == 0) || (strcmp(argv[1], "-s") == 0)) {
      spec = 1;
    }
  }

  test(test_memory, "test memory storage");
  test(test_emdb, "test emdb");

  printf("\nPASSED: %d\nFAILED: %d\n", test_passed, test_failed);

  return (test_failed > 0);
}
