#define nanoFakes_conept_cxx


#include "nanoFakes_conept.h"
#include <TStyle.h>


// Data members
//------------------------------------------------------------------------------
string         option;
TString        filename;
TString        year;

TFile*         root_output;

bool           ismc;
int            channel;
float          inputJetEt;
float          leptonPtMin;
float          leptonEtaMax;
float          event_weight;
float          l2tight_weight;
float          deltaR;
float          eleLowPtPrescale = 0.0;
float          eleHighPtPrescale = 0.0;
float          muonLowPtPrescale = 0.0;
float          muonHighPtPrescale = 0.0;

/*float elePrescale8 = 0.0;
float elePrescale17 = 0.0;
float elePrescale23 = 0.0;

float muonPrescale8 = 0.0;
float muonPrescale17 = 0.0;
float muonPrescale20 = 0.0;
float muonPrescale27 = 0.0;
*/

TLorentzVector tlv1;
TLorentzVector tlv2;

int            jetIndex;
int            leptonIndex;

int            counter    = 0;
int            nentries   = 0;
int            maxentries = -1;

int            counter1 = 0;
int            counter2 = 0;

//------------------------------------------------------------------------------
// Begin
//------------------------------------------------------------------------------
void nanoFakes_conept::Begin(TTree*)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).

  option = GetOption();
  printf("\n");

  printf("   option: %s\n", option.c_str());

  year     = option.substr(0,4);
  filename = option.erase(0,4);

  printf("     year: %s\n", year.Data());
  printf(" filename: %s\n", filename.Data());

  printf("\n");
  
  if (!filename.Contains("Run201")) {

    baseW            = {fReader, "baseW"};
    Xsec             = {fReader, "Xsec"};
    puWeight         = {fReader, "puWeight"};
    Generator_weight = {fReader, "Generator_weight"};
  }

  ismc = (filename.Contains("Run201")) ? false : true;

  root_output = new TFile("results/" + filename + ".root", "recreate");

  TH1::SetDefaultSumw2();

  //Prescale definition depending on the year
  if(year == "2016") {
    //    eleLowPtPrescale = 14.851;
    //    eleHighPtPrescale = 62.808;
    //    muonLowPtPrescale = 7.801;
    //    muonHighPtPrescale = 216.748;
    eleLowPtPrescale = 6.979;
    eleHighPtPrescale = 62.66;
    muonLowPtPrescale = 3.909;
    muonHighPtPrescale = 281.99;
  } else if(year == "2017") {
    eleLowPtPrescale = 3.973; //Ele8
    //////eleLowPtPrescale = 27.699; //Ele12
    eleHighPtPrescale = 43.469;
    muonLowPtPrescale = 2.903;
    muonHighPtPrescale = 65.944;
  } else if(year == "2018") {
    eleLowPtPrescale = 6.412; //Ele8
    //////eleLowPtPrescale = 38.849; //Ele12
    eleHighPtPrescale = 38.906;
    muonLowPtPrescale = 8.561;
    muonHighPtPrescale = 45.781;
  }

  //Tight Ele and mu WP definition
  if (year == "2016") {
    muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight80x"}; // v6 and v7
    //muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight80x_tthmva_80"}; // v6 and v7
    eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016"}; // v7
    //eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016_tthmva_70"}; // v7
    //eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016_SS"}; // v7
    //eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016_SS_tthmva_70"}; // v7
    //
    //eleTightWP = {fReader, "Lepton_isTightElectron_cut_WP_Tight80X"}; // v6
    //eleTightWP = {fReader, "Lepton_isTightElectron_cut_WP_Tight80X_SS"}; // v6
    //eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016"}; // v6
    //eleTightWP = {fReader, "Lepton_isTightElectron_mva_90p_Iso2016_SS"}; // v6
  } else if(year == "2017") {
    //muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight_HWWW"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90"};
    muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight_HWWW_tthmva_80"}; // v6 and v7
    eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90_tthmva_70"}; // v7
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90_SS"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90_SS"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight_SS"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight_SS"};
  } else if(year == "2018") {
    //muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight_HWWW"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90"};
    muonTightWP = {fReader, "Lepton_isTightMuon_cut_Tight_HWWW_tthmva_80"}; // v6 and v7
    eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90_tthmva_70"}; // v7
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V1Iso_WP90_SS"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_mvaFall17V2Iso_WP90_SS"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V1Iso_Tight_SS"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight"};
    //eleTightWP = {fReader, "Lepton_isTightElectron_cutFall17V2Iso_Tight_SS"};
  } else {
    std::cout << "WARNING: the year you specified is not 2016, 2017, or 2018!" << std::endl;
  }

  for (int btag = 0; btag < nbtag ; btag ++) {	  	
  // FR regions
  //----------------------------------------------------------------------------
    
    btagDirectory = btags[btag];
    root_output->cd();
    gDirectory->mkdir(btagDirectory);
    root_output->cd(btagDirectory);

    for (int i=0; i<ncutFR; i++) {
	
      TString directory = scutFR[i];
      
      root_output->cd();
      root_output->cd(btagDirectory);
      gDirectory->mkdir(directory);
      root_output->cd(btagDirectory+"/"+directory);
      
      for (int j=0; j<njetet; j++) {
	
	TString muonsuffix = Form("_%.0fGeV", muonjetet[j]);
	TString elesuffix  = Form("_%.0fGeV", elejetet[j]);
	
	// Fake rate histograms
	//------------------------------------------------------------------------
	h_Muon_loose_pt_eta_bin[i][j][btag] = new TH2D("h_Muon_loose_pt_eta_bin" + muonsuffix, "", nptbin, ptbins, netabin, etabins);
	h_Muon_tight_pt_eta_bin[i][j][btag] = new TH2D("h_Muon_tight_pt_eta_bin" + muonsuffix, "", nptbin, ptbins, netabin, etabins);
	h_Ele_loose_pt_eta_bin [i][j][btag] = new TH2D("h_Ele_loose_pt_eta_bin"  + elesuffix,  "", nptbin, ptbins, netabin, etabins);
	h_Ele_tight_pt_eta_bin [i][j][btag] = new TH2D("h_Ele_tight_pt_eta_bin"  + elesuffix,  "", nptbin, ptbins, netabin, etabins);
	
	h_Muon_loose_pt_bin[i][j][btag] = new TH1D("h_Muon_loose_pt_bin" + muonsuffix, "", nptbin, ptbins);
	h_Muon_tight_pt_bin[i][j][btag] = new TH1D("h_Muon_tight_pt_bin" + muonsuffix, "", nptbin, ptbins);
	h_Ele_loose_pt_bin [i][j][btag] = new TH1D("h_Ele_loose_pt_bin"  + elesuffix,  "", nptbin, ptbins);
	h_Ele_tight_pt_bin [i][j][btag] = new TH1D("h_Ele_tight_pt_bin"  + elesuffix,  "", nptbin, ptbins);
	
	h_Muon_loose_eta_bin[i][j][btag] = new TH1D("h_Muon_loose_eta_bin" + muonsuffix, "", netabin, etabins);
	h_Muon_tight_eta_bin[i][j][btag] = new TH1D("h_Muon_tight_eta_bin" + muonsuffix, "", netabin, etabins);
	h_Ele_loose_eta_bin[i][j][btag] = new TH1D("h_Ele_loose_eta_bin"  + elesuffix,  "", netabin, etabins);
	h_Ele_tight_eta_bin[i][j][btag] = new TH1D("h_Ele_tight_eta_bin"  + elesuffix,  "", netabin, etabins);

	//h_Muon_loose_dRlj_bin[i][j][btag] = new TH1D("h_Muon_loose_dRlj_bin" + muonsuffix, "", 30, 0., 3.0);
	//h_Ele_loose_dRlj_bin[i][j][btag] = new TH1D("h_Ele_loose_dRlj_bin" + muonsuffix, "", 30, 0., 3.0);
	//h_Muon_tight_dRlj_bin[i][j][btag] = new TH1D("h_Muon_tight_dRlj_bin" + muonsuffix, "", 30, 0., 3.0);
	//h_Ele_tight_dRlj_bin[i][j][btag] = new TH1D("h_Ele_tight_dRlj_bin" + muonsuffix, "", 30, 0., 3.0);
	h_Muon_Jet_loose_pt_bin[i][j][btag] = new TH1D("h_Muon_Jet_loose_pt_bin" + muonsuffix, "", nptbin, ptbins);
	h_Muon_Jet_tight_pt_bin[i][j][btag] = new TH1D("h_Muon_Jet_tight_pt_bin" + muonsuffix, "", nptbin, ptbins);
	h_Ele_Jet_loose_pt_bin[i][j][btag] = new TH1D("h_Ele_Jet_loose_pt_bin" + elesuffix, "", nptbin, ptbins);
	h_Ele_Jet_tight_pt_bin[i][j][btag] = new TH1D("h_Ele_Jet_tight_pt_bin" + elesuffix, "", nptbin, ptbins);

      }	
    }
  }
    
  // PR regions
  //----------------------------------------------------------------------------
  for (int i=0; i<ncutPR; i++) {
    
    TString directory = scutPR[i];
    
    root_output->cd();
    gDirectory->mkdir(directory);
    root_output->cd(directory);
    
    // Prompt rate histograms
    //--------------------------------------------------------------------------
    h_Muon_loose_pt_eta_PR[i] = new TH2D("h_Muon_loose_pt_eta_PR", "", nptbin, ptbins, netabin, etabins);
    h_Muon_tight_pt_eta_PR[i] = new TH2D("h_Muon_tight_pt_eta_PR", "", nptbin, ptbins, netabin, etabins);
    h_Ele_loose_pt_eta_PR[i]  = new TH2D("h_Ele_loose_pt_eta_PR",  "", nptbin, ptbins, netabin, etabins);
    h_Ele_tight_pt_eta_PR[i]  = new TH2D("h_Ele_tight_pt_eta_PR",  "", nptbin, ptbins, netabin, etabins);
    
    h_Muon_loose_pt_PR[i] = new TH1D("h_Muon_loose_pt_PR", "", nptbin, ptbins);
    h_Muon_tight_pt_PR[i] = new TH1D("h_Muon_tight_pt_PR", "", nptbin, ptbins);
    h_Ele_loose_pt_PR[i]  = new TH1D("h_Ele_loose_pt_PR",  "", nptbin, ptbins);
    h_Ele_tight_pt_PR[i]  = new TH1D("h_Ele_tight_pt_PR",  "", nptbin, ptbins);
    
    h_Muon_loose_eta_PR[i] = new TH1D("h_Muon_loose_eta_PR", "", netabin, etabins);
    h_Muon_tight_eta_PR[i] = new TH1D("h_Muon_tight_eta_PR", "", netabin, etabins);
    h_Ele_loose_eta_PR[i]  = new TH1D("h_Ele_loose_eta_PR",  "", netabin, etabins);
    h_Ele_tight_eta_PR[i]  = new TH1D("h_Ele_tight_eta_PR",  "", netabin, etabins);
  }
  
}

//------------------------------------------------------------------------------
// SlaveBegin
//------------------------------------------------------------------------------
void nanoFakes_conept::SlaveBegin(TTree*)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
}


Bool_t nanoFakes_conept::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // When processing keyed objects with PROOF, the object is already loaded
  // and is available via the fObject pointer.
  //
  // This function should contain the \"body\" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.

  fReader.SetEntry(entry);  

  if (entry > maxentries && maxentries > -1) return 0;
  if (entry%20000 == 0) printf(" Entry number %lld \n", entry); 	 

  nentries++;
 
  channel = (abs(Lepton_pdgId[0]) == 11) ? e : m;

  leptonPtMin  = (channel == e) ?  13 :  10;  // [GeV]
  leptonEtaMax = (channel == e) ? 2.5 : 2.4;  // [GeV]


  if (Lepton_pt[0] < leptonPtMin) return 0;
  if (fabs(Lepton_eta[0]) > leptonEtaMax) return 0;

  event_weight = 1.0;


  // Make Z candidate
  //------------------------------------------------------------------------  
  Zlepton1type   = Loose;
  Zlepton2type   = Loose;
  Zlepton1idisoW = 1.0;
  Zlepton2idisoW = 1.0;

  m2l = -999.0;

  if (*nLepton >= 2) {
    for (unsigned int iLep1=0; iLep1<*nLepton; iLep1++) {
      
      if (Lepton_pt[iLep1] < 25.) continue;

      if ((abs(Lepton_pdgId[iLep1]) == 11 && eleTightWP[iLep1] > 0.5) ||
	  (abs(Lepton_pdgId[iLep1]) == 13 && muonTightWP[iLep1] > 0.5)) {

	Zlepton1type   = Tight;
	Zdecayflavour  = abs(Lepton_pdgId[iLep1]);
	Zlepton1idisoW = 1.0;  // Temporary value until put in the trees
      }

      for (unsigned int iLep2=iLep1+1; iLep2<*nLepton; iLep2++) {
	
	if (Lepton_pt[iLep2] < 10.) continue;

	if (Lepton_pdgId[iLep1] + Lepton_pdgId[iLep2] != 0) continue;

	float mass1 = (abs(Lepton_pdgId[iLep1]) == 11) ? 0.000511 : 0.106;
	float mass2 = (abs(Lepton_pdgId[iLep2]) == 11) ? 0.000511 : 0.106;

	tlv1.SetPtEtaPhiM(Lepton_pt[iLep1], Lepton_eta[iLep1], Lepton_phi[iLep1], mass1);
	tlv2.SetPtEtaPhiM(Lepton_pt[iLep2], Lepton_eta[iLep2], Lepton_phi[iLep2], mass2);

	float inv_mass = (tlv1 + tlv2).M();

	if (m2l < 0 || fabs(inv_mass - 91.188) < fabs(m2l - 91.188)) {
	  
	  m2l = inv_mass;

	  leptonIndex = iLep2;
	  
	  // Is the second lepton tight?
	  if ((abs(Lepton_pdgId[iLep2]) == 11 && eleTightWP[iLep2] > 0.5) ||
	      (abs(Lepton_pdgId[iLep2]) == 13 && muonTightWP[iLep2] > 0.5)) {
	    
	    Zlepton2type   = Tight;
	    Zlepton2idisoW = 1.0;  // Temporary value until put in the trees
	  }
	}
      }
    }
  }

  l2tight_weight = Zlepton1idisoW * Zlepton2idisoW;


  // Get the event weight
  //----------------------------------------------------------------------------
  bool passTrigger = false;

  if (ismc) {
    
    event_weight = (*baseW/1e3) * (*puWeight) * (*Generator_weight);

    if (channel == m) {
      
      (Lepton_pt[0] <= 20.) ? event_weight *= muonLowPtPrescale : event_weight *= muonHighPtPrescale;  // Luminosity in fb-1 from brilcalc
      
      if (Lepton_pt[0] <= 20. && *HLT_Mu8 > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 20. && *HLT_Mu17 > 0.5) {
	
	passTrigger = true;
      }
    }

    if (channel == e) {
      
      (Lepton_pt[0] <= 25.) ? event_weight *= eleLowPtPrescale : event_weight *= eleHighPtPrescale;  // Luminosity in fb-1 from brilcalc
      
      if (Lepton_pt[0] <= 25. && *HLT_Ele8_CaloIdM_TrackIdM_PFJet30 > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdM_TrackIdM_PFJet30 > 0.5) {
	
	passTrigger = true;
      }
    }

  } else {

    if ((filename.Contains("DoubleMuon") or filename.Contains("SingleMuon")) && channel == m) {
      
      if (Lepton_pt[0] <= 20. && *HLT_Mu8 > 0.5) {
      
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 20. && *HLT_Mu17 > 0.5) {

	passTrigger = true;
      }
    }

    if ((filename.Contains("SingleEle") or filename.Contains("DoubleEG") or filename.Contains("EGamma")) && channel == e) {
      
      if (Lepton_pt[0] <= 25. && *HLT_Ele8_CaloIdM_TrackIdM_PFJet30 > 0.5) {
	
	passTrigger = true;
	
      } else if (Lepton_pt[0] > 25. && *HLT_Ele23_CaloIdM_TrackIdM_PFJet30 > 0.5) {
	
	passTrigger = true;
      }
    }
  }

        counter2 ++;

  // Away jet determination
  //----------------------------------------------------------------------------
  if (*nCleanJet > 0) {

    TLorentzVector tlvLepton;
  
    tlvLepton.SetPtEtaPhiM(Lepton_pt[0], Lepton_eta[0], Lepton_phi[0], 0);

	  counter1 ++;

    for (int i=0; i<njetet; i++) {
    
      jetIndex = -1;

      inputJetEt = (channel == e) ? elejetet[i] : muonjetet[i];
    
      //loop over jets to find away jet (deltaR(lep,jet) > 1, jet pT > 10, jet |eta| < 2.5)
      for (unsigned int j=0; j<*nCleanJet; j++) {
      
	if (CleanJet_pt[j] < 10.) continue;
	if (abs(CleanJet_eta[j]) > 2.5) continue;
	if (CleanJet_pt[j] < inputJetEt) continue;

	TLorentzVector tlvJet;
	
	tlvJet.SetPtEtaPhiM(CleanJet_pt[j], CleanJet_eta[j], CleanJet_phi[j], 0);

	deltaR = tlvJet.DeltaR(tlvLepton);
	
	if (deltaR > 1) {

	  jetIndex = j;
	  
	  break;
	}	
      }

      bool passJets = (jetIndex != -1);
      //bool passJets = true;
      

      // QCD region
      //------------------------------------------------------------------------
      bool passCuts = passTrigger;

      passCuts &= (*nLepton == 1);
      passCuts &= (*mtw1 < 20.);
      passCuts &= (*PuppiMET_pt < 20.);

      FillLevelHistograms(FR_00_QCD, i, passJets && passCuts);
      //FillLevelHistograms(FR_00_QCD, i, true);

      // Z region
      //------------------------------------------------------------------------
      passCuts = passTrigger;

      passCuts &= (*nLepton > 1);
      passCuts &= (*PuppiMET_pt < 20.);
      passCuts &= (m2l > 20.);


      FillLevelHistograms(FR_01_Zpeak, i, passJets && passCuts);
    }
  }


  // Fill prompt rate histograms
  //----------------------------------------------------------------------------
  if ((76. < m2l && 106. > m2l) && filename.Contains("DY") && Zlepton1type == Tight) {

    float Zlep2pt  = Lepton_pt[leptonIndex];
    float Zlep2eta = fabs(Lepton_eta[leptonIndex]);
    
    if (fabs(Zdecayflavour) == 11) {
    
      h_Ele_loose_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
      h_Ele_loose_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
      h_Ele_loose_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      
      if (Zlepton2type == Tight) {
      
	h_Ele_tight_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
	h_Ele_tight_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
	h_Ele_tight_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      }
      
    } else if (fabs(Zdecayflavour) == 13) {
      
      h_Muon_loose_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
      h_Muon_loose_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
      h_Muon_loose_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      
      if (Zlepton2type == Tight) {
	
	h_Muon_tight_pt_eta_PR[PR_00]->Fill(Zlep2pt, Zlep2eta, event_weight);
	h_Muon_tight_pt_PR[PR_00]    ->Fill(Zlep2pt,  event_weight);
	h_Muon_tight_eta_PR[PR_00]   ->Fill(Zlep2eta, event_weight);
      }
    }
  }

  return kTRUE;
}


//------------------------------------------------------------------------------
// SlaveTerminate
//------------------------------------------------------------------------------
void nanoFakes_conept::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
}


//------------------------------------------------------------------------------
// Terminate
//------------------------------------------------------------------------------
void nanoFakes_conept::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.

  printf("\n Writing histograms. This can take a while...\n\n");


  printf("Counter 1: %d \n", counter1);
  printf("Counter 2: %d \n", counter2);

  root_output->Write("", TObject::kOverwrite);
  root_output->Close();
}


//------------------------------------------------------------------------------
// FillLevelHistograms
//------------------------------------------------------------------------------
void nanoFakes_conept::FillLevelHistograms(int icut, int i, bool pass)
{
  if (!pass) return;

  FillAnalysisHistograms(icut, i);
}


//------------------------------------------------------------------------------   
// FillanalysisHistograms
//------------------------------------------------------------------------------                 
void nanoFakes_conept::FillAnalysisHistograms(int icut, int i)
{
  float lep1eta = fabs(Lepton_eta[0]);

  for (int btag = 0; btag < nbtag ; btag ++) {

    btagDirectory = btags[btag]; 
    if(btagDirectory == "") {
      btagDown = -10.0;
      btagUp = 10.0;
    } else if(btagDirectory == "bveto") {
      btagDown = -10.0;
      btagUp = 0.1522;
    } else if(btagDirectory == "loose") {
      btagDown = 0.1522;
      btagUp = 0.4941;
    } else if(btagDirectory == "mediumtight") {
      btagDown = 0.4941;
      btagUp = 10.0;
    }


    double cone_pt = -999.;
    double dR_lj = 999.;
    double thejetpt = 0.;
    // loop over jets to find closest one for cone pt determination
    for (unsigned int j=0; j<*nJet; j++) {
      
      //if (CleanJet_pt[j] < 10.) continue;
      //if (abs(CleanJet_eta[j]) > 2.5) continue;
      
      TLorentzVector tlvJet;
      
      tlvJet.SetPtEtaPhiM(Jet_pt[j], Jet_eta[j], Jet_phi[j], 0);
      
      TLorentzVector tlvLepton;
  
      tlvLepton.SetPtEtaPhiM(Lepton_pt[0], Lepton_eta[0], Lepton_phi[0], 0);

      deltaR = tlvJet.DeltaR(tlvLepton);
      
      if (deltaR < dR_lj) {
	
	dR_lj = deltaR;
	//cout << "DEBUG: dR_lj = " << dR_lj << " and jet index is " << j << endl;
	thejetpt = Jet_pt[j];
	//inputJetEt = (channel == e) ? elejetet[i] : muonjetet[i];
	double iso = (channel == e) ? Electron_miniPFRelIso_all[0] : Muon_miniPFRelIso_all[0];
	if (deltaR > 0.4)
	  cone_pt = Lepton_pt[0]/(Lepton_pt[0] + iso);
	else
	  cone_pt = 0.9*Jet_pt[j];
      }	
    }

    //std::cout << "And the cone pt is: " << cone_pt << " (for jet pt = " << thejetpt << " and dR_lj = " << dR_lj << ")" << std::endl;

    if (channel == m && Jet_btagDeepB[Muon_jetIdx[Lepton_muonIdx[0]]] > btagDown && Jet_btagDeepB[Muon_jetIdx[Lepton_muonIdx[0]]] < btagUp) {
      
      // Loose muons
      //--------------------------------------------------------------------------
      h_Muon_loose_pt_eta_bin[icut][i][btag]->Fill(cone_pt, lep1eta, event_weight);
      h_Muon_loose_pt_bin    [icut][i][btag]->Fill(cone_pt,  event_weight);
      h_Muon_loose_eta_bin   [icut][i][btag]->Fill(lep1eta, event_weight);
      
      //h_Muon_loose_dRlj_bin[icut][i][btag]->Fill(dR_lj, event_weight);
      h_Muon_Jet_loose_pt_bin[icut][i][btag]->Fill(Jet_pt[0], event_weight);
      // Tight muons
      //--------------------------------------------------------------------------
      if (muonTightWP[0] > 0.5) {

	h_Muon_tight_pt_eta_bin[icut][i][btag]->Fill(cone_pt, lep1eta, event_weight);
	h_Muon_tight_pt_bin    [icut][i][btag]->Fill(cone_pt,  event_weight);
	h_Muon_tight_eta_bin   [icut][i][btag]->Fill(lep1eta, event_weight);
	//h_Muon_tight_dRlj_bin[icut][i][btag]->Fill(dR_lj, event_weight);
	h_Muon_Jet_tight_pt_bin[icut][i][btag]->Fill(Jet_pt[0], event_weight);
	
      }
      
    } else if (channel == e && Jet_btagDeepB[Electron_jetIdx[Lepton_electronIdx[0]]] > btagDown && Jet_btagDeepB[Electron_jetIdx[Lepton_electronIdx[0]]] < btagUp) {
      
      
      // Loose electrons
      //--------------------------------------------------------------------------
      h_Ele_loose_pt_eta_bin[icut][i][btag]->Fill(cone_pt, lep1eta, event_weight);
      h_Ele_loose_pt_bin    [icut][i][btag]->Fill(cone_pt,  event_weight);
      h_Ele_loose_eta_bin   [icut][i][btag]->Fill(lep1eta, event_weight);
      
      //h_Ele_loose_dRlj_bin[icut][i][btag]->Fill(dR_lj, event_weight);
      h_Ele_Jet_loose_pt_bin[icut][i][btag]->Fill(Jet_pt[0], event_weight);
      
      // Tight electrons
      //--------------------------------------------------------------------------
      if (eleTightWP[0] > 0.5) {
	
	h_Ele_tight_pt_eta_bin[icut][i][btag]->Fill(cone_pt, lep1eta, event_weight);
	h_Ele_tight_pt_bin    [icut][i][btag]->Fill(cone_pt,  event_weight);
	h_Ele_tight_eta_bin   [icut][i][btag]->Fill(lep1eta, event_weight);
	//h_Ele_tight_dRlj_bin[icut][i][btag]->Fill(dR_lj, event_weight);
	h_Ele_Jet_tight_pt_bin[icut][i][btag]->Fill(Jet_pt[0], event_weight);
	
      }
      
    }
    
  }
}
