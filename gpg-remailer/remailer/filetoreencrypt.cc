#include "remailer.ih"

    // writes reencrypt.x

void Remailer::fileToReencrypt()
{
    if (not step("doc"))
        return;

    IOContext io;

    LogException::open(io.decrypted, d_decryptedName);
    LogException::open(io.toReencrypt, d_reencryptName);

                        // write the file to reencrypt as 
                        //  - a simple one-piece text (simple.cc)
                        //  - text consisting of multiple parts (multipart.cc)
                        //  - text consisting of multiple parts and a detached
                        //    signature (multipartsigned.cc)
    (this->*s_reEncrypt[ encryptionType(io) ])(io);
}


