#ifndef SCRIPT_H
#define SCRIPT_H

#include <ecl/ecl.h>
#include <vector>

#define DEFUN_NONE(name,fun,args) \
    {\
    void (*_run)() = fun; \
    ecl_def_c_function(c_string_to_object(name),\
            (cl_objectfn_fixed)_run,\
            args); \
    }

#define DEFUN(name,fun,args) \
    ecl_def_c_function(c_string_to_object(name),\
            (cl_objectfn_fixed)fun,\
            args)

class Script
{
public:
    static cl_object lisp(const std::string &call);
private:
    static void Strtrim(char* s);
public:
    static void drawUi();
public:
    static void setDrawUi();
public:
    static void Create();
    static void Destory();
    static void init(int argc, char *argv[]);
private:
    char m_inputBuf[256];
    const char * m_commands;
    bool m_open = false;
    bool m_autoScroll = true;
private:
    Script();
    ~Script();
};

#endif /* SCRIPT_H */
