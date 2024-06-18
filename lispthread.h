#ifndef LISPTHREAD_H
#define LISPTHREAD_H

#include <QDebug>
#include <QThread>
#include <QFile>
#include <ecl/ecl.h>

// A macro to create a DEFUN abstraction in C++
// Credit: https://gist.github.com/vwood/662109
#define DEFUN(name,fun,args) \
    ecl_def_c_function(ecl_read_from_cstring(name), \
            (cl_objectfn_fixed)fun, \
            args)

// Define a function to run arbitrary Lisp expressions
inline cl_object lisp(const std::string & call) {
    qDebug() << QString::fromStdString(call);
    return cl_safe_eval(ecl_read_from_cstring(call.c_str()), ECL_NIL, ECL_NIL);
}

class LispThread : public QThread
{
    Q_OBJECT
private:
    const QStringList m_lispExprs;
public:
    LispThread(const QStringList& exprs) :
      m_lispExprs(exprs)
    {
    }

    void run () override
    {
        /*
         * This is the entry point of the threads we have created.
         * These threads have no valid lisp environment. The following
         * routine initializes the lisp and makes it ready for working
         * in this thread.
         */
        ecl_import_current_thread(ECL_NIL, ECL_NIL);

        // Evaluate the S-expressions
        for(auto &expr: m_lispExprs) {
            if (!expr.isEmpty())
                lisp(expr.toStdString());
        }

        /*
         * Finally, when we exit the thread we have to release the
         * resources allocated by the lisp environment.
         */
        ecl_release_current_thread();

        //
        // XXX - I don't know why run() returns but Lisp is still
        //       running.
        //
        qDebug("LispThread::run() returns\n");
    }
};

#endif // LISPTHREAD_H
