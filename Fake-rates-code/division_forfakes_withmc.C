#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>

void division_forfakes_withmc(TString dir)
{

  TFile* file_Data_ele= new TFile(dir+"/Data_ele.root");
  TFile* file_DY_ele= new TFile(dir+"/DY_ele.root");
  TFile* file_WJets_ele= new TFile(dir+"/WJets_ele.root");
  TFile* file_GJets_ele= new TFile(dir+"/GJets_ele.root");
  TFile* file_Data_mu= new TFile(dir+"/Data_mu.root");
  TFile* file_DY_mu= new TFile(dir+"/DY_mu.root");
  TFile* file_WJets_mu= new TFile(dir+"/WJets_mu.root");
  TFile* file_GJets_mu= new TFile(dir+"/GJets_mu.root");

  TH1F* h_DATA_ele[8];
  TH1F* h_DY_ele[8]; 
  TH1F* h_WJets_ele[8];
  TH1F* h_GJets_ele[8];
  TH1F* h_denominator_DATA_ele[8];
  TH1F* h_denominator_DY_ele[8];
  TH1F* h_denominator_WJets_ele[8];
  TH1F* h_denominator_GJets_ele[8];
  TH1F* h_DATA_eta_ele[8];
  TH1F* h_DY_eta_ele[8];
  TH1F* h_WJets_eta_ele[8];
  TH1F* h_GJets_eta_ele[8];
  TH1F* h_denominator_DATA_eta_ele[8];
  TH1F* h_denominator_DY_eta_ele[8];
  TH1F* h_denominator_WJets_eta_ele[8];
  TH1F* h_denominator_GJets_eta_ele[8];  
  TH1F* h_DATA_mu[8];
  TH1F* h_DY_mu[8]; 
  TH1F* h_WJets_mu[8];
  TH1F* h_GJets_mu[8];  
  TH1F* h_denominator_DATA_mu[8];
  TH1F* h_denominator_DY_mu[8];
  TH1F* h_denominator_WJets_mu[8];
  TH1F* h_denominator_GJets_mu[8];
  TH1F* h_DATA_eta_mu[8];
  TH1F* h_DY_eta_mu[8];
  TH1F* h_WJets_eta_mu[8];
  TH1F* h_GJets_eta_mu[8];
  TH1F* h_denominator_DATA_eta_mu[8];
  TH1F* h_denominator_DY_eta_mu[8];
  TH1F* h_denominator_WJets_eta_mu[8];
  TH1F* h_denominator_GJets_eta_mu[8];

  TH2F* FR_pT_eta_num_DATA_ele[8];
  TH2F* FR_pT_eta_num_DY_ele[8];  
  TH2F* FR_pT_eta_num_WJets_ele[8];
  TH2F* FR_pT_eta_num_GJets_ele[8];
  TH2F* FR_pT_eta_num_DATA_mu[8];
  TH2F* FR_pT_eta_num_DY_mu[8];  
  TH2F* FR_pT_eta_num_WJets_mu[8];
  TH2F* FR_pT_eta_num_GJets_mu[8];
  TH2F* FR_pT_eta_den_DATA_ele[8];
  TH2F* FR_pT_eta_den_DY_ele[8];  
  TH2F* FR_pT_eta_den_WJets_ele[8];
  TH2F* FR_pT_eta_den_GJets_ele[8];
  TH2F* FR_pT_eta_den_DATA_mu[8];
  TH2F* FR_pT_eta_den_DY_mu[8];  
  TH2F* FR_pT_eta_den_WJets_mu[8];
  TH2F* FR_pT_eta_den_GJets_mu[8];

  for(int j=0;j<8;j++){
    h_DATA_ele[j] = (TH1F*)file_Data_ele->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_DY_ele[j] = (TH1F*)file_DY_ele->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_WJets_ele[j] = (TH1F*)file_WJets_ele->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_GJets_ele[j] = (TH1F*)file_GJets_ele->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_denominator_DATA_ele[j] = (TH1F*)file_Data_ele->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_denominator_DY_ele[j] = (TH1F*)file_DY_ele->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_denominator_WJets_ele[j] = (TH1F*)file_WJets_ele->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_denominator_GJets_ele[j] = (TH1F*)file_GJets_ele->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_DATA_eta_ele[j] = (TH1F*)file_Data_ele->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_DY_eta_ele[j] = (TH1F*)file_DY_ele->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_WJets_eta_ele[j] = (TH1F*)file_WJets_ele->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_GJets_eta_ele[j] = (TH1F*)file_GJets_ele->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_denominator_DATA_eta_ele[j] = (TH1F*)file_Data_ele->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_denominator_DY_eta_ele[j] = (TH1F*)file_DY_ele->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_denominator_WJets_eta_ele[j] = (TH1F*)file_WJets_ele->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_denominator_GJets_eta_ele[j] = (TH1F*)file_GJets_ele->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_DATA_mu[j] = (TH1F*)file_Data_mu->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_DY_mu[j] = (TH1F*)file_DY_mu->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_WJets_mu[j] = (TH1F*)file_WJets_mu->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_GJets_mu[j] = (TH1F*)file_GJets_mu->Get(Form("jetcut_%d/h_pt1_tight_%d",j*5+10,j*5+10)); 
    h_denominator_DATA_mu[j] = (TH1F*)file_Data_mu->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_denominator_DY_mu[j] = (TH1F*)file_DY_mu->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_denominator_WJets_mu[j] = (TH1F*)file_WJets_mu->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_denominator_GJets_mu[j] = (TH1F*)file_GJets_mu->Get(Form("jetcut_%d/h_pt1_loose_%d",j*5+10,j*5+10));
    h_DATA_eta_mu[j] = (TH1F*)file_Data_mu->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_DY_eta_mu[j] = (TH1F*)file_DY_mu->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_WJets_eta_mu[j] = (TH1F*)file_WJets_mu->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_GJets_eta_mu[j] = (TH1F*)file_GJets_mu->Get(Form("jetcut_%d/h_eta1_tight_%d",j*5+10,j*5+10));
    h_denominator_DATA_eta_mu[j] = (TH1F*)file_Data_mu->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_denominator_DY_eta_mu[j] = (TH1F*)file_DY_mu->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_denominator_WJets_eta_mu[j] = (TH1F*)file_WJets_mu->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    h_denominator_GJets_eta_mu[j] = (TH1F*)file_GJets_mu->Get(Form("jetcut_%d/h_eta1_loose_%d",j*5+10,j*5+10));
    FR_pT_eta_num_DATA_ele[j] = (TH2F*)file_Data_ele->Get(Form("jetcut_%d/h_FR_pT_eta_tight_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_num_DY_ele[j] = (TH2F*)file_DY_ele->Get(Form("jetcut_%d/h_FR_pT_eta_tight_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_num_WJets_ele[j] = (TH2F*)file_WJets_ele->Get(Form("jetcut_%d/h_FR_pT_eta_tight_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_num_GJets_ele[j] = (TH2F*)file_GJets_ele->Get(Form("jetcut_%d/h_FR_pT_eta_tight_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_num_DATA_mu[j] = (TH2F*)file_Data_mu->Get(Form("jetcut_%d/h_FR_pT_eta_tight_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_num_DY_mu[j] = (TH2F*)file_DY_mu->Get(Form("jetcut_%d/h_FR_pT_eta_tight_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_num_WJets_mu[j] = (TH2F*)file_WJets_mu->Get(Form("jetcut_%d/h_FR_pT_eta_tight_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_num_GJets_mu[j] = (TH2F*)file_GJets_mu->Get(Form("jetcut_%d/h_FR_pT_eta_tight_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_den_DATA_ele[j] = (TH2F*)file_Data_ele->Get(Form("jetcut_%d/h_FR_pT_eta_loose_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_den_DY_ele[j] = (TH2F*)file_DY_ele->Get(Form("jetcut_%d/h_FR_pT_eta_loose_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_den_WJets_ele[j] = (TH2F*)file_WJets_ele->Get(Form("jetcut_%d/h_FR_pT_eta_loose_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_den_GJets_ele[j] = (TH2F*)file_GJets_ele->Get(Form("jetcut_%d/h_FR_pT_eta_loose_ele_%d",j*5+10,j*5+10));
    FR_pT_eta_den_DATA_mu[j] = (TH2F*)file_Data_mu->Get(Form("jetcut_%d/h_FR_pT_eta_loose_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_den_DY_mu[j] = (TH2F*)file_DY_mu->Get(Form("jetcut_%d/h_FR_pT_eta_loose_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_den_WJets_mu[j] = (TH2F*)file_WJets_mu->Get(Form("jetcut_%d/h_FR_pT_eta_loose_mu_%d",j*5+10,j*5+10));
    FR_pT_eta_den_GJets_mu[j] = (TH2F*)file_GJets_mu->Get(Form("jetcut_%d/h_FR_pT_eta_loose_mu_%d",j*5+10,j*5+10));
  }
  gStyle->SetOptStat(0);
  gStyle->SetFrameLineWidth(3);
  gStyle->SetLabelSize(0.08);

  TH1F* h_num_ele[8];TH1F* h_den_ele[8];TH1F* h_div_ele[8];TH1F* h_div_noEWKcorr_ele[8];
  for(int j=0;j<8;j++){
    h_num_ele[j] = (TH1F*)h_DATA_ele[j]->Clone(Form("h_num_ele_%d",j*5+10));
    h_num_ele[j]->Add(h_DY_ele[j],-1);
    h_num_ele[j]->Add(h_WJets_ele[j],-1);
    h_num_ele[j]->Add(h_GJets_ele[j],-1);
    h_den_ele[j] = (TH1F*)h_denominator_DATA_ele[j]->Clone(Form("h_den_ele_%d",j*5+10));
    h_den_ele[j]->Add(h_denominator_DY_ele[j],-1);
    h_den_ele[j]->Add(h_denominator_WJets_ele[j],-1);
    h_den_ele[j]->Add(h_denominator_GJets_ele[j],-1);
    h_div_ele[j] = (TH1F*)h_num_ele[j]->Clone(Form("h_div_ele_%d",j*5+10));
    h_div_ele[j]->Divide(h_den_ele[j]);
    h_div_noEWKcorr_ele[j] = (TH1F*)h_DATA_ele[j]->Clone(Form("h_div_noEWKcorr_ele_%d",j*5+10));
    h_div_noEWKcorr_ele[j]->Divide(h_denominator_DATA_ele[j]);
  }

  TH1F* h_num_mu[8];TH1F* h_den_mu[8];TH1F* h_div_mu[8];TH1F* h_div_noEWKcorr_mu[8];
  for(int j=0;j<8;j++){
    h_num_mu[j] = (TH1F*)h_DATA_mu[j]->Clone(Form("h_num_mu_%d",j*5+10));
    h_num_mu[j]->Add(h_DY_mu[j],-1);
    h_num_mu[j]->Add(h_WJets_mu[j],-1);
    h_num_mu[j]->Add(h_GJets_mu[j],-1);
    h_den_mu[j] = (TH1F*)h_denominator_DATA_mu[j]->Clone(Form("h_den_mu_%d",j*5+10));
    h_den_mu[j]->Add(h_denominator_DY_mu[j],-1);
    h_den_mu[j]->Add(h_denominator_WJets_mu[j],-1);
    h_den_mu[j]->Add(h_denominator_GJets_mu[j],-1);
    h_div_mu[j] = (TH1F*)h_num_mu[j]->Clone(Form("h_div_mu_%d",j*5+10));
    h_div_mu[j]->Divide(h_den_mu[j]);
    h_div_noEWKcorr_mu[j] = (TH1F*)h_DATA_mu[j]->Clone(Form("h_div_noEWKcorr_mu_%d",j*5+10));
    h_div_noEWKcorr_mu[j]->Divide(h_denominator_DATA_mu[j]);
  }  

  TH1F* h_relEWKcont_ele[8];TH1F* h_relEWKcont_numerator_ele[8];TH1F* h_relEWKcont2_ele[8];TH1F* h_relEWKcont_denominator_ele[8];
  for(int j=0;j<8;j++){
    h_relEWKcont_ele[j] = (TH1F*)h_DY_ele[j]->Clone(Form("h_relEWKcont_ele_%d",j*5+10));
    h_relEWKcont_ele[j]->Add(h_WJets_ele[j],1);
    h_relEWKcont_ele[j]->Add(h_GJets_ele[j],1);
    h_relEWKcont_numerator_ele[j] = (TH1F*)h_relEWKcont_ele[j]->Clone(Form("h_relEWKcont_numerator_ele_%d",j*5+10));
    h_relEWKcont_numerator_ele[j]->Divide(h_DATA_ele[j]);
    h_relEWKcont2_ele[j] = (TH1F*)h_denominator_DY_ele[j]->Clone(Form("h_relEWKcont2_ele_%d",j*5+10));
    h_relEWKcont2_ele[j]->Add(h_denominator_WJets_ele[j],1);
    h_relEWKcont2_ele[j]->Add(h_denominator_GJets_ele[j],1);
    h_relEWKcont_denominator_ele[j] = (TH1F*)h_relEWKcont2_ele[j]->Clone(Form("h_relEWKcont_denominator_ele_%d",j*5+10));
    h_relEWKcont_denominator_ele[j]->Divide(h_denominator_DATA_ele[j]);
  }

  TH1F* h_relEWKcont_mu[8];TH1F* h_relEWKcont_numerator_mu[8];TH1F* h_relEWKcont2_mu[8];TH1F* h_relEWKcont_denominator_mu[8];
  for(int j=0;j<8;j++){
    h_relEWKcont_mu[j] = (TH1F*)h_DY_mu[j]->Clone(Form("h_relEWKcont_mu_%d",j*5+10));
    h_relEWKcont_mu[j]->Add(h_WJets_mu[j],1);
    h_relEWKcont_mu[j]->Add(h_GJets_mu[j],1);
    h_relEWKcont_numerator_mu[j] = (TH1F*)h_relEWKcont_mu[j]->Clone(Form("h_relEWKcont_numerator_mu_%d",j*5+10));
    h_relEWKcont_numerator_mu[j]->Divide(h_DATA_mu[j]);
    h_relEWKcont2_mu[j] = (TH1F*)h_denominator_DY_mu[j]->Clone(Form("h_relEWKcont2_mu_%d",j*5+10));
    h_relEWKcont2_mu[j]->Add(h_denominator_WJets_mu[j],1);
    h_relEWKcont2_mu[j]->Add(h_denominator_GJets_mu[j],1);
    h_relEWKcont_denominator_mu[j] = (TH1F*)h_relEWKcont2_mu[j]->Clone(Form("h_relEWKcont_denominator_mu_%d",j*5+10));
    h_relEWKcont_denominator_mu[j]->Divide(h_denominator_DATA_mu[j]);
  }

  TH1F* h_num_eta_ele[8];TH1F* h_den_eta_ele[8];TH1F* h_div_eta_ele[8];TH1F* h_div_noEWKcorr_eta_ele[8];
  for(int j=0;j<8;j++){
    h_num_eta_ele[j] = (TH1F*)h_DATA_eta_ele[j]->Clone(Form("h_num_eta_ele_%d",j*5+10));
    h_num_eta_ele[j]->Add(h_DY_eta_ele[j],-1);
    h_num_eta_ele[j]->Add(h_WJets_eta_ele[j],-1);
    h_num_eta_ele[j]->Add(h_GJets_eta_ele[j],-1);
    h_den_eta_ele[j] = (TH1F*)h_denominator_DATA_eta_ele[j]->Clone(Form("h_den_eta_ele_%d",j*5+10));
    h_den_eta_ele[j]->Add(h_denominator_DY_eta_ele[j],-1);
    h_den_eta_ele[j]->Add(h_denominator_WJets_eta_ele[j],-1);
    h_den_eta_ele[j]->Add(h_denominator_GJets_eta_ele[j],-1);
    h_div_eta_ele[j] = (TH1F*)h_num_eta_ele[j]->Clone(Form("h_div_eta_ele_%d",j*5+10));
    h_div_eta_ele[j]->Divide(h_den_eta_ele[j]);
    h_div_noEWKcorr_eta_ele[j] = (TH1F*)h_DATA_eta_ele[j]->Clone(Form("h_div_noEWKcorr_eta_ele_%d",j*5+10));
    h_div_noEWKcorr_eta_ele[j]->Divide(h_denominator_DATA_eta_ele[j]);
  }

  TH1F* h_num_eta_mu[8];TH1F* h_den_eta_mu[8];TH1F* h_div_eta_mu[8];TH1F* h_div_noEWKcorr_eta_mu[8];
  for(int j=0;j<8;j++){
    h_num_eta_mu[j] = (TH1F*)h_DATA_eta_mu[j]->Clone(Form("h_num_eta_mu_%d",j*5+10));
    h_num_eta_mu[j]->Add(h_DY_eta_mu[j],-1);
    h_num_eta_mu[j]->Add(h_WJets_eta_mu[j],-1);
    h_num_eta_mu[j]->Add(h_GJets_eta_mu[j],-1);
    h_den_eta_mu[j] = (TH1F*)h_denominator_DATA_eta_mu[j]->Clone(Form("h_den_eta_mu_%d",j*5+10));
    h_den_eta_mu[j]->Add(h_denominator_DY_eta_mu[j],-1);
    h_den_eta_mu[j]->Add(h_denominator_WJets_eta_mu[j],-1);
    h_den_eta_mu[j]->Add(h_denominator_GJets_eta_mu[j],-1);
    h_div_eta_mu[j] = (TH1F*)h_num_eta_mu[j]->Clone(Form("h_div_eta_mu_%d",j*5+10));
    h_div_eta_mu[j]->Divide(h_den_eta_mu[j]);
    h_div_noEWKcorr_eta_mu[j] = (TH1F*)h_DATA_eta_mu[j]->Clone(Form("h_div_noEWKcorr_eta_mu_%d",j*5+10));
    h_div_noEWKcorr_eta_mu[j]->Divide(h_denominator_DATA_eta_mu[j]);
  }

  TLegend *leg= new TLegend(0.1,0.7,0.48,0.9);
  leg->AddEntry(h_div_noEWKcorr_ele[0],"Without EWK correction");
  leg->AddEntry(h_div_ele[0],"With EWK correction");

  //////////////Eta vs pt histograms///////////////////////////////////////

  TH2F* FR_pT_eta_ele[8];  
  TH2F* FR_pT_eta_numerator_ele[8]; 
  TH2F* FR_pT_eta_denominator_ele[8];
  TH2F* FR_pT_eta_EWKcorr_ele[8];
  TH2F* FR_pT_eta_EWKcorr_numerator_ele[8];
  TH2F* FR_pT_eta_EWKcorr_denominator_ele[8];
  TH2F* FR_pT_eta_mu[8];
  TH2F* FR_pT_eta_numerator_mu[8];
  TH2F* FR_pT_eta_denominator_mu[8];
  TH2F* FR_pT_eta_EWKcorr_mu[8]; 
  TH2F* FR_pT_eta_EWKcorr_numerator_mu[8]; 
  TH2F* FR_pT_eta_EWKcorr_denominator_mu[8];

  for(int j=0;j<8;j++){

    FR_pT_eta_EWKcorr_numerator_ele[j] = (TH2F*) FR_pT_eta_num_DATA_ele[j]->Clone("FR_pT_eta_EWKcorr_numerator");
    FR_pT_eta_EWKcorr_numerator_ele[j]->Add(FR_pT_eta_num_DY_ele[j],-1);
    FR_pT_eta_EWKcorr_numerator_ele[j]->Add(FR_pT_eta_num_WJets_ele[j],-1);
    FR_pT_eta_EWKcorr_numerator_ele[j]->Add(FR_pT_eta_num_GJets_ele[j],-1);
    FR_pT_eta_EWKcorr_denominator_ele[j] = (TH2F*) FR_pT_eta_den_DATA_ele[j]->Clone("FR_pT_eta_EWKcorr_denominator");
    FR_pT_eta_EWKcorr_denominator_ele[j]->Add(FR_pT_eta_den_DY_ele[j],-1);
    FR_pT_eta_EWKcorr_denominator_ele[j]->Add(FR_pT_eta_den_WJets_ele[j],-1);
    FR_pT_eta_EWKcorr_denominator_ele[j]->Add(FR_pT_eta_den_GJets_ele[j],-1);
    FR_pT_eta_EWKcorr_ele[j] = (TH2F*) FR_pT_eta_EWKcorr_numerator_ele[j]->Clone("FR_pT_eta_EWKcorr");
    FR_pT_eta_EWKcorr_ele[j]->Divide(FR_pT_eta_EWKcorr_denominator_ele[j]);
    FR_pT_eta_numerator_ele[j] = (TH2F*) FR_pT_eta_num_DATA_ele[j]->Clone("FR_pT_eta_numerator");
    FR_pT_eta_denominator_ele[j] = (TH2F*) FR_pT_eta_den_DATA_ele[j]->Clone("FR_pT_eta_denominator");
    FR_pT_eta_ele[j] = (TH2F*) FR_pT_eta_numerator_ele[j]->Clone("FR_pT_eta");
    FR_pT_eta_ele[j]->Divide(FR_pT_eta_denominator_ele[j]);
    
    FR_pT_eta_EWKcorr_numerator_mu[j] = (TH2F*) FR_pT_eta_num_DATA_mu[j]->Clone("FR_pT_eta_EWKcorr_numerator");
    FR_pT_eta_EWKcorr_numerator_mu[j]->Add(FR_pT_eta_num_DY_mu[j],-1);
    FR_pT_eta_EWKcorr_numerator_mu[j]->Add(FR_pT_eta_num_WJets_mu[j],-1);
    FR_pT_eta_EWKcorr_numerator_mu[j]->Add(FR_pT_eta_num_GJets_mu[j],-1);
    FR_pT_eta_EWKcorr_denominator_mu[j] = (TH2F*) FR_pT_eta_den_DATA_mu[j]->Clone("FR_pT_eta_EWKcorr_denominator");
    FR_pT_eta_EWKcorr_denominator_mu[j]->Add(FR_pT_eta_den_DY_mu[j],-1);
    FR_pT_eta_EWKcorr_denominator_mu[j]->Add(FR_pT_eta_den_WJets_mu[j],-1);
    FR_pT_eta_EWKcorr_denominator_mu[j]->Add(FR_pT_eta_den_GJets_mu[j],-1);
    FR_pT_eta_EWKcorr_mu[j] = (TH2F*) FR_pT_eta_EWKcorr_numerator_mu[j]->Clone("FR_pT_eta_EWKcorr");
    FR_pT_eta_EWKcorr_mu[j]->Divide(FR_pT_eta_EWKcorr_denominator_mu[j]);
    FR_pT_eta_numerator_mu[j] = (TH2F*) FR_pT_eta_num_DATA_mu[j]->Clone("FR_pT_eta_numerator");
    FR_pT_eta_denominator_mu[j] = (TH2F*) FR_pT_eta_den_DATA_mu[j]->Clone("FR_pT_eta_denominator");
    FR_pT_eta_mu[j] = (TH2F*) FR_pT_eta_numerator_mu[j]->Clone("FR_pT_eta");
    FR_pT_eta_mu[j]->Divide(FR_pT_eta_denominator_mu[j]);
     
  }

  /////////////Efficiency errors //////////////////
  float binvalue ;
  float totaln ;
  float newerror ;
 
  for(int j=0;j<8;j++){
    for (int i=1; i<= 8; i++) {
      binvalue = h_div_ele[j]->GetBinContent(i);
      totaln = h_den_ele[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_ele[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 8; i++) {
      binvalue = h_div_noEWKcorr_ele[j]->GetBinContent(i);
      totaln = h_denominator_DATA_ele[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_noEWKcorr_ele[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 5; i++) {
      binvalue = h_div_eta_ele[j]->GetBinContent(i);
      totaln = h_den_eta_ele[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_eta_ele[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 5; i++) {
      binvalue = h_div_noEWKcorr_eta_ele[j]->GetBinContent(i);
      totaln = h_denominator_DATA_eta_ele[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_noEWKcorr_eta_ele[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 8; i++) {
      binvalue = h_div_mu[j]->GetBinContent(i);
      totaln = h_den_mu[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_mu[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 8; i++) {
      binvalue = h_div_noEWKcorr_mu[j]->GetBinContent(i);
      totaln = h_denominator_DATA_mu[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_noEWKcorr_mu[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 5; i++) {
      binvalue = h_div_eta_mu[j]->GetBinContent(i);
      totaln = h_den_eta_mu[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_eta_mu[j]->SetBinError(i,newerror);
    }
    for (int i=1; i<= 5; i++) {
      binvalue = h_div_noEWKcorr_eta_mu[j]->GetBinContent(i);
      totaln = h_denominator_DATA_eta_mu[j]->GetBinContent(i);
      newerror = sqrt((binvalue*(1-binvalue))/totaln);
      h_div_noEWKcorr_eta_mu[j]->SetBinError(i,newerror);
    }
   
  }
  //////////////////////Output plots///////////////////////
  
  TString dirname= dir.ReplaceAll("outputsFR","plots");
  system("mkdir -p "+dirname);
  chdir(dirname);


  TCanvas *c[3][2][8];
  for(int j=0;j<8;j++){
    c[0][0][j]= new TCanvas();c[0][0][j]->cd();
    h_div_ele[j]->Draw("E"); h_div_ele[j]->GetYaxis()->SetRangeUser(0,1); h_div_ele[j]->SetTitle(Form("Electron FR (jet pt > %dGeV)",j*5+10)); h_div_ele[j]->SetLineColor(2); h_div_ele[j]->GetXaxis()->SetTitle("p_{T} [GeV]"); h_div_ele[j]->GetYaxis()->SetTitle("Ele fake rate");c[0][0][j]->SetGridx(1);c[0][0][j]->SetGridy(1); h_div_ele[j]->SetLineWidth(2); h_div_ele[j]->SetMarkerColor(2);  h_div_ele[j]->SetMarkerStyle(kFullCircle);
    h_div_noEWKcorr_ele[j]->Draw("sameE"); h_div_noEWKcorr_ele[j]->SetLineColor(1);h_div_noEWKcorr_ele[j]->SetLineWidth(2); h_div_noEWKcorr_ele[j]->SetMarkerColor(1);  h_div_noEWKcorr_ele[j]->SetMarkerStyle(kFullCircle);
    leg->Draw();c[0][0][j]->SaveAs(Form("eleFR_pt_jet%d.png",j*5+10));
    c[0][1][j]= new TCanvas();c[0][1][j]->cd();
    h_div_mu[j]->Draw("E"); h_div_mu[j]->GetYaxis()->SetRangeUser(0,1); h_div_mu[j]->SetTitle(Form("Muon FR (jet pt > %dGeV)",j*5+10)); h_div_mu[j]->SetLineColor(2); h_div_mu[j]->GetXaxis()->SetTitle("p_{T} [GeV]"); h_div_mu[j]->GetYaxis()->SetTitle("Mu fake rate");c[0][1][j]->SetGridx(1);c[0][1][j]->SetGridy(1); h_div_mu[j]->SetLineWidth(2); h_div_mu[j]->SetMarkerColor(2);  h_div_mu[j]->SetMarkerStyle(kFullCircle);
    h_div_noEWKcorr_mu[j]->Draw("sameE"); h_div_noEWKcorr_mu[j]->SetLineColor(1);h_div_noEWKcorr_mu[j]->SetLineWidth(2); h_div_noEWKcorr_mu[j]->SetMarkerColor(1);  h_div_noEWKcorr_mu[j]->SetMarkerStyle(kFullCircle);
    leg->Draw();c[0][1][j]->SaveAs(Form("muFR_pt_jet%d.png",j*5+10));

    c[1][0][j]= new TCanvas();c[1][0][j]->cd();
    h_relEWKcont_numerator_ele[j]->Draw();h_relEWKcont_numerator_ele[j]->GetYaxis()->SetRangeUser(0,1);h_relEWKcont_numerator_ele[j]->SetTitle(Form("Electron EWK contamination (numerator) (jet pt > %dGeV)",j*5+10)); h_relEWKcont_numerator_ele[j]->GetYaxis()->SetTitle("EWK MC/DATA");h_relEWKcont_numerator_ele[j]->GetXaxis()->SetTitle("p_{T} [GeV]");c[1][0][j]->SetGridx(1);c[1][0][j]->SetGridy(1);c[1][0][j]->SaveAs(Form("EWK_contamination_ele_numerator_jet%d.png",j*5+10));
    h_relEWKcont_denominator_ele[j]->Draw();h_relEWKcont_denominator_ele[j]->GetYaxis()->SetRangeUser(0,1);h_relEWKcont_denominator_ele[j]->SetTitle(Form("Electron EWK contamination (denominator) (jet pt > %dGeV) ",j*5+10)); h_relEWKcont_denominator_ele[j]->GetYaxis()->SetTitle("EWK MC/DATA");h_relEWKcont_denominator_ele[j]->GetXaxis()->SetTitle("p_{T} [GeV]");c[1][0][j]->SetGridx(1);c[1][0][j]->SetGridy(1);c[1][0][j]->SaveAs(Form("EWK_contamination_ele_denominator_jet%d.png",j*5+10));
    c[1][1][j]= new TCanvas();c[1][1][j]->cd();
    h_relEWKcont_numerator_mu[j]->Draw();h_relEWKcont_numerator_mu[j]->GetYaxis()->SetRangeUser(0,1);h_relEWKcont_numerator_mu[j]->SetTitle(Form("Muon EWK contamination (numerator) (jet pt > %dGeV)",j*5+10)); h_relEWKcont_numerator_mu[j]->GetYaxis()->SetTitle("EWK MC/DATA");h_relEWKcont_numerator_mu[j]->GetXaxis()->SetTitle("p_{T} [GeV]");c[1][1][j]->SetGridx(1);c[1][1][j]->SetGridy(1);c[1][1][j]->SaveAs(Form("EWK_contamination_mu_numerator_jet%d.png",j*5+10));
    h_relEWKcont_denominator_mu[j]->Draw();h_relEWKcont_denominator_mu[j]->GetYaxis()->SetRangeUser(0,1);h_relEWKcont_denominator_mu[j]->SetTitle(Form("Muon EWK contamination (denominator) (jet pt > %dGeV)",j*5+10)); h_relEWKcont_denominator_mu[j]->GetYaxis()->SetTitle("EWK MC/DATA");h_relEWKcont_denominator_mu[j]->GetXaxis()->SetTitle("p_{T} [GeV]");c[1][1][j]->SetGridx(1);c[1][1][j]->SetGridy(1);c[1][1][j]->SaveAs(Form("EWK_contamination_mu_denominator_jet%d.png",j*5+10));

    c[2][0][j]= new TCanvas();c[2][0][j]->cd();
    h_div_eta_ele[j]->Draw("E"); h_div_eta_ele[j]->GetYaxis()->SetRangeUser(0,1); h_div_eta_ele[j]->SetTitle(Form("Electron FR (jet pt > %dGeV)",j*5+10)); h_div_eta_ele[j]->SetLineColor(2); h_div_eta_ele[j]->GetXaxis()->SetTitle("|#eta|"); h_div_eta_ele[j]->GetYaxis()->SetTitle("Ele fake rate");c[2][0][j]->SetGridx(1);c[2][0][j]->SetGridy(1); h_div_eta_ele[j]->SetLineWidth(2); h_div_eta_ele[j]->SetMarkerColor(2);  h_div_eta_ele[j]->SetMarkerStyle(kFullCircle);
    h_div_noEWKcorr_eta_ele[j]->Draw("sameE"); h_div_noEWKcorr_eta_ele[j]->SetLineColor(1);h_div_noEWKcorr_eta_ele[j]->SetLineWidth(2); h_div_noEWKcorr_eta_ele[j]->SetMarkerColor(1);  h_div_noEWKcorr_eta_ele[j]->SetMarkerStyle(kFullCircle);
    leg->Draw();c[2][0][j]->SaveAs(Form("eleFR_eta_jet%d.png",j*5+10));
    c[2][1][j]= new TCanvas();c[2][1][j]->cd();
    h_div_eta_mu[j]->Draw("E"); h_div_eta_mu[j]->GetYaxis()->SetRangeUser(0,1); h_div_eta_mu[j]->SetTitle(Form("Muon FR (jet pt > %dGeV)",j*5+10)); h_div_eta_mu[j]->SetLineColor(2); h_div_eta_mu[j]->GetXaxis()->SetTitle("|#eta|"); h_div_eta_mu[j]->GetYaxis()->SetTitle("Mu fake rate");c[2][1][j]->SetGridx(1);c[2][1][j]->SetGridy(1); h_div_eta_mu[j]->SetLineWidth(2); h_div_eta_mu[j]->SetMarkerColor(2);  h_div_eta_mu[j]->SetMarkerStyle(kFullCircle);
    h_div_noEWKcorr_eta_mu[j]->Draw("sameE"); h_div_noEWKcorr_eta_mu[j]->SetLineColor(1);h_div_noEWKcorr_eta_mu[j]->SetLineWidth(2); h_div_noEWKcorr_eta_mu[j]->SetMarkerColor(1);  h_div_noEWKcorr_eta_mu[j]->SetMarkerStyle(kFullCircle);
    leg->Draw();c[2][1][j]->SaveAs(Form("muFR_eta_jet%d.png",j*5+10));

  }
  
  /////////////Combined plots//////////////////////

  TLegend *combinedleg= new TLegend(0.1,0.7,0.48,0.9);
  combinedleg->AddEntry(h_div_ele[0],"jet pt >10 GeV");
  combinedleg->AddEntry(h_div_ele[1],"jet pt >15 GeV");
  combinedleg->AddEntry(h_div_ele[2],"jet pt >20 GeV");
  combinedleg->AddEntry(h_div_ele[3],"jet pt >25 GeV");
  combinedleg->AddEntry(h_div_ele[4],"jet pt >30 GeV");
  combinedleg->AddEntry(h_div_ele[5],"jet pt >35 GeV");
  combinedleg->AddEntry(h_div_ele[6],"jet pt >40 GeV");
  combinedleg->AddEntry(h_div_ele[7],"jet pt >45 GeV");

  TCanvas* combined_pt_ele= new TCanvas();
  combined_pt_ele->cd();
  h_div_ele[0]->Draw(); h_div_ele[0]->GetYaxis()->SetRangeUser(0,1); h_div_ele[0]->SetTitle("Electron fake rate"); h_div_ele[0]->GetXaxis()->SetTitle("p_{T} [GeV]"); h_div_ele[0]->GetYaxis()->SetTitle("Ele fake rate");combined_pt_ele->SetGridx(1);combined_pt_ele->SetGridy(1); h_div_ele[0]->SetLineWidth(2);  h_div_ele[0]->SetMarkerStyle(kFullCircle); h_div_ele[0]->SetLineColor(6); h_div_ele[0]->SetMarkerColor(6);
  for(int j=1;j<5;j++){h_div_ele[j]->Draw("same"); h_div_ele[j]->SetLineColor(j); h_div_ele[j]->SetMarkerColor(j); h_div_ele[j]->SetLineWidth(2);  h_div_ele[j]->SetMarkerStyle(kFullCircle);}
  h_div_ele[5]->Draw("same"); h_div_ele[5]->SetLineColor(17); h_div_ele[5]->SetMarkerColor(17); h_div_ele[5]->SetLineWidth(2);  h_div_ele[5]->SetMarkerStyle(kFullCircle);
  for(int j=6;j<8;j++){h_div_ele[j]->Draw("same"); h_div_ele[j]->SetLineColor(j+1); h_div_ele[j]->SetMarkerColor(j+1); h_div_ele[j]->SetLineWidth(2);  h_div_ele[j]->SetMarkerStyle(kFullCircle);}
  combinedleg->Draw(); combined_pt_ele->SaveAs("combined_pt_eleFR.png");

  TCanvas* combined_pt_mu= new TCanvas();
  combined_pt_mu->cd();
  h_div_mu[0]->Draw(); h_div_mu[0]->GetYaxis()->SetRangeUser(0,1); h_div_mu[0]->SetTitle("Muon fake rate"); h_div_mu[0]->GetXaxis()->SetTitle("p_{T} [GeV]"); h_div_mu[0]->GetYaxis()->SetTitle("Mu fake rate");combined_pt_mu->SetGridx(1);combined_pt_mu->SetGridy(1); h_div_mu[0]->SetLineWidth(2);  h_div_mu[0]->SetMarkerStyle(kFullCircle); h_div_mu[0]->SetLineColor(6); h_div_mu[0]->SetMarkerColor(6);
  for(int j=1;j<5;j++){h_div_mu[j]->Draw("same"); h_div_mu[j]->SetLineColor(j); h_div_mu[j]->SetMarkerColor(j); h_div_mu[j]->SetLineWidth(2);  h_div_mu[j]->SetMarkerStyle(kFullCircle);}
  h_div_mu[5]->Draw("same"); h_div_mu[5]->SetLineColor(17); h_div_mu[5]->SetMarkerColor(17); h_div_mu[5]->SetLineWidth(2);  h_div_mu[5]->SetMarkerStyle(kFullCircle);
  for(int j=6;j<8;j++){h_div_mu[j]->Draw("same"); h_div_mu[j]->SetLineColor(j+1); h_div_mu[j]->SetMarkerColor(j+1); h_div_mu[j]->SetLineWidth(2);  h_div_mu[j]->SetMarkerStyle(kFullCircle);}
  combinedleg->Draw();combined_pt_mu->SaveAs("combined_pt_muFR.png");

  TCanvas* combined_eta_ele= new TCanvas(); 
  combined_eta_ele->cd();
  h_div_eta_ele[0]->Draw(); h_div_eta_ele[0]->GetYaxis()->SetRangeUser(0,1); h_div_eta_ele[0]->SetTitle("Electron fake rate"); h_div_eta_ele[0]->GetXaxis()->SetTitle("|#eta|"); h_div_eta_ele[0]->GetYaxis()->SetTitle("Ele fake rate");combined_eta_ele->SetGridx(1);combined_eta_ele->SetGridy(1); h_div_eta_ele[0]->SetLineWidth(2);  h_div_eta_ele[0]->SetMarkerStyle(kFullCircle); h_div_eta_ele[0]->SetLineColor(6); h_div_eta_ele[0]->SetMarkerColor(6);
  for(int j=1;j<5;j++){h_div_eta_ele[j]->Draw("same"); h_div_eta_ele[j]->SetLineColor(j); h_div_eta_ele[j]->SetMarkerColor(j); h_div_eta_ele[j]->SetLineWidth(2);  h_div_eta_ele[j]->SetMarkerStyle(kFullCircle);}
  h_div_eta_ele[5]->Draw("same"); h_div_eta_ele[5]->SetLineColor(17); h_div_eta_ele[5]->SetMarkerColor(17); h_div_eta_ele[5]->SetLineWidth(2);  h_div_eta_ele[5]->SetMarkerStyle(kFullCircle);
  for(int j=6;j<8;j++){h_div_eta_ele[j]->Draw("same"); h_div_eta_ele[j]->SetLineColor(j+1); h_div_eta_ele[j]->SetMarkerColor(j+1); h_div_eta_ele[j]->SetLineWidth(2);  h_div_eta_ele[j]->SetMarkerStyle(kFullCircle);}
  combinedleg->Draw();combined_eta_ele->SaveAs("combined_eta_eleFR.png");

  TCanvas* combined_eta_mu= new TCanvas();
  combined_eta_mu->cd();
  h_div_eta_mu[0]->Draw(); h_div_eta_mu[0]->GetYaxis()->SetRangeUser(0,1); h_div_eta_mu[0]->SetTitle("Muon fake rate"); h_div_eta_mu[0]->GetXaxis()->SetTitle("|#eta|"); h_div_eta_mu[0]->GetYaxis()->SetTitle("Mu fake rate");combined_eta_mu->SetGridx(1);combined_eta_mu->SetGridy(1); h_div_eta_mu[0]->SetLineWidth(2);  h_div_eta_mu[0]->SetMarkerStyle(kFullCircle); h_div_eta_mu[0]->SetLineColor(6); h_div_eta_mu[0]->SetMarkerColor(6);
  for(int j=1;j<5;j++){h_div_eta_mu[j]->Draw("same"); h_div_eta_mu[j]->SetLineColor(j); h_div_eta_mu[j]->SetMarkerColor(j); h_div_eta_mu[j]->SetLineWidth(2);  h_div_eta_mu[j]->SetMarkerStyle(kFullCircle);}
  h_div_eta_mu[5]->Draw("same"); h_div_eta_mu[5]->SetLineColor(17); h_div_eta_mu[5]->SetMarkerColor(17); h_div_eta_mu[5]->SetLineWidth(2);  h_div_eta_mu[5]->SetMarkerStyle(kFullCircle);
  for(int j=6;j<8;j++){h_div_eta_mu[j]->Draw("same"); h_div_eta_mu[j]->SetLineColor(j+1); h_div_eta_mu[j]->SetMarkerColor(j+1); h_div_eta_mu[j]->SetLineWidth(2);  h_div_eta_mu[j]->SetMarkerStyle(kFullCircle);}
  combinedleg->Draw();combined_eta_mu->SaveAs("combined_eta_muFR.png");

  

  /////////Rootfiles with 2D histograms//////////
  
  for(int j=0;j<8;j++){
    TFile* root_elefile = new TFile(Form("EleFR_jet%d.root",10+j*5), "recreate");
    FR_pT_eta_ele[j]->SetTitle(Form("FR_pT_eta_ele_jet%d",10+j*5));                                            FR_pT_eta_ele[j]->Write();  
    FR_pT_eta_numerator_ele[j]->SetTitle(Form("FR_pT_eta_numerator_ele_jet%d",10+j*5));                        FR_pT_eta_numerator_ele[j]->Write(); 
    FR_pT_eta_denominator_ele[j]->SetTitle(Form("FR_pT_eta_denominator_ele_jet%d",10+j*5));                    FR_pT_eta_denominator_ele[j]->Write();
    FR_pT_eta_EWKcorr_ele[j]->SetTitle(Form("FR_pT_eta_EWKcorr_ele_jet%d",10+j*5));                            FR_pT_eta_EWKcorr_ele[j]->Write();
    FR_pT_eta_EWKcorr_numerator_ele[j]->SetTitle(Form("FR_pT_eta_EWKcorr_numerator_ele_jet%d",10+j*5));        FR_pT_eta_EWKcorr_numerator_ele[j]->Write();
    FR_pT_eta_EWKcorr_denominator_ele[j]->SetTitle(Form("FR_pT_eta_EWKcorr_denominator_ele_jet%d",10+j*5));    FR_pT_eta_EWKcorr_denominator_ele[j]->Write();
    root_elefile->Close();

    TFile* root_mufile = new TFile(Form("MuonFR_jet%d.root",10+j*5), "recreate");
    FR_pT_eta_mu[j]->SetTitle(Form("FR_pT_eta_mu_jet%d",10+j*5));                                            FR_pT_eta_mu[j]->Write();  
    FR_pT_eta_numerator_mu[j]->SetTitle(Form("FR_pT_eta_numerator_mu_jet%d",10+j*5));                        FR_pT_eta_numerator_mu[j]->Write(); 
    FR_pT_eta_denominator_mu[j]->SetTitle(Form("FR_pT_eta_denominator_mu_jet%d",10+j*5));                    FR_pT_eta_denominator_mu[j]->Write();
    FR_pT_eta_EWKcorr_mu[j]->SetTitle(Form("FR_pT_eta_EWKcorr_mu_jet%d",10+j*5));                            FR_pT_eta_EWKcorr_mu[j]->Write();
    FR_pT_eta_EWKcorr_numerator_mu[j]->SetTitle(Form("FR_pT_eta_EWKcorr_numerator_mu_jet%d",10+j*5));        FR_pT_eta_EWKcorr_numerator_mu[j]->Write();
    FR_pT_eta_EWKcorr_denominator_mu[j]->SetTitle(Form("FR_pT_eta_EWKcorr_denominator_mu_jet%d",10+j*5));    FR_pT_eta_EWKcorr_denominator_mu[j]->Write();
    root_mufile->Close();
  }
  
cout<<"THE END"<<endl;
}



 
