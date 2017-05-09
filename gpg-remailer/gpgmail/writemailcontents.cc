#include "gpgmail.ih"

void GPGMail::writeMailContents(string const &mailData) const
{
    ifstream in;
    Exception::open(in, mailData);

    ofstream out;
    Exception::open(out, d_mailName);

    out << headers() << // create the mail to send.
        "\r\n"
        "--" << d_boundary << "\r\n"
        "Content-Type: application/pgp-encrypted\r\n"
        "Content-Transfer-Encoding: 7bit\r\n"
        "\r\n"
        "Version: 1\r\n"
        "\r\n"
        "--" << d_boundary << "\r\n"
        "Content-Type: application/octet-stream; name=gpg.asc\r\n"
        "Content-Transfer-Encoding: 7bit\r\n"
        "\r\n" <<
        in.rdbuf() << "\r\n"
        "\r\n"
        "--" << d_boundary << "--\r\n";
}





