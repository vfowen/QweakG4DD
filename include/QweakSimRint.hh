#ifndef __QweakSimRint_h__
#define __QweakSimRint_h__

// ROOT headers
#include <TRint.h>
#include <TThread.h>

// Global pointers recognised by CINT
R__EXTERN class QweakSimRint* gQweakSimRint;


/**
 *  \class QweakSimRint
 *  \ingroup QwThreadSafe
 *  \brief A ROOT command line interface
 *
 * The QwRint class implements a ROOT command line interface.  It inherits
 * from the ROOT interactive C++ interpreter TRint.  All functionality available
 * in ROOT is available in this interface.  In particular, all histograms that
 * are defined in memory or in a ROOT file are accessible under the path
 * "/root/ROOT memory", while they are being filled.  All Qweak specific class
 * structures are available in an interactive mode.
 *
 */
class QweakSimRint : public TRint {

  protected:

    static QweakSimRint* fExists;	///< Check whether interface already existing

  public:
    /// \brief Constructor
    QweakSimRint (const char* appClassName, int* argc, char** argv,
		void* options = 0, int numOptions = 0, bool noLogo = kFALSE);

    /// \brief Destructor
    virtual ~QweakSimRint();

}; // class QweakSimRint

#endif // __QweakSimRint_h__
