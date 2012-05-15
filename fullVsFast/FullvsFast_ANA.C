#include "FullvsFast_ANA.h"

void fullVsFast::BookHistos(){

	nBJets1DHist 	= new TH1D("BJet Multiplicity", "BJet Multiplicity", 16, 0, 16);
	nJets1DHist 	= new TH1D("Jet Multiplicity", "Jet Multiplicity", 16, 0, 16);
	HT1DHist		= new TH1D("HT Distribution", "HT Distribution", 750, 0., 1500.);
	MHTMET1DHist	= new TH1D("MHT over MET Distribution", "MHT over MET Distribution", 1000,0.,10.);
	MHT1DHist		= new TH1D("MHT Distribution", "MHT Distribution", 750, 0., 1500.);
	alphaT1DHist	= new TH1D("#alpha_{T} Distribution", "#alpha_{T} Distribution", 800,0.,10.);
	bJetPt1DHist	= new TH1D("BJet pT Distribution", "BJet pT Distribution", 500, 0., 1000.);
	bJetEta1DHist	= new TH1D("BJet #eta Distribution", "BJet #eta Distribution", 200, -10., 10.);
	bJetPhi1DHist	= new TH1D("BJet #phi Distribution", "BJet #phi Distribution", 200, -4, 4);
	leadJetPt1DHist	= new TH1D("Leading Jet Pt Distribution", "Leading Jet Pt Distribution", 500, 0., 1000.);
	muonPhi1DHist	= new TH1D("Muon phi", "Muon phi", 200, 0., 6.5);

}

TH1D* fullVsFast::getBJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, float scaleF){
	//want to get the plots nbjet_CommJetgeq2_h_<N>;1

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

	nBJets1DHist->Scale(scaleF);

	return nBJets1DHist;

}

TH1D* fullVsFast::getJetMultiHist(TFile* inFile, std::vector<TString> vHTBins, float scaleF){
	//want to get the plots njet_CommJetgeq2_h_<N>;1

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

	nJets1DHist->Scale(scaleF);

	return nJets1DHist;

}


TH1D* fullVsFast::getGenericObjHist(TFile* inFile, std::vector<TString> vHTBins, TString histName, float scaleF, TH2D* h2D, TH1D* h1D, float normF, float binOffset){

	std::vector<TFile*> vInFiles;
	std::vector<TString> hNames;
	playHist2D factor=playHist2D(); //create playHist2D with default constructor

	vInFiles.push_back(inFile);
	hNames.push_back(histName);

	h1D->Reset("ICES");

	h2D = factor.addHistForDiffFoldersAndFiles2D(vInFiles,vHTBins, hNames.at(0));
	for(int i=0;i<h2D->GetXaxis()->GetNbins();i++){
		for(int j=0;j<h2D->GetYaxis()->GetNbins();j++){
			h1D->Fill( ((i+1)*normF)-binOffset, h2D->GetBinContent(i+1,j+1) );
		}
	}

	h1D->Scale(scaleF);

	return h1D;

}

//-------------------------------------------------//

void fullVsFast::runAnalysis(){

	TCanvas c2;
	TString inFileNameFull, inFileNameFast;
	std::vector<TString> vHTBins;

	inFileNameFull = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/T1tttt_fullSim_allbins.root";
	inFileNameFast = "/Users/cl7359/SUSY/FastvsFullStudy/data_files/T1tttt_fastSim_allbins.root";

	TFile *inFileFull = TFile::Open(inFileNameFull, "r");
	TFile *inFileFast = TFile::Open(inFileNameFast, "r");

	BookHistos();

	//fill vectors
	vHTBins.push_back("275-325");
	vHTBins.push_back("325_375");
	vHTBins.push_back("375_475");
	vHTBins.push_back("475_575");
	vHTBins.push_back("575_675");
	vHTBins.push_back("675_775");
	vHTBins.push_back("775_875");
	vHTBins.push_back("875");

	//calculate scaling factor for full->fast event size
	float fullToFastScale = 3346000./550600.;


	TH1D aT1 = *getGenericObjHist(inFileFull, vHTBins, "AlphaT_CommJetgeq2_h_all;1", fullToFastScale, alphaT2DHist, alphaT1DHist, 1./100.);
	aT1.SetLineColor(kBlue);
	aT1.GetXaxis()->SetRangeUser(0,1);
	aT1.Draw();

	TH1D aT2 = *getGenericObjHist(inFileFast, vHTBins, "AlphaT_CommJetgeq2_h_all;1", 1., alphaT2DHist, alphaT1DHist, 1./100.);
	aT2.SetLineColor(kRed);
	aT2.GetXaxis()->SetRangeUser(0,1);
	aT2.Draw("SAME");

	c2.Print("Output.pdf(");



	TH1D bJM1 = *getBJetMultiHist(inFileFull, vHTBins, fullToFastScale);
	bJM1.SetLineColor(kBlue);
	bJM1.GetXaxis()->SetRangeUser(0,10);
	bJM1.Draw();

	TH1D bJM2 = *getBJetMultiHist(inFileFast, vHTBins, 1.);
	bJM2.SetLineColor(kRed);
	bJM2.GetXaxis()->SetRangeUser(0,10);

	bJM2.Draw();
	bJM1.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D jM1 = *getJetMultiHist(inFileFull, vHTBins, fullToFastScale);
	jM1.SetLineColor(kBlue);
	jM1.Draw();

	TH1D jM2 = *getJetMultiHist(inFileFast, vHTBins, 1.);
	jM2.SetLineColor(kRed);
	jM2.Draw();
	jM1.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D bJPt1 = *getGenericObjHist(inFileFull, vHTBins, "bjetPt_CommJetgeq2_h__all;1", fullToFastScale, bJetPt2DHist, bJetPt1DHist);
	bJPt1.SetLineColor(kBlue);
	bJPt1.Draw();

	TH1D bJPt2 = *getGenericObjHist(inFileFast, vHTBins, "bjetPt_CommJetgeq2_h__all;1", 1., bJetPt2DHist, bJetPt1DHist);
	bJPt2.SetLineColor(kRed);
	bJPt2.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D bJEta1 = *getGenericObjHist(inFileFull, vHTBins, "bjetEta_CommJetgeq2_h__all;1", fullToFastScale, bJetEta2DHist, bJetEta1DHist, 1./10., 10.);
	bJEta1.SetLineColor(kBlue);
	bJEta1.GetXaxis()->SetRangeUser(-5,5);
	bJEta1.Draw();

	TH1D bJEta2 = *getGenericObjHist(inFileFast, vHTBins, "bjetEta_CommJetgeq2_h__all;1", 1., bJetEta2DHist, bJetEta1DHist, 1./10., 10.);
	bJEta2.SetLineColor(kRed);
	bJEta2.GetXaxis()->SetRangeUser(-5,5);
	bJEta2.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D bJPhi1 = *getGenericObjHist(inFileFull, vHTBins, "bjetPhi_CommJetgeq2_h__all;1", fullToFastScale, bJetPhi2DHist, bJetPhi1DHist, 6.5/200.);
	bJPhi1.SetLineColor(kBlue);
	bJPhi1.GetXaxis()->SetRangeUser(-0.1,3.5);
	bJPhi1.Draw();

	TH1D bJPhi2 = *getGenericObjHist(inFileFast, vHTBins, "bjetPhi_CommJetgeq2_h__all;1", 1.1, bJetPhi2DHist, bJetPhi1DHist, 6.5/200.);
	bJPhi2.SetLineColor(kRed);
	bJPhi2.GetXaxis()->SetRangeUser(-0.1,3.5);
	bJPhi2.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D leadJPt1 = *getGenericObjHist(inFileFull, vHTBins, "leadJetPt_CommJetgeq2_h__all;1", fullToFastScale, leadJetPt2DHist, leadJetPt1DHist);
	leadJPt1.SetLineColor(kBlue);


	TH1D leadJPt2 = *getGenericObjHist(inFileFast, vHTBins, "leadJetPt_CommJetgeq2_h__all;1", 1.1, leadJetPt2DHist, leadJetPt1DHist);
	leadJPt2.SetLineColor(kRed);
	leadJPt2.Draw();
	leadJPt1.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D HT1 = *getGenericObjHist(inFileFull, vHTBins, "HT_CommJetgeq2_h_all;1", fullToFastScale, HT2DHist, HT1DHist);
	HT1.SetLineColor(kBlue);
	HT1.Draw();

	TH1D HT2 = *getGenericObjHist(inFileFast, vHTBins, "HT_CommJetgeq2_h_all;1", 1.1, HT2DHist, HT1DHist);
	HT2.SetLineColor(kRed);
	HT2.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D MHT1 = *getGenericObjHist(inFileFull, vHTBins, "MHT_CommJetgeq2_h_all;1", fullToFastScale, MHT2DHist, MHT1DHist);
	MHT1.SetLineColor(kBlue);
	MHT1.Draw();

	TH1D MHT2 = *getGenericObjHist(inFileFast, vHTBins, "MHT_CommJetgeq2_h_all;1", 1.1, MHT2DHist, MHT1DHist);
	MHT2.SetLineColor(kRed);
	MHT2.Draw("SAME");

	c2.Print("Output.pdf");



	TH1D MHTMET1 = *getGenericObjHist(inFileFull, vHTBins, "MHToverMET_CommJetgeq2_h_all;1", fullToFastScale, MHTMET2DHist, MHTMET1DHist, 1./100.);
	MHTMET1.SetLineColor(kBlue);
	MHTMET1.GetXaxis()->SetRangeUser(0,1.5);


	TH1D MHTMET2 = *getGenericObjHist(inFileFast, vHTBins, "MHToverMET_CommJetgeq2_h_all;1", 1.1, MHTMET2DHist, MHTMET1DHist, 1./100.);
	MHTMET2.SetLineColor(kRed);
	MHTMET2.GetXaxis()->SetRangeUser(0,1.5);
	MHTMET2.Draw();
	MHTMET1.Draw("SAME");

	c2.Print("Output.pdf)");
}
