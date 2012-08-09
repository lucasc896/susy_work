#ifndef fullVsFast_h
#define fullVsFast_h

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TH1.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TPad.h"
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

		TH1D* getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, std::vector<TH2D*> h2D, TH1D* h1D, float scaleF = 1.);
		TH1D* getJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, std::vector<TH2D*> h2D, TH1D* h1D, float scaleF = 1.);
		TH1D* getGenericObjHist2D(TFile* inFile, std::vector<TString> vHTBins, TString histName, float scaleF, float normF = 1., float binOffset = 0.);
		void runAnalysis();

	private:
		void BookHistos();

		std::vector<TH2D*> nBJets2DHist;
		std::vector<TH2D*> nJets2DHist;
		
		TH1D* nBJets1DHist;
		TH1D* nJets1DHist;
		

};

#endif
