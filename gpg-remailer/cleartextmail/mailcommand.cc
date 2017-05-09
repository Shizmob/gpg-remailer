#include "cleartextmail.ih"

string ClearTextMail::mailCommand(string const &recipient) const
{
    return "/usr/sbin/sendmail " + recipient;
}
