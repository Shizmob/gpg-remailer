#ifndef INCLUDED_GPGMAIL_
#define INCLUDED_GPGMAIL_

#include <string>

#include "../mailer/mailer.h"

namespace FBB
{
    class Log;
}

class Headers;

class GPGMail: public Mailer
{
    std::string const &d_mailName;
    std::string const &d_replyTo;
    std::string d_boundary;

    public:
        GPGMail(FBB::Log &log, Headers &headers, 
                std::string const &mailName, std::string const &replyTo,
                std::string const &step);

    private:
        static std::string makeBoundary();

        virtual void writeMailContents(std::string const &mailData) const;
        virtual std::string mailCommand(std::string const &recipients) const;
        virtual std::string label() const;
};
        
#endif



