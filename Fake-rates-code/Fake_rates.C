#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <TLorentzVector.h>
#include "TMath.h"
using namespace std;

Double_t deltaPhi(Double_t Phi0, Double_t Phi1) {
        Double_t dphi = Phi0-Phi1;
        while (dphi >= TMath::Pi()) dphi -= TMath::TwoPi();
        while (dphi < -TMath::Pi()) dphi += TMath::TwoPi();
        return dphi;
      } 

void Fake_rates(TString sample,  TString channel, TString year, TString btagWP) {

  //if (argc<4) {
  //  printf('Ejemplo: root -b -q "Fake_rates.C(\"nanoLatino_SingleElectron_Run2017F-31Mar2018-v1__part50.root\" , \"mu\" , \"2017\" , \"loose\")" ');
  //  return -1;
  // }

  //Options
  //--------------------------------------------------------------------------------------------------------------------------------------
  if (channel != "ele" && channel != "mu") {printf("ERROR: Channel must be ele or mu \n");return -1;}
  if (year!="2016"&&year!="2017"&&year!="2018"){cout<<"ERROR: Year is not valid!"<<endl;return -1;}
  if (btagWP!="loose"&&btagWP!="mediumtight"&&btagWP!="medium"&&btagWP!="tight"&&btagWP!="bveto"&&btagWP!="none"){cout<<"ERROR: BtagWP not valid!"<<endl;return -1;}

  // Import the nanoLatino Tree
  //--------------------------------------------------------------------------------------------------------------------------------------
  TChain* tree = new TChain("Events");
  //DATA
  TString myFolderData ="";
  if(year=="2018") myFolderData = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2018_102X_nAODv4_14Dec_Full2018v4/DATAl1loose2018__fakeSel/";  //2018 
  if(year=="2017") myFolderData = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_nAOD_v1_Full2017v2/DATAl1loose2017v2__DATACorr2017__fakeSel/"; //2017
  if(year=="2016") myFolderData = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2016_102X_nAODv4_Full2016v4/DATAl1loose2016__fakeSel/"; //2016  
  //MC
  TString myFolderMC ="";
  if(year=="2018") myFolderMC = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Autumn18_102X_nAODv4_GTv16_Full2018v4/MCl1loose2018__MCCorr2018__fakeSelMC/"; //2018  
  if(year=="2018") myFolderMC = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Autumn18_102X_nAODv4_GTv16_Full2018v4/MCl1loose2018__MCCorr2018/"; //2018 Wjets 
  if(year=="2017"&&sample.Contains("DY")) myFolderMC = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Fall2017_nAOD_v1_Full2017v2/MCl1loose2017v2__MCCorr2017__btagPerEvent__fakeSelMC/";  //2017
  if(year=="2017"&&sample.Contains("WJets")) myFolderMC = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Fall2017_nAOD_v1_Full2017v2/MCl1loose2017v2__MCCorr2017__btagPerEvent/";  //2017
  if(year=="2017"&&sample.Contains("GJets")) myFolderMC = "/eos/cms/store/user/yiiyama/HWWNano/Fall2017_nAOD_v1_Full2017v2/MCl1loose2017v2__MCCorr2017/";  //2017  gamma +jets samples
  if(year=="2016") myFolderMC = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Summer16_102X_nAODv4_Full2016v4/MCl1loose2016__MCCorr2016__fakeSelMC/"; //2016

  TString dirname = "FR_"+year+"_12jun";
  TString subdirname =dirname; subdirname.ReplaceAll("FR","outputsFR");subdirname+="_"+btagWP+"btag";
  TString outputdir ="/afs/cern.ch/work/a/alvareza/public/CMSSW_9_4_7/src/PlotsConfigurations/Configurations/Fake-rates-code/"+dirname+"/"+subdirname+"/";
  system("mkdir -p "+outputdir);

  TString file = "";
  bool isData = false; bool isQCD =false; bool isMC =false;
  double weight = 1;
  if(sample.Contains("Run")){ file = myFolderData + sample ; isData=true; }
  else{ file = myFolderMC +sample ; isMC=true; if(sample.Contains("QCD"))isQCD=true; }
 
  TFile* root_output = new TFile(outputdir +"output_" +channel+"_"+ sample, "recreate");
  /////Ele//Trigger//////////////////////
  TString eletrig="8";
  if(year=="2016")eletrig="12";
  //BTagWP///////////////////////////////
  double btagdown; double btagup;
  bool useDeepCSV=true;
  //DeepCSV 
  if(useDeepCSV==true){  
    if(btagWP=="bveto"){btagdown=0;btagup=0.1522;} 
    if(btagWP=="loose"){btagdown=0.1522;btagup=0.4941;}  
    if(btagWP=="medium"){btagdown=0.4941;btagup=0.8001;} 
    if(btagWP=="tight"){btagdown=0.8001;btagup=1;}  
    if(btagWP=="mediumtight"){btagdown=0.4941;btagup=1;}
  }  
  ////////////////////////////////////////////

  cout<<file<<endl;
  if(ifstream(file))tree->Add(file);
  else{ cout<<"ERROR: File not loaded"<<endl; return 0;}
     
  // Import the variables
  //--------------------------------------------------------------------------------------------------------------------------------------
  Int_t nLepton;
  tree->SetBranchAddress("nLepton",&nLepton);
  Int_t nCleanJet;
  tree->SetBranchAddress("nCleanJet",&nCleanJet);
  Int_t Lepton_muonIdx[200];
  tree->SetBranchAddress("Lepton_muonIdx",&Lepton_muonIdx);
  Int_t Lepton_electronIdx[200];
  tree->SetBranchAddress("Lepton_electronIdx",&Lepton_electronIdx);
  Int_t CleanJet_jetIdx[200];
  tree->SetBranchAddress("CleanJet_jetIdx",&CleanJet_jetIdx);
  Int_t Electron_jetIdx[200];
  tree->SetBranchAddress("Electron_jetIdx",&Electron_jetIdx);
  Int_t Muon_jetIdx[200];
  tree->SetBranchAddress("Muon_jetIdx",&Muon_jetIdx);
  Int_t Lepton_pdgId[200];
  tree->SetBranchAddress("Lepton_pdgId",&Lepton_pdgId);
  Bool_t Lepton_isTightElectron_mvaFall17Iso_WP90[200];
  if (tree->GetBranch("Lepton_isTightElectron_mvaFall17Iso_WP90"))  tree->SetBranchAddress("Lepton_isTightElectron_mvaFall17Iso_WP90",&Lepton_isTightElectron_mvaFall17Iso_WP90);
  Bool_t Lepton_isTightElectron_mvaFall17Iso_WP90_SS[200];
  if (tree->GetBranch("Lepton_isTightElectron_mvaFall17Iso_WP90_SS"))tree->SetBranchAddress("Lepton_isTightElectron_mvaFall17Iso_WP90_SS",&Lepton_isTightElectron_mvaFall17Iso_WP90_SS);
  Bool_t Lepton_isTightElectron_mvaFall17V1Iso_WP90[200];
  if (tree->GetBranch("Lepton_isTightElectron_mvaFall17V1Iso_WP90"))tree->SetBranchAddress("Lepton_isTightElectron_mvaFall17V1Iso_WP90",&Lepton_isTightElectron_mvaFall17V1Iso_WP90);
  Bool_t Lepton_isTightElectron_mva_90p_Iso2016[200];
  if (tree->GetBranch("Lepton_isTightElectron_mva_90p_Iso2016"))tree->SetBranchAddress("Lepton_isTightElectron_mva_90p_Iso2016",&Lepton_isTightElectron_mva_90p_Iso2016);
  Bool_t Lepton_isTightElectron_cut_WP_Tight80X[200];
  if (tree->GetBranch("Lepton_isTightElectron_cut_WP_Tight80X"))tree->SetBranchAddress("Lepton_isTightElectron_cut_WP_Tight80X",&Lepton_isTightElectron_cut_WP_Tight80X);
  Bool_t Lepton_isTightElectron_mva_90p_Iso2016_SS[200];
  if (tree->GetBranch("Lepton_isTightElectron_mva_90p_Iso2016_SS"))tree->SetBranchAddress("Lepton_isTightElectron_mva_90p_Iso2016_SS",&Lepton_isTightElectron_mva_90p_Iso2016_SS);
  Bool_t Lepton_isTightElectron_cut_WP_Tight80X_SS[200];
  if (tree->GetBranch("Lepton_isTightElectron_cut_WP_Tight80X_SS"))tree->SetBranchAddress("Lepton_isTightElectron_cut_WP_Tight80X_SS",&Lepton_isTightElectron_cut_WP_Tight80X_SS);
  Bool_t Lepton_isTightMuon_cut_Tight_HWWW[200];
  if (tree->GetBranch("Lepton_isTightMuon_cut_Tight_HWWW"))tree->SetBranchAddress("Lepton_isTightMuon_cut_Tight_HWWW",&Lepton_isTightMuon_cut_Tight_HWWW);
  Bool_t Lepton_isTightMuon_cut_Tight80x[200];
  if (tree->GetBranch("Lepton_isTightMuon_cut_Tight80x"))tree->SetBranchAddress("Lepton_isTightMuon_cut_Tight80x",&Lepton_isTightMuon_cut_Tight80x);
  Bool_t Electron_mvaFall17Iso_WP90[200];
  if (tree->GetBranch("Electron_mvaFall17Iso_WP90"))tree->SetBranchAddress("Electron_mvaFall17Iso_WP90",&Electron_mvaFall17Iso_WP90);
  Bool_t Electron_mvaFall17V1Iso_WP90[200];
  if (tree->GetBranch("Electron_mvaFall17V1Iso_WP90"))tree->SetBranchAddress("Electron_mvaFall17V1Iso_WP90",&Electron_mvaFall17V1Iso_WP90);
  Bool_t Electron_mva_90p_Iso2016[200];
  if (tree->GetBranch("Electron_mva_90p_Iso2016"))tree->SetBranchAddress("Electron_mva_90p_Iso2016",&Electron_mva_90p_Iso2016);
  Int_t Electron_cutBased[200];
  tree->SetBranchAddress("Electron_cutBased",&Electron_cutBased);
  Float_t Electron_dxy[200];
  tree->SetBranchAddress("Electron_dxy",&Electron_dxy);
  Float_t Electron_dz[200];
  tree->SetBranchAddress("Electron_dz",&Electron_dz);
  Float_t Electron_pfRelIso03_all[200];
  tree->SetBranchAddress("Electron_pfRelIso03_all",&Electron_pfRelIso03_all);
  Float_t Muon_dxy[200];
  tree->SetBranchAddress("Muon_dxy",&Muon_dxy);
  Float_t Muon_dz[200];
  tree->SetBranchAddress("Muon_dz",&Muon_dz);
  Float_t Lepton_pt[200];
  tree->SetBranchAddress("Lepton_pt",&Lepton_pt);
  Float_t Lepton_eta[200];
  tree->SetBranchAddress("Lepton_eta",&Lepton_eta);
  Float_t Lepton_phi[200];
  tree->SetBranchAddress("Lepton_phi",&Lepton_phi);
  Float_t MET_pt;
  tree->SetBranchAddress("MET_pt",&MET_pt);
  Float_t PuppiMET_pt;
  tree->SetBranchAddress("PuppiMET_pt",&PuppiMET_pt);
  Float_t MET_phi;
  tree->SetBranchAddress("MET_phi",&MET_phi);
  Float_t mtw1;
  tree->SetBranchAddress("mtw1",&mtw1);
  Float_t TkMET_pt;
  tree->SetBranchAddress("TkMET_pt",&TkMET_pt);
  Float_t TkMET_phi;
  tree->SetBranchAddress("TkMET_phi",&TkMET_phi);
  Float_t Jet_btagCSVV2[200];
  tree->SetBranchAddress("Jet_btagCSVV2",&Jet_btagCSVV2);
  Float_t Jet_btagDeepB[200];
  tree->SetBranchAddress("Jet_btagDeepB",&Jet_btagDeepB);
  Float_t CleanJet_pt[200];
  tree->SetBranchAddress("CleanJet_pt",&CleanJet_pt);
  Float_t Jet_pt[200];
  tree->SetBranchAddress("Jet_pt",&Jet_pt);
  Float_t CleanJet_eta[200];
  tree->SetBranchAddress("CleanJet_eta",&CleanJet_eta);
  Float_t CleanJet_phi[200];
  tree->SetBranchAddress("CleanJet_phi",&CleanJet_phi);
  Int_t Jet_partonFlavour[200];
  if (tree->GetBranch("Jet_partonFlavour"))tree->SetBranchAddress("Jet_partonFlavour",&Jet_partonFlavour);
  Int_t GenJet_partonFlavour[200];
  if (tree->GetBranch("GenJet_partonFlavour"))tree->SetBranchAddress("GenJet_partonFlavour",&GenJet_partonFlavour);
  Float_t puWeight;
  if (tree->GetBranch("puWeight"))tree->SetBranchAddress("puWeight",&puWeight);
  Float_t baseW;
  if (tree->GetBranch("baseW"))tree->SetBranchAddress("baseW",&baseW);
  Float_t Generator_weight;
  if (tree->GetBranch("Generator_weight"))tree->SetBranchAddress("Generator_weight",&Generator_weight);

  //Int_t event;
  //tree->SetBranchAddress("event",&event);
  Bool_t HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30;
  tree->SetBranchAddress("HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30",&HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30);
  Bool_t HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30;
  tree->SetBranchAddress("HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30",&HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30);
  Bool_t HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30;
  tree->SetBranchAddress("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30",&HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30);
  Bool_t HLT_Mu8_TrkIsoVVL;
  tree->SetBranchAddress("HLT_Mu8_TrkIsoVVL",&HLT_Mu8_TrkIsoVVL);
  Bool_t HLT_Mu17_TrkIsoVVL;
  tree->SetBranchAddress("HLT_Mu17_TrkIsoVVL",&HLT_Mu17_TrkIsoVVL);


  TLorentzVector lep1;
  TLorentzVector lep2;
  TLorentzVector ll;
  TLorentzVector MET;
  TLorentzVector trkMET;
  Float_t mass_1;
  Float_t mass_2;
  Float_t event_weight;
  Float_t dphil1trkmet;
  Float_t dphil2trkmet;
  Float_t dphiltrkmet;
  Float_t dphil1met;
  Float_t dphil2met;
  Float_t dphilmet;
  Float_t fullpmet;
  Float_t trkpmet;
  Float_t mpmet;
  Float_t dphillmet;
  Float_t mth;
  Float_t mtw2;

  Float_t eletight[8] = {0};
  Float_t eleloose[8] = {0};
  Float_t mutight[8] = {0};
  Float_t muloose[8] = {0};
  Float_t eletight_low[8] = {0};
  Float_t eleloose_low[8] = {0};
  Float_t mutight_low[8] = {0};
  Float_t muloose_low[8] = {0};
  Float_t eletight_high[8] = {0};
  Float_t eleloose_high[8] = {0};
  Float_t mutight_high[8] = {0};
  Float_t muloose_high[8] = {0};

  Float_t afterpreselection=0;
  Float_t afterjetcut[8]={0};
  Float_t eleselection=0;
  Float_t muselection=0;
  Float_t afterelelow[8]={0};
  Float_t afterelelowandbtag[8]={0};
  Float_t afterelehigh[8]={0};
  Float_t afterelehighandbtag[8]={0};

  cout<<"Begin..."<<endl;

  // Create the output histograms
  //--------------------------------------------------------------------------------------------------------------------------------------
  TH1::SetDefaultSumw2();

  TH1F* h_pt1_tight[8];
  TH1F* h_eta1_tight[8];
  TH1F* h_pt1_loose[8];
  TH1F* h_eta1_loose[8];
  TH1F* h_pt1_tight_low[8];
  TH1F* h_eta1_tight_low[8];
  TH1F* h_pt1_loose_low[8];
  TH1F* h_eta1_loose_low[8];
  TH1F* h_pt1_tight_high[8];
  TH1F* h_eta1_tight_high[8];
  TH1F* h_pt1_loose_high[8];
  TH1F* h_eta1_loose_high[8];

  TH1F* h_associated_jet_flavour_tight[8];
  TH1F* h_associated_jet_flavour_loose[8];
  TH1F* h_associated_genjet_flavour_tight[8];
  TH1F* h_associated_genjet_flavour_loose[8];
  TH1F* h_associated_jet_pt_tight[8];
  TH1F* h_associated_jet_pt_loose[8];
  TH1F* h_leppt_dividedby_jet_pt_tight[8];
  TH1F* h_leppt_dividedby_jet_pt_loose[8];
  TH2D *h_lepptvsjetpt_tight[8];
  TH2D *h_lepptvsjetpt_loose[8];

  TH2D * FR_pT_eta_loose_ele[8];
  TH2D * FR_pT_eta_tight_ele[8];
  TH2D * FR_pT_eta_loose_mu[8];
  TH2D * FR_pT_eta_tight_mu[8];


  for(int jet=0;jet<8;jet++){
    h_pt1_tight[jet]   = new TH1F(Form("h_pt1_tight_%d",10+5*jet),Form("h_pt1_tight_%d",10+5*jet),8,10,50);
    h_eta1_tight[jet]  = new TH1F(Form("h_eta1_tight_%d",10+5*jet),Form("h_eta1_tight_%d",10+5*jet),5,0,2.5);
    h_pt1_loose[jet]   = new TH1F(Form("h_pt1_loose_%d",10+5*jet),Form("h_pt1_loose_%d",10+5*jet),8,10,50);
    h_eta1_loose[jet]  = new TH1F(Form("h_eta1_loose_%d",10+5*jet),Form("h_eta1_loose_%d",10+5*jet),5,0,2.5);
    h_pt1_tight_low[jet]   = new TH1F(Form("h_pt1_tight_low_%d",10+5*jet),Form("h_pt1_tight_low_%d",10+5*jet),8,10,50);
    h_eta1_tight_low[jet]  = new TH1F(Form("h_eta1_tight_low_%d",10+5*jet),Form("h_eta1_tight_low_%d",10+5*jet),5,0,2.5);
    h_pt1_loose_low[jet]   = new TH1F(Form("h_pt1_loose_low_%d",10+5*jet),Form("h_pt1_loose_low_%d",10+5*jet),8,10,50);
    h_eta1_loose_low[jet]  = new TH1F(Form("h_eta1_loose_low_%d",10+5*jet),Form("h_eta1_loose_low_%d",10+5*jet),5,0,2.5);
    h_pt1_tight_high[jet]   = new TH1F(Form("h_pt1_tight_high_%d",10+5*jet),Form("h_pt1_tight_high_%d",10+5*jet),8,10,50);
    h_eta1_tight_high[jet]  = new TH1F(Form("h_eta1_tight_high_%d",10+5*jet),Form("h_eta1_tight_high_%d",10+5*jet),5,0,2.5);
    h_pt1_loose_high[jet]   = new TH1F(Form("h_pt1_loose_high_%d",10+5*jet),Form("h_pt1_loose_high_%d",10+5*jet),8,10,50);
    h_eta1_loose_high[jet]  = new TH1F(Form("h_eta1_loose_high_%d",10+5*jet),Form("h_eta1_loose_high_%d",10+5*jet),5,0,2.5);
    h_associated_jet_pt_tight[jet]= new TH1F(Form("h_associated_jet_pt_tight_%d",10+5*jet),Form("h_associated_jet_pt_tight_%d",10+5*jet),18,10,100);
    h_associated_jet_pt_loose[jet]= new TH1F(Form("h_associated_jet_pt_loose_%d",10+5*jet),Form("h_associated_jet_pt_loose_%d",10+5*jet),18,10,100);
    h_leppt_dividedby_jet_pt_tight[jet]= new TH1F(Form("h_leppt_jet_pt_tight_%d",10+5*jet),Form("h_leppt_jet_pt_tight_%d",10+5*jet),10,0,1);
    h_leppt_dividedby_jet_pt_loose[jet]= new TH1F(Form("h_leppt_jet_pt_loose_%d",10+5*jet),Form("h_leppt_jet_pt_loose_%d",10+5*jet),10,0,1);
    h_lepptvsjetpt_tight[jet] = new TH2D(Form("h_leptonpt_vs_associatedjetpt_tight_%d",10+5*jet),Form("h_leptonpt_vs_associatedjetpt_tight_%d",10+5*jet),8,10,50,18,10,100);
    h_lepptvsjetpt_loose[jet] = new TH2D(Form("h_leptonpt_vs_associatedjetpt_loose_%d",10+5*jet),Form("h_leptonpt_vs_associatedjetpt_loose_%d",10+5*jet),8,10,50,18,10,100);
    h_associated_jet_flavour_tight[jet]= new TH1F(Form("h_associated_jet_flavour_tight_%d",10+5*jet),Form("h_associated_jet_flavour_tight_%d",10+5*jet),25,0,25);
    h_associated_jet_flavour_loose[jet]= new TH1F(Form("h_associated_jet_flavour_loose_%d",10+5*jet),Form("h_associated_jet_flavour_loose_%d",10+5*jet),25,0,25);
    h_associated_genjet_flavour_tight[jet]= new TH1F(Form("h_associated_genjet_flavour_tight_%d",10+5*jet),Form("h_associated_genjet_flavour_tight_%d",10+5*jet),25,0,25);
    h_associated_genjet_flavour_loose[jet]= new TH1F(Form("h_associated_genjet_flavour_loose_%d",10+5*jet),Form("h_associated_genjet_flavour_loose_%d",10+5*jet),25,0,25);

    FR_pT_eta_tight_ele[jet]= new TH2D(Form("h_FR_pT_eta_tight_ele_%d",10+5*jet),Form("h_FR_pT_eta_tight_ele_%d",10+5*jet),8,10,50,5,0,2.5);
    FR_pT_eta_loose_ele[jet]= new TH2D(Form("h_FR_pT_eta_loose_ele_%d",10+5*jet),Form("h_FR_pT_eta_loose_ele_%d",10+5*jet),8,10,50,5,0,2.5);
    FR_pT_eta_tight_mu[jet]= new TH2D(Form("h_FR_pT_eta_tight_mu_%d",10+5*jet),Form("h_FR_pT_eta_tight_mu_%d",10+5*jet),8,10,50,5,0,2.5);
    FR_pT_eta_loose_mu[jet]= new TH2D(Form("h_FR_pT_eta_loose_mu_%d",10+5*jet),Form("h_FR_pT_eta_loose_mu_%d",10+5*jet),8,10,50,5,0,2.5);
  }

  // Loop over the tree events
  //--------------------------------------------------------------------------------------------------------------------------------------
  for (int j = 0; j < tree->GetEntries(); ++j){
    tree->GetEntry(j);
    int nentries = tree->GetEntriesFast();
    if(fmod(j,100000)==0) printf(" ..... event %d of %d", int(j), int(nentries));

    //if (Lepton_pt[0]<10 || fabs(Lepton_eta[0])>2.4 || fabs(Lepton_pdgId[0])!=13)continue;
    //muselection++;

    //------------------------------ Preselection --------------------------------------
    if (nLepton!=1){continue;}
    if (PuppiMET_pt>20){continue;}
    if (mtw1>20){continue;}
    afterpreselection++;
    
    //-------------------- Jet cuts------------------------------------------
        
    for(int jetcut=0;jetcut<8;jetcut++){
      if(isMC==true && isQCD==false) weight=baseW*Generator_weight*puWeight;
      int passjets =0;
      for (int jet=0; jet<nCleanJet; jet++){
	//if(CleanJet_pt[jet]>=(10.+5*jetcut) && fabs(CleanJet_eta[jet])<=2.5 && sqrt(deltaPhi(CleanJet_phi[jet],Lepton_phi[0])*deltaPhi(CleanJet_phi[jet],Lepton_phi[0])+(CleanJet_eta[jet]-Lepton_eta[0])*(CleanJet_eta[jet]-Lepton_eta[0]))>=1. && Jet_btagCSVV2[CleanJet_jetIdx[jet]]>btagcut) passjets=1;
	if(CleanJet_pt[jet]>=(10.+5*jetcut) && fabs(CleanJet_eta[jet])<=2.5  && sqrt(deltaPhi(CleanJet_phi[jet],Lepton_phi[0])*deltaPhi(CleanJet_phi[jet],Lepton_phi[0])+(CleanJet_eta[jet]-Lepton_eta[0])*(CleanJet_eta[jet]-Lepton_eta[0]))>=1.) passjets=1;
      }
      if (passjets==0)continue;
      afterjetcut[jetcut]+=weight;      
      if (channel=="ele"){
	if (abs(Lepton_pdgId[0])!=11) continue;
	if (Lepton_pt[0]<13 || fabs(Lepton_eta[0])>2.5)continue;
	if (Lepton_pt[0] <= 25.){

	  if(eletrig=="12"){
	    if (HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30 < 0.5 && isQCD==false)continue;
	    if(isMC==true && isQCD==false){ if(year=="2017")weight*=0.027699; if(year=="2016")weight*=0.014851;if(year=="2018")weight*=0.038849;} //Ele12
	  }
	  if(eletrig=="8"){
	    if (HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30 < 0.5 && isQCD==false)continue;
	    if(isMC==true && isQCD==false){ if(year=="2017")weight*=0.003973; if(year=="2016")weight*=0.006980;if(year=="2018")weight*=0.006412;}   //Ele8
	  }	  
	  afterelelow[jetcut]+=weight;
	  if(btagWP!="none"){
	    if(Electron_jetIdx[Lepton_electronIdx[0]]<0 || Jet_btagDeepB[Electron_jetIdx[Lepton_electronIdx[0]]] <=btagdown || Jet_btagDeepB[Electron_jetIdx[Lepton_electronIdx[0]]] >btagup)continue;
	  }
	  afterelelowandbtag[jetcut]+=weight;

	  eleloose[jetcut]+=weight;eleloose_low[jetcut]+=weight; h_pt1_loose[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose[jetcut]->Fill(fabs(Lepton_eta[0]),weight); h_pt1_loose_low[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose_low[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	  FR_pT_eta_loose_ele[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);
	  if(Electron_jetIdx[Lepton_electronIdx[0]]>=0){
	    h_associated_jet_pt_loose[jetcut]->Fill(Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	    h_leppt_dividedby_jet_pt_loose[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	    h_lepptvsjetpt_loose[jetcut]->Fill(Lepton_pt[0],Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	    if(isMC==true)h_associated_jet_flavour_loose[jetcut]->Fill(fabs(Jet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));
	    if(isMC==true)h_associated_genjet_flavour_loose[jetcut]->Fill(fabs(GenJet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));
	  }
	  //if((year=="2016" && Lepton_isTightElectron_mva_90p_Iso2016[0]>0.5)|| (year=="2017" && Lepton_isTightElectron_mvaFall17Iso_WP90[0]>0.5)||(year=="2018" && Lepton_isTightElectron_mvaFall17V1Iso_WP90[0]>0.5)){
	  if((year=="2016" && Lepton_isTightElectron_cut_WP_Tight80X[0]>0.5)|| (year=="2017" && Lepton_isTightElectron_mvaFall17Iso_WP90[0]>0.5)||(year=="2018" && Lepton_isTightElectron_mvaFall17V1Iso_WP90[0]>0.5)){
	    if (year=="2017" && Electron_pfRelIso03_all[Lepton_electronIdx[0]]>=0.057)continue;
	    eletight[jetcut]+=weight;eletight_low[jetcut]+=weight; h_pt1_tight[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight[jetcut]->Fill(fabs(Lepton_eta[0]),weight);h_pt1_tight_low[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight_low[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	    FR_pT_eta_tight_ele[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);

	    if(Electron_jetIdx[Lepton_electronIdx[0]]>=0){
	      h_associated_jet_pt_tight[jetcut]->Fill(Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	      h_leppt_dividedby_jet_pt_tight[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	      h_lepptvsjetpt_tight[jetcut]->Fill(Lepton_pt[0],Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	      if(isMC==true)h_associated_jet_flavour_tight[jetcut]->Fill(fabs(Jet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));
	      if(isMC==true)h_associated_genjet_flavour_tight[jetcut]->Fill(fabs(GenJet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));
	    }
	  }
	}

	if (Lepton_pt[0] > 25.){
	  if (HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30 < 0.5 && isQCD==false)continue;
	  if(isMC==true && isQCD==false){ if(year=="2017")weight*=0.043469; if(year=="2016")weight*=0.062808;if(year=="2018")weight*=0.038906;}
	  afterelehigh[jetcut]+=weight;
	  if(btagWP!="none"){
	    if(Electron_jetIdx[Lepton_electronIdx[0]]<0 || Jet_btagDeepB[Electron_jetIdx[Lepton_electronIdx[0]]] <btagdown || Jet_btagDeepB[Electron_jetIdx[Lepton_electronIdx[0]]] >btagup)continue;
	  }	  
	  afterelehighandbtag[jetcut]+=weight;

	  eleloose[jetcut]+=weight;eleloose_high[jetcut]+=weight; h_pt1_loose[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose[jetcut]->Fill(fabs(Lepton_eta[0]),weight);h_pt1_loose_high[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose_high[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	  FR_pT_eta_loose_ele[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);
	  if(Electron_jetIdx[Lepton_electronIdx[0]]>=0){
	    h_associated_jet_pt_loose[jetcut]->Fill(Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	    h_leppt_dividedby_jet_pt_loose[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	    h_lepptvsjetpt_loose[jetcut]->Fill(Lepton_pt[0],Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	    if(isMC==true)h_associated_jet_flavour_loose[jetcut]->Fill(fabs(Jet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));
	    if(isMC==true)h_associated_genjet_flavour_loose[jetcut]->Fill(fabs(GenJet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));	    
	  }
	  //if((year=="2016" && Lepton_isTightElectron_mva_90p_Iso2016[0]>0.5)|| (year=="2017" && Lepton_isTightElectron_mvaFall17Iso_WP90[0]>0.5)||(year=="2018" && Lepton_isTightElectron_mvaFall17V1Iso_WP90[0]>0.5)){
	  if((year=="2016" && Lepton_isTightElectron_cut_WP_Tight80X[0]>0.5)|| (year=="2017" && Lepton_isTightElectron_mvaFall17Iso_WP90[0]>0.5)||(year=="2018" && Lepton_isTightElectron_mvaFall17V1Iso_WP90[0]>0.5)){
	    if (year=="2017" && Electron_pfRelIso03_all[Lepton_electronIdx[0]]>=0.057)continue;
	    eletight[jetcut]+=weight;eletight_high[jetcut]+=weight; h_pt1_tight[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight[jetcut]->Fill(fabs(Lepton_eta[0]),weight); h_pt1_tight_high[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight_high[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	    FR_pT_eta_tight_ele[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);

	    if(Electron_jetIdx[Lepton_electronIdx[0]]>=0){
	      h_associated_jet_pt_tight[jetcut]->Fill(Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	      h_leppt_dividedby_jet_pt_tight[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	      h_lepptvsjetpt_tight[jetcut]->Fill(Lepton_pt[0],Jet_pt[Electron_jetIdx[Lepton_electronIdx[0]]]);
	      if(isMC==true)h_associated_jet_flavour_tight[jetcut]->Fill(fabs(Jet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));
	      if(isMC==true)h_associated_genjet_flavour_tight[jetcut]->Fill(fabs(GenJet_partonFlavour[Electron_jetIdx[Lepton_electronIdx[0]]]));	     
	    }
	  }
	}

      }// Close ele channel

      if (channel=="mu"){
	if (abs(Lepton_pdgId[0])!=13) continue;
	if (Lepton_pt[0]<10 || fabs(Lepton_eta[0])>2.4)continue;
	if (Lepton_pt[0] <= 20.){
	  if (HLT_Mu8_TrkIsoVVL < 0.5 && isQCD==false)continue;
	  if(isMC==true && isQCD==false){ if(year=="2017")weight*=0.002903; if(year=="2016")weight*=0.007801;if(year=="2018")weight*=0.008561;}
	  if(btagWP!="none"){
	    if(Muon_jetIdx[Lepton_muonIdx[0]]<0 || Jet_btagDeepB[Muon_jetIdx[Lepton_muonIdx[0]]] <btagdown || Jet_btagDeepB[Muon_jetIdx[Lepton_muonIdx[0]]] >btagup)continue;
	  }
	  muloose[jetcut]+=weight;muloose_low[jetcut]+=weight; h_pt1_loose[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose[jetcut]->Fill(fabs(Lepton_eta[0]),weight); h_pt1_loose_low[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose_low[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	  FR_pT_eta_loose_mu[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);
	  if(Muon_jetIdx[Lepton_muonIdx[0]]>=0){ 
	    h_associated_jet_pt_loose[jetcut]->Fill(Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	    h_leppt_dividedby_jet_pt_loose[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	    h_lepptvsjetpt_loose[jetcut]->Fill(Lepton_pt[0],Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	    if(isMC==true)h_associated_jet_flavour_loose[jetcut]->Fill(fabs(Jet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	    if(isMC==true)h_associated_genjet_flavour_loose[jetcut]->Fill(fabs(GenJet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	  }
	  if(( (year=="2017"||year=="2018") && Lepton_isTightMuon_cut_Tight_HWWW[0]>0.5)|| (year=="2016" && Lepton_isTightMuon_cut_Tight80x[0]>0.5)){
	    mutight[jetcut]+=weight;mutight_low[jetcut]+=weight; h_pt1_tight[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight[jetcut]->Fill(fabs(Lepton_eta[0]),weight);h_pt1_tight_low[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight_low[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	    FR_pT_eta_tight_mu[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);
	    if(Muon_jetIdx[Lepton_muonIdx[0]]>=0){
	      h_associated_jet_pt_tight[jetcut]->Fill(Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	      h_leppt_dividedby_jet_pt_tight[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	      h_lepptvsjetpt_tight[jetcut]->Fill(Lepton_pt[0],Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	      if(isMC==true)h_associated_jet_flavour_tight[jetcut]->Fill(fabs(Jet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	      if(isMC==true)h_associated_genjet_flavour_tight[jetcut]->Fill(fabs(GenJet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	    }
	  }
	}

	if (Lepton_pt[0] > 20.){
	  if (HLT_Mu17_TrkIsoVVL < 0.5 && isQCD==false)continue;
	  if(isMC==true && isQCD==false){ if(year=="2017")weight*=0.065944; if(year=="2016")weight*=0.216748;if(year=="2018")weight*=0.045781;}
	  if(btagWP!="none"){
	    if(Muon_jetIdx[Lepton_muonIdx[0]]<0 || Jet_btagDeepB[Muon_jetIdx[Lepton_muonIdx[0]]] <btagdown || Jet_btagDeepB[Muon_jetIdx[Lepton_muonIdx[0]]] >btagup)continue;
	  }
	  muloose[jetcut]+=weight;muloose_high[jetcut]+=weight; h_pt1_loose[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose[jetcut]->Fill(fabs(Lepton_eta[0]),weight); h_pt1_loose_high[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_loose_high[jetcut]->Fill(fabs(Lepton_eta[0]),weight); 
	  FR_pT_eta_loose_mu[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);
	  if(Muon_jetIdx[Lepton_muonIdx[0]]>=0){
	    h_associated_jet_pt_loose[jetcut]->Fill(Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	    h_leppt_dividedby_jet_pt_loose[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	    h_lepptvsjetpt_loose[jetcut]->Fill(Lepton_pt[0],Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	    if(isMC==true)h_associated_jet_flavour_loose[jetcut]->Fill(fabs(Jet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	    if(isMC==true)h_associated_genjet_flavour_loose[jetcut]->Fill(fabs(GenJet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	  }
	  if(( (year=="2017"||year=="2018") && Lepton_isTightMuon_cut_Tight_HWWW[0]>0.5)|| (year=="2016" && Lepton_isTightMuon_cut_Tight80x[0]>0.5)){
	    mutight[jetcut]+=weight;mutight_high[jetcut]+=weight; h_pt1_tight[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight[jetcut]->Fill(fabs(Lepton_eta[0]),weight);h_pt1_tight_high[jetcut]->Fill(Lepton_pt[0],weight); h_eta1_tight_high[jetcut]->Fill(fabs(Lepton_eta[0]),weight);
	    FR_pT_eta_tight_mu[jetcut]->Fill(Lepton_pt[0],fabs(Lepton_eta[0]),weight);
	    if(Muon_jetIdx[Lepton_muonIdx[0]]>=0){
	      h_associated_jet_pt_tight[jetcut]->Fill(Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	      h_leppt_dividedby_jet_pt_tight[jetcut]->Fill((double)Lepton_pt[0]/Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	      h_lepptvsjetpt_tight[jetcut]->Fill(Lepton_pt[0],Jet_pt[Muon_jetIdx[Lepton_muonIdx[0]]]);
	      if(isMC==true)h_associated_jet_flavour_tight[jetcut]->Fill(fabs(Jet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	      if(isMC==true)h_associated_genjet_flavour_tight[jetcut]->Fill(fabs(GenJet_partonFlavour[Muon_jetIdx[Lepton_muonIdx[0]]]));
	    }
	  } 
	}   
	
      }//Close mu channel

    }//Close loop in jetcut
  }//Close loop in entries

  //Write histograms in root output
  TDirectory *dir[8];
  for(int jetcut=0;jetcut<8;jetcut++){
    dir[jetcut] = root_output->mkdir(Form("jetcut_%d",10+5*jetcut));
    dir[jetcut]->cd();
    h_pt1_tight[jetcut] ->Write();
    h_eta1_tight[jetcut]->Write();
    h_pt1_loose[jetcut] ->Write();
    h_eta1_loose[jetcut]->Write();
    h_pt1_tight_low[jetcut] ->Write();
    h_eta1_tight_low[jetcut]->Write();
    h_pt1_loose_low[jetcut] ->Write();
    h_eta1_loose_low[jetcut]->Write();
    h_pt1_tight_high[jetcut] ->Write();
    h_eta1_tight_high[jetcut]->Write();
    h_pt1_loose_high[jetcut] ->Write();
    h_eta1_loose_high[jetcut]->Write();

    FR_pT_eta_tight_mu[jetcut]->Write();
    FR_pT_eta_loose_mu[jetcut]->Write();
    FR_pT_eta_tight_ele[jetcut]->Write();
    FR_pT_eta_loose_ele[jetcut]->Write();
  
    h_associated_jet_pt_tight[jetcut]->Write();
    h_associated_jet_pt_loose[jetcut]->Write();
    h_leppt_dividedby_jet_pt_tight[jetcut]->Write();
    h_leppt_dividedby_jet_pt_loose[jetcut]->Write();
    h_lepptvsjetpt_tight[jetcut]->Write();
    h_lepptvsjetpt_loose[jetcut]->Write();
  
    if (isMC==true){
     h_associated_genjet_flavour_tight[jetcut]->Write();
     h_associated_genjet_flavour_loose[jetcut]->Write();
     h_associated_jet_flavour_tight[jetcut]->Write();
     h_associated_jet_flavour_loose[jetcut]->Write();
    }
  }
  root_output->Close();
 
  //Print number of events
  cout<<""<<endl;
  cout<<"After preselection "<<afterpreselection<<endl;
     
  for(int jetcut=0;jetcut<8;jetcut++){
   
    if(jetcut==5 && channel=="ele"){
      cout<< "-----------Jet pt >"<<jetcut*5+10<<"-------"<<endl;
      //cout<<"After ele selection         :"<<eleselection<<endl;
      cout<<"After jet cut               :"<< afterjetcut[jetcut]<<endl;
      cout<<"After trigger low           :"<< afterelelow[jetcut]<<endl;
      cout<<"After trigger low and btag  :"<< afterelelowandbtag[jetcut]<<endl;
      cout<<"After trigger high          :"<< afterelehigh[jetcut]<<endl;
      cout<<"After trigger high and btag :"<< afterelehighandbtag[jetcut]<<endl;

      printf("loose electrons      : %.2f \n",  eleloose[jetcut]);
      printf("loose electrons low  : %.2f \n",  eleloose_low[jetcut]);
      printf("loose electrons high : %.2f \n",  eleloose_high[jetcut]);
      printf("tight electrons      : %.2f \n",  eletight[jetcut]);
      printf("tight electrons low  : %.2f \n",  eletight_low[jetcut]);
      printf("tight electrons high : %.2f \n",  eletight_high[jetcut]);
    }

    if(jetcut==3 && channel=="mu"){
      cout<< "-----------Jet pt >"<<jetcut*5+10<<"-------"<<endl;
      cout<<"After mu selection         :"<<muselection<<endl;
      printf("loose muons      : %.2f \n", muloose[jetcut]);
      printf("loose muons low  : %.2f \n", muloose_low[jetcut]);
      printf("loose muons high : %.2f \n", muloose_high[jetcut]);
      printf("tight muons      : %.2f \n", mutight[jetcut]);
      printf("tight muons low  : %.2f \n", mutight_low[jetcut]);
      printf("tight muons high : %.2f \n", mutight_high[jetcut]);
    }  

  }
  cout << endl;
  cout << "-------- Done ---------";
  cout << endl;

}
