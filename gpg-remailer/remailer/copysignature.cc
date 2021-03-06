#include "remailer.ih"

void Remailer::copySignature(ostream &out, string const &boundary)
{
    if (boundary.length())
        out <<
            "Content-Type: text/plain; charset=us-ascii\n"
            "Content-Disposition: inline\n"
            "Content-Transfer-Encoding: quoted-printable\n"
            "\n";

    ifstream sig;
    LogException::open(sig, d_signatureName);

    d_log << level(LOGDEBUG) << "Signature expected on " << d_signatureName <<
                                                                    '\n';

    SigStruct sigStruct = {out, ABSENT};

    out << '\n';

    for_each(istream_iterator<StringLine>(sig), istream_iterator<StringLine>(),
        [&](string const &line)
        {
            signatureFilter(line, sigStruct);
        }
    );

    if 
    (
        (d_sigRequired == GOOD_SIGNATURE && 
            sigStruct.sigType != GOOD_SIGNATURE)
        ||
        (d_sigRequired == SIGNATURE_REQUIRED && 
            sigStruct.sigType == ABSENT)
    )
        throw LogException() << "bad or missing signature in " << 
                d_contentsName << '\n';

    d_log << level(LOGDEBUG) << "Signature check successfully passed\n";

    out << '\n' <<
            boundary << '\n';
}




