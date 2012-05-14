#ifndef fullVsFast_h
#define fullVsFast_h

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TH2D.h"
#include "TH1D.h"
#include "TFile.h"
#include "TString.h"
#include <stdio.h>
#include "menus.h"
#include "vectors.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "tdrstyle.h"
#include "playHist2D.h"
#include "playHist1D.h"

using namespace std;

class fullVsFast : public menus, public vectors{
	public:
		fullVsFast(){;} //constructor
		~fullVsFast(){;} //destructor

		TH1D* getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins);
		TH1D* getJetMultiHist(TFile* inFile, std::vector<TString> vHTBins);
		TH1D* getHTHist(TFile* inFile, std::vector<TString> vHTBins);
		TH1D* getMHTMETHist(TFile* inFile, std::vector<TString> vHTBins);
		TH1D* getMHTHist(TFile* inFile, std::vector<TString> vHTBins);
		TH1D* getAlphaTHist(TFile* inFile, std::vector<TString> vHTBins);
		void runAnalysis();

	private:
		void BookHistos();

		TH2D* nBJets2DHist[17];
		TH2D* nJets2DHist[17];
		TH2D* HT2DHist;
		TH2D* MHTMET2DHist;
		TH2D* MHT2DHist;
		TH2D* alphaT2DHist;
		TH1D* nBJets1DHist;
		TH1D* nJets1DHist;
		TH1D* HT1DHist;
		TH1D* MHTMET1DHist;
		TH1D* MHT1DHist;
		TH1D* alphaT1DHist;



};

#endif
