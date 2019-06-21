
https://github.com/adrianalvarezf/Fake-rates-code

# How to get the fake rates : 

First of all,

   python condorsubmit_mc.py 2017

(and condorsubmit_data.mc) will send the jobs to condor. You can also use years 2016 and 2018. All the related code is in Fake_rates.C .

Then you use

   ./script_hadd.sh foldername/outputfolder
  
to merge the files and with 

   root -q -b "division_forfakes_withmc.C(\"foldername/outputfolder\")"

you get the plots. 

Finally, to produce a txt table of yields you can use

   root -q "Tableyields.C(25,\"foldername/outputfolder\")"

The 25 means that the cut in the away jet pt is of 25 GeV. To compare muons we use 25GeV and we use 35GeV to compare electrons.


# Btag update :

For 2017 and 2018 the FR is also computed in bins of btagscore. The bins are "bveto", "loose", "mediumtight" and "none", which is used for obtaining the inclusive FR with no btag requirement. After the division_forfakes_withmc.C step you can use the treeadder.C program to make the rootfiles with the 2D histograms than then are used in NanoGardener/python/data/ in the latinos' framework:

    root -b -q "treeadder.C(\"mainfoldername\",\"channel\")"

Channel must be "Ele" or "Muon" for naming consistency. 


