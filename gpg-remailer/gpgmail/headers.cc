#include "gpgmail.ih"

string GPGMail::headers() const
{
    string contentHdr;
    contentHdr += "From: " + d_replyTo + "\r\n";
    contentHdr += subject() + "\r\n";
    contentHdr += "Reply-To: " + d_replyTo + "\r\n";
    contentHdr += "Content-Type: multipart/encrypted; "
        "protocol=\"application/pgp-encrypted\"; "
        "boundary=\"" + d_boundary + "\"";
    return contentHdr;
}
