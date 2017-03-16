#include "Book.h"
#include "available.h"

Book :: Book () : LibItem () {}

Book :: Book (string id, string title, string subject, string author, LMS * obj) : LibItem (id, title, subject, author, obj) {}
