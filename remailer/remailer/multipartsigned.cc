#include "remailer.ih"

    // Third format mentioned in the man-page
bool Remailer::multipartSigned()
{
    ifstream in;
    Msg::open(in, d_decryptedName);

    string line;
    getline(in, line);              // does this line contains multipart/signed
        
    if (line.find("Content-Type: multipart/signed;") != 0)
        return false;               // no, it doesn't

    // It does: find the boundary
    while (!(d_bdry << line))
    {
        if (!getline(in, line))
            msg() << "multipart/signed: no boundary found" << fatal;
    }

    // found the boundary
    d_boundary = "--" + d_bdry[1];
    d_log << level(LOGDEBUG) << "Using boundary " << d_boundary << 
                " in multipart/signed message\n";

                                    // skip until the contents section
    while (getline(in, line) && line.find(d_boundary) != 0)
        ;
    
    if (!in)
        throw Errno(1, "multipart/signed: no boundary separator found");
    
    copyTo(d_multipartSignedName, in);
    in.close();

    ostringstream command;

    command << "--verify " << 
            d_decryptedName << " " << d_multipartSignedName <<
            " 2> " << d_signatureName;
    
    gpg(command.str());

    ofstream out;
    ofopen(d_reencryptName, &out);
    signatureSection(out, d_boundary);

    Msg::open(in, d_multipartSignedName);
    cout << "Processing the multipart signed section " << 
                                                d_multipartSignedName << "\n";

    out << in.rdbuf();

    return true;
}

