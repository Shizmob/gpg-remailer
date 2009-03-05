#ifndef _INCLUDED_REMAILER_
#define _INCLUDED_REMAILER_

#include <string>
#include <vector>

#include <bobcat/user>
#include <bobcat/configfile>
#include <bobcat/arg>
#include <bobcat/pattern>
#include <bobcat/log>
#include <bobcat/stat>

class Remailer
{
    enum SigType
    {
        NO_SIGNATURE,
        SIGNATURE_FOUND,
        GOOD_SIGNATURE 
    };

    enum LOGLEVELS
    {
        LOGDEBUG,
        LOGCOMMANDS,
        LOGDEFAULT
    };

    enum EncryptionEnum
    {
        SIMPLE,
        MULTIPART,
        MULTIPART_SIGNED
    };

    FBB::Arg &d_arg;

    bool d_keepFiles;
    bool d_relax;                       // relax permission tests

    FBB::ConfigFile d_config;

    FBB::User d_user;
    FBB::Log d_log;

    SigType d_sigRequired;

    std::string d_configName;
    std::string d_step;
    std::string d_replyTo;
    std::string d_boundary;
    std::string d_subject;
    std::string d_gpgOptions;
    
    std::string d_nr;                   // nr assigned to files
    std::string d_decryptedName;
    std::string d_errName;
    std::string d_mailName;
    std::string d_multipartSignedName;
    std::string d_orgName;
    std::string d_reencryptName;
    std::string d_reencryptedName;
    std::string d_signatureName;

    std::vector<std::string> d_members;
    std::vector<std::string> d_recipients;

    static void (Remailer::*s_reEncrypt[])(std::ostream &, std::istream &);

    public:
        Remailer();
        ~Remailer();
        void preparations();
        void unhex();
        void decrypt();
        void reencrypt();
        void mail();

    private:
        struct FieldStruct
        {
            std::vector<std::string> &dest;
            FBB::Pattern &pattern;
            std::string &configRegex;
        };
        void multiField(std::vector<std::string> &dest, char const *keyWord);
                                            // add members from config file
        static void addField(std::string const &line, FieldStruct &fs);

        void setLog();
        std::string configField(std::string const &field);
        void gpg(std::string const &command);
        void setFilenames();
        bool PGPmessage(std::ostream &out);
        void filter(std::ostream &out);
        void inspect(std::ostream &out, std::string const &line);
        void hexChar(std::ostream &out, std::istream &in);

        void copyToBoundary(std::ostream &out, std::istream &in);

        void signatureSection(std::ostream &out, std::string const &boundary);
        struct SigStruct
        {
            std::ostream &out;
            SigType sigType;
        };
        static void signatureFilter(std::string const &line, 
                                    SigStruct &sigStruct);

        void copyToBoundary(std::string const &destName, std::istream &in);

        void fileToReencrypt();
        void writeReencrypted();
        void setSuffixNr();
        bool step(char const *stepName);

        std::string makeBoundary();
        void writeMail(std::string const &boundary);

        struct MailStruct
        {
            std::string boundary;
            std::string const &mailName;
            std::string const &subject;
            std::string const &replyTo;
            FBB::Log &log;
            bool nomail;
        };
        static void sendMail(std::string const &recipient, 
                                MailStruct const &mailStruct); 

        void rmQuotes(std::string &str) const;
        void ofopen(std::string const &name, std::ofstream *out = 0);
        void testPermissions(std::string const &path, size_t permissions = 
                FBB::Stat::UR | FBB::Stat::UW | FBB::Stat::UX);

        bool foundIn(std::string const &text, std::string const &target) 
                                                                        const;
        bool onlyWS(std::string const &text) const;

        EncryptionEnum encryptionType(std::ostream &out, std::istream &in);
        void multipart(std::ostream &toReencrypt, std::istream &in);
        void multipartSigned(std::ostream &toReencrypt, std::istream &in);
        void simple(std::ostream &toReencrypt, std::istream &in);

        bool findBoundary(std::istream &in);
        bool hasBoundary(std::string const &line, 
                                            std::string const &msgTypeName);

};

inline bool Remailer::foundIn(std::string const &text, 
                              std::string const &target) const
{
    return text.find(target) == 0;
}
        
inline bool Remailer::onlyWS(std::string const &text) const
{
    return text.find_first_not_of(" \t") == std::string::npos;
}
        

#endif
