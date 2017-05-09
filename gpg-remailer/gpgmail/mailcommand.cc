#include "gpgmail.ih"

string GPGMail::mailCommand(string const &recipient) const
{
    return "/usr/sbin/sendmail " + recipient;
}

