#include "remailer.ih"

Remailer::~Remailer()
{
    if (d_keepFiles)
        return;

    d_log << level(LOGDEFAULT) << 
            "Removing all temporary files\n";

    unlink(d_decryptedName.c_str());
    unlink(d_errName.c_str());
    unlink(d_mailName.c_str());
    unlink(d_multipartSignedDataName.c_str());
    unlink(d_contentsName.c_str());
    unlink(d_reencryptName.c_str());
    unlink(d_reencryptedName.c_str());
    unlink(d_signatureName.c_str());
    unlink(d_hdrsName.c_str());
}
