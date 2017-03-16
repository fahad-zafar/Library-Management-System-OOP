#include "DVD.h"

DVD :: DVD () : LibItem () {}

DVD :: DVD (string id, string title, string subject, LMS * obj) : LibItem (id, title, subject, "", obj) {}
