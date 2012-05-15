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

		TH1D* getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, float scaleF = 1.);
		TH1D* getJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, float scaleF = 1.);
		TH1D* getGenericObjHist(TFile* inFile, std::vector<TString> vHTBins, TString histName, float scaleF, TH2D* h2D, TH1D* h1D, float normF = 1., float binOffset = 0.);
		void runAnalysis();

	private:
		void BookHistos();

		TH2D* nBJets2DHist[17];
		TH2D* nJets2DHist[17];
		TH2D* HT2DHist;
		TH2D* MHTMET2DHist;
		TH2D* MHT2DHist;
		TH2D* alphaT2DHist;
		TH2D* bJetPt2DHist;
		TH2D* bJetEta2DHist;
		TH2D* bJetPhi2DHist;
		TH2D* leadJetPt2DHist;
		TH2D* muonPhi2DHist;

		TH1D* nBJets1DHist;
		TH1D* nJets1DHist;
		TH1D* HT1DHist;
		TH1D* MHTMET1DHist;
		TH1D* MHT1DHist;
		TH1D* alphaT1DHist;
		TH1D* bJetPt1DHist;
		TH1D* bJetEta1DHist;
		TH1D* bJetPhi1DHist;
		TH1D* leadJetPt1DHist;
		TH1D* muonPhi1DHist;

};

#endif
