//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 12 16:31:53 2024 by ROOT version 6.30/07
// from TTree nkfadc/nkfadc
// found on file: aa.root
//////////////////////////////////////////////////////////

#ifndef NKFADC_Skel_h
#define NKFADC_Skel_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "Skel_Event.h"

class NKFADC_Skel {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Skel_Event      *Skel_Event;

   // List of branches
   TBranch        *b_Skel_Event;   //!

   NKFADC_Skel(TTree *tree=0);
   virtual ~NKFADC_Skel();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef NKFADC_Skel_cxx
NKFADC_Skel::NKFADC_Skel(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("aa.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("aa.root");
      }
      f->GetObject("nkfadc",tree);

   }
   Init(tree);
}

NKFADC_Skel::~NKFADC_Skel()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t NKFADC_Skel::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t NKFADC_Skel::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void NKFADC_Skel::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Skel_Event = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Skel_Event", &Skel_Event, &b_Skel_Event);
   Notify();
}

Bool_t NKFADC_Skel::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void NKFADC_Skel::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t NKFADC_Skel::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef NKFADC_Skel_cxx
