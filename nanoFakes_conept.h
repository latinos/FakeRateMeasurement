//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Jul 23 15:59:15 2018 by ROOT version 6.10/09
// from TTree Events/Events
// found on file: /eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_nAOD_v1_Study2017/DATAl1loose2017/nanoLatino_DoubleMuon_Run2017C-31Mar2018-v1__part0.root
//////////////////////////////////////////////////////////

#ifndef nanoFakes_conept_h
#define nanoFakes_conept_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>

enum {
  e,
  m,
  l, 
  nchannel  // This line should be always last
};

const TString schannel[nchannel] = {
  "e",
  "m",
  "l",
};

const TString lchannel[nchannel] = {
  "e",
  "#mu",
  "l",
};

const int njetet = 7; 
const Double_t muonjetet[njetet] = {10, 15, 20, 25, 30, 35, 45}; 
const Double_t elejetet [njetet] = {10, 15, 20, 25, 30, 35, 45}; 

//reco pt
const int nptbin = 8;
const Double_t ptbins[nptbin+1] = {10, 15, 20, 25, 30, 35, 40, 45, 50};
//cone pt
//const int nptbin = 20;
//const Double_t ptbins[nptbin+1] = {0, 2.5, 5, 7.5, 10, 12.5, 15, 17.5, 20, 22.5, 25, 27.5, 30, 32.5, 35, 37.5, 40, 42.5, 45, 47.5, 50};
// cone pt, wider pt range for plotting
//const int nptbin = 20;
//const Double_t ptbins[nptbin+1] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100};

const int netabin = 5;
const Double_t etabins[netabin+1] = {0, 0.5, 1.0, 1.5, 2.0, 2.5};

//Btag division                                                                        
const int nbtag = 4;
const TString btags[nbtag] = {"", "bveto", "loose", "mediumtight"};
float btagDown = 0.0;
float btagUp = 1.0;
TString btagDirectory = "";

// Z candidate
int   Zlepton1type;
int   Zlepton2type;
float Zlepton1idisoW;
float Zlepton2idisoW;
int   Zdecayflavour;
float m2l;

enum {Loose, Tight};

enum {
  FR_00_QCD,
  FR_01_Zpeak,
  ncutFR
};

const TString scutFR[ncutFR] = {
  "FR/00_QCD",
  "FR/01_Zpeak",
};

enum {
  PR_00,
  ncutPR
};

const TString scutPR[ncutPR] = {
  "PR/00",
};

//------------------------------------------------------------------------------
// nanoFakes_conept constructor
//------------------------------------------------------------------------------
class nanoFakes_conept : public TSelector
{
 public :

  TTreeReader fReader;     //!the tree reader
  TTree*      fChain = 0;  //!pointer to the analyzed TTree or TChain

  void FillAnalysisHistograms(int  icut,
			      int  i);

   void FillLevelHistograms  (int  icut,
			      int  i,
			      bool pass);


   // Fake rate histograms
   //---------------------------------------------------------------------------
   TH2D* h_Muon_loose_pt_eta_bin[ncutFR][njetet][nbtag];
   TH2D* h_Muon_tight_pt_eta_bin[ncutFR][njetet][nbtag];
   TH2D* h_Ele_loose_pt_eta_bin [ncutFR][njetet][nbtag];
   TH2D* h_Ele_tight_pt_eta_bin [ncutFR][njetet][nbtag];

   TH1D* h_Muon_loose_pt_bin[ncutFR][njetet][nbtag];
   TH1D* h_Muon_tight_pt_bin[ncutFR][njetet][nbtag];
   TH1D* h_Ele_loose_pt_bin [ncutFR][njetet][nbtag];
   TH1D* h_Ele_tight_pt_bin [ncutFR][njetet][nbtag];

   TH1D* h_Muon_loose_conv_bin[ncutFR][njetet][nbtag];
   TH1D* h_Muon_tight_conv_bin[ncutFR][njetet][nbtag];
   TH1D* h_Ele_loose_conv_bin [ncutFR][njetet][nbtag];
   TH1D* h_Ele_tight_conv_bin [ncutFR][njetet][nbtag];

   TH1D* h_Muon_loose_eta_bin[ncutFR][njetet][nbtag];
   TH1D* h_Muon_tight_eta_bin[ncutFR][njetet][nbtag];
   TH1D* h_Ele_loose_eta_bin [ncutFR][njetet][nbtag];
   TH1D* h_Ele_tight_eta_bin [ncutFR][njetet][nbtag];


   TH1D* h_Muon_Jet_loose_pt_bin[ncutFR][njetet][nbtag];
   TH1D* h_Muon_Jet_tight_pt_bin[ncutFR][njetet][nbtag];
   TH1D* h_Ele_Jet_loose_pt_bin[ncutFR][njetet][nbtag];
   TH1D* h_Ele_Jet_tight_pt_bin[ncutFR][njetet][nbtag];

   //TH1D* h_Muon_loose_dRlj_bin[ncutFR][njetet][nbtag];
   //TH1D* h_Ele_loose_dRlj_bin[ncutFR][njetet][nbtag];
   //TH1D* h_Muon_tight_dRlj_bin[ncutFR][njetet][nbtag];
   //TH1D* h_Ele_tight_dRlj_bin[ncutFR][njetet][nbtag];

   // Prompt rate histograms
   //---------------------------------------------------------------------------
   TH2D* h_Muon_loose_pt_eta_PR[ncutPR];
   TH2D* h_Muon_tight_pt_eta_PR[ncutPR];
   TH2D* h_Ele_loose_pt_eta_PR[ncutPR];
   TH2D* h_Ele_tight_pt_eta_PR[ncutPR];

   TH1D* h_Muon_loose_pt_PR[ncutPR];
   TH1D* h_Muon_tight_pt_PR[ncutPR];
   TH1D* h_Ele_loose_pt_PR[ncutPR];
   TH1D* h_Ele_tight_pt_PR[ncutPR];

   TH1D* h_Muon_loose_eta_PR[ncutPR];
   TH1D* h_Muon_tight_eta_PR[ncutPR];
   TH1D* h_Ele_loose_eta_PR[ncutPR];
   TH1D* h_Ele_tight_eta_PR[ncutPR];


   // Readers to access the data (delete the ones you do not need)
   //---------------------------------------------------------------------------
   TTreeReaderValue<Float_t> baseW;
   TTreeReaderValue<Float_t> Xsec;
   TTreeReaderValue<Float_t> puWeight;
   TTreeReaderValue<Float_t> Generator_weight;


   // Common variables for 2016, 2017 and 2018
   //---------------------------------------------------------------------------
   TTreeReaderValue<UInt_t> nLepton = {fReader, "nLepton"};
   TTreeReaderArray<Int_t> Lepton_pdgId = {fReader, "Lepton_pdgId"};
   TTreeReaderArray<Float_t> Lepton_pt = {fReader, "Lepton_pt"};
   //TTreeReaderArray<Float_t> Electron_lostHits = {fReader, "Electron_lostHits"};
   TTreeReaderArray<Float_t> Lepton_eta = {fReader, "Lepton_eta"};
   TTreeReaderArray<Float_t> Lepton_phi = {fReader, "Lepton_phi"};

   TTreeReaderArray<Float_t> Jet_btagDeepB = {fReader, "Jet_btagDeepB"};
   TTreeReaderArray<Int_t> Lepton_muonIdx = {fReader, "Lepton_muonIdx"};
   TTreeReaderArray<Int_t> Muon_jetIdx = {fReader, "Muon_jetIdx"};
   TTreeReaderArray<Int_t> Lepton_electronIdx = {fReader, "Lepton_electronIdx"};
   TTreeReaderArray<Int_t> Electron_jetIdx = {fReader, "Electron_jetIdx"};

   TTreeReaderArray<Float_t> Muon_mvaTTH = {fReader, "Muon_mvaTTH"};
   TTreeReaderArray<Float_t> Electron_mvaTTH = {fReader, "Electron_mvaTTH"};

   TTreeReaderArray<Float_t> Electron_miniPFRelIso_all = {fReader, "Electron_miniPFRelIso_all"};
   TTreeReaderArray<Float_t> Muon_miniPFRelIso_all = {fReader, "Muon_miniPFRelIso_all"};

   TTreeReaderValue<UInt_t> nCleanJet = {fReader, "nCleanJet"};
   TTreeReaderArray<Float_t> CleanJet_pt = {fReader, "CleanJet_pt"};
   TTreeReaderArray<Float_t> CleanJet_eta = {fReader, "CleanJet_eta"};
   TTreeReaderArray<Float_t> CleanJet_phi = {fReader, "CleanJet_phi"};

   TTreeReaderValue<UInt_t> nJet = {fReader, "nJet"};
   TTreeReaderArray<Float_t> Jet_pt = {fReader, "Jet_pt"};
   TTreeReaderArray<Float_t> Jet_eta = {fReader, "Jet_eta"};
   TTreeReaderArray<Float_t> Jet_phi = {fReader, "Jet_phi"};
   
   TTreeReaderValue<Float_t> mtw1 = {fReader, "mtw1"};
   TTreeReaderValue<Float_t> PuppiMET_pt = {fReader, "PuppiMET_pt"};
   TTreeReaderValue<Float_t> dphilep1jet1 = {fReader, "dphilep1jet1"};
   TTreeReaderValue<Float_t> Electron_pfRelIso03_all = {fReader, "Electron_pfRelIso03_all"};

   TTreeReaderValue<Bool_t> HLT_Mu8 = {fReader, "HLT_Mu8"};
   TTreeReaderValue<Bool_t> HLT_Mu17 = {fReader, "HLT_Mu17"};
   TTreeReaderValue<Bool_t> HLT_Ele8_CaloIdM_TrackIdM_PFJet30 = {fReader, "HLT_Ele8_CaloIdM_TrackIdM_PFJet30"};
   TTreeReaderValue<Bool_t> HLT_Ele23_CaloIdM_TrackIdM_PFJet30 = {fReader, "HLT_Ele23_CaloIdM_TrackIdM_PFJet30"};


   //Different electron and muon working points
   //---------------------------------------------------------------------------

   // 2016
   ////TTreeReaderArray<Int_t> muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight80x"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cut_WP_Tight80X"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cut_WP_Tight80X_SS"};
   ////TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016"};
   ////TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016_SS"};

   // 2017
   TTreeReaderArray<Int_t> muonTightWP = {fReader, ""}; // just a placeholder -- see nanoFakes_conept.C where WP is actually set/defined
   TTreeReaderArray<Int_t> eleTightWP = {fReader, ""}; // just a placeholder -- see nanoFakes_conept.C where WP is actually set/defined
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90_SS"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90_SS"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight_SS"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight_SS"};

   // 2018
   //TTreeReaderArray<Int_t> muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight_HWWW"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90_SS"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90_SS"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight_SS"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight"};
   //TTreeReaderArray<Int_t> eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight_SS"};

   nanoFakes_conept(TTree * /*tree*/ =0) { }
   virtual ~nanoFakes_conept() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(nanoFakes_conept,0);
};

#endif

#ifdef nanoFakes_conept_cxx


//------------------------------------------------------------------------------
// Init
//------------------------------------------------------------------------------
void nanoFakes_conept::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the reader is initialized.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  
  fReader.SetTree(tree);
}


//------------------------------------------------------------------------------
// Notify
//------------------------------------------------------------------------------
Bool_t nanoFakes_conept::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

#endif // #ifdef nanoFakes_conept_cxx
