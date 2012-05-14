#include "FullvsFast_ANA.h"

void fullVsFast::BookHistos(){

	nBJets1DHist 	= new TH1D("BJet Multiplicity", "BJet Multiplicity", 16, 0, 16);
	nJets1DHist 	= new TH1D("Jet Multiplicity", "Jet Multiplicity", 16, 0, 16);
	HT1DHist		= new TH1D("HT Distribution", "HT Distribution", 1500, 0., 1500.);
	MHTMET1DHist	= new TH1D("MHT over MET Distribution", "MHT over MET Distribution", 1000,0.,10.);
	MHT1DHist		= new TH1D("MHT Distribution", "MHT Distribution", 1500, 0., 1500.);
	alphaT1DHist	= new TH1D("#alpha_{T} Distribution", "#alpha_{T} Distribution", 1000,0.,10.);

}

TH1D* fullVsFast::getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins){
	//want to get the plots nbjet_CommJetgeq2_h_<N>;1
	std::cout << "Getting BJet Multiplicity" << std::endl;

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);

	//load histograms into vector
	for(int i=1;i<17;i++){
		std::ostringstream inHistName;
		inHistName << "nbjet_CommJetgeq2_h_" << i <<";1";
		hNames.push_back(inHistName.str().c_str());
	}

	//sum every nbjets plot
	for(int i=0; i<16; i++){
		nBJets2DHist[i] = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(i));
		TH1D* h = nBJets2DHist[i]->ProjectionX();
		nBJets1DHist->Add(h);
	}

	return nBJets1DHist;

}

TH1D* fullVsFast::getJetMultiHist(TFile* inFile, std::vector<TString> vHTBins){
	//want to get the plots njet_CommJetgeq2_h_<N>;1
	std::cout << "Getting Jet Multiplicity" << std::endl;

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);

	//load histograms into vector
	for(int i=1;i<17;i++){
		std::ostringstream inHistName;
		inHistName << "njet_CommJetgeq2_h_" << i <<";1";
		hNames.push_back(inHistName.str().c_str());
	}

	//sum every njets plot
	for(int i=0; i<16; i++){
		nJets2DHist[i] = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(i));
		TH1D* h1 = nJets2DHist[i]->ProjectionX();
		nJets1DHist->Add(h1);
	}

	return nJets1DHist;

}

TH1D* fullVsFast::getHTHist(TFile* inFile, std::vector<TString> vHTBins){
	//want to get the plots HT_CommJetgeq2_h_<N>;1
	std::cout << "Getting HT Distribution" << std::endl;

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();

	//this appears to be only including the last plot...

	vInFiles.push_back(inFile);

	//load histograms into vector
	TString histName = "HT_CommJetgeq2_h_all;1";
	hNames.push_back(histName);


	HT2DHist = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(0));

	for(int i=0;i<HT2DHist->GetXaxis()->GetNbins();i++){
		for(int j=0;j<HT2DHist->GetYaxis()->GetNbins();j++){
			float normF = 1500./1500.;
			HT1DHist->Fill((i+1)*normF,HT2DHist->GetBinContent(i+1,j+1));
		}
	}

	return HT1DHist;

}

TH1D* fullVsFast::getMHTMETHist(TFile* inFile, std::vector<TString> vHTBins){

	//want to get the plots MHToverMET_CommJetgeq2_h_<N>;1
	std::cout << "Getting MHT over MET Distribution" << std::endl;

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);
	//load histograms into vector
	TString histName = "MHToverMET_CommJetgeq2_h_all;1";
	hNames.push_back(histName);

	//
	MHTMET2DHist = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(0));

	for(int i=0;i<MHTMET2DHist->GetXaxis()->GetNbins();i++){
		for(int j=0;j<MHTMET2DHist->GetYaxis()->GetNbins();j++){
			float normF = 10./1000.;
			MHTMET1DHist->Fill((i+1)*normF,MHTMET2DHist->GetBinContent(i+1,j+1));
		}
	}

	return MHTMET1DHist;

}

TH1D* fullVsFast::getMHTHist(TFile* inFile, std::vector<TString> vHTBins){

	//want to get the plots MHT_CommJetgeq2_h_<N>;1
	std::cout << "Getting MHT Distribution" << std::endl;

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();


	vInFiles.push_back(inFile);
	//load histograms into vector
	TString histName = "MHT_CommJetgeq2_h_all;1";
	hNames.push_back(histName);

	//
	MHT2DHist = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(0));

	for(int i=0;i<MHT2DHist->GetXaxis()->GetNbins();i++){
		for(int j=0;j<MHT2DHist->GetYaxis()->GetNbins();j++){
			float normF = 1500./1500.;
			MHT1DHist->Fill((i+1)*normF,MHT2DHist->GetBinContent(i+1,j+1));
		}
	}

	return MHT1DHist;

}

TH1D* fullVsFast::getAlphaTHist(TFile* inFile, std::vector<TString> vHTBins){
	//want to get the plots AlphaT_CommJetgeq2_h_<N>;1
	std::cout << "Getting AlphaT Distribution" << std::endl;

	TCanvas c1;
	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;

	playHist2D factor=playHist2D();

	//this appears to be only including the last plot...

	vInFiles.push_back(inFile);

	//load histograms into vector
	TString histName = "AlphaT_CommJetgeq2_h_all;1";
	hNames.push_back(histName);


	alphaT2DHist = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(0));

	for(int i=0;i<alphaT2DHist->GetXaxis()->GetNbins();i++){
		for(int j=0;j<alphaT2DHist->GetYaxis()->GetNbins();j++){
			float normF = 10./1000.;
			alphaT1DHist->Fill((i+1)*normF,alphaT2DHist->GetBinContent(i+1,j+1));
		}
	}

	return alphaT1DHist;

}

//-------------------------------------------------//

void fullVsFast::runAnalysis(){

	TCanvas c2;
	TString inFileName;
	std::vector<TString> vHTBins;

	inFileName = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/AK5Calo_SMS_T1ttttProtoScan_Mgluino_350to1200_mLSP_0to400_8TeV_Pythia6Z_StoreResults_PU_START52_V5_FullSim_v1_V17_pre4_taus_0_jetCorrections_L1FastJet_L2Relative_L3Absolute_L2L3Residual_jetCollections_ak5calo_ak5pf_clucasJob108_all.root";

	TFile *inFile = TFile::Open(inFileName, "r");

	BookHistos();

	//fill vectors
	//vHTBins->push_back("275-325");
	//vHTBins->push_back("325-375");
	vHTBins.push_back("375-475");
	vHTBins.push_back("475-575");
	vHTBins.push_back("575-675");
	vHTBins.push_back("675-775");
	vHTBins.push_back("775-875");
	vHTBins.push_back("875");


	TH1D* h1 = getAlphaTHist(inFile, vHTBins);
	h1->GetXaxis()->SetRangeUser(0,1);
	h1->Draw();

	c2.Print("Output.pdf(");

	getBJetMultiHist(inFile, vHTBins)->Draw();
	c2.Print("Output.pdf");

	getJetMultiHist(inFile, vHTBins)->Draw();
	c2.Print("Output.pdf");

	getHTHist(inFile, vHTBins)->Draw();
	c2.Print("Output.pdf");

	getMHTHist(inFile, vHTBins)->Draw();
	c2.Print("Output.pdf");

	getMHTMETHist(inFile, vHTBins)->Draw();
	c2.Print("Output.pdf)");

	//need to eventually modify to accept histograms, one from each
	//input file. then plot both on same plot and print to a single
	//pdf


}
