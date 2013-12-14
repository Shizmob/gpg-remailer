#ifndef INCLUDED_SPAWN_
#define INCLUDED_SPAWN_

#include <string>

#include <bobcat/fork>
#include <bobcat/redirector>

#include "../enums/enums.h"

class Spawn: private Enums, public FBB::Fork
{
    int d_in;      // -2 indicates `ignore'
    int d_out;
    int d_err;

    FBB::Redirector d_inRedirector;
    FBB::Redirector d_outRedirector;
    FBB::Redirector d_errRedirector;

    std::string d_command;

    public:
        Spawn(std::string const &command,
            std::string const &in, std::string const &out, 
                                                std::string const &err);
    
    private:
        void childProcess() override;
        void parentProcess() override;
        void childRedirections() override;
};
        
#endif


