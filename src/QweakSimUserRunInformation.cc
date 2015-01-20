#include "QweakSimUserRunInformation.hh"

// root includes
#include <TObjString.h>

// user includes
#include "QweakSimVersion.hh"

ClassImp(QweakSimUserRunInformation)

QweakSimUserRunInformation::QweakSimUserRunInformation()
{
  Conditions.AddLast(new TObjString("Revision: " + TString(QWEAKSIM_REVISION)));
  Conditions.AddLast(new TObjString("Root: " + TString(QWEAKSIM_ROOT)));
  Conditions.AddLast(new TObjString("URL: " + TString(QWEAKSIM_URL)));
  Conditions.AddLast(new TObjString("Last changed author: " + TString(QWEAKSIM_LAST_CHANGED_AUTHOR)));
  Conditions.AddLast(new TObjString("Last changed date: " + TString(QWEAKSIM_LAST_CHANGED_DATE)));
  Conditions.AddLast(new TObjString("Last changed revision: " + TString(QWEAKSIM_LAST_CHANGED_REV)));
}

QweakSimUserRunInformation::~QweakSimUserRunInformation()
{ }
