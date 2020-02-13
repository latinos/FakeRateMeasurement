//------------------------------------------------------------------------------
//
//      Target: Produce fake and prompt rates
//      Authors: Jonatan Piedra, Cedric Prieels
//      Last update: May 10th, 2019
//
//------------------------------------------------------------------------------
TString path_mc   = "";
TString path_data = "";


std::string to_string(int i)
{
  std::stringstream ss;
  ss << i;
  return ss.str();
}


void runNanoFakes(TString year = "2017", TString filename = "NONE")
{
  if (year == "2016")
    {
      path_mc   = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Summer16_102X_nAODv5_Full2016v6/MCl1loose2016v6__MCCorr2016v6/";
      //path_mc   = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Summer16_102X_nAODv4_Full2016v5/MCl1loose2016v5__MCCorr2016v5/";
      path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2016_102X_nAODv5_Full2016v6/DATAl1loose2016v6/";
      //path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2016_102X_nAODv4_Full2016v5/DATAl1loose2016v5__fakeSel/";
    }
  else if (year == "2017")
    {
      path_mc   = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Fall2017_102X_nAODv5_Full2017v6/MCl1loose2017v6__fakeSelKinMC/";
      path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2017_102X_nAODv5_Full2017v6/DATAl1loose2017v6/";
    }
  else if (year == "2018")
    {
      path_mc   = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Autumn18_102X_nAODv5_Full2018v6/MCl1loose2018v6__fakeSelKinMC/";
      path_data = "/eos/cms/store/group/phys_higgs/cmshww/amassiro/HWWNano/Run2018_102X_nAODv5_Full2018v6/DATAl1loose2018v6/";
    }
  else
    {
      printf(" The year should be either 2016, 2017 or 2018\n");
      return;
    }

  if (filename.EqualTo("NONE"))
    {
      printf("\n Examples\n\n");
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_DoubleMuon_Run2017C-31Mar2018-v1__part0\")\'\n", year.Data());
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_SingleElectron_Run2017C-31Mar2018-v1__part0\")\'\n", year.Data());
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_WJetsToLNu-LO__part0\")\'\n", year.Data());
      printf(" root -l -b -q \'runNanoFakes.C(\"%s\", \"nanoLatino_DYJetsToLL_M-50__part0\")\'\n", year.Data());
      printf("\n");

      return;
    }
  
  TString path = (filename.Contains("Run201")) ? path_data : path_mc;

  TChain* mychain = new TChain("Events", "Events");

  mychain->Add(path + filename + ".root");

  printf("\n Executing mychain->Process(\"nanoFakes.C+\")...\n\n");

  TString option = year + filename;

//mychain->Process("/afs/cern.ch/user/c/cprieels/work/public/Fakes/CMSSW_10_1_0/src/getFakeRate/nanoFakes.C+", option);
  mychain->Process("nanoFakes.C+", option);
  
  return;
}
