#include "QweakSimRint.hh"

// Standard C and C++ headers
#include <iostream>
#include <cstdlib>

// ROOT headers
#include <TROOT.h>

// Global pointers
QweakSimRint* gQweakSimRint = NULL;

// Pointer to self
QweakSimRint* QweakSimRint::fExists = NULL;


//--------------------------------------------------------------------------
QweakSimRint::QweakSimRint (const char* appClassName, int* argc, char** argv,
		      void* options, int numOptions, bool noLogo)
: TRint (appClassName, argc, argv, options, numOptions, noLogo)
{
  gQweakSimRint = this;

  // Qw-Root command prompt
  SetPrompt("Qw-Root [%d] ");

  // Pointer to self
  fExists = this;
}

//---------------------------------------------------------------------------
QweakSimRint::~QweakSimRint()
{
  // Reset point to self
  if (fExists == this)
    fExists = NULL;
}
